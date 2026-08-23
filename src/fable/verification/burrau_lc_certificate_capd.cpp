// Rigorous second-brake exclusion certificate for the 3:4:5 Pythagorean
// Burrau free-fall problem (u = 1/3) with a Levi--Civita chart through the
// deep pair-{1,3} encounter near t = 3.166.
//
// Mathematical basis: docs/FABLE_EVENT_REDUCTION.md and
// docs/FABLE_LC_COVERING_DESIGN.md.  Outside the encounter zone the
// verifier works exactly like burrau_event_certificate_capd.cpp: on every
// accepted-step solution enclosure at least one of
//   (i)  0 not in dI/dt,  (ii) inf K > 0,  (iii) a Hopf-residual
//   component excludes 0,  (iv) inf U > U0 from positions alone
// holds, plus the initial phase (U < 2 U0 up to t1) and the terminal
// binary--escaper certificate.  Inside the zone |g| < rho_zone with
// g = q3 - q1 the brake bound r13 >= m1 m3 / U0 (Theorem A) makes a brake
// impossible, so the only obligations there are 0 < |g| (no collision)
// and |g| below the bound; the chart's job is transporting the set.
//
// Chart (validated numerically against direct integration to 1.7e-9):
//   g = w^2 (complex), dt = |w|^2 dsigma, z = dw/dsigma,
//   z' = (h/2) w + (|w|^2/2) conj(w) F_ext,
//   h' = 2 Re(conj(w z) F_ext),   h = |g'|^2/2 - M13/|g|,
//   G = a X + b Y (pair-complement),  G'' regular,
//   with F_ext the regular external force on g.
// Entry writes chart variables exactly by the unit-time construction-flow
// idiom (rates equal to target expressions of the frozen physical state;
// chart block is zero beforehand).  Exit writes the physical variables by
// the damped construction x' = c (T - x) + delta with c = 400 and an
// interval parameter |delta| <= 1e-165 that rigorously encloses the
// e^{-400} residual (all quantities are verified to be bounded by 100 at
// exit time).
//
// Dependency pin: CAPD 6.1.0, commit
// 731079217a9254ea2948d742df2b170895effe7f, MP build.  Compile with
// -DFABLE_MP via scripts/fable_run_capd_burrau_lc.sh.

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "capd/mpcapdlib.h"

