// Rigorous first-order torque-contact gap on the isosceles pre-syzygy arc.
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
//
// Reflection and leg-exchange symmetry reduce the endpoint orbit and its odd
// tied-family variation to (x,h,vx,vh,c,b,vc,vb).  The scalar certified below
// is
//
//   g(t) = d/dv (eta - threshold_h) |_{v=1}.
//
// The launch quotient is handled by integral averages of a_t and a_v,t;
// the compact middle is checked directly; and the terminal tail is covered
// by g_t<0 together with the exact terminal identity g(t_syzygy)=0.

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "capd/capdlib.h"

namespace {

using capd::IVector;
using capd::interval;

struct GapQuantities {
  interval angular_momentum;
  interval angular_momentum_rate;
  interval angular_variation;
  interval angular_variation_rate;
  interval threshold_variation;
  interval gap;
  interval gap_rate;
  interval normalized_side;
  interval side_variation;
};

interval integer_power(const interval& value, int exponent) {
  interval result(1.0);
  for (int index = 0; index < exponent; ++index) {
    result *= value;
  }
  return result;
}

interval interval_hull(const interval& left, const interval& right) {
  return interval(std::min(left.leftBound(), right.leftBound()),
                  std::max(left.rightBound(), right.rightBound()));
}

GapQuantities evaluate_gap(const IVector& state, bool divide_by_momentum) {
  const interval root_two = sqrt(interval(2.0));
  const interval total_mass = interval(1.0) + root_two;
  const interval x = state[0];
  const interval height = state[1];
  const interval vx = state[2];
  const interval vh = state[3];
  const interval c = state[4];
  const interval b = state[5];
  const interval vc = state[6];
  const interval vb = state[7];

  const interval radius_squared = sqr(x) + sqr(height);
  const interval radius = sqrt(radius_squared);
  const interval radius_cubed = radius_squared * radius;
  const interval radius_fifth = sqr(radius_squared) * radius;
  const interval ax =
      -interval(1.0) / (interval(4.0) * root_two * sqr(x))
      - x / radius_cubed;
  const interval ah = -total_mass * height / radius_cubed;
  const interval cdd =
      x / radius_cubed - interval(1.0) / (interval(8.0) * sqr(x))
      + total_mass * (interval(2.0) * sqr(x) - sqr(height)) * c
            / radius_fifth
      - interval(3.0) * total_mass * height * x * b / radius_fifth;
  const interval bdd =
      -interval(3.0) * height * x * c / radius_fifth
      + ((interval(2.0) * sqr(height) - sqr(x)) / radius_fifth
         - root_two / (interval(8.0) * integer_power(x, 3)))
            * b;

  const interval angular_momentum = height * vx - x * vh;
  const interval angular_variation =
      c * vh + b * vx - x * vb - height * vc;
  const interval angular_momentum_rate = height * ax - x * ah;
  const interval angular_variation_rate =
      c * ah + b * ax - x * bdd - height * cdd;

  const interval radius_rate = (x * vx + height * vh) / radius;
  const interval normalized_side = radius / (interval(2.0) * x);
  const interval normalized_side_rate =
      radius_rate / (interval(2.0) * x)
      - radius * vx / (interval(2.0) * sqr(x));
  const interval shape_numerator = x * c - height * b;
  const interval shape_numerator_rate =
      vx * c + x * vc - vh * b - height * vb;
  const interval shape_denominator = interval(2.0) * x * radius;
  const interval shape_denominator_rate =
      interval(2.0) * (vx * radius + x * radius_rate);
  const interval side_variation = shape_numerator / shape_denominator;
  const interval side_variation_rate =
      (shape_numerator_rate * shape_denominator
       - shape_numerator * shape_denominator_rate)
      / sqr(shape_denominator);

  const interval d = normalized_side;
  const interval d2 = sqr(d);
  const interval threshold_side_coefficient =
      -interval(4.0) * (interval(2.0) * root_two * d2 + interval(1.0))
      * (interval(16.0) * integer_power(d, 5)
         - interval(5.0) * integer_power(d, 3) - interval(4.0) * d2
         + interval(2.0))
      / (d * (d - interval(1.0)) * sqr(interval(4.0) * d2 + root_two)
         * (d2 + d + interval(1.0)));
  const interval threshold_mass_term =
      -interval(2.0) / (interval(4.0) * d2 + root_two);

  const interval d3 = integer_power(d, 3);
  const interval d4 = integer_power(d, 4);
  const interval d5 = integer_power(d, 5);
  const interval d6 = integer_power(d, 6);
  const interval d7 = integer_power(d, 7);
  const interval d8 = integer_power(d, 8);
  const interval d9 = integer_power(d, 9);
  const interval d10 = integer_power(d, 10);
  const interval d12 = integer_power(d, 12);
  const interval threshold_side_derivative =
      interval(4.0)
      * (interval(128.0) * root_two * d12
         - interval(120.0) * root_two * d10
         + interval(128.0) * root_two * d9 - interval(80.0) * d8
         - interval(16.0) * root_two * d8
         + interval(96.0) * root_two * d7 + interval(288.0) * d7
         + interval(27.0) * root_two * d6 + interval(40.0) * d5
         + interval(56.0) * root_two * d5
         - interval(48.0) * root_two * d4
         - interval(2.0) * root_two * d3 - interval(32.0) * d2
         - interval(4.0) * root_two * d2 - interval(2.0) * root_two)
      / (d2 * sqr(d - interval(1.0))
         * integer_power(interval(4.0) * d2 + root_two, 3)
         * sqr(d2 + d + interval(1.0)));
  const interval threshold_mass_derivative =
      interval(16.0) * d / sqr(interval(4.0) * d2 + root_two);

  const interval threshold_variation =
      threshold_side_coefficient * side_variation + threshold_mass_term;
  const interval threshold_variation_rate =
      threshold_side_derivative * normalized_side_rate * side_variation
      + threshold_side_coefficient * side_variation_rate
      + threshold_mass_derivative * normalized_side_rate;

  interval gap;
  interval gap_rate;
  if (divide_by_momentum) {
    const interval history_variation =
        -root_two
        - interval(2.0) * angular_variation / angular_momentum;
    const interval history_variation_rate =
        -interval(2.0)
        * (angular_variation_rate * angular_momentum
           - angular_variation * angular_momentum_rate)
        / sqr(angular_momentum);
    gap = history_variation - threshold_variation;
    gap_rate = history_variation_rate - threshold_variation_rate;
  }
  return {angular_momentum,
          angular_momentum_rate,
          angular_variation,
          angular_variation_rate,
          threshold_variation,
          gap,
          gap_rate,
          normalized_side,
          side_variation};
}

void check_collision_free(const IVector& tube) {
  if (!(tube[0].leftBound() > 0.0)
      || !((sqr(tube[0]) + sqr(tube[1])).leftBound() > 0.0)) {
    throw std::runtime_error("endpoint variation tube reached collision");
  }
}

}  // namespace

