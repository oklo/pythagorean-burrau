// Rigorous second-brake exclusion certificate for the 3:4:5 Pythagorean
// Burrau free-fall problem (Euclid parameter u = 1/3).
//
// Mathematical basis: docs/FABLE_EVENT_REDUCTION.md.  A second labelled
// brake at a collision-free time forces simultaneously dI/dt = 0, K = 0,
// and every component of the Hopf residual B to vanish.  The verifier
// integrates the exact normalized problem with interval arithmetic and
// proves that on every accepted-step solution enclosure at least one of
//   (i)   0 is not in the interval enclosure of dI/dt,
//   (ii)  the kinetic energy enclosure is strictly positive,
//   (iii) some component of the Hopf residual enclosure excludes zero,
// except on an explicit initial phase where it instead proves U < 2 U0
// throughout, which forces d^2I/dt^2 < 0 and hence dI/dt < 0 after t = 0
// because dI/dt(0) = 0.  Finally it verifies the strict inequalities of
// the terminal binary--escaper certificate of docs/ESCAPE_CRITERIA.md on
// the reached state box, which excludes every later classical brake.  A
// successful run therefore proves that the classical 3:4:5 Burrau solution
// is collision-free on the covered time range and admits no second
// labelled brake at any positive time, i.e. it is nonperiodic.
//
// The deep binary encounters make double-precision interval boxes wrap
// catastrophically, so the certificate runs in MPFR multiprecision when
// compiled with -DFABLE_MP (default precision 768 bits, configurable with
// the first command-line argument).
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
// Build CAPD with -DCAPD_INTERVAL_TYPE=NATIVE (plus
// -DCAPD_ENABLE_MULTIPRECISION=ON for the MP variant) and compile with
// capd-config flags; scripts/fable_run_capd_burrau_event.sh automates the
// checks.

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

#ifdef FABLE_MP
#include "capd/mpcapdlib.h"
#else
#include "capd/capdlib.h"
#endif

