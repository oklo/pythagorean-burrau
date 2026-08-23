// Conditional compact-core certificate for the triple-endpoint global match.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
//
// The finite collision-tail boxes used below are deliberately looser than the
// proved analytic enclosures in TRIPLE_ENDPOINT_COLLISION_TAIL.md.

#include <algorithm>
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

IMap make_fuchsian_field() {
  // s increases away from collision, r=rho*exp(s), and yx=dy/dX for
  // X=-log(r).  The final two components are the canonical fast mode.
  return IMap(
      "var:s,r,y,yx,p,px;"
      "fun:1,r,-yx,"
      "(y*((y^2+1/4)^(-3/2)-1)-(1-2*r)*yx)/(2*(1-r)),"
      "-px,"
      "((3-2*r)*px-(1-2*y^2)*p/"
      "(2*(y^2+1/4)^(5/2)))/(2*(1-r));");
}

IMap make_outgoing_field() {
  // lambda is reversed eccentric anomaly.  Z=-z and w=dz/dt give the
  // ordinary outgoing softened-Kepler equations.  (p,q) retain the original
  // physical-time orientation used in W(J,P_+).
  return IMap(
      "var:lambda,psi,Z,w,p,q;"
      "fun:1,-1,"
      "cos(psi)^2*w,"
      "-2*Z*cos(psi)^2/"
      "((Z^2+cos(psi)^4/4)*sqrt(Z^2+cos(psi)^4/4)),"
      "-cos(psi)^2*q,"
      "-cos(psi)^2*(cos(psi)^4-2*Z^2)*p/"
      "((Z^2+cos(psi)^4/4)^2*sqrt(Z^2+cos(psi)^4/4));");
}

IVector collision_box(const interval& amplitude) {
  using namespace capd;
  const interval rho = interval(1.0) / interval(4294967296.0);  // 2^-32
  const interval nu = (-interval(1.0) + sqrt(interval(19.0))) / interval(4.0);
  const interval beta_plus =
      (interval(3.0) + sqrt(interval(7.0))) / interval(4.0);
  const interval shape_mode = exp(nu * log(rho));
  const interval fast_mode = exp(beta_plus * log(rho));
  const interval base_error_radius =
      interval(1.0) / power(interval(10.0), 14);
  const interval fast_error_radius =
      interval(1.0) / power(interval(10.0), 20);
  const interval base_error(-base_error_radius.rightBound(),
                            base_error_radius.rightBound());
  const interval fast_error(-fast_error_radius.rightBound(),
                            fast_error_radius.rightBound());

  IVector initial(6);
  initial[0] = 0.0;
  initial[1] = rho;
  initial[2] = -sqrt(interval(3.0)) / interval(2.0) +
               amplitude * shape_mode + base_error;
  initial[3] = -nu * amplitude * shape_mode + base_error;
  initial[4] = fast_mode + fast_error;
  initial[5] = -beta_plus * fast_mode + fast_error;

  IMap field = make_fuchsian_field();
  IOdeSolver solver(field, 30);
  solver.setAbsoluteTolerance(1e-16);
  solver.setRelativeTolerance(1e-16);
  ITimeMap time_map(solver);
  C0Rect2Set set(initial);
  const interval duration = log((interval(1.0) / interval(5.0)) / rho);
  return time_map(duration, set);
}

IVector propagate_core(const interval& amplitude, bool path_check) {
  using namespace capd;
  const IVector local = collision_box(amplitude);
  const interval radius = local[1];
  const interval radial_velocity =
      -interval(2.0) * sqrt((interval(1.0) - radius) / radius);

  IVector initial(6);
  initial[0] = 0.0;
  initial[1] = acos(sqrt(radius));
  initial[2] = -radius * local[2];
  initial[3] = radial_velocity * (local[2] - local[3]);
  initial[4] = local[4];
  initial[5] = -radial_velocity * local[5] / radius;

  IMap field = make_outgoing_field();
  IOdeSolver solver(field, 30);
  solver.setAbsoluteTolerance(1e-15);
  solver.setRelativeTolerance(1e-15);
  ITimeMap time_map(solver);
  C0Rect2Set set(initial);
  const interval duration = interval(19.0) * interval::pi();
  if (!path_check) {
    return time_map(duration, set);
  }

  time_map.stopAfterStep(true);
  do {
    time_map(duration, set);
    if (!(set.getLastEnclosure()[3].leftBound() > 0.0)) {
      throw std::runtime_error("candidate box lost first-leg outgoing velocity");
    }
  } while (!time_map.completed());
  return static_cast<IVector>(set);
}

}  // namespace

