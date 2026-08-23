// Rigorous half-line certificate for the restricted transverse scattering sign.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "capd/capdlib.h"

namespace {

using capd::C0Rect2Set;
using capd::IMap;
using capd::IOdeSolver;
using capd::ITimeMap;
using capd::IVector;
using capd::interval;

IMap make_field() {
  // psi is eccentric anomaly, r=cos(psi)^2, and dtheta=r dpsi.
  // (u,up) and (v,vp) are the two transverse fundamental solutions.
  return IMap(
      "var:psi,z,w,u,up,v,vp;"
      "fun:1,"
      "cos(psi)^2*w,"
      "-2*z*cos(psi)^2/((z^2+cos(psi)^4/4)*sqrt(z^2+cos(psi)^4/4)),"
      "cos(psi)^2*up,"
      "cos(psi)^2*(cos(psi)^4-2*z^2)*u/"
      "((z^2+cos(psi)^4/4)^2*sqrt(z^2+cos(psi)^4/4)),"
      "cos(psi)^2*vp,"
      "cos(psi)^2*(cos(psi)^4-2*z^2)*v/"
      "((z^2+cos(psi)^4/4)^2*sqrt(z^2+cos(psi)^4/4));");
}

IVector propagate(const interval& launch_velocity, bool fundamental_fields,
                  bool certify_outgoing = false) {
  IMap field = make_field();
  IOdeSolver solver(field, 30);
  solver.setAbsoluteTolerance(1e-15);
  solver.setRelativeTolerance(1e-15);
  ITimeMap time_map(solver);

  IVector initial(7);
  initial[0] = 0.0;
  initial[1] = 0.0;
  initial[2] = launch_velocity;
  initial[3] = fundamental_fields ? interval(1.0) : interval(0.0);
  initial[4] = 0.0;
  initial[5] = 0.0;
  initial[6] = fundamental_fields ? interval(1.0) : interval(0.0);
  C0Rect2Set set(initial);
  const interval final_time = interval::pi() * 80.0;
  if (!certify_outgoing) {
    return time_map(final_time, set);
  }

  // Endpoint positivity alone would permit a prior turn and center
  // recrossing. Enclose every accepted Taylor step and prove w>0 throughout
  // the entire initial outbound leg.
  time_map.stopAfterStep(true);
  do {
    time_map(final_time, set);
    const IVector step_enclosure = set.getLastEnclosure();
    if (!(step_enclosure[2].leftBound() > 0.0)) {
      throw std::runtime_error("upper launch outbound velocity not path-positive");
    }
  } while (!time_map.completed());
  return static_cast<IVector>(set);
}

}  // namespace

int main() {
  using namespace capd;

  try {
    // Exact rational endpoints 2.905110 and 2.905113.
    const interval velocity_low = interval(2905110.0) / interval(1000000.0);
    const interval velocity_high = interval(2905113.0) / interval(1000000.0);

    const IVector low = propagate(velocity_low, false);
    const IVector high = propagate(velocity_high, false, true);
    const interval low_energy = sqr(low[2]) / 2.0 - 2.0 / low[1];
    const interval low_tail = 1.0 / (4.0 * low[1] * low[1] * low[1]);
    const interval high_energy = sqr(high[2]) / 2.0 - 2.0 / high[1];

    if (!(low[1].leftBound() > 1.0 && low[2].leftBound() > 0.0 &&
          (low_energy + low_tail).rightBound() < 0.0)) {
      std::cerr << "FAIL lower launch not certified returning: z=" << low[1]
                << " w=" << low[2] << " H+tail=" << low_energy + low_tail
                << "\n";
      return 1;
    }
    if (!(high[1].leftBound() > 1.0 && high[2].leftBound() > 0.0 &&
          high_energy.leftBound() > 0.0)) {
      std::cerr << "FAIL upper launch not certified escaping: z=" << high[1]
                << " w=" << high[2] << " H=" << high_energy << "\n";
      return 1;
    }

    // The lower endpoint is in the first-turn set and the stepwise path check
    // plus positive energy puts the upper endpoint in the escape set. Enclose
    // the parabolic boundary and its transverse fundamental matrix.
    const interval velocity_bracket(velocity_low.leftBound(),
                                    velocity_high.rightBound());
    const IVector state = propagate(velocity_bracket, true);
    const interval z = state[1];
    const interval w = state[2];
    const interval u = state[3];
    const interval up = state[4];
    const interval v = state[5];
    const interval vp = state[6];
    if (!(z.leftBound() > 1.0 && w.leftBound() > 0.0)) {
      throw std::runtime_error("parabolic bracket endpoint is not outgoing");
    }

    // Analytic outgoing-Jost tail bounds. For K=z and K>=1,
    // q=k/z lies in [1,Q], W=zk'-z'k lies in
    // [-Q/(sqrt(7/2) K^(3/2)),0]. Monotonicity lets us use z.leftBound()
    // for a rectangular enclosure over the section box.
    const interval k_lower(z.leftBound());
    const interval c0 = sqrt(interval(7.0) / 2.0);
    const interval tail_norm = 1.0 / (7.0 * k_lower * k_lower);
    const interval q_upper = 1.0 / (1.0 - tail_norm);
    const interval q(1.0, q_upper.rightBound());
    const interval rotation_wronskian(
        (-q_upper / (c0 * k_lower * sqrt(k_lower))).leftBound(), 0.0);
    const interval jost_value = z * q;
    const interval jost_derivative = w * q + rotation_wronskian / z;

    // The exact fundamental determinant is one. Its inverse gives
    // k'(0)=-u'(L)k(L)+u(L)k'(L).
    const interval center_derivative = -up * jost_value + u * jost_derivative;
    const interval center_value = vp * jost_value - v * jost_derivative;
    const interval center_value_threshold = interval(7.0) / interval(20.0);
    const interval center_derivative_threshold = interval(3.0) / interval(5.0);
    if (!(center_value.leftBound() > center_value_threshold.rightBound() &&
          center_derivative.leftBound() >
              center_derivative_threshold.rightBound())) {
      std::cerr << "FAIL Jost center sign: k0=" << center_value
                << " k0prime=" << center_derivative << "\n";
      return 1;
    }

    std::cout << std::hexfloat
              << "PASS method=CAPD-6.1.0-native"
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
              << " endpoint_psi=80*pi"
              << " velocity_bracket_hex=[" << velocity_bracket.leftBound() << ","
              << velocity_bracket.rightBound() << "]"
              << " lower_H_plus_tail_hex=[" << (low_energy + low_tail).leftBound()
              << "," << (low_energy + low_tail).rightBound() << "]"
              << " upper_path_w_positive=true"
              << " upper_H_hex=[" << high_energy.leftBound() << ","
              << high_energy.rightBound() << "]"
              << " z_hex=[" << z.leftBound() << "," << z.rightBound() << "]"
              << " rational_thresholds=k0>7/20,k0prime>3/5"
              << " k0_hex=[" << center_value.leftBound() << ","
              << center_value.rightBound() << "]"
              << " k0prime_hex=[" << center_derivative.leftBound() << ","
              << center_derivative.rightBound() << "]\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "ERROR " << error.what() << "\n";
    return 2;
  }
}