namespace {

#ifdef FABLE_MP
typedef capd::MpInterval Ival;
typedef capd::MpIMap Map;
typedef capd::MpIOdeSolver Solver;
typedef capd::MpITimeMap TimeMap;
typedef capd::MpIVector Vector;
typedef capd::MpC0TripletonSet Set;
#else
typedef capd::interval Ival;
typedef capd::IMap Map;
typedef capd::IOdeSolver Solver;
typedef capd::ITimeMap TimeMap;
typedef capd::IVector Vector;
typedef capd::C0HOTripletonSet Set;
#endif

#ifdef FABLE_MP
double bound_double(const capd::MpFloat& x) { return toDouble(x); }
#else
double bound_double(double x) { return x; }
#endif

double to_double(const Ival& x) { return bound_double(x.rightBound()); }

// Masses for u = 1/3: (m1, m2, m3) = (4/5, 3/5, 1).
Ival kM1() { return Ival(4) / Ival(5); }
Ival kM2() { return Ival(3) / Ival(5); }
Ival kM3() { return Ival(1); }
Ival kPairMass12() { return Ival(7) / Ival(5); }
Ival kTotalMass() { return Ival(12) / Ival(5); }
Ival kMu1() { return Ival(12) / Ival(35); }
Ival kMu2() { return Ival(7) / Ival(12); }
Ival kU0() { return Ival(769) / Ival(300); }

Map make_field() {
  // State (x1,x2,y1,y2,u1,u2,v1,v2): unweighted Jacobi vectors and their
  // velocities.  d1 = Y + (3/7) X and d2 = Y - (4/7) X are the vectors from
  // bodies 1 and 2 to body 3.
  const std::string d1sq = "((y1+3*x1/7)^2+(y2+3*x2/7)^2)";
  const std::string d2sq = "((y1-4*x1/7)^2+(y2-4*x2/7)^2)";
  const std::string rsq = "(x1^2+x2^2)";
  const std::string inv_r3 = "(" + rsq + "*sqrt(" + rsq + "))";
  const std::string inv_d13 = "(" + d1sq + "*sqrt(" + d1sq + "))";
  const std::string inv_d23 = "(" + d2sq + "*sqrt(" + d2sq + "))";
  const std::string field_text =
      "var:x1,x2,y1,y2,u1,u2,v1,v2;"
      "fun:"
      "u1,u2,v1,v2,"
      "-7*x1/(5*" + inv_r3 + ")"
      "+(y1-4*x1/7)/" + inv_d23 + "-(y1+3*x1/7)/" + inv_d13 + ","
      "-7*x2/(5*" + inv_r3 + ")"
      "+(y2-4*x2/7)/" + inv_d23 + "-(y2+3*x2/7)/" + inv_d13 + ","
      "-(12/7)*((4/5)*(y1+3*x1/7)/" + inv_d13 +
      "+(3/5)*(y1-4*x1/7)/" + inv_d23 + "),"
      "-(12/7)*((4/5)*(y2+3*x2/7)/" + inv_d13 +
      "+(3/5)*(y2-4*x2/7)/" + inv_d23 + ");";
  return Map(field_text);
}

Ival dot(const Ival& a1, const Ival& a2, const Ival& b1, const Ival& b2) {
  return a1 * b1 + a2 * b2;
}

Ival cross(const Ival& a1, const Ival& a2, const Ival& b1, const Ival& b2) {
  return a1 * b2 - a2 * b1;
}

bool contains_zero(const Ival& x) {
  return !(x.leftBound() > 0) && !(x.rightBound() < 0);
}

struct Scalars {
  Ival i_dot;
  Ival kinetic;
  Ival b1;
  Ival b2;
  Ival b3;
  Ival potential;
};

Scalars evaluate_scalars(const Vector& s, bool want_potential) {
  const Ival &x1 = s[0], &x2 = s[1], &y1 = s[2], &y2 = s[3];
  const Ival &u1 = s[4], &u2 = s[5], &v1 = s[6], &v2 = s[7];
  Scalars out;
  out.i_dot =
      2 * (kMu1() * dot(x1, x2, u1, u2) + kMu2() * dot(y1, y2, v1, v2));
  out.kinetic =
      (kMu1() * dot(u1, u2, u1, u2) + kMu2() * dot(v1, v2, v1, v2)) / 2;
  out.b1 = dot(x1, x2, u1, u2) - dot(y1, y2, v1, v2);
  out.b2 = dot(u1, u2, y1, y2) + dot(x1, x2, v1, v2);
  out.b3 = cross(u1, u2, y1, y2) + cross(x1, x2, v1, v2);
  out.potential = Ival(0);
  if (want_potential) {
    const Ival d11 = y1 + 3 * x1 / 7;
    const Ival d12 = y2 + 3 * x2 / 7;
    const Ival d21 = y1 - 4 * x1 / 7;
    const Ival d22 = y2 - 4 * x2 / 7;
    const Ival r12 = sqrt(dot(x1, x2, x1, x2));
    const Ival r13 = sqrt(dot(d11, d12, d11, d12));
    const Ival r23 = sqrt(dot(d21, d22, d21, d22));
    out.potential =
        kM1() * kM2() / r12 + kM1() * kM3() / r13 + kM2() * kM3() / r23;
  }
  return out;
}

bool step_excludes_brake(const Scalars& sc) {
  if (!contains_zero(sc.i_dot)) {
    return true;  // (i) dI/dt bounded away from zero
  }
  if (sc.kinetic.leftBound() > 0) {
    return true;  // (ii) kinetic energy strictly positive
  }
  return !contains_zero(sc.b1) || !contains_zero(sc.b2) ||
         !contains_zero(sc.b3);  // (iii)
}

// (iv) Position-only exclusion: on the true orbit K = U - U0, so
// inf U > U0 from the position box alone excludes a brake even when the
// velocity enclosure is useless (deep encounters).
bool positions_exclude_brake(const Vector& s) {
  const Ival &x1 = s[0], &x2 = s[1], &y1 = s[2], &y2 = s[3];
  const Ival d11 = y1 + 3 * x1 / 7;
  const Ival d12 = y2 + 3 * x2 / 7;
  const Ival d21 = y1 - 4 * x1 / 7;
  const Ival d22 = y2 - 4 * x2 / 7;
  const Ival s12 = dot(x1, x2, x1, x2);
  const Ival s13 = dot(d11, d12, d11, d12);
  const Ival s23 = dot(d21, d22, d21, d22);
  if (!(s12.leftBound() > 0) || !(s13.leftBound() > 0) ||
      !(s23.leftBound() > 0)) {
    return false;
  }
  const Ival u_val = kM1() * kM2() / sqrt(s12) + kM1() * kM3() / sqrt(s13) +
                     kM2() * kM3() / sqrt(s23);
  return u_val.leftBound() > kU0().rightBound();
}

// Terminal binary--escaper certificate (docs/ESCAPE_CRITERIA.md) for the
// binary {body3, body1} with escaper body2 and eta = 4.  All inequalities
// are evaluated with outward rounding on the state box.
bool escape_certificate_fires(const Vector& s, Ival* margin_out) {
  const Ival eta = Ival(4);
  const Ival &x1 = s[0], &x2 = s[1], &y1 = s[2], &y2 = s[3];
  const Ival &u1 = s[4], &u2 = s[5], &v1 = s[6], &v2 = s[7];

  // Cartesian recovery in the center-of-mass frame.
  const Ival q3x = (kPairMass12() / kTotalMass()) * y1;
  const Ival q3y = (kPairMass12() / kTotalMass()) * y2;
  const Ival c12x = -(kM3() / kTotalMass()) * y1;
  const Ival c12y = -(kM3() / kTotalMass()) * y2;
  const Ival q1x = c12x - (kM2() / kPairMass12()) * x1;
  const Ival q1y = c12y - (kM2() / kPairMass12()) * x2;
  const Ival q2x = c12x + (kM1() / kPairMass12()) * x1;
  const Ival q2y = c12y + (kM1() / kPairMass12()) * x2;
  const Ival w3x = (kPairMass12() / kTotalMass()) * v1;
  const Ival w3y = (kPairMass12() / kTotalMass()) * v2;
  const Ival e12x = -(kM3() / kTotalMass()) * v1;
  const Ival e12y = -(kM3() / kTotalMass()) * v2;
  const Ival w1x = e12x - (kM2() / kPairMass12()) * u1;
  const Ival w1y = e12y - (kM2() / kPairMass12()) * u2;
  const Ival w2x = e12x + (kM1() / kPairMass12()) * u1;
  const Ival w2y = e12y + (kM1() / kPairMass12()) * u2;

  // Binary bodies 3 and 1; escaper body 2.
  const Ival pair_mass = kM3() + kM1();  // 9/5
  const Ival inner_x = q1x - q3x;
  const Ival inner_y = q1y - q3y;
  const Ival inner_vx = w1x - w3x;
  const Ival inner_vy = w1y - w3y;
  const Ival cx = (kM3() * q3x + kM1() * q1x) / pair_mass;
  const Ival cy = (kM3() * q3y + kM1() * q1y) / pair_mass;
  const Ival cvx = (kM3() * w3x + kM1() * w1x) / pair_mass;
  const Ival cvy = (kM3() * w3y + kM1() * w1y) / pair_mass;
  const Ival outer_x = q2x - cx;
  const Ival outer_y = q2y - cy;
  const Ival outer_vx = w2x - cvx;
  const Ival outer_vy = w2y - cvy;

  const Ival r = sqrt(dot(inner_x, inner_y, inner_x, inner_y));
  const Ival rho = sqrt(dot(outer_x, outer_y, outer_x, outer_y));
  const Ival rho_dot = dot(outer_x, outer_y, outer_vx, outer_vy) / rho;
  const Ival inner_energy =
      dot(inner_vx, inner_vy, inner_vx, inner_vy) / 2 - pair_mass / r;

  const Ival radius_bound = pair_mass / eta;
  const Ival separation = rho - radius_bound;
  if (!(separation.leftBound() > 0)) return false;
  if (!(rho_dot.leftBound() > 0)) return false;
  const Ival radial_margin =
      rho_dot * rho_dot / 2 - kTotalMass() / separation;
  if (!(radial_margin.leftBound() > 0)) return false;
  const Ival speed_floor = sqrt(2 * radial_margin);
  const Ival allowance = kM2() * sqrt(2 * pair_mass * radius_bound) /
                         (speed_floor * separation * separation);
  const Ival inner_margin = -eta - inner_energy - allowance;
  if (margin_out != nullptr) *margin_out = inner_margin;
  return inner_margin.leftBound() > 0;
}

double hull_width(const Vector& s) {
  double w = 0;
  for (int i = 0; i < 8; ++i) {
    w = std::max(w, bound_double(s[i].rightBound() - s[i].leftBound()));
  }
  return w;
}

}  // namespace