int main() {
  using namespace capd;

  try {
    IMap field(
        "var:x,h,vx,vh,c,b,vc,vb;"
        "fun:vx,vh,"
        "-1/(4*sqrt(2)*x^2)-x/((x^2+h^2)*sqrt(x^2+h^2)),"
        "-(1+sqrt(2))*h/((x^2+h^2)*sqrt(x^2+h^2)),"
        "vc,vb,"
        "x/((x^2+h^2)*sqrt(x^2+h^2))-1/(8*x^2)"
        "+(1+sqrt(2))*(2*x^2-h^2)*c/((x^2+h^2)^2*sqrt(x^2+h^2))"
        "-3*(1+sqrt(2))*h*x*b/((x^2+h^2)^2*sqrt(x^2+h^2)),"
        "-3*h*x*c/((x^2+h^2)^2*sqrt(x^2+h^2))"
        "+((2*h^2-x^2)/((x^2+h^2)^2*sqrt(x^2+h^2))"
        "-sqrt(2)/(8*x^3))*b;");

    IOdeSolver solver(field, 24);
    solver.setAbsoluteTolerance(1e-15);
    solver.setRelativeTolerance(1e-15);
    solver.setStep(interval(1.0) / interval(10000.0));
    ITimeMap time_map(solver);
    time_map.stopAfterStep(true);

    IVector initial(8);
    initial[0] = interval(1.0) / interval(2.0);
    initial[1] = interval(1.0) / interval(2.0);
    initial[2] = 0.0;
    initial[3] = 0.0;
    initial[4] = interval(1.0) / sqrt(interval(2.0));
    initial[5] = 0.0;
    initial[6] = 0.0;
    initial[7] = 0.0;
    C0Rect2Set set(initial);

    const interval early_end = interval(1.0) / interval(1000.0);
    const interval tail_start = interval(43.0) / interval(100.0);
    const interval final_target = interval(943.0) / interval(2000.0);

    bool early_initialized = false;
    interval early_momentum_rate;
    interval early_variation_rate;
    interval early_threshold_variation;
    int early_steps = 0;
    do {
      time_map(early_end, set);
      ++early_steps;
      const interval step = solver.getStep();
      const interval domain = interval(0.0, 1.0) * step;
      const IVector tube = solver.getCurve()(domain);
      check_collision_free(tube);
      const GapQuantities data = evaluate_gap(tube, false);
      if (!(data.normalized_side.rightBound() < 1.0)
          || !(data.side_variation.leftBound() > 0.0)) {
        throw std::runtime_error("early ordered-cone tangent failed");
      }
      if (!early_initialized) {
        early_momentum_rate = data.angular_momentum_rate;
        early_variation_rate = data.angular_variation_rate;
        early_threshold_variation = data.threshold_variation;
        early_initialized = true;
      } else {
        early_momentum_rate =
            interval_hull(early_momentum_rate, data.angular_momentum_rate);
        early_variation_rate =
            interval_hull(early_variation_rate, data.angular_variation_rate);
        early_threshold_variation = interval_hull(
            early_threshold_variation, data.threshold_variation);
      }
    } while (!time_map.completed());

    if (!(early_momentum_rate.leftBound() > 0.0)) {
      throw std::runtime_error("early angular-momentum rate is not positive");
    }
    const interval early_history_variation =
        -sqrt(interval(2.0))
        - interval(2.0) * early_variation_rate / early_momentum_rate;
    const interval early_gap =
        early_history_variation - early_threshold_variation;
    if (!(early_gap.leftBound() > 0.0)) {
      throw std::runtime_error("early averaged contact-gap bound failed");
    }

    int middle_steps = 0;
    double middle_gap_lower = early_gap.leftBound();
    double side_variation_lower = 1e300;
    double normalized_side_upper = -1e300;
    do {
      time_map(tail_start, set);
      ++middle_steps;
      const interval step = solver.getStep();
      const interval domain = interval(0.0, 1.0) * step;
      const IVector tube = solver.getCurve()(domain);
      check_collision_free(tube);
      const GapQuantities data = evaluate_gap(tube, true);
      if (!(data.angular_momentum.leftBound() > 0.0)
          || !(data.gap.leftBound() > 0.0)
          || !(data.normalized_side.rightBound() < 1.0)
          || !(data.side_variation.leftBound() > 0.0)) {
        throw std::runtime_error("compact pre-syzygy gap positivity failed");
      }
      middle_gap_lower = std::min(middle_gap_lower, data.gap.leftBound());
      side_variation_lower =
          std::min(side_variation_lower, data.side_variation.leftBound());
      normalized_side_upper =
          std::max(normalized_side_upper, data.normalized_side.rightBound());
    } while (!time_map.completed());

    bool crossing_found = false;
    int tail_steps = 0;
    double tail_gap_rate_upper = -1e300;
    interval crossing_time;
    do {
      const interval start_time = time_map.getCurrentTime();
      const IVector start_state = IVector(set);
      time_map(final_target, set);
      ++tail_steps;
      const interval step = solver.getStep();
      const interval domain = interval(0.0, 1.0) * step;
      const IVector tube = solver.getCurve()(domain);
      const IVector end_state = IVector(set);
      check_collision_free(tube);
      const GapQuantities data = evaluate_gap(tube, true);
      if (!(data.angular_momentum.leftBound() > 0.0)
          || !(data.gap_rate.rightBound() < 0.0)
          || !(data.normalized_side.rightBound() < 1.0)
          || !(data.side_variation.leftBound() > 0.0)) {
        throw std::runtime_error("terminal contact-gap derivative failed");
      }
      tail_gap_rate_upper =
          std::max(tail_gap_rate_upper, data.gap_rate.rightBound());
      side_variation_lower =
          std::min(side_variation_lower, data.side_variation.leftBound());
      normalized_side_upper =
          std::max(normalized_side_upper, data.normalized_side.rightBound());

      if (!crossing_found && tube[1].contains(0.0)) {
        if (!(start_state[1].leftBound() > 0.0)
            || !(end_state[1].rightBound() < 0.0)
            || !(tube[3].rightBound() < 0.0)) {
          throw std::runtime_error("terminal syzygy is not a unique crossing");
        }
        crossing_found = true;
        crossing_time = start_time + domain;
      } else if (!crossing_found && !(tube[1].leftBound() > 0.0)) {
        throw std::runtime_error("unclassified height before terminal syzygy");
      }
      if (crossing_found) {
        break;
      }
    } while (!time_map.completed());

    if (!crossing_found) {
      throw std::runtime_error("terminal syzygy was not reached");
    }
    if (!(early_gap.leftBound() > 6.0)
        || !(middle_gap_lower > 4.0)
        || !(tail_gap_rate_upper < -6.0)
        || !(side_variation_lower > 0.5)
        || !(normalized_side_upper < 0.75)) {
      throw std::runtime_error("advertised rational margins failed");
    }

    std::cout << std::hexfloat
              << "PASS_ISOSCELES_PRE_SYZYGY_GAP"
              << " method=CAPD-6.1.0-native"
              << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
              << " early_steps=" << early_steps
              << " middle_steps=" << middle_steps
              << " tail_steps=" << tail_steps
              << " early_gap_hex=[" << early_gap.leftBound() << ","
              << early_gap.rightBound() << "]"
              << " middle_gap_lower_hex=" << middle_gap_lower
              << " tail_gap_rate_upper_hex=" << tail_gap_rate_upper
              << " compact_side_variation_lower_hex=" << side_variation_lower
              << " compact_normalized_side_upper_hex=" << normalized_side_upper
              << " rational_margins=early_gap>6,middle_gap>4,"
                 "tail_gap_rate<-6,compact_Y>1/2,compact_d<3/4"
              << " crossing_time_hex=[" << crossing_time.leftBound() << ","
              << crossing_time.rightBound() << "]\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "ERROR " << error.what() << "\n";
    return 2;
  }
}
