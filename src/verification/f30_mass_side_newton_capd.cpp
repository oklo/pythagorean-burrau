// Validated interval-Newton enclosure of the nearby Li--Liao F30
// mass--side-tied periodic brake candidate.
//
// Unknowns are (wr0,wi0,S,m1,m2). Here g=q3-q2=w^2 is regularized
// globally, dt/dsigma=|w|^2, and S is the regularized half-duration. The
// five equations are the chart-native brake residual (zr,zi,G dot P) at
// sigma=S and r23=m1, r31=m2 at the initial brake. The Pythagorean equation is not
// imposed: its interval at the unique root is the decisive output.
//
// A global pair-{2,3} Levi--Civita chart avoids repeated graph overwrites and
// preserves one C1 parameter set through every close 2--3 passage.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "capd/mpcapdlib.h"

namespace {

using C1Set = capd::MpC1Rect2Set;
using C0Set = capd::MpC0TripletonSet;
using IMap = capd::MpIMap;
using IMatrix = capd::MpIMatrix;
using IOdeSolver = capd::MpIOdeSolver;
using ITimeMap = capd::MpITimeMap;
using IVector = capd::MpIVector;
using interval = capd::MpInterval;

interval exact(const char* digits) { return interval(digits, digits); }

interval symmetric(const char* radius) {
  const interval r = exact(radius);
  return interval(-r.rightBound(), r.rightBound());
}

double width_double(const interval& value) {
  return toDouble(value.rightBound() - value.leftBound());
}

interval square(const interval& value) { return sqr(value); }

// State: (w,z,h,G,P,tp,a,b,S), with complex pairs written real then imag.
// The selected relative vector is g=q3-q2=w^2. The complement is
// G=q1-C23, where C23=(b q2+q3)/(b+1), and P=dG/dt.
IMap make_scaled_global_lc_field() {
  const std::string r = "(wr^2+wi^2)";
  const std::string gx = "(wr^2-wi^2)";
  const std::string gy = "(2*wr*wi)";
  const std::string pair = "(b+1)";
  const std::string total = "(a+b+1)";
  const std::string d12x = "(Gx+" + gx + "/" + pair + ")";
  const std::string d12y = "(Gy+" + gy + "/" + pair + ")";
  const std::string d13x = "(Gx-b*" + gx + "/" + pair + ")";
  const std::string d13y = "(Gy-b*" + gy + "/" + pair + ")";
  const std::string r12sq = "(" + d12x + "^2+" + d12y + "^2)";
  const std::string r13sq = "(" + d13x + "^2+" + d13y + "^2)";
  const std::string r12cube = "(" + r12sq + "*sqrt(" + r12sq + "))";
  const std::string r13cube = "(" + r13sq + "*sqrt(" + r13sq + "))";
  const std::string fx =
      "(a*(" + d13x + "/" + r13cube + "-" + d12x + "/" +
      r12cube + "))";
  const std::string fy =
      "(a*(" + d13y + "/" + r13cube + "-" + d12y + "/" +
      r12cube + "))";
  const std::string gddx =
      "(-" + total + "/" + pair + "*(b*" + d12x + "/" + r12cube +
      "+" + d13x + "/" + r13cube + "))";
  const std::string gddy =
      "(-" + total + "/" + pair + "*(b*" + d12y + "/" + r12cube +
      "+" + d13y + "/" + r13cube + "))";

  return IMap(
      "var:wr,wi,zr,zi,h,Gx,Gy,Px,Py,tp,a,b,S;"
      "fun:"
      "S*zr,S*zi,"
      "S*((h/2)*wr+(" + r + "/2)*(wr*" + fx + "+wi*" + fy + ")),"
      "S*((h/2)*wi+(" + r + "/2)*(wr*" + fy + "-wi*" + fx + ")),"
      "S*2*((wr*zr-wi*zi)*" + fx + "+(wr*zi+wi*zr)*" + fy + "),"
      "S*" + r + "*Px,S*" + r + "*Py,"
      "S*" + r + "*" + gddx + ",S*" + r + "*" + gddy + ","
      "S*" + r + ",0,0,0;");
}

IMap make_lc_brake_map() {
  // The exact flow has zero total angular momentum.  If z=0, the selected
  // pair is instantaneously at rest and angular momentum gives G cross P=0.
  // Thus G dot P=0 forces P=0 whenever G is nonzero.  The endpoint audit
  // below proves that chart condition over the whole Newton box.
  return IMap(
      "var:wr,wi,zr,zi,h,Gx,Gy,Px,Py,tp,a,b,S;"
      "fun:zr,zi,Gx*Px+Gy*Py;");
}

IVector candidate_center() {
  IVector p(5);
  p[0] = exact("0.34592828233767692");
  p[1] = exact("0.68930781951890674");
  p[2] = exact("21.091601754059013");
  p[3] = exact("0.59481164657100516");
  p[4] = exact("0.80177497331787684");
  return p;
}

IVector candidate_box(const IVector& center, const char* radius) {
  IVector box(center);
  const interval r = symmetric(radius);
  for (int i = 0; i < 5; ++i) box[i] += r;
  return box;
}

IVector initial_state(const IVector& p) {
  const interval w2 = square(p[0]) + square(p[1]);
  const interval gx = square(p[0]) - square(p[1]);
  const interval gy = 2 * p[0] * p[1];
  const interval pair = p[4] + 1;
  IVector initial(13);
  initial[0] = p[0];
  initial[1] = p[1];
  initial[2] = interval(0);
  initial[3] = interval(0);
  initial[4] = -pair / w2;
  initial[5] = (-p[4] - 1 - gx) / pair;
  initial[6] = -gy / pair;
  initial[7] = interval(0);
  initial[8] = interval(0);
  initial[9] = interval(0);
  initial[10] = p[3];
  initial[11] = p[4];
  initial[12] = p[2];
  return initial;
}

IMatrix initial_parameter_tangent(const IVector& p) {
  IMatrix tangent(13, 5);
  for (int row = 0; row < 13; ++row)
    for (int column = 0; column < 5; ++column)
      tangent[row][column] = interval(0);

  const interval w2 = square(p[0]) + square(p[1]);
  const interval w2_squared = square(w2);
  const interval pair = p[4] + 1;
  const interval pair_squared = square(pair);
  const interval gx = square(p[0]) - square(p[1]);
  const interval gy = 2 * p[0] * p[1];

  tangent[0][0] = interval(1);
  tangent[1][1] = interval(1);
  tangent[4][0] = 2 * pair * p[0] / w2_squared;
  tangent[4][1] = 2 * pair * p[1] / w2_squared;
  tangent[4][4] = -1 / w2;
  tangent[5][0] = -2 * p[0] / pair;
  tangent[5][1] = 2 * p[1] / pair;
  tangent[5][4] = gx / pair_squared;
  tangent[6][0] = -2 * p[1] / pair;
  tangent[6][1] = -2 * p[0] / pair;
  tangent[6][4] = gy / pair_squared;
  tangent[10][3] = interval(1);
  tangent[11][4] = interval(1);
  tangent[12][2] = interval(1);
  return tangent;
}

struct Evaluation {
  IVector residual;
  IMatrix jacobian;
  IVector final_state;
  interval minimum_separation_squared;
  long steps;
};

struct CenterEvaluation {
  IVector residual;
  IVector final_state;
  interval minimum_separation_squared;
  long steps;
};

interval separation_lower_bound(const IVector& enclosure) {
  const interval r23 = square(enclosure[0]) + square(enclosure[1]);
  const interval gx = square(enclosure[0]) - square(enclosure[1]);
  const interval gy = 2 * enclosure[0] * enclosure[1];
  const interval pair = enclosure[11] + 1;
  const interval d12x = enclosure[5] + gx / pair;
  const interval d12y = enclosure[6] + gy / pair;
  const interval d13x = enclosure[5] - enclosure[11] * gx / pair;
  const interval d13y = enclosure[6] - enclosure[11] * gy / pair;
  const interval r12_squared = square(d12x) + square(d12y);
  const interval r13_squared = square(d13x) + square(d13y);
  const interval r23_squared = square(r23);
  if (!(r12_squared.leftBound() > 0 && r13_squared.leftBound() > 0 &&
        r23_squared.leftBound() > 0)) {
    std::cerr << "F30_COLLISION_AUDIT r12sq=" << r12_squared
              << " r13sq=" << r13_squared << " r23sq=" << r23_squared
              << "\n";
    throw std::runtime_error("global LC flow did not exclude collision");
  }
  const auto lower = std::min(
      r12_squared.leftBound(),
      std::min(r13_squared.leftBound(), r23_squared.leftBound()));
  return interval(lower, lower);
}

IVector residual_at(const IVector& p, const IVector& final_state) {
  IMap residual_map = make_lc_brake_map();
  const IVector brake = residual_map(final_state);
  IVector residual(5);
  for (int row = 0; row < 3; ++row) residual[row] = brake[row];
  const interval w2 = square(p[0]) + square(p[1]);
  const interval gx = square(p[0]) - square(p[1]);
  const interval gy = 2 * p[0] * p[1];
  residual[3] = w2 - p[3];
  residual[4] = sqrt(square(gx + 1) + square(gy)) - p[4];
  return residual;
}

CenterEvaluation evaluate_center(const IVector& p, double tolerance,
                                 int order, const interval& maximum_step) {
  C0Set set(initial_state(p));
  IMap field = make_scaled_global_lc_field();
  IOdeSolver solver(field, order);
  solver.setAbsoluteTolerance(tolerance);
  solver.setRelativeTolerance(tolerance);
  solver.setMaxStep(maximum_step);

  interval minimum_squared(1000000);
  long steps = 0;
  const interval target(1);
  const interval direct_cutoff = target - maximum_step;
  while (set.getCurrentTime().rightBound() < direct_cutoff.leftBound()) {
    solver.setMaxStep(maximum_step);
    set.move(solver);
    ++steps;
    const interval lower = separation_lower_bound(set.getLastEnclosure());
    if (lower < minimum_squared) minimum_squared = lower;
    if (steps % 100 == 0)
      std::cerr << "F30_CENTER_PROGRESS steps=" << steps
                << " scaled_time=" << set.getCurrentTime()
                << " minimum_separation_squared=" << minimum_squared << "\n";
  }
  ITimeMap time_map(solver);
  time_map.stopAfterStep(true);
  do {
    time_map(target, set);
    ++steps;
    const interval lower = separation_lower_bound(set.getLastEnclosure());
    if (lower < minimum_squared) minimum_squared = lower;
  } while (!time_map.completed());

  const IVector final_state = static_cast<IVector>(set);
  return {residual_at(p, final_state), final_state, minimum_squared, steps};
}

Evaluation evaluate(const IVector& p, double tolerance, int order,
                    const interval& maximum_step) {
  C1Set set(initial_state(p));
  IMap field = make_scaled_global_lc_field();
  IOdeSolver solver(field, order);
  solver.setAbsoluteTolerance(tolerance);
  solver.setRelativeTolerance(tolerance);
  solver.setMaxStep(maximum_step);

  interval minimum_squared(1000000);
  long steps = 0;
  const interval target(1);
  const interval direct_cutoff = target - maximum_step;
  while (set.getCurrentTime().rightBound() < direct_cutoff.leftBound()) {
    solver.setMaxStep(maximum_step);
    set.move(solver);
    ++steps;
    const interval lower = separation_lower_bound(set.getLastEnclosure());
    if (lower < minimum_squared) minimum_squared = lower;
    if (steps % 100 == 0)
      std::cerr << "F30_C1_PROGRESS steps=" << steps
                << " scaled_time=" << set.getCurrentTime()
                << " minimum_separation_squared=" << minimum_squared << "\n";
  }
  ITimeMap time_map(solver);
  time_map.stopAfterStep(true);
  do {
    time_map(target, set);
    ++steps;
    const interval lower = separation_lower_bound(set.getLastEnclosure());
    if (lower < minimum_squared) minimum_squared = lower;
  } while (!time_map.completed());

  const IVector final_state = static_cast<IVector>(set);
  const IMatrix flow_derivative = static_cast<IMatrix>(set);
  const IMatrix parameter_tangent =
      flow_derivative * initial_parameter_tangent(p);
  IMap residual_map = make_lc_brake_map();
  const IMatrix brake_parameter_derivative =
      residual_map.derivative(final_state) * parameter_tangent;

  const IVector residual = residual_at(p, final_state);
  IMatrix jacobian(5, 5);
  for (int row = 0; row < 3; ++row)
    for (int column = 0; column < 5; ++column)
      jacobian[row][column] = brake_parameter_derivative[row][column];

  const interval gx = square(p[0]) - square(p[1]);
  const interval gy = 2 * p[0] * p[1];
  const interval r31 = sqrt(square(gx + 1) + square(gy));
  for (int column = 0; column < 5; ++column) {
    jacobian[3][column] = interval(0);
    jacobian[4][column] = interval(0);
  }
  jacobian[3][0] = 2 * p[0];
  jacobian[3][1] = 2 * p[1];
  jacobian[3][3] = interval(-1);
  jacobian[4][0] = ((gx + 1) * 2 * p[0] + gy * 2 * p[1]) / r31;
  jacobian[4][1] = (-(gx + 1) * 2 * p[1] + gy * 2 * p[0]) / r31;
  jacobian[4][4] = interval(-1);
  return {residual, jacobian, final_state, minimum_squared, steps};
}

double maximum_width(const IVector& vector) {
  double result = 0;
  for (int i = 0; i < vector.dimension(); ++i)
    result = std::max(result, width_double(vector[i]));
  return result;
}

IVector krawczyk_image(const IVector& center, const IVector& box,
                       const IVector& center_residual,
                       const IMatrix& box_jacobian) {
  // A point inverse of mid(DF(box)) is only a preconditioner; every operation
  // in the displayed Krawczyk image remains interval arithmetic.
  const IMatrix midpoint_jacobian = capd::vectalg::midMatrix(box_jacobian);
  const IMatrix preconditioner =
      capd::matrixAlgorithms::inverseMatrix(midpoint_jacobian);
  const IMatrix identity = IMatrix::Identity(5);
  return center - preconditioner * center_residual +
         (identity - preconditioner * box_jacobian) * (box - center);
}

}  // namespace