namespace {

typedef capd::MpInterval Ival;
typedef capd::MpIMap Map;
typedef capd::MpIOdeSolver Solver;
typedef capd::MpITimeMap TimeMap;
typedef capd::MpIVector Vector;
typedef capd::MpC0TripletonSet Set;

double bound_double(const capd::MpFloat& x) { return toDouble(x); }
double to_double(const Ival& x) { return bound_double(x.rightBound()); }

// Masses for u = 1/3.
Ival kM1() { return Ival(4) / Ival(5); }
Ival kM2() { return Ival(3) / Ival(5); }
Ival kM3() { return Ival(1); }
Ival kU0() { return Ival(769) / Ival(300); }
Ival kMu1() { return Ival(12) / Ival(35); }
Ival kMu2() { return Ival(7) / Ival(12); }
// M12 = 7/5, M = 12/5, M13 = m1 + m3 = 9/5.
// alpha = m2/M12 = 3/7, beta = m1/M12 = 4/7.
// G = a X + b Y with a = beta + m1*alpha/M13 = 4/7 + (4/5)(3/7)/(9/5)
//   = 4/7 + 4/21 = 16/21,  b = -m3/M13 = -5/9.
// Inverse of [[alpha,1],[a,b]] has determinant D = alpha*b - a
//   = (3/7)(-5/9) - 16/21 = -5/21 - 16/21 = -1.
// So X = -( b g - G ) = G - b g,  Y = -( -a g + alpha G ) = a g - alpha G.
// (With D = -1 the inverse is exact and simple.)

const char* kVars =
    "var:x1,x2,y1,y2,p1,p2,q1,q2,wr,wi,zr,zi,hh,cgx,cgy,cpx,cpy,tp;";

// State layout: physical X=(x1,x2), Y=(y1,y2), VX=(p1,p2), VY=(q1,q2);
// chart w=(wr,wi), z=(zr,zi), pair energy hh, complement G=(cgx,cgy),
// P=(cpx,cpy); physical time tp.

Map make_physical_field() {
  const std::string d1sq = "((y1+3*x1/7)^2+(y2+3*x2/7)^2)";
  const std::string d2sq = "((y1-4*x1/7)^2+(y2-4*x2/7)^2)";
  const std::string rsq = "(x1^2+x2^2)";
  const std::string inv_r3 = "(" + rsq + "*sqrt(" + rsq + "))";
  const std::string inv_d13 = "(" + d1sq + "*sqrt(" + d1sq + "))";
  const std::string inv_d23 = "(" + d2sq + "*sqrt(" + d2sq + "))";
  return Map(std::string(kVars) +
      "fun:p1,p2,q1,q2,"
      "-7*x1/(5*" + inv_r3 + ")"
      "+(y1-4*x1/7)/" + inv_d23 + "-(y1+3*x1/7)/" + inv_d13 + ","
      "-7*x2/(5*" + inv_r3 + ")"
      "+(y2-4*x2/7)/" + inv_d23 + "-(y2+3*x2/7)/" + inv_d13 + ","
      "-(12/7)*((4/5)*(y1+3*x1/7)/" + inv_d13 +
      "+(3/5)*(y1-4*x1/7)/" + inv_d23 + "),"
      "-(12/7)*((4/5)*(y2+3*x2/7)/" + inv_d13 +
      "+(3/5)*(y2-4*x2/7)/" + inv_d23 + "),"
      "0,0,0,0,0,0,0,0,0,1;");
}

// Entry construction: chart block is zero; each rate is the exact target,
// a function of the frozen physical variables, so time-1 writes it.
// Form A (gx > 0):  wr = sqrt((|g|+gx)/2), wi = gy/(2 wr).
// Form B (gx < 0):  wi = sqrt((|g|-gx)/2), wr = gy/(2 wi).
// g = Y + (3/7) X, gdot = VY + (3/7) VX.
Map make_entry_field(bool form_a) {
  const std::string gx = "(y1+3*x1/7)";
  const std::string gy = "(y2+3*x2/7)";
  const std::string gdx = "(q1+3*p1/7)";
  const std::string gdy = "(q2+3*p2/7)";
  const std::string absg = "sqrt(" + gx + "^2+" + gy + "^2)";
  std::string wr_t, wi_t;
  if (form_a) {
    wr_t = "sqrt((" + absg + "+" + gx + ")/2)";
    wi_t = "(" + gy + "/(2*" + wr_t + "))";
  } else {
    wi_t = "sqrt((" + absg + "-" + gx + ")/2)";
    wr_t = "(" + gy + "/(2*" + wi_t + "))";
  }
  const std::string zr_t = "((" + wr_t + "*" + gdx + "+" + wi_t + "*" + gdy + ")/2)";
  const std::string zi_t = "((" + wr_t + "*" + gdy + "-" + wi_t + "*" + gdx + ")/2)";
  const std::string h_t =
      "((" + gdx + "^2+" + gdy + "^2)/2-(9/5)/" + absg + ")";
  // G = (16/21) X - (5/9) Y ; P likewise on velocities.
  return Map(std::string(kVars) +
      "fun:0,0,0,0,0,0,0,0," +
      wr_t + "," + wi_t + "," + zr_t + "," + zi_t + "," + h_t + ","
      "(16*x1/21-5*y1/9),(16*x2/21-5*y2/9),"
      "(16*p1/21-5*q1/9),(16*p2/21-5*q2/9),0;");
}

// LC-zone field in sigma.
Map make_lc_field() {
  const std::string w2 = "(wr^2+wi^2)";
  const std::string gx = "(wr^2-wi^2)";
  const std::string gy = "(2*wr*wi)";
  // d21 = q2 - q1 = G + (m3/M13) g = G + (5/9) g
  // d23 = q2 - q3 = G - (m1/M13) g = G - (4/9) g
  const std::string d21x = "(cgx+5*" + gx + "/9)";
  const std::string d21y = "(cgy+5*" + gy + "/9)";
  const std::string d23x = "(cgx-4*" + gx + "/9)";
  const std::string d23y = "(cgy-4*" + gy + "/9)";
  const std::string r12sq = "(" + d21x + "^2+" + d21y + "^2)";
  const std::string r23sq = "(" + d23x + "^2+" + d23y + "^2)";
  const std::string ir12 = "(" + r12sq + "*sqrt(" + r12sq + "))";
  const std::string ir23 = "(" + r23sq + "*sqrt(" + r23sq + "))";
  // F_ext on g: m2 (d23/r23^3 - d21/r12^3), m2 = 3/5.
  const std::string fx = "((3/5)*(" + d23x + "/" + ir23 + "-" + d21x + "/" + ir12 + "))";
  const std::string fy = "((3/5)*(" + d23y + "/" + ir23 + "-" + d21y + "/" + ir12 + "))";
  // G'' = -(M/M13)(m1 d21/r12^3 + m3 d23/r23^3), M/M13 = (12/5)/(9/5) = 4/3.
  const std::string gddx =
      "(-(4/3)*((4/5)*" + d21x + "/" + ir12 + "+" + d23x + "/" + ir23 + "))";
  const std::string gddy =
      "(-(4/3)*((4/5)*" + d21y + "/" + ir12 + "+" + d23y + "/" + ir23 + "))";
  return Map(std::string(kVars) +
      "fun:0,0,0,0,0,0,0,0,"
      "zr,zi,"
      "(hh/2)*wr+(" + w2 + "/2)*(wr*" + fx + "+wi*" + fy + "),"
      "(hh/2)*wi+(" + w2 + "/2)*(wr*" + fy + "-wi*" + fx + "),"
      "2*((wr*zr-wi*zi)*" + fx + "+(wr*zi+wi*zr)*" + fy + "),"
      + w2 + "*cpx," + w2 + "*cpy,"
      + w2 + "*" + gddx + "," + w2 + "*" + gddy + ","
      + w2 + ";");
}

// Exit construction: physical variables receive damped writes toward the
// chart-determined targets; chart frozen; tp frozen.
//   X = G - b g = G + (5/9) g,  Y = a g - alpha G = (16/21) g - (3/7) G
//   [with D = -1: X = cg + (5/9) g ... see header]
// Wait: X = G - b g with b = -5/9 gives X = G + (5/9) g.
//       Y = a g - alpha G = (16/21) g - (3/7) G.
// Velocities identically with gdot = 2 w z / |w|^2 and P.
Map make_exit_field() {
  const std::string w2 = "(wr^2+wi^2)";
  const std::string gx = "(wr^2-wi^2)";
  const std::string gy = "(2*wr*wi)";
  const std::string gdx = "(2*(wr*zr-wi*zi)/" + w2 + ")";
  const std::string gdy = "(2*(wr*zi+wi*zr)/" + w2 + ")";
  const std::string xt1 = "(cgx+5*" + gx + "/9)";
  const std::string xt2 = "(cgy+5*" + gy + "/9)";
  const std::string yt1 = "(16*" + gx + "/21-3*cgx/7)";
  const std::string yt2 = "(16*" + gy + "/21-3*cgy/7)";
  const std::string vx1 = "(cpx+5*" + gdx + "/9)";
  const std::string vx2 = "(cpy+5*" + gdy + "/9)";
  const std::string vy1 = "(16*" + gdx + "/21-3*cpx/7)";
  const std::string vy2 = "(16*" + gdy + "/21-3*cpy/7)";
  return Map(
      "par:e1,e2,e3,e4,e5,e6,e7,e8;" + std::string(kVars).substr(0) +
      "fun:"
      "400*(" + xt1 + "-x1)+e1,"
      "400*(" + xt2 + "-x2)+e2,"
      "400*(" + yt1 + "-y1)+e3,"
      "400*(" + yt2 + "-y2)+e4,"
      "400*(" + vx1 + "-p1)+e5,"
      "400*(" + vx2 + "-p2)+e6,"
      "400*(" + vy1 + "-q1)+e7,"
      "400*(" + vy2 + "-q2)+e8,"
      "0,0,0,0,0,0,0,0,0,0;");
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
  if (!contains_zero(sc.i_dot)) return true;
  if (sc.kinetic.leftBound() > 0) return true;
  return !contains_zero(sc.b1) || !contains_zero(sc.b2) ||
         !contains_zero(sc.b3);
}

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

// Terminal binary--escaper certificate: binary {3,1}, escaper body 2,
// eta = 4 (identical to burrau_event_certificate_capd.cpp).
bool escape_certificate_fires(const Vector& s, Ival* margin_out) {
  const Ival eta = Ival(4);
  const Ival &x1 = s[0], &x2 = s[1], &y1 = s[2], &y2 = s[3];
  const Ival &u1 = s[4], &u2 = s[5], &v1 = s[6], &v2 = s[7];
  const Ival kPairMass12 = Ival(7) / Ival(5);
  const Ival kTotalMass = Ival(12) / Ival(5);
  const Ival q3x = (kPairMass12 / kTotalMass) * y1;
  const Ival q3y = (kPairMass12 / kTotalMass) * y2;
  const Ival c12x = -(kM3() / kTotalMass) * y1;
  const Ival c12y = -(kM3() / kTotalMass) * y2;
  const Ival q1x = c12x - (kM2() / kPairMass12) * x1;
  const Ival q1y = c12y - (kM2() / kPairMass12) * x2;
  const Ival q2x = c12x + (kM1() / kPairMass12) * x1;
  const Ival q2y = c12y + (kM1() / kPairMass12) * x2;
  const Ival w3x = (kPairMass12 / kTotalMass) * v1;
  const Ival w3y = (kPairMass12 / kTotalMass) * v2;
  const Ival e12x = -(kM3() / kTotalMass) * v1;
  const Ival e12y = -(kM3() / kTotalMass) * v2;
  const Ival w1x = e12x - (kM2() / kPairMass12) * u1;
  const Ival w1y = e12y - (kM2() / kPairMass12) * u2;
  const Ival w2x = e12x + (kM1() / kPairMass12) * u1;
  const Ival w2y = e12y + (kM1() / kPairMass12) * u2;

  const Ival pair_mass = kM3() + kM1();
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
  const Ival radial_margin = rho_dot * rho_dot / 2 - kTotalMass / separation;
  if (!(radial_margin.leftBound() > 0)) return false;
  const Ival speed_floor = sqrt(2 * radial_margin);
  const Ival allowance = kM2() * sqrt(2 * pair_mass * radius_bound) /
                         (speed_floor * separation * separation);
  const Ival inner_margin = -eta - inner_energy - allowance;
  if (margin_out != nullptr) *margin_out = inner_margin;
  return inner_margin.leftBound() > 0;
}

double hull_width(const Vector& s, int n) {
  double w = 0;
  for (int i = 0; i < n; ++i) {
    w = std::max(w, bound_double(s[i].rightBound() - s[i].leftBound()));
  }
  return w;
}

Ival pair_g_sq(const Vector& s) {
  const Ival g1 = s[2] + 3 * s[0] / 7;
  const Ival g2 = s[3] + 3 * s[1] / 7;
  return g1 * g1 + g2 * g2;
}

struct PhaseRunner {
  Solver solver;
  std::unique_ptr<TimeMap> tm;
  double step_cap = 1e6;
  double cap_ceiling = 1e6;
  long capped_retries = 0;
  long successes = 0;

