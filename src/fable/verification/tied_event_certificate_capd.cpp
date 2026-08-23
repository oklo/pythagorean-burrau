// Parametric rigorous second-brake exclusion / event-atlas tool for the
// tied Pythagorean--Burrau family at an arbitrary rational Euclid
// parameter u = p/q.
//
// Mathematical basis: docs/FABLE_EVENT_REDUCTION.md (Theorems A--C).  In
// certify mode the program proves, exactly as
// burrau_event_certificate_capd.cpp does for u = 1/3, that the classical
// tied solution admits no second labelled brake on the covered time range
// and satisfies the terminal binary--escaper certificate.  In atlas mode
// it instead reports rigorous interval enclosures of the event scalars on
// every accepted step whose dI/dt enclosure contains zero, without
// claiming a certificate; this is the trusted instrument for studying
// near-brake events beyond the reach of double precision.
//
// Usage:
//   tied_event_certificate_capd MODE P Q TEND [PREC TOL ORDER \
//       BIN_A BIN_B ESCAPER ETA_NUM ETA_DEN CHECK_START [T1_NUM T1_DEN]]
//   tied_event_certificate_capd icert P Q P2 Q2 TEND [same tail...]
// where MODE is "certify", "atlas", or "icert" (u ranging over the whole
// interval [P/Q, P2/Q2]); u = P/Q; bodies are 1-indexed.
// The initial phase proves U < 2 U0 on [0, t1] (t1 = T1_NUM/T1_DEN,
// default 1/4).
//
// Dependency pin:
//   CAPD 6.1.0, git commit 731079217a9254ea2948d742df2b170895effe7f
// Requires the multiprecision CAPD build; compile with -DFABLE_MP via
// scripts/fable_run_capd_tied_event.sh.

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
double bound_double(const capd::MpFloat& x) { return toDouble(x); }
#else
typedef capd::interval Ival;
typedef capd::IMap Map;
typedef capd::IOdeSolver Solver;
typedef capd::ITimeMap TimeMap;
typedef capd::IVector Vector;
typedef capd::C0HOTripletonSet Set;
double bound_double(double x) { return x; }
#endif

double to_double(const Ival& x) { return bound_double(x.rightBound()); }

Ival rational(long numerator, long denominator) {
  return Ival(numerator) / Ival(denominator);
}

struct Family {
  // All exact intervals derived from u = p/q.
  Ival a;        // m1 = A = (q^2-p^2)/(q^2+p^2)
  Ival b;        // m2 = B = 2pq/(q^2+p^2)
  Ival m3;       // 1
  Ival m12;      // A + B
  Ival total;    // A + B + 1
  Ival mu1;      // AB/(A+B)
  Ival mu2;      // (A+B)/(A+B+1)
  Ival u0;       // AB + 1/(AB)
  Ival alpha;    // m2/m12  (d1 = Y + alpha X)
  Ival beta;     // m1/m12  (d2 = Y - beta X)
};

Family make_family_from_u(const Ival& u) {
  Family f;
  const Ival u2 = u * u;
  const Ival denom = 1 + u2;
  f.a = (1 - u2) / denom;
  f.b = 2 * u / denom;
  f.m3 = Ival(1);
  f.m12 = f.a + f.b;
  f.total = f.m12 + 1;
  f.mu1 = f.a * f.b / f.m12;
  f.mu2 = f.m12 / f.total;
  f.u0 = f.a * f.b + 1 / (f.a * f.b);
  f.alpha = f.b / f.m12;
  f.beta = f.a / f.m12;
  return f;
}

Family make_family(long p, long q) {
  return make_family_from_u(Ival(p) / Ival(q));
}

