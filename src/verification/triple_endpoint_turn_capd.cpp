// Rigorous first-turn sign certificate for the universal triple endpoint.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
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

IMap make_field() {
  // mu=1-lambda is increasing physical time, with
  // s=1-sign(lambda)|lambda|^3.  The dimensionless height is Y=Z/9^(1/3).
  // (P0,Q0) starts at (1,1/1000), while (P1,Q1) starts at (0,1).
  // Every center logarithmic derivative at least 1/1000 is their positive
  // linear combination.
  return IMap(
      "var:l,Y,U,P0,Q0,P1,Q1;"
      "fun:-1,"
      "3*l^2*U,"
      "-(2/3)*l^2*Y/((Y^2+l^4/4)*sqrt(Y^2+l^4/4)),"
      "3*l^2*Q0,"
      "(1/3)*l^2*(l^4-2*Y^2)*P0/"
      "((Y^2+l^4/4)^2*sqrt(Y^2+l^4/4)),"
      "3*l^2*Q1,"
      "(1/3)*l^2*(l^4-2*Y^2)*P1/"
      "((Y^2+l^4/4)^2*sqrt(Y^2+l^4/4));");
}

struct SlabResult {
  double min_height;
  double min_q0;
  double min_q1;
  double crossing_mu_upper;
};

SlabResult certify_slab(const interval& center_speed) {
  IMap field = make_field();
  IOdeSolver solver(field, 30);
  solver.setAbsoluteTolerance(1e-15);
  solver.setRelativeTolerance(1e-15);
  ITimeMap time_map(solver);
  time_map.stopAfterStep(true);

  IVector initial(7);
  initial[0] = 1.0;
  initial[1] = 0.0;
  initial[2] = center_speed;
  initial[3] = 1.0;
  initial[4] = interval(1.0) / interval(1000.0);
  initial[5] = 0.0;
  initial[6] = 1.0;
  C0Rect2Set set(initial);

  const interval final_time(1.65);
  double min_height = std::numeric_limits<double>::infinity();
  double min_q0 = std::numeric_limits<double>::infinity();
  double min_q1 = std::numeric_limits<double>::infinity();
  bool first_step = true;

  do {
    time_map(final_time, set);
    const IVector enclosure = set.getLastEnclosure();
    const IVector endpoint = static_cast<IVector>(set);

    if (!(enclosure[4].leftBound() > 0.0 &&
          enclosure[6].leftBound() > 0.0)) {
      throw std::runtime_error("transverse derivative lost positivity");
    }
    min_q0 = std::min(min_q0, enclosure[4].leftBound());
    min_q1 = std::min(min_q1, enclosure[6].leftBound());

    if (first_step) {
      // At mu=0, Y=0 and U>0 exactly. The displayed vector field gives
      // Y_mu>0 until the end of this first step.
      if (!(enclosure[2].leftBound() > 0.0 &&
            endpoint[1].leftBound() > 0.0)) {
        throw std::runtime_error("first step does not leave the center upward");
      }
      first_step = false;
    } else if (!(enclosure[1].leftBound() > 0.0)) {
      throw std::runtime_error("height is not positive before first turn");
    }
    min_height = std::min(min_height, endpoint[1].leftBound());

    if (endpoint[2].rightBound() < 0.0) {
      const interval crossing_mu = 1.0 - endpoint[0];
      return {min_height, min_q0, min_q1, crossing_mu.rightBound()};
    }
  } while (!time_map.completed());
  throw std::runtime_error("no first turn before mu=1.65");
}

}  // namespace

int main() {
  try {
    // The analytic center estimates give
    // sqrt(5/18)<y_tau(0)<=sqrt(19)/6, hence the larger rational cover
    // [1/2,3/4]. Divide it into exact binary-rational slabs.
    constexpr int slab_count = 256;
    double min_height = std::numeric_limits<double>::infinity();
    double min_q0 = std::numeric_limits<double>::infinity();
    double min_q1 = std::numeric_limits<double>::infinity();
    double max_crossing_mu = 0.0;
    for (int index = 0; index < slab_count; ++index) {
      const double lower = 0.5 + static_cast<double>(index) / 1024.0;
      const double upper = 0.5 + static_cast<double>(index + 1) / 1024.0;
      SlabResult result;
      try {
        result = certify_slab(interval(lower, upper));
      } catch (const std::exception& error) {
        throw std::runtime_error("slab " + std::to_string(index) + ": " +
                                 error.what());
      }
      min_height = std::min(min_height, result.min_height);
      min_q0 = std::min(min_q0, result.min_q0);
      min_q1 = std::min(min_q1, result.min_q1);
      max_crossing_mu = std::max(max_crossing_mu, result.crossing_mu_upper);
    }

    std::cout << std::hexfloat
              << "PASS method=CAPD-6.1.0-native"
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
              << " center_speed_cover=[1/2,3/4]"
              << " center_log_derivative_lower=1/1000"
              << " slabs=" << slab_count
              << " min_height_hex=" << min_height
              << " min_q0_hex=" << min_q0
              << " min_q1_hex=" << min_q1
              << " max_crossing_mu_hex=" << max_crossing_mu << "\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "ERROR " << error.what() << "\n";
    return 2;
  }
}
