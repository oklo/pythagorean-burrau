// Interval-Newton certificate for the planar projective light-heavy collision.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
//
// The exact stable graph is represented by the quartic jet plus the analytic
// state and parameter-tangent boxes proved in PLANAR_STABLE_TAIL_ENCLOSURE.md.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "capd/capdlib.h"
#include "capd/dynsys/DynSysMap.h"

namespace {

using capd::C1Rect2Set;
using capd::C0Rect2Set;
using capd::IMap;
using capd::IMatrix;
using capd::IOdeSolver;
using capd::ICoordinateSection;
using capd::IPoincareMap;
using capd::ITimeMap;
using capd::IVector;
using capd::interval;

constexpr double kZetaStart = 15.0;

struct TailData {
  IVector state;
  IVector kappa_tangent;
};

interval symmetric(const interval& radius) {
  return interval(-radius.rightBound(), radius.rightBound());
}

interval exact_integer(const char* digits) {
  return interval(digits, digits);
}

std::string frozen_variables(int count) {
  std::string result;
  for (int index = 0; index < count; ++index) {
    if (!result.empty()) {
      result += ",";
    }
    result += "z" + std::to_string(index);
  }
  return result;
}

std::string frozen_zeros(int count) {
  std::string result;
  for (int index = 0; index < count; ++index) {
    if (!result.empty()) {
      result += ",";
    }
    result += "0";
  }
  return result;
}

std::string frozen_identity(int count) {
  return frozen_variables(count);
}

IMap make_combined_shape_field() {
  return IMap(
      "var:zs,x,y,vx,vy,ls,ur,ui,vr,vi,h,t,R;"
      "fun:1,-vx,-vy,"
      "vx/3-(2*x-(x+1/2)/(((x+1/2)^2+y^2)*sqrt((x+1/2)^2+y^2))"
      "-(x-1/2)/(((x-1/2)^2+y^2)*sqrt((x-1/2)^2+y^2)))/9,"
      "vy/3-(2*y-y/(((x+1/2)^2+y^2)*sqrt((x+1/2)^2+y^2))"
      "-y/(((x-1/2)^2+y^2)*sqrt((x-1/2)^2+y^2)))/9,"
      "0,0,0,0,0,0,0,0;");
}

IMap make_combined_entry_field() {
  return IMap(
      "par:S,V,T;var:zs,x,y,vx,vy,ls,ur,ui,vr,vi,h,t,R;"
      "fun:0,0,0,0,0,0,"
      "sqrt((sqrt((S*(x-1/2))^2+(S*y)^2)+S*(x-1/2))/2),"
      "sqrt((sqrt((S*(x-1/2))^2+(S*y)^2)-S*(x-1/2))/2),"
      "(sqrt((sqrt((S*(x-1/2))^2+(S*y)^2)+S*(x-1/2))/2)"
      "*V*(2*(x-1/2)/3+vx)"
      "+sqrt((sqrt((S*(x-1/2))^2+(S*y)^2)-S*(x-1/2))/2)"
      "*V*(2*y/3+vy))/2,"
      "(sqrt((sqrt((S*(x-1/2))^2+(S*y)^2)+S*(x-1/2))/2)"
      "*V*(2*y/3+vy)"
      "-sqrt((sqrt((S*(x-1/2))^2+(S*y)^2)-S*(x-1/2))/2)"
      "*V*(2*(x-1/2)/3+vx))/2,"
      "(V*(2*(x-1/2)/3+vx))^2/2+(V*(2*y/3+vy))^2/2"
      "-1/sqrt((S*(x-1/2))^2+(S*y)^2),T,S;");
}

IMap make_combined_lc_field() {
  const std::string qx = "(ur^2-ui^2)";
  const std::string qy = "(2*ur*ui)";
  const std::string squared_distance =
      "((" + qx + "+R)^2+" + qy + "^2)";
  const std::string denominator =
      "(" + squared_distance + "*sqrt(" + squared_distance + "))";
  const std::string gx =
      "(1/R^2-(" + qx + "+R)/" + denominator + ")";
  const std::string gy = "(-" + qy + "/" + denominator + ")";
  const std::string force_real =
      "(ur*" + gx + "+ui*" + gy + ")";
  const std::string force_imag =
      "(ur*" + gy + "-ui*" + gx + ")";
  const std::string energy_derivative =
      "(-2*((ur*vr-ui*vi)*" + gx + "+(ur*vi+ui*vr)*" + gy + "))";
  return IMap(
      "var:zs,x,y,vx,vy,ls,ur,ui,vr,vi,h,t,R;"
      "fun:0,0,0,0,0,1,-vr,-vi,"
      "-h*ur/2-(ur^2+ui^2)*" + force_real + "/2,"
      "-h*ui/2-(ur^2+ui^2)*" + force_imag + "/2," +
      energy_derivative + ",- (ur^2+ui^2),"
      "-2*R*(ur^2+ui^2)/(3*t);");
}

IMap make_heavy_binary_bridge_field() {
  const std::string scale = "exp(log(9)/3)";
  const std::string radius = "(" + scale + "*l^2/2)";
  const std::string plus_squared = "((x+" + radius + ")^2+y^2)";
  const std::string minus_squared = "((x-" + radius + ")^2+y^2)";
  const std::string plus_denominator =
      "(" + plus_squared + "*sqrt(" + plus_squared + "))";
  const std::string minus_denominator =
      "(" + minus_squared + "*sqrt(" + minus_squared + "))";
  return IMap(
      "var:l,x,y,vx,vy;"
      "fun:-1,-3*l^2*vx,-3*l^2*vy,"
      "3*l^2*((x+" + radius + ")/" + plus_denominator +
      "+(x-" + radius + ")/" + minus_denominator + "),"
      "3*l^2*(y/" + plus_denominator + "+y/" + minus_denominator + ");");
}

IMap make_positive_exit_to_bridge_map() {
  const std::string scale = "exp(log(9)/3)";
  const std::string lambda = "exp(log(ct)/3)";
  const std::string separation = "(" + scale + "*(" + lambda + ")^2)";
  const std::string selected_norm = "(cr^2+ci^2)";
  const std::string qx = "(cr^2-ci^2)";
  const std::string qy = "(2*cr*ci)";
  const std::string qtx = "(2*(cr*dr-ci*di)/" + selected_norm + ")";
  const std::string qty = "(2*(cr*di+ci*dr)/" + selected_norm + ")";
  return IMap("var:cr,ci,dr,di,ch,ct;fun:" + lambda + "," + qx + "+" +
              separation + "/2," + qy + "," + qtx + "+" + separation +
              "/(3*ct)," + qty + ";");
}

IMap make_bridge_to_negative_entry_map() {
  const std::string scale = "exp(log(9)/3)";
  const std::string half_binary = "(" + scale + "*l^2/2)";
  const std::string qx = "(x+" + half_binary + ")";
  const std::string qnorm = "sqrt((" + qx + ")^2+y^2)";
  const std::string ar = "sqrt((" + qnorm + "+" + qx + ")/2)";
  const std::string ai = "(y/(2*(" + ar + ")))";
  const std::string qtx = "(vx+" + scale + "/(3*l))";
  const std::string br = "((" + ar + ")*(" + qtx + ")+(" + ai + ")*vy)/2";
  const std::string bi = "((" + ar + ")*vy-(" + ai + ")*(" + qtx + "))/2";
  const std::string energy = "((" + qtx + ")^2+vy^2)/2-1/" + qnorm;
  return IMap("var:l,x,y,vx,vy;fun:" + ar + "," + ai + "," + br +
              "," + bi + "," + energy + ",l^3;");
}

IMap make_other_pair_entry_map() {
  const std::string selected_norm = "(ur^2+ui^2)";
  const std::string qx = "(ur^2-ui^2+R)";
  const std::string qy = "(2*ur*ui)";
  const std::string qnorm = "sqrt(" + qx + "^2+" + qy + "^2)";
  const std::string ar = "sqrt((" + qnorm + "+" + qx + ")/2)";
  const std::string ai = "(-sqrt((" + qnorm + "-" + qx + ")/2))";
  const std::string qtx =
      "(2*(ur*vr-ui*vi)/" + selected_norm + "+2*R/(3*t))";
  const std::string qty =
      "(2*(ur*vi+ui*vr)/" + selected_norm + ")";
  const std::string br = "((" + ar + ")*(" + qtx + ")+(" + ai +
                         ")*(" + qty + "))/2";
  const std::string bi = "((" + ar + ")*(" + qty + ")-(" + ai +
                         ")*(" + qtx + "))/2";
  const std::string energy = "((" + qtx + ")^2+(" + qty + ")^2)/2-1/(" +
                             qnorm + ")";
  return IMap("var:zs,x,y,vx,vy,ls,ur,ui,vr,vi,h,t,R;fun:" + ar + "," +
              ai + "," + br + "," + bi + "," + energy + ",t;");
}

IMap make_other_pair_stable_entry_map() {
  const std::string selected_norm = "(ur^2+ui^2)";
  const std::string qx = "(ur^2-ui^2+R)";
  const std::string qy = "(2*ur*ui)";
  const std::string qnorm = "sqrt(" + qx + "^2+" + qy + "^2)";
  const std::string ar = "sqrt((" + qnorm + "+" + qx + ")/2)";
  const std::string ai = "(" + qy + "/(2*(" + ar + ")))";
  const std::string qtx =
      "(2*(ur*vr-ui*vi)/" + selected_norm + "+2*R/(3*t))";
  const std::string qty =
      "(2*(ur*vi+ui*vr)/" + selected_norm + ")";
  const std::string br = "((" + ar + ")*(" + qtx + ")+(" + ai +
                         ")*(" + qty + "))/2";
  const std::string bi = "((" + ar + ")*(" + qty + ")-(" + ai +
                         ")*(" + qtx + "))/2";
  const std::string energy = "((" + qtx + ")^2+(" + qty + ")^2)/2-1/(" +
                             qnorm + ")";
  return IMap("var:zs,x,y,vx,vy,ls,ur,ui,vr,vi,h,t,R;fun:" + ar + "," +
              ai + "," + br + "," + bi + "," + energy + ",t;");
}

IMap make_other_pair_lc_field() {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation =
      "(" + scale + "*exp(2*log(at)/3))";
  const std::string qx = "(ar^2-ai^2)";
  const std::string qy = "(2*ar*ai)";
  const std::string other_squared =
      "((" + qx + "-" + separation + ")^2+" + qy + "^2)";
  const std::string other_denominator =
      "(" + other_squared + "*sqrt(" + other_squared + "))";
  const std::string gx = "(-1/(" + separation + ")^2-(" + qx + "-" +
                         separation + ")/" + other_denominator + ")";
  const std::string gy = "(-" + qy + "/" + other_denominator + ")";
  const std::string force_real = "(ar*" + gx + "+ai*" + gy + ")";
  const std::string force_imag = "(ar*" + gy + "-ai*" + gx + ")";
  const std::string energy_derivative =
      "(-2*((ar*br-ai*bi)*" + gx + "+(ar*bi+ai*br)*" + gy + "))";
  return IMap("var:ar,ai,br,bi,ah,at;fun:-br,-bi,-ah*ar/2-"
              "(ar^2+ai^2)*" +
              force_real + "/2,-ah*ai/2-(ar^2+ai^2)*" + force_imag +
              "/2," + energy_derivative + ",- (ar^2+ai^2);");
}

IMap make_positive_pair_entry_map() {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation =
      "(" + scale + "*exp(2*log(at)/3))";
  const std::string selected_norm = "(ar^2+ai^2)";
  const std::string qx = "(ar^2-ai^2-" + separation + ")";
  const std::string qy = "(2*ar*ai)";
  const std::string qnorm = "sqrt(" + qx + "^2+" + qy + "^2)";
  const std::string ci = "(-sqrt((" + qnorm + "-" + qx + ")/2))";
  // This switch occurs close to the negative real q-axis.  Computing cr from
  // sqrt((|q|+qx)/2) loses interval significance there; qy/(2*ci) is the
  // equivalent, cancellation-free lift on the already certified qy<0 sheet.
  const std::string cr = "(" + qy + "/(2*(" + ci + ")))";
  const std::string qtx =
      "(2*(ar*br-ai*bi)/" + selected_norm + "-2*" + separation +
      "/(3*at))";
  const std::string qty =
      "(2*(ar*bi+ai*br)/" + selected_norm + ")";
  const std::string dr = "((" + cr + ")*(" + qtx + ")+(" + ci +
                         ")*(" + qty + "))/2";
  const std::string di = "((" + cr + ")*(" + qty + ")-(" + ci +
                         ")*(" + qtx + "))/2";
  const std::string energy = "((" + qtx + ")^2+(" + qty + ")^2)/2-1/(" +
                             qnorm + ")";
  return IMap("var:ar,ai,br,bi,ah,at;fun:" + cr + "," + ci + "," + dr +
              "," + di + "," + energy + ",at;");
}

IMap make_positive_pair_lc_field() {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation =
      "(" + scale + "*exp(2*log(ct)/3))";
  const std::string qx = "(cr^2-ci^2)";
  const std::string qy = "(2*cr*ci)";
  const std::string other_squared =
      "((" + qx + "+" + separation + ")^2+" + qy + "^2)";
  const std::string other_denominator =
      "(" + other_squared + "*sqrt(" + other_squared + "))";
  const std::string gx = "(1/(" + separation + ")^2-(" + qx + "+" +
                         separation + ")/" + other_denominator + ")";
  const std::string gy = "(-" + qy + "/" + other_denominator + ")";
  const std::string force_real = "(cr*" + gx + "+ci*" + gy + ")";
  const std::string force_imag = "(cr*" + gy + "-ci*" + gx + ")";
  const std::string energy_derivative =
      "(-2*((cr*dr-ci*di)*" + gx + "+(cr*di+ci*dr)*" + gy + "))";
  return IMap("var:cr,ci,dr,di,ch,ct;fun:-dr,-di,-ch*cr/2-"
              "(cr^2+ci^2)*" +
              force_real + "/2,-ch*ci/2-(cr^2+ci^2)*" + force_imag +
              "/2," + energy_derivative + ",- (cr^2+ci^2);");
}

IMap make_fourth_fifth_combined_negative_field() {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation =
      "(" + scale + "*exp(2*log(at)/3))";
  const std::string qx = "(ar^2-ai^2)";
  const std::string qy = "(2*ar*ai)";
  const std::string other_squared =
      "((" + qx + "-" + separation + ")^2+" + qy + "^2)";
  const std::string other_denominator =
      "(" + other_squared + "*sqrt(" + other_squared + "))";
  const std::string gx = "(-1/(" + separation + ")^2-(" + qx + "-" +
                         separation + ")/" + other_denominator + ")";
  const std::string gy = "(-" + qy + "/" + other_denominator + ")";
  const std::string force_real = "(ar*" + gx + "+ai*" + gy + ")";
  const std::string force_imag = "(ar*" + gy + "-ai*" + gx + ")";
  const std::string energy_derivative =
      "(-2*((ar*br-ai*bi)*" + gx + "+(ar*bi+ai*br)*" + gy + "))";
  return IMap(
      "var:ar,ai,br,bi,ah,at,cr,ci,dr,di,ch,ct;fun:-br,-bi,-ah*ar/2-"
      "(ar^2+ai^2)*" +
      force_real + "/2,-ah*ai/2-(ar^2+ai^2)*" + force_imag + "/2," +
      energy_derivative + ",- (ar^2+ai^2),0,0,0,0,0,0;");
}

IMap make_fourth_fifth_combined_entry_field() {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation =
      "(" + scale + "*exp(2*log(at)/3))";
  const std::string selected_norm = "(ar^2+ai^2)";
  const std::string qx = "(ar^2-ai^2-" + separation + ")";
  const std::string qy = "(2*ar*ai)";
  const std::string qnorm = "sqrt(" + qx + "^2+" + qy + "^2)";
  const std::string ci = "(-sqrt((" + qnorm + "-" + qx + ")/2))";
  const std::string cr = "(" + qy + "/(2*(" + ci + ")))";
  const std::string qtx =
      "(2*(ar*br-ai*bi)/" + selected_norm + "-2*" + separation +
      "/(3*at))";
  const std::string qty =
      "(2*(ar*bi+ai*br)/" + selected_norm + ")";
  const std::string dr =
      "((" + cr + ")*(" + qtx + ")+(" + ci + ")*(" + qty + "))/2";
  const std::string di =
      "((" + cr + ")*(" + qty + ")-(" + ci + ")*(" + qtx + "))/2";
  const std::string energy =
      "((" + qtx + ")^2+(" + qty + ")^2)/2-1/(" + qnorm + ")";
  return IMap(
      "var:ar,ai,br,bi,ah,at,cr,ci,dr,di,ch,ct;fun:0,0,0,0,0,0," +
      cr + "," + ci + "," + dr + "," + di + "," + energy + ",at;");
}

IMap make_fourth_fifth_combined_positive_field() {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation =
      "(" + scale + "*exp(2*log(ct)/3))";
  const std::string qx = "(cr^2-ci^2)";
  const std::string qy = "(2*cr*ci)";
  const std::string other_squared =
      "((" + qx + "+" + separation + ")^2+" + qy + "^2)";
  const std::string other_denominator =
      "(" + other_squared + "*sqrt(" + other_squared + "))";
  const std::string gx = "(1/(" + separation + ")^2-(" + qx + "+" +
                         separation + ")/" + other_denominator + ")";
  const std::string gy = "(-" + qy + "/" + other_denominator + ")";
  const std::string force_real = "(cr*" + gx + "+ci*" + gy + ")";
  const std::string force_imag = "(cr*" + gy + "-ci*" + gx + ")";
  const std::string energy_derivative =
      "(-2*((cr*dr-ci*di)*" + gx + "+(cr*di+ci*dr)*" + gy + "))";
  return IMap(
      "var:ar,ai,br,bi,ah,at,cr,ci,dr,di,ch,ct;fun:0,0,0,0,0,0,-dr,-di,-ch*cr/2-"
      "(cr^2+ci^2)*" +
      force_real + "/2,-ch*ci/2-(cr^2+ci^2)*" + force_imag + "/2," +
              energy_derivative + ",- (cr^2+ci^2);");
}

IMap make_first_other_combined_entry_field() {
  const std::string selected_norm = "(ur^2+ui^2)";
  const std::string qx = "(ur^2-ui^2+R)";
  const std::string qy = "(2*ur*ui)";
  const std::string qnorm = "sqrt(" + qx + "^2+" + qy + "^2)";
  const std::string ar = "sqrt((" + qnorm + "+" + qx + ")/2)";
  const std::string ai = "(" + qy + "/(2*(" + ar + ")))";
  const std::string qtx =
      "(2*(ur*vr-ui*vi)/" + selected_norm + "+2*R/(3*t))";
  const std::string qty =
      "(2*(ur*vi+ui*vr)/" + selected_norm + ")";
  const std::string br =
      "((" + ar + ")*(" + qtx + ")+(" + ai + ")*(" + qty + "))/2";
  const std::string bi =
      "((" + ar + ")*(" + qty + ")-(" + ai + ")*(" + qtx + "))/2";
  const std::string energy =
      "((" + qtx + ")^2+(" + qty + ")^2)/2-1/(" + qnorm + ")";
  return IMap(
      "var:zs,x,y,vx,vy,ls,ur,ui,vr,vi,h,t,R,ar,ai,br,bi,ah,at;"
      "fun:0,0,0,0,0,0,0,0,0,0,0,0,0," +
      ar + "," + ai + "," + br + "," + bi + "," + energy + ",t;");
}

IMap make_positive_bridge_combined_entry_field() {
  const std::string scale = "exp(log(9)/3)";
  const std::string lambda = "exp(log(ct)/3)";
  const std::string separation = "(" + scale + "*(" + lambda + ")^2)";
  const std::string selected_norm = "(cr^2+ci^2)";
  const std::string qx = "(cr^2-ci^2)";
  const std::string qy = "(2*cr*ci)";
  const std::string qtx =
      "(2*(cr*dr-ci*di)/" + selected_norm + ")";
  const std::string qty =
      "(2*(cr*di+ci*dr)/" + selected_norm + ")";
  return IMap(
      "var:cr,ci,dr,di,ch,ct,l,x,y,vx,vy;fun:0,0,0,0,0,0," +
      lambda + "," + qx + "+" + separation + "/2," + qy + "," + qtx +
      "+" + separation + "/(3*ct)," + qty + ";");
}

IMap make_bridge_negative_combined_entry_field() {
  const std::string scale = "exp(log(9)/3)";
  const std::string half_binary = "(" + scale + "*l^2/2)";
  const std::string qx = "(x+" + half_binary + ")";
  const std::string qnorm = "sqrt((" + qx + ")^2+y^2)";
  const std::string ar = "sqrt((" + qnorm + "+" + qx + ")/2)";
  const std::string ai = "(y/(2*(" + ar + ")))";
  const std::string qtx = "(vx+" + scale + "/(3*l))";
  const std::string br =
      "((" + ar + ")*(" + qtx + ")+(" + ai + ")*vy)/2";
  const std::string bi =
      "((" + ar + ")*vy-(" + ai + ")*(" + qtx + "))/2";
  const std::string energy =
      "((" + qtx + ")^2+vy^2)/2-1/" + qnorm;
  return IMap("var:l,x,y,vx,vy,ar,ai,br,bi,ah,at;"
              "fun:0,0,0,0,0," +
              ar + "," + ai + "," + br + "," + bi + "," + energy +
              ",l^3;");
}

IMap make_prefixed_negative_lc_field(int frozen_count) {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation = "(" + scale + "*exp(2*log(at)/3))";
  const std::string qx = "(ar^2-ai^2)";
  const std::string qy = "(2*ar*ai)";
  const std::string other_squared =
      "((" + qx + "-" + separation + ")^2+" + qy + "^2)";
  const std::string denominator =
      "(" + other_squared + "*sqrt(" + other_squared + "))";
  const std::string gx = "(-1/(" + separation + ")^2-(" + qx + "-" +
                         separation + ")/" + denominator + ")";
  const std::string gy = "(-" + qy + "/" + denominator + ")";
  const std::string force_real = "(ar*" + gx + "+ai*" + gy + ")";
  const std::string force_imag = "(ar*" + gy + "-ai*" + gx + ")";
  const std::string energy_derivative =
      "(-2*((ar*br-ai*bi)*" + gx + "+(ar*bi+ai*br)*" + gy + "))";
  return IMap("var:" + frozen_variables(frozen_count) +
              ",ar,ai,br,bi,ah,at;fun:" + frozen_zeros(frozen_count) +
              ",-br,-bi,-ah*ar/2-(ar^2+ai^2)*" + force_real +
              "/2,-ah*ai/2-(ar^2+ai^2)*" + force_imag + "/2," +
              energy_derivative + ",- (ar^2+ai^2);");
}

IMap make_prefixed_positive_lc_field(int frozen_count) {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation = "(" + scale + "*exp(2*log(ct)/3))";
  const std::string qx = "(cr^2-ci^2)";
  const std::string qy = "(2*cr*ci)";
  const std::string other_squared =
      "((" + qx + "+" + separation + ")^2+" + qy + "^2)";
  const std::string denominator =
      "(" + other_squared + "*sqrt(" + other_squared + "))";
  const std::string gx = "(1/(" + separation + ")^2-(" + qx + "+" +
                         separation + ")/" + denominator + ")";
  const std::string gy = "(-" + qy + "/" + denominator + ")";
  const std::string force_real = "(cr*" + gx + "+ci*" + gy + ")";
  const std::string force_imag = "(cr*" + gy + "-ci*" + gx + ")";
  const std::string energy_derivative =
      "(-2*((cr*dr-ci*di)*" + gx + "+(cr*di+ci*dr)*" + gy + "))";
  return IMap("var:" + frozen_variables(frozen_count) +
              ",cr,ci,dr,di,ch,ct;fun:" + frozen_zeros(frozen_count) +
              ",-dr,-di,-ch*cr/2-(cr^2+ci^2)*" + force_real +
              "/2,-ch*ci/2-(cr^2+ci^2)*" + force_imag + "/2," +
              energy_derivative + ",- (cr^2+ci^2);");
}

IMap make_prefixed_positive_entry_map(int frozen_count) {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation = "(" + scale + "*exp(2*log(at)/3))";
  const std::string selected_norm = "(ar^2+ai^2)";
  const std::string qx = "(ar^2-ai^2-" + separation + ")";
  const std::string qy = "(2*ar*ai)";
  const std::string qnorm = "sqrt(" + qx + "^2+" + qy + "^2)";
  const std::string ci = "(-sqrt((" + qnorm + "-" + qx + ")/2))";
  const std::string cr = "(" + qy + "/(2*(" + ci + ")))";
  const std::string qtx =
      "(2*(ar*br-ai*bi)/" + selected_norm + "-2*" + separation +
      "/(3*at))";
  const std::string qty =
      "(2*(ar*bi+ai*br)/" + selected_norm + ")";
  const std::string dr =
      "((" + cr + ")*(" + qtx + ")+(" + ci + ")*(" + qty + "))/2";
  const std::string di =
      "((" + cr + ")*(" + qty + ")-(" + ci + ")*(" + qtx + "))/2";
  const std::string energy =
      "((" + qtx + ")^2+(" + qty + ")^2)/2-1/(" + qnorm + ")";
  return IMap("var:" + frozen_variables(frozen_count) +
              ",ar,ai,br,bi,ah,at;fun:" + frozen_identity(frozen_count) +
              "," + cr + "," + ci + "," + dr + "," + di + "," + energy +
              ",at;");
}

IMap make_prefixed_positive_bridge_entry_field(int frozen_count) {
  const std::string scale = "exp(log(9)/3)";
  const std::string lambda = "exp(log(ct)/3)";
  const std::string separation = "(" + scale + "*(" + lambda + ")^2)";
  const std::string selected_norm = "(cr^2+ci^2)";
  const std::string qx = "(cr^2-ci^2)";
  const std::string qy = "(2*cr*ci)";
  const std::string qtx =
      "(2*(cr*dr-ci*di)/" + selected_norm + ")";
  const std::string qty =
      "(2*(cr*di+ci*dr)/" + selected_norm + ")";
  return IMap("var:" + frozen_variables(frozen_count) +
              ",cr,ci,dr,di,ch,ct,l,x,y,vx,vy;fun:" +
              frozen_zeros(frozen_count + 6) + "," + lambda + "," + qx +
              "+" + separation + "/2," + qy + "," + qtx + "+" +
              separation + "/(3*ct)," + qty + ";");
}

IMap make_prefixed_bridge_field(int frozen_count) {
  const std::string scale = "exp(log(9)/3)";
  const std::string radius = "(" + scale + "*l^2/2)";
  const std::string plus_squared = "((x+" + radius + ")^2+y^2)";
  const std::string minus_squared = "((x-" + radius + ")^2+y^2)";
  const std::string plus_denominator =
      "(" + plus_squared + "*sqrt(" + plus_squared + "))";
  const std::string minus_denominator =
      "(" + minus_squared + "*sqrt(" + minus_squared + "))";
  return IMap("var:" + frozen_variables(frozen_count) +
              ",l,x,y,vx,vy;fun:" + frozen_zeros(frozen_count) +
              ",-1,-3*l^2*vx,-3*l^2*vy,3*l^2*((x+" + radius + ")/" +
              plus_denominator + "+(x-" + radius + ")/" +
              minus_denominator + "),3*l^2*(y/" + plus_denominator +
              "+y/" + minus_denominator + ");");
}

IMap make_prefixed_bridge_negative_entry_field(int frozen_count) {
  const std::string scale = "exp(log(9)/3)";
  const std::string half_binary = "(" + scale + "*l^2/2)";
  const std::string qx = "(x+" + half_binary + ")";
  const std::string qnorm = "sqrt((" + qx + ")^2+y^2)";
  const std::string ar = "sqrt((" + qnorm + "+" + qx + ")/2)";
  const std::string ai = "(y/(2*(" + ar + ")))";
  const std::string qtx = "(vx+" + scale + "/(3*l))";
  const std::string br =
      "((" + ar + ")*(" + qtx + ")+(" + ai + ")*vy)/2";
  const std::string bi =
      "((" + ar + ")*vy-(" + ai + ")*(" + qtx + "))/2";
  const std::string energy =
      "((" + qtx + ")^2+vy^2)/2-1/" + qnorm;
  return IMap("var:" + frozen_variables(frozen_count) +
              ",l,x,y,vx,vy,ar,ai,br,bi,ah,at;fun:" +
              frozen_zeros(frozen_count + 5) + "," + ar + "," + ai + "," +
              br + "," + bi + "," + energy + ",l^3;");
}

TailData stable_tail_data(const interval& kappa,
                          double zeta_start = kZetaStart,
                          bool use_quintic = false) {
  using namespace capd;
  const interval sqrt3 = sqrt(interval(3.0));
  const interval sqrt7 = sqrt(interval(7.0));
  const interval sqrt19 = sqrt(interval(19.0));
  const interval sqrt21 = sqrt(interval(21.0));
  const interval sqrt57 = sqrt(interval(57.0));
  const interval sqrt133 = sqrt(interval(133.0));
  const interval sqrt399 = sqrt(interval(399.0));
  const interval a_t = (interval(1.0) + sqrt7) / interval(6.0);
  const interval a_l = (interval(1.0) + sqrt19) / interval(6.0);
  const interval p = -exp(-interval(zeta_start) * a_t);
  const interval nu_scale = exp(-interval(zeta_start) * a_l);
  const interval nu = kappa * nu_scale;

  const interval A =
      (-interval(5.0) * sqrt21 - sqrt399 + interval(12.0) * sqrt3 +
       interval(3.0) * sqrt57) /
      interval(6.0);
  const interval K =
      (interval(2.0) * sqrt21 - interval(5.0) * sqrt3) / interval(4.0);
  const interval D =
      (-interval(2.0) * sqrt57 + interval(29.0) * sqrt3) / interval(340.0);
  const interval B =
      -interval(67.0) / interval(108.0) +
      interval(43.0) * sqrt7 / interval(216.0);
  const interval C =
      (-interval(2819.0) * sqrt133 - interval(2314.0) * sqrt19 +
       interval(2498.0) * sqrt7) /
          interval(31620.0) +
      interval(83681.0) / interval(63240.0);
  const interval E =
      -interval(337.0) / interval(248.0) +
      (interval(6.0) * sqrt7 + interval(14.0) * sqrt19 +
       interval(11.0) * sqrt133) /
          interval(124.0);
  const interval F = interval(121.0) / interval(5100.0) -
                     interval(29.0) * sqrt19 / interval(10200.0);
  const interval G =
      (-interval(93651910.0) * sqrt399 - interval(392572319.0) * sqrt21 +
       interval(1018625929.0) * sqrt3 + interval(250916714.0) * sqrt57) /
      interval(45037296.0);
  const interval H =
      (-interval(386571066.0) * sqrt399 - interval(833244582.0) * sqrt21 +
       interval(312559697.0) * sqrt57 + interval(6447516829.0) * sqrt3) /
      interval(8038436400.0);
  const interval I =
      (-interval(3671.0) * sqrt3 + interval(187.0) * sqrt21) /
      interval(76464.0);
  const interval J =
      (-interval(1022448154.0) * sqrt21 - interval(213073373.0) * sqrt399 +
       interval(2563820254.0) * sqrt3 + interval(612798518.0) * sqrt57) /
      interval(267947880.0);
  const interval L =
      (-interval(4307297.0) * sqrt3 + interval(308435.0) * sqrt57) /
      interval(242413200.0);
  const interval M =
      (exact_integer("139388") - exact_integer("52377") * sqrt7) /
      exact_integer("22656");
  const interval N =
      (-exact_integer("774477456573583") -
       exact_integer("138316082351786") * sqrt19 +
       exact_integer("233813248132331") * sqrt7 +
       exact_integer("65671343849527") * sqrt133) /
      exact_integer("3414727782720");
  const interval O =
      (-exact_integer("12013435545841763") * sqrt133 -
       exact_integer("29654748827119993") * sqrt7 +
       exact_integer("11068114004318700") * sqrt19 +
       exact_integer("201875601915437169")) /
      exact_integer("116407941497942400");
  const interval P =
      (-exact_integer("2922965759") * sqrt133 -
       exact_integer("12051945556") * sqrt7 +
       exact_integer("31581467405") +
       exact_integer("7786167931") * sqrt19) /
      exact_integer("360298368");
  const interval Q =
      (-exact_integer("69108245795306") * sqrt7 -
       exact_integer("4224822501153") * sqrt133 +
       exact_integer("57183552400781") +
       exact_integer("40730719418703") * sqrt19) /
      exact_integer("4898087246400");
  const interval R =
      (-exact_integer("2131571208") +
       exact_integer("209218965") * sqrt19) /
      exact_integer("35984892800");

  interval x = p + A * p * nu + B * power(p, 3) + C * p * sqr(nu) +
               G * power(p, 3) * nu + H * p * power(nu, 3);
  interval q = nu + K * sqr(p) + D * sqr(nu) + E * sqr(p) * nu +
               F * power(nu, 3) + I * power(p, 4) +
               J * sqr(p) * sqr(nu) + L * power(nu, 4);
  interval vx =
      -a_t * p - (a_t + a_l) * A * p * nu -
      interval(3.0) * a_t * B * power(p, 3) -
      (a_t + interval(2.0) * a_l) * C * p * sqr(nu) -
      (interval(3.0) * a_t + a_l) * G * power(p, 3) * nu -
      (a_t + interval(3.0) * a_l) * H * p * power(nu, 3);
  interval vq =
      -a_l * nu - interval(2.0) * a_t * K * sqr(p) -
      interval(2.0) * a_l * D * sqr(nu) -
      (interval(2.0) * a_t + a_l) * E * sqr(p) * nu -
      interval(3.0) * a_l * F * power(nu, 3) -
      interval(4.0) * a_t * I * power(p, 4) -
      interval(2.0) * (a_t + a_l) * J * sqr(p) * sqr(nu) -
      interval(4.0) * a_l * L * power(nu, 4);

  interval dx_dnu =
      A * p + interval(2.0) * C * p * nu + G * power(p, 3) +
      interval(3.0) * H * p * sqr(nu);
  interval dq_dnu =
      interval(1.0) + interval(2.0) * D * nu + E * sqr(p) +
      interval(3.0) * F * sqr(nu) +
      interval(2.0) * J * sqr(p) * nu +
      interval(4.0) * L * power(nu, 3);
  interval dvx_dnu =
      -(a_t + a_l) * A * p -
      interval(2.0) * (a_t + interval(2.0) * a_l) * C * p * nu -
      (interval(3.0) * a_t + a_l) * G * power(p, 3) -
      interval(3.0) * (a_t + interval(3.0) * a_l) * H * p * sqr(nu);
  interval dvq_dnu =
      -a_l - interval(4.0) * a_l * D * nu -
      (interval(2.0) * a_t + a_l) * E * sqr(p) -
      interval(9.0) * a_l * F * sqr(nu) -
      interval(4.0) * (a_t + a_l) * J * sqr(p) * nu -
      interval(16.0) * a_l * L * power(nu, 3);

  if (use_quintic) {
    x += M * power(p, 5) + N * power(p, 3) * sqr(nu) +
         O * p * power(nu, 4);
    q += P * power(p, 4) * nu + Q * sqr(p) * power(nu, 3) +
         R * power(nu, 5);
    vx -= interval(5.0) * a_t * M * power(p, 5) +
          (interval(3.0) * a_t + interval(2.0) * a_l) * N *
              power(p, 3) * sqr(nu) +
          (a_t + interval(4.0) * a_l) * O * p * power(nu, 4);
    vq -= (interval(4.0) * a_t + a_l) * P * power(p, 4) * nu +
          (interval(2.0) * a_t + interval(3.0) * a_l) * Q * sqr(p) *
              power(nu, 3) +
          interval(5.0) * a_l * R * power(nu, 5);
    dx_dnu += interval(2.0) * N * power(p, 3) * nu +
              interval(4.0) * O * p * power(nu, 3);
    dq_dnu += P * power(p, 4) +
              interval(3.0) * Q * sqr(p) * sqr(nu) +
              interval(5.0) * R * power(nu, 4);
    dvx_dnu -= interval(2.0) *
                   (interval(3.0) * a_t + interval(2.0) * a_l) * N *
                   power(p, 3) * nu +
               interval(4.0) * (a_t + interval(4.0) * a_l) * O * p *
                   power(nu, 3);
    dvq_dnu -= (interval(4.0) * a_t + a_l) * P * power(p, 4) +
               interval(3.0) *
                   (interval(2.0) * a_t + interval(3.0) * a_l) * Q *
                   sqr(p) * sqr(nu) +
               interval(25.0) * a_l * R * power(nu, 4);
  }

  const interval p_ratio = interval(400.0) * exp(-interval(zeta_start) * a_t);
  const interval nu_ratio =
      interval(6500.0) * exp(-interval(zeta_start) * a_l);
  const double lambda_upper =
      std::max(p_ratio.rightBound(), nu_ratio.rightBound());
  const interval tail_scale =
      power(interval(lambda_upper), use_quintic ? 6 : 5);
  const interval position_error =
      symmetric(tail_scale / interval(4000000000.0));
  const interval velocity_error =
      symmetric(tail_scale / interval(800000000.0));
  const interval position_tangent_error =
      symmetric(tail_scale / interval(1000000000.0));
  const interval velocity_tangent_error =
      symmetric(tail_scale / interval(200000000.0));

  IVector state(5);
  state[0] = interval(0.0);
  state[1] = x + position_error;
  state[2] = -sqrt3 / interval(2.0) + q + position_error;
  state[3] = vx + velocity_error;
  state[4] = vq + velocity_error;

  IVector tangent(5);
  tangent[0] = interval(0.0);
  tangent[1] = dx_dnu * nu_scale + position_tangent_error;
  tangent[2] = dq_dnu * nu_scale + position_tangent_error;
  tangent[3] = dvx_dnu * nu_scale + velocity_tangent_error;
  tangent[4] = dvq_dnu * nu_scale + velocity_tangent_error;
  return {state, tangent};
}

C0Rect2Set lift_with_zero_coordinates(const C0Rect2Set& source,
                                      int extra_dimension) {
  const int source_dimension = source.get_x().dimension();
  const int target_dimension = source_dimension + extra_dimension;
  IVector x(target_dimension);
  IVector r(target_dimension);
  IVector r0(target_dimension);
  IMatrix c(target_dimension, target_dimension);
  IMatrix b(target_dimension, target_dimension);
  for (int row = 0; row < source_dimension; ++row) {
    x[row] = source.get_x()[row];
    r[row] = source.get_r()[row];
    r0[row] = source.get_r0()[row];
    for (int column = 0; column < source_dimension; ++column) {
      c[row][column] = source.get_C()[row][column];
      b[row][column] = source.get_B()[row][column];
    }
  }
  for (int row = source_dimension; row < target_dimension; ++row) {
    x[row] = interval(0.0);
    r[row] = interval(0.0);
    r0[row] = interval(0.0);
    c[row][row] = interval(1.0);
    b[row][row] = interval(1.0);
  }
  return C0Rect2Set(x, c, r0, b, r,
                    source.getCurrentTime());
}

C0Rect2Set append_coordinate_map(const C0Rect2Set& source,
                                 int target_dimension,
                                 IMap& combined_field) {
  C0Rect2Set combined =
      lift_with_zero_coordinates(source, target_dimension);
  IOdeSolver solver(combined_field, 20);
  solver.setAbsoluteTolerance(1e-15);
  solver.setRelativeTolerance(1e-15);
  ITimeMap time_map(solver);
  const interval end_time = combined.getCurrentTime() + interval(1.0);
  time_map(end_time, combined);
  return combined;
}

void apply_same_dimension_map(C0Rect2Set& set, IMap& map) {
  capd::dynsys::DynSysMap<IMap> dynamical_map(map);
  set.move(dynamical_map);
}

void propagate_relative_time(C0Rect2Set& set, IMap& field,
                             const interval& duration,
                             double initial_step = 0.0) {
  IOdeSolver solver(field, 30);
  solver.setAbsoluteTolerance(1e-15);
  solver.setRelativeTolerance(1e-15);
  if (initial_step > 0.0) {
    solver.setStep(initial_step);
  }
  ITimeMap time_map(solver);
  const interval end_time = set.getCurrentTime() + duration;
  time_map(end_time, set);
}

template <typename Set>
void propagate_to_lc_section(Set& set, const interval& duration,
                             bool pre_collision_checks,
                             bool require_selected_separation = false,
                             double zeta_start = kZetaStart) {
  IMap shape_field = make_combined_shape_field();
  IOdeSolver shape_solver(shape_field, 30);
  shape_solver.setAbsoluteTolerance(1e-15);
  shape_solver.setRelativeTolerance(1e-15);
  ITimeMap shape_time_map(shape_solver);
  const interval shape_end =
      interval(zeta_start) - interval(3.0) / interval(10.0);
  shape_time_map.stopAfterStep(true);
  const interval shape_distance_square_threshold =
      interval(1.0) / interval(1000000.0);
  do {
    shape_time_map(shape_end, set);
    const IVector enclosure = set.getLastEnclosure();
    const interval plus_squared =
        sqr(enclosure[1] + interval(1.0) / interval(2.0)) + sqr(enclosure[2]);
    const interval minus_squared =
        sqr(enclosure[1] - interval(1.0) / interval(2.0)) + sqr(enclosure[2]);
    if (!(plus_squared.leftBound() >
              shape_distance_square_threshold.rightBound() &&
          minus_squared.leftBound() >
              shape_distance_square_threshold.rightBound())) {
      throw std::runtime_error("shape path approached a primary boundary");
    }
  } while (!shape_time_map.completed());
  const IVector shape_state = static_cast<IVector>(set);
  if (!(shape_state[2].leftBound() > 0.0)) {
    throw std::runtime_error(
        "shape-to-LC entry crossed the chosen square-root lift");
  }

  IMap entry_field = make_combined_entry_field();
  const interval radial_time = exp(interval(3.0) / interval(10.0));
  const interval binary_scale = exp(log(interval(9.0)) / interval(3.0)) *
                                exp(interval(1.0) / interval(5.0));
  const interval velocity_scale =
      exp(log(interval(9.0)) / interval(3.0)) /
      exp(interval(1.0) / interval(10.0));
  entry_field.setParameter("S", binary_scale);
  entry_field.setParameter("V", velocity_scale);
  entry_field.setParameter("T", radial_time);
  IOdeSolver entry_solver(entry_field, 20);
  entry_solver.setAbsoluteTolerance(1e-15);
  entry_solver.setRelativeTolerance(1e-15);
  ITimeMap entry_time_map(entry_solver);
  const interval entry_end = shape_end + interval(1.0);
  entry_time_map(entry_end, set);
  const IVector entry_state = static_cast<IVector>(set);
  if (!(entry_state[6].leftBound() > 0.0 &&
        entry_state[7].leftBound() > 0.0)) {
    throw std::runtime_error("LC entry lift reached a branch boundary");
  }

  IMap lc_field = make_combined_lc_field();
  IOdeSolver lc_solver(lc_field, 30);
  lc_solver.setAbsoluteTolerance(1e-15);
  lc_solver.setRelativeTolerance(1e-15);
  ITimeMap lc_time_map(lc_solver);
  const interval lc_end = entry_end + duration;
  lc_time_map.stopAfterStep(true);
  do {
    lc_time_map(lc_end, set);
    const IVector enclosure = set.getLastEnclosure();
    const interval qx = sqr(enclosure[6]) - sqr(enclosure[7]);
    const interval qy = interval(2.0) * enclosure[6] * enclosure[7];
    const interval selected_distance =
        sqr(enclosure[6]) + sqr(enclosure[7]);
    const interval other_squared = sqr(qx + enclosure[12]) + sqr(qy);
    if (require_selected_separation &&
        !(selected_distance.leftBound() > 1e-8)) {
      throw std::runtime_error("selected-pair LC path reached collision");
    }
    if (pre_collision_checks) {
      if (!(enclosure[11].leftBound() > 1.0 &&
            enclosure[12].leftBound() > 2.0 &&
            other_squared.leftBound() > 1.0)) {
        throw std::runtime_error(
            "pre-collision LC path left its certified chart");
      }
    } else if (!(enclosure[11].leftBound() > 0.3 &&
                 enclosure[12].leftBound() > 1.0 &&
                 other_squared.leftBound() > 0.01)) {
      throw std::runtime_error("collision-ejection LC path lost separation");
    }
  } while (!lc_time_map.completed());
}

struct Evaluation {
  IVector residual;
  IMatrix jacobian;
  IVector final_state;
  IVector kappa_tangent;
};

Evaluation evaluate_box(const interval& kappa, const interval& duration,
                        bool pre_collision_checks = true,
                        bool require_selected_separation = false,
                        double zeta_start = kZetaStart,
                        bool use_quintic = false) {
  const TailData tail = stable_tail_data(kappa, zeta_start, use_quintic);
  IVector initial(13);
  IVector initial_tangent(13);
  for (int index = 0; index < 5; ++index) {
    initial[index] = tail.state[index];
    initial_tangent[index] = tail.kappa_tangent[index];
  }
  for (int index = 5; index < 13; ++index) {
    initial[index] = interval(0.0);
    initial_tangent[index] = interval(0.0);
  }
  C1Rect2Set set(initial);
  propagate_to_lc_section(set, duration, pre_collision_checks,
                          require_selected_separation, zeta_start);
  const IVector state = static_cast<IVector>(set);
  const IMatrix derivative = static_cast<IMatrix>(set);
  const IVector kappa_tangent = derivative * initial_tangent;

  IVector residual(2);
  residual[0] = state[6];
  residual[1] = state[7];
  IMatrix jacobian(2, 2);
  jacobian[0][0] = kappa_tangent[6];
  jacobian[1][0] = kappa_tangent[7];
  jacobian[0][1] = -state[8];
  jacobian[1][1] = -state[9];
  return {residual, jacobian, state, kappa_tangent};
}

IVector evaluate_escape_lc_state(const interval& kappa,
                                 const interval& duration) {
  const TailData tail = stable_tail_data(kappa);
  IVector initial(13);
  for (int index = 0; index < 5; ++index) {
    initial[index] = tail.state[index];
  }
  for (int index = 5; index < 13; ++index) {
    initial[index] = interval(0.0);
  }
  C0Rect2Set set(initial);
  propagate_to_lc_section(set, duration, false);
  return static_cast<IVector>(set);
}

Evaluation evaluate_other_pair_collision(const interval& kappa,
                                         const interval& duration,
                                         bool stable_entry = false,
                                         bool require_selected_separation = false,
                                         double zeta_start = kZetaStart,
                                         bool use_quintic = false) {
  const Evaluation first =
      evaluate_box(kappa, interval(7.0) / interval(4.0), true, true,
                   zeta_start, use_quintic);
  const interval switch_qy =
      interval(2.0) * first.final_state[6] * first.final_state[7];
  if (!(switch_qy.rightBound() < 0.0)) {
    throw std::runtime_error("other-pair LC switch did not prove q_y<0");
  }
  IMap entry = stable_entry ? make_other_pair_stable_entry_map()
                            : make_other_pair_entry_map();
  const IVector entry_state = entry(first.final_state);
  const IMatrix entry_derivative = entry.derivative(first.final_state);
  const IVector entry_tangent = entry_derivative * first.kappa_tangent;
  if (!(entry_state[0].leftBound() > 1.0 &&
        entry_state[1].rightBound() < 0.0 &&
        entry_state[5].leftBound() > 1.0)) {
    throw std::runtime_error("other-pair LC entry left its selected lift");
  }

  C1Rect2Set set(entry_state);
  IMap field = make_other_pair_lc_field();
  IOdeSolver solver(field, 30);
  solver.setAbsoluteTolerance(1e-15);
  solver.setRelativeTolerance(1e-15);
  ITimeMap time_map(solver);
  time_map.stopAfterStep(true);
  do {
    time_map(duration, set);
    const IVector enclosure = set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval selected_distance =
        sqr(enclosure[0]) + sqr(enclosure[1]);
    const interval other_squared = sqr(qx - separation) + sqr(qy);
    if (!(!require_selected_separation ||
          selected_distance.leftBound() > 1e-8)) {
      std::cerr << std::hexfloat
                << "OTHER_PAIR_SELECTED_PATH enclosure=" << enclosure
                << " selected_distance=" << selected_distance << "\n";
      throw std::runtime_error(
          "other-pair LC path did not exclude an earlier collision");
    }
    if (!(enclosure[2].leftBound() > 0.5 &&
          enclosure[5].leftBound() > 0.5 &&
          other_squared.leftBound() > 0.01)) {
      std::cerr << std::hexfloat << "OTHER_PAIR_PATH enclosure=" << enclosure
                << " other_squared=" << other_squared << "\n";
      throw std::runtime_error("other-pair LC path lost separation");
    }
  } while (!time_map.completed());

  const IVector state = static_cast<IVector>(set);
  const IMatrix derivative = static_cast<IMatrix>(set);
  const IVector kappa_tangent = derivative * entry_tangent;
  IVector residual(2);
  residual[0] = state[0];
  residual[1] = state[1];
  IMatrix jacobian(2, 2);
  jacobian[0][0] = kappa_tangent[0];
  jacobian[1][0] = kappa_tangent[1];
  jacobian[0][1] = -state[2];
  jacobian[1][1] = -state[3];
  return {residual, jacobian, state, kappa_tangent};
}

Evaluation evaluate_third_pair_collision(const interval& kappa,
                                          const interval& duration) {
  const interval second_duration =
      interval(10275749204.0) / interval(10000000000.0);
  const Evaluation second =
      evaluate_other_pair_collision(kappa, second_duration, true, true);

  C1Rect2Set negative_set(second.final_state);
  IMap negative_field = make_other_pair_lc_field();
  IOdeSolver negative_solver(negative_field, 30);
  negative_solver.setAbsoluteTolerance(1e-15);
  negative_solver.setRelativeTolerance(1e-15);
  ITimeMap negative_time_map(negative_solver);
  const interval negative_duration =
      interval(83687424.0) / interval(100000000.0);
  negative_time_map.stopAfterStep(true);
  do {
    negative_time_map(negative_duration, negative_set);
    const IVector enclosure = negative_set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval selected_distance =
        sqr(enclosure[0]) + sqr(enclosure[1]);
    const interval other_squared = sqr(qx - separation) + sqr(qy);
    if (!(selected_distance.leftBound() > 0.0 &&
          enclosure[5].leftBound() > 0.4 &&
          other_squared.leftBound() > 0.1)) {
      throw std::runtime_error(
          "third-root negative-primary path lost its chart");
    }
  } while (!negative_time_map.completed());
  const IVector negative_exit = static_cast<IVector>(negative_set);
  const IMatrix negative_derivative = static_cast<IMatrix>(negative_set);
  const IVector negative_tangent =
      negative_derivative * second.kappa_tangent;

  IMap positive_entry_map = make_positive_pair_entry_map();
  const IVector positive_entry = positive_entry_map(negative_exit);
  const IMatrix positive_entry_derivative =
      positive_entry_map.derivative(negative_exit);
  const IVector positive_entry_tangent =
      positive_entry_derivative * negative_tangent;
  if (!(positive_entry[1].rightBound() < 0.0 &&
        positive_entry[5].leftBound() > 0.4)) {
    throw std::runtime_error(
        "third-root positive-primary entry lost its selected lift");
  }

  C1Rect2Set positive_set(positive_entry);
  IMap positive_field = make_positive_pair_lc_field();
  IOdeSolver positive_solver(positive_field, 30);
  positive_solver.setAbsoluteTolerance(1e-15);
  positive_solver.setRelativeTolerance(1e-15);
  ITimeMap positive_time_map(positive_solver);
  positive_time_map.stopAfterStep(true);
  do {
    positive_time_map(duration, positive_set);
    const IVector enclosure = positive_set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval other_squared = sqr(qx + separation) + sqr(qy);
    if (!(enclosure[3].rightBound() < -0.5 &&
          enclosure[5].leftBound() > 0.2 &&
          other_squared.leftBound() > 0.1)) {
      std::cerr << std::hexfloat
                << "THIRD_ROOT_POSITIVE_PATH enclosure=" << enclosure
                << " other_squared=" << other_squared << "\n";
      throw std::runtime_error(
          "third-root positive-primary path lost monotonicity or separation");
    }
  } while (!positive_time_map.completed());

  const IVector state = static_cast<IVector>(positive_set);
  const IMatrix derivative = static_cast<IMatrix>(positive_set);
  const IVector kappa_tangent = derivative * positive_entry_tangent;
  IVector residual(2);
  residual[0] = state[0];
  residual[1] = state[1];
  IMatrix jacobian(2, 2);
  jacobian[0][0] = kappa_tangent[0];
  jacobian[1][0] = kappa_tangent[1];
  jacobian[0][1] = -state[2];
  jacobian[1][1] = -state[3];
  return {residual, jacobian, state, kappa_tangent};
}

Evaluation evaluate_fourth_pair_collision(const interval& kappa,
                                           const interval& duration,
                                           double zeta_start = kZetaStart,
                                           bool use_quintic = false) {
  const interval second_duration =
      interval(10275749204.0) / interval(10000000000.0);
  const Evaluation second =
      evaluate_other_pair_collision(kappa, second_duration, true, true,
                                    zeta_start, use_quintic);

  C1Rect2Set negative_set(second.final_state);
  IMap negative_field = make_other_pair_lc_field();
  IOdeSolver negative_solver(negative_field, 30);
  negative_solver.setAbsoluteTolerance(1e-15);
  negative_solver.setRelativeTolerance(1e-15);
  ITimeMap negative_time_map(negative_solver);
  const interval negative_duration =
      interval(83687424.0) / interval(100000000.0);
  negative_time_map.stopAfterStep(true);
  do {
    negative_time_map(negative_duration, negative_set);
    const IVector enclosure = negative_set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval selected_distance =
        sqr(enclosure[0]) + sqr(enclosure[1]);
    const interval other_squared = sqr(qx - separation) + sqr(qy);
    if (!(selected_distance.leftBound() > 0.0 &&
          enclosure[5].leftBound() > 0.4 &&
          other_squared.leftBound() > 0.1)) {
      std::cerr << std::hexfloat
                << "FOURTH_ROOT_NEGATIVE_PATH enclosure=" << enclosure
                << " selected_distance=" << selected_distance
                << " other_squared=" << other_squared << "\n";
      throw std::runtime_error(
          "fourth-root negative-primary path lost its chart");
    }
  } while (!negative_time_map.completed());
  const IVector negative_exit = static_cast<IVector>(negative_set);
  const IMatrix negative_derivative = static_cast<IMatrix>(negative_set);
  const IVector negative_tangent =
      negative_derivative * second.kappa_tangent;

  IMap positive_entry_map = make_positive_pair_entry_map();
  const IVector positive_entry = positive_entry_map(negative_exit);
  const IMatrix positive_entry_derivative =
      positive_entry_map.derivative(negative_exit);
  const IVector positive_entry_tangent =
      positive_entry_derivative * negative_tangent;
  if (!(positive_entry[1].rightBound() < 0.0 &&
        positive_entry[5].leftBound() > 0.4)) {
    throw std::runtime_error(
        "fourth-root positive-primary entry lost its selected lift");
  }

  C1Rect2Set positive_set(positive_entry);
  IMap positive_field = make_positive_pair_lc_field();
  IOdeSolver positive_solver(positive_field, 30);
  positive_solver.setAbsoluteTolerance(1e-15);
  positive_solver.setRelativeTolerance(1e-15);
  ITimeMap positive_time_map(positive_solver);
  const interval positive_duration =
      interval(123106953.0) / interval(100000000.0);
  const interval third_collision_window_end =
      interval(3.0) / interval(5.0);
  positive_time_map.stopAfterStep(true);
  do {
    positive_time_map(third_collision_window_end, positive_set);
    const IVector enclosure = positive_set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval other_squared = sqr(qx + separation) + sqr(qy);
    if (!(enclosure[3].rightBound() < -0.5 &&
          enclosure[5].leftBound() > 0.2 &&
          other_squared.leftBound() > 0.1)) {
      std::cerr << std::hexfloat
                << "FOURTH_ROOT_POSITIVE_MONOTONE_PATH regularized_time="
                << positive_time_map.getCurrentTime()
                << " enclosure=" << enclosure
                << " other_squared=" << other_squared << "\n";
      throw std::runtime_error(
          "fourth-root positive-primary path lost monotonicity or separation");
    }
  } while (!positive_time_map.completed());
  const IVector post_collision_window = static_cast<IVector>(positive_set);
  if (!(post_collision_window[1].leftBound() > 0.0)) {
    throw std::runtime_error(
        "fourth-root positive-primary path did not exit the collision window");
  }
  do {
    positive_time_map(positive_duration, positive_set);
    const IVector enclosure = positive_set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval other_squared = sqr(qx + separation) + sqr(qy);
    if (!(enclosure[1].leftBound() > 0.0 &&
          enclosure[5].leftBound() > 0.2 &&
          other_squared.leftBound() > 0.1)) {
      throw std::runtime_error(
          "fourth-root positive-primary exit path lost sign or separation");
    }
  } while (!positive_time_map.completed());
  const IVector positive_exit = static_cast<IVector>(positive_set);
  const IMatrix positive_derivative = static_cast<IMatrix>(positive_set);
  const IVector positive_tangent =
      positive_derivative * positive_entry_tangent;

  IMap bridge_entry_map = make_positive_exit_to_bridge_map();
  const IVector bridge_entry = bridge_entry_map(positive_exit);
  const IMatrix bridge_entry_derivative =
      bridge_entry_map.derivative(positive_exit);
  const IVector bridge_entry_tangent =
      bridge_entry_derivative * positive_tangent;
  C1Rect2Set bridge_set(bridge_entry);
  IMap bridge_field = make_heavy_binary_bridge_field();
  IOdeSolver bridge_solver(bridge_field, 30);
  bridge_solver.setAbsoluteTolerance(1e-15);
  bridge_solver.setRelativeTolerance(1e-15);
  ITimeMap bridge_time_map(bridge_solver);
  const interval bridge_duration = interval(97.0) / interval(5000.0);
  bridge_time_map.stopAfterStep(true);
  do {
    bridge_time_map(bridge_duration, bridge_set);
    const IVector enclosure = bridge_set.getLastEnclosure();
    const interval half_binary =
        exp(log(interval(9.0)) / interval(3.0)) * sqr(enclosure[0]) /
        interval(2.0);
    const interval selected_squared =
        sqr(enclosure[1] + half_binary) + sqr(enclosure[2]);
    const interval other_squared =
        sqr(enclosure[1] - half_binary) + sqr(enclosure[2]);
    if (!(enclosure[0].leftBound() > 0.6 &&
          selected_squared.leftBound() > 1e-5 &&
          other_squared.leftBound() > 0.1)) {
      throw std::runtime_error(
          "fourth-root bridge entry path lost ordinary separation");
    }
  } while (!bridge_time_map.completed());
  const IVector bridge_exit = static_cast<IVector>(bridge_set);
  const IMatrix bridge_derivative = static_cast<IMatrix>(bridge_set);
  const IVector bridge_tangent =
      bridge_derivative * bridge_entry_tangent;

  IMap fourth_entry_map = make_bridge_to_negative_entry_map();
  const interval half_binary =
      exp(log(interval(9.0)) / interval(3.0)) * sqr(bridge_exit[0]) /
      interval(2.0);
  const interval fourth_qx = bridge_exit[1] + half_binary;
  if (!(fourth_qx.leftBound() > 0.05)) {
    throw std::runtime_error(
        "fourth-root square-root entry lost its positive-real chart");
  }
  const IVector fourth_entry = fourth_entry_map(bridge_exit);
  const IMatrix fourth_entry_derivative =
      fourth_entry_map.derivative(bridge_exit);
  const IVector fourth_entry_tangent =
      fourth_entry_derivative * bridge_tangent;

  C1Rect2Set fourth_set(fourth_entry);
  IMap fourth_field = make_other_pair_lc_field();
  IOdeSolver fourth_solver(fourth_field, 30);
  fourth_solver.setAbsoluteTolerance(1e-15);
  fourth_solver.setRelativeTolerance(1e-15);
  ITimeMap fourth_time_map(fourth_solver);
  fourth_time_map.stopAfterStep(true);
  do {
    fourth_time_map(duration, fourth_set);
    const IVector enclosure = fourth_set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval other_squared = sqr(qx - separation) + sqr(qy);
    if (!(enclosure[2].leftBound() > 0.5 &&
          enclosure[5].leftBound() > 0.05 &&
          other_squared.leftBound() > 0.1)) {
      throw std::runtime_error(
          "fourth-root LC path lost clock or other-primary separation");
    }
  } while (!fourth_time_map.completed());

  const IVector state = static_cast<IVector>(fourth_set);
  const IMatrix derivative = static_cast<IMatrix>(fourth_set);
  const IVector kappa_tangent = derivative * fourth_entry_tangent;
  IVector residual(2);
  residual[0] = state[0];
  residual[1] = state[1];
  IMatrix jacobian(2, 2);
  jacobian[0][0] = kappa_tangent[0];
  jacobian[1][0] = kappa_tangent[1];
  jacobian[0][1] = -state[2];
  jacobian[1][1] = -state[3];
  return {residual, jacobian, state, kappa_tangent};
}

struct EscapeEvaluation {
  IVector lc_exit;
  IVector bridge_exit;
  interval minimum_primary_squared;
  interval escape_margin;
  interval finite_mass_margin;
};

struct SecondEscapeEvaluation {
  IVector negative_lc_exit;
  IVector positive_lc_entry;
  IVector positive_lc_exit;
  IVector bridge_exit;
  interval minimum_negative_chart_other_squared;
  interval minimum_positive_chart_other_squared;
  interval minimum_bridge_primary_squared;
  interval escape_margin;
  interval finite_mass_margin;
};

EscapeEvaluation evaluate_collision_ejection_escape(const interval& kappa) {
  const interval lc_duration = interval(61.0) / interval(25.0);
  const IVector state = evaluate_escape_lc_state(kappa, lc_duration);
  const interval ur = state[6];
  const interval ui = state[7];
  const interval vr = state[8];
  const interval vi = state[9];
  const interval radial_time = state[11];
  const interval binary_separation = state[12];
  const interval u_squared = sqr(ur) + sqr(ui);
  const interval qx = sqr(ur) - sqr(ui);
  const interval qy = interval(2.0) * ur * ui;
  const interval qtx =
      interval(2.0) * (ur * vr - ui * vi) / u_squared;
  const interval qty =
      interval(2.0) * (ur * vi + ui * vr) / u_squared;
  const interval lambda = exp(log(radial_time) / interval(3.0));

  IVector initial(5);
  initial[0] = lambda;
  initial[1] = qx + binary_separation / interval(2.0);
  initial[2] = qy;
  initial[3] = qtx + binary_separation / (interval(3.0) * radial_time);
  initial[4] = qty;
  C0Rect2Set set(initial);

  IMap bridge_field = make_heavy_binary_bridge_field();
  IOdeSolver bridge_solver(bridge_field, 30);
  bridge_solver.setAbsoluteTolerance(1e-15);
  bridge_solver.setRelativeTolerance(1e-15);
  ITimeMap bridge_time_map(bridge_solver);
  const double lambda_center =
      (lambda.leftBound() + lambda.rightBound()) / 2.0;
  const interval bridge_end = interval(lambda_center + 2.0);
  bridge_time_map.stopAfterStep(true);
  interval minimum_primary_squared = interval(1000000.0);
  do {
    bridge_time_map(bridge_end, set);
    const IVector enclosure = set.getLastEnclosure();
    const interval half_binary =
        exp(log(interval(9.0)) / interval(3.0)) * sqr(enclosure[0]) /
        interval(2.0);
    const interval plus_squared =
        sqr(enclosure[1] + half_binary) + sqr(enclosure[2]);
    const interval minus_squared =
        sqr(enclosure[1] - half_binary) + sqr(enclosure[2]);
    const interval step_minimum =
        interval(std::min(plus_squared.leftBound(), minus_squared.leftBound()),
                 std::min(plus_squared.rightBound(), minus_squared.rightBound()));
    minimum_primary_squared =
        interval(std::min(minimum_primary_squared.leftBound(),
                          step_minimum.leftBound()),
                 std::min(minimum_primary_squared.rightBound(),
                          step_minimum.rightBound()));
    if (!(plus_squared.leftBound() > 0.25 &&
          minus_squared.leftBound() > 0.25)) {
      throw std::runtime_error("heavy-binary bridge approached a primary");
    }
  } while (!bridge_time_map.completed());

  const IVector bridge_exit = static_cast<IVector>(set);
  if (!(bridge_exit[0].rightBound() < -1.9 &&
        bridge_exit[0].leftBound() > -2.1)) {
    throw std::runtime_error("heavy-binary bridge missed the target lambda section");
  }
  const interval outer_radius =
      sqrt(sqr(bridge_exit[1]) + sqr(bridge_exit[2]));
  const interval radial_clock_speed =
      (bridge_exit[1] * bridge_exit[3] + bridge_exit[2] * bridge_exit[4]) /
      outer_radius;
  const interval physical_outward_speed = -radial_clock_speed;
  const interval scale = exp(log(interval(9.0)) / interval(3.0));
  const interval half_binary = scale * sqr(bridge_exit[0]) / interval(2.0);
  const interval clearance = outer_radius - half_binary;
  const interval binary_boundary_speed =
      scale / (interval(3.0) * (-bridge_exit[0]));
  const interval comparison_speed = interval(2.0);
  const interval escape_margin =
      physical_outward_speed -
      interval(2.0) / (comparison_speed * clearance) -
      comparison_speed - binary_boundary_speed;
  // At the massless endpoint the two primaries have total mass M=2 and
  // parabolic relative energy e=0.  This is the strict limiting inequality
  // used by the finite-mass hierarchical escape lemma: allow e<1/100,
  // bound the binary's linear envelope by v_b, and require the outer radius
  // to outrun that envelope by c=3/2 even after all future radial-force loss.
  const interval inner_separation = scale * sqr(bridge_exit[0]);
  const interval outer_clearance = outer_radius - inner_separation;
  const interval energy_ceiling = interval(1.0) / interval(100.0);
  const interval cone_speed = interval(3.0) / interval(2.0);
  const interval binary_envelope_speed =
      sqrt(interval(4.0) / inner_separation +
           interval(2.0) * energy_ceiling);
  const interval finite_mass_margin =
      physical_outward_speed -
      interval(2.0) / (cone_speed * outer_clearance) -
      binary_envelope_speed - cone_speed;
  if (!(clearance.leftBound() > 10.0 &&
        physical_outward_speed.leftBound() > 2.5 &&
        escape_margin.leftBound() > 0.0 &&
        outer_clearance.leftBound() > 10.0 &&
        finite_mass_margin.leftBound() > 0.0)) {
    throw std::runtime_error("post-binary state failed the analytic escape test");
  }
  return {state, bridge_exit, minimum_primary_squared, escape_margin,
          finite_mass_margin};
}

SecondEscapeEvaluation evaluate_second_collision_ejection_escape(
    const interval& kappa, const interval& collision_duration,
    bool stable_entry = false, bool bridge_negative_lc = false,
    const interval& bridge_lc_duration = interval(0.0)) {
  const Evaluation collision =
      evaluate_other_pair_collision(kappa, collision_duration, stable_entry);

  C0Rect2Set negative_set(collision.final_state);
  IMap negative_field = make_other_pair_lc_field();
  IOdeSolver negative_solver(negative_field, 30);
  negative_solver.setAbsoluteTolerance(1e-15);
  negative_solver.setRelativeTolerance(1e-15);
  ITimeMap negative_time_map(negative_solver);
  const interval negative_duration =
      interval(83687424.0) / interval(100000000.0);
  negative_time_map.stopAfterStep(true);
  interval minimum_negative_other_squared = interval(1000000.0);
  do {
    negative_time_map(negative_duration, negative_set);
    const IVector enclosure = negative_set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval other_squared = sqr(qx - separation) + sqr(qy);
    minimum_negative_other_squared =
        interval(std::min(minimum_negative_other_squared.leftBound(),
                          other_squared.leftBound()),
                 std::min(minimum_negative_other_squared.rightBound(),
                          other_squared.rightBound()));
    if (!(enclosure[5].leftBound() > 0.4 &&
          other_squared.leftBound() > 0.01)) {
      std::cerr << std::hexfloat
                << "SECOND_ESCAPE_NEGATIVE_PATH enclosure=" << enclosure
                << " other_squared=" << other_squared << "\n";
      throw std::runtime_error(
          "second-root negative-primary outgoing path lost separation");
    }
  } while (!negative_time_map.completed());
  const IVector negative_exit = static_cast<IVector>(negative_set);

  const interval negative_norm =
      sqr(negative_exit[0]) + sqr(negative_exit[1]);
  const interval separation =
      exp(log(interval(9.0)) / interval(3.0)) *
      exp(interval(2.0) * log(negative_exit[5]) / interval(3.0));
  const interval positive_qx =
      sqr(negative_exit[0]) - sqr(negative_exit[1]) - separation;
  const interval positive_qy =
      interval(2.0) * negative_exit[0] * negative_exit[1];
  const interval positive_norm_squared =
      sqr(positive_qx) + sqr(positive_qy);
  if (!(negative_norm.leftBound() > 0.01 &&
        positive_norm_squared.leftBound() > 0.01 &&
        positive_qx.rightBound() < 0.0)) {
    throw std::runtime_error(
        "positive-primary LC switch did not certify its square-root sheet");
  }
  IMap positive_entry_map = make_positive_pair_entry_map();
  const IVector positive_entry = positive_entry_map(negative_exit);
  if (!(positive_entry[1].rightBound() < 0.0 &&
        positive_entry[5].leftBound() > 0.4)) {
    std::cerr << std::hexfloat
              << "SECOND_ESCAPE_POSITIVE_ENTRY state=" << positive_entry
              << "\n";
    throw std::runtime_error("positive-primary LC entry left its selected lift");
  }

  C0Rect2Set positive_set(positive_entry);
  IMap positive_field = make_positive_pair_lc_field();
  IOdeSolver positive_solver(positive_field, 30);
  positive_solver.setAbsoluteTolerance(1e-15);
  positive_solver.setRelativeTolerance(1e-15);
  ITimeMap positive_time_map(positive_solver);
  const interval positive_duration =
      interval(123106953.0) / interval(100000000.0);
  positive_time_map.stopAfterStep(true);
  interval minimum_positive_other_squared = interval(1000000.0);
  do {
    positive_time_map(positive_duration, positive_set);
    const IVector enclosure = positive_set.getLastEnclosure();
    const interval current_separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval other_squared =
        sqr(qx + current_separation) + sqr(qy);
    minimum_positive_other_squared =
        interval(std::min(minimum_positive_other_squared.leftBound(),
                          other_squared.leftBound()),
                 std::min(minimum_positive_other_squared.rightBound(),
                          other_squared.rightBound()));
    if (!(enclosure[5].leftBound() > 0.2 &&
          other_squared.leftBound() > 0.01)) {
      std::cerr << std::hexfloat
                << "SECOND_ESCAPE_POSITIVE_PATH enclosure=" << enclosure
                << " other_squared=" << other_squared << "\n";
      throw std::runtime_error(
          "second-root positive-primary LC path lost separation");
    }
  } while (!positive_time_map.completed());
  const IVector positive_exit = static_cast<IVector>(positive_set);

  const interval cr = positive_exit[0];
  const interval ci = positive_exit[1];
  const interval dr = positive_exit[2];
  const interval di = positive_exit[3];
  const interval radial_time = positive_exit[5];
  const interval u_squared = sqr(cr) + sqr(ci);
  const interval qx = sqr(cr) - sqr(ci);
  const interval qy = interval(2.0) * cr * ci;
  const interval qtx =
      interval(2.0) * (cr * dr - ci * di) / u_squared;
  const interval qty =
      interval(2.0) * (cr * di + ci * dr) / u_squared;
  const interval lambda = exp(log(radial_time) / interval(3.0));
  const interval binary_separation =
      exp(log(interval(9.0)) / interval(3.0)) * sqr(lambda);

  IVector bridge_initial(5);
  bridge_initial[0] = lambda;
  bridge_initial[1] = qx + binary_separation / interval(2.0);
  bridge_initial[2] = qy;
  bridge_initial[3] =
      qtx + binary_separation / (interval(3.0) * radial_time);
  bridge_initial[4] = qty;
  IVector bridge_restart = bridge_initial;
  if (bridge_negative_lc) {
    C0Rect2Set bridge_pre_set(bridge_initial);
    IMap bridge_pre_field = make_heavy_binary_bridge_field();
    IOdeSolver bridge_pre_solver(bridge_pre_field, 30);
    bridge_pre_solver.setAbsoluteTolerance(1e-15);
    bridge_pre_solver.setRelativeTolerance(1e-15);
    ITimeMap bridge_pre_time_map(bridge_pre_solver);
    const interval bridge_switch_lambda =
        interval(13.0) / interval(20.0);
    const double bridge_pre_lambda_center =
        (lambda.leftBound() + lambda.rightBound()) / 2.0;
    const interval bridge_pre_end =
        interval(bridge_pre_lambda_center) - bridge_switch_lambda;
    if (!(bridge_pre_end.leftBound() > 0.0)) {
      throw std::runtime_error("fourth-chart bridge switch is not forward");
    }
    bridge_pre_time_map.stopAfterStep(true);
    do {
      bridge_pre_time_map(bridge_pre_end, bridge_pre_set);
      const IVector enclosure = bridge_pre_set.getLastEnclosure();
      const interval half_binary =
          exp(log(interval(9.0)) / interval(3.0)) * sqr(enclosure[0]) /
          interval(2.0);
      const interval selected_squared =
          sqr(enclosure[1] + half_binary) + sqr(enclosure[2]);
      const interval other_squared =
          sqr(enclosure[1] - half_binary) + sqr(enclosure[2]);
      if (!(selected_squared.leftBound() > 1e-5 &&
            other_squared.leftBound() > 0.1 &&
            enclosure[0].leftBound() > 0.6)) {
        std::cerr << std::hexfloat
                  << "SECOND_FOURTH_BRIDGE_ENTRY_PATH enclosure="
                  << enclosure << " selected_squared=" << selected_squared
                  << " other_squared=" << other_squared << "\n";
        throw std::runtime_error(
            "fourth-chart bridge entry lost ordinary separation");
      }
    } while (!bridge_pre_time_map.completed());

    const IVector bridge_pre_exit = static_cast<IVector>(bridge_pre_set);
    const interval pre_lambda = bridge_pre_exit[0];
    const interval pre_half_binary =
        exp(log(interval(9.0)) / interval(3.0)) * sqr(pre_lambda) /
        interval(2.0);
    const interval q_minus_x = bridge_pre_exit[1] + pre_half_binary;
    const interval q_minus_y = bridge_pre_exit[2];
    const interval q_minus_norm =
        sqrt(sqr(q_minus_x) + sqr(q_minus_y));
    if (!(q_minus_x.leftBound() > 0.0)) {
      std::cerr << std::hexfloat
                << "SECOND_FOURTH_ENTRY_SHEET bridge_pre_exit="
                << bridge_pre_exit << " q_minus_x=" << q_minus_x
                << " q_minus_y=" << q_minus_y << "\n";
      throw std::runtime_error("fourth-chart square-root sheet is unresolved");
    }
    const interval fourth_ar =
        sqrt((q_minus_norm + q_minus_x) / interval(2.0));
    const interval fourth_ai = q_minus_y / (interval(2.0) * fourth_ar);
    const interval scale = exp(log(interval(9.0)) / interval(3.0));
    const interval fourth_qtx =
        bridge_pre_exit[3] + scale / (interval(3.0) * pre_lambda);
    const interval fourth_qty = bridge_pre_exit[4];
    const interval fourth_br =
        (fourth_ar * fourth_qtx + fourth_ai * fourth_qty) /
        interval(2.0);
    const interval fourth_bi =
        (fourth_ar * fourth_qty - fourth_ai * fourth_qtx) /
        interval(2.0);
    const interval fourth_energy =
        (sqr(fourth_qtx) + sqr(fourth_qty)) / interval(2.0) -
        interval(1.0) / q_minus_norm;

    IVector fourth_entry(6);
    fourth_entry[0] = fourth_ar;
    fourth_entry[1] = fourth_ai;
    fourth_entry[2] = fourth_br;
    fourth_entry[3] = fourth_bi;
    fourth_entry[4] = fourth_energy;
    fourth_entry[5] = power(pre_lambda, 3);
    std::cout << std::hexfloat
              << "SECOND_FOURTH_ENTRY bridge_state=" << bridge_pre_exit
              << " lc_state=" << fourth_entry << "\n";

    C0Rect2Set fourth_set(fourth_entry);
    IMap fourth_field = make_other_pair_lc_field();
    IOdeSolver fourth_solver(fourth_field, 30);
    fourth_solver.setAbsoluteTolerance(1e-15);
    fourth_solver.setRelativeTolerance(1e-15);
    ITimeMap fourth_time_map(fourth_solver);
    fourth_time_map.stopAfterStep(true);
    interval fourth_other_minimum = interval(1000000.0);
    do {
      fourth_time_map(bridge_lc_duration, fourth_set);
      const IVector enclosure = fourth_set.getLastEnclosure();
      const interval selected_qx = sqr(enclosure[0]) - sqr(enclosure[1]);
      const interval selected_qy =
          interval(2.0) * enclosure[0] * enclosure[1];
      const interval separation =
          exp(log(interval(9.0)) / interval(3.0)) *
          exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
      const interval other_squared =
          sqr(selected_qx - separation) + sqr(selected_qy);
      fourth_other_minimum =
          interval(std::min(fourth_other_minimum.leftBound(),
                            other_squared.leftBound()),
                   std::min(fourth_other_minimum.rightBound(),
                            other_squared.rightBound()));
      if (!(enclosure[5].leftBound() > 0.05 &&
            other_squared.leftBound() > 0.1)) {
        std::cerr << std::hexfloat
                  << "SECOND_FOURTH_LC_PATH enclosure=" << enclosure
                  << " other_squared=" << other_squared << "\n";
        throw std::runtime_error(
            "fourth-chart LC path lost clock or other-primary separation");
      }
    } while (!fourth_time_map.completed());

    const IVector fourth_exit = static_cast<IVector>(fourth_set);
    const interval exit_selected_norm =
        sqr(fourth_exit[0]) + sqr(fourth_exit[1]);
    if (!(exit_selected_norm.leftBound() > 1e-5)) {
      std::cerr << std::hexfloat
                << "SECOND_FOURTH_EXIT_SELECTED lc_state=" << fourth_exit
                << " selected_norm=" << exit_selected_norm << "\n";
      throw std::runtime_error(
          "fourth-chart LC exit has not cleared the selected primary");
    }
    const interval exit_lambda =
        exp(log(fourth_exit[5]) / interval(3.0));
    const interval exit_separation = scale * sqr(exit_lambda);
    const interval exit_qx = sqr(fourth_exit[0]) - sqr(fourth_exit[1]);
    const interval exit_qy =
        interval(2.0) * fourth_exit[0] * fourth_exit[1];
    const interval exit_qtx =
        interval(2.0) *
        (fourth_exit[0] * fourth_exit[2] -
         fourth_exit[1] * fourth_exit[3]) /
        exit_selected_norm;
    const interval exit_qty =
        interval(2.0) *
        (fourth_exit[0] * fourth_exit[3] +
         fourth_exit[1] * fourth_exit[2]) /
        exit_selected_norm;
    bridge_restart[0] = exit_lambda;
    bridge_restart[1] = exit_qx - exit_separation / interval(2.0);
    bridge_restart[2] = exit_qy;
    bridge_restart[3] =
        exit_qtx - scale / (interval(3.0) * exit_lambda);
    bridge_restart[4] = exit_qty;
    std::cout << std::hexfloat
              << "SECOND_FOURTH_EXIT lc_state=" << fourth_exit
              << " bridge_state=" << bridge_restart
              << " other_minimum_squared=" << fourth_other_minimum << "\n";
  }

  C0Rect2Set bridge_set(bridge_restart);

  IMap bridge_field = make_heavy_binary_bridge_field();
  IOdeSolver bridge_solver(bridge_field, 30);
  bridge_solver.setAbsoluteTolerance(1e-15);
  bridge_solver.setRelativeTolerance(1e-15);
  ITimeMap bridge_time_map(bridge_solver);
  const double lambda_center =
      (bridge_restart[0].leftBound() + bridge_restart[0].rightBound()) / 2.0;
  const interval bridge_end = interval(lambda_center + 2.0);
  bridge_time_map.stopAfterStep(true);
  interval minimum_bridge_primary_squared = interval(1000000.0);
  do {
    bridge_time_map(bridge_end, bridge_set);
    const IVector enclosure = bridge_set.getLastEnclosure();
    const interval half_binary =
        exp(log(interval(9.0)) / interval(3.0)) * sqr(enclosure[0]) /
        interval(2.0);
    const interval plus_squared =
        sqr(enclosure[1] + half_binary) + sqr(enclosure[2]);
    const interval minus_squared =
        sqr(enclosure[1] - half_binary) + sqr(enclosure[2]);
    const interval step_minimum(
        std::min(plus_squared.leftBound(), minus_squared.leftBound()),
        std::min(plus_squared.rightBound(), minus_squared.rightBound()));
    minimum_bridge_primary_squared =
        interval(std::min(minimum_bridge_primary_squared.leftBound(),
                          step_minimum.leftBound()),
                 std::min(minimum_bridge_primary_squared.rightBound(),
                          step_minimum.rightBound()));
    if (!(plus_squared.leftBound() > 0.001 &&
          minus_squared.leftBound() > 0.001)) {
      std::cerr << std::hexfloat
                << "SECOND_ESCAPE_BRIDGE_PATH enclosure=" << enclosure
                << " plus_squared=" << plus_squared
                << " minus_squared=" << minus_squared << "\n";
      throw std::runtime_error(
          "second-root heavy-binary bridge approached a primary");
    }
  } while (!bridge_time_map.completed());

  const IVector bridge_exit = static_cast<IVector>(bridge_set);
  if (!(bridge_exit[0].rightBound() < -1.9 &&
        bridge_exit[0].leftBound() > -2.1)) {
    throw std::runtime_error(
        "second-root heavy-binary bridge missed the target lambda section");
  }
  const interval outer_radius =
      sqrt(sqr(bridge_exit[1]) + sqr(bridge_exit[2]));
  const interval radial_clock_speed =
      (bridge_exit[1] * bridge_exit[3] +
       bridge_exit[2] * bridge_exit[4]) /
      outer_radius;
  const interval physical_outward_speed = -radial_clock_speed;
  const interval scale = exp(log(interval(9.0)) / interval(3.0));
  const interval half_binary =
      scale * sqr(bridge_exit[0]) / interval(2.0);
  const interval clearance = outer_radius - half_binary;
  const interval binary_boundary_speed =
      scale / (interval(3.0) * (-bridge_exit[0]));
  const interval comparison_speed = interval(2.0);
  const interval escape_margin =
      physical_outward_speed -
      interval(2.0) / (comparison_speed * clearance) - comparison_speed -
      binary_boundary_speed;
  const interval inner_separation = scale * sqr(bridge_exit[0]);
  const interval outer_clearance = outer_radius - inner_separation;
  const interval energy_ceiling = interval(1.0) / interval(100.0);
  const interval cone_speed = interval(3.0) / interval(2.0);
  const interval binary_envelope_speed =
      sqrt(interval(4.0) / inner_separation +
           interval(2.0) * energy_ceiling);
  const interval finite_mass_margin =
      physical_outward_speed -
      interval(2.0) / (cone_speed * outer_clearance) -
      binary_envelope_speed - cone_speed;
  if (!(clearance.leftBound() > 10.0 &&
        physical_outward_speed.leftBound() > 2.5 &&
        escape_margin.leftBound() > 0.0 &&
        outer_clearance.leftBound() > 10.0 &&
        finite_mass_margin.leftBound() > 0.0)) {
    std::cerr << std::hexfloat
              << "SECOND_ESCAPE_TERMINAL bridge_exit=" << bridge_exit
              << " escape_margin=" << escape_margin
              << " finite_mass_margin=" << finite_mass_margin << "\n";
    throw std::runtime_error(
        "second-root post-binary state failed the analytic escape test");
  }
  return {negative_exit,
          positive_entry,
          positive_exit,
          bridge_exit,
          minimum_negative_other_squared,
          minimum_positive_other_squared,
          minimum_bridge_primary_squared,
          escape_margin,
          finite_mass_margin};
}

struct FourthOutgoingEvaluation {
  IVector fourth_exit;
  IVector fifth_entry;
  IVector fifth_exit;
  IVector bridge_exit;
  interval minimum_fourth_other_squared;
  interval fourth_exit_selected_norm;
  interval fifth_switch_qx;
  interval fifth_switch_squared;
  interval minimum_fifth_other_squared;
  interval minimum_bridge_primary_squared;
  interval escape_margin;
  interval finite_mass_margin;
};

struct CorrelatedFifthEvaluation {
  IVector fifth_entry;
  IVector fifth_exit;
  interval minimum_fourth_other_squared;
  interval minimum_fifth_other_squared;
  interval fifth_exit_selected_norm;
  interval fifth_exit_other_squared;
  interval fifth_section_derivative;
  interval fifth_return_time;
};

CorrelatedFifthEvaluation evaluate_fully_correlated_fifth_section_probe(
    const interval& kappa, const interval& fifth_section_value) {
  const TailData tail = stable_tail_data(kappa, kZetaStart, true);
  IVector initial(13);
  for (int index = 0; index < 5; ++index) {
    initial[index] = tail.state[index];
  }
  for (int index = 5; index < 13; ++index) {
    initial[index] = interval(0.0);
  }
  C0Rect2Set first_set(initial);
  propagate_to_lc_section(first_set, interval(7.0) / interval(4.0), true,
                          true);

  IMap first_entry_field = make_first_other_combined_entry_field();
  C0Rect2Set active =
      append_coordinate_map(first_set, 6, first_entry_field);
  IMap negative_field = make_prefixed_negative_lc_field(13);
  propagate_relative_time(
      active, negative_field,
      interval(10275749204.0) / interval(10000000000.0));
  propagate_relative_time(
      active, negative_field,
      interval(83687424.0) / interval(100000000.0));

  IMap positive_entry_map = make_prefixed_positive_entry_map(13);
  apply_same_dimension_map(active, positive_entry_map);
  IMap positive_field = make_prefixed_positive_lc_field(13);
  propagate_relative_time(
      active, positive_field,
      interval(123106953.0) / interval(100000000.0));

  IMap bridge_entry_field = make_prefixed_positive_bridge_entry_field(13);
  active = append_coordinate_map(active, 5, bridge_entry_field);
  IMap bridge_field = make_prefixed_bridge_field(19);
  propagate_relative_time(active, bridge_field,
                          interval(97.0) / interval(5000.0));

  IMap fourth_entry_field = make_prefixed_bridge_negative_entry_field(19);
  active = append_coordinate_map(active, 6, fourth_entry_field);
  negative_field = make_prefixed_negative_lc_field(24);
  propagate_relative_time(active, negative_field,
                          interval(4.0) / interval(5.0));

  positive_entry_map = make_prefixed_positive_entry_map(24);
  apply_same_dimension_map(active, positive_entry_map);
  const IVector fifth_entry_full = static_cast<IVector>(active);
  IVector fifth_entry(6);
  for (int index = 0; index < 6; ++index) {
    fifth_entry[index] = fifth_entry_full[index + 24];
  }
  positive_field = make_prefixed_positive_lc_field(24);
  IOdeSolver fifth_solver(positive_field, 30);
  fifth_solver.setAbsoluteTolerance(1e-15);
  fifth_solver.setRelativeTolerance(1e-15);
  ICoordinateSection fifth_section(30, 25, fifth_section_value);
  IPoincareMap fifth_poincare(fifth_solver, fifth_section,
                              capd::poincare::MinusPlus);
  fifth_poincare.setMaxReturnTime(2.0);
  interval fifth_return_time;
  const IVector fifth_exit_full = fifth_poincare(active, fifth_return_time);
  IVector fifth_exit(6);
  for (int index = 0; index < 6; ++index) {
    fifth_exit[index] = fifth_exit_full[index + 24];
  }
  const interval fifth_exit_selected_norm =
      sqr(fifth_exit[0]) + sqr(fifth_exit[1]);
  const interval scale = exp(log(interval(9.0)) / interval(3.0));
  const interval fifth_separation =
      scale * exp(interval(2.0) * log(fifth_exit[5]) / interval(3.0));
  const interval fifth_qx = sqr(fifth_exit[0]) - sqr(fifth_exit[1]);
  const interval fifth_qy = interval(2.0) * fifth_exit[0] * fifth_exit[1];
  const interval fifth_exit_other_squared =
      sqr(fifth_qx + fifth_separation) + sqr(fifth_qy);

  return {fifth_entry,
          fifth_exit,
          interval(0.0),
          interval(0.0),
          fifth_exit_selected_norm,
          fifth_exit_other_squared,
          -fifth_exit[3],
          fifth_return_time};
}

CorrelatedFifthEvaluation evaluate_correlated_fifth_probe(
    const interval& kappa, const interval& fourth_start_duration,
    const interval& fourth_extra_duration,
    const interval& fifth_target, bool use_poincare_section = false,
    double zeta_start = kZetaStart) {
  const Evaluation start =
      evaluate_fourth_pair_collision(kappa, fourth_start_duration,
                                     zeta_start, use_poincare_section);
  IVector combined_initial(12);
  for (int index = 0; index < 6; ++index) {
    combined_initial[index] = start.final_state[index];
    combined_initial[index + 6] = interval(0.0);
  }
  C0Rect2Set combined_set(combined_initial);

  IMap negative_field = make_fourth_fifth_combined_negative_field();
  IOdeSolver negative_solver(negative_field, 30);
  negative_solver.setAbsoluteTolerance(1e-15);
  negative_solver.setRelativeTolerance(1e-15);
  ITimeMap negative_time_map(negative_solver);
  negative_time_map.stopAfterStep(true);
  interval minimum_fourth_other_squared = interval(1000000.0);
  do {
    negative_time_map(fourth_extra_duration, combined_set);
    const IVector enclosure = combined_set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval other_squared = sqr(qx - separation) + sqr(qy);
    minimum_fourth_other_squared =
        interval(std::min(minimum_fourth_other_squared.leftBound(),
                          other_squared.leftBound()),
                 std::min(minimum_fourth_other_squared.rightBound(),
                          other_squared.rightBound()));
    if (!(enclosure[5].leftBound() > 0.05 &&
          other_squared.leftBound() > 0.01)) {
      throw std::runtime_error(
          "correlated fifth probe lost the negative-chart domain");
    }
  } while (!negative_time_map.completed());

  IMap entry_field = make_fourth_fifth_combined_entry_field();
  IOdeSolver entry_solver(entry_field, 20);
  entry_solver.setAbsoluteTolerance(1e-15);
  entry_solver.setRelativeTolerance(1e-15);
  ITimeMap entry_time_map(entry_solver);
  const interval entry_end = fourth_extra_duration + interval(1.0);
  entry_time_map(entry_end, combined_set);
  const IVector combined_entry = static_cast<IVector>(combined_set);
  IVector fifth_entry(6);
  for (int index = 0; index < 6; ++index) {
    fifth_entry[index] = combined_entry[index + 6];
  }
  if (!(fifth_entry[1].rightBound() < 0.0 &&
        fifth_entry[5].leftBound() > 0.05)) {
    throw std::runtime_error(
        "correlated fifth construction lost its selected lift");
  }

  IMap fifth_field = make_fourth_fifth_combined_positive_field();
  IOdeSolver fifth_solver(fifth_field, 30);
  fifth_solver.setAbsoluteTolerance(1e-15);
  fifth_solver.setRelativeTolerance(1e-15);
  interval minimum_fifth_other_squared = interval(1000000.0);
  interval fifth_return_time(0.0);
  IVector combined_exit(12);
  if (use_poincare_section) {
    ICoordinateSection fifth_section(12, 7, fifth_target);
    IPoincareMap fifth_poincare(fifth_solver, fifth_section,
                                capd::poincare::MinusPlus);
    fifth_poincare.setMaxReturnTime(2.0);
    combined_exit = fifth_poincare(combined_set, fifth_return_time);
  } else {
    ITimeMap fifth_time_map(fifth_solver);
    fifth_time_map.stopAfterStep(true);
    const interval fifth_end = entry_end + fifth_target;
    do {
      fifth_time_map(fifth_end, combined_set);
      const IVector enclosure = combined_set.getLastEnclosure();
      const interval separation =
          exp(log(interval(9.0)) / interval(3.0)) *
          exp(interval(2.0) * log(enclosure[11]) / interval(3.0));
      const interval qx = sqr(enclosure[6]) - sqr(enclosure[7]);
      const interval qy = interval(2.0) * enclosure[6] * enclosure[7];
      const interval other_squared = sqr(qx + separation) + sqr(qy);
      minimum_fifth_other_squared =
          interval(std::min(minimum_fifth_other_squared.leftBound(),
                            other_squared.leftBound()),
                   std::min(minimum_fifth_other_squared.rightBound(),
                            other_squared.rightBound()));
      if (!(enclosure[11].leftBound() > 0.01 &&
            other_squared.leftBound() > 0.01)) {
        std::cerr << std::hexfloat
                  << "CORRELATED_FIFTH_PATH enclosure=" << enclosure
                  << " other_squared=" << other_squared << "\n";
        throw std::runtime_error(
            "correlated fifth probe lost its ordinary denominator");
      }
    } while (!fifth_time_map.completed());
    combined_exit = static_cast<IVector>(combined_set);
  }
  IVector fifth_exit(6);
  for (int index = 0; index < 6; ++index) {
    fifth_exit[index] = combined_exit[index + 6];
  }
  const interval fifth_exit_selected_norm =
      sqr(fifth_exit[0]) + sqr(fifth_exit[1]);
  const interval scale = exp(log(interval(9.0)) / interval(3.0));
  const interval fifth_separation =
      scale * exp(interval(2.0) * log(fifth_exit[5]) / interval(3.0));
  const interval fifth_qx = sqr(fifth_exit[0]) - sqr(fifth_exit[1]);
  const interval fifth_qy = interval(2.0) * fifth_exit[0] * fifth_exit[1];
  const interval fifth_exit_other_squared =
      sqr(fifth_qx + fifth_separation) + sqr(fifth_qy);
  const interval fifth_section_derivative = -fifth_exit[3];
  return {fifth_entry,
          fifth_exit,
          minimum_fourth_other_squared,
          minimum_fifth_other_squared,
          fifth_exit_selected_norm,
          fifth_exit_other_squared,
          fifth_section_derivative,
          fifth_return_time};
}

FourthOutgoingEvaluation evaluate_fourth_outgoing(
    const interval& kappa, const interval& fourth_start_duration,
    const interval& fourth_extra_duration,
    const interval& fifth_duration, bool stop_after_fifth_entry = false) {
  const Evaluation start =
      evaluate_fourth_pair_collision(kappa, fourth_start_duration);

  C0Rect2Set fourth_set(start.final_state);
  IMap fourth_field = make_other_pair_lc_field();
  IOdeSolver fourth_solver(fourth_field, 30);
  fourth_solver.setAbsoluteTolerance(1e-15);
  fourth_solver.setRelativeTolerance(1e-15);
  ITimeMap fourth_time_map(fourth_solver);
  fourth_time_map.stopAfterStep(true);
  interval minimum_fourth_other_squared = interval(1000000.0);
  do {
    fourth_time_map(fourth_extra_duration, fourth_set);
    const IVector enclosure = fourth_set.getLastEnclosure();
    const interval separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval other_squared = sqr(qx - separation) + sqr(qy);
    minimum_fourth_other_squared =
        interval(std::min(minimum_fourth_other_squared.leftBound(),
                          other_squared.leftBound()),
                 std::min(minimum_fourth_other_squared.rightBound(),
                          other_squared.rightBound()));
    if (!(enclosure[5].leftBound() > 0.05 &&
          other_squared.leftBound() > 0.01)) {
      std::cerr << std::hexfloat
                << "FOURTH_OUTGOING_NEGATIVE_PATH enclosure=" << enclosure
                << " other_squared=" << other_squared << "\n";
      throw std::runtime_error(
          "fourth outgoing negative chart lost its ordinary denominator");
    }
  } while (!fourth_time_map.completed());
  const IVector fourth_exit = static_cast<IVector>(fourth_set);
  const interval fourth_selected_norm =
      sqr(fourth_exit[0]) + sqr(fourth_exit[1]);
  const interval separation =
      exp(log(interval(9.0)) / interval(3.0)) *
      exp(interval(2.0) * log(fourth_exit[5]) / interval(3.0));
  const interval fourth_qx =
      sqr(fourth_exit[0]) - sqr(fourth_exit[1]);
  const interval fourth_qy =
      interval(2.0) * fourth_exit[0] * fourth_exit[1];
  const interval positive_qx = fourth_qx - separation;
  const interval positive_squared =
      sqr(positive_qx) + sqr(fourth_qy);
  if (!(fourth_selected_norm.leftBound() > 1e-5 &&
        positive_qx.rightBound() < -0.05 &&
        positive_squared.leftBound() > 0.01)) {
    std::cerr << std::hexfloat
              << "FOURTH_OUTGOING_FIFTH_SWITCH fourth_exit=" << fourth_exit
              << " selected_norm=" << fourth_selected_norm
              << " positive_qx=" << positive_qx
              << " positive_squared=" << positive_squared << "\n";
    throw std::runtime_error(
        "fourth outgoing fifth-chart switch lost its square-root sheet");
  }

  IMap fifth_entry_map = make_positive_pair_entry_map();
  const IVector fifth_entry = fifth_entry_map(fourth_exit);
  if (!(fifth_entry[1].rightBound() < 0.0 &&
        fifth_entry[5].leftBound() > 0.05)) {
    throw std::runtime_error(
        "fourth outgoing fifth-chart entry lost its selected lift");
  }
  if (stop_after_fifth_entry) {
    const IVector empty_state(static_cast<IVector::size_type>(0));
    return {fourth_exit,
            fifth_entry,
            empty_state,
            empty_state,
            minimum_fourth_other_squared,
            fourth_selected_norm,
            positive_qx,
            positive_squared,
            interval(0.0),
            interval(0.0),
            interval(0.0),
            interval(0.0)};
  }
  C0Rect2Set fifth_set(fifth_entry);
  IMap fifth_field = make_positive_pair_lc_field();
  IOdeSolver fifth_solver(fifth_field, 30);
  fifth_solver.setAbsoluteTolerance(1e-15);
  fifth_solver.setRelativeTolerance(1e-15);
  ITimeMap fifth_time_map(fifth_solver);
  fifth_time_map.stopAfterStep(true);
  interval minimum_fifth_other_squared = interval(1000000.0);
  do {
    fifth_time_map(fifth_duration, fifth_set);
    const IVector enclosure = fifth_set.getLastEnclosure();
    const interval current_separation =
        exp(log(interval(9.0)) / interval(3.0)) *
        exp(interval(2.0) * log(enclosure[5]) / interval(3.0));
    const interval qx = sqr(enclosure[0]) - sqr(enclosure[1]);
    const interval qy = interval(2.0) * enclosure[0] * enclosure[1];
    const interval other_squared =
        sqr(qx + current_separation) + sqr(qy);
    minimum_fifth_other_squared =
        interval(std::min(minimum_fifth_other_squared.leftBound(),
                          other_squared.leftBound()),
                 std::min(minimum_fifth_other_squared.rightBound(),
                          other_squared.rightBound()));
    if (!(enclosure[5].leftBound() > 0.01 &&
          other_squared.leftBound() > 0.01)) {
      std::cerr << std::hexfloat
                << "FOURTH_OUTGOING_POSITIVE_PATH enclosure=" << enclosure
                << " other_squared=" << other_squared << "\n";
      throw std::runtime_error(
          "fourth outgoing fifth chart lost its ordinary denominator");
    }
  } while (!fifth_time_map.completed());
  const IVector fifth_exit = static_cast<IVector>(fifth_set);
  const interval fifth_selected_norm =
      sqr(fifth_exit[0]) + sqr(fifth_exit[1]);
  if (!(fifth_selected_norm.leftBound() > 1e-5)) {
    std::cerr << std::hexfloat
              << "FOURTH_OUTGOING_FIFTH_EXIT fifth_exit=" << fifth_exit
              << " selected_norm=" << fifth_selected_norm << "\n";
    throw std::runtime_error(
        "fourth outgoing fifth chart has not cleared the selected primary");
  }

  IMap fifth_exit_map = make_positive_exit_to_bridge_map();
  const IVector bridge_initial = fifth_exit_map(fifth_exit);
  C0Rect2Set bridge_set(bridge_initial);
  IMap bridge_field = make_heavy_binary_bridge_field();
  IOdeSolver bridge_solver(bridge_field, 30);
  bridge_solver.setAbsoluteTolerance(1e-15);
  bridge_solver.setRelativeTolerance(1e-15);
  ITimeMap bridge_time_map(bridge_solver);
  const double lambda_center =
      (bridge_initial[0].leftBound() + bridge_initial[0].rightBound()) / 2.0;
  const interval bridge_end = interval(lambda_center + 2.0);
  bridge_time_map.stopAfterStep(true);
  interval minimum_bridge_primary_squared = interval(1000000.0);
  do {
    bridge_time_map(bridge_end, bridge_set);
    const IVector enclosure = bridge_set.getLastEnclosure();
    const interval half_binary =
        exp(log(interval(9.0)) / interval(3.0)) * sqr(enclosure[0]) /
        interval(2.0);
    const interval plus_squared =
        sqr(enclosure[1] + half_binary) + sqr(enclosure[2]);
    const interval minus_squared =
        sqr(enclosure[1] - half_binary) + sqr(enclosure[2]);
    const interval step_minimum(
        std::min(plus_squared.leftBound(), minus_squared.leftBound()),
        std::min(plus_squared.rightBound(), minus_squared.rightBound()));
    minimum_bridge_primary_squared =
        interval(std::min(minimum_bridge_primary_squared.leftBound(),
                          step_minimum.leftBound()),
                 std::min(minimum_bridge_primary_squared.rightBound(),
                          step_minimum.rightBound()));
    if (!(plus_squared.leftBound() > 0.001 &&
          minus_squared.leftBound() > 0.001)) {
      std::cerr << std::hexfloat
                << "FOURTH_OUTGOING_BRIDGE_PATH enclosure=" << enclosure
                << " plus_squared=" << plus_squared
                << " minus_squared=" << minus_squared << "\n";
      throw std::runtime_error(
          "fourth outgoing bridge approached a light primary");
    }
  } while (!bridge_time_map.completed());

  const IVector bridge_exit = static_cast<IVector>(bridge_set);
  if (!(bridge_exit[0].rightBound() < -1.9 &&
        bridge_exit[0].leftBound() > -2.1)) {
    throw std::runtime_error(
        "fourth outgoing bridge missed the terminal lambda section");
  }
  const interval outer_radius =
      sqrt(sqr(bridge_exit[1]) + sqr(bridge_exit[2]));
  const interval radial_clock_speed =
      (bridge_exit[1] * bridge_exit[3] +
       bridge_exit[2] * bridge_exit[4]) /
      outer_radius;
  const interval physical_outward_speed = -radial_clock_speed;
  const interval scale = exp(log(interval(9.0)) / interval(3.0));
  const interval half_binary =
      scale * sqr(bridge_exit[0]) / interval(2.0);
  const interval clearance = outer_radius - half_binary;
  const interval binary_boundary_speed =
      scale / (interval(3.0) * (-bridge_exit[0]));
  const interval comparison_speed = interval(2.0);
  const interval escape_margin =
      physical_outward_speed -
      interval(2.0) / (comparison_speed * clearance) - comparison_speed -
      binary_boundary_speed;
  const interval inner_separation = scale * sqr(bridge_exit[0]);
  const interval outer_clearance = outer_radius - inner_separation;
  const interval energy_ceiling = interval(1.0) / interval(100.0);
  const interval cone_speed = interval(3.0) / interval(2.0);
  const interval binary_envelope_speed =
      sqrt(interval(4.0) / inner_separation +
           interval(2.0) * energy_ceiling);
  const interval finite_mass_margin =
      physical_outward_speed -
      interval(2.0) / (cone_speed * outer_clearance) -
      binary_envelope_speed - cone_speed;
  if (!(clearance.leftBound() > 10.0 &&
        physical_outward_speed.leftBound() > 2.5 &&
        escape_margin.leftBound() > 0.0 &&
        outer_clearance.leftBound() > 10.0 &&
        finite_mass_margin.leftBound() > 0.0)) {
    std::cerr << std::hexfloat
              << "FOURTH_OUTGOING_TERMINAL bridge_exit=" << bridge_exit
              << " escape_margin=" << escape_margin
              << " finite_mass_margin=" << finite_mass_margin << "\n";
    throw std::runtime_error(
        "fourth outgoing terminal state failed the escape test");
  }
  return {fourth_exit,
          fifth_entry,
          fifth_exit,
          bridge_exit,
          minimum_fourth_other_squared,
          fourth_selected_norm,
          positive_qx,
          positive_squared,
          minimum_fifth_other_squared,
          minimum_bridge_primary_squared,
          escape_margin,
          finite_mass_margin};
}

IVector interval_newton(const IVector& center, const IVector& value,
                        const IMatrix& jacobian) {
  return center - capd::matrixAlgorithms::gauss(jacobian, value);
}

int parse_integer(const char* text) {
  std::size_t consumed = 0;
  const std::string value(text);
  const int result = std::stoi(value, &consumed);
  if (consumed != value.size()) {
    throw std::invalid_argument("nonintegral tile argument");
  }
  return result;
}

}  // namespace

