// Rigorous first-syzygy amplitude bound at the isosceles-right endpoint.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f

// In the reflection-fixed endpoint problem, x is the base half-separation
// and h is the apex height relative to the base.  The first syzygy is h=0.
// At that event the terminal torque amplitude is
//
//   Z = ell_23^2 / r_12 = x*h_dot^2/2.
//
// The verifier encloses every Taylor step, proves h>0 before one unique
// transverse crossing, excludes collision, and proves Z<1 on the complete
// crossing step.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "capd/capdlib.h"

int main() {
  using namespace capd;

  try {
    IMap field(
        "var:x,h,vx,vh;"
        "fun:vx,"
        "vh,"
        "-1/(4*sqrt(2)*x^2)-x/((x^2+h^2)*sqrt(x^2+h^2)),"
        "-(1+sqrt(2))*h/((x^2+h^2)*sqrt(x^2+h^2));");

    IOdeSolver solver(field, 24);
    solver.setAbsoluteTolerance(1e-15);
    solver.setRelativeTolerance(1e-15);
    solver.setStep(interval(1.0) / interval(10000.0));
    ITimeMap time_map(solver);
    time_map.stopAfterStep(true);

    IVector initial(4);
    initial[0] = interval(1.0) / interval(2.0);
    initial[1] = interval(1.0) / interval(2.0);
    initial[2] = 0.0;
    initial[3] = 0.0;
    C0Rect2Set set(initial);

    const interval target = interval(943.0) / interval(2000.0);  // 0.4715
    bool crossing_found = false;
    int steps = 0;
    interval crossing_time;
    interval crossing_tube_x;
    interval crossing_tube_vh;
    interval amplitude;

    do {
      const interval start_time = time_map.getCurrentTime();
      const IVector start_state = IVector(set);
      time_map(target, set);
      ++steps;

      const interval step = solver.getStep();
      const IOdeSolver::SolutionCurve& curve = solver.getCurve();
      const interval domain(0.0, step.rightBound());
      const IVector tube = curve(domain);
      const IVector end_state = IVector(set);

      const interval radius_squared = sqr(tube[0]) + sqr(tube[1]);
      if (!(tube[0].leftBound() > 0.0) ||
          !(radius_squared.leftBound() > 0.0)) {
        throw std::runtime_error("collision exclusion failed");
      }

      if (!crossing_found) {
        if (tube[1].contains(0.0)) {
          if (!(start_state[1].leftBound() > 0.0) ||
              !(end_state[1].rightBound() < 0.0) ||
              !(tube[3].rightBound() < 0.0)) {
            throw std::runtime_error(
                "candidate syzygy step is not a unique downward crossing");
          }
          crossing_found = true;
          crossing_time = start_time + domain;
          crossing_tube_x = tube[0];
          crossing_tube_vh = tube[3];
          amplitude = tube[0] * sqr(tube[3]) / interval(2.0);
          if (!(amplitude.rightBound() < 1.0)) {
            throw std::runtime_error("endpoint amplitude bound Z<1 failed");
          }
        } else if (!(tube[1].leftBound() > 0.0)) {
          throw std::runtime_error("unclassified pre-syzygy height tube");
        }
      }
    } while (!time_map.completed());

    if (!crossing_found) {
      const IVector terminal_state = IVector(set);
      std::cerr << "DIAGNOSTIC steps=" << steps
                << " current_time=" << time_map.getCurrentTime()
                << " terminal_state=" << terminal_state << "\n";
      throw std::runtime_error("first syzygy not found before target time");
    }

    std::cout << std::hexfloat
              << "PASS_ISOSCELES_SYZYGY"
              << " method=CAPD-6.1.0-native"
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
              << " steps=" << steps
              << " crossing_time_hex=[" << crossing_time.leftBound() << ","
              << crossing_time.rightBound() << "]"
              << " x_tube_hex=[" << crossing_tube_x.leftBound() << ","
              << crossing_tube_x.rightBound() << "]"
              << " vh_tube_hex=[" << crossing_tube_vh.leftBound() << ","
              << crossing_tube_vh.rightBound() << "]"
              << " Z_tube_hex=[" << amplitude.leftBound() << ","
              << amplitude.rightBound() << "]"
              << " rational_upper=1\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "ERROR " << error.what() << "\n";
    return 2;
  }
}
