// Rigorous transverse unfolding of the isosceles base-pair collision.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
//
// The selected pair is (1,2), with g=q2-q1=w^2 and complement
// G=q3-C12.  The exact endpoint collision is the transverse section wr=0.
// A C1 Poincare map propagates the tied launch tangent and proves wi_v<0
// at that section.  This is the normal coefficient which unfolds the binary
// collision into a collision-free near miss.

#include <iomanip>
#include <iostream>
#include <stdexcept>

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

    INonlinearSection section(
        "var:wr,wi,zr,zi,h,Gx,Gy,Px,Py,tp,m,n;fun:wr;");
    IPoincareMap poincare_map(solver, section, poincare::PlusMinus);

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

    C1Rect2Set set(initial);
    IMatrix flow_derivative(12, 12);
    interval return_time;
    const IVector image = poincare_map(set, flow_derivative, return_time);
    const IMatrix section_derivative =
        poincare_map.computeDP(image, flow_derivative, return_time);

    IVector launch_tangent(12);
    for (int index = 0; index < 12; ++index) {
      launch_tangent[index] = interval(0.0);
    }
    launch_tangent[5] = interval(1.0) / (interval(2.0) * sqrt(interval(2.0)));
    launch_tangent[10] = -interval(1.0) / interval(2.0);
    launch_tangent[11] = interval(1.0) / interval(2.0);
    const IVector event_tangent = section_derivative * launch_tangent;

    if (!(image[2].rightBound() < -0.8)) {
      throw std::runtime_error("base collision is not transverse");
    }
    if (!(event_tangent[1].rightBound() < -30.0)) {
      throw std::runtime_error("normal collision-unfolding coefficient failed");
    }
    const interval selected_radius = sqr(image[0]) + sqr(image[1]);
    const interval selected_x = sqr(image[0]) - sqr(image[1]);
    const interval selected_y = interval(2.0) * image[0] * image[1];
    const interval pair_value = image[10] + image[11];
    const interval d31x_image =
        image[5] + image[11] * selected_x / pair_value;
    const interval d31y_image =
        image[6] + image[11] * selected_y / pair_value;
    const interval d23x_image =
        image[5] - image[10] * selected_x / pair_value;
    const interval d23y_image =
        image[6] - image[10] * selected_y / pair_value;
    const interval r31_squared_image =
        sqr(d31x_image) + sqr(d31y_image);
    const interval r23_squared_image =
        sqr(d23x_image) + sqr(d23y_image);
    if (!(r31_squared_image.leftBound() > 0.002)
        || !(r23_squared_image.leftBound() > 0.002)) {
      throw std::runtime_error("unselected separation at collision is too small");
    }

    std::cout << std::hexfloat
              << "PASS_ISOSCELES_BASE_COLLISION_VARIATION"
              << " method=CAPD-6.1.0-native"
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
              << " return_time_hex=[" << return_time.leftBound() << ","
              << return_time.rightBound() << "]"
              << " physical_time_hex=[" << image[9].leftBound() << ","
              << image[9].rightBound() << "]"
              << " zr_hex=[" << image[2].leftBound() << ","
              << image[2].rightBound() << "]"
              << " wi_v_hex=[" << event_tangent[1].leftBound() << ","
              << event_tangent[1].rightBound() << "]"
              << " zi_v_hex=[" << event_tangent[3].leftBound() << ","
              << event_tangent[3].rightBound() << "]"
              << " Gx_v_hex=[" << event_tangent[5].leftBound() << ","
              << event_tangent[5].rightBound() << "]"
              << " selected_radius_hex=[" << selected_radius.leftBound() << ","
              << selected_radius.rightBound() << "]"
              << " r31_squared_hex=[" << r31_squared_image.leftBound() << ","
              << r31_squared_image.rightBound() << "]"
              << " r23_squared_hex=[" << r23_squared_image.leftBound() << ","
              << r23_squared_image.rightBound() << "]"
              << " rational_normal_upper=-30"
              << " rational_transverse_upper=-4/5"
              << " rational_other_squared_lower=1/500\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "ERROR " << error.what() << "\n";
    return 2;
  }
}
