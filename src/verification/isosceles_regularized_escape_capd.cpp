// Rigorous terminal escape certificate on the regularized isosceles endpoint.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
//
// The exact reflection-symmetric endpoint suffers repeated pair-(1,2)
// collisions, so this orbit is only a regularized comparison orbit after its
// first collision.  Pair Levi-Civita coordinates make that comparison smooth.
// This verifier encloses the complete arc 0 <= sigma <= 7, proves that neither
// unselected separation vanishes, and validates the strict eta=4 terminal
// binary-escaper inequalities.  Together with separate C1 certificates that
// unfold every selected collision, these strict inequalities transfer to a
// punctured tied-parameter neighborhood of classical collision-free orbits.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "capd/capdlib.h"

int main() {
  using namespace capd;

  try {
    const std::string radius = "(wr^2+wi^2)";
    const std::string gx = "(wr^2-wi^2)";
    const std::string gy = "(2*wr*wi)";
    const std::string pair = "(m+n)";
    const std::string total = "(m+n+1)";
    const std::string d31x = "(Gx+n*" + gx + "/" + pair + ")";
    const std::string d31y = "(Gy+n*" + gy + "/" + pair + ")";
    const std::string d23x = "(Gx-m*" + gx + "/" + pair + ")";
    const std::string d23y = "(Gy-m*" + gy + "/" + pair + ")";
    const std::string r31_squared =
        "(" + d31x + "^2+" + d31y + "^2)";
    const std::string r23_squared =
        "(" + d23x + "^2+" + d23y + "^2)";
    const std::string r31_cubed =
        "(" + r31_squared + "*sqrt(" + r31_squared + "))";
    const std::string r23_cubed =
        "(" + r23_squared + "*sqrt(" + r23_squared + "))";
    const std::string force_x =
        "(" + d23x + "/" + r23_cubed + "-" + d31x + "/" +
        r31_cubed + ")";
    const std::string force_y =
        "(" + d23y + "/" + r23_cubed + "-" + d31y + "/" +
        r31_cubed + ")";
    const std::string complement_x =
        "(-" + total + "/" + pair + "*(m*" + d31x + "/" +
        r31_cubed + "+n*" + d23x + "/" + r23_cubed + "))";
    const std::string complement_y =
        "(-" + total + "/" + pair + "*(m*" + d31y + "/" +
        r31_cubed + "+n*" + d23y + "/" + r23_cubed + "))";

    IMap field(
        "var:wr,wi,zr,zi,h,Gx,Gy,Px,Py,tp,m,n;fun:"
        "zr,zi,"
        "(h/2)*wr+(" + radius + "/2)*(wr*" + force_x + "+wi*" +
        force_y + "),"
        "(h/2)*wi+(" + radius + "/2)*(wr*" + force_y + "-wi*" +
        force_x + "),"
        "2*((wr*zr-wi*zi)*" + force_x +
        "+(wr*zi+wi*zr)*" + force_y + "),"
        +radius + "*Px," + radius + "*Py," + radius + "*" +
        complement_x + "," + radius + "*" + complement_y + "," +
        radius + ",0,0;");

    IOdeSolver solver(field, 24);
    solver.setAbsoluteTolerance(1e-14);
    solver.setRelativeTolerance(1e-14);
    solver.setStep(interval(1.0) / interval(1000.0));
    ITimeMap time_map(solver);
    time_map.stopAfterStep(true);

    const interval endpoint_mass = interval(1.0) / sqrt(interval(2.0));
    IVector initial(12);
    initial[0] = interval(1.0);
    initial[1] = interval(0.0);
    initial[2] = interval(0.0);
    initial[3] = interval(0.0);
    initial[4] = -sqrt(interval(2.0));
    initial[5] = interval(0.0);
    initial[6] = interval(1.0) / interval(2.0);
    initial[7] = interval(0.0);
    initial[8] = interval(0.0);
    initial[9] = interval(0.0);
    initial[10] = endpoint_mass;
    initial[11] = endpoint_mass;
    C0Rect2Set set(initial);

    const interval target(7.0);
    int steps = 0;
    double minimum_other_squared = 1.0e300;
    double minimum_brake_residual_squared = 1.0e300;
    bool pre_syzygy_interface_checked = false;
    interval interface_gy;
    do {
      const interval start_time = time_map.getCurrentTime();
      time_map(target, set);
      ++steps;
      const interval step = solver.getStep();
      const interval domain(0.0, step.rightBound());
      const IVector tube = solver.getCurve()(domain);

      const interval tube_radius = sqr(tube[0]) + sqr(tube[1]);
      const interval tube_gx = sqr(tube[0]) - sqr(tube[1]);
      const interval tube_gy = interval(2.0) * tube[0] * tube[1];
      const interval tube_pair = tube[10] + tube[11];
      const interval tube_d31x = tube[5] + tube[11] * tube_gx / tube_pair;
      const interval tube_d31y = tube[6] + tube[11] * tube_gy / tube_pair;
      const interval tube_d23x = tube[5] - tube[10] * tube_gx / tube_pair;
      const interval tube_d23y = tube[6] - tube[10] * tube_gy / tube_pair;
      const interval tube_r31_squared = sqr(tube_d31x) + sqr(tube_d31y);
      const interval tube_r23_squared = sqr(tube_d23x) + sqr(tube_d23y);
      const double step_other_squared = std::min(
          tube_r31_squared.leftBound(), tube_r23_squared.leftBound());
      minimum_other_squared =
          std::min(minimum_other_squared, step_other_squared);
      if (!(step_other_squared > 0.002)) {
        throw std::runtime_error(
            "unselected squared separation is not above 1/500");
      }
      // The selected collision is regular in w.  This guard catches an
      // accidental enclosure blow-up without excluding the legitimate w=0
      // crossings.
      if (!(tube_radius.rightBound() < 2.0)) {
        throw std::runtime_error("selected-pair radius enclosure blew up");
      }
      if (!pre_syzygy_interface_checked
          && time_map.getCurrentTime().leftBound() >= 0.5) {
        const IVector interface_state = IVector(set);
        interface_gy = interface_state[6];
        if (!(interface_gy.leftBound() > 0.1)) {
          throw std::runtime_error(
              "sigma=1/2 interface height is not above 1/10");
        }
        pre_syzygy_interface_checked = true;
      }
      if (start_time.leftBound() >= 0.5) {
        // At an ordinary point, a labelled brake is equivalent to z=P=0:
        // dot(g)=2z/conj(w), while P=dot(G).  The same polynomial residual
        // stays regular and nonzero at each comparison-orbit collision.
        const interval brake_residual_squared =
            sqr(tube[2]) + sqr(tube[3]) + sqr(tube[7]) + sqr(tube[8]);
        minimum_brake_residual_squared = std::min(
            minimum_brake_residual_squared,
            brake_residual_squared.leftBound());
        if (!(brake_residual_squared.leftBound() > 2.0)) {
          throw std::runtime_error(
              "regularized brake residual squared is not above 2");
        }
      }
    } while (!time_map.completed());

    if (!pre_syzygy_interface_checked) {
      throw std::runtime_error("pre-syzygy interface was not checked");
    }

    const IVector terminal = IVector(set);
    const interval terminal_radius = sqr(terminal[0]) + sqr(terminal[1]);
    const interval rho = sqrt(sqr(terminal[5]) + sqr(terminal[6]));
    const interval radial_speed =
        (terminal[5] * terminal[7] + terminal[6] * terminal[8]) / rho;
    const interval pair_mass = terminal[10] + terminal[11];
    const interval total_mass = pair_mass + interval(1.0);
    const interval eta(4.0);
    const interval binary_radius_bound = pair_mass / eta;
    const interval separation_margin = rho - binary_radius_bound;
    const interval radial_margin =
        sqr(radial_speed) / interval(2.0) - total_mass / separation_margin;
    if (!(separation_margin.leftBound() > 1.0)) {
      throw std::runtime_error("terminal separation margin <= 1");
    }
    if (!(radial_speed.leftBound() > 2.0)) {
      throw std::runtime_error("terminal outward speed <= 2");
    }
    if (!(radial_margin.leftBound() > 0.05)) {
      throw std::runtime_error("terminal radial energy margin <= 1/20");
    }
    const interval speed_floor = sqrt(interval(2.0) * radial_margin);
    const interval tidal_allowance =
        sqrt(interval(2.0) * pair_mass * binary_radius_bound) /
        (speed_floor * sqr(separation_margin));
    const interval inner_margin = -eta - terminal[4] - tidal_allowance;
    if (!(inner_margin.leftBound() > 2.0)) {
      throw std::runtime_error("terminal inner energy margin <= 2");
    }
    if (!(terminal[0].leftBound() > 0.005)) {
      throw std::runtime_error("fixed terminal point may be a selected collision");
    }

    std::cout << std::hexfloat
              << "PASS_ISOSCELES_REGULARIZED_ESCAPE"
              << " method=CAPD-6.1.0-native"
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
              << " steps=" << steps
              << " minimum_other_squared_hex=" << minimum_other_squared
              << " minimum_brake_residual_squared_hex="
              << minimum_brake_residual_squared
              << " interface_Gy_hex=[" << interface_gy.leftBound() << ","
              << interface_gy.rightBound() << "]"
              << " wr_hex=[" << terminal[0].leftBound() << ","
              << terminal[0].rightBound() << "]"
              << " terminal_radius_hex=[" << terminal_radius.leftBound()
              << "," << terminal_radius.rightBound() << "]"
              << " physical_time_hex=[" << terminal[9].leftBound() << ","
              << terminal[9].rightBound() << "]"
              << " rho_hex=[" << rho.leftBound() << ","
              << rho.rightBound() << "]"
              << " radial_speed_hex=[" << radial_speed.leftBound() << ","
              << radial_speed.rightBound() << "]"
              << " pair_energy_hex=[" << terminal[4].leftBound() << ","
              << terminal[4].rightBound() << "]"
              << " separation_margin_hex=["
              << separation_margin.leftBound() << ","
              << separation_margin.rightBound() << "]"
              << " radial_margin_hex=[" << radial_margin.leftBound() << ","
              << radial_margin.rightBound() << "]"
              << " tidal_allowance_hex=[" << tidal_allowance.leftBound()
              << "," << tidal_allowance.rightBound() << "]"
              << " inner_margin_hex=[" << inner_margin.leftBound() << ","
              << inner_margin.rightBound() << "]"
              << " rational_margins=interface_Gy>1/10,"
                 "other_squared>1/500,"
                 "brake_residual_squared>2,"
                 "wr>1/200,separation>1,radial_speed>2,"
                 "radial_margin>1/20,inner_margin>2\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "ERROR " << error.what() << "\n";
    return 2;
  }
}