  explicit PhaseRunner(Map& field, int order, double tol)
      : solver(field, order) {
    solver.setAbsoluteTolerance(tol);
    solver.setRelativeTolerance(tol);
    tm.reset(new TimeMap(solver));
    tm->stopAfterStep(true);
  }

  // One direct solver step (no time map): respects setMaxStep, keeps the
  // set's clock a sum of exact machine steps.  Used inside the LC zone,
  // where the step cap must actually bind (ITimeMap overrides maxStep,
  // and target arithmetic compounds the time-interval width).
  void direct_move(Set& set, double cap) {
    for (;;) {
      try {
        solver.setMaxStep(Ival(cap));
        set.move(solver);
        return;
      } catch (const std::exception&) {
        ++capped_retries;
        if (capped_retries > 200000 || cap < 1e-14) throw;
        cap /= 2;
      }
    }
  }

  // One accepted step toward target; returns false when target reached.
  bool step(const Ival& target, Set& set) {
    for (;;) {
      try {
        solver.setMaxStep(Ival(step_cap));
        (*tm)(target, set);
      } catch (const std::exception&) {
        ++capped_retries;
        successes = 0;
        if (capped_retries > 200000 || step_cap < 1e-14) throw;
        const double last = bound_double(solver.getStep().rightBound());
        const double ref = (last > 1e-13 && last < step_cap) ? last : step_cap;
        step_cap = ref / 2;
        tm.reset(new TimeMap(solver));
        tm->stopAfterStep(true);
        continue;
      }
      if (step_cap < cap_ceiling && ++successes >= 40) {
        step_cap = std::min(step_cap * 2, cap_ceiling);
        successes = 0;
      }
      if (tm->completed() &&
          to_double(tm->getCurrentTime()) <
              bound_double(target.leftBound()) - 1e-9) {
        tm.reset(new TimeMap(solver));
        tm->stopAfterStep(true);
        continue;
      }
      return !tm->completed();
    }
  }
};

}  // namespace

