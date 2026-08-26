// Deterministic regression probe for CAPD's quadratic coefficient convention
// and C2 Poincare return-time derivatives.
//
// Dependency pin: CAPD 6.1.0, commit
// 731079217a9254ea2948d742df2b170895effe7f, MP build.

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "capd/mpcapdlib.h"

namespace {

using Ival = capd::MpInterval;
using Map = capd::MpIMap;
using Vector = capd::MpIVector;
using Matrix = capd::MpIMatrix;
using Hessian = capd::MpIHessian;
using C2Set = capd::MpC2Rect2Set;
using C2Solver = capd::MpIC2OdeSolver;
using Section = capd::MpICoordinateSection;
using C2PoincareMap = capd::MpIC2PoincareMap;

std::string interval_string(const Ival& value) {
  std::ostringstream stream;
  stream << value;
  return stream.str();
}

void require_subset(const Ival& expected, const Ival& enclosure,
                    const std::string& label) {
  if (!expected.subset(enclosure)) {
    throw std::runtime_error(label + ": expected " +
                             interval_string(expected) +
                             " not contained in " + interval_string(enclosure));
  }
}

void require_zero(const Ival& enclosure, const std::string& label) {
  require_subset(Ival(0), enclosure, label);
}

void test_static_map_coefficients() {
  // f_0=x^2+xy, f_1=y^2.  CAPD stores the homogeneous Taylor
  // coefficients H_xx=1, H_xy=1, H_yy=0 for f_0, not the symmetric
  // matrix entries (2,1;1,0) of the ordinary Hessian.
  Map map("var:x,y;fun:x^2+x*y,y^2;");
  map.setDegree(2);
  Vector x(2);
  x[0] = Ival(2);
  x[1] = Ival(3);
  Matrix derivative(2, 2);
  Hessian quadratic(2, 2);
  const Vector image = map(x, derivative, quadratic);

  require_subset(Ival(10), image[0], "static image f0");
  require_subset(Ival(9), image[1], "static image f1");
  require_subset(Ival(7), derivative[0][0], "static Df00");
  require_subset(Ival(2), derivative[0][1], "static Df01");
  require_zero(derivative[1][0], "static Df10");
  require_subset(Ival(6), derivative[1][1], "static Df11");

  require_subset(Ival(1), quadratic(0, 0, 0), "static H0xx");
  require_subset(Ival(1), quadratic(0, 0, 1), "static H0xy");
  require_zero(quadratic(0, 1, 1), "static H0yy");
  require_zero(quadratic(1, 0, 0), "static H1xx");
  require_zero(quadratic(1, 0, 1), "static H1xy");
  require_subset(Ival(1), quadratic(1, 1, 1), "static H1yy");

  // For v=(1,1), the correct homogeneous evaluation is Hxx+Hxy+Hyy=2.
  // Treating the stored mixed entry as both Hxy and Hyx would instead give
  // 3, an explicit regression witness for the forbidden full double sum.
  const Ival correct = quadratic(0, 0, 0) + quadratic(0, 0, 1) +
                       quadratic(0, 1, 1);
  const Ival wrong_symmetric = quadratic(0, 0, 0) +
                               2 * quadratic(0, 0, 1) +
                               quadratic(0, 1, 1);
  require_subset(Ival(2), correct, "static homogeneous evaluation");
  if (wrong_symmetric.contains(Ival(2))) {
    throw std::runtime_error("forbidden symmetric double sum was not detected");
  }
}

void test_fiber_dependent_poincare_map() {
  // x'=1, y'=y, with section x=1.  Starting from (x0,y0),
  //
  //   tau=1-x0,  P(x0,y0)=(1,y0 exp(1-x0)).
  //
  // At (0,2), with e=exp(1), the exact derivatives are
  //
  //   DP = [[0,0],[-2e,e]],
  //
  // and CAPD's normalized quadratic coefficients in the second output are
  // H_xx=e, H_xy=-e, H_yy=0.  The nonzero x0 derivatives arise entirely
  // from the fiber-dependent return time.
  Map field("var:x,y;fun:1,y;");
  C2Solver solver(field, 20);
  solver.setAbsoluteTolerance(1e-30);
  solver.setRelativeTolerance(1e-30);
  Section section(2, 0, Ival(1));
  C2PoincareMap poincare(solver, section, capd::poincare::MinusPlus);
  poincare.setMaxReturnTime(2.0);

  Vector initial(2);
  initial[0] = Ival(0);
  initial[1] = Ival(2);
  C2Set set(initial);
  Matrix flow_derivative(2, 2), section_derivative(2, 2);
  Hessian flow_quadratic(2, 2), section_quadratic(2, 2);
  Ival return_time;
  const Vector image =
      poincare(set, flow_derivative, flow_quadratic, return_time);
  poincare.computeDP(image, flow_derivative, flow_quadratic,
                     section_derivative, section_quadratic, return_time);

  const Ival e = exp(Ival(1));
  require_subset(Ival(1), return_time, "Poincare return time");
  require_subset(Ival(1), image[0], "Poincare section coordinate");
  require_subset(2 * e, image[1], "Poincare image y");

  require_zero(section_derivative[0][0], "Poincare DP00");
  require_zero(section_derivative[0][1], "Poincare DP01");
  require_subset(-2 * e, section_derivative[1][0], "Poincare DP10");
  require_subset(e, section_derivative[1][1], "Poincare DP11");

  require_zero(section_quadratic(0, 0, 0), "Poincare H0xx");
  require_zero(section_quadratic(0, 0, 1), "Poincare H0xy");
  require_zero(section_quadratic(0, 1, 1), "Poincare H0yy");
  require_subset(e, section_quadratic(1, 0, 0), "Poincare H1xx");
  require_subset(-e, section_quadratic(1, 0, 1), "Poincare H1xy");
  require_zero(section_quadratic(1, 1, 1), "Poincare H1yy");
}

void test_masked_directional_composition() {
  // Use the same exact Poincare map, but initialize CAPD's formal coordinate
  // xi with the nonlinear state jet
  //
  //   (x0,y0)=(0,2)+(1,3)xi+(0,4)xi^2.
  //
  // Then P_y=(2+3xi+4xi^2)exp(1-xi), whose derivative and normalized
  // quadratic coefficient at zero are e and 2e.  This tests both custom
  // initial C1/C2 data and a mask retaining only the xi^2 coefficient.
  Map field("var:x,y;fun:1,y;");
  C2Solver solver(field, 20);
  solver.setAbsoluteTolerance(1e-30);
  solver.setRelativeTolerance(1e-30);
  using Multiindex = capd::vectalg::Multiindex;
  Multiindex retained{2, 0};
  solver.setMask(static_cast<Multiindex*>(nullptr),
                 static_cast<Multiindex*>(nullptr));
  solver.addMultiindexToMask({1, 0});
  solver.addMultiindexToMask({0, 1});
  solver.addMultiindexToMask(retained);
  Section section(2, 0, Ival(1));
  C2PoincareMap poincare(solver, section, capd::poincare::MinusPlus);
  poincare.setMaxReturnTime(2.0);

  Vector initial(2);
  initial[0] = Ival(0);
  initial[1] = Ival(2);
  Matrix initial_derivative(2, 2);
  initial_derivative[0][0] = Ival(1);
  initial_derivative[1][0] = Ival(3);
  Hessian initial_quadratic(2, 2);
  initial_quadratic(1, 0, 0) = Ival(4);
  C2Set::C0BaseSet c0(initial);
  C2Set::C1BaseSet c1(initial_derivative);
  C2Set set(c0, c1, initial_quadratic);

  Matrix flow_derivative(2, 2), section_derivative(2, 2);
  Hessian flow_quadratic(2, 2), section_quadratic(2, 2);
  Ival return_time;
  const Vector image =
      poincare(set, flow_derivative, flow_quadratic, return_time);
  poincare.computeDP(image, flow_derivative, flow_quadratic,
                     section_derivative, section_quadratic, return_time);

  const Ival e = exp(Ival(1));
  require_subset(e, section_derivative[1][0],
                 "masked composed tangent");
  require_subset(2 * e, section_quadratic(1, 0, 0),
                 "masked composed curvature");
  require_zero(section_derivative[0][0],
               "masked exact section tangent");
  require_zero(section_quadratic(0, 0, 0),
               "masked exact section curvature");
}

}  // namespace

int main(int argc, char** argv) {
  const int precision = argc > 1 ? std::atoi(argv[1]) : 160;
  capd::MpFloat::setDefaultPrecision(precision);
  try {
    test_static_map_coefficients();
    test_fiber_dependent_poincare_map();
    test_masked_directional_composition();
    std::cout << "PASS_CAPD_C2_SEMANTICS precision_bits=" << precision
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FAIL_CAPD_C2_SEMANTICS " << error.what() << "\n";
    return 1;
  }
}
