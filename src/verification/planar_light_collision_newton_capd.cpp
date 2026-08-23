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

namespace {

using capd::C1Rect2Set;
using capd::C0Rect2Set;
using capd::IMap;
using capd::IMatrix;
using capd::IOdeSolver;
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

TailData stable_tail_data(const interval& kappa) {
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
  const interval p = -exp(-interval(kZetaStart) * a_t);
  const interval nu_scale = exp(-interval(kZetaStart) * a_l);
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

  const interval x = p + A * p * nu + B * power(p, 3) + C * p * sqr(nu) +
                     G * power(p, 3) * nu + H * p * power(nu, 3);
  const interval q = nu + K * sqr(p) + D * sqr(nu) + E * sqr(p) * nu +
                     F * power(nu, 3) + I * power(p, 4) +
                     J * sqr(p) * sqr(nu) + L * power(nu, 4);
  const interval vx =
      -a_t * p - (a_t + a_l) * A * p * nu -
      interval(3.0) * a_t * B * power(p, 3) -
      (a_t + interval(2.0) * a_l) * C * p * sqr(nu) -
      (interval(3.0) * a_t + a_l) * G * power(p, 3) * nu -
      (a_t + interval(3.0) * a_l) * H * p * power(nu, 3);
  const interval vq =
      -a_l * nu - interval(2.0) * a_t * K * sqr(p) -
      interval(2.0) * a_l * D * sqr(nu) -
      (interval(2.0) * a_t + a_l) * E * sqr(p) * nu -
      interval(3.0) * a_l * F * power(nu, 3) -
      interval(4.0) * a_t * I * power(p, 4) -
      interval(2.0) * (a_t + a_l) * J * sqr(p) * sqr(nu) -
      interval(4.0) * a_l * L * power(nu, 4);

  const interval dx_dnu =
      A * p + interval(2.0) * C * p * nu + G * power(p, 3) +
      interval(3.0) * H * p * sqr(nu);
  const interval dq_dnu =
      interval(1.0) + interval(2.0) * D * nu + E * sqr(p) +
      interval(3.0) * F * sqr(nu) +
      interval(2.0) * J * sqr(p) * nu +
      interval(4.0) * L * power(nu, 3);
  const interval dvx_dnu =
      -(a_t + a_l) * A * p -
      interval(2.0) * (a_t + interval(2.0) * a_l) * C * p * nu -
      (interval(3.0) * a_t + a_l) * G * power(p, 3) -
      interval(3.0) * (a_t + interval(3.0) * a_l) * H * p * sqr(nu);
  const interval dvq_dnu =
      -a_l - interval(4.0) * a_l * D * nu -
      (interval(2.0) * a_t + a_l) * E * sqr(p) -
      interval(9.0) * a_l * F * sqr(nu) -
      interval(4.0) * (a_t + a_l) * J * sqr(p) * nu -
      interval(16.0) * a_l * L * power(nu, 3);

  const interval p_ratio = interval(400.0) * exp(-interval(kZetaStart) * a_t);
  const interval nu_ratio =
      interval(6500.0) * exp(-interval(kZetaStart) * a_l);
  const double lambda_upper =
      std::max(p_ratio.rightBound(), nu_ratio.rightBound());
  const interval tail_scale = power(interval(lambda_upper), 5);
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

template <typename Set>
void propagate_to_lc_section(Set& set, const interval& duration,
                             bool pre_collision_checks,
                             bool require_selected_separation = false) {
  IMap shape_field = make_combined_shape_field();
  IOdeSolver shape_solver(shape_field, 30);
  shape_solver.setAbsoluteTolerance(1e-15);
  shape_solver.setRelativeTolerance(1e-15);
  ITimeMap shape_time_map(shape_solver);
  const interval shape_end =
      interval(kZetaStart) - interval(3.0) / interval(10.0);
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
                        bool require_selected_separation = false) {
  const TailData tail = stable_tail_data(kappa);
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
                          require_selected_separation);
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
                                         bool stable_entry = false) {
  const Evaluation first =
      evaluate_box(kappa, interval(7.0) / interval(4.0), true, true);
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
    const interval other_squared = sqr(qx - separation) + sqr(qy);
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
    bool stable_entry = false) {
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
        positive_qy.rightBound() < 0.0)) {
    throw std::runtime_error(
        "positive-primary LC switch did not certify its square-root sheet");
  }
  IMap positive_entry_map = make_positive_pair_entry_map();
  const IVector positive_entry = positive_entry_map(negative_exit);
  if (!(positive_entry[0].leftBound() > 0.0 &&
        positive_entry[1].rightBound() < 0.0 &&
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
  C0Rect2Set bridge_set(bridge_initial);

  IMap bridge_field = make_heavy_binary_bridge_field();
  IOdeSolver bridge_solver(bridge_field, 30);
  bridge_solver.setAbsoluteTolerance(1e-15);
  bridge_solver.setRelativeTolerance(1e-15);
  ITimeMap bridge_time_map(bridge_solver);
  const double lambda_center =
      (lambda.leftBound() + lambda.rightBound()) / 2.0;
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
    if (!(plus_squared.leftBound() > 0.01 &&
          minus_squared.leftBound() > 0.01)) {
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
    if (argc == 2 && std::string(argv[1]) == "--second-root") {
      second_root_only = true;
    } else if (argc == 2 && std::string(argv[1]) == "--second-escape") {
      second_escape_only = true;
    } else if (argc == 2 &&
               std::string(argv[1]) == "--second-escape-wide") {
      second_escape_wide = true;
    } else if ((argc == 4 || argc == 5) &&
        std::string(argv[1]) == "--escape-tiles") {
      first_escape_offset = parse_integer(argv[2]);
      escape_tile_count = parse_integer(argv[3]);
      if (argc == 5) {
        escape_tile_radius = parse_integer(argv[4]);
      }
    } else if (argc != 1) {
      std::cerr << "usage: " << argv[0]
                << " [--second-root | --second-escape | "
                   "--second-escape-wide | --escape-tiles FIRST_OFFSET "
                   "COUNT [RADIUS]]\n";
      return 2;
    }
    if (escape_tile_count < 1 || escape_tile_count > 1000 ||
        escape_tile_radius < 1 || escape_tile_radius > 1000) {
      throw std::invalid_argument(
          "tile count and radius must lie in [1,1000]");
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
      for (int offset = -714; offset <= 714; offset += 14) {
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