Map make_field(const Family& f) {
  // Parameters: al, be, gm = m12, ca = (total/m12)*m1, cb = (total/m12)*m2.
  const std::string d1sq = "((y1+al*x1)^2+(y2+al*x2)^2)";
  const std::string d2sq = "((y1-be*x1)^2+(y2-be*x2)^2)";
  const std::string rsq = "(x1^2+x2^2)";
  const std::string inv_r3 = "(" + rsq + "*sqrt(" + rsq + "))";
  const std::string inv_d13 = "(" + d1sq + "*sqrt(" + d1sq + "))";
  const std::string inv_d23 = "(" + d2sq + "*sqrt(" + d2sq + "))";
  Map field(
      "par:al,be,gm,ca,cb;"
      "var:x1,x2,y1,y2,u1,u2,v1,v2;"
      "fun:"
      "u1,u2,v1,v2,"
      "-gm*x1/" + inv_r3 +
      "+(y1-be*x1)/" + inv_d23 + "-(y1+al*x1)/" + inv_d13 + ","
      "-gm*x2/" + inv_r3 +
      "+(y2-be*x2)/" + inv_d23 + "-(y2+al*x2)/" + inv_d13 + ","
      "-(ca*(y1+al*x1)/" + inv_d13 + "+cb*(y1-be*x1)/" + inv_d23 + "),"
      "-(ca*(y2+al*x2)/" + inv_d13 + "+cb*(y2-be*x2)/" + inv_d23 + ");");
  field.setParameter("al", f.alpha);
  field.setParameter("be", f.beta);
  field.setParameter("gm", f.m12);
  field.setParameter("ca", (f.total / f.m12) * f.a);
  field.setParameter("cb", (f.total / f.m12) * f.b);
  return field;
}

// Nine-variable field with the Euclid parameter as a frozen state
// variable w (w' = 0), so that set representations track the
// state--parameter correlation affinely.  All mass coefficients are the
// exact rational functions of w:
//   al = 2w/(1+2w-w^2),  be = (1-w^2)/(1+2w-w^2),
//   gm = (1+2w-w^2)/(1+w^2),
//   ca = (2+2w)(1-w^2)/((1+2w-w^2)(1+w^2)),
//   cb = (2+2w)2w/((1+2w-w^2)(1+w^2)).
Map make_field_correlated() {
  const std::string P = "(1+2*w-w^2)";
  const std::string Q = "(1+w^2)";
  const std::string al = "(2*w/" + P + ")";
  const std::string be = "((1-w^2)/" + P + ")";
  const std::string gm = "(" + P + "/" + Q + ")";
  const std::string ca = "((2+2*w)*(1-w^2)/(" + P + "*" + Q + "))";
  const std::string cb = "((2+2*w)*2*w/(" + P + "*" + Q + "))";
  const std::string d1sq =
      "((y1+" + al + "*x1)^2+(y2+" + al + "*x2)^2)";
  const std::string d2sq =
      "((y1-" + be + "*x1)^2+(y2-" + be + "*x2)^2)";
  const std::string rsq = "(x1^2+x2^2)";
  const std::string inv_r3 = "(" + rsq + "*sqrt(" + rsq + "))";
  const std::string inv_d13 = "(" + d1sq + "*sqrt(" + d1sq + "))";
  const std::string inv_d23 = "(" + d2sq + "*sqrt(" + d2sq + "))";
  return Map(
      "var:x1,x2,y1,y2,u1,u2,v1,v2,w;"
      "fun:"
      "u1,u2,v1,v2,"
      "-" + gm + "*x1/" + inv_r3 +
      "+(y1-" + be + "*x1)/" + inv_d23 +
      "-(y1+" + al + "*x1)/" + inv_d13 + ","
      "-" + gm + "*x2/" + inv_r3 +
      "+(y2-" + be + "*x2)/" + inv_d23 +
      "-(y2+" + al + "*x2)/" + inv_d13 + ","
      "-(" + ca + "*(y1+" + al + "*x1)/" + inv_d13 +
      "+" + cb + "*(y1-" + be + "*x1)/" + inv_d23 + "),"
      "-(" + ca + "*(y2+" + al + "*x2)/" + inv_d13 +
      "+" + cb + "*(y2-" + be + "*x2)/" + inv_d23 + "),"
      "0;");
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
  Ival zeta_re;
  Ival zeta_im;
};

Scalars evaluate_scalars(const Vector& s, const Family& f,
                         bool want_potential) {
  const Ival &x1 = s[0], &x2 = s[1], &y1 = s[2], &y2 = s[3];
  const Ival &u1 = s[4], &u2 = s[5], &v1 = s[6], &v2 = s[7];
  Scalars out;
  const Ival radial_x = dot(x1, x2, u1, u2);
  const Ival radial_y = dot(y1, y2, v1, v2);
  const Ival angular_x = cross(x1, x2, u1, u2);
  const Ival angular_y = cross(y1, y2, v1, v2);
  out.i_dot = 2 * (f.mu1 * radial_x + f.mu2 * radial_y);
  out.kinetic =
      (f.mu1 * dot(u1, u2, u1, u2) + f.mu2 * dot(v1, v2, v1, v2)) / 2;
  out.b1 = radial_x - radial_y;
  out.b2 = dot(u1, u2, y1, y2) + dot(x1, x2, v1, v2);
  out.b3 = cross(u1, u2, y1, y2) + cross(x1, x2, v1, v2);
  out.zeta_re = f.mu1 * radial_x - f.mu2 * radial_y;
  out.zeta_im = f.mu1 * angular_x - f.mu2 * angular_y;
  out.potential = Ival(0);
  if (want_potential) {
    const Ival d11 = y1 + f.alpha * x1;
    const Ival d12 = y2 + f.alpha * x2;
    const Ival d21 = y1 - f.beta * x1;
    const Ival d22 = y2 - f.beta * x2;
    const Ival r12 = sqrt(dot(x1, x2, x1, x2));
    const Ival r13 = sqrt(dot(d11, d12, d11, d12));
    const Ival r23 = sqrt(dot(d21, d22, d21, d22));
    out.potential = f.a * f.b / r12 + f.a * f.m3 / r13 + f.b * f.m3 / r23;
  }
  return out;
}

