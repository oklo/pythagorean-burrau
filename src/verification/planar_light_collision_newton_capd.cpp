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

#include "capd/capdlib.h"

namespace {

using capd::C1Rect2Set;
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

struct Evaluation {
  IVector residual;
  IMatrix jacobian;
  IVector final_state;
};

Evaluation evaluate_box(const interval& kappa, const interval& duration,
                        bool pre_collision_checks = true) {
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

  IMap shape_field = make_combined_shape_field();
  IOdeSolver shape_solver(shape_field, 30);
  shape_solver.setAbsoluteTolerance(1e-15);
  shape_solver.setRelativeTolerance(1e-15);
  ITimeMap shape_time_map(shape_solver);
  const interval shape_end = interval(kZetaStart) - interval(3.0) / interval(10.0);
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
    throw std::runtime_error("shape-to-LC entry crossed the chosen square-root lift");
  }

  IMap entry_field = make_combined_entry_field();
  const interval radial_time = exp(interval(3.0) / interval(10.0));
  const interval binary_scale =
      exp(log(interval(9.0)) / interval(3.0)) * exp(interval(1.0) / interval(5.0));
  const interval velocity_scale =
      exp(log(interval(9.0)) / interval(3.0)) / exp(interval(1.0) / interval(10.0));
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
    const interval other_squared =
        sqr(qx + enclosure[12]) + sqr(qy);
    if (pre_collision_checks) {
      if (!(enclosure[11].leftBound() > 1.0 &&
            enclosure[12].leftBound() > 2.0 &&
            other_squared.leftBound() > 1.0)) {
        throw std::runtime_error("pre-collision LC path left its certified chart");
      }
    } else if (!(enclosure[11].leftBound() > 0.3 &&
                 enclosure[12].leftBound() > 1.0 &&
                 other_squared.leftBound() > 0.01)) {
      throw std::runtime_error("collision-ejection LC path lost separation");
    }
  } while (!lc_time_map.completed());
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
  return {residual, jacobian, state};
}

struct EscapeEvaluation {
  IVector lc_exit;
  IVector bridge_exit;
  interval minimum_primary_squared;
  interval escape_margin;
  interval finite_mass_margin;
};

EscapeEvaluation evaluate_collision_ejection_escape(const interval& kappa) {
  const interval lc_duration = interval(61.0) / interval(25.0);
  const Evaluation lc = evaluate_box(kappa, lc_duration, false);
  const IVector& state = lc.final_state;
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
  C1Rect2Set set(initial);

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

IVector interval_newton(const IVector& center, const IVector& value,
                        const IMatrix& jacobian) {
  return center - capd::matrixAlgorithms::gauss(jacobian, value);
}

}  // namespace

int main() {
  using namespace capd;
  try {
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
    const EscapeEvaluation escape =
        evaluate_collision_ejection_escape(newton[0]);
    std::cout << "ESCAPE_DATA method=CAPD-6.1.0-native"
              << " lc_exit=" << escape.lc_exit
              << " bridge_exit=" << escape.bridge_exit
              << " minimum_primary_squared=" << escape.minimum_primary_squared
              << " escape_margin=" << escape.escape_margin
              << " finite_mass_margin=" << escape.finite_mass_margin << "\n";
    std::cout << "PASS_ROOT method=CAPD-6.1.0-native "
                 "stage=planar-light-collision-interval-newton\n";
    std::cout << "PASS_ESCAPE method=CAPD-6.1.0-native "
                 "stage=planar-light-collision-ejection-escape\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FAIL " << error.what() << "\n";
    return 2;
  }
}
