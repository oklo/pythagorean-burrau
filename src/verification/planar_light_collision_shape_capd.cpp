// Exploratory validated propagation of the planar stable-tail box.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
//
// This program validates the finite shape leg from zeta=10 to zeta=0.3,
// conversion into one analytic LC chart, and a fixed-duration LC leg.  It is
// not a collision-zero certificate.

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "capd/capdlib.h"

namespace {

using capd::C0Rect2Set;
using capd::IMap;
using capd::IOdeSolver;
using capd::ITimeMap;
using capd::IVector;
using capd::interval;

IMap make_reversed_shape_field() {
  return IMap(
      "var:s,x,y,vx,vy;"
      "fun:1,-vx,-vy,"
      "vx/3-(2*x-(x+1/2)/(((x+1/2)^2+y^2)*sqrt((x+1/2)^2+y^2))"
      "-(x-1/2)/(((x-1/2)^2+y^2)*sqrt((x-1/2)^2+y^2)))/9,"
      "vy/3-(2*y-y/(((x+1/2)^2+y^2)*sqrt((x+1/2)^2+y^2))"
      "-y/(((x-1/2)^2+y^2)*sqrt((x-1/2)^2+y^2)))/9;");
}

IMap make_reversed_lc_field() {
  // s=-sigma increases toward the incoming close encounter.  The selected
  // primary is +R/2 and t is the positive radial clock.
  const std::string qx = "(ur^2-ui^2)";
  const std::string qy = "(2*ur*ui)";
  const std::string squared_distance =
      "((" + qx + "+R)^2+" + qy + "^2)";
  const std::string denominator =
      "(" + squared_distance + "*sqrt(" + squared_distance + "))";
  const std::string gx =
      "(1/R^2-(" + qx + "+R)/" + denominator + ")";
  const std::string gy = "(-" + qy + "/" + denominator + ")";
  const std::string conjugate_u_force_real =
      "(ur*" + gx + "+ui*" + gy + ")";
  const std::string conjugate_u_force_imag =
      "(ur*" + gy + "-ui*" + gx + ")";
  const std::string energy_derivative =
      "(-2*((ur*vr-ui*vi)*" + gx + "+(ur*vi+ui*vr)*" + gy + "))";
  const std::string field =
      "var:s,ur,ui,vr,vi,h,t,R;fun:1,-vr,-vi,"
      "-h*ur/2-(ur^2+ui^2)*" +
      conjugate_u_force_real +
      "/2,"
      "-h*ui/2-(ur^2+ui^2)*" +
      conjugate_u_force_imag + "/2," + energy_derivative +
      ",- (ur^2+ui^2),"
      "-2*R*(ur^2+ui^2)/(3*t);";
  return IMap(field);
}

IVector lc_entry_box(const IVector& shape) {
  using namespace capd;
  const interval radial_time = exp(interval(3.0) / interval(10.0));
  const interval binary_scale =
      exp(log(interval(9.0)) / interval(3.0)) *
      exp(interval(1.0) / interval(5.0));
  const interval velocity_scale =
      exp(log(interval(9.0)) / interval(3.0)) /
      exp(interval(1.0) / interval(10.0));
  const interval relative_x = shape[1] - interval(1.0) / interval(2.0);
  const interval relative_y = shape[2];
  const interval qx = binary_scale * relative_x;
  const interval qy = binary_scale * relative_y;
  const interval qt_x =
      velocity_scale * (interval(2.0) * relative_x / interval(3.0) + shape[3]);
  const interval qt_y =
      velocity_scale * (interval(2.0) * relative_y / interval(3.0) + shape[4]);
  const interval q_radius = sqrt(sqr(qx) + sqr(qy));
  const interval ur = sqrt((q_radius + qx) / interval(2.0));
  const interval ui = sqrt((q_radius - qx) / interval(2.0));
  const interval vr = (ur * qt_x + ui * qt_y) / interval(2.0);
  const interval vi = (ur * qt_y - ui * qt_x) / interval(2.0);
  const interval energy =
      (sqr(qt_x) + sqr(qt_y)) / interval(2.0) - interval(1.0) / q_radius;

  IVector initial(8);
  initial[0] = 0.0;
  initial[1] = ur;
  initial[2] = ui;
  initial[3] = vr;
  initial[4] = vi;
  initial[5] = energy;
  initial[6] = radial_time;
  initial[7] = binary_scale;
  return initial;
}

IVector stable_tail_box(const interval& kappa) {
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
  const interval p = -exp(-interval(10.0) * a_t);
  const interval nu = kappa * exp(-interval(10.0) * a_l);

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
      -a_t * p - (a_t + a_l) * A * p * nu - interval(3.0) * a_t * B * power(p, 3) -
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

  const interval position_error_radius =
      interval(1.0) / interval(4000000000.0);
  const interval velocity_error_radius =
      interval(1.0) / interval(800000000.0);
  const interval position_error(-position_error_radius.rightBound(),
                                position_error_radius.rightBound());
  const interval velocity_error(-velocity_error_radius.rightBound(),
                                velocity_error_radius.rightBound());

  IVector initial(5);
  initial[0] = 0.0;
  initial[1] = x + position_error;
  initial[2] = -sqrt3 / interval(2.0) + q + position_error;
  initial[3] = vx + velocity_error;
  initial[4] = vq + velocity_error;
  return initial;
}

}  // namespace

