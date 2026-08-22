// Rigorous finite-time certificate for the restricted transversality sign.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
// Build CAPD with -DCAPD_INTERVAL_TYPE=NATIVE and compile this file with
// CAPD's generated capd-config.  The accompanying shell script automates the
// commit check, compilation, and execution.

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "capd/capdlib.h"

namespace {

constexpr int kSlabs = 256;

bool verbose_requested(int argc, char** argv) {
  if (argc == 1) {
    return false;
  }
  if (argc == 2 && std::string(argv[1]) == "--verbose") {
    return true;
  }
  throw std::invalid_argument("usage: restricted_transversality_capd [--verbose]");
}

}  // namespace

int main(int argc, char** argv) {
  using namespace capd;

  try {
    const bool verbose = verbose_requested(argc, argv);

    // phi is eccentric anomaly, r=cos(phi)^2, and dtheta=r dphi.
    // w=dz/dtheta and p=dq/dtheta, where q=h/v normalizes the even
    // homogeneous Jacobi field h by its positive launch speed v.
    IMap field(
        "var:phi,z,w,q,p;"
        "fun:1,"
        "cos(phi)^2*w,"
        "-2*z*cos(phi)^2/((z^2+cos(phi)^4/4)*sqrt(z^2+cos(phi)^4/4)),"
        "cos(phi)^2*p,"
        "cos(phi)^2*(4*z^2-cos(phi)^4/2)*q/"
        "((z^2+cos(phi)^4/4)^2*sqrt(z^2+cos(phi)^4/4));");

    // The exact analytic bracket sqrt(8)<v_*<4 lies in the rational cover
    // [14/5,4].  Interval evaluation makes the stored endpoints outward.
    const interval velocity_lower = interval(14.0) / interval(5.0);
    const interval velocity_upper = interval(4.0);
    const interval velocity_span = velocity_upper - velocity_lower;
    const interval final_endpoint =
        velocity_lower + velocity_span * interval(kSlabs) / interval(kSlabs);
    const interval velocity_cover(velocity_lower.leftBound(),
                                  final_endpoint.rightBound());
    const interval analytic_lower = sqrt(interval(8.0));
    const interval analytic_bracket(analytic_lower.leftBound(), 4.0);
    if (!subset(analytic_bracket, velocity_cover)) {
      throw std::runtime_error("rational velocity cover does not contain [sqrt(8),4]");
    }

    double global_lower = 1.0;
    double global_upper = -1.0;
    int worst_slab = -1;
    interval worst_velocity;
    interval worst_derivative;

    if (verbose) {
      std::cout << "slab velocity_lower velocity_upper derivative_lower derivative_upper\n";
      std::cout << std::hexfloat;
    }

    for (int i = 0; i < kSlabs; ++i) {
      // Interval endpoints overlap, so rounding cannot leave a gap between
      // adjacent slabs.
      const interval endpoint0 =
          velocity_lower + velocity_span * interval(i) / interval(kSlabs);
      const interval endpoint1 =
          velocity_lower + velocity_span * interval(i + 1) / interval(kSlabs);
      const interval velocity(endpoint0.leftBound(), endpoint1.rightBound());

      IOdeSolver solver(field, 20);
      solver.setAbsoluteTolerance(1e-14);
      solver.setRelativeTolerance(1e-14);
      ITimeMap time_map(solver);

      IVector initial(5);
      initial[0] = 0.0;      // phi
      initial[1] = 0.0;      // z
      initial[2] = velocity; // w
      initial[3] = 1.0;      // q=h/v
      initial[4] = 0.0;      // p=dq/dtheta
      C0Rect2Set set(initial);

      // CAPD's interval pi encloses the exact endpoint.  Treating time as an
      // interval encloses the target phi=pi/2; the autonomous phase equation
      // has phi'=1.
      const IVector result = time_map(interval::pi() / 2.0, set);
      const interval derivative = result[4];
      const interval rational_threshold = interval(1.0) / interval(125.0);
      if (!std::isfinite(derivative.leftBound()) ||
          !std::isfinite(derivative.rightBound()) ||
          !(derivative.leftBound() > rational_threshold.rightBound())) {
        std::cerr << "FAIL slab=" << i << " velocity=" << velocity
                  << " derivative=" << derivative
                  << " required_lower=1/125\n";
        return 1;
      }

      if (derivative.leftBound() < global_lower) {
        global_lower = derivative.leftBound();
        worst_slab = i;
        worst_velocity = velocity;
        worst_derivative = derivative;
      }
      global_upper = std::max(global_upper, derivative.rightBound());

      if (verbose) {
        std::cout << i << " "
                  << velocity.leftBound() << " " << velocity.rightBound() << " "
                  << derivative.leftBound() << " " << derivative.rightBound() << "\n";
      }
    }

    std::cout << std::hexfloat
              << "PASS method=CAPD-6.1.0-native"
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
              << " slabs=" << kSlabs
              << " velocity_cover_hex=[" << velocity_cover.leftBound() << ","
              << velocity_cover.rightBound() << "]"
              << " rational_lower=1/125"
              << " normalized_derivative_global_hex=[" << global_lower << ","
              << global_upper << "]"
              << " worst_slab=" << worst_slab
              << " worst_velocity_hex=[" << worst_velocity.leftBound() << ","
              << worst_velocity.rightBound() << "]"
              << " worst_derivative_hex=[" << worst_derivative.leftBound() << ","
              << worst_derivative.rightBound() << "]\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "ERROR " << error.what() << "\n";
    return 2;
  }
}