int main() {
  using namespace capd;
  try {
    const interval escape_amplitude =
        -interval(24696.0) / interval(100000.0);
    const interval return_amplitude =
        -interval(24694.0) / interval(100000.0);
    const interval candidate_amplitude(escape_amplitude.leftBound(),
                                       return_amplitude.rightBound());

    const IVector escaping = propagate_core(escape_amplitude, true);
    const IVector returning = propagate_core(return_amplitude, true);
    const IVector candidate = propagate_core(candidate_amplitude, true);

    const interval escape_energy =
        sqr(escaping[3]) / interval(2.0) - interval(2.0) / escaping[2];
    const interval return_energy =
        sqr(returning[3]) / interval(2.0) - interval(2.0) / returning[2];
    const interval return_tail = interval(1.0) /
        (interval(4.0) * power(returning[2], 3));
    if (!(escaping[2].leftBound() > interval(10.0).rightBound() &&
          escape_energy.leftBound() > 0.0)) {
      std::cerr << "FAIL escape amplitude: state=" << escaping
                << " H=" << escape_energy << "\n";
      return 1;
    }
    if (!(returning[2].leftBound() > interval(10.0).rightBound() &&
          returning[3].leftBound() > 0.0 &&
          (return_energy + return_tail).rightBound() < 0.0)) {
      std::cerr << "FAIL return amplitude: state=" << returning
                << " H+tail=" << return_energy + return_tail << "\n";
      return 1;
    }

    // Analytic incoming-parabolic tail enclosure for the returned Jost field.
    // With z=-2/x^2, P=x^2 p and Omega=z p_dot-z_dot p, one has
    //
    //   |dP/dx| <= sqrt(2)c |Omega|,
    //   |dOmega/dx| <= 3 c x^2 |P|/(8 sqrt(2)),
    //   c=(1-X^4/32)^(-1/2).
    //
    // The exact boundary intervals are 2 gamma in [-1/50,-1/125] and
    // Omega in [-9/20,-11/25]. The following Volterra bootstrap is uniform
    // in binary phase and in every parabolic member of the amplitude box.
    const interval x_lower = sqrt(interval(2.0) / candidate[2].rightBound());
    const interval x_upper = sqrt(interval(2.0) / candidate[2].leftBound());
    const interval tail_factor =
        interval(1.0) /
        sqrt(interval(1.0) - power(x_upper, 4) / interval(32.0));
    const interval coupling_p = sqrt(interval(2.0)) * tail_factor * x_upper;
    const interval coupling_omega =
        tail_factor * power(x_upper, 3) /
        (interval(8.0) * sqrt(interval(2.0)));
    const interval bootstrap_denominator =
        interval(1.0) - coupling_p * coupling_omega;
    if (!(bootstrap_denominator.leftBound() > 0.0)) {
      throw std::runtime_error("returned-Jost tail bootstrap did not close");
    }
    const interval p_abs =
        (interval(1.0) / interval(50.0) +
         coupling_p * interval(9.0) / interval(20.0)) /
        bootstrap_denominator;
    const interval omega_change = coupling_omega * p_abs;
    const interval omega(
        (-interval(9.0) / interval(20.0) - omega_change).leftBound(),
        (-interval(11.0) / interval(25.0) + omega_change).rightBound());
    if (!(omega.rightBound() < 0.0)) {
      throw std::runtime_error("returned-Jost Wronskian lost its tail sign");
    }
    const interval p_normalized_lower =
        -interval(1.0) / interval(50.0) + sqrt(interval(2.0)) *
        x_lower * (-omega.rightBound());
    const interval p_normalized_upper =
        -interval(1.0) / interval(125.0) + coupling_p *
        (-omega.leftBound());
    const interval p_normalized(p_normalized_lower.leftBound(),
                                p_normalized_upper.rightBound());
    if (!(p_normalized.leftBound() > 0.0)) {
      throw std::runtime_error("returned-Jost normalized field not positive");
    }
    const interval x_squared = interval(2.0) / candidate[2];
    const interval jost_value = p_normalized / x_squared;
    const interval jost_derivative =
        -(candidate[3] * p_normalized + x_squared * omega) / interval(2.0);
    const interval jost_fast_wronskian =
        jost_value * candidate[5] - jost_derivative * candidate[4];
    const interval wronskian_upper = -interval(1.0) / interval(2.0);
    if (!(jost_fast_wronskian.rightBound() < wronskian_upper.leftBound())) {
      std::cerr << "FAIL returned-Jost/fast-mode sign: P=" << p_normalized
                << " Omega=" << omega << " p=" << jost_value
                << " pdot=" << jost_derivative
                << " W=" << jost_fast_wronskian << "\n";
      return 1;
    }

    std::cout << std::hexfloat
              << "PASS method=CAPD-6.1.0-native"
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
              << " collision_rho=2^-32"
              << " proved_base_tail_box=1e-14"
              << " proved_fast_tail_box=1e-20"
              << " candidate_path_w_positive=true"
              << " rational_threshold=W_J_Pplus<-1/2"
              << " amplitude_bracket=[" << escape_amplitude.leftBound() << ","
              << return_amplitude.rightBound() << "]"
              << " escape_H=[" << escape_energy.leftBound() << ","
              << escape_energy.rightBound() << "]"
              << " return_H_plus_tail=["
              << (return_energy + return_tail).leftBound() << ","
              << (return_energy + return_tail).rightBound() << "]"
              << " candidate_Z=[" << candidate[2].leftBound() << ","
              << candidate[2].rightBound() << "]"
              << " candidate_w=[" << candidate[3].leftBound() << ","
              << candidate[3].rightBound() << "]"
              << " candidate_Pplus=[" << candidate[4].leftBound() << ","
              << candidate[4].rightBound() << "]"
              << " candidate_Pplus_dot=[" << candidate[5].leftBound() << ","
              << candidate[5].rightBound() << "]"
              << " returned_P=[" << p_normalized.leftBound() << ","
              << p_normalized.rightBound() << "]"
              << " returned_Omega=[" << omega.leftBound() << ","
              << omega.rightBound() << "]"
              << " returned_p=[" << jost_value.leftBound() << ","
              << jost_value.rightBound() << "]"
              << " returned_p_dot=[" << jost_derivative.leftBound() << ","
              << jost_derivative.rightBound() << "]"
              << " W_J_Pplus=[" << jost_fast_wronskian.leftBound() << ","
              << jost_fast_wronskian.rightBound() << "]\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "ERROR " << error.what() << "\n";
    return 2;
  }
}