int main(int argc, char** argv) {
  const int precision = argc > 1 ? std::atoi(argv[1]) : 512;
  const double tolerance = argc > 2 ? std::atof(argv[2]) : 1e-60;
  const int order = argc > 3 ? std::atoi(argv[3]) : 50;
  const char* radius = argc > 4 ? argv[4] : "1e-7";
  const interval maximum_step = argc > 5 ? exact(argv[5]) : exact("1e-3");
  capd::MpFloat::setDefaultPrecision(precision);
  std::cout << std::setprecision(18);
  try {
    const IVector center = candidate_center();
    const IVector box = candidate_box(center, radius);
    const CenterEvaluation center_evaluation =
        evaluate_center(center, tolerance, order, maximum_step);
    std::cerr << "F30_CENTER residual=" << center_evaluation.residual
              << " final_state=" << center_evaluation.final_state
              << " physical_half_time=" << center_evaluation.final_state[9]
              << " min_separation_squared="
              << center_evaluation.minimum_separation_squared
              << " steps=" << center_evaluation.steps << "\n";
    if (std::getenv("F30_CENTER_ONLY") != nullptr) {
      std::cout << "PASS_F30_CENTER_SEGMENT\n";
      return 0;
    }
    const Evaluation box_evaluation =
        evaluate(box, tolerance, order, maximum_step);
    const IVector newton =
        center - capd::matrixAlgorithms::gauss(
                     box_evaluation.jacobian, center_evaluation.residual);
    const IVector krawczyk =
        krawczyk_image(center, box, center_evaluation.residual,
                       box_evaluation.jacobian);
    const bool newton_inclusion = capd::vectalg::subsetInterior(newton, box);
    const bool krawczyk_inclusion =
        capd::vectalg::subsetInterior(krawczyk, box);
    const bool inclusion = newton_inclusion || krawczyk_inclusion;
    const IVector& root_enclosure =
        newton_inclusion ? newton : krawczyk;
    const interval complement_squared =
        square(box_evaluation.final_state[5]) +
        square(box_evaluation.final_state[6]);
    const interval pythagorean_defect =
        root_enclosure[3] * root_enclosure[3] +
        root_enclosure[4] * root_enclosure[4] - interval(1);

    std::cout << "F30_MASS_SIDE_NEWTON"
              << " center=" << center
              << " box=" << box
              << " center_residual=" << center_evaluation.residual
              << " jacobian=" << box_evaluation.jacobian
              << " newton=" << newton
              << " krawczyk=" << krawczyk
              << " newton_inclusion=" << newton_inclusion
              << " krawczyk_inclusion=" << krawczyk_inclusion
              << " root_enclosure=" << root_enclosure
              << " pythagorean_defect=" << pythagorean_defect
              << " min_separation_squared="
              << box_evaluation.minimum_separation_squared
              << " center_steps=" << center_evaluation.steps
              << " box_steps=" << box_evaluation.steps
              << " physical_half_time=" << box_evaluation.final_state[9]
              << " endpoint_complement_squared=" << complement_squared
              << " final_hull_width="
              << maximum_width(box_evaluation.final_state) << "\n";
    if (!inclusion)
      throw std::runtime_error("interval Newton inclusion failed");
    if (!(complement_squared.leftBound() > 0))
      throw std::runtime_error("endpoint LC brake chart allowed G=0");
    if (!(pythagorean_defect.rightBound() < 0))
      throw std::runtime_error(
          "validated mass--side root was not separated from Pythagorean locus");
    std::cout << "PASS_F30_MASS_SIDE_NONPYTHAGOREAN\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FAIL " << error.what() << "\n";
    return 1;
  }
}
