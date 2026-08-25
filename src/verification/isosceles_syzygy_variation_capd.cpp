// Rigorous symmetry-breaking derivative at the isosceles first syzygy.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
//
// The independent variables m1,m2 are frozen state coordinates.  The
// derivative tangent of the tied family at v=1 is
//
//   (m1_v,m2_v,q3x_v)=(-1/2,1/2,1/sqrt(2)).
//
// A C1 Poincare map to signed area zero supplies the event-corrected tangent.
// If q=r31/r12 and z=q(m1+m2)/m2, then lambda=z_v at v=1.  Proving lambda>0
// proves z(v)<1 for v<1 sufficiently close to one, i.e. the continued first
// syzygy lies on the torque-compatible side of the ordered syzygy face.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "capd/capdlib.h"

int main() {
  using namespace capd;

  try {
    IMap field(
        "var:m1,m2,x1,y1,x2,y2,x3,y3,vx1,vy1,vx2,vy2,vx3,vy3;"
        "fun:0,0,"
        "vx1,vy1,vx2,vy2,vx3,vy3,"
        "m2*(x2-x1)/(((x2-x1)^2+(y2-y1)^2)*sqrt((x2-x1)^2+(y2-y1)^2))"
        "+(x3-x1)/(((x3-x1)^2+(y3-y1)^2)*sqrt((x3-x1)^2+(y3-y1)^2)),"
        "m2*(y2-y1)/(((x2-x1)^2+(y2-y1)^2)*sqrt((x2-x1)^2+(y2-y1)^2))"
        "+(y3-y1)/(((x3-x1)^2+(y3-y1)^2)*sqrt((x3-x1)^2+(y3-y1)^2)),"
        "m1*(x1-x2)/(((x2-x1)^2+(y2-y1)^2)*sqrt((x2-x1)^2+(y2-y1)^2))"
        "+(x3-x2)/(((x3-x2)^2+(y3-y2)^2)*sqrt((x3-x2)^2+(y3-y2)^2)),"
        "m1*(y1-y2)/(((x2-x1)^2+(y2-y1)^2)*sqrt((x2-x1)^2+(y2-y1)^2))"
        "+(y3-y2)/(((x3-x2)^2+(y3-y2)^2)*sqrt((x3-x2)^2+(y3-y2)^2)),"
        "m1*(x1-x3)/(((x3-x1)^2+(y3-y1)^2)*sqrt((x3-x1)^2+(y3-y1)^2))"
        "+m2*(x2-x3)/(((x3-x2)^2+(y3-y2)^2)*sqrt((x3-x2)^2+(y3-y2)^2)),"
        "m1*(y1-y3)/(((x3-x1)^2+(y3-y1)^2)*sqrt((x3-x1)^2+(y3-y1)^2))"
        "+m2*(y2-y3)/(((x3-x2)^2+(y3-y2)^2)*sqrt((x3-x2)^2+(y3-y2)^2));");

    IOdeSolver solver(field, 24);
    solver.setAbsoluteTolerance(1e-14);
    solver.setRelativeTolerance(1e-14);

    INonlinearSection section(
        "var:m1,m2,x1,y1,x2,y2,x3,y3,vx1,vy1,vx2,vy2,vx3,vy3;"
        "fun:(x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);");
    IPoincareMap poincare_map(solver, section, poincare::PlusMinus);

    const interval endpoint_mass = interval(1.0) / sqrt(interval(2.0));
    IVector initial(14);
    initial[0] = endpoint_mass;
    initial[1] = endpoint_mass;
    initial[2] = -interval(1.0) / interval(2.0);
    initial[3] = 0.0;
    initial[4] = interval(1.0) / interval(2.0);
    initial[5] = 0.0;
    initial[6] = 0.0;
    initial[7] = interval(1.0) / interval(2.0);
    for (int index = 8; index < 14; ++index) {
      initial[index] = 0.0;
    }

    C1Rect2Set set(initial);
    IMatrix flow_derivative(14, 14);
    interval return_time;
    const IVector image = poincare_map(set, flow_derivative, return_time);
    const IMatrix section_derivative =
        poincare_map.computeDP(image, flow_derivative, return_time);

    IVector launch_tangent(14);
    for (int index = 0; index < 14; ++index) {
      launch_tangent[index] = 0.0;
    }
    launch_tangent[0] = -interval(1.0) / interval(2.0);
    launch_tangent[1] = interval(1.0) / interval(2.0);
    launch_tangent[6] = endpoint_mass;
    const IVector event_tangent = section_derivative * launch_tangent;

    const interval dx12 = image[4] - image[2];
    const interval dy12 = image[5] - image[3];
    const interval dx31 = image[2] - image[6];
    const interval dy31 = image[3] - image[7];
    const interval r12 = sqrt(sqr(dx12) + sqr(dy12));
    const interval r31 = sqrt(sqr(dx31) + sqr(dy31));
    const interval dx12_v = event_tangent[4] - event_tangent[2];
    const interval dy12_v = event_tangent[5] - event_tangent[3];
    const interval dx31_v = event_tangent[2] - event_tangent[6];
    const interval dy31_v = event_tangent[3] - event_tangent[7];
    const interval r12_v =
        (dx12 * dx12_v + dy12 * dy12_v) / r12;
    const interval r31_v =
        (dx31 * dx31_v + dy31 * dy31_v) / r31;
    const interval q = r31 / r12;
    const interval q_v = (r31_v * r12 - r31 * r12_v) / sqr(r12);

    const interval mass_sum = image[0] + image[1];
    const interval mass_sum_v = event_tangent[0] + event_tangent[1];
    const interval z_v =
        q_v * mass_sum / image[1]
        + q
              * (mass_sum_v * image[1]
                 - mass_sum * event_tangent[1])
              / sqr(image[1]);
    const interval rational_lower = interval(18.0);
    if (!(z_v.leftBound() > rational_lower.rightBound())) {
      throw std::runtime_error("corner slope lower bound lambda>18 failed");
    }

    const interval area_velocity =
        (image[10] - image[8]) * (image[7] - image[3])
        + (image[4] - image[2]) * (image[13] - image[9])
        - (image[11] - image[9]) * (image[6] - image[2])
        - (image[5] - image[3]) * (image[12] - image[8]);
    if (!(area_velocity.rightBound() < 0.0)) {
      throw std::runtime_error("first-syzygy transversality failed");
    }

    std::cout << std::hexfloat
              << "PASS_ISOSCELES_SYZYGY_VARIATION"
              << " method=CAPD-6.1.0-native"
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
              << " return_time_hex=[" << return_time.leftBound() << ","
              << return_time.rightBound() << "]"
              << " q_hex=[" << q.leftBound() << "," << q.rightBound() << "]"
              << " q_v_hex=[" << q_v.leftBound() << "," << q_v.rightBound()
              << "]"
              << " lambda_hex=[" << z_v.leftBound() << ","
              << z_v.rightBound() << "]"
              << " rational_lambda_lower=18"
              << " area_velocity_hex=[" << area_velocity.leftBound() << ","
              << area_velocity.rightBound() << "]\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "ERROR " << error.what() << "\n";
    return 2;
  }
}