int main(int argc, char** argv) {
  const int precision = argc > 1 ? std::atoi(argv[1]) : 512;
  const double tolerance = argc > 2 ? std::atof(argv[2]) : 1e-110;
  const int order = argc > 3 ? std::atoi(argv[3]) : 80;
  capd::MpFloat::setDefaultPrecision(precision);
  try {
    Map physical_field = make_physical_field();
    Map lc_field = make_lc_field();
    Map exit_field = make_exit_field();
    const Ival eps_exit =
        Ival(-1, 1) * (Ival(1) / Ival(10)) / exp(Ival(380));
    for (int i = 1; i <= 8; ++i) {
      exit_field.setParameter("e" + std::to_string(i), eps_exit);
    }

    Vector initial(18);
    for (int i = 0; i < 18; ++i) initial[i] = Ival(0);
    initial[0] = Ival(1);
    initial[2] = Ival(-12) / Ival(175);
    initial[3] = Ival(12) / Ival(25);
    Set set(initial);

    const Ival t1 = Ival(1) / Ival(4);
    const double escape_check_start = 11.5;
    // Zone thresholds: enter below 1/1000 (only the t=3.166 encounter,
    // r13 ~ 8.3e-5, goes that deep; the t=0.376 encounter bottoms at
    // 2.8e-3), exit above 1/500; brake-free zone bound
    // |g| < 1/4 < m1 m3 / U0 = 240/769.
    const Ival rho_in_sq = Ival(1) / Ival(1000000);
    const Ival rho_out = Ival(1) / Ival(500);
    const Ival zone_bound = Ival(1) / Ival(4);

    long steps = 0;
    long event_steps = 0;
    double min_event_kinetic = 1e300;
    bool initial_phase = true;
    bool lc_used = false;
    bool certified = false;
    Ival final_margin;

    std::cout << std::setprecision(17);

    // Physical phases interleaved with at most one LC passage.
    std::unique_ptr<PhaseRunner> phys(
        new PhaseRunner(physical_field, order, tolerance));
    Ival phys_target = set.getCurrentTime() + Ival(25);

    for (;;) {
      const bool more = phys->step(phys_target, set);
      ++steps;
      const Vector enclosure = set.getLastEnclosure();
      const Vector snapshot(set);
      const Ival tp = snapshot[17];
      const Scalars sc = evaluate_scalars(enclosure, initial_phase);

      if (initial_phase) {
        if (!(sc.potential.rightBound() < (2 * kU0()).leftBound())) {
          std::cerr << "FAIL initial-window potential bound at tp="
                    << to_double(tp) << "\n";
          return 1;
        }
        if (tp.leftBound() > t1.rightBound()) initial_phase = false;
      } else {
        if (!step_excludes_brake(sc) && !positions_exclude_brake(enclosure)) {
          std::cerr << "FAIL uncovered physical step at tp=" << to_double(tp)
                    << "\n";
          return 1;
        }
        if (contains_zero(sc.i_dot)) {
          ++event_steps;
          min_event_kinetic = std::min(min_event_kinetic,
                                       bound_double(sc.kinetic.leftBound()));
        }
      }

      if (steps % 500 == 0) {
        std::cout << "phys tp=" << to_double(tp) << " steps=" << steps
                  << " hull_width=" << hull_width(snapshot, 8)
                  << " retries=" << phys->capped_retries << "\n"
                  << std::flush;
      }

      if (bound_double(tp.rightBound()) > escape_check_start) {
        if (escape_certificate_fires(snapshot, &final_margin)) {
          certified = true;
          std::cout << "escape certificate fired at tp=" << to_double(tp)
                    << " margin=" << bound_double(final_margin.leftBound())
                    << "\n";
          break;
        }
      }
      if (bound_double(tp.leftBound()) > 14.5) {
        std::cerr << "FAIL tp exceeded 14.5 without escape certificate\n";
        return 1;
      }
      if (!more) {
        std::cerr << "FAIL phase clock bound reached\n";
        return 1;
      }

      // Zone entry test on the post-step snapshot.
      const Ival gsq = pair_g_sq(snapshot);
      if (!lc_used && gsq.rightBound() < rho_in_sq.leftBound()) {
        lc_used = true;
        std::cout << "LC entry at tp=" << to_double(tp)
                  << " |g|^2<" << bound_double(gsq.rightBound())
                  << " hull_width=" << hull_width(snapshot, 8) << "\n"
                  << std::flush;

        // Entry-branch selection by the sign of gx (form B is valid for
        // any g off the positive real axis, i.e. whenever gy != 0 or
        // gx < 0; form A off the negative axis).
        const Ival gx = snapshot[2] + 3 * snapshot[0] / 7;
        const Ival gy = snapshot[3] + 3 * snapshot[1] / 7;
        bool form_a;
        if (gx.leftBound() > 0) {
          form_a = true;
        } else if (gx.rightBound() < 0 ||
                   gy.leftBound() > 0 || gy.rightBound() < 0) {
          form_a = false;
        } else {
          std::cerr << "FAIL cannot certify entry branch\n";
          return 1;
        }
        {
          Map entry_field = make_entry_field(form_a);
          PhaseRunner entry(entry_field, 20, 1e-30);
          const Ival target = set.getCurrentTime() + Ival(1);
          while (entry.step(target, set)) {
          }
          // Guard: the chart block must now be genuinely written.
          const Vector post_entry(set);
          const Ival w2chk = post_entry[8] * post_entry[8] +
                             post_entry[9] * post_entry[9];
          if (!(w2chk.leftBound() > 0)) {
            std::cerr << "FAIL entry construction did not write the chart\n";
            return 1;
          }
          if (std::getenv("FABLE_DEBUG") != nullptr) {
            std::cout << "entry form_a=" << form_a;
            for (int i = 8; i < 18; ++i) {
              std::cout << " v" << i << "="
                        << bound_double(post_entry[i].leftBound());
            }
            std::cout << "\n" << std::flush;
          }
        }

        // LC passage.
        {
          PhaseRunner lc(lc_field, order, tolerance);
          // Small sigma-steps keep each step's swept enclosure of w well
          // inside a disc that excludes w = 0 (|w| ~ 9e-3 at closest
          // approach, |dw/dsigma| ~ 1), so the per-step no-collision check
          // certifies the strong collision-free statement.  Direct solver
          // moves make the cap actually bind.
          const double lc_cap = 1.0 / 4000.0;
          long lc_steps = 0;
          for (;;) {
            lc.direct_move(set, lc_cap);
            const bool lc_more = lc_steps < 20000;
            ++lc_steps;
            const Vector lc_enc = set.getLastEnclosure();
            const Ival w2enc =
                lc_enc[8] * lc_enc[8] + lc_enc[9] * lc_enc[9];
            if (!(w2enc.leftBound() > 0)) {
              std::cerr << "FAIL possible collision inside LC zone\n";
              return 1;
            }
            if (!(w2enc.rightBound() <
                  bound_double(zone_bound.leftBound()))) {
              std::cerr << "FAIL LC path left the certified zone bound\n";
              return 1;
            }
            const Vector lc_snap(set);
            const Ival w2 =
                lc_snap[8] * lc_snap[8] + lc_snap[9] * lc_snap[9];
            if (std::getenv("FABLE_DEBUG") != nullptr && lc_steps % 5 == 1) {
              std::cout << "lc step " << lc_steps << " |w|2="
                        << bound_double(w2.leftBound()) << " wr="
                        << bound_double(lc_snap[8].leftBound()) << " wi="
                        << bound_double(lc_snap[9].leftBound()) << " tp="
                        << to_double(lc_snap[17])
                        << " encw2left=" << bound_double(
                               (set.getLastEnclosure()[8] *
                                    set.getLastEnclosure()[8] +
                                set.getLastEnclosure()[9] *
                                    set.getLastEnclosure()[9])
                                   .leftBound()) << "\n"
                      << std::flush;
            }
            if (w2.leftBound() > rho_out.rightBound()) {
              std::cout << "LC exit after " << lc_steps
                        << " sigma-steps at tp=" << to_double(lc_snap[17])
                        << " |g|>" << bound_double(w2.leftBound())
                        << " hull_width=" << hull_width(lc_snap, 18)
                        << " retries=" << lc.capped_retries << "\n"
                        << std::flush;
              break;
            }
            if (!lc_more) {
              std::cerr << "FAIL LC phase hit sigma bound without exit\n";
              return 1;
            }
          }
        }

        // Exit construction after a boundedness check.
        {
          const Vector pre(set);
          for (int i = 0; i < 18; ++i) {
            if (!(pre[i].rightBound() < 100 && pre[i].leftBound() > -100)) {
              std::cerr << "FAIL exit boundedness check\n";
              return 1;
            }
          }
          PhaseRunner exitr(exit_field, 20, 1e-30);
          const Ival target = set.getCurrentTime() + Ival(1);
          while (exitr.step(target, set)) {
          }
          const Vector post(set);
          std::cout << "exit construction done tp=" << to_double(post[17])
                    << " hull_width=" << hull_width(post, 8) << "\n"
                    << std::flush;
        }

        // Resume physical integration with a fresh runner.
        phys.reset(new PhaseRunner(physical_field, order, tolerance));
        phys_target = set.getCurrentTime() + Ival(25);
      }
    }

    if (!certified) {
      std::cerr << "FAIL terminal escape certificate did not fire\n";
      return 1;
    }
    const Vector final_state(set);
    std::cout << "steps=" << steps << " event_steps=" << event_steps
              << " min_event_kinetic=" << min_event_kinetic
              << " final_hull_width=" << hull_width(final_state, 8) << "\n";
    std::cout << "PASS_BURRAU_LC\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FAIL exception: " << error.what() << "\n";
    return 1;
  }
}