int main(int argc, char** argv) {
  using namespace capd;
  try {
    int first_escape_offset = -9;
    int escape_tile_count = 10;
    int escape_tile_radius = 1;
    bool second_root_only = false;
    bool second_escape_only = false;
    bool second_escape_wide = false;
    bool second_escape_probe = false;
    bool second_fourth_probe = false;
    bool second_fourth_root_probe = false;
    bool third_root_probe = false;
    bool third_root_only = false;
    bool fourth_root_only = false;
    bool fourth_fifth_entry_only = false;
    bool fourth_fifth_outgoing_only = false;
    bool fourth_outgoing_probe = false;
    bool fourth_correlated_probe = false;
    bool fourth_correlated_section_probe = false;
    bool fourth_correlated_section_tile = false;
    int second_probe_offset = 0;
    int second_probe_radius = 0;
    int second_fourth_duration_million = 0;
    int second_fourth_duration_radius_million = 0;
    int second_fifth_duration_million = 0;
    int correlated_offset_pico = 0;
    int correlated_radius_pico = 395;
    if (argc == 2 && std::string(argv[1]) == "--second-root") {
      second_root_only = true;
    } else if (argc == 2 && std::string(argv[1]) == "--second-escape") {
      second_escape_only = true;
    } else if (argc == 2 &&
               std::string(argv[1]) == "--second-escape-wide") {
      second_escape_wide = true;
    } else if (argc == 2 && std::string(argv[1]) == "--fourth-root") {
      fourth_root_only = true;
    } else if (argc == 2 && std::string(argv[1]) == "--third-root") {
      third_root_only = true;
    } else if (argc == 2 &&
               std::string(argv[1]) == "--fourth-fifth-entry") {
      fourth_fifth_entry_only = true;
    } else if (argc == 2 &&
               std::string(argv[1]) == "--fourth-fifth-outgoing") {
      fourth_fifth_outgoing_only = true;
      fourth_correlated_section_probe = true;
      second_fifth_duration_million = 50000;
    } else if (argc == 3 &&
               std::string(argv[1]) == "--fourth-correlated-probe") {
      fourth_correlated_probe = true;
      second_fifth_duration_million = parse_integer(argv[2]);
    } else if (argc == 3 &&
               std::string(argv[1]) == "--fourth-correlated-section-probe") {
      fourth_correlated_section_probe = true;
      second_fifth_duration_million = parse_integer(argv[2]);
    } else if (argc == 5 &&
               std::string(argv[1]) == "--fourth-correlated-section-tile") {
      fourth_correlated_section_probe = true;
      fourth_correlated_section_tile = true;
      correlated_offset_pico = parse_integer(argv[2]);
      correlated_radius_pico = parse_integer(argv[3]);
      second_fifth_duration_million = parse_integer(argv[4]);
    } else if (argc == 4 &&
               std::string(argv[1]) == "--second-escape-probe") {
      second_escape_probe = true;
      second_probe_offset = parse_integer(argv[2]);
      second_probe_radius = parse_integer(argv[3]);
    } else if (argc == 4 &&
               std::string(argv[1]) == "--fourth-outgoing-probe") {
      fourth_outgoing_probe = true;
      second_fourth_duration_million = parse_integer(argv[2]);
      second_fifth_duration_million = parse_integer(argv[3]);
    } else if (argc == 5 &&
               std::string(argv[1]) == "--second-fourth-probe") {
      second_fourth_probe = true;
      second_probe_offset = parse_integer(argv[2]);
      second_probe_radius = parse_integer(argv[3]);
      second_fourth_duration_million = parse_integer(argv[4]);
    } else if (argc == 6 &&
               std::string(argv[1]) == "--second-fourth-root-probe") {
      second_fourth_root_probe = true;
      second_probe_offset = parse_integer(argv[2]);
      second_probe_radius = parse_integer(argv[3]);
      second_fourth_duration_million = parse_integer(argv[4]);
      second_fourth_duration_radius_million = parse_integer(argv[5]);
    } else if (argc == 6 &&
               std::string(argv[1]) == "--third-root-probe") {
      third_root_probe = true;
      second_probe_offset = parse_integer(argv[2]);
      second_probe_radius = parse_integer(argv[3]);
      second_fourth_duration_million = parse_integer(argv[4]);
      second_fourth_duration_radius_million = parse_integer(argv[5]);
    } else if ((argc == 4 || argc == 5) &&
        std::string(argv[1]) == "--escape-tiles") {
      first_escape_offset = parse_integer(argv[2]);
      escape_tile_count = parse_integer(argv[3]);
      if (argc == 5) {
        escape_tile_radius = parse_integer(argv[4]);
      }
    } else if (argc != 1) {
      std::cerr << "usage: " << argv[0]
                << " [--second-root | --third-root | --fourth-root | "
                   "--fourth-fifth-entry | "
                   "--fourth-fifth-outgoing | "
                   "--fourth-correlated-probe FIFTH_DURATION_MILLION | "
                   "--fourth-correlated-section-probe CI_MILLION | "
                   "--fourth-correlated-section-tile OFFSET_PICO "
                   "RADIUS_PICO CI_MILLION | "
                   "--second-escape | "
                   "--second-escape-wide | --second-escape-probe "
                   "OFFSET_NANO RADIUS_NANO | --escape-tiles FIRST_OFFSET "
                   "COUNT [RADIUS] | --fourth-outgoing-probe "
                   "FOURTH_EXTRA_MILLION FIFTH_DURATION_MILLION | "
                   "--second-fourth-probe OFFSET_NANO "
                   "RADIUS_NANO DURATION_MILLION | "
                   "--second-fourth-root-probe OFFSET_NANO RADIUS_NANO "
                   "DURATION_MILLION DURATION_RADIUS_MILLION | "
                   "--third-root-probe OFFSET_NANO RADIUS_NANO "
                   "DURATION_MILLION DURATION_RADIUS_MILLION]\n";
      return 2;
    }
    if (escape_tile_count < 1 || escape_tile_count > 1000 ||
        escape_tile_radius < 1 || escape_tile_radius > 1000) {
      throw std::invalid_argument(
          "tile count and radius must lie in [1,1000]");
    }
    if (second_escape_probe &&
        (second_probe_radius < 1 || second_probe_radius > 1000000)) {
      throw std::invalid_argument("second probe radius must lie in [1,1000000]");
    }
    if (second_fourth_probe &&
        (second_probe_radius < 1 || second_probe_radius > 1000000 ||
         second_fourth_duration_million < 1 ||
         second_fourth_duration_million > 10000000)) {
      throw std::invalid_argument(
          "fourth probe radius/duration is outside its safe range");
    }
    if (fourth_outgoing_probe &&
        (second_fourth_duration_million < 1 ||
         second_fourth_duration_million > 10000000 ||
         second_fifth_duration_million < 1 ||
         second_fifth_duration_million > 10000000)) {
      throw std::invalid_argument(
          "fourth outgoing probe durations are outside their safe ranges");
    }
    if (fourth_correlated_probe &&
        (second_fifth_duration_million < 1 ||
         second_fifth_duration_million > 10000000)) {
      throw std::invalid_argument(
          "correlated fifth probe duration is outside its safe range");
    }
    if (fourth_correlated_section_probe &&
        (second_fifth_duration_million < 1 ||
         second_fifth_duration_million > 500000)) {
      throw std::invalid_argument(
          "correlated fifth section is outside its safe range");
    }
    if (fourth_correlated_section_tile &&
        (correlated_offset_pico < -1000 || correlated_offset_pico > 1000 ||
         correlated_radius_pico < 1 || correlated_radius_pico > 395)) {
      throw std::invalid_argument(
          "correlated fifth section tile is outside its safe range");
    }
    if (second_fourth_root_probe &&
        (second_probe_radius < 1 || second_probe_radius > 1000000 ||
         second_fourth_duration_million < 1 ||
         second_fourth_duration_million > 10000000 ||
         second_fourth_duration_radius_million < 1 ||
         second_fourth_duration_radius_million > 1000000)) {
      throw std::invalid_argument(
          "fourth-root probe box is outside its safe range");
    }
    if (third_root_probe &&
        (second_probe_radius < 1 || second_probe_radius > 1000000 ||
         second_fourth_duration_million < 1 ||
         second_fourth_duration_million > 10000000 ||
         second_fourth_duration_radius_million < 1 ||
         second_fourth_duration_radius_million > 1000000)) {
      throw std::invalid_argument(
          "third-root probe box is outside its safe range");
    }
    if (second_root_only) {
      const interval second_kappa_center =
          interval(12640119251.0) / interval(10000000000.0);
      const interval second_duration_center =
          interval(10275749204.0) / interval(10000000000.0);
      const interval second_kappa_radius =
          interval(7.0) / interval(1000000000.0);
      const interval second_duration_radius =
          interval(5.0) / interval(100000000.0);
      const interval second_kappa_box =
          second_kappa_center + symmetric(second_kappa_radius);
      const interval second_duration_box =
          second_duration_center + symmetric(second_duration_radius);
      const Evaluation second_center = evaluate_other_pair_collision(
          second_kappa_center, second_duration_center);
      const Evaluation second_box = evaluate_other_pair_collision(
          second_kappa_box, second_duration_box);
      IVector second_x_center(2);
      second_x_center[0] = second_kappa_center;
      second_x_center[1] = second_duration_center;
      IVector second_x_box(2);
      second_x_box[0] = second_kappa_box;
      second_x_box[1] = second_duration_box;
      const IVector second_newton = interval_newton(
          second_x_center, second_center.residual, second_box.jacobian);
      const interval second_determinant =
          second_box.jacobian[0][0] * second_box.jacobian[1][1] -
          second_box.jacobian[0][1] * second_box.jacobian[1][0];
      std::cout << std::hexfloat
                << "SECOND_ROOT_DATA method=CAPD-6.1.0-native"
                << " box=" << second_x_box
                << " center_residual=" << second_center.residual
                << " jacobian=" << second_box.jacobian
                << " determinant=" << second_determinant
                << " newton=" << second_newton
                << " final_state_box=" << second_box.final_state
                << " inclusion="
                << subsetInterior(second_newton, second_x_box) << "\n";
      if (!subsetInterior(second_newton, second_x_box)) {
        return 1;
      }
      if (second_determinant.contains(0.0)) {
        throw std::runtime_error(
            "second Newton inclusion passed but determinant contains zero");
      }
      std::cout << "PASS_SECOND_ROOT method=CAPD-6.1.0-native "
                   "stage=planar-second-light-collision-interval-newton\n";
      return 0;
    }
    if (fourth_root_only) {
      const interval kappa_center =
          interval(1264009098895.0 +
                   static_cast<double>(correlated_offset_pico)) /
          interval(1000000000000.0);
      const interval kappa_radius =
          interval(static_cast<double>(correlated_radius_pico)) /
          interval(1000000000000.0);
      const interval fourth_duration_center =
          interval(37184.0) / interval(100000.0);
      const interval fourth_duration_radius =
          interval(1.0) / interval(1000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const interval fourth_duration_box =
          fourth_duration_center + symmetric(fourth_duration_radius);
      const Evaluation center = evaluate_fourth_pair_collision(
          kappa_center, fourth_duration_center);
      const Evaluation box = evaluate_fourth_pair_collision(
          kappa_box, fourth_duration_box);
      IVector x_center(2);
      x_center[0] = kappa_center;
      x_center[1] = fourth_duration_center;
      IVector x_box(2);
      x_box[0] = kappa_box;
      x_box[1] = fourth_duration_box;
      const IVector newton =
          interval_newton(x_center, center.residual, box.jacobian);
      const interval determinant =
          box.jacobian[0][0] * box.jacobian[1][1] -
          box.jacobian[0][1] * box.jacobian[1][0];
      const interval third_kappa_center =
          interval(12640090991.0) / interval(10000000000.0);
      const interval third_kappa_radius =
          interval(1.0) / interval(1000000000.0);
      const interval third_duration_center =
          interval(588416.0) / interval(1000000.0);
      const interval third_duration_radius =
          interval(1.0) / interval(10000.0);
      const interval third_kappa_box =
          third_kappa_center + symmetric(third_kappa_radius);
      const interval third_duration_box =
          third_duration_center + symmetric(third_duration_radius);
      const Evaluation third_center = evaluate_third_pair_collision(
          third_kappa_center, third_duration_center);
      const Evaluation third_box = evaluate_third_pair_collision(
          third_kappa_box, third_duration_box);
      IVector third_x_center(2);
      third_x_center[0] = third_kappa_center;
      third_x_center[1] = third_duration_center;
      IVector third_x_box(2);
      third_x_box[0] = third_kappa_box;
      third_x_box[1] = third_duration_box;
      const IVector third_newton = interval_newton(
          third_x_center, third_center.residual, third_box.jacobian);
      const Evaluation third_lower = evaluate_third_pair_collision(
          third_kappa_box,
          third_duration_center - third_duration_radius);
      const Evaluation third_upper = evaluate_third_pair_collision(
          third_kappa_box,
          third_duration_center + third_duration_radius);
      const interval root_parameter_gap = third_newton[0] - newton[0];
      const bool fourth_box_in_third_parameter_box =
          kappa_box.leftBound() >= third_kappa_box.leftBound() &&
          kappa_box.rightBound() <= third_kappa_box.rightBound();
      const bool third_window_brackets_every_imaginary_zero =
          third_lower.residual[1].rightBound() < 0.0 &&
          third_upper.residual[1].leftBound() > 0.0;
      std::cout << std::hexfloat
                << "FOURTH_ROOT_DATA method=CAPD-6.1.0-native"
                << " box=" << x_box
                << " center_residual=" << center.residual
                << " jacobian=" << box.jacobian
                << " determinant=" << determinant
                << " newton=" << newton
                << " final_state_box=" << box.final_state
                << " inclusion=" << subsetInterior(newton, x_box) << "\n";
      std::cout << std::hexfloat
                << "FOURTH_ROOT_EARLIER_COLLISION_EXCLUSION"
                << " third_box=" << third_x_box
                << " third_newton=" << third_newton
                << " third_lower_imaginary=" << third_lower.residual[1]
                << " third_upper_imaginary=" << third_upper.residual[1]
                << " fourth_parameter_box_in_third_parameter_box="
                << fourth_box_in_third_parameter_box
                << " third_inclusion="
                << subsetInterior(third_newton, third_x_box)
                << " root_parameter_gap=" << root_parameter_gap << "\n";
      if (!subsetInterior(newton, x_box)) {
        return 1;
      }
      if (determinant.contains(0.0)) {
        throw std::runtime_error(
            "fourth-root Newton inclusion passed but determinant contains zero");
      }
      if (!fourth_box_in_third_parameter_box ||
          !third_window_brackets_every_imaginary_zero ||
          !subsetInterior(third_newton, third_x_box) ||
          !(root_parameter_gap.leftBound() > 0.0)) {
        throw std::runtime_error(
            "fourth root did not exclude the earlier positive-primary root");
      }
      std::cout << "PASS_FOURTH_ROOT method=CAPD-6.1.0-native "
                   "stage=planar-fourth-light-collision-interval-newton\n";
      return 0;
    }
    if (third_root_only) {
      const interval kappa_center =
          interval(12640090996.0) / interval(10000000000.0);
      const interval kappa_radius =
          interval(4.0) / interval(10000000000.0);
      const interval third_duration_center =
          interval(588416.0) / interval(1000000.0);
      const interval third_duration_radius =
          interval(2.0) / interval(100000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const interval third_duration_box =
          third_duration_center + symmetric(third_duration_radius);
      const Evaluation center = evaluate_third_pair_collision(
          kappa_center, third_duration_center);
      const Evaluation box = evaluate_third_pair_collision(
          kappa_box, third_duration_box);
      IVector x_center(2);
      x_center[0] = kappa_center;
      x_center[1] = third_duration_center;
      IVector x_box(2);
      x_box[0] = kappa_box;
      x_box[1] = third_duration_box;
      const IVector newton =
          interval_newton(x_center, center.residual, box.jacobian);
      const interval determinant =
          box.jacobian[0][0] * box.jacobian[1][1] -
          box.jacobian[0][1] * box.jacobian[1][0];
      std::cout << std::hexfloat
                << "THIRD_ROOT_DATA method=CAPD-6.1.0-native"
                << " box=" << x_box
                << " center_residual=" << center.residual
                << " jacobian=" << box.jacobian
                << " determinant=" << determinant
                << " newton=" << newton
                << " final_state_box=" << box.final_state
                << " inclusion=" << subsetInterior(newton, x_box) << "\n";
      if (!subsetInterior(newton, x_box)) {
        return 1;
      }
      if (determinant.contains(0.0)) {
        throw std::runtime_error(
            "third-root Newton inclusion passed but determinant contains zero");
      }
      std::cout << "PASS_THIRD_ROOT method=CAPD-6.1.0-native "
                   "stage=planar-third-light-collision-interval-newton\n";
      return 0;
    }
    if (second_escape_only) {
      const interval second_kappa_center =
          interval(12640119251.0) / interval(10000000000.0);
      const interval second_duration_center =
          interval(10275749204.0) / interval(10000000000.0);
      const interval second_kappa_radius =
          interval(7.0) / interval(1000000000.0);
      const interval second_duration_radius =
          interval(5.0) / interval(100000000.0);
      const interval second_kappa_box =
          second_kappa_center + symmetric(second_kappa_radius);
      const interval second_duration_box =
          second_duration_center + symmetric(second_duration_radius);
      const SecondEscapeEvaluation second_escape =
          evaluate_second_collision_ejection_escape(second_kappa_box,
                                                     second_duration_box);
      std::cout << std::hexfloat
                << "SECOND_ESCAPE_DATA method=CAPD-6.1.0-native"
                << " kappa_box=" << second_kappa_box
                << " duration_box=" << second_duration_box
                << " negative_lc_exit=" << second_escape.negative_lc_exit
                << " positive_lc_entry=" << second_escape.positive_lc_entry
                << " positive_lc_exit=" << second_escape.positive_lc_exit
                << " bridge_exit=" << second_escape.bridge_exit
                << " minimum_negative_chart_other_squared="
                << second_escape.minimum_negative_chart_other_squared
                << " minimum_positive_chart_other_squared="
                << second_escape.minimum_positive_chart_other_squared
                << " minimum_bridge_primary_squared="
                << second_escape.minimum_bridge_primary_squared
                << " escape_margin=" << second_escape.escape_margin
                << " finite_mass_margin="
                << second_escape.finite_mass_margin << "\n";
      std::cout << "PASS_SECOND_ESCAPE method=CAPD-6.1.0-native "
                   "stage=planar-second-collision-ejection-escape\n";
      return 0;
    }
    if (second_escape_wide) {
      const interval base_kappa =
          interval(12640119251.0) / interval(10000000000.0);
      const interval duration_center =
          interval(10275749204.0) / interval(10000000000.0);
      const interval duration_radius =
          interval(5.0) / interval(100000000.0);
      const interval duration_box =
          duration_center + symmetric(duration_radius);
      std::vector<std::pair<int, int>> tiles;
      for (int offset = -2002; offset <= 714; offset += 14) {
        tiles.emplace_back(offset, 7);
      }
      interval covered_lower;
      interval covered_upper;
      double worst_negative_other_squared = 1000000.0;
      double worst_positive_other_squared = 1000000.0;
      double worst_bridge_primary_squared = 1000000.0;
      double worst_escape_margin = 1000000.0;
      double worst_finite_mass_margin = 1000000.0;
      for (std::size_t index = 0; index < tiles.size(); ++index) {
        const interval center =
            base_kappa + interval(static_cast<double>(tiles[index].first)) /
                             interval(1000000000.0);
        const interval radius =
            interval(static_cast<double>(tiles[index].second)) /
            interval(1000000000.0);
        const interval kappa_box = center + symmetric(radius);
        const SecondEscapeEvaluation result =
            evaluate_second_collision_ejection_escape(
                kappa_box, duration_box, tiles[index].first != 0);
        if (index == 0) {
          covered_lower = interval(kappa_box.leftBound());
        }
        covered_upper = interval(kappa_box.rightBound());
        worst_negative_other_squared =
            std::min(worst_negative_other_squared,
                     result.minimum_negative_chart_other_squared.leftBound());
        worst_positive_other_squared =
            std::min(worst_positive_other_squared,
                     result.minimum_positive_chart_other_squared.leftBound());
        worst_bridge_primary_squared =
            std::min(worst_bridge_primary_squared,
                     result.minimum_bridge_primary_squared.leftBound());
        worst_escape_margin =
            std::min(worst_escape_margin, result.escape_margin.leftBound());
        worst_finite_mass_margin =
            std::min(worst_finite_mass_margin,
                     result.finite_mass_margin.leftBound());
        std::cout << std::hexfloat
                  << "SECOND_ESCAPE_TILE method=CAPD-6.1.0-native"
                  << " tile=" << index << " offset_nano="
                  << tiles[index].first << " radius_nano="
                  << tiles[index].second << " kappa_box=" << kappa_box << "\n";
      }
      std::cout << "PASS_SECOND_ESCAPE_WIDE method=CAPD-6.1.0-native "
                   "stage=planar-second-collision-ejection-escape"
                << " tiles=" << tiles.size() << " kappa_interval="
                << interval(covered_lower.leftBound(),
                            covered_upper.rightBound())
                << " worst_negative_chart_other_squared="
                << worst_negative_other_squared
                << " worst_positive_chart_other_squared="
                << worst_positive_other_squared
                << " worst_bridge_primary_squared="
                << worst_bridge_primary_squared
                << " worst_escape_margin=" << worst_escape_margin
                << " worst_finite_mass_margin=" << worst_finite_mass_margin
                << "\n";
      return 0;
    }
    if (second_escape_probe) {
      const interval base_kappa =
          interval(12640119251.0) / interval(10000000000.0);
      const interval duration_center =
          interval(10275749204.0) / interval(10000000000.0);
      const interval duration_radius =
          interval(5.0) / interval(100000000.0);
      const interval kappa_center =
          base_kappa + interval(static_cast<double>(second_probe_offset)) /
                           interval(1000000000.0);
      const interval kappa_radius =
          interval(static_cast<double>(second_probe_radius)) /
          interval(1000000000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const interval duration_box =
          duration_center + symmetric(duration_radius);
      const SecondEscapeEvaluation result =
          evaluate_second_collision_ejection_escape(
              kappa_box, duration_box, second_probe_offset != 0);
      std::cout << std::hexfloat
                << "PASS_SECOND_ESCAPE_PROBE method=CAPD-6.1.0-native"
                << " offset_nano=" << second_probe_offset
                << " radius_nano=" << second_probe_radius
                << " kappa_box=" << kappa_box
                << " minimum_negative_chart_other_squared="
                << result.minimum_negative_chart_other_squared
                << " minimum_positive_chart_other_squared="
                << result.minimum_positive_chart_other_squared
                << " minimum_bridge_primary_squared="
                << result.minimum_bridge_primary_squared
                << " escape_margin=" << result.escape_margin
                << " finite_mass_margin=" << result.finite_mass_margin
                << "\n";
      return 0;
    }
    if (second_fourth_probe) {
      const interval base_kappa =
          interval(12640119251.0) / interval(10000000000.0);
      const interval duration_center =
          interval(10275749204.0) / interval(10000000000.0);
      const interval duration_radius =
          interval(5.0) / interval(100000000.0);
      const interval kappa_center =
          base_kappa + interval(static_cast<double>(second_probe_offset)) /
                           interval(1000000000.0);
      const interval kappa_radius =
          interval(static_cast<double>(second_probe_radius)) /
          interval(1000000000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const interval duration_box =
          duration_center + symmetric(duration_radius);
      const interval fourth_duration =
          interval(static_cast<double>(second_fourth_duration_million)) /
          interval(1000000.0);
      const SecondEscapeEvaluation result =
          evaluate_second_collision_ejection_escape(
              kappa_box, duration_box, second_probe_offset != 0, true,
              fourth_duration);
      std::cout << std::hexfloat
                << "PASS_SECOND_FOURTH_PROBE method=CAPD-6.1.0-native"
                << " offset_nano=" << second_probe_offset
                << " radius_nano=" << second_probe_radius
                << " duration_million=" << second_fourth_duration_million
                << " kappa_box=" << kappa_box
                << " minimum_bridge_primary_squared="
                << result.minimum_bridge_primary_squared
                << " escape_margin=" << result.escape_margin
                << " finite_mass_margin=" << result.finite_mass_margin
                << "\n";
      return 0;
    }
    if (fourth_correlated_probe || fourth_correlated_section_probe) {
      const interval kappa_center =
          interval(1264009098895.0 +
                   static_cast<double>(correlated_offset_pico)) /
          interval(1000000000000.0);
      const interval kappa_radius =
          interval(static_cast<double>(correlated_radius_pico)) /
          interval(1000000000000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const interval fourth_start_duration =
          interval(37284.0) / interval(100000.0);
      const interval fourth_extra_duration =
          interval(427160.0) / interval(1000000.0);
      const interval fifth_target =
          interval(static_cast<double>(second_fifth_duration_million)) /
          interval(1000000.0);
      const double correlated_zeta_start =
          kZetaStart;
      const CorrelatedFifthEvaluation result =
          fourth_correlated_section_probe
              ? evaluate_fully_correlated_fifth_section_probe(kappa_box,
                                                              fifth_target)
              : evaluate_correlated_fifth_probe(
                    kappa_box, fourth_start_duration, fourth_extra_duration,
                    fifth_target, false, correlated_zeta_start);
      std::cout << std::hexfloat
                << (fourth_fifth_outgoing_only
                        ? "FOURTH_FIFTH_OUTGOING_DATA "
                        : (fourth_correlated_section_probe
                               ? "CORRELATED_FIFTH_SECTION_PROBE "
                               : "CORRELATED_FIFTH_PROBE "))
                << "method=CAPD-6.1.0-native"
                << " offset_pico=" << correlated_offset_pico
                << " radius_pico=" << correlated_radius_pico
                << " zeta_start=" << correlated_zeta_start
                << " kappa_box=" << kappa_box
                << " fifth_target=" << fifth_target
                << " fifth_entry=" << result.fifth_entry
                << " fifth_exit=" << result.fifth_exit;
      if (!fourth_correlated_section_probe) {
        std::cout << " minimum_fourth_other_squared="
                  << result.minimum_fourth_other_squared
                  << " minimum_fifth_other_squared="
                  << result.minimum_fifth_other_squared;
      }
      std::cout
                << " fifth_exit_selected_norm="
                << result.fifth_exit_selected_norm
                << " fifth_exit_other_squared="
                << result.fifth_exit_other_squared
                << " fifth_section_derivative="
                << result.fifth_section_derivative
                << " fifth_return_time=" << result.fifth_return_time
                << "\n";
      if (fourth_fifth_outgoing_only) {
        if (!(result.fifth_entry[1].rightBound() < 0.0 &&
              result.fifth_exit_selected_norm.leftBound() > 0.0 &&
              result.fifth_exit_other_squared.leftBound() > 0.0 &&
              result.fifth_section_derivative.leftBound() > 0.0)) {
          throw std::runtime_error(
              "fifth outgoing section failed a terminal inequality");
        }
        std::cout << "PASS_FOURTH_FIFTH_OUTGOING "
                     "method=CAPD-6.1.0-native "
                     "stage=planar-fourth-root-to-fifth-outgoing-section\n";
      }
      return 0;
    }
    if (fourth_fifth_entry_only) {
      const interval kappa_center =
          interval(1264009098895.0) / interval(1000000000000.0);
      const interval kappa_radius =
          interval(395.0) / interval(1000000000000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const interval fourth_start_duration =
          interval(37284.0) / interval(100000.0);
      const interval fourth_extra_duration =
          interval(427160.0) / interval(1000000.0);
      const FourthOutgoingEvaluation result = evaluate_fourth_outgoing(
          kappa_box, fourth_start_duration, fourth_extra_duration,
          interval(0.0), true);
      std::cout << std::hexfloat
                << "FOURTH_FIFTH_ENTRY_DATA method=CAPD-6.1.0-native"
                << " kappa_box=" << kappa_box
                << " fourth_start_duration=" << fourth_start_duration
                << " fourth_extra_duration=" << fourth_extra_duration
                << " fourth_exit=" << result.fourth_exit
                << " fifth_entry=" << result.fifth_entry
                << " minimum_fourth_other_squared="
                << result.minimum_fourth_other_squared
                << " fourth_exit_selected_norm="
                << result.fourth_exit_selected_norm
                << " fifth_switch_qx=" << result.fifth_switch_qx
                << " fifth_switch_squared="
                << result.fifth_switch_squared << "\n";
      std::cout << "PASS_FOURTH_FIFTH_ENTRY method=CAPD-6.1.0-native "
                   "stage=planar-fourth-outgoing-fifth-chart-entry\n";
      return 0;
    }
    if (fourth_outgoing_probe) {
      const interval kappa_center =
          interval(1264009098895.0) / interval(1000000000000.0);
      const interval kappa_radius =
          interval(395.0) / interval(1000000000000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const interval fourth_start_duration =
          interval(37284.0) / interval(100000.0);
      const interval fourth_extra_duration =
          interval(static_cast<double>(second_fourth_duration_million)) /
          interval(1000000.0);
      const interval fifth_duration =
          interval(static_cast<double>(second_fifth_duration_million)) /
          interval(1000000.0);
      const FourthOutgoingEvaluation result = evaluate_fourth_outgoing(
          kappa_box, fourth_start_duration, fourth_extra_duration,
          fifth_duration);
      std::cout << std::hexfloat
                << "PASS_FOURTH_OUTGOING_PROBE method=CAPD-6.1.0-native"
                << " kappa_box=" << kappa_box
                << " fourth_start_duration=" << fourth_start_duration
                << " fourth_extra_duration=" << fourth_extra_duration
                << " fifth_duration=" << fifth_duration
                << " fourth_exit=" << result.fourth_exit
                << " fifth_entry=" << result.fifth_entry
                << " fifth_exit=" << result.fifth_exit
                << " bridge_exit=" << result.bridge_exit
                << " minimum_fourth_other_squared="
                << result.minimum_fourth_other_squared
                << " minimum_fifth_other_squared="
                << result.minimum_fifth_other_squared
                << " minimum_bridge_primary_squared="
                << result.minimum_bridge_primary_squared
                << " escape_margin=" << result.escape_margin
                << " finite_mass_margin=" << result.finite_mass_margin
                << "\n";
      return 0;
    }
    if (second_fourth_root_probe) {
      const interval base_kappa =
          interval(12640119251.0) / interval(10000000000.0);
      const interval kappa_center =
          base_kappa + interval(static_cast<double>(second_probe_offset)) /
                           interval(1000000000.0);
      const interval kappa_radius =
          interval(static_cast<double>(second_probe_radius)) /
          interval(1000000000.0);
      const interval fourth_duration_center =
          interval(static_cast<double>(second_fourth_duration_million)) /
          interval(1000000.0);
      const interval fourth_duration_radius =
          interval(static_cast<double>(
              second_fourth_duration_radius_million)) /
          interval(1000000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const interval fourth_duration_box =
          fourth_duration_center + symmetric(fourth_duration_radius);
      const Evaluation center = evaluate_fourth_pair_collision(
          kappa_center, fourth_duration_center);
      const Evaluation box = evaluate_fourth_pair_collision(
          kappa_box, fourth_duration_box);
      IVector x_center(2);
      x_center[0] = kappa_center;
      x_center[1] = fourth_duration_center;
      IVector x_box(2);
      x_box[0] = kappa_box;
      x_box[1] = fourth_duration_box;
      const IVector newton =
          interval_newton(x_center, center.residual, box.jacobian);
      const interval determinant =
          box.jacobian[0][0] * box.jacobian[1][1] -
          box.jacobian[0][1] * box.jacobian[1][0];
      std::cout << std::hexfloat
                << "FOURTH_ROOT_PROBE method=CAPD-6.1.0-native"
                << " box=" << x_box
                << " center_residual=" << center.residual
                << " jacobian=" << box.jacobian
                << " determinant=" << determinant
                << " newton=" << newton
                << " final_state_box=" << box.final_state
                << " inclusion=" << subsetInterior(newton, x_box) << "\n";
      return subsetInterior(newton, x_box) ? 0 : 1;
    }
    if (third_root_probe) {
      const interval base_kappa =
          interval(12640119251.0) / interval(10000000000.0);
      const interval kappa_center =
          base_kappa + interval(static_cast<double>(second_probe_offset)) /
                           interval(1000000000.0);
      const interval kappa_radius =
          interval(static_cast<double>(second_probe_radius)) /
          interval(1000000000.0);
      const interval third_duration_center =
          interval(static_cast<double>(second_fourth_duration_million)) /
          interval(1000000.0);
      const interval third_duration_radius =
          interval(static_cast<double>(
              second_fourth_duration_radius_million)) /
          interval(1000000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const interval third_duration_box =
          third_duration_center + symmetric(third_duration_radius);
      const Evaluation center = evaluate_third_pair_collision(
          kappa_center, third_duration_center);
      const Evaluation box = evaluate_third_pair_collision(
          kappa_box, third_duration_box);
      IVector x_center(2);
      x_center[0] = kappa_center;
      x_center[1] = third_duration_center;
      IVector x_box(2);
      x_box[0] = kappa_box;
      x_box[1] = third_duration_box;
      const IVector newton =
          interval_newton(x_center, center.residual, box.jacobian);
      const interval determinant =
          box.jacobian[0][0] * box.jacobian[1][1] -
          box.jacobian[0][1] * box.jacobian[1][0];
      std::cout << std::hexfloat
                << "THIRD_ROOT_PROBE method=CAPD-6.1.0-native"
                << " box=" << x_box
                << " center_residual=" << center.residual
                << " jacobian=" << box.jacobian
                << " determinant=" << determinant
                << " newton=" << newton
                << " final_state_box=" << box.final_state
                << " inclusion=" << subsetInterior(newton, x_box) << "\n";
      return subsetInterior(newton, x_box) ? 0 : 1;
    }
    const interval kappa_center = interval(12679351755.0) / interval(10000000000.0);
    const interval duration_center = interval(10712485057.0) / interval(10000000000.0);
    const interval kappa_radius = interval(1.0) / interval(10000000.0);
    const interval duration_radius = interval(1.0) / interval(10000000.0);
    const interval kappa_box = kappa_center + symmetric(kappa_radius);
    const interval duration_box = duration_center + symmetric(duration_radius);

    const Evaluation center = evaluate_box(kappa_center, duration_center);
    const Evaluation box = evaluate_box(kappa_box, duration_box);
    IVector x_center(2);
    x_center[0] = kappa_center;
    x_center[1] = duration_center;
    IVector x_box(2);
    x_box[0] = kappa_box;
    x_box[1] = duration_box;
    const IVector newton = interval_newton(x_center, center.residual, box.jacobian);
    const interval determinant =
        box.jacobian[0][0] * box.jacobian[1][1] -
        box.jacobian[0][1] * box.jacobian[1][0];

    std::cout << std::hexfloat
              << "ROOT_DATA method=CAPD-6.1.0-native"
              << " box=" << x_box
              << " center_residual=" << center.residual
              << " jacobian=" << box.jacobian
              << " determinant=" << determinant
              << " newton=" << newton
              << " final_state_box=" << box.final_state
              << " inclusion=" << subsetInterior(newton, x_box) << "\n";
    if (!subsetInterior(newton, x_box)) {
      return 1;
    }
    if (determinant.contains(0.0)) {
      throw std::runtime_error("Newton inclusion passed but determinant contains zero");
    }
    const interval escape_kappa_radius =
        interval(static_cast<double>(escape_tile_radius)) /
        interval(1000000.0);
    for (int tile = 0; tile < escape_tile_count; ++tile) {
      const int offset_numerator =
          first_escape_offset + 2 * escape_tile_radius * tile;
      const interval escape_kappa_center =
          kappa_center + interval(static_cast<double>(offset_numerator)) /
                             interval(1000000.0);
      const interval escape_kappa_box =
          escape_kappa_center + symmetric(escape_kappa_radius);
      const EscapeEvaluation escape =
          evaluate_collision_ejection_escape(escape_kappa_box);
      std::cout << "ESCAPE_TILE method=CAPD-6.1.0-native"
                << " tile=" << tile
                << " kappa_box=" << escape_kappa_box
                << " minimum_primary_squared=" << escape.minimum_primary_squared
                << " escape_margin=" << escape.escape_margin
                << " finite_mass_margin=" << escape.finite_mass_margin << "\n";
    }
    const interval escape_kappa_lower =
        kappa_center +
        interval(static_cast<double>(first_escape_offset - escape_tile_radius)) /
            interval(1000000.0);
    const interval escape_kappa_upper =
        kappa_center +
        interval(static_cast<double>(first_escape_offset +
                                     2 * escape_tile_radius *
                                         (escape_tile_count - 1) +
                                     escape_tile_radius)) /
            interval(1000000.0);
    const interval escape_kappa_union(escape_kappa_lower.leftBound(),
                                      escape_kappa_upper.rightBound());
    std::cout << "PASS_ROOT method=CAPD-6.1.0-native "
                 "stage=planar-light-collision-interval-newton\n";
    std::cout << "PASS_ESCAPE method=CAPD-6.1.0-native "
                 "stage=planar-light-collision-ejection-escape"
              << " tiles=" << escape_tile_count;
    if (first_escape_offset != -9 || escape_tile_radius != 1) {
      std::cout << " first_offset=" << first_escape_offset
                << " tile_radius=" << escape_tile_radius;
    }
    std::cout << " kappa_interval=" << escape_kappa_union << "\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FAIL " << error.what() << "\n";
    return 2;
  }
}