bool step_excludes_brake(const Scalars& sc) {
  if (!contains_zero(sc.i_dot)) return true;
  if (sc.kinetic.leftBound() > 0) return true;
  return !contains_zero(sc.b1) || !contains_zero(sc.b2) ||
         !contains_zero(sc.b3);
}

// Terminal binary--escaper certificate for arbitrary labelling.  Bodies are
// 0-indexed here; masses[i] from the family.
bool escape_certificate_fires(const Vector& s, const Family& f, int body_a,
                              int body_b, int body_c, const Ival& eta,
                              Ival* margin_out) {
  const Ival masses[3] = {f.a, f.b, f.m3};
  const Ival &x1 = s[0], &x2 = s[1], &y1 = s[2], &y2 = s[3];
  const Ival &u1 = s[4], &u2 = s[5], &v1 = s[6], &v2 = s[7];

  // Cartesian recovery in the center-of-mass frame.
  Ival qx[3], qy[3], wx[3], wy[3];
  qx[2] = (f.m12 / f.total) * y1;
  qy[2] = (f.m12 / f.total) * y2;
  const Ival c12x = -(f.m3 / f.total) * y1;
  const Ival c12y = -(f.m3 / f.total) * y2;
  qx[0] = c12x - f.alpha * x1;
  qy[0] = c12y - f.alpha * x2;
  qx[1] = c12x + f.beta * x1;
  qy[1] = c12y + f.beta * x2;
  wx[2] = (f.m12 / f.total) * v1;
  wy[2] = (f.m12 / f.total) * v2;
  const Ival e12x = -(f.m3 / f.total) * v1;
  const Ival e12y = -(f.m3 / f.total) * v2;
  wx[0] = e12x - f.alpha * u1;
  wy[0] = e12y - f.alpha * u2;
  wx[1] = e12x + f.beta * u1;
  wy[1] = e12y + f.beta * u2;

  const Ival pair_mass = masses[body_a] + masses[body_b];
  const Ival inner_x = qx[body_b] - qx[body_a];
  const Ival inner_y = qy[body_b] - qy[body_a];
  const Ival inner_vx = wx[body_b] - wx[body_a];
  const Ival inner_vy = wy[body_b] - wy[body_a];
  const Ival cx = (masses[body_a] * qx[body_a] + masses[body_b] * qx[body_b]) / pair_mass;
  const Ival cy = (masses[body_a] * qy[body_a] + masses[body_b] * qy[body_b]) / pair_mass;
  const Ival cvx = (masses[body_a] * wx[body_a] + masses[body_b] * wx[body_b]) / pair_mass;
  const Ival cvy = (masses[body_a] * wy[body_a] + masses[body_b] * wy[body_b]) / pair_mass;
  const Ival outer_x = qx[body_c] - cx;
  const Ival outer_y = qy[body_c] - cy;
  const Ival outer_vx = wx[body_c] - cvx;
  const Ival outer_vy = wy[body_c] - cvy;

  const Ival r = sqrt(dot(inner_x, inner_y, inner_x, inner_y));
  const Ival rho = sqrt(dot(outer_x, outer_y, outer_x, outer_y));
  const Ival rho_dot = dot(outer_x, outer_y, outer_vx, outer_vy) / rho;
  const Ival inner_energy =
      dot(inner_vx, inner_vy, inner_vx, inner_vy) / 2 - pair_mass / r;

  const Ival radius_bound = pair_mass / eta;
  const Ival separation = rho - radius_bound;
  if (!(separation.leftBound() > 0)) return false;
  if (!(rho_dot.leftBound() > 0)) return false;
  const Ival radial_margin = rho_dot * rho_dot / 2 - f.total / separation;
  if (!(radial_margin.leftBound() > 0)) return false;
  const Ival speed_floor = sqrt(2 * radial_margin);
  const Ival allowance = masses[body_c] * sqrt(2 * pair_mass * radius_bound) /
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

void print_interval(const char* name, const Ival& x) {
  std::cout << " " << name << "=[" << bound_double(x.leftBound()) << ","
            << bound_double(x.rightBound()) << "]";
}

}  // namespace