int main() {
  using namespace capd;
  try {
    const interval kappa_lower = interval(126793.0) / interval(100000.0);
    const interval kappa_upper = interval(126794.0) / interval(100000.0);
    const interval kappa(kappa_lower.leftBound(), kappa_upper.rightBound());
    IVector initial = stable_tail_box(kappa);
    IMap field = make_reversed_shape_field();
    IOdeSolver solver(field, 30);
    solver.setAbsoluteTolerance(1e-15);
    solver.setRelativeTolerance(1e-15);
    ITimeMap time_map(solver);
    C0Rect2Set set(initial);
    const IVector result = time_map(interval(97.0) / interval(10.0), set);
    const IVector lc_initial = lc_entry_box(result);
    IMap lc_field = make_reversed_lc_field();
    IOdeSolver lc_solver(lc_field, 30);
    lc_solver.setAbsoluteTolerance(1e-15);
    lc_solver.setRelativeTolerance(1e-15);
    ITimeMap lc_time_map(lc_solver);
    C0Rect2Set lc_set(lc_initial);
    const interval lc_duration = interval(1071249.0) / interval(1000000.0);
    lc_time_map.stopAfterStep(true);
    do {
      lc_time_map(lc_duration, lc_set);
      const IVector enclosure = lc_set.getLastEnclosure();
      const interval qx = sqr(enclosure[1]) - sqr(enclosure[2]);
      const interval qy = interval(2.0) * enclosure[1] * enclosure[2];
      const interval other_squared = sqr(qx + enclosure[7]) + sqr(qy);
      if (!(enclosure[6].leftBound() > 1.0 &&
            enclosure[7].leftBound() > 2.0 &&
            other_squared.leftBound() > 1.0)) {
        throw std::runtime_error("LC path left the analytic one-primary chart");
      }
    } while (!lc_time_map.completed());
    const IVector lc_result = static_cast<IVector>(lc_set);
    std::cout << std::hexfloat
              << "PASS_STAGE method=CAPD-6.1.0-native"
              << " stage=stable-tail-through-fixed-LC-time"
              << " kappa=" << kappa
              << " initial=" << initial
              << " shape_result=" << result
              << " lc_initial=" << lc_initial
              << " lc_result=" << lc_result
              << " path_t_gt_1=true"
              << " path_R_gt_2=true"
              << " path_other_primary_distance_gt_1=true\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FAIL " << error.what() << "\n";
    return 1;
  }
}