int main(int argc, char** argv) {
  const bool verbose = argc > 1 && std::string(argv[1]) == "--verbose";
#ifdef FABLE_MP
  const int precision = argc > 2 ? std::atoi(argv[2]) : 768;
  capd::MpFloat::setDefaultPrecision(precision);
  const double tolerance = argc > 3 ? std::atof(argv[3]) : 1e-100;
  const int order = argc > 4 ? std::atoi(argv[4]) : 60;
#else
  const double tolerance = argc > 3 ? std::atof(argv[3]) : 1e-15;
  const int order = argc > 4 ? std::atoi(argv[4]) : 26;
#endif
  try {
    Map field = make_field();
    Solver solver(field, order);
    solver.setAbsoluteTolerance(tolerance);
    solver.setRelativeTolerance(tolerance);
    std::unique_ptr<TimeMap> time_map(new TimeMap(solver));

    // Exact tied initial state for u = 1/3.
    Vector initial(8);
    initial[0] = Ival(1);
    initial[1] = Ival(0);
    initial[2] = Ival(-12) / Ival(175);
    initial[3] = Ival(12) / Ival(25);
    initial[4] = Ival(0);
    initial[5] = Ival(0);
    initial[6] = Ival(0);
    initial[7] = Ival(0);
    Set set(initial);

    const Ival t1 = Ival(1) / Ival(4);
    const Ival final_time = Ival(14);
    const double escape_check_start = 11.5;

    time_map->stopAfterStep(true);

    // Near a deep binary encounter the trial-step rough enclosure can
    // sweep across the collision set, making the interval vector field
    // throw a division-by-zero domain error before the set is modified.
    // That is a failed step attempt, not a failed certificate: cap the
    // step and retry.  The cap relaxes geometrically after successes.
    double step_cap = 1e6;
    long capped_retries = 0;
    long successes_since_cap = 0;

    long steps = 0;
    long event_steps = 0;
    double min_event_kinetic = 1e300;
    double min_event_residual = 1e300;
    bool certified = false;
    bool initial_phase = true;
    Ival final_margin;

    bool finished = false;
    do {
      try {
        solver.setMaxStep(Ival(step_cap));
        (*time_map)(final_time, set);
      } catch (const std::exception& step_error) {
        ++capped_retries;
        successes_since_cap = 0;
        if (capped_retries > 200000 || step_cap < 1e-14) {
          throw;
        }
        const double last = bound_double(solver.getStep().rightBound());
        const double reference = (last > 1e-13 && last < step_cap) ? last : step_cap;
        step_cap = reference / 2;
        // A thrown step can leave the time map in a spurious completed
        // state; rebuild it (the set carries its own current time).
        time_map.reset(new TimeMap(solver));
        time_map->stopAfterStep(true);
        continue;
      }
      if (step_cap < 1e6) {
        ++successes_since_cap;
        if (successes_since_cap >= 40) {
          step_cap *= 2;
          successes_since_cap = 0;
        }
      }
      ++steps;
      const Vector enclosure = set.getLastEnclosure();
      const Ival current_time = time_map->getCurrentTime();
      const Scalars sc = evaluate_scalars(enclosure, initial_phase);

      if (initial_phase) {
        // Initial phase: prove U < 2 U0 on every step enclosure up to and
        // including the first accepted step ending past t1.  Then I'' < 0
        // throughout, and dI/dt(0) = 0 forces dI/dt < 0 there after t = 0:
        // no brake in the phase.
        if (!(sc.potential.rightBound() < (2 * kU0()).leftBound())) {
          std::cerr << "FAIL initial-window potential bound at t="
                    << to_double(current_time) << "\n";
          return 1;
        }
        if (current_time.leftBound() > t1.rightBound()) {
          initial_phase = false;
        }
      } else {
        if (!step_excludes_brake(sc) &&
            !positions_exclude_brake(enclosure)) {
          std::cerr << "FAIL uncovered step at t=" << to_double(current_time)
                    << " i_dot=[" << bound_double(sc.i_dot.leftBound())
                    << "," << bound_double(sc.i_dot.rightBound())
                    << "] K=[" << bound_double(sc.kinetic.leftBound())
                    << "," << bound_double(sc.kinetic.rightBound())
                    << "]\n";
          return 1;
        }
        if (contains_zero(sc.i_dot)) {
          ++event_steps;
          min_event_kinetic = std::min(
              min_event_kinetic, bound_double(sc.kinetic.leftBound()));
          double res = 0;
          res = std::max(res, std::min(
              std::abs(bound_double(sc.b1.leftBound())),
              std::abs(bound_double(sc.b1.rightBound()))));
          if (!contains_zero(sc.b1) || !contains_zero(sc.b2) ||
              !contains_zero(sc.b3)) {
            min_event_residual = std::min(min_event_residual, res);
          }
        }
      }

      if (verbose && steps % 500 == 0) {
        const Vector snapshot(set);
        std::cout << "t=" << to_double(current_time)
                  << " steps=" << steps
                  << " hull_width=" << hull_width(snapshot)
                  << " capped_retries=" << capped_retries
                  << " step_cap=" << step_cap << "\n"
                  << std::flush;
      }

      if (bound_double(current_time.rightBound()) > escape_check_start) {
        const Vector current(set);
        if (escape_certificate_fires(current, &final_margin)) {
          certified = true;
          std::cout << std::setprecision(17);
          std::cout << "escape certificate fired at t="
                    << to_double(current_time) << " margin="
                    << bound_double(final_margin.leftBound()) << "\n";
          break;
        }
      }
      if (time_map->completed()) {
        if (to_double(current_time) <
            bound_double(final_time.leftBound()) - 1e-9) {
          time_map.reset(new TimeMap(solver));
          time_map->stopAfterStep(true);
          continue;
        }
        finished = true;
      }
    } while (!finished);

    if (!certified) {
      std::cerr << "FAIL terminal escape certificate did not fire\n";
      return 1;
    }

    const Vector final_state(set);
    std::cout << std::setprecision(17);
    std::cout << "final state box (outward-rounded to double):\n";
    for (int i = 0; i < 8; ++i) {
      std::cout << "  [" << bound_double(final_state[i].leftBound())
                << ", " << bound_double(final_state[i].rightBound())
                << "]\n";
    }
    std::cout << "steps=" << steps << " event_steps=" << event_steps
              << " min_event_kinetic=" << min_event_kinetic
              << " final_hull_width=" << hull_width(final_state) << "\n";
    std::cout << "PASS_BURRAU_EVENT\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FAIL exception: " << error.what() << "\n";
    return 1;
  }
}