int main(int argc, char** argv) {
  try {
    if (argc < 5) {
      std::cerr << "usage: tied_event_certificate_capd MODE P Q TEND"
                   " [PREC TOL ORDER BIN_A BIN_B ESCAPER ETA_NUM ETA_DEN"
                   " CHECK_START [T1_NUM T1_DEN]]\n";
      return 2;
    }
    const std::string mode = argv[1];
    const bool interval_mode = mode == "icert";
    const bool certify = mode == "certify" || interval_mode;
    if (!certify && mode != "atlas") {
      std::cerr << "MODE must be certify, icert, or atlas\n";
      return 2;
    }
    const long p = std::atol(argv[2]);
    const long q = std::atol(argv[3]);
    long p2 = p, q2 = q;
    int base = 4;
    if (interval_mode) {
      if (argc < 7) {
        std::cerr << "icert needs P Q P2 Q2 TEND\n";
        return 2;
      }
      p2 = std::atol(argv[4]);
      q2 = std::atol(argv[5]);
      base = 6;
    }
    const double tend = std::atof(argv[base]);
    const int precision = argc > base + 1 ? std::atoi(argv[base + 1]) : 768;
    const double tolerance = argc > base + 2 ? std::atof(argv[base + 2]) : 1e-80;
    const int order = argc > base + 3 ? std::atoi(argv[base + 3]) : 60;
    const int body_a = argc > base + 4 ? std::atoi(argv[base + 4]) - 1 : 2;
    const int body_b = argc > base + 5 ? std::atoi(argv[base + 5]) - 1 : 0;
    const int body_c = argc > base + 6 ? std::atoi(argv[base + 6]) - 1 : 1;
    const long eta_num = argc > base + 7 ? std::atol(argv[base + 7]) : 4;
    const long eta_den = argc > base + 8 ? std::atol(argv[base + 8]) : 1;
    const double check_start =
        argc > base + 9 ? std::atof(argv[base + 9]) : tend - 2.5;
    const long t1_num = argc > base + 10 ? std::atol(argv[base + 10]) : 1;
    const long t1_den = argc > base + 11 ? std::atol(argv[base + 11]) : 4;

#ifdef FABLE_MP
    capd::MpFloat::setDefaultPrecision(precision);
#else
    (void)precision;
#endif
    Ival u_param = Ival(p) / Ival(q);
    if (interval_mode) {
      const Ival upper = Ival(p2) / Ival(q2);
      u_param = Ival(u_param.leftBound(), upper.rightBound());
      if (!(u_param.leftBound() < u_param.rightBound())) {
        std::cerr << "icert interval endpoints out of order\n";
        return 2;
      }
    }
    const Family f = make_family_from_u(u_param);
    Map field = interval_mode ? make_field_correlated() : make_field(f);
    Solver solver(field, order);
    solver.setAbsoluteTolerance(tolerance);
    solver.setRelativeTolerance(tolerance);
    std::unique_ptr<TimeMap> time_map(new TimeMap(solver));

    // Exact tied initial state: X = (1,0), Y = (AB(B-A)/(A+B), AB); in
    // interval mode the frozen parameter w carries the u-interval.
    Vector initial(interval_mode ? 9 : 8);
    initial[0] = Ival(1);
    initial[1] = Ival(0);
    initial[2] = f.a * f.b * (f.b - f.a) / f.m12;
    initial[3] = f.a * f.b;
    for (int i = 4; i < 8; ++i) initial[i] = Ival(0);
    if (interval_mode) initial[8] = u_param;
    Set set(initial);

    const Ival t1 = rational(t1_num, t1_den);
    const Ival final_time = Ival(tend);
    const Ival eta = rational(eta_num, eta_den);

    time_map->stopAfterStep(true);

    // Near a deep binary encounter the trial-step rough enclosure can
    // sweep across the collision set, making the interval vector field
    // throw a division-by-zero domain error before the set is modified.
    // That is a failed step attempt, not a failed certificate: cap the
    // step and retry.  The cap relaxes geometrically after successes.
    double step_cap = 1e6;
    long capped_retries = 0;

    long steps = 0;
    long event_steps = 0;
    double min_event_kinetic = 1e300;
    bool certified = false;
    bool initial_phase = true;
    Ival final_margin;

    std::cout << std::setprecision(17);
    bool finished = false;
    do {
      try {
        solver.setMaxStep(Ival(step_cap));
        (*time_map)(final_time, set);
      } catch (const std::exception& step_error) {
        ++capped_retries;
        if (capped_retries > 4000 || step_cap < 1e-13) {
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
        step_cap *= 1.25;
      }
      ++steps;
      const Vector enclosure = set.getLastEnclosure();
      const Ival current_time = time_map->getCurrentTime();
      const Scalars sc = evaluate_scalars(enclosure, f, initial_phase);

      if (initial_phase) {
        if (!(sc.potential.rightBound() < (2 * f.u0).leftBound())) {
          std::cerr << "FAIL initial-window potential bound at t="
                    << to_double(current_time) << "\n";
          return 1;
        }
        if (current_time.leftBound() > t1.rightBound()) {
          initial_phase = false;
        }
      } else if (contains_zero(sc.i_dot)) {
        ++event_steps;
        min_event_kinetic = std::min(min_event_kinetic,
                                     bound_double(sc.kinetic.leftBound()));
        if (!certify) {
          std::cout << "EVENT t=[" << bound_double(current_time.leftBound())
                    << "," << bound_double(current_time.rightBound()) << "]";
          print_interval("K", sc.kinetic);
          print_interval("B1", sc.b1);
          print_interval("B2", sc.b2);
          print_interval("B3", sc.b3);
          print_interval("zre", sc.zeta_re);
          print_interval("zim", sc.zeta_im);
          print_interval("UoverU0", sc.potential / f.u0);
          std::cout << "\n" << std::flush;
        } else if (!step_excludes_brake(sc)) {
          std::cerr << "FAIL uncovered step at t=" << to_double(current_time)
                    << "\n";
          return 1;
        }
      } else if (certify && !step_excludes_brake(sc)) {
        std::cerr << "FAIL uncovered step at t=" << to_double(current_time)
                  << "\n";
        return 1;
      }

      if (steps % 500 == 0) {
        const Vector snapshot(set);
        std::cout << "progress t=" << to_double(current_time)
                  << " steps=" << steps
                  << " hull_width=" << hull_width(snapshot) << "\n"
                  << std::flush;
      }

      if (certify &&
          bound_double(current_time.rightBound()) > check_start) {
        const Vector current(set);
        if (std::getenv("FABLE_DEBUG_ESCAPE") != nullptr) {
          Ival dbg(0);
          const bool ok = escape_certificate_fires(current, f, body_a, body_b,
                                                   body_c, eta, &dbg);
          std::cout << "escape_check t=" << to_double(current_time)
                    << " fired=" << ok << " margin=["
                    << bound_double(dbg.leftBound()) << ","
                    << bound_double(dbg.rightBound()) << "]\n" << std::flush;
        }
        if (escape_certificate_fires(current, f, body_a, body_b, body_c,
                                     eta, &final_margin)) {
          certified = true;
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

    const Vector final_state(set);
    std::cout << "end_time=" << to_double(time_map->getCurrentTime())
              << "\n";
    std::cout << "steps=" << steps << " event_steps=" << event_steps
              << " min_event_kinetic=" << min_event_kinetic
              << " final_hull_width=" << hull_width(final_state) << "\n";

    if (certify) {
      if (!certified) {
        std::cerr << "FAIL terminal escape certificate did not fire\n";
        return 1;
      }
      std::cout << "final state box (outward-rounded to double):\n";
      for (int i = 0; i < 8; ++i) {
        std::cout << "  [" << bound_double(final_state[i].leftBound())
                  << ", " << bound_double(final_state[i].rightBound())
                  << "]\n";
      }
      if (interval_mode) {
        std::cout << "PASS_TIED_EVENT_INTERVAL u=[" << p << "/" << q
                  << "," << p2 << "/" << q2 << "]\n";
      } else {
        std::cout << "PASS_TIED_EVENT p=" << p << " q=" << q << "\n";
      }
    } else {
      std::cout << "ATLAS_DONE p=" << p << " q=" << q << "\n";
    }
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FAIL exception: " << error.what() << "\n";
    return 1;
  }
}
