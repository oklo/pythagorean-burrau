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

#ifdef BURRAU_CAPD_MULTIPRECISION
#include "capd/mpcapdlib.h"
#else
#include "capd/capdlib.h"
#endif
#include "capd/dynsys/DynSysMap.h"

namespace {

#ifdef BURRAU_CAPD_MULTIPRECISION
using C1Rect2Set = capd::MpC1Rect2Set;
using C0Rect2Set = capd::MpC0Rect2Set;
using IMap = capd::MpIMap;
using IMatrix = capd::MpIMatrix;
using IOdeSolver = capd::MpIOdeSolver;
using ICoordinateSection = capd::MpICoordinateSection;
using IPoincareMap = capd::MpIPoincareMap;
using ITimeMap = capd::MpITimeMap;
using IVector = capd::MpIVector;
using interval = capd::MpInterval;
#else
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
#endif

constexpr double kZetaStart = 15.0;
#ifdef BURRAU_CAPD_MULTIPRECISION
constexpr double kSolverTolerance = 1e-20;
#else
constexpr double kSolverTolerance = 1e-15;
#endif

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

double lower_bound_as_double(const interval& value) {
#ifdef BURRAU_CAPD_MULTIPRECISION
  return toDouble(value.leftBound());
#else
  return value.leftBound();
#endif
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

std::string optional_variable_prefix(int count) {
  return count > 0 ? frozen_variables(count) + "," : "";
}

std::string optional_zero_prefix(int count) {
  return count > 0 ? frozen_zeros(count) + "," : "";
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

IMap make_prefixed_positive_section_delta_field(int frozen_count) {
  return IMap("par:C;var:" + optional_variable_prefix(frozen_count) +
              "cr,ci,dr,di,ch,ct,delta;fun:" +
              frozen_zeros(frozen_count + 6) + ",C-ci;");
}

IMap make_prefixed_positive_section_projection_field(int frozen_count) {
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
  const std::string dr_field =
      "(-ch*cr/2-(cr^2+ci^2)*" + force_real + "/2)";
  const std::string di_field =
      "(-ch*ci/2-(cr^2+ci^2)*" + force_imag + "/2)";
  const std::string energy_field =
      "(-2*((cr*dr-ci*di)*" + gx + "+(cr*di+ci*dr)*" + gy + "))";
  const std::string factor = "(delta/(-di))";
  return IMap("var:" + optional_variable_prefix(frozen_count) +
              "cr,ci,dr,di,ch,ct,delta;fun:" +
              optional_zero_prefix(frozen_count) + "(-dr)*" + factor +
              ",delta," + dr_field + "*" + factor + "," + di_field +
              "*" + factor + "," + energy_field + "*" + factor +
              ",(-(cr^2+ci^2))*" + factor + ",0;");
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

std::pair<std::string, std::string> two_centre_reversed_momentum(
    const std::string& sr, const std::string& si,
    const std::string& cr, const std::string& ci) {
  const std::string metric =
      "((" + sr + "^2+" + si + "^2)*(" + cr + "^2+" + ci + "^2))";
  const std::string zr =
      "((" + cr + "^2-" + ci + "^2-" + sr + "^2+" + si + "^2)/2)";
  const std::string zi = "(" + cr + "*" + ci + "-" + sr + "*" + si + ")";
  const std::string ar = "(-" + sr + "*" + cr + "+" + si + "*" + ci + ")";
  const std::string ai = "(-" + sr + "*" + ci + "-" + si + "*" + cr + ")";
  const std::string dr =
      "((" + ar + ")^2-(" + ai + ")^2-(" + zr + ")^2+(" + zi + ")^2)";
  const std::string di =
      "(-2*(" + ar + ")*(" + ai + ")+2*(" + zr + ")*(" + zi + "))";
  const std::string azr =
      "((" + ar + ")*(" + zr + ")-(" + ai + ")*(" + zi + "))";
  const std::string azi =
      "((" + ar + ")*(" + zi + ")+(" + ai + ")*(" + zr + "))";
  const std::string k0r =
      "(2*(" + azr + "*" + dr + "-" + azi + "*" + di + ")/9)";
  const std::string k0i =
      "(2*(" + azr + "*" + di + "+" + azi + "*" + dr + ")/9)";
  const std::string br =
      "(-2*ee*((" + ar + ")*(" + zr + ")+(" + ai + ")*(" + zi + "))+" +
      k0r + "-" + metric + "*pr/3)";
  const std::string bi =
      "(-2*ee*((" + ai + ")*(" + zr + ")-(" + ar + ")*(" + zi + "))+" +
      k0i + "+2*(" + si + "*" + cr + "-" + sr + "*" + ci + ")/9-" +
      metric + "*pi/3)";
  return {"-(" + br + ")", "-(" + bi + ")"};
}

IMap make_prefixed_two_centre_s_entry_field(int frozen_count,
                                            bool has_section_delta = false) {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation =
      "(" + scale + "*exp(2*log(t)/3))";
  const std::string sqrt_separation = "sqrt(" + separation + ")";
  const std::string selected_norm = "(ur^2+ui^2)";
  const std::string qx = "(ur^2-ui^2)";
  const std::string qy = "(2*ur*ui)";
  const std::string qtx = "(2*(ur*vr-ui*vi)/" + selected_norm + ")";
  const std::string qty = "(2*(ur*vi+ui*vr)/" + selected_norm + ")";
  const std::string sr = "(-ui/" + sqrt_separation + ")";
  const std::string si = "(ur/" + sqrt_separation + ")";
  const std::string c_square_real = "(1-(" + sr + ")^2+(" + si + ")^2)";
  const std::string c_square_imag = "(-2*(" + sr + ")*(" + si + "))";
  const std::string c_square_norm =
      "sqrt((" + c_square_real + ")^2+(" + c_square_imag + ")^2)";
  const std::string cr =
      "sqrt((" + c_square_norm + "+" + c_square_real + ")/2)";
  const std::string ci = "((" + c_square_imag + ")/(2*(" + cr + ")))";
  const std::string zvx =
      "(t*(" + qtx + ")/" + separation + "-2*(" + qx + ")/(3*" +
      separation + "))";
  const std::string zvy =
      "(t*(" + qty + ")/" + separation + "-2*(" + qy + ")/(3*" +
      separation + "))";
  const std::string ar = "(-(" + sr + ")*(" + cr + ")+(" + si + ")*(" + ci + "))";
  const std::string ai = "(-(" + sr + ")*(" + ci + ")-(" + si + ")*(" + cr + "))";
  const std::string pr = "((" + ar + ")*(" + zvx + ")+(" + ai + ")*(" + zvy + "))";
  const std::string pi = "((" + ar + ")*(" + zvy + ")-(" + ai + ")*(" + zvx + "))";
  const std::string zr = "(1/2+(" + qx + ")/" + separation + ")";
  const std::string zi = "((" + qy + ")/" + separation + ")";
  const std::string c_norm = "((" + cr + ")^2+(" + ci + ")^2)";
  const std::string energy =
      "(" + separation + "*h/9-2*t*((" + qx + ")*(" + qtx + ")+(" +
      qy + ")*(" + qty + "))/(3*(" + separation + ")^2)+2*(" +
      selected_norm + ")^2/(9*(" + separation + ")^2)-((" + zr +
      ")^2+(" + zi + ")^2+1/(" + c_norm + "))/9)";
  const std::string section_delta_variable =
      has_section_delta ? ",section_delta" : "";
  return IMap("var:" + optional_variable_prefix(frozen_count) +
              "ur,ui,vr,vi,h,t" + section_delta_variable +
              ",sr,si,pr,pi,ee,zz;fun:" +
              frozen_zeros(frozen_count + 6 + (has_section_delta ? 1 : 0)) +
              "," + sr + "," + si + "," + pr + "," + pi + "," + energy +
              ",log(t);");
}

IMap make_prefixed_two_centre_s_to_xi_map(int frozen_count) {
  const std::string radius_plus =
      "sqrt((sr+1)^2+si^2)";
  const std::string radius_minus =
      "sqrt((sr-1)^2+si^2)";
  const std::string alpha_half =
      "asin((" + radius_plus + "-" + radius_minus + ")/2)";
  const std::string sinh_beta_half =
      "(si/cos(" + alpha_half + "))";
  const std::string beta_half =
      "log(" + sinh_beta_half + "+sqrt(1+(" + sinh_beta_half + ")^2))";
  return IMap("var:" + frozen_variables(frozen_count) +
              ",sr,si,pr,pi,ee,zz;fun:" +
              frozen_identity(frozen_count) + ",2*(" + alpha_half +
              "),2*(" + beta_half + "),pr,pi,ee,zz;");
}

IMap make_prefixed_negative_two_centre_entry_field(int frozen_count) {
  const std::string scale = "exp(log(9)/3)";
  const std::string separation =
      "(" + scale + "*exp(2*log(t)/3))";
  const std::string sqrt_separation = "sqrt(" + separation + ")";
  const std::string norm = "(ur^2+ui^2)";
  const std::string wr = "(-ur/" + sqrt_separation + ")";
  const std::string wi = "(-ui/" + sqrt_separation + ")";
  const std::string s_square_real = "(1-(" + wr + ")^2+(" + wi + ")^2)";
  const std::string s_square_imag = "(-2*(" + wr + ")*(" + wi + "))";
  const std::string s_square_norm =
      "sqrt((" + s_square_real + ")^2+(" + s_square_imag + ")^2)";
  const std::string sr =
      "sqrt((" + s_square_norm + "+" + s_square_real + ")/2)";
  const std::string si = "((" + s_square_imag + ")/(2*(" + sr + ")))";
  const std::string conjugate_s_v_real =
      "((" + sr + ")*vr+(" + si + ")*vi)";
  const std::string conjugate_s_v_imag =
      "((" + sr + ")*vi-(" + si + ")*vr)";
  const std::string conjugate_s_u_real =
      "((" + sr + ")*ur+(" + si + ")*ui)";
  const std::string conjugate_s_u_imag =
      "((" + sr + ")*ui-(" + si + ")*ur)";
  const std::string pr =
      "(-2*(" + conjugate_s_v_real + ")/3+2*" + norm + "*(" +
      conjugate_s_u_real + ")/(9*t))";
  const std::string pi =
      "(-2*(" + conjugate_s_v_imag + ")/3+2*" + norm + "*(" +
      conjugate_s_u_imag + ")/(9*t))";
  const std::string qx = "(ur^2-ui^2)";
  const std::string qy = "(2*ur*ui)";
  const std::string zr = "((" + qx + ")/" + separation + "-1/2)";
  const std::string zi = "((" + qy + ")/" + separation + ")";
  const std::string s_norm = "((" + sr + ")^2+(" + si + ")^2)";
  const std::string energy =
      "(" + separation + "*h/9-4*t*(ur*vr+ui*vi)/(3*(" + separation +
      ")^2)+2*(" + norm + ")^2/(9*(" + separation + ")^2)-((" + zr +
      ")^2+(" + zi + ")^2+1/(" + s_norm + "))/9)";
  return IMap(
      "var:" + optional_variable_prefix(frozen_count) +
      "ur,ui,vr,vi,h,t,wr,wi,pr,pi,ee,zz;fun:" +
      frozen_zeros(frozen_count + 6) + "," + wr + "," + wi + "," + pr +
      "," + pi + "," + energy + ",log(t);");
}

IMap make_prefixed_negative_two_centre_to_xi_map(int frozen_count) {
  const std::string radius_plus = "sqrt((wr+1)^2+wi^2)";
  const std::string radius_minus = "sqrt((wr-1)^2+wi^2)";
  const std::string delta_half =
      "asin((" + radius_plus + "-" + radius_minus + ")/2)";
  const std::string sinh_beta_half =
      "(wi/cos(" + delta_half + "))";
  const std::string beta_half =
      "log(" + sinh_beta_half + "+sqrt(1+(" + sinh_beta_half + ")^2))";
  IMap map(
      "par:P;var:" + frozen_variables(frozen_count) +
      ",wr,wi,pr,pi,ee,zz;fun:" + frozen_identity(frozen_count) +
      ",P+2*(" + delta_half + "),2*(" + beta_half +
      "),pr,pi,ee,zz;");
  map.setParameter("P", acos(interval(-1.0)));
  return map;
}

IMap make_prefixed_two_centre_xi_field(int frozen_count) {
  const std::string exp_half = "exp(beta/2)";
  const std::string exp_minus_half = "exp(-beta/2)";
  const std::string cosh_half =
      "((" + exp_half + "+" + exp_minus_half + ")/2)";
  const std::string sinh_half =
      "((" + exp_half + "-" + exp_minus_half + ")/2)";
  const std::string sr = "(sin(alpha/2)*" + cosh_half + ")";
  const std::string si = "(cos(alpha/2)*" + sinh_half + ")";
  const std::string cr = "(cos(alpha/2)*" + cosh_half + ")";
  const std::string ci = "(-sin(alpha/2)*" + sinh_half + ")";
  const auto momentum =
      two_centre_reversed_momentum(sr, si, cr, ci);
  const std::string metric =
      "((" + sr + "^2+" + si + "^2)*(" + cr + "^2+" + ci + "^2))";
  return IMap("var:" + optional_variable_prefix(frozen_count) +
              "alpha,beta,pr,pi,ee,zz;fun:" +
              optional_zero_prefix(frozen_count) + "-pr,-pi," + momentum.first +
              "," + momentum.second + ",(pr^2+pi^2)/3,-" + metric + ";");
}

IMap make_two_centre_xi_to_bridge_map() {
  const std::string exp_half = "exp(beta/2)";
  const std::string exp_minus_half = "exp(-beta/2)";
  const std::string cosh_half =
      "((" + exp_half + "+" + exp_minus_half + ")/2)";
  const std::string sinh_half =
      "((" + exp_half + "-" + exp_minus_half + ")/2)";
  const std::string sr = "(sin(alpha/2)*" + cosh_half + ")";
  const std::string si = "(cos(alpha/2)*" + sinh_half + ")";
  const std::string cr = "(cos(alpha/2)*" + cosh_half + ")";
  const std::string ci = "(-sin(alpha/2)*" + sinh_half + ")";
  const std::string ar = "(-(" + sr + "*" + cr + "-" + si + "*" + ci + "))";
  const std::string ai = "(-(" + sr + "*" + ci + "+" + si + "*" + cr + "))";
  const std::string a_norm = "((" + ar + ")^2+(" + ai + ")^2)";
  const std::string zr =
      "((" + cr + "^2-" + ci + "^2-" + sr + "^2+" + si + "^2)/2)";
  const std::string zi = "(" + cr + "*" + ci + "-" + sr + "*" + si + ")";
  const std::string zeta_r =
      "((pr*(" + ar + ")-pi*(" + ai + "))/" + a_norm + ")";
  const std::string zeta_i =
      "((pr*(" + ai + ")+pi*(" + ar + "))/" + a_norm + ")";
  const std::string lambda = "exp(zz/3)";
  const std::string time = "exp(zz)";
  const std::string radius =
      "(exp(log(9)/3)*(" + lambda + ")^2)";
  const std::string velocity_scale = "(" + radius + "/" + time + ")";
  return IMap("var:alpha,beta,pr,pi,ee,zz;fun:" + lambda + "," +
              radius + "*(" + zr + ")," + radius + "*(" + zi + ")," +
              velocity_scale + "*(" + zeta_r + "+2*(" + zr + ")/3)," +
              velocity_scale + "*(" + zeta_i + "+2*(" + zi + ")/3);");
}

IMap make_two_centre_xi_bridge_entry_field() {
  const std::string exp_half = "exp(beta/2)";
  const std::string exp_minus_half = "exp(-beta/2)";
  const std::string cosh_half =
      "((" + exp_half + "+" + exp_minus_half + ")/2)";
  const std::string sinh_half =
      "((" + exp_half + "-" + exp_minus_half + ")/2)";
  const std::string sr = "(sin(alpha/2)*" + cosh_half + ")";
  const std::string si = "(cos(alpha/2)*" + sinh_half + ")";
  const std::string cr = "(cos(alpha/2)*" + cosh_half + ")";
  const std::string ci = "(-sin(alpha/2)*" + sinh_half + ")";
  const std::string ar =
      "(-(" + sr + "*" + cr + "-" + si + "*" + ci + "))";
  const std::string ai =
      "(-(" + sr + "*" + ci + "+" + si + "*" + cr + "))";
  const std::string a_norm = "((" + ar + ")^2+(" + ai + ")^2)";
  const std::string zr =
      "((" + cr + "^2-" + ci + "^2-" + sr + "^2+" + si + "^2)/2)";
  const std::string zi =
      "(" + cr + "*" + ci + "-" + sr + "*" + si + ")";
  const std::string zeta_r =
      "((pr*(" + ar + ")-pi*(" + ai + "))/" + a_norm + ")";
  const std::string zeta_i =
      "((pr*(" + ai + ")+pi*(" + ar + "))/" + a_norm + ")";
  const std::string lambda = "exp(zz/3)";
  const std::string time = "exp(zz)";
  const std::string radius =
      "(exp(log(9)/3)*(" + lambda + ")^2)";
  const std::string velocity_scale = "(" + radius + "/" + time + ")";
  return IMap("var:alpha,beta,pr,pi,ee,zz,l,x,y,vx,vy;fun:0,0,0,0,0,0," +
              lambda + "," + radius + "*(" + zr + ")," + radius + "*(" +
              zi + ")," + velocity_scale + "*(" + zeta_r + "+2*(" + zr +
              ")/3)," + velocity_scale + "*(" + zeta_i + "+2*(" + zi +
              ")/3);");
}

TailData stable_tail_data(const interval& kappa,
                          double zeta_start = kZetaStart,
                          bool use_quintic = false,
                          bool use_octic = false) {
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

  if (use_octic) {
    struct HigherCoefficient {
      int transverse_degree;
      int longitudinal_degree;
      interval value;
    };
    const std::vector<HigherCoefficient> coefficients = {
        {0, 6, interval("-0.03554752308110342", "-0.03554752308110340")},
        {1, 5, interval("0.2906160326693456", "0.2906160326693458")},
        {2, 4, interval("0.7646840239192992", "0.7646840239192994")},
        {3, 3, interval("-0.5122119837097500", "-0.5122119837097498")},
        {4, 2, interval("-0.3255787974192630", "-0.3255787974192628")},
        {5, 1, interval("0.09018289042047256", "0.09018289042047258")},
        {6, 0, interval("0.01521532442954046", "0.01521532442954048")},
        {0, 7, interval("-0.02964819863976053", "-0.02964819863976051")},
        {1, 6, interval("0.2600382727429194", "0.2600382727429196")},
        {2, 5, interval("0.7759047148743020", "0.7759047148743022")},
        {3, 4, interval("-0.4073648753423704", "-0.4073648753423702")},
        {4, 3, interval("-0.2187679612531311", "-0.2187679612531309")},
        {5, 2, interval("0.02807587277422612", "0.02807587277422614")},
        {6, 1, interval("-0.000404357144551293", "-0.000404357144551291")},
        {7, 0, interval("0.000708212832192856", "0.000708212832192859")},
        {0, 8, interval("-0.01873149020245309", "-0.01873149020245307")},
        {1, 7, interval("0.1918736731487997", "0.1918736731487999")},
        {2, 6, interval("0.6342982024406687", "0.6342982024406689")},
        {3, 5, interval("0.04852346039467547", "0.04852346039467549")},
        {4, 4, interval("0.4311777542055598", "0.4311777542055600")},
        {5, 3, interval("-0.4538061636312411", "-0.4538061636312409")},
        {6, 2, interval("-0.2579769472856199", "-0.2579769472856197")},
        {7, 1, interval("0.06829716549840599", "0.06829716549840601")},
        {8, 0, interval("0.008908225658082670", "0.008908225658082672")},
    };
    for (const HigherCoefficient& coefficient : coefficients) {
      const int i = coefficient.transverse_degree;
      const int j = coefficient.longitudinal_degree;
      const interval monomial = power(p, i) * power(nu, j);
      const interval decay = interval(static_cast<double>(i)) * a_t +
                             interval(static_cast<double>(j)) * a_l;
      if (i % 2 == 1) {
        x += coefficient.value * monomial;
        vx -= decay * coefficient.value * monomial;
        if (j > 0) {
          dx_dnu += interval(static_cast<double>(j)) * coefficient.value *
                    power(p, i) * power(nu, j - 1);
          dvx_dnu -= decay * interval(static_cast<double>(j)) *
                     coefficient.value * power(p, i) *
                     power(nu, j - 1);
        }
      } else {
        q += coefficient.value * monomial;
        vq -= decay * coefficient.value * monomial;
        if (j > 0) {
          dq_dnu += interval(static_cast<double>(j)) * coefficient.value *
                    power(p, i) * power(nu, j - 1);
          dvq_dnu -= decay * interval(static_cast<double>(j)) *
                     coefficient.value * power(p, i) *
                     power(nu, j - 1);
        }
      }
    }
  }

  const interval p_ratio = interval(400.0) * exp(-interval(zeta_start) * a_t);
  const interval nu_ratio =
      interval(6500.0) * exp(-interval(zeta_start) * a_l);
  const interval lambda_upper(
      std::max(p_ratio.rightBound(), nu_ratio.rightBound()));
  const interval tail_scale =
      power(lambda_upper, use_octic ? 9 : (use_quintic ? 6 : 5));
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
  solver.setAbsoluteTolerance(kSolverTolerance);
  solver.setRelativeTolerance(kSolverTolerance);
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
  solver.setAbsoluteTolerance(kSolverTolerance);
  solver.setRelativeTolerance(kSolverTolerance);
  if (initial_step > 0.0) {
    solver.setStep(interval(initial_step));
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
  shape_solver.setAbsoluteTolerance(kSolverTolerance);
  shape_solver.setRelativeTolerance(kSolverTolerance);
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
  entry_solver.setAbsoluteTolerance(kSolverTolerance);
  entry_solver.setRelativeTolerance(kSolverTolerance);
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
  lc_solver.setAbsoluteTolerance(kSolverTolerance);
  lc_solver.setRelativeTolerance(kSolverTolerance);
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
                        bool use_quintic = false,
                        bool use_octic = false) {
  const TailData tail =
      stable_tail_data(kappa, zeta_start, use_quintic, use_octic);
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
                                         bool use_quintic = false,
                                         bool use_octic = false) {
  const Evaluation first =
      evaluate_box(kappa, interval(7.0) / interval(4.0), true, true,
                   zeta_start, use_quintic, use_octic);
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
  solver.setAbsoluteTolerance(kSolverTolerance);
  solver.setRelativeTolerance(kSolverTolerance);
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
  negative_solver.setAbsoluteTolerance(kSolverTolerance);
  negative_solver.setRelativeTolerance(kSolverTolerance);
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
  positive_solver.setAbsoluteTolerance(kSolverTolerance);
  positive_solver.setRelativeTolerance(kSolverTolerance);
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
                                           bool use_quintic = false,
                                           bool use_octic = false) {
  const interval second_duration =
      interval(10275749204.0) / interval(10000000000.0);
  const Evaluation second =
      evaluate_other_pair_collision(kappa, second_duration, true, true,
                                    zeta_start, use_quintic, use_octic);

  C1Rect2Set negative_set(second.final_state);
  IMap negative_field = make_other_pair_lc_field();
  IOdeSolver negative_solver(negative_field, 30);
  negative_solver.setAbsoluteTolerance(kSolverTolerance);
  negative_solver.setRelativeTolerance(kSolverTolerance);
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
  positive_solver.setAbsoluteTolerance(kSolverTolerance);
  positive_solver.setRelativeTolerance(kSolverTolerance);
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
  bridge_solver.setAbsoluteTolerance(kSolverTolerance);
  bridge_solver.setRelativeTolerance(kSolverTolerance);
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
  fourth_solver.setAbsoluteTolerance(kSolverTolerance);
  fourth_solver.setRelativeTolerance(kSolverTolerance);
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

IVector certified_fourth_collision_lc_state() {
  const interval kappa_center =
      exact_integer("1264009098895") / exact_integer("1000000000000");
  const interval kappa_radius =
      exact_integer("395") / exact_integer("1000000000000");
  const interval duration_center =
      exact_integer("37184") / exact_integer("100000");
  const interval duration_radius =
      exact_integer("1") / exact_integer("1000");
  const interval kappa_box = kappa_center + symmetric(kappa_radius);
  const interval duration_box = duration_center + symmetric(duration_radius);
  const Evaluation center = evaluate_fourth_pair_collision(
      kappa_center, duration_center, kZetaStart, true, true);
  const Evaluation box = evaluate_fourth_pair_collision(
      kappa_box, duration_box, kZetaStart, true, true);
  IVector root_center(2);
  root_center[0] = kappa_center;
  root_center[1] = duration_center;
  const IVector newton =
      root_center - capd::matrixAlgorithms::gauss(box.jacobian,
                                                   center.residual);
  IVector root_box(2);
  root_box[0] = kappa_box;
  root_box[1] = duration_box;
  std::cerr << std::hexfloat << "FOURTH_ROOT_OCTIC box=" << root_box
            << " residual=" << center.residual
            << " jacobian=" << box.jacobian << " newton=" << newton
            << " inclusion=" << subsetInterior(newton, root_box) << "\n";
  if (!subsetInterior(newton, root_box)) {
    throw std::runtime_error("octic fourth-root interval Newton failed");
  }
  Evaluation root_enclosure = evaluate_fourth_pair_collision(
      newton[0], newton[1], kZetaStart, true, true);
#ifdef BURRAU_CAPD_MULTIPRECISION
  IVector refined_center(2);
  refined_center[0] = newton[0].mid();
  refined_center[1] = newton[1].mid();
  const Evaluation refined_center_evaluation = evaluate_fourth_pair_collision(
      refined_center[0], refined_center[1], kZetaStart, true, true);
  const IVector refined_newton =
      refined_center - capd::matrixAlgorithms::gauss(
                           root_enclosure.jacobian,
                           refined_center_evaluation.residual);
  std::cerr << std::hexfloat
            << "FOURTH_ROOT_OCTIC_REFINED box=" << newton
            << " center=" << refined_center
            << " residual=" << refined_center_evaluation.residual
            << " jacobian=" << root_enclosure.jacobian
            << " newton=" << refined_newton
            << " inclusion=" << subsetInterior(refined_newton, newton)
            << "\n";
  if (!subsetInterior(refined_newton, newton)) {
    throw std::runtime_error("refined octic fourth-root Newton step failed");
  }
  root_enclosure = evaluate_fourth_pair_collision(
      refined_newton[0], refined_newton[1], kZetaStart, true, true);
#endif
  const interval vi = root_enclosure.final_state[3];
  const interval speed_square = interval(1.0) / interval(2.0) - sqr(vi);
  if (!(speed_square.leftBound() > 0.0 &&
        root_enclosure.final_state[2].leftBound() > 0.0)) {
    throw std::runtime_error(
        "fourth collision root lost its positive LC velocity sheet");
  }
  IVector collision(6);
  collision[0] = interval(0.0);
  collision[1] = interval(0.0);
  collision[2] = sqrt(speed_square);
  collision[3] = vi;
  collision[4] = root_enclosure.final_state[4];
  collision[5] = root_enclosure.final_state[5];
  return collision;
}

IVector cached_multiprecision_fourth_collision_lc_state() {
  // Deliberately widened decimal-rational hull of the independently replayed
  // PASS_FOURTH_ROOT_OCTIC MPFR-200 certificate.
  IVector collision(6);
  collision[0] = interval(0.0);
  collision[1] = interval(0.0);
  collision[3] = interval("-0.000000383235", "-0.000000368194");
  collision[2] = sqrt(interval(1.0) / interval(2.0) - sqr(collision[3]));
  collision[4] = interval("31.14722803", "31.14722824");
  collision[5] = interval("0.2644229941", "0.2644229946");
  return collision;
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
  bridge_solver.setAbsoluteTolerance(kSolverTolerance);
  bridge_solver.setRelativeTolerance(kSolverTolerance);
  ITimeMap bridge_time_map(bridge_solver);
  const interval lambda_center =
      (interval(lambda.leftBound()) + interval(lambda.rightBound())) /
      interval(2.0);
  const interval bridge_end = lambda_center + interval(2.0);
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
  negative_solver.setAbsoluteTolerance(kSolverTolerance);
  negative_solver.setRelativeTolerance(kSolverTolerance);
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
  positive_solver.setAbsoluteTolerance(kSolverTolerance);
  positive_solver.setRelativeTolerance(kSolverTolerance);
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
  bridge_pre_solver.setAbsoluteTolerance(kSolverTolerance);
  bridge_pre_solver.setRelativeTolerance(kSolverTolerance);
    ITimeMap bridge_pre_time_map(bridge_pre_solver);
    const interval bridge_switch_lambda =
        interval(13.0) / interval(20.0);
    const interval bridge_pre_lambda_center =
        (interval(lambda.leftBound()) + interval(lambda.rightBound())) /
        interval(2.0);
    const interval bridge_pre_end =
        bridge_pre_lambda_center - bridge_switch_lambda;
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
  fourth_solver.setAbsoluteTolerance(kSolverTolerance);
  fourth_solver.setRelativeTolerance(kSolverTolerance);
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
  bridge_solver.setAbsoluteTolerance(kSolverTolerance);
  bridge_solver.setRelativeTolerance(kSolverTolerance);
  ITimeMap bridge_time_map(bridge_solver);
  const interval lambda_center =
      (interval(bridge_restart[0].leftBound()) +
       interval(bridge_restart[0].rightBound())) /
      interval(2.0);
  const interval bridge_end = lambda_center + interval(2.0);
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
  IVector two_centre_entry;
  IVector two_centre_exit;
  interval minimum_fourth_other_squared;
  interval minimum_fifth_other_squared;
  interval fifth_exit_selected_norm;
  interval fifth_exit_other_squared;
  interval fifth_section_derivative;
  interval fifth_return_time;
  interval two_centre_shape_real_constraint;
  interval two_centre_shape_imag_constraint;
  interval two_centre_energy_constraint;
};

struct CommonClockFocusEvaluation {
  IVector lc_state;
  IVector two_centre_entry;
  IVector focus;
  interval selected_norm;
  interval return_time;
  interval energy_constraint;
};

struct CommonClockEscapeEvaluation {
  IVector first_focus;
  IVector separated_section;
  IVector bridge_exit;
  interval first_focus_selected_norm;
  interval minimum_primary_squared;
  interval escape_margin;
  interval finite_mass_margin;
};

IVector mean_value_fourth_common_clock_state(const interval& kappa) {
  const interval root_kappa(
      "1.26400909893331527", "1.26400909893331813");
  const interval root_clock(
      "0.371840180067887265", "0.371840186320052546");
  const interval common_clock =
      exact_integer("37184019") / exact_integer("100000000");

  C0Rect2Set reference_set(
      cached_multiprecision_fourth_collision_lc_state());
  IMap fourth_field = make_other_pair_lc_field();
  propagate_relative_time(
      reference_set, fourth_field, common_clock - root_clock);
  const IVector reference_state = static_cast<IVector>(reference_set);

  const interval hull(
      std::min(root_kappa.leftBound(), kappa.leftBound()),
      std::max(root_kappa.rightBound(), kappa.rightBound()));
  const Evaluation derivative_enclosure = evaluate_fourth_pair_collision(
      hull, common_clock, kZetaStart, true, true);
  const interval displacement = kappa - root_kappa;
  IVector state(6);
  for (int index = 0; index < 6; ++index) {
    state[index] =
        reference_state[index] +
        derivative_enclosure.kappa_tangent[index] * displacement;
  }
  return state;
}

void audit_common_clock_two_centre_leg(
    const C0Rect2Set& initial, IMap& field,
    const interval& return_time, bool require_decreasing_beta,
    int coordinate_offset = 6) {
  C0Rect2Set audit_set = initial;
  IOdeSolver audit_solver(field, 30);
  audit_solver.setAbsoluteTolerance(kSolverTolerance);
  audit_solver.setRelativeTolerance(kSolverTolerance);
  ITimeMap audit_map(audit_solver);
  const interval audit_end =
      audit_set.getCurrentTime() +
      interval(return_time.rightBound());
  audit_map.stopAfterStep(true);
  do {
    audit_map(audit_end, audit_set);
    const IVector enclosure = audit_set.getLastEnclosure();
    if (!(enclosure[coordinate_offset + 2].rightBound() < 0.0)) {
      throw std::runtime_error(
          "common-clock two-centre leg lost increasing alpha");
    }
    if (require_decreasing_beta &&
        !(enclosure[coordinate_offset + 3].leftBound() > 0.0)) {
      throw std::runtime_error(
          "common-clock two-centre leg lost decreasing beta");
    }
  } while (!audit_map.completed());
}

CommonClockFocusEvaluation evaluate_fourth_common_clock_focus(
    const interval& kappa, int focus_count) {
  const IVector common_state =
      mean_value_fourth_common_clock_state(kappa);
  C0Rect2Set active(common_state);
  IMap entry_field = make_prefixed_negative_two_centre_entry_field(0);
  active = append_coordinate_map(active, 6, entry_field);
  IMap xi_map = make_prefixed_negative_two_centre_to_xi_map(6);
  apply_same_dimension_map(active, xi_map);
  const IVector entry_full = static_cast<IVector>(active);
  IVector entry(6);
  for (int index = 0; index < 6; ++index) {
    entry[index] = entry_full[index + 6];
  }

  IMap field = make_prefixed_two_centre_xi_field(6);
  interval total_return_time(0.0);
  IVector focus(6);
  for (int focus_index = 0; focus_index < focus_count; ++focus_index) {
    const C0Rect2Set monotonicity_initial = active;
    IOdeSolver focus_solver(field, 30);
    focus_solver.setAbsoluteTolerance(kSolverTolerance);
    focus_solver.setRelativeTolerance(kSolverTolerance);
    const interval target_alpha =
        interval(static_cast<double>(2 + focus_index)) *
        acos(interval(-1.0));
    ICoordinateSection section(12, 6, target_alpha);
    IPoincareMap poincare(
        focus_solver, section, capd::poincare::MinusPlus);
    poincare.setMaxReturnTime(10.0);
    interval leg_return_time;
    const IVector focus_full = poincare(active, leg_return_time);
    total_return_time += leg_return_time;
    for (int index = 0; index < 6; ++index) {
      focus[index] = focus_full[index + 6];
    }

    audit_common_clock_two_centre_leg(
        monotonicity_initial, field, leg_return_time, false);
    active = C0Rect2Set(focus_full);
  }

  const interval beta = focus[1];
  const interval sinh_half =
      (exp(beta / interval(2.0)) -
       exp(-beta / interval(2.0))) /
      interval(2.0);
  const interval selected_norm = sqr(sinh_half);
  const interval alpha = focus[0];
  const interval cosh_half =
      (exp(beta / interval(2.0)) +
       exp(-beta / interval(2.0))) /
      interval(2.0);
  const interval sr = sin(alpha / interval(2.0)) * cosh_half;
  const interval si = cos(alpha / interval(2.0)) * sinh_half;
  const interval cr = cos(alpha / interval(2.0)) * cosh_half;
  const interval ci = -sin(alpha / interval(2.0)) * sinh_half;
  const interval s_norm = sqr(sr) + sqr(si);
  const interval c_norm = sqr(cr) + sqr(ci);
  const interval metric = s_norm * c_norm;
  const interval zr =
      (sqr(cr) - sqr(ci) - sqr(sr) + sqr(si)) / interval(2.0);
  const interval zi = cr * ci - sr * si;
  const interval energy_constraint =
      sqr(focus[2]) + sqr(focus[3]) -
      interval(2.0) * metric * focus[4] -
      interval(2.0) / interval(9.0) *
          (metric * (sqr(zr) + sqr(zi)) + s_norm + c_norm);
  return {common_state, entry, focus, selected_norm,
          total_return_time, energy_constraint};
}

CommonClockEscapeEvaluation evaluate_fourth_common_clock_escape(
    const interval& kappa) {
  const IVector common_state =
      mean_value_fourth_common_clock_state(kappa);
  C0Rect2Set active(common_state);
  IMap entry_field = make_prefixed_negative_two_centre_entry_field(0);
  active = append_coordinate_map(active, 6, entry_field);
  IMap xi_map = make_prefixed_negative_two_centre_to_xi_map(6);
  apply_same_dimension_map(active, xi_map);
  IMap field = make_prefixed_two_centre_xi_field(6);
  const C0Rect2Set focus_initial = active;

  IOdeSolver focus_solver(field, 30);
  focus_solver.setAbsoluteTolerance(kSolverTolerance);
  focus_solver.setRelativeTolerance(kSolverTolerance);
  const interval first_focus_alpha =
      interval(2.0) * acos(interval(-1.0));
  ICoordinateSection focus_section(12, 6, first_focus_alpha);
  IPoincareMap focus_poincare(
      focus_solver, focus_section, capd::poincare::MinusPlus);
  focus_poincare.setMaxReturnTime(10.0);
  interval focus_return_time;
  const IVector first_focus_full =
      focus_poincare(active, focus_return_time);
  audit_common_clock_two_centre_leg(
      focus_initial, field, focus_return_time, false);
  IVector first_focus(6);
  for (int index = 0; index < 6; ++index) {
    first_focus[index] = first_focus_full[index + 6];
  }
  const interval first_sinh =
      (exp(first_focus[1] / interval(2.0)) -
       exp(-first_focus[1] / interval(2.0))) /
      interval(2.0);
  const interval first_focus_selected_norm = sqr(first_sinh);
  if (!(first_focus[1].rightBound() < 0.0 &&
        first_focus[2].rightBound() < 0.0 &&
        first_focus_selected_norm.leftBound() > 0.0)) {
    throw std::runtime_error(
        "common-clock escape tile did not clear its first focus");
  }

  active = C0Rect2Set(first_focus_full);
  const C0Rect2Set separated_initial = active;
  IOdeSolver separated_solver(field, 30);
  separated_solver.setAbsoluteTolerance(kSolverTolerance);
  separated_solver.setRelativeTolerance(kSolverTolerance);
  const interval separated_beta(-1.0);
  ICoordinateSection separated_section_function(12, 7, separated_beta);
  IPoincareMap separated_poincare(
      separated_solver, separated_section_function,
      capd::poincare::PlusMinus);
  separated_poincare.setMaxReturnTime(10.0);
  interval separated_return_time;
  const IVector separated_full =
      separated_poincare(active, separated_return_time);
  audit_common_clock_two_centre_leg(
      separated_initial, field, separated_return_time, true);
  IVector separated_section(6);
  for (int index = 0; index < 6; ++index) {
    separated_section[index] = separated_full[index + 6];
  }
  const interval third_focus_alpha =
      interval(3.0) * acos(interval(-1.0));
  if (!(separated_section[0].rightBound() <
            third_focus_alpha.leftBound() &&
        separated_section[2].rightBound() < 0.0 &&
        separated_section[3].leftBound() > 0.0)) {
    throw std::runtime_error(
        "common-clock escape tile lost its separated outgoing sheet");
  }

  C0Rect2Set bridge_set(separated_section);
  IMap bridge_entry_field = make_two_centre_xi_bridge_entry_field();
  bridge_set =
      append_coordinate_map(bridge_set, 5, bridge_entry_field);
  IMap bridge_field = make_prefixed_bridge_field(6);
  IOdeSolver bridge_solver(bridge_field, 30);
  bridge_solver.setAbsoluteTolerance(kSolverTolerance);
  bridge_solver.setRelativeTolerance(kSolverTolerance);
  ITimeMap bridge_time_map(bridge_solver);
  const IVector bridge_entry_full = static_cast<IVector>(bridge_set);
  const interval lambda_center = bridge_entry_full[6].mid();
  const interval bridge_end =
      bridge_set.getCurrentTime() + lambda_center + interval(2.0);
  bridge_time_map.stopAfterStep(true);
  interval minimum_primary_squared(1000000.0);
  do {
    bridge_time_map(bridge_end, bridge_set);
    const IVector enclosure = bridge_set.getLastEnclosure();
    const interval half_binary =
        exp(log(interval(9.0)) / interval(3.0)) * sqr(enclosure[6]) /
        interval(2.0);
    const interval plus_squared =
        sqr(enclosure[7] + half_binary) + sqr(enclosure[8]);
    const interval minus_squared =
        sqr(enclosure[7] - half_binary) + sqr(enclosure[8]);
    const interval step_minimum(
        std::min(plus_squared.leftBound(), minus_squared.leftBound()),
        std::min(plus_squared.rightBound(), minus_squared.rightBound()));
    minimum_primary_squared = interval(
        std::min(minimum_primary_squared.leftBound(),
                 step_minimum.leftBound()),
        std::min(minimum_primary_squared.rightBound(),
                 step_minimum.rightBound()));
    if (!(plus_squared.leftBound() > 0.001 &&
          minus_squared.leftBound() > 0.001)) {
      throw std::runtime_error(
          "common-clock escape bridge approached a primary");
    }
  } while (!bridge_time_map.completed());
  const IVector bridge_exit_full = static_cast<IVector>(bridge_set);
  IVector bridge_exit(5);
  for (int index = 0; index < 5; ++index) {
    bridge_exit[index] = bridge_exit_full[index + 6];
  }
  const interval outer_radius =
      sqrt(sqr(bridge_exit[1]) + sqr(bridge_exit[2]));
  const interval radial_clock_speed =
      (bridge_exit[1] * bridge_exit[3] +
       bridge_exit[2] * bridge_exit[4]) /
      outer_radius;
  const interval physical_outward_speed = -radial_clock_speed;
  const interval binary_scale =
      exp(log(interval(9.0)) / interval(3.0));
  const interval inner_separation =
      binary_scale * sqr(bridge_exit[0]);
  const interval half_binary = inner_separation / interval(2.0);
  const interval clearance = outer_radius - half_binary;
  const interval binary_boundary_speed =
      binary_scale / (interval(3.0) * (-bridge_exit[0]));
  const interval escape_margin =
      physical_outward_speed -
      interval(2.0) / (interval(2.0) * clearance) -
      interval(2.0) - binary_boundary_speed;
  const interval outer_clearance =
      outer_radius - inner_separation;
  const interval binary_envelope_speed =
      sqrt(interval(4.0) / inner_separation +
           interval(2.0) / interval(100.0));
  const interval finite_mass_margin =
      physical_outward_speed -
      interval(2.0) / (interval(1.5) * outer_clearance) -
      binary_envelope_speed - interval(1.5);
  if (!(bridge_exit[0].leftBound() > -2.1 &&
        bridge_exit[0].rightBound() < -1.9 &&
        clearance.leftBound() > 10.0 &&
        outer_clearance.leftBound() > 10.0 &&
        escape_margin.leftBound() > 0.0 &&
        finite_mass_margin.leftBound() > 0.0)) {
    throw std::runtime_error(
        "common-clock escape tile failed its terminal cone");
  }
  return {first_focus, separated_section, bridge_exit,
          first_focus_selected_norm, minimum_primary_squared,
          escape_margin, finite_mass_margin};
}

struct CommonClockCoverSummary {
  int tile_count;
  double maximum_first_focus_beta;
  double minimum_first_focus_selected_norm;
  double minimum_third_focus_alpha_gap;
  double minimum_primary_squared;
  double minimum_escape_margin;
  double minimum_finite_mass_margin;
};

CommonClockCoverSummary evaluate_fourth_common_clock_escape_cover() {
  CommonClockCoverSummary summary{
      0, -1000000.0, 1000000.0, 1000000.0,
      1000000.0, 1000000.0, 1000000.0};
  const interval third_focus_alpha =
      interval(3.0) * acos(interval(-1.0));
  const auto evaluate_tile = [&](int offset_pico, int radius_pico) {
    const interval center =
        interval(1264009098895.0 +
                 static_cast<double>(offset_pico)) /
        interval(1000000000000.0);
    const interval radius =
        interval(static_cast<double>(radius_pico)) /
        interval(1000000000000.0);
    const CommonClockEscapeEvaluation result =
        evaluate_fourth_common_clock_escape(center + symmetric(radius));
    ++summary.tile_count;
    summary.maximum_first_focus_beta =
        std::max(summary.maximum_first_focus_beta,
                 result.first_focus[1].rightBound());
    summary.minimum_first_focus_selected_norm =
        std::min(summary.minimum_first_focus_selected_norm,
                 result.first_focus_selected_norm.leftBound());
    summary.minimum_third_focus_alpha_gap =
        std::min(summary.minimum_third_focus_alpha_gap,
                 third_focus_alpha.leftBound() -
                     result.separated_section[0].rightBound());
    summary.minimum_primary_squared =
        std::min(summary.minimum_primary_squared,
                 result.minimum_primary_squared.leftBound());
    summary.minimum_escape_margin =
        std::min(summary.minimum_escape_margin,
                 result.escape_margin.leftBound());
    summary.minimum_finite_mass_margin =
        std::min(summary.minimum_finite_mass_margin,
                 result.finite_mass_margin.leftBound());
  };
  for (int offset = 120; offset <= 198; offset += 2) {
    evaluate_tile(offset, 1);
  }
  for (int offset = 200; offset <= 560; offset += 4) {
    evaluate_tile(offset, 2);
  }
  return summary;
}

CorrelatedFifthEvaluation evaluate_direct_fourth_collision_two_centre_probe(
    const interval& two_centre_duration, bool restrict_collision_phase,
    int phase_offset_micro, int phase_radius_micro,
    bool use_cached_multiprecision_root = false,
    int phase_scale = 1000000) {
  IVector collision = use_cached_multiprecision_root
                          ? cached_multiprecision_fourth_collision_lc_state()
                          : certified_fourth_collision_lc_state();
  if (restrict_collision_phase) {
    const interval phase_center =
        interval(static_cast<double>(phase_offset_micro)) /
        interval(static_cast<double>(phase_scale));
    const interval phase_radius =
        interval(static_cast<double>(phase_radius_micro)) /
        interval(static_cast<double>(phase_scale));
    interval restricted_phase;
    if (!intersection(collision[3],
                      phase_center + symmetric(phase_radius),
                      restricted_phase)) {
      throw std::runtime_error(
          "collision-phase tile misses the certified fourth-root box");
    }
    collision[3] = restricted_phase;
    collision[2] =
        sqrt(interval(1.0) / interval(2.0) - sqr(collision[3]));
  }
  const interval scale = exp(log(interval(9.0)) / interval(3.0));
  const interval radius =
      scale * exp(interval(2.0) * log(collision[5]) / interval(3.0));
  IVector entry(6);
  entry[0] = acos(interval(-1.0));
  entry[1] = interval(0.0);
  entry[2] = -interval(2.0) * collision[2] / interval(3.0);
  entry[3] = -interval(2.0) * collision[3] / interval(3.0);
  entry[4] = radius * collision[4] / interval(9.0) -
             interval(5.0) / interval(36.0);
  entry[5] = log(collision[5]);
  C0Rect2Set active(entry);
  IMap field = make_prefixed_two_centre_xi_field(0);
  const auto certify_monotone_alpha =
      [](const C0Rect2Set& initial_set, const interval& return_time,
         const char* label) {
        C0Rect2Set audit_set = initial_set;
        IMap audit_field = make_prefixed_two_centre_xi_field(0);
        IOdeSolver audit_solver(audit_field, 30);
        audit_solver.setAbsoluteTolerance(kSolverTolerance);
        audit_solver.setRelativeTolerance(kSolverTolerance);
        ITimeMap audit_time_map(audit_solver);
        const interval audit_end =
            audit_set.getCurrentTime() + interval(return_time.rightBound());
        audit_time_map.stopAfterStep(true);
        do {
          audit_time_map(audit_end, audit_set);
          const IVector enclosure = audit_set.getLastEnclosure();
          if (!(enclosure[2].rightBound() < 0.0)) {
            throw std::runtime_error(
                std::string(label) +
                " lost strict alpha monotonicity before its focus");
          }
        } while (!audit_time_map.completed());
      };
  C0Rect2Set focus_set = active;
  const C0Rect2Set focus_audit_set = focus_set;
  IOdeSolver focus_solver(field, 30);
  focus_solver.setAbsoluteTolerance(kSolverTolerance);
  focus_solver.setRelativeTolerance(kSolverTolerance);
  const interval focus_alpha = interval(2.0) * acos(interval(-1.0));
  ICoordinateSection focus_section(6, 0, focus_alpha);
  IPoincareMap focus_poincare(focus_solver, focus_section,
                              capd::poincare::MinusPlus);
  focus_poincare.setMaxReturnTime(10.0);
  interval focus_return_time;
  const IVector focus = focus_poincare(focus_set, focus_return_time);
  certify_monotone_alpha(focus_audit_set, focus_return_time, "fifth focus");
  const interval focus_sinh_half =
      (exp(focus[1] / interval(2.0)) -
       exp(-focus[1] / interval(2.0))) /
      interval(2.0);
  const interval focus_selected_norm = sqr(focus_sinh_half);
  C0Rect2Set sixth_focus_set(focus);
  const C0Rect2Set sixth_focus_audit_set = sixth_focus_set;
  IOdeSolver sixth_focus_solver(field, 30);
  sixth_focus_solver.setAbsoluteTolerance(kSolverTolerance);
  sixth_focus_solver.setRelativeTolerance(kSolverTolerance);
  const interval sixth_focus_alpha =
      interval(3.0) * acos(interval(-1.0));
  ICoordinateSection sixth_focus_section(6, 0, sixth_focus_alpha);
  IPoincareMap sixth_focus_poincare(
      sixth_focus_solver, sixth_focus_section, capd::poincare::MinusPlus);
  sixth_focus_poincare.setMaxReturnTime(10.0);
  interval sixth_focus_return_time;
  const IVector sixth_focus =
      sixth_focus_poincare(sixth_focus_set, sixth_focus_return_time);
  certify_monotone_alpha(
      sixth_focus_audit_set, sixth_focus_return_time, "sixth focus");
  const interval sixth_focus_sinh_half =
      (exp(sixth_focus[1] / interval(2.0)) -
       exp(-sixth_focus[1] / interval(2.0))) /
      interval(2.0);
  const interval sixth_focus_selected_norm = sqr(sixth_focus_sinh_half);
  std::cerr << std::hexfloat
            << "SIXTH_FOCUS_DATA state=" << sixth_focus
            << " selected_norm=" << sixth_focus_selected_norm
            << " return_time=" << sixth_focus_return_time << "\n";
  C0Rect2Set seventh_focus_set(sixth_focus);
  const C0Rect2Set seventh_focus_audit_set = seventh_focus_set;
  IOdeSolver seventh_focus_solver(field, 30);
  seventh_focus_solver.setAbsoluteTolerance(kSolverTolerance);
  seventh_focus_solver.setRelativeTolerance(kSolverTolerance);
  const interval seventh_focus_alpha =
      interval(4.0) * acos(interval(-1.0));
  ICoordinateSection seventh_focus_section(6, 0, seventh_focus_alpha);
  IPoincareMap seventh_focus_poincare(
      seventh_focus_solver, seventh_focus_section, capd::poincare::MinusPlus);
  seventh_focus_poincare.setMaxReturnTime(10.0);
  interval seventh_focus_return_time;
  const IVector seventh_focus =
      seventh_focus_poincare(seventh_focus_set, seventh_focus_return_time);
  certify_monotone_alpha(
      seventh_focus_audit_set, seventh_focus_return_time, "seventh focus");
  const interval seventh_focus_sinh_half =
      (exp(seventh_focus[1] / interval(2.0)) -
       exp(-seventh_focus[1] / interval(2.0))) /
      interval(2.0);
  const interval seventh_focus_selected_norm =
      sqr(seventh_focus_sinh_half);
  std::cerr << std::hexfloat
            << "SEVENTH_FOCUS_DATA state=" << seventh_focus
            << " selected_norm=" << seventh_focus_selected_norm
            << " return_time=" << seventh_focus_return_time << "\n";
  IVector exit(6);
  if (two_centre_duration.leftBound() > 10.0) {
    exit = seventh_focus;
    IMap bridge_entry_field = make_two_centre_xi_bridge_entry_field();
    C0Rect2Set bridge_set =
        append_coordinate_map(seventh_focus_set, 5, bridge_entry_field);
    const IVector bridge_entry_full = static_cast<IVector>(bridge_set);
    IVector bridge_entry(5);
    for (int index = 0; index < 5; ++index) {
      bridge_entry[index] = bridge_entry_full[index + 6];
    }
    IMap bridge_field = make_prefixed_bridge_field(6);
    IOdeSolver bridge_solver(bridge_field, 30);
    bridge_solver.setAbsoluteTolerance(kSolverTolerance);
    bridge_solver.setRelativeTolerance(kSolverTolerance);
    ITimeMap bridge_time_map(bridge_solver);
    const interval lambda_center = bridge_entry[0].mid();
    const interval bridge_end =
        bridge_set.getCurrentTime() + lambda_center + interval(2.0);
    bridge_time_map.stopAfterStep(true);
    interval minimum_primary_squared(1000000.0);
    do {
      bridge_time_map(bridge_end, bridge_set);
      const IVector enclosure = bridge_set.getLastEnclosure();
      const interval half_binary =
          exp(log(interval(9.0)) / interval(3.0)) * sqr(enclosure[6]) /
          interval(2.0);
      const interval plus_squared =
          sqr(enclosure[7] + half_binary) + sqr(enclosure[8]);
      const interval minus_squared =
          sqr(enclosure[7] - half_binary) + sqr(enclosure[8]);
      const interval step_minimum(
          std::min(plus_squared.leftBound(), minus_squared.leftBound()),
          std::min(plus_squared.rightBound(), minus_squared.rightBound()));
      minimum_primary_squared = interval(
          std::min(minimum_primary_squared.leftBound(),
                   step_minimum.leftBound()),
          std::min(minimum_primary_squared.rightBound(),
                   step_minimum.rightBound()));
      if (!(plus_squared.leftBound() > 1e-8 &&
            minus_squared.leftBound() > 1e-8)) {
        throw std::runtime_error(
            "two-centre exit bridge lost primary separation");
      }
    } while (!bridge_time_map.completed());
    const IVector bridge_exit_full = static_cast<IVector>(bridge_set);
    IVector bridge_exit(5);
    for (int index = 0; index < 5; ++index) {
      bridge_exit[index] = bridge_exit_full[index + 6];
    }
    const interval outer_radius =
        sqrt(sqr(bridge_exit[1]) + sqr(bridge_exit[2]));
    const interval radial_clock_speed =
        (bridge_exit[1] * bridge_exit[3] +
         bridge_exit[2] * bridge_exit[4]) /
        outer_radius;
    const interval physical_outward_speed = -radial_clock_speed;
    const interval binary_scale =
        exp(log(interval(9.0)) / interval(3.0));
    const interval half_binary =
        binary_scale * sqr(bridge_exit[0]) / interval(2.0);
    const interval clearance = outer_radius - half_binary;
    const interval binary_boundary_speed =
        binary_scale / (interval(3.0) * (-bridge_exit[0]));
    const interval comparison_speed(2.0);
    const interval escape_margin =
        physical_outward_speed -
        interval(2.0) / (comparison_speed * clearance) -
        comparison_speed - binary_boundary_speed;
    const interval inner_separation =
        binary_scale * sqr(bridge_exit[0]);
    const interval outer_clearance = outer_radius - inner_separation;
    const interval binary_envelope_speed =
        sqrt(interval(4.0) / inner_separation + interval(2.0) / interval(100.0));
    const interval finite_mass_margin =
        physical_outward_speed -
        interval(2.0) / (interval(1.5) * outer_clearance) -
        binary_envelope_speed - interval(1.5);
    if (!(focus_selected_norm.leftBound() > 0.0 &&
          sixth_focus_selected_norm.leftBound() > 0.0 &&
          seventh_focus_selected_norm.leftBound() > 0.01 &&
          minimum_primary_squared.leftBound() > 0.001 &&
          bridge_exit[0].leftBound() > -2.1 &&
          bridge_exit[0].rightBound() < -1.9 &&
          clearance.leftBound() > 10.0 &&
          physical_outward_speed.leftBound() > 2.5 &&
          escape_margin.leftBound() > 0.0 &&
          outer_clearance.leftBound() > 10.0 &&
          finite_mass_margin.leftBound() > 0.0)) {
      throw std::runtime_error(
          "two-centre collision-ejection branch failed terminal escape");
    }
    std::cerr << std::hexfloat
              << "TWO_CENTRE_BRIDGE_DATA entry=" << bridge_entry
              << " exit=" << bridge_exit
              << " minimum_primary_squared=" << minimum_primary_squared
              << " escape_margin=" << escape_margin
              << " finite_mass_margin=" << finite_mass_margin << "\n";
    std::cout << "PASS_FOURTH_TWO_CENTRE_ESCAPE "
                 "method=CAPD-6.1.0-native "
                 "stage=regularized-fourth-collision-ejection-to-escape\n";
  } else {
    propagate_relative_time(active, field, two_centre_duration);
    exit = static_cast<IVector>(active);
  }
  const interval alpha = exit[0];
  const interval beta = exit[1];
  const interval exp_half = exp(beta / interval(2.0));
  const interval exp_minus_half = exp(-beta / interval(2.0));
  const interval cosh_half =
      (exp_half + exp_minus_half) / interval(2.0);
  const interval sinh_half =
      (exp_half - exp_minus_half) / interval(2.0);
  const interval sr = sin(alpha / interval(2.0)) * cosh_half;
  const interval si = cos(alpha / interval(2.0)) * sinh_half;
  const interval cr = cos(alpha / interval(2.0)) * cosh_half;
  const interval ci = -sin(alpha / interval(2.0)) * sinh_half;
  const interval s_norm = sqr(sr) + sqr(si);
  const interval c_norm = sqr(cr) + sqr(ci);
  const interval metric = s_norm * c_norm;
  const interval zr =
      (sqr(cr) - sqr(ci) - sqr(sr) + sqr(si)) / interval(2.0);
  const interval zi = cr * ci - sr * si;
  const interval energy_constraint =
      sqr(exit[2]) + sqr(exit[3]) -
      interval(2.0) * metric * exit[4] -
      interval(2.0) / interval(9.0) *
          (metric * (sqr(zr) + sqr(zi)) + s_norm + c_norm);
  return {collision,
          focus,
          entry,
          exit,
          interval(0.0),
          interval(0.0),
          focus_selected_norm,
          interval(0.0),
          -focus[2],
          focus_return_time,
          interval(0.0),
          interval(0.0),
          energy_constraint};
}

CorrelatedFifthEvaluation evaluate_fourth_collision_terminal_probe(
    const interval& fifth_section_value,
    const interval& two_centre_duration) {
  C0Rect2Set active(certified_fourth_collision_lc_state());
  IMap negative_field = make_other_pair_lc_field();
  propagate_relative_time(active, negative_field,
                          interval(107.0) / interval(250.0));
  const IVector negative_exit = static_cast<IVector>(active);
  const interval negative_norm =
      sqr(negative_exit[0]) + sqr(negative_exit[1]);
  if (!(negative_norm.leftBound() > 0.01 &&
        negative_exit[5].leftBound() > 0.1)) {
    throw std::runtime_error(
        "fourth collision ejection did not reach the fifth switch");
  }

  IMap positive_entry_map = make_positive_pair_entry_map();
  apply_same_dimension_map(active, positive_entry_map);
  const IVector fifth_entry = static_cast<IVector>(active);
  const C0Rect2Set fifth_entry_set = active;
  IMap positive_field = make_positive_pair_lc_field();
  IOdeSolver fifth_solver(positive_field, 30);
  fifth_solver.setAbsoluteTolerance(kSolverTolerance);
  fifth_solver.setRelativeTolerance(kSolverTolerance);
  ICoordinateSection fifth_section(6, 1, fifth_section_value);
  IPoincareMap fifth_poincare(fifth_solver, fifth_section,
                              capd::poincare::MinusPlus);
  fifth_poincare.setMaxReturnTime(2.0);
  interval fifth_return_time;
  const IVector fifth_exit = fifth_poincare(active, fifth_return_time);
  const interval fifth_exit_selected_norm =
      sqr(fifth_exit[0]) + sqr(fifth_exit[1]);
  const interval scale = exp(log(interval(9.0)) / interval(3.0));
  const interval fifth_separation =
      scale * exp(interval(2.0) * log(fifth_exit[5]) / interval(3.0));
  const interval fifth_qx = sqr(fifth_exit[0]) - sqr(fifth_exit[1]);
  const interval fifth_qy = interval(2.0) * fifth_exit[0] * fifth_exit[1];
  const interval fifth_exit_other_squared =
      sqr(fifth_qx + fifth_separation) + sqr(fifth_qy);

  active = fifth_entry_set;
  const interval projection_margin = interval(1.0) / interval(256.0);
  const interval fixed_leg = fifth_return_time.left() - projection_margin -
                             active.getCurrentTime();
  propagate_relative_time(active, positive_field, fixed_leg);
  const IVector before_projection = static_cast<IVector>(active);
  if (!(before_projection[1] < fifth_section_value) ||
      !(before_projection[3] < 0.0)) {
    throw std::runtime_error(
        "root-anchored fixed leg missed the outgoing projection tube");
  }
  IMap section_delta_field =
      make_prefixed_positive_section_delta_field(0);
  section_delta_field.setParameter("C", fifth_section_value);
  active = append_coordinate_map(active, 1, section_delta_field);
  IMap section_projection_field =
      make_prefixed_positive_section_projection_field(0);
  propagate_relative_time(active, section_projection_field, interval(1.0),
                          0.02);
  const IVector projected_section = static_cast<IVector>(active);
  if (!projected_section[1].contains(fifth_section_value) ||
      projected_section[3].contains(0.0)) {
    throw std::runtime_error(
        "root-anchored section projection failed transversality");
  }

  IMap two_centre_entry_field =
      make_prefixed_two_centre_s_entry_field(0, true);
  active = append_coordinate_map(active, 6, two_centre_entry_field);
  IMap s_to_xi_map = make_prefixed_two_centre_s_to_xi_map(7);
  apply_same_dimension_map(active, s_to_xi_map);
  const IVector entry_full = static_cast<IVector>(active);
  IVector two_centre_entry(6);
  for (int index = 0; index < 6; ++index) {
    two_centre_entry[index] = entry_full[index + 7];
  }
  IMap two_centre_xi_field = make_prefixed_two_centre_xi_field(7);
  propagate_relative_time(active, two_centre_xi_field,
                          two_centre_duration);
  const IVector exit_full = static_cast<IVector>(active);
  IVector two_centre_exit(6);
  for (int index = 0; index < 6; ++index) {
    two_centre_exit[index] = exit_full[index + 7];
  }

  const interval alpha = two_centre_exit[0];
  const interval beta = two_centre_exit[1];
  const interval exp_half = exp(beta / interval(2.0));
  const interval exp_minus_half = exp(-beta / interval(2.0));
  const interval cosh_half =
      (exp_half + exp_minus_half) / interval(2.0);
  const interval sinh_half =
      (exp_half - exp_minus_half) / interval(2.0);
  const interval sr = sin(alpha / interval(2.0)) * cosh_half;
  const interval si = cos(alpha / interval(2.0)) * sinh_half;
  const interval cr = cos(alpha / interval(2.0)) * cosh_half;
  const interval ci = -sin(alpha / interval(2.0)) * sinh_half;
  const interval pr = two_centre_exit[2];
  const interval pi = two_centre_exit[3];
  const interval energy = two_centre_exit[4];
  const interval s_norm = sqr(sr) + sqr(si);
  const interval c_norm = sqr(cr) + sqr(ci);
  const interval metric = s_norm * c_norm;
  const interval zr =
      (sqr(cr) - sqr(ci) - sqr(sr) + sqr(si)) / interval(2.0);
  const interval zi = cr * ci - sr * si;
  const interval energy_constraint =
      sqr(pr) + sqr(pi) - interval(2.0) * metric * energy -
      interval(2.0) / interval(9.0) *
          (metric * (sqr(zr) + sqr(zi)) + s_norm + c_norm);
  return {fifth_entry,
          fifth_exit,
          two_centre_entry,
          two_centre_exit,
          interval(0.0),
          interval(0.0),
          fifth_exit_selected_norm,
          fifth_exit_other_squared,
          -fifth_exit[3],
          fifth_return_time,
          interval(0.0),
          interval(0.0),
          energy_constraint};
}

CorrelatedFifthEvaluation evaluate_fully_correlated_fifth_section_probe(
    const interval& kappa, const interval& fifth_section_value,
    const interval& two_centre_duration = interval(0.0)) {
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
  const C0Rect2Set fifth_entry_set = active;
  IOdeSolver fifth_solver(positive_field, 30);
  fifth_solver.setAbsoluteTolerance(kSolverTolerance);
  fifth_solver.setRelativeTolerance(kSolverTolerance);
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

  IVector two_centre_entry(6);
  IVector two_centre_exit(6);
  for (int index = 0; index < 6; ++index) {
    two_centre_entry[index] = interval(0.0);
  }
  for (int index = 0; index < 6; ++index) {
    two_centre_exit[index] = interval(0.0);
  }
  interval two_centre_shape_real_constraint(0.0);
  interval two_centre_shape_imag_constraint(0.0);
  interval two_centre_energy_constraint(0.0);
  if (two_centre_duration.rightBound() > 0.0) {
    active = fifth_entry_set;
    const interval projection_margin = interval(1.0) / interval(256.0);
    const interval fixed_leg = fifth_return_time.left() - projection_margin -
                               active.getCurrentTime();
    propagate_relative_time(active, positive_field, fixed_leg);
    const IVector before_projection = static_cast<IVector>(active);
    if (!(before_projection[25] < fifth_section_value) ||
        !(before_projection[27] < 0.0)) {
      throw std::runtime_error(
          "fixed fifth leg did not reach the outgoing projection tube");
    }
    IMap section_delta_field =
        make_prefixed_positive_section_delta_field(24);
    section_delta_field.setParameter("C", fifth_section_value);
    active = append_coordinate_map(active, 1, section_delta_field);
    IMap section_projection_field =
        make_prefixed_positive_section_projection_field(24);
    propagate_relative_time(active, section_projection_field, interval(1.0),
                            0.02);
    const IVector projected_section = static_cast<IVector>(active);
    if (!projected_section[25].contains(fifth_section_value)) {
      throw std::runtime_error(
          "correlated section projection missed the fifth section");
    }
    if (projected_section[27].contains(0.0)) {
      throw std::runtime_error(
          "correlated section projection lost transversality");
    }
    IMap two_centre_entry_field =
        make_prefixed_two_centre_s_entry_field(24, true);
    active = append_coordinate_map(active, 6, two_centre_entry_field);
    IMap s_to_xi_map = make_prefixed_two_centre_s_to_xi_map(31);
    apply_same_dimension_map(active, s_to_xi_map);
    const IVector two_centre_entry_full = static_cast<IVector>(active);
    for (int index = 0; index < 6; ++index) {
      two_centre_entry[index] = two_centre_entry_full[index + 31];
    }
    IMap two_centre_xi_field = make_prefixed_two_centre_xi_field(31);
    propagate_relative_time(active, two_centre_xi_field,
                            two_centre_duration);
    const IVector two_centre_exit_full = static_cast<IVector>(active);
    for (int index = 0; index < 6; ++index) {
      two_centre_exit[index] = two_centre_exit_full[index + 31];
    }
    const interval alpha = two_centre_exit[0];
    const interval beta = two_centre_exit[1];
    const interval exp_half = exp(beta / interval(2.0));
    const interval exp_minus_half = exp(-beta / interval(2.0));
    const interval cosh_half =
        (exp_half + exp_minus_half) / interval(2.0);
    const interval sinh_half =
        (exp_half - exp_minus_half) / interval(2.0);
    const interval sr = sin(alpha / interval(2.0)) * cosh_half;
    const interval si = cos(alpha / interval(2.0)) * sinh_half;
    const interval cr = cos(alpha / interval(2.0)) * cosh_half;
    const interval ci = -sin(alpha / interval(2.0)) * sinh_half;
    const interval pr = two_centre_exit[2];
    const interval pi = two_centre_exit[3];
    const interval energy = two_centre_exit[4];
    const interval s_norm = sqr(sr) + sqr(si);
    const interval c_norm = sqr(cr) + sqr(ci);
    const interval metric = s_norm * c_norm;
    const interval zr =
        (sqr(cr) - sqr(ci) - sqr(sr) + sqr(si)) / interval(2.0);
    const interval zi = cr * ci - sr * si;
    two_centre_shape_real_constraint = interval(0.0);
    two_centre_shape_imag_constraint = interval(0.0);
    two_centre_energy_constraint =
        sqr(pr) + sqr(pi) - interval(2.0) * metric * energy -
        interval(2.0) / interval(9.0) *
            (metric * (sqr(zr) + sqr(zi)) + s_norm + c_norm);
  }

  return {fifth_entry,
          fifth_exit,
          two_centre_entry,
          two_centre_exit,
          interval(0.0),
          interval(0.0),
          fifth_exit_selected_norm,
          fifth_exit_other_squared,
          -fifth_exit[3],
          fifth_return_time,
          two_centre_shape_real_constraint,
          two_centre_shape_imag_constraint,
          two_centre_energy_constraint};
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
  negative_solver.setAbsoluteTolerance(kSolverTolerance);
  negative_solver.setRelativeTolerance(kSolverTolerance);
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
  entry_solver.setAbsoluteTolerance(kSolverTolerance);
  entry_solver.setRelativeTolerance(kSolverTolerance);
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
  fifth_solver.setAbsoluteTolerance(kSolverTolerance);
  fifth_solver.setRelativeTolerance(kSolverTolerance);
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
          IVector(1),
          IVector(1),
          minimum_fourth_other_squared,
          minimum_fifth_other_squared,
          fifth_exit_selected_norm,
          fifth_exit_other_squared,
          fifth_section_derivative,
          fifth_return_time,
          interval(0.0),
          interval(0.0),
          interval(0.0)};
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
  fourth_solver.setAbsoluteTolerance(kSolverTolerance);
  fourth_solver.setRelativeTolerance(kSolverTolerance);
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
  fifth_solver.setAbsoluteTolerance(kSolverTolerance);
  fifth_solver.setRelativeTolerance(kSolverTolerance);
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
  bridge_solver.setAbsoluteTolerance(kSolverTolerance);
  bridge_solver.setRelativeTolerance(kSolverTolerance);
  ITimeMap bridge_time_map(bridge_solver);
  const interval lambda_center =
      (interval(bridge_initial[0].leftBound()) +
       interval(bridge_initial[0].rightBound())) /
      interval(2.0);
  const interval bridge_end = lambda_center + interval(2.0);
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
#ifdef BURRAU_CAPD_MULTIPRECISION
  capd::MpFloat::setDefaultPrecision(200);
#endif
  std::cout << std::setprecision(18);
  std::cerr << std::setprecision(18);
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
    bool fourth_root_octic_only = false;
    bool fourth_fifth_entry_only = false;
    bool fourth_fifth_outgoing_only = false;
    bool fourth_outgoing_probe = false;
    bool fourth_correlated_probe = false;
    bool fourth_correlated_section_probe = false;
    bool fourth_correlated_section_tile = false;
    bool fourth_common_clock_focus_tile = false;
    bool fourth_common_clock_escape_tile = false;
    bool fourth_common_clock_escape_cover = false;
    bool fourth_two_centre_probe = false;
    bool fourth_two_centre_cached_probe = false;
    int second_probe_offset = 0;
    int second_probe_radius = 0;
    int second_fourth_duration_million = 0;
    int second_fourth_duration_radius_million = 0;
    int second_fifth_duration_million = 0;
    int correlated_offset_pico = 0;
    int correlated_radius_pico = 395;
    int two_centre_duration_million = 0;
    int two_centre_focus_count = 0;
    int collision_phase_scale = 1000000;
    if (argc == 2 && std::string(argv[1]) == "--second-root") {
      second_root_only = true;
    } else if (argc == 2 && std::string(argv[1]) == "--second-escape") {
      second_escape_only = true;
    } else if (argc == 2 &&
               std::string(argv[1]) == "--second-escape-wide") {
      second_escape_wide = true;
    } else if (argc == 2 && std::string(argv[1]) == "--fourth-root") {
      fourth_root_only = true;
    } else if (argc == 2 &&
               std::string(argv[1]) == "--fourth-root-octic") {
      fourth_root_octic_only = true;
    } else if (argc == 2 &&
               std::string(argv[1]) ==
                   "--fourth-common-clock-escape-cover") {
      fourth_common_clock_escape_cover = true;
    } else if (argc == 2 &&
               std::string(argv[1]) == "--fourth-two-centre-terminal") {
      fourth_correlated_section_probe = true;
      fourth_two_centre_probe = true;
      fourth_two_centre_cached_probe = true;
      second_fifth_duration_million = 50000;
      two_centre_duration_million = 11000000;
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
    } else if (argc == 3 &&
               std::string(argv[1]) == "--fourth-two-centre-probe") {
      fourth_correlated_section_probe = true;
      fourth_two_centre_probe = true;
      second_fifth_duration_million = 50000;
      two_centre_duration_million = parse_integer(argv[2]);
    } else if (argc == 3 &&
               std::string(argv[1]) ==
                   "--fourth-two-centre-cached-probe") {
      fourth_correlated_section_probe = true;
      fourth_two_centre_probe = true;
      fourth_two_centre_cached_probe = true;
      second_fifth_duration_million = 50000;
      two_centre_duration_million = parse_integer(argv[2]);
    } else if (argc == 5 &&
               std::string(argv[1]) == "--fourth-correlated-section-tile") {
      fourth_correlated_section_probe = true;
      fourth_correlated_section_tile = true;
      correlated_offset_pico = parse_integer(argv[2]);
      correlated_radius_pico = parse_integer(argv[3]);
      second_fifth_duration_million = parse_integer(argv[4]);
    } else if (argc == 5 &&
               std::string(argv[1]) == "--fourth-common-clock-focus-tile") {
      fourth_common_clock_focus_tile = true;
      correlated_offset_pico = parse_integer(argv[2]);
      correlated_radius_pico = parse_integer(argv[3]);
      two_centre_focus_count = parse_integer(argv[4]);
    } else if (argc == 4 &&
               std::string(argv[1]) == "--fourth-common-clock-escape-tile") {
      fourth_common_clock_escape_tile = true;
      correlated_offset_pico = parse_integer(argv[2]);
      correlated_radius_pico = parse_integer(argv[3]);
    } else if (argc == 5 &&
               std::string(argv[1]) == "--fourth-two-centre-tile") {
      fourth_correlated_section_probe = true;
      fourth_correlated_section_tile = true;
      fourth_two_centre_probe = true;
      correlated_offset_pico = parse_integer(argv[2]);
      correlated_radius_pico = parse_integer(argv[3]);
      second_fifth_duration_million = 50000;
      two_centre_duration_million = parse_integer(argv[4]);
    } else if (argc == 5 &&
               std::string(argv[1]) ==
                   "--fourth-two-centre-phase-nano") {
      fourth_correlated_section_probe = true;
      fourth_correlated_section_tile = true;
      fourth_two_centre_probe = true;
      fourth_two_centre_cached_probe = true;
      correlated_offset_pico = parse_integer(argv[2]);
      correlated_radius_pico = parse_integer(argv[3]);
      second_fifth_duration_million = 50000;
      two_centre_duration_million = parse_integer(argv[4]);
      collision_phase_scale = 1000000000;
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
                   "--fourth-root-octic | "
                   "--fourth-two-centre-terminal | "
                   "--fourth-fifth-entry | "
                   "--fourth-fifth-outgoing | "
                   "--fourth-correlated-probe FIFTH_DURATION_MILLION | "
                   "--fourth-correlated-section-probe CI_MILLION | "
                   "--fourth-correlated-section-tile OFFSET_PICO "
                   "RADIUS_PICO CI_MILLION | "
                   "--fourth-common-clock-focus-tile OFFSET_PICO "
                   "RADIUS_PICO FOCUS_COUNT | "
                   "--fourth-common-clock-escape-tile OFFSET_PICO "
                   "RADIUS_PICO | "
                   "--fourth-common-clock-escape-cover | "
                   "--fourth-two-centre-probe DURATION_MILLION | "
                   "--fourth-two-centre-cached-probe DURATION_MILLION | "
                   "--fourth-two-centre-tile OFFSET_PICO RADIUS_PICO "
                   "DURATION_MILLION | "
                   "--fourth-two-centre-phase-nano OFFSET_NANO "
                   "RADIUS_NANO DURATION_MILLION | "
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
    if (fourth_two_centre_probe &&
        (two_centre_duration_million < 1 ||
         two_centre_duration_million > 20000000)) {
      throw std::invalid_argument(
          "two-centre probe duration is outside its safe range");
    }
    if (fourth_correlated_section_tile &&
        (correlated_offset_pico < -1000 || correlated_offset_pico > 1000 ||
         correlated_radius_pico < 1 || correlated_radius_pico > 395)) {
      throw std::invalid_argument(
          "correlated fifth section tile is outside its safe range");
    }
    if (fourth_common_clock_focus_tile &&
        (correlated_offset_pico < -1000 || correlated_offset_pico > 1000 ||
         correlated_radius_pico < 1 || correlated_radius_pico > 395 ||
         two_centre_focus_count < 1 || two_centre_focus_count > 3)) {
      throw std::invalid_argument(
          "common-clock focus tile is outside its safe range");
    }
    if (fourth_common_clock_escape_tile &&
        (correlated_offset_pico < -1000 || correlated_offset_pico > 1000 ||
         correlated_radius_pico < 1 || correlated_radius_pico > 395)) {
      throw std::invalid_argument(
          "common-clock escape tile is outside its safe range");
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
    if (fourth_root_octic_only) {
      const IVector collision = certified_fourth_collision_lc_state();
      std::cout << std::hexfloat
                << "PASS_FOURTH_ROOT_OCTIC method=CAPD-6.1.0"
#ifdef BURRAU_CAPD_MULTIPRECISION
                   "-MPFR-200"
#else
                   "-native"
#endif
                << " collision_state=" << collision << "\n";
      return 0;
    }
    if (fourth_common_clock_escape_cover) {
      const CommonClockCoverSummary summary =
          evaluate_fourth_common_clock_escape_cover();
      if (summary.tile_count != 131 ||
          !(summary.maximum_first_focus_beta < 0.0 &&
            summary.minimum_first_focus_selected_norm > 0.0 &&
            summary.minimum_third_focus_alpha_gap > 0.0 &&
            summary.minimum_primary_squared > 0.001 &&
            summary.minimum_escape_margin > 0.0 &&
            summary.minimum_finite_mass_margin > 0.0)) {
        throw std::runtime_error(
            "common-clock escape cover lost a strict global margin");
      }
      std::cout << std::hexfloat
                << "COMMON_CLOCK_ESCAPE_COVER method=CAPD-6.1.0-native"
                << " kappa_box=[1.264009099014,1.264009099457]"
                << " tile_count=" << summary.tile_count
                << " maximum_first_focus_beta="
                << summary.maximum_first_focus_beta
                << " minimum_first_focus_selected_norm="
                << summary.minimum_first_focus_selected_norm
                << " minimum_third_focus_alpha_gap="
                << summary.minimum_third_focus_alpha_gap
                << " minimum_primary_squared="
                << summary.minimum_primary_squared
                << " minimum_escape_margin="
                << summary.minimum_escape_margin
                << " minimum_finite_mass_margin="
                << summary.minimum_finite_mass_margin << "\n";
      std::cout << "PASS_COMMON_CLOCK_ESCAPE_COVER "
                   "method=CAPD-6.1.0-native "
                   "stage=fourth-adjacent-continuum-cover\n";
      return 0;
    }
    if (fourth_common_clock_focus_tile) {
      const interval kappa_center =
          interval(1264009098895.0 +
                   static_cast<double>(correlated_offset_pico)) /
          interval(1000000000000.0);
      const interval kappa_radius =
          interval(static_cast<double>(correlated_radius_pico)) /
          interval(1000000000000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const CommonClockFocusEvaluation result =
          evaluate_fourth_common_clock_focus(
              kappa_box, two_centre_focus_count);
      std::cout << std::hexfloat
                << "COMMON_CLOCK_FOCUS method=CAPD-6.1.0-native"
                << " kappa_box=" << kappa_box
                << " focus_count=" << two_centre_focus_count
                << " lc_state=" << result.lc_state
                << " entry=" << result.two_centre_entry
                << " focus=" << result.focus
                << " selected_norm=" << result.selected_norm
                << " return_time=" << result.return_time
                << " energy_constraint=" << result.energy_constraint
                << "\n";
      if (!(result.focus[2].rightBound() < 0.0 &&
            result.selected_norm.leftBound() > 0.0 &&
            result.energy_constraint.contains(0.0))) {
        throw std::runtime_error(
            "common-clock focus failed monotonicity, separation, or constraint");
      }
      std::cout << "PASS_COMMON_CLOCK_FOCUS method=CAPD-6.1.0-native "
                   "stage=fourth-neighborhood-two-centre-focus\n";
      return 0;
    }
    if (fourth_common_clock_escape_tile) {
      const interval kappa_center =
          interval(1264009098895.0 +
                   static_cast<double>(correlated_offset_pico)) /
          interval(1000000000000.0);
      const interval kappa_radius =
          interval(static_cast<double>(correlated_radius_pico)) /
          interval(1000000000000.0);
      const interval kappa_box =
          kappa_center + symmetric(kappa_radius);
      const CommonClockEscapeEvaluation result =
          evaluate_fourth_common_clock_escape(kappa_box);
      std::cout << std::hexfloat
                << "COMMON_CLOCK_ESCAPE method=CAPD-6.1.0-native"
                << " kappa_box=" << kappa_box
                << " first_focus=" << result.first_focus
                << " first_focus_selected_norm="
                << result.first_focus_selected_norm
                << " separated_section=" << result.separated_section
                << " bridge_exit=" << result.bridge_exit
                << " minimum_primary_squared="
                << result.minimum_primary_squared
                << " escape_margin=" << result.escape_margin
                << " finite_mass_margin=" << result.finite_mass_margin
                << "\n";
      std::cout << "PASS_COMMON_CLOCK_ESCAPE method=CAPD-6.1.0-native "
                   "stage=fourth-component-interior-terminal-escape\n";
      return 0;
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
                     lower_bound_as_double(
                         result.minimum_negative_chart_other_squared));
        worst_positive_other_squared =
            std::min(worst_positive_other_squared,
                     lower_bound_as_double(
                         result.minimum_positive_chart_other_squared));
        worst_bridge_primary_squared =
            std::min(worst_bridge_primary_squared,
                     lower_bound_as_double(
                         result.minimum_bridge_primary_squared));
        worst_escape_margin =
            std::min(worst_escape_margin,
                     lower_bound_as_double(result.escape_margin));
        worst_finite_mass_margin =
            std::min(worst_finite_mass_margin,
                     lower_bound_as_double(result.finite_mass_margin));
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
      const interval two_centre_duration =
          interval(static_cast<double>(two_centre_duration_million)) /
          interval(1000000.0);
      const double correlated_zeta_start =
          kZetaStart;
      const CorrelatedFifthEvaluation result =
          fourth_two_centre_probe
              ? evaluate_direct_fourth_collision_two_centre_probe(
                    two_centre_duration, fourth_correlated_section_tile,
                    correlated_offset_pico, correlated_radius_pico,
                    fourth_two_centre_cached_probe, collision_phase_scale)
          : fourth_correlated_section_probe
              ? evaluate_fully_correlated_fifth_section_probe(
                    kappa_box, fifth_target, two_centre_duration)
              : evaluate_correlated_fifth_probe(
                    kappa_box, fourth_start_duration, fourth_extra_duration,
                    fifth_target, false, correlated_zeta_start);
      std::cout << std::hexfloat
                << (fourth_fifth_outgoing_only
                        ? "FOURTH_FIFTH_OUTGOING_DATA "
                        : (fourth_two_centre_probe
                               ? "TWO_CENTRE_PROBE "
                        : (fourth_correlated_section_probe
                               ? "CORRELATED_FIFTH_SECTION_PROBE "
                               : "CORRELATED_FIFTH_PROBE ")))
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
      if (fourth_two_centre_probe) {
        std::cout << std::hexfloat
                  << "TWO_CENTRE_DATA duration=" << two_centre_duration
                  << " entry=" << result.two_centre_entry
                  << " exit=" << result.two_centre_exit
                  << " shape_real_constraint="
                  << result.two_centre_shape_real_constraint
                  << " shape_imag_constraint="
                  << result.two_centre_shape_imag_constraint
                  << " energy_constraint="
                  << result.two_centre_energy_constraint << "\n";
      }
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
