// Rigorous second-brake exclusion certificate for the 3:4:5 Pythagorean
// Burrau free-fall problem (u = 1/3), plus parameter-interval prefix and
// maximum-event modes, with pair-{1,3} and pair-{2,3} Levi--Civita charts.
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
//
// Additional usage:
//   burrau_lc_certificate_capd iprefix P Q P2 Q2 TEND [PREC TOL ORDER]
// proves absence of a labelled brake on the complete collision-free prefix
// 0 < t <= TEND for every u in [P/Q,P2/Q2].  It makes no terminal escape
// claim.  `ilcprefix` uses the direct parameterized LC graph, while `ilcmax`
// and `ilcmax2` target the first and second positive inertia maxima.  The
// legacy invocation `[PREC TOL ORDER]` remains the full u=1/3
// collision-free/escape certificate.

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "capd/mpcapdlib.h"
#include "capd/dynsys/DynSysMap.h"

namespace {

typedef capd::MpInterval Ival;
typedef capd::MpIMap Map;
typedef capd::MpIOdeSolver Solver;
typedef capd::MpITimeMap TimeMap;
typedef capd::MpIVector Vector;
typedef capd::MpIMatrix Matrix;
typedef capd::MpC0TripletonSet Set;
typedef capd::MpC1Rect2Set C1Set;
typedef capd::MpINonlinearSection NonlinearSection;
typedef capd::MpICoordinateSection CoordinateSection;
typedef capd::MpIPoincareMap PoincareMap;

double bound_double(const capd::MpFloat& x) { return toDouble(x); }
double to_double(const Ival& x) { return bound_double(x.rightBound()); }

// Masses for the legacy u = 1/3 terminal certificate.
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

struct Family {
  Ival a;
  Ival b;
  Ival m12;
  Ival total;
  Ival mu1;
  Ival mu2;
  Ival u0;
  Ival alpha;
  Ival beta;
  Ival m13;
  Ival inv_m13;
  Ival ag;
  Ival bg;
};

Family make_family(const Ival& w) {
  Family f;
  const Ival w2 = w * w;
  const Ival q = 1 + w2;
  f.a = (1 - w2) / q;
  f.b = 2 * w / q;
  f.m12 = f.a + f.b;
  f.total = f.m12 + 1;
  f.mu1 = f.a * f.b / f.m12;
  f.mu2 = f.m12 / f.total;
  f.u0 = f.a * f.b + 1 / (f.a * f.b);
  f.alpha = f.b / f.m12;
  f.beta = f.a / f.m12;
  f.m13 = f.a + 1;
  f.inv_m13 = 1 / f.m13;
  f.ag = 1 - f.alpha / f.m13;
  f.bg = -f.inv_m13;
  return f;
}

const char* kVars =
    "var:x1,x2,y1,y2,p1,p2,q1,q2,wr,wi,zr,zi,hh,cgx,cgy,cpx,cpy,tp,ww;";

// State layout: physical X=(x1,x2), Y=(y1,y2), VX=(p1,p2), VY=(q1,q2);
// chart w=(wr,wi), z=(zr,zi), pair energy hh, complement G=(cgx,cgy),
// P=(cpx,cpy); physical time tp; frozen Euclid parameter ww.

Map make_physical_field() {
  const std::string mass_den = "(1+ww^2)";
  const std::string pair_den = "(1+2*ww-ww^2)";
  const std::string ma = "((1-ww^2)/" + mass_den + ")";
  const std::string mb = "(2*ww/" + mass_den + ")";
  const std::string m12 = "(" + pair_den + "/" + mass_den + ")";
  const std::string total = "(2*(1+ww)/" + mass_den + ")";
  const std::string alpha = "(2*ww/" + pair_den + ")";
  const std::string beta = "((1-ww^2)/" + pair_den + ")";
  const std::string d1sq =
      "((y1+" + alpha + "*x1)^2+(y2+" + alpha + "*x2)^2)";
  const std::string d2sq =
      "((y1-" + beta + "*x1)^2+(y2-" + beta + "*x2)^2)";
  const std::string rsq = "(x1^2+x2^2)";
  const std::string inv_r3 = "(" + rsq + "*sqrt(" + rsq + "))";
  const std::string inv_d13 = "(" + d1sq + "*sqrt(" + d1sq + "))";
  const std::string inv_d23 = "(" + d2sq + "*sqrt(" + d2sq + "))";
  return Map(std::string(kVars) +
      "fun:p1,p2,q1,q2,"
      "-" + m12 + "*x1/" + inv_r3 +
      "+(y1-" + beta + "*x1)/" + inv_d23 +
      "-(y1+" + alpha + "*x1)/" + inv_d13 + ","
      "-" + m12 + "*x2/" + inv_r3 +
      "+(y2-" + beta + "*x2)/" + inv_d23 +
      "-(y2+" + alpha + "*x2)/" + inv_d13 + ","
      "-(" + total + "/" + m12 + ")*(" + ma +
      "*(y1+" + alpha + "*x1)/" + inv_d13 + "+" + mb +
      "*(y1-" + beta + "*x1)/" + inv_d23 + "),"
      "-(" + total + "/" + m12 + ")*(" + ma +
      "*(y2+" + alpha + "*x2)/" + inv_d13 + "+" + mb +
      "*(y2-" + beta + "*x2)/" + inv_d23 + "),"
      "0,0,0,0,0,0,0,0,0,1,0;");
}

// Time-one graph embedding of the exact tied initial configuration over ww.
Map make_initial_graph_field() {
  const std::string p = "(1+2*ww-ww^2)";
  const std::string q = "(1+ww^2)";
  const std::string y1 =
      "(2*ww*(1-ww^2)*(ww^2+2*ww-1)/(" + q + "^2*" + p + "))";
  const std::string y2 = "(2*ww*(1-ww^2)/" + q + "^2)";
  return Map(std::string(kVars) + "fun:0,0," + y1 + "," + y2 +
             ",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0;");
}

// Entry construction: chart block is zero; each rate is the exact target,
// a function of the frozen physical variables, so time-1 writes it.
// Form A (gx > 0):  wr = sqrt((|g|+gx)/2), wi = gy/(2 wr).
// Form B (gx < 0):  wi = sqrt((|g|-gx)/2), wr = gy/(2 wi).
// g = Y + (3/7) X, gdot = VY + (3/7) VX.
Map make_entry_field(bool form_a, int damping_rate) {
  const std::string pden = "(1+2*ww-ww^2)";
  const std::string qden = "(1+ww^2)";
  const std::string alpha = "(2*ww/" + pden + ")";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string ag = "(1-ww*" + qden + "/" + pden + ")";
  const std::string bg = "(-" + inv_m13 + ")";
  const std::string m13 = "(2/" + qden + ")";
  const std::string gx = "(y1+" + alpha + "*x1)";
  const std::string gy = "(y2+" + alpha + "*x2)";
  const std::string gdx = "(q1+" + alpha + "*p1)";
  const std::string gdy = "(q2+" + alpha + "*p2)";
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
      "((" + gdx + "^2+" + gdy + "^2)/2-" + m13 + "/" + absg + ")";
  const std::string rate = std::to_string(damping_rate);
  // Damped writes (c = 400) with inflation parameters so re-entry into a
  // stale chart block is exact up to a rigorously enclosed e^{-400}
  // residual; on a zero block the same flow is equally valid.
  return Map(
      "par:f1,f2,f3,f4,f5,f6,f7,f8,f9;" + std::string(kVars) +
      "fun:0,0,0,0,0,0,0,0,"
      + rate + "*(" + wr_t + "-wr)+f1,"
      + rate + "*(" + wi_t + "-wi)+f2,"
      + rate + "*(" + zr_t + "-zr)+f3,"
      + rate + "*(" + zi_t + "-zi)+f4,"
      + rate + "*(" + h_t + "-hh)+f5,"
      + rate + "*(" + ag + "*x1+" + bg + "*y1-cgx)+f6,"
      + rate + "*(" + ag + "*x2+" + bg + "*y2-cgy)+f7,"
      + rate + "*(" + ag + "*p1+" + bg + "*q1-cpx)+f8,"
      + rate + "*(" + ag + "*p2+" + bg + "*q2-cpy)+f9,0,0;");
}

// LC-zone field in sigma.
Map make_lc_field() {
  const std::string qden = "(1+ww^2)";
  const std::string ma = "((1-ww^2)/" + qden + ")";
  const std::string mb = "(2*ww/" + qden + ")";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string total_over_m13 = "(1+ww)";
  const std::string w2 = "(wr^2+wi^2)";
  const std::string gx = "(wr^2-wi^2)";
  const std::string gy = "(2*wr*wi)";
  // d21 = q2-q1 = G + g/M13; d23 = q2-q3 = d21-g.
  const std::string d21x = "(cgx+" + inv_m13 + "*" + gx + ")";
  const std::string d21y = "(cgy+" + inv_m13 + "*" + gy + ")";
  const std::string d23x =
      "(cgx+(" + inv_m13 + "-1)*" + gx + ")";
  const std::string d23y =
      "(cgy+(" + inv_m13 + "-1)*" + gy + ")";
  const std::string r12sq = "(" + d21x + "^2+" + d21y + "^2)";
  const std::string r23sq = "(" + d23x + "^2+" + d23y + "^2)";
  const std::string ir12 = "(" + r12sq + "*sqrt(" + r12sq + "))";
  const std::string ir23 = "(" + r23sq + "*sqrt(" + r23sq + "))";
  // F_ext on g: m2 (d23/r23^3 - d21/r12^3).
  const std::string fx = "(" + mb + "*(" + d23x + "/" + ir23 + "-" + d21x + "/" + ir12 + "))";
  const std::string fy = "(" + mb + "*(" + d23y + "/" + ir23 + "-" + d21y + "/" + ir12 + "))";
  // G'' = -(M/M13)(m1 d21/r12^3 + m3 d23/r23^3).
  const std::string gddx =
      "(-" + total_over_m13 + "*(" + ma + "*" + d21x + "/" + ir12 + "+" + d23x + "/" + ir23 + "))";
  const std::string gddy =
      "(-" + total_over_m13 + "*(" + ma + "*" + d21y + "/" + ir12 + "+" + d23y + "/" + ir23 + "))";
  return Map(std::string(kVars) +
      "fun:0,0,0,0,0,0,0,0,"
      "zr,zi,"
      "(hh/2)*wr+(" + w2 + "/2)*(wr*" + fx + "+wi*" + fy + "),"
      "(hh/2)*wi+(" + w2 + "/2)*(wr*" + fy + "-wi*" + fx + "),"
      "2*((wr*zr-wi*zi)*" + fx + "+(wr*zi+wi*zr)*" + fy + "),"
      + w2 + "*cpx," + w2 + "*cpy,"
      + w2 + "*" + gddx + "," + w2 + "*" + gddy + ","
      + w2 + ",0;");
}

const char* kDirectLcVars =
    "var:wr,wi,zr,zi,hh,cgx,cgy,cpx,cpy,tp,ww,jd;";

// The same selected-pair regularization without the frozen physical/chart
// blocks.  This chart is nonsingular from the tied launch through the early
// maximum-event branch and avoids both entry and exit time-shift wrapping.
Map make_direct_lc_field(bool energy_leaf_h = false) {
  const std::string qden = "(1+ww^2)";
  const std::string ma = "((1-ww^2)/" + qden + ")";
  const std::string mb = "(2*ww/" + qden + ")";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string total_over_m13 = "(1+ww)";
  const std::string w2 = "(wr^2+wi^2)";
  const std::string gx = "(wr^2-wi^2)";
  const std::string gy = "(2*wr*wi)";
  const std::string d21x = "(cgx+" + inv_m13 + "*" + gx + ")";
  const std::string d21y = "(cgy+" + inv_m13 + "*" + gy + ")";
  const std::string d23x =
      "(cgx+(" + inv_m13 + "-1)*" + gx + ")";
  const std::string d23y =
      "(cgy+(" + inv_m13 + "-1)*" + gy + ")";
  const std::string r12sq = "(" + d21x + "^2+" + d21y + "^2)";
  const std::string r23sq = "(" + d23x + "^2+" + d23y + "^2)";
  const std::string ir12 = "(" + r12sq + "*sqrt(" + r12sq + "))";
  const std::string ir23 = "(" + r23sq + "*sqrt(" + r23sq + "))";
  const std::string fx =
      "(" + mb + "*(" + d23x + "/" + ir23 + "-" + d21x +
      "/" + ir12 + "))";
  const std::string fy =
      "(" + mb + "*(" + d23y + "/" + ir23 + "-" + d21y +
      "/" + ir12 + "))";
  const std::string gddx =
      "(-" + total_over_m13 + "*(" + ma + "*" + d21x + "/" +
      ir12 + "+" + d23x + "/" + ir23 + "))";
  const std::string gddy =
      "(-" + total_over_m13 + "*(" + ma + "*" + d21y + "/" +
      ir12 + "+" + d23y + "/" + ir23 + "))";
  const std::string ab = "(" + ma + "*" + mb + ")";
  const std::string u0 = "(" + ab + "+1/" + ab + ")";
  const std::string pair_mu = "(" + ma + "/(1+" + ma + "))";
  const std::string complement_mu =
      "(" + mb + "*(1+" + ma + ")/(1+" + ma + "+" + mb + "))";
  // Restrict the regularized flow to the exact total-energy leaf H=-U0.
  // Since H=mu13*h+(muG/2)|P|^2-AB/r12-B/r23, this expression for h
  // has no selected-pair 0/0 cancellation and stays regular at w=0 as
  // long as the two unselected pairs remain separated.
  const std::string h_from_energy =
      "((-" + u0 + "-(" + complement_mu + "/2)*(cpx^2+cpy^2)+" +
      ab + "/sqrt(" + r12sq + ")+" + mb + "/sqrt(" + r23sq + "))/" +
      pair_mu + ")";
  const std::string h_used =
      energy_leaf_h ? h_from_energy : "hh";
  const std::string h_sigma =
      energy_leaf_h
          ? "0"
          : "2*((wr*zr-wi*zi)*" + fx +
                "+(wr*zi+wi*zr)*" + fy + ")";
  // jd = dI/dt.  Multiplication by dt/dsigma=|w|^2 cancels the selected
  // A/|g| potential term, leaving a field regular at w=0.
  const std::string jd_sigma =
      "(2*(" + ab + "*" + w2 + "/sqrt(" + r12sq + ")+" + ma +
      "+" + mb + "*" + w2 + "/sqrt(" + r23sq + "))-4*" + u0 +
      "*" + w2 + ")";
  return Map(std::string(kDirectLcVars) + "fun:zr,zi," +
             "(" + h_used + "/2)*wr+(" + w2 + "/2)*(wr*" + fx +
             "+wi*" + fy + ")," +
             "(" + h_used + "/2)*wi+(" + w2 + "/2)*(wr*" + fy +
             "-wi*" + fx + ")," + h_sigma + "," +
             w2 + "*cpx," + w2 + "*cpy," + w2 + "*" + gddx + "," +
             w2 + "*" + gddy + "," + w2 + ",0," + jd_sigma + ";");
}

// Direct Levi--Civita field for selected pair {2,3}, with
// g=q3-q2 and complement G=q1-C23.  The state layout is unchanged.
Map make_pair23_lc_field(bool energy_leaf_h = false) {
  const std::string qden = "(1+ww^2)";
  const std::string ma = "((1-ww^2)/" + qden + ")";
  const std::string mb = "(2*ww/" + qden + ")";
  const std::string m23 = "((1+ww)^2/" + qden + ")";
  const std::string inv_m23 = "(" + qden + "/(1+ww)^2)";
  const std::string total_over_m23 = "(2/(1+ww))";
  const std::string w2 = "(wr^2+wi^2)";
  const std::string gx = "(wr^2-wi^2)";
  const std::string gy = "(2*wr*wi)";
  const std::string d12x = "(cgx+" + inv_m23 + "*" + gx + ")";
  const std::string d12y = "(cgy+" + inv_m23 + "*" + gy + ")";
  const std::string d13x =
      "(cgx+(" + inv_m23 + "-1)*" + gx + ")";
  const std::string d13y =
      "(cgy+(" + inv_m23 + "-1)*" + gy + ")";
  const std::string r12sq = "(" + d12x + "^2+" + d12y + "^2)";
  const std::string r13sq = "(" + d13x + "^2+" + d13y + "^2)";
  const std::string ir12 = "(" + r12sq + "*sqrt(" + r12sq + "))";
  const std::string ir13 = "(" + r13sq + "*sqrt(" + r13sq + "))";
  const std::string fx =
      "(" + ma + "*(" + d13x + "/" + ir13 + "-" + d12x +
      "/" + ir12 + "))";
  const std::string fy =
      "(" + ma + "*(" + d13y + "/" + ir13 + "-" + d12y +
      "/" + ir12 + "))";
  const std::string gddx =
      "(-" + total_over_m23 + "*(" + mb + "*" + d12x + "/" +
      ir12 + "+" + d13x + "/" + ir13 + "))";
  const std::string gddy =
      "(-" + total_over_m23 + "*(" + mb + "*" + d12y + "/" +
      ir12 + "+" + d13y + "/" + ir13 + "))";
  const std::string ab = "(" + ma + "*" + mb + ")";
  const std::string u0 = "(" + ab + "+1/" + ab + ")";
  const std::string pair_mu = "(" + mb + "/" + m23 + ")";
  const std::string complement_mu =
      "(" + ma + "*" + m23 + "/(1+" + ma + "+" + mb + "))";
  // H=mu23*h+(muG/2)|P|^2-AB/r12-A/r13 on this Jacobi tree.
  const std::string h_from_energy =
      "((-" + u0 + "-(" + complement_mu + "/2)*(cpx^2+cpy^2)+" +
      ab + "/sqrt(" + r12sq + ")+" + ma + "/sqrt(" + r13sq + "))/" +
      pair_mu + ")";
  const std::string h_used =
      energy_leaf_h ? h_from_energy : "hh";
  const std::string h_sigma =
      energy_leaf_h
          ? "0"
          : "2*((wr*zr-wi*zi)*" + fx +
                "+(wr*zi+wi*zr)*" + fy + ")";
  const std::string jd_sigma =
      "(2*(" + ab + "*" + w2 + "/sqrt(" + r12sq + ")+" + mb +
      "+" + ma + "*" + w2 + "/sqrt(" + r13sq + "))-4*" + u0 +
      "*" + w2 + ")";
  return Map(std::string(kDirectLcVars) + "fun:zr,zi," +
             "(" + h_used + "/2)*wr+(" + w2 + "/2)*(wr*" + fx +
             "+wi*" + fy + ")," +
             "(" + h_used + "/2)*wi+(" + w2 + "/2)*(wr*" + fy +
             "-wi*" + fx + ")," + h_sigma + "," +
             w2 + "*cpx," + w2 + "*cpy," + w2 + "*" + gddx + "," +
             w2 + "*" + gddy + "," + w2 + ",0," + jd_sigma + ";");
}

Map make_pair13_to_pair23_map(bool dummy_h = false) {
  const std::string qden = "(1+ww^2)";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string inv_m23 = "(" + qden + "/(1+ww)^2)";
  const std::string m23 = "((1+ww)^2/" + qden + ")";
  const std::string old_w2 = "(wr^2+wi^2)";
  const std::string old_gx = "(wr^2-wi^2)";
  const std::string old_gy = "(2*wr*wi)";
  const std::string old_gdx =
      "(2*(wr*zr-wi*zi)/" + old_w2 + ")";
  const std::string old_gdy =
      "(2*(wr*zi+wi*zr)/" + old_w2 + ")";
  const std::string old_xx =
      "(cgx+" + inv_m13 + "*" + old_gx + ")";
  const std::string old_xy =
      "(cgy+" + inv_m13 + "*" + old_gy + ")";
  const std::string old_xdx =
      "(cpx+" + inv_m13 + "*" + old_gdx + ")";
  const std::string old_xdy =
      "(cpy+" + inv_m13 + "*" + old_gdy + ")";
  // g23=q3-q2=g13-X13.
  const std::string gx = "(" + old_gx + "-" + old_xx + ")";
  const std::string gy = "(" + old_gy + "-" + old_xy + ")";
  const std::string gdx = "(" + old_gdx + "-" + old_xdx + ")";
  const std::string gdy = "(" + old_gdy + "-" + old_xdy + ")";
  const std::string abs_g = "sqrt(" + gx + "^2+" + gy + "^2)";
  const std::string new_wr = "sqrt((" + abs_g + "+" + gx + ")/2)";
  const std::string new_wi = "(" + gy + "/(2*" + new_wr + "))";
  const std::string new_zr =
      "((" + new_wr + "*" + gdx + "+" + new_wi + "*" + gdy + ")/2)";
  const std::string new_zi =
      "((" + new_wr + "*" + gdy + "-" + new_wi + "*" + gdx + ")/2)";
  const std::string new_h =
      "((" + gdx + "^2+" + gdy + "^2)/2-" + m23 + "/" + abs_g + ")";
  // d12=q1-q2=-X13=G23+g23/M23.
  const std::string new_gx =
      "(-" + old_xx + "-" + inv_m23 + "*" + gx + ")";
  const std::string new_gy =
      "(-" + old_xy + "-" + inv_m23 + "*" + gy + ")";
  const std::string new_px =
      "(-" + old_xdx + "-" + inv_m23 + "*" + gdx + ")";
  const std::string new_py =
      "(-" + old_xdy + "-" + inv_m23 + "*" + gdy + ")";
  const std::string h_output = dummy_h ? "0" : new_h;
  return Map(std::string(kDirectLcVars) + "fun:" + new_wr + "," +
             new_wi + "," + new_zr + "," + new_zi + "," + h_output +
             "," + new_gx + "," + new_gy + "," + new_px + "," +
             new_py + ",tp,ww,jd;");
}

Map make_pair23_to_pair13_map(bool dummy_h = false) {
  const std::string qden = "(1+ww^2)";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string inv_m23 = "(" + qden + "/(1+ww)^2)";
  const std::string m13 = "(2/" + qden + ")";
  const std::string old_w2 = "(wr^2+wi^2)";
  const std::string old_gx = "(wr^2-wi^2)";
  const std::string old_gy = "(2*wr*wi)";
  const std::string old_gdx =
      "(2*(wr*zr-wi*zi)/" + old_w2 + ")";
  const std::string old_gdy =
      "(2*(wr*zi+wi*zr)/" + old_w2 + ")";
  // d12=q1-q2=G23+g23/M23, while
  // g13=q3-q1=g23-d12.
  const std::string old_d12x =
      "(cgx+" + inv_m23 + "*" + old_gx + ")";
  const std::string old_d12y =
      "(cgy+" + inv_m23 + "*" + old_gy + ")";
  const std::string old_d12dx =
      "(cpx+" + inv_m23 + "*" + old_gdx + ")";
  const std::string old_d12dy =
      "(cpy+" + inv_m23 + "*" + old_gdy + ")";
  const std::string gx = "(" + old_gx + "-" + old_d12x + ")";
  const std::string gy = "(" + old_gy + "-" + old_d12y + ")";
  const std::string gdx = "(" + old_gdx + "-" + old_d12dx + ")";
  const std::string gdy = "(" + old_gdy + "-" + old_d12dy + ")";
  const std::string abs_g = "sqrt(" + gx + "^2+" + gy + "^2)";
  const std::string new_wr = "sqrt((" + abs_g + "+" + gx + ")/2)";
  const std::string new_wi = "(" + gy + "/(2*" + new_wr + "))";
  const std::string new_zr =
      "((" + new_wr + "*" + gdx + "+" + new_wi + "*" + gdy + ")/2)";
  const std::string new_zi =
      "((" + new_wr + "*" + gdy + "-" + new_wi + "*" + gdx + ")/2)";
  const std::string new_h =
      "((" + gdx + "^2+" + gdy + "^2)/2-" + m13 + "/" + abs_g + ")";
  // X13=q2-q1=-d12=G13+g13/M13.
  const std::string new_gx =
      "(-" + old_d12x + "-" + inv_m13 + "*" + gx + ")";
  const std::string new_gy =
      "(-" + old_d12y + "-" + inv_m13 + "*" + gy + ")";
  const std::string new_px =
      "(-" + old_d12dx + "-" + inv_m13 + "*" + gdx + ")";
  const std::string new_py =
      "(-" + old_d12dy + "-" + inv_m13 + "*" + gdy + ")";
  const std::string h_output = dummy_h ? "0" : new_h;
  return Map(std::string(kDirectLcVars) + "fun:" + new_wr + "," +
             new_wi + "," + new_zr + "," + new_zi + "," + h_output +
             "," + new_gx + "," + new_gy + "," + new_px + "," +
             new_py + ",tp,ww,jd;");
}

// Exact tied launch in the direct selected-pair chart.  Since
// g=q3-q1=(B^2,AB) and |g|=B, the positive square-root branch is explicit.
Map make_direct_lc_initial_graph_field() {
  const std::string qden = "(1+ww^2)";
  const std::string pden = "(1+2*ww-ww^2)";
  const std::string ma = "((1-ww^2)/" + qden + ")";
  const std::string mb = "(2*ww/" + qden + ")";
  const std::string alpha = "(2*ww/" + pden + ")";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string m13 = "(2/" + qden + ")";
  const std::string ag = "(1-ww*" + qden + "/" + pden + ")";
  const std::string bg = "(-" + inv_m13 + ")";
  const std::string tied_yx =
      "(2*ww*(1-ww^2)*(ww^2+2*ww-1)/(" + qden + "^2*" +
      pden + "))";
  const std::string tied_yy =
      "(2*ww*(1-ww^2)/" + qden + "^2)";
  const std::string gx = "(" + mb + "^2)";
  const std::string gy = "(" + ma + "*" + mb + ")";
  const std::string wr = "sqrt((" + mb + "+" + gx + ")/2)";
  const std::string wi = "(" + gy + "/(2*" + wr + "))";
  const std::string hh = "(-" + m13 + "/" + mb + ")";
  const std::string cgx = "(" + ag + "+" + bg + "*" + tied_yx + ")";
  const std::string cgy = "(" + bg + "*" + tied_yy + ")";
  return Map(std::string(kDirectLcVars) +
             "fun:" + wr + "," + wi + ",0,0," + hh + "," + cgx +
             "," + cgy + ",0,0,0,0,0;");
}

// Exit construction: physical variables receive damped writes toward the
// chart-determined targets; chart frozen; tp frozen.
//   X = G - b g = G + (5/9) g,  Y = a g - alpha G = (16/21) g - (3/7) G
//   [with D = -1: X = cg + (5/9) g ... see header]
// Wait: X = G - b g with b = -5/9 gives X = G + (5/9) g.
//       Y = a g - alpha G = (16/21) g - (3/7) G.
// Velocities identically with gdot = 2 w z / |w|^2 and P.
Map make_exit_field(int damping_rate) {
  const std::string pden = "(1+2*ww-ww^2)";
  const std::string qden = "(1+ww^2)";
  const std::string alpha = "(2*ww/" + pden + ")";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string ag = "(1-ww*" + qden + "/" + pden + ")";
  const std::string w2 = "(wr^2+wi^2)";
  const std::string gx = "(wr^2-wi^2)";
  const std::string gy = "(2*wr*wi)";
  const std::string gdx = "(2*(wr*zr-wi*zi)/" + w2 + ")";
  const std::string gdy = "(2*(wr*zi+wi*zr)/" + w2 + ")";
  const std::string xt1 = "(cgx+" + inv_m13 + "*" + gx + ")";
  const std::string xt2 = "(cgy+" + inv_m13 + "*" + gy + ")";
  const std::string yt1 = "(" + ag + "*" + gx + "-" + alpha + "*cgx)";
  const std::string yt2 = "(" + ag + "*" + gy + "-" + alpha + "*cgy)";
  const std::string vx1 = "(cpx+" + inv_m13 + "*" + gdx + ")";
  const std::string vx2 = "(cpy+" + inv_m13 + "*" + gdy + ")";
  const std::string vy1 = "(" + ag + "*" + gdx + "-" + alpha + "*cpx)";
  const std::string vy2 = "(" + ag + "*" + gdy + "-" + alpha + "*cpy)";
  const std::string rate = std::to_string(damping_rate);
  return Map(
      "par:e1,e2,e3,e4,e5,e6,e7,e8;" + std::string(kVars).substr(0) +
      "fun:"
      + rate + "*(" + xt1 + "-x1)+e1,"
      + rate + "*(" + xt2 + "-x2)+e2,"
      + rate + "*(" + yt1 + "-y1)+e3,"
      + rate + "*(" + yt2 + "-y2)+e4,"
      + rate + "*(" + vx1 + "-p1)+e5,"
      + rate + "*(" + vx2 + "-p2)+e6,"
      + rate + "*(" + vy1 + "-q1)+e7,"
      + rate + "*(" + vy2 + "-q2)+e8,"
      "0,0,0,0,0,0,0,0,0,0,0;");
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

Scalars evaluate_scalars(const Vector& s, const Family& f,
                         bool want_potential) {
  const Ival &x1 = s[0], &x2 = s[1], &y1 = s[2], &y2 = s[3];
  const Ival &u1 = s[4], &u2 = s[5], &v1 = s[6], &v2 = s[7];
  Scalars out;
  out.i_dot =
      2 * (f.mu1 * dot(x1, x2, u1, u2) + f.mu2 * dot(y1, y2, v1, v2));
  out.kinetic =
      (f.mu1 * dot(u1, u2, u1, u2) + f.mu2 * dot(v1, v2, v1, v2)) / 2;
  out.b1 = dot(x1, x2, u1, u2) - dot(y1, y2, v1, v2);
  out.b2 = dot(u1, u2, y1, y2) + dot(x1, x2, v1, v2);
  out.b3 = cross(u1, u2, y1, y2) + cross(x1, x2, v1, v2);
  out.potential = Ival(0);
  if (want_potential) {
    const Ival d11 = y1 + f.alpha * x1;
    const Ival d12 = y2 + f.alpha * x2;
    const Ival d21 = y1 - f.beta * x1;
    const Ival d22 = y2 - f.beta * x2;
    const Ival r12 = sqrt(dot(x1, x2, x1, x2));
    const Ival r13 = sqrt(dot(d11, d12, d11, d12));
    const Ival r23 = sqrt(dot(d21, d22, d21, d22));
    out.potential = f.a * f.b / r12 + f.a / r13 + f.b / r23;
  }
  return out;
}

bool step_excludes_brake(const Scalars& sc) {
  if (!contains_zero(sc.i_dot)) return true;
  if (sc.kinetic.leftBound() > 0) return true;
  return !contains_zero(sc.b1) || !contains_zero(sc.b2) ||
         !contains_zero(sc.b3);
}

bool positions_exclude_brake(const Vector& s, const Family& f) {
  const Ival &x1 = s[0], &x2 = s[1], &y1 = s[2], &y2 = s[3];
  const Ival d11 = y1 + f.alpha * x1;
  const Ival d12 = y2 + f.alpha * x2;
  const Ival d21 = y1 - f.beta * x1;
  const Ival d22 = y2 - f.beta * x2;
  const Ival s12 = dot(x1, x2, x1, x2);
  const Ival s13 = dot(d11, d12, d11, d12);
  const Ival s23 = dot(d21, d22, d21, d22);
  if (!(s12.leftBound() > 0) || !(s13.leftBound() > 0) ||
      !(s23.leftBound() > 0)) {
    return false;
  }
  const Ival u_val =
      f.a * f.b / sqrt(s12) + f.a / sqrt(s13) + f.b / sqrt(s23);
  return u_val.leftBound() > f.u0.rightBound();
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

Ival pair_g_sq(const Vector& s, const Family& f) {
  const Ival g1 = s[2] + f.alpha * s[0];
  const Ival g2 = s[3] + f.alpha * s[1];
  return g1 * g1 + g2 * g2;
}

Ival damped_write_gap_allowance(const Ival& forcing, int damping_rate,
                                const Ival& duration_lower) {
  // For y' = c(T-y)+f with frozen T and duration tau,
  // y(tau)=T exactly when
  //   f = c exp(-c tau) (T-y(0))/(1-exp(-c tau)).
  // The right side decreases with tau.  Thus the interval forcing
  // contains the required state-dependent value whenever every target
  // gap is bounded by the quantity below at the rigorous lower duration.
  if (!(duration_lower.leftBound() > 0)) {
    throw std::runtime_error(
        "damped construction has no positive duration lower bound");
  }
  const Ival rate(damping_rate);
  const Ival decay = exp(-rate * duration_lower);
  const Ival forcing_magnitude(forcing.rightBound());
  return forcing_magnitude * (Ival(1) - decay) / (rate * decay);
}

void require_gap_inside_allowance(const Ival& gap,
                                  const Ival& allowance,
                                  const char* label) {
  const auto bound = allowance.leftBound();
  if (!(gap.leftBound() >= -bound && gap.rightBound() <= bound)) {
    std::cerr << "FAIL " << label << " gap=["
              << bound_double(gap.leftBound()) << ","
              << bound_double(gap.rightBound()) << "] allowance="
              << bound_double(bound) << "\n";
    throw std::runtime_error(
        "damped construction forcing does not cover exact overwrite");
  }
}

void audit_entry_damped_write(const Vector& s, bool form_a,
                              const Family& f,
                              int damping_rate,
                              const Ival& forcing,
                              const Ival& duration_lower) {
  const Ival gx = s[2] + f.alpha * s[0];
  const Ival gy = s[3] + f.alpha * s[1];
  const Ival gdx = s[6] + f.alpha * s[4];
  const Ival gdy = s[7] + f.alpha * s[5];
  const Ival abs_g = sqrt(gx * gx + gy * gy);
  Ival wr, wi;
  if (form_a) {
    wr = sqrt((abs_g + gx) / 2);
    wi = gy / (2 * wr);
  } else {
    wi = sqrt((abs_g - gx) / 2);
    wr = gy / (2 * wi);
  }
  Vector target(9);
  target[0] = wr;
  target[1] = wi;
  target[2] = (wr * gdx + wi * gdy) / 2;
  target[3] = (wr * gdy - wi * gdx) / 2;
  target[4] = (gdx * gdx + gdy * gdy) / 2 - f.m13 / abs_g;
  target[5] = f.ag * s[0] + f.bg * s[2];
  target[6] = f.ag * s[1] + f.bg * s[3];
  target[7] = f.ag * s[4] + f.bg * s[6];
  target[8] = f.ag * s[5] + f.bg * s[7];
  const Ival allowance =
      damped_write_gap_allowance(forcing, damping_rate, duration_lower);
  for (int i = 0; i < 9; ++i) {
    require_gap_inside_allowance(
        target[i] - s[8 + i], allowance, "entry construction");
  }
}

void audit_exit_damped_write(const Vector& s, const Family& f,
                             int damping_rate,
                             const Ival& forcing,
                             const Ival& duration_lower) {
  const Ival w2 = s[8] * s[8] + s[9] * s[9];
  const Ival gx = s[8] * s[8] - s[9] * s[9];
  const Ival gy = 2 * s[8] * s[9];
  const Ival gdx = 2 * (s[8] * s[10] - s[9] * s[11]) / w2;
  const Ival gdy = 2 * (s[8] * s[11] + s[9] * s[10]) / w2;
  Vector target(8);
  target[0] = s[13] + f.inv_m13 * gx;
  target[1] = s[14] + f.inv_m13 * gy;
  target[2] = f.ag * gx - f.alpha * s[13];
  target[3] = f.ag * gy - f.alpha * s[14];
  target[4] = s[15] + f.inv_m13 * gdx;
  target[5] = s[16] + f.inv_m13 * gdy;
  target[6] = f.ag * gdx - f.alpha * s[15];
  target[7] = f.ag * gdy - f.alpha * s[16];
  const Ival allowance =
      damped_write_gap_allowance(forcing, damping_rate, duration_lower);
  for (int i = 0; i < 8; ++i) {
    require_gap_inside_allowance(
        target[i] - s[i], allowance, "exit construction");
  }
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
  template <class SetT>
  void direct_move(SetT& set, double cap) {
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

struct DirectLcScalars {
  Ival selected_radius;
  Ival r12_squared;
  Ival r23_squared;
  Ival potential;
  Ival i_dot;
  Ival kinetic;
};

DirectLcScalars evaluate_direct_lc(const Vector& s, const Family& f) {
  DirectLcScalars out;
  const Ival &wr = s[0], &wi = s[1];
  const Ival gx = wr * wr - wi * wi;
  const Ival gy = 2 * wr * wi;
  out.selected_radius = wr * wr + wi * wi;
  const Ival gdx =
      2 * (wr * s[2] - wi * s[3]) / out.selected_radius;
  const Ival gdy =
      2 * (wr * s[3] + wi * s[2]) / out.selected_radius;
  const Ival d21x = s[5] + f.inv_m13 * gx;
  const Ival d21y = s[6] + f.inv_m13 * gy;
  const Ival d23x = s[5] + (f.inv_m13 - 1) * gx;
  const Ival d23y = s[6] + (f.inv_m13 - 1) * gy;
  out.r12_squared = d21x * d21x + d21y * d21y;
  out.r23_squared = d23x * d23x + d23y * d23y;
  const Ival yx = f.ag * gx - f.alpha * s[5];
  const Ival yy = f.ag * gy - f.alpha * s[6];
  const Ival xd_x = s[7] + f.inv_m13 * gdx;
  const Ival xd_y = s[8] + f.inv_m13 * gdy;
  const Ival yd_x = f.ag * gdx - f.alpha * s[7];
  const Ival yd_y = f.ag * gdy - f.alpha * s[8];
  out.i_dot = s.dimension() > 11
                  ? s[11]
                  : 2 * (f.mu1 * (d21x * xd_x + d21y * xd_y) +
                         f.mu2 * (yx * yd_x + yy * yd_y));
  out.kinetic =
      (f.mu1 * (xd_x * xd_x + xd_y * xd_y) +
       f.mu2 * (yd_x * yd_x + yd_y * yd_y)) /
      2;
  out.potential = Ival(0);
  if (out.selected_radius.leftBound() > 0 &&
      out.r12_squared.leftBound() > 0 &&
      out.r23_squared.leftBound() > 0) {
    out.potential =
        f.a * f.b / sqrt(out.r12_squared) +
        f.a / out.selected_radius + f.b / sqrt(out.r23_squared);
  }
  return out;
}

DirectLcScalars evaluate_pair23_lc(const Vector& s, const Family& f) {
  DirectLcScalars out;
  const Ival &wr = s[0], &wi = s[1];
  const Ival gx = wr * wr - wi * wi;
  const Ival gy = 2 * wr * wi;
  out.selected_radius = wr * wr + wi * wi;
  const Ival m23 = f.b + 1;
  const Ival inv_m23 = 1 / m23;
  const Ival gdx =
      2 * (wr * s[2] - wi * s[3]) / out.selected_radius;
  const Ival gdy =
      2 * (wr * s[3] + wi * s[2]) / out.selected_radius;
  const Ival d12x = s[5] + inv_m23 * gx;
  const Ival d12y = s[6] + inv_m23 * gy;
  const Ival d13x = s[5] + (inv_m23 - 1) * gx;
  const Ival d13y = s[6] + (inv_m23 - 1) * gy;
  out.r12_squared = d12x * d12x + d12y * d12y;
  out.r23_squared = d13x * d13x + d13y * d13y;
  const Ival pair_mu = f.b / m23;
  const Ival complement_mu = f.a * m23 / f.total;
  out.i_dot = s.dimension() > 11 ? s[11] : Ival(0);
  out.kinetic =
      (pair_mu * (gdx * gdx + gdy * gdy) +
       complement_mu * (s[7] * s[7] + s[8] * s[8])) /
      2;
  out.potential = Ival(0);
  if (out.selected_radius.leftBound() > 0 &&
      out.r12_squared.leftBound() > 0 &&
      out.r23_squared.leftBound() > 0) {
    out.potential =
        f.a * f.b / sqrt(out.r12_squared) +
        f.b / out.selected_radius + f.a / sqrt(out.r23_squared);
  }
  return out;
}

bool direct_lc_residual_excludes_brake(const Vector& enclosure) {
  // At a collision-free selected-pair state, physical pair velocity is
  // 2*w*z/|w|^2 and complementary velocity is P.  Hence a labelled brake
  // forces zr=zi=Px=Py=0.  Only this necessary direction is used.
  return !contains_zero(enclosure[2]) || !contains_zero(enclosure[3]) ||
         !contains_zero(enclosure[7]) || !contains_zero(enclosure[8]);
}

struct DirectCorrelatedGraph {
  Vector anchor;
  Vector tangent;
  Ival u_range;
  Ival u_center;

  Set c0_set() const {
    const int dimension = anchor.dimension();
    Vector x(dimension), r0(dimension), r(dimension);
    Matrix c(dimension, dimension), b(dimension, dimension);
    for (int row = 0; row < dimension; ++row) {
      const Ival center =
          (Ival(anchor[row].leftBound()) + Ival(anchor[row].rightBound())) /
          2;
      x[row] = center;
      r[row] = anchor[row] - center;
      r0[row] = Ival(0);
      for (int column = 0; column < dimension; ++column) {
        c[row][column] = Ival(row == column ? 1 : 0);
        b[row][column] = Ival(row == column ? 1 : 0);
      }
      c[row][0] = tangent[row];
    }
    r0[0] = u_range - u_center;
    return Set(x, c, r0, b, r, Ival(0));
  }

  C1Set c1_set() const {
    const int dimension = anchor.dimension();
    Vector x(dimension), r0(dimension), r(dimension);
    Matrix c(dimension, dimension), b(dimension, dimension);
    for (int row = 0; row < dimension; ++row) {
      const Ival center =
          (Ival(anchor[row].leftBound()) + Ival(anchor[row].rightBound())) /
          2;
      x[row] = center;
      r[row] = anchor[row] - center;
      r0[row] = Ival(0);
      for (int column = 0; column < dimension; ++column) {
        c[row][column] = Ival(row == column ? 1 : 0);
        b[row][column] = Ival(row == column ? 1 : 0);
      }
      c[row][0] = tangent[row];
    }
    r0[0] = u_range - u_center;
    return C1Set(x, c, r0, b, r, Ival(0));
  }
};

DirectCorrelatedGraph make_direct_launch_graph(const Ival& u_range) {
  const Ival u_center =
      (Ival(u_range.leftBound()) + Ival(u_range.rightBound())) / 2;
  Vector center_input(12), range_input(12);
  for (int i = 0; i < 12; ++i) {
    center_input[i] = Ival(0);
    range_input[i] = Ival(0);
  }
  center_input[10] = u_center;
  range_input[10] = u_range;
  Map launch_map = make_direct_lc_initial_graph_field();
  Vector anchor = launch_map(center_input);
  const Matrix launch_derivative = launch_map.derivative(range_input);
  Vector tangent(12);
  for (int row = 0; row < 12; ++row) {
    tangent[row] = launch_derivative[row][10];
  }
  // The construction field freezes ww; the actual launch graph retains it.
  anchor[10] = u_center;
  tangent[10] = Ival(1);
  return {anchor, tangent, u_range, u_center};
}

DirectCorrelatedGraph project_direct_graph(
    const DirectCorrelatedGraph& input, int section_coordinate,
    const Ival& section_value,
    capd::poincare::CrossingDirection direction, int order,
    double tolerance, bool pair23_chart = false,
    int expected_j_sign = 0, bool energy_leaf_h = false) {
  Map field = pair23_chart ? make_pair23_lc_field(energy_leaf_h)
                           : make_direct_lc_field(energy_leaf_h);
  CoordinateSection section(12, section_coordinate, section_value);
  Solver interval_solver(field, order);
  interval_solver.setAbsoluteTolerance(tolerance);
  interval_solver.setRelativeTolerance(tolerance);
  PoincareMap interval_map(interval_solver, section, direction);
  interval_map.setMaxReturnTime(50.0);
  C1Set interval_set = input.c1_set();
  Matrix flow_derivative(12, 12);
  Ival interval_return;
  const Vector interval_image =
      interval_map(interval_set, flow_derivative, interval_return);
  const Matrix section_derivative =
      interval_map.computeDP(
          interval_image, flow_derivative, interval_return);
  Vector output_tangent = section_derivative * input.tangent;

  // Poincare-map existence alone does not prove that the selected LC lift
  // stays away from w=0.  Replay the complete common-clock tube past the
  // latest return time and inspect every accepted-step enclosure.  On
  // physical-time checkpoint legs the same audit also proves the required
  // strict sign of J=dI/dt throughout the leg.
  {
    Set audit_set = input.c0_set();
    Map audit_field = pair23_chart ? make_pair23_lc_field(energy_leaf_h)
                                   : make_direct_lc_field(energy_leaf_h);
    PhaseRunner audit(audit_field, order, tolerance);
    const Family audit_family = make_family(input.u_range);
    bool launch_window = expected_j_sign == -2;
    bool positive_launch_window = expected_j_sign == 2;
    const Ival audit_target = Ival(interval_return.rightBound());
    for (int audit_steps = 0;; ++audit_steps) {
      if (audit_steps > 200000) {
        throw std::runtime_error(
            "direct correlated graph leg audit step limit");
      }
      const Vector before(audit_set);
      const double w_abs = std::sqrt(std::max(
          1e-12,
          bound_double((before[0] * before[0] + before[1] * before[1])
                           .leftBound())));
      const double cap =
          std::max(1.0 / 8000.0,
                   std::min(w_abs / 24.0, 1.0 / 100.0));
      audit.direct_move(audit_set, cap);
      const Vector enclosure = audit_set.getLastEnclosure();
      const DirectLcScalars sc =
          pair23_chart ? evaluate_pair23_lc(enclosure, audit_family)
                       : evaluate_direct_lc(enclosure, audit_family);
      if (!(sc.selected_radius.leftBound() > 0) ||
          !(sc.r12_squared.leftBound() > 0) ||
          !(sc.r23_squared.leftBound() > 0)) {
        throw std::runtime_error(
            "direct correlated graph leg lost collision separation");
      }
      if (launch_window) {
        if (!(sc.potential.rightBound() <
              (2 * audit_family.u0).leftBound())) {
          if (!(sc.i_dot.rightBound() < 0)) {
            throw std::runtime_error(
                "direct correlated launch leg lost initial concavity/J sign");
          }
          launch_window = false;
        }
      } else if (positive_launch_window) {
        if (!(sc.potential.leftBound() >
              (2 * audit_family.u0).rightBound())) {
          if (!(sc.i_dot.leftBound() > 0)) {
            throw std::runtime_error(
                "direct correlated minimum launch lost concavity/J sign");
          }
          positive_launch_window = false;
        }
      } else if (expected_j_sign == 3) {
        if (!(sc.potential.leftBound() >
              (2 * audit_family.u0).rightBound())) {
          throw std::runtime_error(
              "direct correlated graph leg left the convex-I corridor");
        }
      } else if (((expected_j_sign == -1 || expected_j_sign == -2) &&
                  !(sc.i_dot.rightBound() < 0)) ||
          (expected_j_sign > 0 && !(sc.i_dot.leftBound() > 0))) {
        throw std::runtime_error(
            "direct correlated graph leg lost its prescribed J sign");
      }
      if (audit_set.getCurrentTime().leftBound() >=
          audit_target.rightBound()) {
        break;
      }
    }
  }

  CoordinateSection anchor_section(12, section_coordinate, section_value);
  Solver anchor_solver(field, order);
  anchor_solver.setAbsoluteTolerance(tolerance);
  anchor_solver.setRelativeTolerance(tolerance);
  PoincareMap anchor_map(anchor_solver, anchor_section, direction);
  anchor_map.setMaxReturnTime(50.0);
  Set anchor_set(input.anchor);
  Ival anchor_return;
  Vector output_anchor = anchor_map(anchor_set, anchor_return);
  if (!interval_image[section_coordinate].contains(section_value) ||
      !output_anchor[section_coordinate].contains(section_value)) {
    throw std::runtime_error(
        "direct correlated graph missed its Poincare section");
  }
  output_anchor[section_coordinate] = section_value;
  output_tangent[section_coordinate] = Ival(0);

  return {output_anchor, output_tangent,
          input.u_range, input.u_center};
}

void apply_exact_direct_map(Set& set, Map& map) {
  capd::dynsys::DynSysMap<Map> discrete_map(map);
  set.move(discrete_map);
}

Vector propagate_persistent_direct_to_physical_lower(
    Set& set, const Ival& target_tp, int order, double tolerance,
    const Ival& u_range, bool pair23_chart,
    int expected_j_sign, bool energy_leaf_h) {
  Map field = pair23_chart ? make_pair23_lc_field(energy_leaf_h)
                           : make_direct_lc_field(energy_leaf_h);
  PhaseRunner flow(field, order, tolerance);
  const Family family = make_family(u_range);
  for (int steps = 0; steps < 200000; ++steps) {
    const Vector before(set);
    if (before[9].leftBound() >= target_tp.rightBound()) {
      return before;
    }
    const double w_abs = std::sqrt(std::max(
        1e-12,
        bound_double((before[0] * before[0] + before[1] * before[1])
                         .leftBound())));
    const double cap =
        std::max(1.0 / 8000.0,
                 std::min(w_abs / 32.0, 1.0 / 200.0));
    try {
      flow.direct_move(set, cap);
    } catch (const std::exception& error) {
      const Vector snapshot(set);
      std::cout << "DIRECT_LC_EVENT_PROBE kind=common_sigma_flow_failure"
                << " step=" << steps << " tp=["
                << bound_double(snapshot[9].leftBound()) << ","
                << bound_double(snapshot[9].rightBound()) << "] w2=["
                << bound_double((snapshot[0] * snapshot[0] +
                                 snapshot[1] * snapshot[1]).leftBound())
                << ","
                << bound_double((snapshot[0] * snapshot[0] +
                                 snapshot[1] * snapshot[1]).rightBound())
                << "] hull=" << hull_width(snapshot, 12)
                << " what=" << error.what() << "\n" << std::flush;
      throw;
    }
    const Vector enclosure = set.getLastEnclosure();
    const DirectLcScalars sc =
        pair23_chart ? evaluate_pair23_lc(enclosure, family)
                     : evaluate_direct_lc(enclosure, family);
    if (!(sc.selected_radius.leftBound() > 0) ||
        !(sc.r12_squared.leftBound() > 0) ||
        !(sc.r23_squared.leftBound() > 0)) {
      throw std::runtime_error(
          "persistent common-sigma leg lost collision separation");
    }
    const bool prescribed_j =
        (expected_j_sign < 0 && sc.i_dot.rightBound() < 0) ||
        (expected_j_sign > 0 && sc.i_dot.leftBound() > 0) ||
        expected_j_sign == 0;
    const bool potential_excludes_brake =
        sc.potential.leftBound() > family.u0.rightBound();
    if (!prescribed_j && !potential_excludes_brake &&
        !direct_lc_residual_excludes_brake(enclosure)) {
      const Vector snapshot(set);
      std::cout << "DIRECT_LC_EVENT_PROBE kind=common_sigma_guard_failure"
                << " tp=[" << bound_double(snapshot[9].leftBound()) << ","
                << bound_double(snapshot[9].rightBound()) << "] jd=["
                << bound_double(sc.i_dot.leftBound()) << ","
                << bound_double(sc.i_dot.rightBound()) << "] hull="
                << hull_width(snapshot, 12) << "\n" << std::flush;
      throw std::runtime_error(
          "persistent common-sigma leg lost every brake obstruction");
    }
  }
  throw std::runtime_error(
      "persistent common-sigma leg exceeded its step limit");
}

Vector project_persistent_direct_c0_set(
    Set& interval_set, int section_coordinate,
    const Ival& section_value,
    capd::poincare::CrossingDirection direction, int order,
    double tolerance, const Ival& u_range,
    bool pair23_chart = false, int expected_j_sign = 0,
    bool energy_leaf_h = false) {
  // PoincareMap advances interval_set to just after the section while the
  // C0 tripleton retains its correlation generators.  A separate copy
  // audits every accepted-step enclosure up to the latest return time.
  Set audit_set(interval_set);
  Map field = pair23_chart ? make_pair23_lc_field(energy_leaf_h)
                           : make_direct_lc_field(energy_leaf_h);
  CoordinateSection section(12, section_coordinate, section_value);
  Solver interval_solver(field, order);
  interval_solver.setAbsoluteTolerance(tolerance);
  interval_solver.setRelativeTolerance(tolerance);
  PoincareMap interval_map(interval_solver, section, direction);
  interval_map.setMaxReturnTime(50.0);
  Ival interval_return;
  const Vector interval_image = interval_map(interval_set, interval_return);
  if (!interval_image[section_coordinate].contains(section_value)) {
    throw std::runtime_error(
        "persistent direct C0 set missed its Poincare section");
  }

  Map audit_field = pair23_chart ? make_pair23_lc_field(energy_leaf_h)
                                 : make_direct_lc_field(energy_leaf_h);
  PhaseRunner audit(audit_field, order, tolerance);
  const Family audit_family = make_family(u_range);
  bool launch_window = expected_j_sign == -2;
  bool positive_launch_window = expected_j_sign == 2;
  const Ival audit_target = interval_set.getCurrentTime();
  for (int audit_steps = 0;; ++audit_steps) {
    if (audit_steps > 200000) {
      throw std::runtime_error(
          "persistent direct C0 set leg audit step limit");
    }
    const Vector before(audit_set);
    const double w_abs = std::sqrt(std::max(
        1e-12,
        bound_double((before[0] * before[0] + before[1] * before[1])
                         .leftBound())));
    const double cap =
        std::max(1.0 / 8000.0,
                 std::min(w_abs / 24.0, 1.0 / 100.0));
    audit.direct_move(audit_set, cap);
    const Vector enclosure = audit_set.getLastEnclosure();
    const DirectLcScalars sc =
        pair23_chart ? evaluate_pair23_lc(enclosure, audit_family)
                     : evaluate_direct_lc(enclosure, audit_family);
    if (!(sc.selected_radius.leftBound() > 0) ||
        !(sc.r12_squared.leftBound() > 0) ||
        !(sc.r23_squared.leftBound() > 0)) {
      throw std::runtime_error(
          "persistent direct C0 set leg lost collision separation");
    }
    if (launch_window) {
      if (!(sc.potential.rightBound() <
            (2 * audit_family.u0).leftBound())) {
        if (!(sc.i_dot.rightBound() < 0)) {
          throw std::runtime_error(
              "persistent C0 launch leg lost initial concavity/J sign");
        }
        launch_window = false;
      }
    } else if (positive_launch_window) {
      if (!(sc.potential.leftBound() >
            (2 * audit_family.u0).rightBound())) {
        if (!(sc.i_dot.leftBound() > 0)) {
          throw std::runtime_error(
              "persistent C0 minimum launch lost concavity/J sign");
        }
        positive_launch_window = false;
      }
    } else if (expected_j_sign == 3) {
      if (!(sc.potential.leftBound() >
            (2 * audit_family.u0).rightBound())) {
        throw std::runtime_error(
            "persistent direct C0 set left the convex-I corridor");
      }
    } else if (((expected_j_sign == -1 || expected_j_sign == -2) &&
                !(sc.i_dot.rightBound() < 0)) ||
               (expected_j_sign > 0 && !(sc.i_dot.leftBound() > 0))) {
      throw std::runtime_error(
          "persistent direct C0 set leg lost its prescribed J sign");
    }
    if (audit_set.getCurrentTime().leftBound() >=
        audit_target.rightBound()) {
      break;
    }
  }
  return interval_image;
}

Vector project_persistent_direct_set(
    C1Set& interval_set, int section_coordinate,
    const Ival& section_value,
    capd::poincare::CrossingDirection direction, int order,
    double tolerance, const Ival& u_range,
    bool pair23_chart = false, int expected_j_sign = 0,
    bool energy_leaf_h = false, bool restart_from_section = false) {
  // Preserve a copy for a stepwise tube audit.  PoincareMap intentionally
  // advances interval_set to just after the section, retaining its full
  // C1 doubleton correlations for the next leg.
  C1Set audit_set(interval_set);
  Map field = pair23_chart ? make_pair23_lc_field(energy_leaf_h)
                           : make_direct_lc_field(energy_leaf_h);
  CoordinateSection section(12, section_coordinate, section_value);
  Solver interval_solver(field, order);
  interval_solver.setAbsoluteTolerance(tolerance);
  interval_solver.setRelativeTolerance(tolerance);
  PoincareMap interval_map(interval_solver, section, direction);
  interval_map.setMaxReturnTime(50.0);
  Matrix flow_derivative(12, 12);
  Ival interval_return;
  const Vector interval_image =
      interval_map(interval_set, flow_derivative, interval_return);
  if (!interval_image[section_coordinate].contains(section_value)) {
    throw std::runtime_error(
        "persistent direct set missed its Poincare section");
  }

  Map audit_field = pair23_chart ? make_pair23_lc_field(energy_leaf_h)
                                 : make_direct_lc_field(energy_leaf_h);
  PhaseRunner audit(audit_field, order, tolerance);
  const Family audit_family = make_family(u_range);
  bool launch_window = expected_j_sign == -2;
  bool positive_launch_window = expected_j_sign == 2;
  const Ival audit_target = interval_set.getCurrentTime();
  for (int audit_steps = 0;; ++audit_steps) {
    if (audit_steps > 200000) {
      throw std::runtime_error(
          "persistent direct set leg audit step limit");
    }
    const Vector before(audit_set);
    const double w_abs = std::sqrt(std::max(
        1e-12,
        bound_double((before[0] * before[0] + before[1] * before[1])
                         .leftBound())));
    const double cap =
        std::max(1.0 / 8000.0,
                 std::min(w_abs / 24.0, 1.0 / 100.0));
    audit.direct_move(audit_set, cap);
    const Vector enclosure = audit_set.getLastEnclosure();
    const DirectLcScalars sc =
        pair23_chart ? evaluate_pair23_lc(enclosure, audit_family)
                     : evaluate_direct_lc(enclosure, audit_family);
    if (!(sc.selected_radius.leftBound() > 0) ||
        !(sc.r12_squared.leftBound() > 0) ||
        !(sc.r23_squared.leftBound() > 0)) {
      throw std::runtime_error(
          "persistent direct set leg lost collision separation");
    }
    if (launch_window) {
      if (!(sc.potential.rightBound() <
            (2 * audit_family.u0).leftBound())) {
        if (!(sc.i_dot.rightBound() < 0)) {
          throw std::runtime_error(
              "persistent launch leg lost initial concavity/J sign");
        }
        launch_window = false;
      }
    } else if (positive_launch_window) {
      if (!(sc.potential.leftBound() >
            (2 * audit_family.u0).rightBound())) {
        if (!(sc.i_dot.leftBound() > 0)) {
          throw std::runtime_error(
              "persistent minimum launch lost concavity/J sign");
        }
        positive_launch_window = false;
      }
    } else if (expected_j_sign == 3) {
      if (!(sc.potential.leftBound() >
            (2 * audit_family.u0).rightBound())) {
        throw std::runtime_error(
            "persistent direct set left the convex-I corridor");
      }
    } else if (((expected_j_sign == -1 || expected_j_sign == -2) &&
                !(sc.i_dot.rightBound() < 0)) ||
               (expected_j_sign > 0 && !(sc.i_dot.leftBound() > 0))) {
      throw std::runtime_error(
          "persistent direct set leg lost its prescribed J sign");
    }
    if (audit_set.getCurrentTime().leftBound() >=
        audit_target.rightBound()) {
      break;
    }
  }
  if (restart_from_section) {
    // Optional fail-safe reboxing.  PoincareMap leaves its working set just
    // after the crossing; its returned section image is often much tighter.
    Vector restart_image(interval_image);
    restart_image[section_coordinate] = section_value;
    if (energy_leaf_h) {
      restart_image[4] = Ival(0);
    }
    interval_set = C1Set(restart_image);
  }
  return interval_image;
}

DirectCorrelatedGraph transform_pair13_to_pair23(
    const DirectCorrelatedGraph& input) {
  Map transformation = make_pair13_to_pair23_map();
  const Vector domain(input.c0_set());
  Vector output_anchor = transformation(input.anchor);
  const Matrix derivative = transformation.derivative(domain);
  Vector output_tangent = derivative * input.tangent;
  return {output_anchor, output_tangent, input.u_range, input.u_center};
}

DirectCorrelatedGraph transform_pair23_to_pair13(
    const DirectCorrelatedGraph& input) {
  Map transformation = make_pair23_to_pair13_map();
  const Vector domain(input.c0_set());
  Vector output_anchor = transformation(input.anchor);
  const Matrix derivative = transformation.derivative(domain);
  Vector output_tangent = derivative * input.tangent;
  return {output_anchor, output_tangent, input.u_range, input.u_center};
}

int run_direct_lc_prefix(const Ival& u_param, long p, long q,
                         long p2, long q2, double prefix_end,
                         int order, double tolerance,
                         bool certify_first_maximum = false,
                         bool certify_second_maximum = false) {
  const Family family = make_family(u_param);
  Map graph_field = make_direct_lc_initial_graph_field();
  Vector initial(12);
  for (int i = 0; i < 12; ++i) initial[i] = Ival(0);
  initial[10] = u_param;
  Set set(initial);
  {
    PhaseRunner graph(graph_field, std::max(order, 30), tolerance);
    const Ival start = set.getCurrentTime();
    const Ival target = start + Ival(1);
    while (graph.step(target, set)) {
    }
    const Ival duration = set.getCurrentTime() - start;
    if (!(duration.leftBound() <= 1 && duration.rightBound() >= 1)) {
      std::cerr << "FAIL direct-LC initial graph duration\n";
      return 1;
    }
  }


  if (certify_first_maximum || certify_second_maximum ||
      std::getenv("FABLE_PROBE_DIRECT_EVENTS") != nullptr) {
    DirectCorrelatedGraph event_graph = make_direct_launch_graph(u_param);
    const Ival checkpoint_times[8] = {
        Ival(2) / Ival(5), Ival(11) / Ival(20), Ival(3) / Ival(5),
        Ival(31) / Ival(50), Ival(16) / Ival(25), Ival(33) / Ival(50),
        Ival(17) / Ival(25), Ival(7) / Ival(10)};
    bool first_incoming_checkpoint = true;
    for (const Ival& checkpoint_time : checkpoint_times) {
      event_graph = project_direct_graph(
          event_graph, 9, checkpoint_time,
          capd::poincare::MinusPlus, order, tolerance, false,
          first_incoming_checkpoint ? -2 : -1);
      first_incoming_checkpoint = false;
      const Vector time_image(event_graph.c0_set());
      const DirectLcScalars checkpoint_sc =
          evaluate_direct_lc(time_image, family);
      if (!(checkpoint_sc.selected_radius.leftBound() > 0) ||
          !(checkpoint_sc.r12_squared.leftBound() > 0) ||
          !(checkpoint_sc.r23_squared.leftBound() > 0)) {
        throw std::runtime_error(
            "direct-LC physical-time checkpoint lost separation");
      }
      std::cout << "DIRECT_LC_EVENT_PROBE kind=checkpoint tp=["
                << bound_double(time_image[9].leftBound()) << ","
                << bound_double(time_image[9].rightBound()) << "]"
                << " jd=[" << bound_double(time_image[11].leftBound())
                << "," << bound_double(time_image[11].rightBound())
                << "] hull=" << hull_width(time_image, 12) << "\n"
                << std::flush;
    }
    const Vector time_image(event_graph.c0_set());
    const DirectLcScalars approach_sc =
        evaluate_direct_lc(time_image, family);
    if (!(approach_sc.i_dot.rightBound() < 0) ||
        !(approach_sc.selected_radius.leftBound() > 0) ||
        !(approach_sc.r12_squared.leftBound() > 0) ||
        !(approach_sc.r23_squared.leftBound() > 0)) {
      throw std::runtime_error(
          "direct-LC physical-time approach did not reach the pre-minimum tube");
    }
    event_graph = project_direct_graph(
        event_graph, 11, Ival(0), capd::poincare::MinusPlus,
        order, tolerance);
    const Vector minimum_image(event_graph.c0_set());
    const DirectLcScalars minimum_sc =
        evaluate_direct_lc(minimum_image, family);
    if (!(minimum_sc.potential.leftBound() >
          (2 * family.u0).rightBound())) {
      throw std::runtime_error(
          "direct-LC first minimum is not uniformly strict");
    }
    std::cout << "DIRECT_LC_EVENT_PROBE kind=minimum tp=["
              << bound_double(minimum_image[9].leftBound()) << ","
              << bound_double(minimum_image[9].rightBound()) << "]"
              << " UoverU0=["
              << bound_double((minimum_sc.potential / family.u0).leftBound())
              << ","
              << bound_double((minimum_sc.potential / family.u0).rightBound())
              << "] hull=" << hull_width(minimum_image, 12) << "\n"
              << std::flush;

    const Ival pair13_outgoing_times[4] = {
        Ival(17) / Ival(20), Ival(9) / Ival(10),
        Ival(19) / Ival(20), Ival(1)};
    bool first_outgoing_checkpoint = true;
    for (const Ival& checkpoint_time : pair13_outgoing_times) {
      event_graph = project_direct_graph(
          event_graph, 9, checkpoint_time,
          capd::poincare::MinusPlus, order, tolerance, false,
          first_outgoing_checkpoint ? 2 : 1);
      first_outgoing_checkpoint = false;
      const Vector checkpoint_image(event_graph.c0_set());
      const DirectLcScalars checkpoint_sc =
          evaluate_direct_lc(checkpoint_image, family);
      if (!(checkpoint_sc.i_dot.leftBound() > 0) ||
          !(checkpoint_sc.selected_radius.leftBound() > 0) ||
          !(checkpoint_sc.r12_squared.leftBound() > 0) ||
          !(checkpoint_sc.r23_squared.leftBound() > 0)) {
        throw std::runtime_error(
            "direct-LC outgoing checkpoint lost its positive-J tube");
      }
      std::cout << "DIRECT_LC_EVENT_PROBE kind=outgoing_checkpoint tp=["
                << bound_double(checkpoint_image[9].leftBound()) << ","
                << bound_double(checkpoint_image[9].rightBound()) << "]"
                << " jd=[" << bound_double(checkpoint_image[11].leftBound())
                << "," << bound_double(checkpoint_image[11].rightBound())
                << "] hull=" << hull_width(checkpoint_image, 12) << "\n"
                << std::flush;
    }

    event_graph = transform_pair13_to_pair23(event_graph);
    {
      const Vector switched(event_graph.c0_set());
      const DirectLcScalars switch_sc = evaluate_pair23_lc(switched, family);
      if (!(switch_sc.selected_radius.leftBound() > 0) ||
          !(switch_sc.r12_squared.leftBound() > 0) ||
          !(switch_sc.r23_squared.leftBound() > 0) ||
          !(switch_sc.i_dot.leftBound() > 0)) {
        throw std::runtime_error(
            "direct-LC pair-23 switch lost its collision-free positive-J tube");
      }
      std::cout << "DIRECT_LC_EVENT_PROBE kind=pair23_switch tp=["
                << bound_double(switched[9].leftBound()) << ","
                << bound_double(switched[9].rightBound()) << "]"
                << " jd=[" << bound_double(switched[11].leftBound())
                << "," << bound_double(switched[11].rightBound())
                << "] hull=" << hull_width(switched, 12) << "\n"
                << std::flush;
    }
    const Ival pair23_outgoing_times[6] = {
        Ival(21) / Ival(20), Ival(11) / Ival(10),
        Ival(23) / Ival(20), Ival(6) / Ival(5),
        Ival(5) / Ival(4), Ival(13) / Ival(10)};
    for (const Ival& checkpoint_time : pair23_outgoing_times) {
      event_graph = project_direct_graph(
          event_graph, 9, checkpoint_time,
          capd::poincare::MinusPlus, order, tolerance, true, 1);
      const Vector checkpoint_image(event_graph.c0_set());
      const DirectLcScalars checkpoint_sc =
          evaluate_pair23_lc(checkpoint_image, family);
      if (!(checkpoint_sc.i_dot.leftBound() > 0) ||
          !(checkpoint_sc.selected_radius.leftBound() > 0) ||
          !(checkpoint_sc.r12_squared.leftBound() > 0) ||
          !(checkpoint_sc.r23_squared.leftBound() > 0)) {
        throw std::runtime_error(
            "pair-23 outgoing checkpoint lost its positive-J tube");
      }
      std::cout << "DIRECT_LC_EVENT_PROBE kind=pair23_checkpoint tp=["
                << bound_double(checkpoint_image[9].leftBound()) << ","
                << bound_double(checkpoint_image[9].rightBound()) << "]"
                << " jd=[" << bound_double(checkpoint_image[11].leftBound())
                << "," << bound_double(checkpoint_image[11].rightBound())
                << "] hull=" << hull_width(checkpoint_image, 12) << "\n"
                << std::flush;
    }

    event_graph = project_direct_graph(
        event_graph, 11, Ival(0), capd::poincare::PlusMinus,
        order, tolerance, true);
    const Vector maximum_image(event_graph.c0_set());
    const DirectLcScalars maximum_sc =
        evaluate_pair23_lc(maximum_image, family);
    if (!(maximum_sc.potential.rightBound() <
          (2 * family.u0).leftBound()) ||
        !direct_lc_residual_excludes_brake(maximum_image)) {
      throw std::runtime_error(
          "direct-LC first maximum lacks strictness or brake separation");
    }
    std::cout << "DIRECT_LC_EVENT_PROBE kind=maximum tp=["
              << bound_double(maximum_image[9].leftBound()) << ","
              << bound_double(maximum_image[9].rightBound()) << "]"
              << " UoverU0=["
              << bound_double((maximum_sc.potential / family.u0).leftBound())
              << ","
              << bound_double((maximum_sc.potential / family.u0).rightBound())
              << "] z=[" << bound_double(maximum_image[2].leftBound())
              << "," << bound_double(maximum_image[2].rightBound())
              << "]+[" << bound_double(maximum_image[3].leftBound())
              << "," << bound_double(maximum_image[3].rightBound())
              << "]i P=[" << bound_double(maximum_image[7].leftBound())
              << "," << bound_double(maximum_image[7].rightBound())
              << "]x[" << bound_double(maximum_image[8].leftBound())
              << "," << bound_double(maximum_image[8].rightBound())
              << "] hull=" << hull_width(maximum_image, 12) << "\n"
              << std::flush;
    if (certify_first_maximum && !certify_second_maximum) {
      std::cout << "PASS_TIED_FIRST_MAXIMUM_INTERVAL u=["
                << p << "/" << q << "," << p2 << "/" << q2 << "]"
                << " method=CAPD-6.1.0-MPFR"
                << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
                << "\n";
      return 0;
    }
    if (certify_second_maximum) {
      const Ival pair23_second_incoming_times[5] = {
          Ival(7) / Ival(5), Ival(3) / Ival(2), Ival(8) / Ival(5),
          Ival(17) / Ival(10), Ival(7) / Ival(4)};
      bool first_second_incoming_checkpoint = true;
      for (const Ival& checkpoint_time : pair23_second_incoming_times) {
        event_graph = project_direct_graph(
            event_graph, 9, checkpoint_time,
            capd::poincare::MinusPlus, order, tolerance, true,
            first_second_incoming_checkpoint ? -2 : -1);
        first_second_incoming_checkpoint = false;
        const Vector checkpoint_image(event_graph.c0_set());
        const DirectLcScalars checkpoint_sc =
            evaluate_pair23_lc(checkpoint_image, family);
        if (!(checkpoint_sc.i_dot.rightBound() < 0) ||
            !(checkpoint_sc.selected_radius.leftBound() > 0) ||
            !(checkpoint_sc.r12_squared.leftBound() > 0) ||
            !(checkpoint_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-23 second-incoming checkpoint lost its negative-J tube");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=second_incoming_pair23"
                  << " tp=["
                  << bound_double(checkpoint_image[9].leftBound()) << ","
                  << bound_double(checkpoint_image[9].rightBound()) << "]"
                  << " jd=["
                  << bound_double(checkpoint_image[11].leftBound()) << ","
                  << bound_double(checkpoint_image[11].rightBound()) << "]"
                  << " hull=" << hull_width(checkpoint_image, 12) << "\n"
                  << std::flush;
      }

      event_graph = transform_pair23_to_pair13(event_graph);
      {
        const Vector switched(event_graph.c0_set());
        const DirectLcScalars switch_sc =
            evaluate_direct_lc(switched, family);
        if (!(switch_sc.selected_radius.leftBound() > 0) ||
            !(switch_sc.r12_squared.leftBound() > 0) ||
            !(switch_sc.r23_squared.leftBound() > 0) ||
            !(switch_sc.i_dot.rightBound() < 0)) {
          throw std::runtime_error(
              "direct-LC pair-13 return switch lost its collision-free negative-J tube");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair13_return_switch tp=["
                  << bound_double(switched[9].leftBound()) << ","
                  << bound_double(switched[9].rightBound()) << "]"
                  << " jd=[" << bound_double(switched[11].leftBound())
                  << "," << bound_double(switched[11].rightBound()) << "]"
                  << " hull=" << hull_width(switched, 12) << "\n"
                  << std::flush;
      }

      // The pair-13 vector field below reconstructs the selected-pair
      // Kepler energy h exactly from the fixed total-energy leaf.  Its
      // stored h coordinate is therefore a dummy.  Zeroing that row avoids
      // injecting an unused, strongly wrapping chart coordinate into the
      // pair-13 mean-value graph.
      event_graph.anchor[4] = Ival(0);
      event_graph.tangent[4] = Ival(0);
      Set middle_set(event_graph.c0_set());
      auto project_middle_c0 =
          [&](int section_coordinate, const Ival& section_value,
              capd::poincare::CrossingDirection direction,
              bool pair23_chart, int expected_j_sign) {
            return project_persistent_direct_c0_set(
                middle_set, section_coordinate, section_value, direction,
                order, tolerance, u_param, pair23_chart,
                expected_j_sign, true);
          };
      auto project_middle_mean_value =
          [&](DirectCorrelatedGraph& graph, int section_coordinate,
              const Ival& section_value,
              capd::poincare::CrossingDirection direction,
              bool pair23_chart, int expected_j_sign) {
            graph = project_direct_graph(
                graph, section_coordinate, section_value, direction,
                order, tolerance, pair23_chart, expected_j_sign, true);
            return Vector(graph.c0_set());
          };

      // Diagnostic physical-time checkpoints are useful for scouting but
      // ill-conditioned Poincare sections near the encounter because
      // tp_sigma=|w|^2.  The monotone wr chain below replaces them.
#if 0
      const Ival pair13_second_incoming_times[3] = {
          Ival(9) / Ival(5), Ival(37) / Ival(20), Ival(19) / Ival(10)};
      for (const Ival& checkpoint_time : pair13_second_incoming_times) {
        const Vector checkpoint_image = project_middle_mean_value(
            event_graph, 9, checkpoint_time,
            capd::poincare::MinusPlus, false, -1);
        const DirectLcScalars checkpoint_sc =
            evaluate_direct_lc(checkpoint_image, family);
        if (!(checkpoint_sc.i_dot.rightBound() < 0) ||
            !(checkpoint_sc.selected_radius.leftBound() > 0) ||
            !(checkpoint_sc.r12_squared.leftBound() > 0) ||
            !(checkpoint_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 second-incoming checkpoint lost its negative-J tube");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=second_incoming_pair13"
                  << " tp=["
                  << bound_double(checkpoint_image[9].leftBound()) << ","
                  << bound_double(checkpoint_image[9].rightBound()) << "]"
                  << " jd=["
                  << bound_double(checkpoint_image[11].leftBound()) << ","
                  << bound_double(checkpoint_image[11].rightBound()) << "]"
                  << " hull=" << hull_width(checkpoint_image, 12) << "\n"
                  << std::flush;
      }
#endif

      // Approach the square-root branch seam through short wr sections.
      // Every normal speed is wr_sigma=zr<0, whereas a physical-time
      // section loses transversality as tp_sigma=|w|^2 becomes small.
      const Ival pair13_incoming_wr_sections[8] = {
          Ival(7) / Ival(10), Ival(3) / Ival(5),
          Ival(1) / Ival(2), Ival(2) / Ival(5),
          Ival(3) / Ival(10), Ival(1) / Ival(5),
          Ival(1) / Ival(10), Ival(0)};
      int incoming_section_index = 0;
      for (const Ival& wr_section : pair13_incoming_wr_sections) {
        const Vector seam_image = project_middle_c0(
            0, wr_section, capd::poincare::PlusMinus, false, -1);
        const DirectLcScalars seam_sc =
            evaluate_direct_lc(seam_image, family);
        if (!(seam_sc.i_dot.rightBound() < 0) ||
            !(seam_sc.selected_radius.leftBound() > 0) ||
            !(seam_sc.r12_squared.leftBound() > 0) ||
            !(seam_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 seam section lost its collision-free negative-J tube");
        }
        ++incoming_section_index;
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair13_incoming_section"
                  << " ordinal=" << incoming_section_index << " tp=["
                  << bound_double(seam_image[9].leftBound()) << ","
                  << bound_double(seam_image[9].rightBound()) << "]"
                  << " wi=[" << bound_double(seam_image[1].leftBound())
                  << "," << bound_double(seam_image[1].rightBound()) << "]"
                  << " zr=[" << bound_double(seam_image[2].leftBound())
                  << "," << bound_double(seam_image[2].rightBound()) << "]"
                  << " jd=[" << bound_double(seam_image[11].leftBound())
                  << "," << bound_double(seam_image[11].rightBound()) << "]"
                  << " hull=" << hull_width(seam_image, 12) << "\n"
                  << std::flush;
      }

      // Go directly to the next J=0 section.  A fixed physical-time
      // checkpoint between the seam and the minimum is counterproductive:
      // it divides by tp_sigma=|w|^2 immediately after the close passage.
      // The J section itself is transverse because ddot(I)>0 there.
      Set second_minimum_set(middle_set);
      const Vector second_minimum_image =
          project_persistent_direct_c0_set(
              second_minimum_set, 11, Ival(0),
              capd::poincare::MinusPlus, order, tolerance, u_param,
              false, 0, true);
      const DirectLcScalars second_minimum_sc =
          evaluate_direct_lc(second_minimum_image, family);
      if (!(second_minimum_sc.potential.leftBound() >
            (2 * family.u0).rightBound())) {
        throw std::runtime_error(
            "direct-LC second minimum is not uniformly strict");
      }
      std::cout << "DIRECT_LC_EVENT_PROBE kind=second_minimum tp=["
                << bound_double(second_minimum_image[9].leftBound()) << ","
                << bound_double(second_minimum_image[9].rightBound()) << "]"
                << " UoverU0=["
                << bound_double(
                       (second_minimum_sc.potential / family.u0).leftBound())
                << ","
                << bound_double(
                       (second_minimum_sc.potential / family.u0).rightBound())
                << "] hull=" << hull_width(second_minimum_image, 12) << "\n"
                << std::flush;

      // Leave the close pair through short, fast LC-coordinate sections.
      // Their normal speed wr_sigma=zr stays order one.  Retaining four
      // correlated section graphs avoids both the 1/|w|^2 physical-clock
      // divisor and the wrapping produced by one long seam-to-exit map.
      const Ival pair13_outgoing_wr_sections[4] = {
          Ival(-1) / Ival(10), Ival(-1) / Ival(5),
          Ival(-3) / Ival(10), Ival(-2) / Ival(5)};
      int outgoing_section_index = 0;
      for (const Ival& wr_section : pair13_outgoing_wr_sections) {
        const Vector section_image = project_middle_c0(
            0, wr_section, capd::poincare::PlusMinus, false, 3);
        const DirectLcScalars section_sc =
            evaluate_direct_lc(section_image, family);
        if (!(section_image[2].rightBound() < 0) ||
            !(section_sc.selected_radius.leftBound() > 0) ||
            !(section_sc.r12_squared.leftBound() > 0) ||
            !(section_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 outgoing LC section lost its collision-free convex-I tube");
        }
        ++outgoing_section_index;
        if (outgoing_section_index == 4 &&
            !(section_sc.i_dot.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 final outgoing LC section lost positive J");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair13_outgoing_section"
                  << " ordinal=" << outgoing_section_index
                  << " tp=[" << bound_double(section_image[9].leftBound())
                  << "," << bound_double(section_image[9].rightBound())
                  << "] zr=[" << bound_double(section_image[2].leftBound())
                  << "," << bound_double(section_image[2].rightBound())
                  << "] jd=[" << bound_double(section_image[11].leftBound())
                  << "," << bound_double(section_image[11].rightBound())
                  << "] hull=" << hull_width(section_image, 12) << "\n"
                  << std::flush;
      }

      // Superseded by the pair-23 switch immediately after wr=-2/5.
#if 0
      const Ival pair13_far_outgoing_wr_sections[1] = {
          Ival(-9) / Ival(20)};
      for (const Ival& wr_section : pair13_far_outgoing_wr_sections) {
        const Vector section_image = project_middle_c0(
            0, wr_section, capd::poincare::PlusMinus, false, 1);
        const DirectLcScalars section_sc =
            evaluate_direct_lc(section_image, family);
        if (!(section_sc.i_dot.leftBound() > 0) ||
            !(section_image[2].rightBound() < 0) ||
            !(section_sc.selected_radius.leftBound() > 0) ||
            !(section_sc.r12_squared.leftBound() > 0) ||
            !(section_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 far-outgoing LC section lost its positive-J tube");
        }
        ++outgoing_section_index;
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair13_outgoing_section"
                  << " ordinal=" << outgoing_section_index
                  << " tp=[" << bound_double(section_image[9].leftBound())
                  << "," << bound_double(section_image[9].rightBound())
                  << "] zr=[" << bound_double(section_image[2].leftBound())
                  << "," << bound_double(section_image[2].rightBound())
                  << "] jd=[" << bound_double(section_image[11].leftBound())
                  << "," << bound_double(section_image[11].rightBound())
                  << "] hull=" << hull_width(section_image, 12) << "\n"
                  << std::flush;
      }
#endif

      // The next close passage belongs to pair {2,3}, not the currently
      // selected pair {1,3}.  Switch Jacobi trees while both pairs are well
      // separated, eliminate the new h from the same total-energy leaf,
      // and cross the encounter on monotone wi sections (wi_sigma=zi>0).
      Map pair13_to_pair23_energy_map = make_pair13_to_pair23_map(true);
      apply_exact_direct_map(middle_set, pair13_to_pair23_energy_map);
      {
        const Vector switched(middle_set);
        const DirectLcScalars switch_sc =
            evaluate_pair23_lc(switched, family);
        if (!(switched[0].leftBound() > 0) ||
            !(switch_sc.i_dot.leftBound() > 0) ||
            !(switch_sc.selected_radius.leftBound() > 0) ||
            !(switch_sc.r12_squared.leftBound() > 0) ||
            !(switch_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-23 middle switch lost its positive-J collision-free tube");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair23_middle_switch tp=["
                  << bound_double(switched[9].leftBound()) << ","
                  << bound_double(switched[9].rightBound()) << "] wi=["
                  << bound_double(switched[1].leftBound()) << ","
                  << bound_double(switched[1].rightBound()) << "] hull="
                  << hull_width(switched, 12) << "\n" << std::flush;
      }

      // Repeated set-valued wi Poincare returns were rigorously correct but
      // destroyed the tripleton representation.  The common-sigma leg below
      // supersedes this diagnostic chain.
#if 0
      const Ival pair23_middle_wi_sections[21] = {
          Ival(-7) / Ival(20), Ival(-13) / Ival(40),
          Ival(-3) / Ival(10),
          Ival(-1) / Ival(4), Ival(-1) / Ival(5),
          Ival(-3) / Ival(20), Ival(-1) / Ival(10),
          Ival(-1) / Ival(20), Ival(0), Ival(1) / Ival(20),
          Ival(1) / Ival(10), Ival(3) / Ival(20),
          Ival(1) / Ival(5), Ival(1) / Ival(4),
          Ival(3) / Ival(10), Ival(7) / Ival(20),
          Ival(2) / Ival(5), Ival(9) / Ival(20),
          Ival(1) / Ival(2), Ival(11) / Ival(20),
          Ival(3) / Ival(5)};
      int pair23_middle_index = 0;
      for (const Ival& wi_section : pair23_middle_wi_sections) {
        const Vector section_image = project_middle_c0(
            1, wi_section, capd::poincare::MinusPlus, true, 1);
        const DirectLcScalars section_sc =
            evaluate_pair23_lc(section_image, family);
        if (!(section_image[3].leftBound() > 0) ||
            !(section_sc.i_dot.leftBound() > 0) ||
            !(section_sc.selected_radius.leftBound() > 0) ||
            !(section_sc.r12_squared.leftBound() > 0) ||
            !(section_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-23 middle LC section lost its positive-J tube");
        }
        ++pair23_middle_index;
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair23_middle_section"
                  << " ordinal=" << pair23_middle_index << " tp=["
                  << bound_double(section_image[9].leftBound()) << ","
                  << bound_double(section_image[9].rightBound())
                  << "] wr=[" << bound_double(section_image[0].leftBound())
                  << "," << bound_double(section_image[0].rightBound())
                  << "] zi=[" << bound_double(section_image[3].leftBound())
                  << "," << bound_double(section_image[3].rightBound())
                  << "] hull=" << hull_width(section_image, 12) << "\n"
                  << std::flush;
      }
#endif
      const Vector pair23_middle_exit =
          propagate_persistent_direct_to_physical_lower(
              middle_set, Ival(43) / Ival(20), order, tolerance,
              u_param, true, 1, true);
      {
        const DirectLcScalars exit_sc =
            evaluate_pair23_lc(pair23_middle_exit, family);
        if (!(pair23_middle_exit[9].leftBound() >=
              (Ival(43) / Ival(20)).rightBound()) ||
            (!(exit_sc.i_dot.leftBound() > 0) &&
             !(exit_sc.potential.leftBound() > family.u0.rightBound()) &&
             !direct_lc_residual_excludes_brake(pair23_middle_exit)) ||
            !(exit_sc.selected_radius.leftBound() > 0) ||
            !(exit_sc.r12_squared.leftBound() > 0) ||
            !(exit_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-23 common-sigma middle exit lost its certified guards");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair23_middle_sigma_exit"
                  << " tp=[" << bound_double(pair23_middle_exit[9].leftBound())
                  << "," << bound_double(pair23_middle_exit[9].rightBound())
                  << "] wi=[" << bound_double(pair23_middle_exit[1].leftBound())
                  << "," << bound_double(pair23_middle_exit[1].rightBound())
                  << "] hull=" << hull_width(pair23_middle_exit, 12) << "\n"
                  << std::flush;
      }

      // Pair {1,3} is again the next close binary.  At the certified
      // t>43/20 common-sigma exit its relative vector lies on the
      // well-conditioned Form-A square-root sheet, so the exact inverse
      // tree map has wr13>0 uniformly.
      Map pair23_to_pair13_energy_map = make_pair23_to_pair13_map(true);
      apply_exact_direct_map(middle_set, pair23_to_pair13_energy_map);
      {
        const Vector switched(middle_set);
        const DirectLcScalars switch_sc = evaluate_direct_lc(switched, family);
        if (!(switched[0].leftBound() > 0) ||
            (!(switch_sc.i_dot.leftBound() > 0) &&
             !(switch_sc.potential.leftBound() > family.u0.rightBound()) &&
             !direct_lc_residual_excludes_brake(switched)) ||
            !(switch_sc.selected_radius.leftBound() > 0) ||
            !(switch_sc.r12_squared.leftBound() > 0) ||
            !(switch_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 second-passage switch lost its positive-J tube");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair13_second_passage_switch tp=["
                  << bound_double(switched[9].leftBound()) << ","
                  << bound_double(switched[9].rightBound()) << "] wr=["
                  << bound_double(switched[0].leftBound()) << ","
                  << bound_double(switched[0].rightBound()) << "] hull="
                  << hull_width(switched, 12) << "\n" << std::flush;
      }

      const Ival pair13_third_incoming_wr_sections[6] = {
          Ival(1) / Ival(2), Ival(2) / Ival(5),
          Ival(3) / Ival(10), Ival(1) / Ival(5),
          Ival(1) / Ival(10), Ival(0)};
      int third_passage_index = 0;
      for (const Ival& wr_section : pair13_third_incoming_wr_sections) {
        const Vector section_image = project_middle_c0(
            0, wr_section, capd::poincare::PlusMinus, false, 1);
        const DirectLcScalars section_sc =
            evaluate_direct_lc(section_image, family);
        if (!(section_image[2].rightBound() < 0) ||
            !(section_sc.i_dot.leftBound() > 0) ||
            !(section_sc.selected_radius.leftBound() > 0) ||
            !(section_sc.r12_squared.leftBound() > 0) ||
            !(section_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 third-incoming section lost its positive-J tube");
        }
        ++third_passage_index;
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair13_third_passage_section"
                  << " ordinal=" << third_passage_index << " tp=["
                  << bound_double(section_image[9].leftBound()) << ","
                  << bound_double(section_image[9].rightBound())
                  << "] zr=[" << bound_double(section_image[2].leftBound())
                  << "," << bound_double(section_image[2].rightBound())
                  << "] hull=" << hull_width(section_image, 12) << "\n"
                  << std::flush;
      }

      const Ival pair13_third_outgoing_wr_sections[6] = {
          Ival(-1) / Ival(10), Ival(-1) / Ival(5),
          Ival(-3) / Ival(10), Ival(-2) / Ival(5),
          Ival(-1) / Ival(2), Ival(-3) / Ival(5)};
      for (const Ival& wr_section : pair13_third_outgoing_wr_sections) {
        const Vector section_image = project_middle_c0(
            0, wr_section, capd::poincare::PlusMinus, false, 1);
        const DirectLcScalars section_sc =
            evaluate_direct_lc(section_image, family);
        if (!(section_image[2].rightBound() < 0) ||
            !(section_sc.i_dot.leftBound() > 0) ||
            !(section_sc.selected_radius.leftBound() > 0) ||
            !(section_sc.r12_squared.leftBound() > 0) ||
            !(section_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 third-outgoing section lost its positive-J tube");
        }
        ++third_passage_index;
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair13_third_passage_section"
                  << " ordinal=" << third_passage_index << " tp=["
                  << bound_double(section_image[9].leftBound()) << ","
                  << bound_double(section_image[9].rightBound())
                  << "] zr=[" << bound_double(section_image[2].leftBound())
                  << "," << bound_double(section_image[2].rightBound())
                  << "] hull=" << hull_width(section_image, 12) << "\n"
                  << std::flush;
      }

      // At the selected-pair outer turning point the radial LC component
      // zr crosses from negative to positive.  This is a fast geometric
      // section and leaves |w|^2 safely away from zero for the next
      // physical-time checkpoints.
      const Vector outer_turn_image = project_middle_c0(
          2, Ival(0), capd::poincare::MinusPlus, false, 1);
      {
        const DirectLcScalars outer_turn_sc =
            evaluate_direct_lc(outer_turn_image, family);
        if (!(outer_turn_sc.i_dot.leftBound() > 0) ||
            !(outer_turn_sc.selected_radius.leftBound() >
              (Ival(1) / Ival(4)).rightBound()) ||
            !(outer_turn_sc.r12_squared.leftBound() > 0) ||
            !(outer_turn_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 outer-turn section lost its separated positive-J tube");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair13_outer_turn_section"
                  << " tp=[" << bound_double(outer_turn_image[9].leftBound())
                  << "," << bound_double(outer_turn_image[9].rightBound())
                  << "] wr=[" << bound_double(outer_turn_image[0].leftBound())
                  << "," << bound_double(outer_turn_image[0].rightBound())
                  << "] wi=[" << bound_double(outer_turn_image[1].leftBound())
                  << "," << bound_double(outer_turn_image[1].rightBound())
                  << "] jd=[" << bound_double(outer_turn_image[11].leftBound())
                  << "," << bound_double(outer_turn_image[11].rightBound())
                  << "] hull=" << hull_width(outer_turn_image, 12) << "\n"
                  << std::flush;
      }

      // Superseded by the adaptive pair-23 round trip above: those sections
      // already crossed the t=2.329 pair-13 scattering before this outer
      // turn.  Retain the former itinerary temporarily for comparison.
#if 0
      const Ival pair13_pre_scatter_times[2] = {
          Ival(11) / Ival(5), Ival(23) / Ival(10)};
      for (const Ival& checkpoint_time : pair13_pre_scatter_times) {
        const Vector checkpoint_image = project_pair13_mean_value(
            event_graph, 9, checkpoint_time,
            capd::poincare::MinusPlus, 1);
        const DirectLcScalars checkpoint_sc =
            evaluate_direct_lc(checkpoint_image, family);
        if (!(checkpoint_sc.i_dot.leftBound() > 0) ||
            !(checkpoint_sc.selected_radius.leftBound() > 0) ||
            !(checkpoint_sc.r12_squared.leftBound() > 0) ||
            !(checkpoint_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 second-outgoing checkpoint lost its positive-J tube");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=second_outgoing_pair13"
                  << " tp=["
                  << bound_double(checkpoint_image[9].leftBound()) << ","
                  << bound_double(checkpoint_image[9].rightBound()) << "]"
                  << " jd=["
                  << bound_double(checkpoint_image[11].leftBound()) << ","
                  << bound_double(checkpoint_image[11].rightBound()) << "]"
                  << " hull=" << hull_width(checkpoint_image, 12) << "\n"
                  << std::flush;
      }

      // The next selected-pair scattering rotates zr from positive to
      // negative.  Recenter on that transverse LC-coordinate section before
      // the physical clock again slows near the pair passage.
      {
        const Vector before_scatter(event_graph.c0_set());
        if (!(before_scatter[2].leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 pre-scatter graph did not have positive zr");
        }
      }
      const Vector scatter_image = project_pair13_mean_value(
          event_graph, 2, Ival(0), capd::poincare::PlusMinus, 1);
      {
        const DirectLcScalars scatter_sc =
            evaluate_direct_lc(scatter_image, family);
        if (!(scatter_sc.i_dot.leftBound() > 0) ||
            !(scatter_sc.selected_radius.leftBound() > 0) ||
            !(scatter_sc.r12_squared.leftBound() > 0) ||
            !(scatter_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 second-scatter section lost its positive-J tube");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=pair13_second_scatter_section"
                  << " tp=[" << bound_double(scatter_image[9].leftBound())
                  << "," << bound_double(scatter_image[9].rightBound())
                  << "] wr=[" << bound_double(scatter_image[0].leftBound())
                  << "," << bound_double(scatter_image[0].rightBound())
                  << "] wi=[" << bound_double(scatter_image[1].leftBound())
                  << "," << bound_double(scatter_image[1].rightBound())
                  << "] jd=[" << bound_double(scatter_image[11].leftBound())
                  << "," << bound_double(scatter_image[11].rightBound())
                  << "] hull=" << hull_width(scatter_image, 12) << "\n"
                  << std::flush;
      }

      const Ival pair13_post_scatter_times[4] = {
          Ival(12) / Ival(5), Ival(5) / Ival(2), Ival(13) / Ival(5),
          Ival(53) / Ival(20)};
      for (const Ival& checkpoint_time : pair13_post_scatter_times) {
        const Vector checkpoint_image = project_pair13_mean_value(
            event_graph, 9, checkpoint_time,
            capd::poincare::MinusPlus, 1);
        const DirectLcScalars checkpoint_sc =
            evaluate_direct_lc(checkpoint_image, family);
        if (!(checkpoint_sc.i_dot.leftBound() > 0) ||
            !(checkpoint_sc.selected_radius.leftBound() > 0) ||
            !(checkpoint_sc.r12_squared.leftBound() > 0) ||
            !(checkpoint_sc.r23_squared.leftBound() > 0)) {
          throw std::runtime_error(
              "pair-13 post-scatter checkpoint lost its positive-J tube");
        }
        std::cout << "DIRECT_LC_EVENT_PROBE kind=second_outgoing_pair13"
                  << " tp=["
                  << bound_double(checkpoint_image[9].leftBound()) << ","
                  << bound_double(checkpoint_image[9].rightBound()) << "]"
                  << " jd=["
                  << bound_double(checkpoint_image[11].leftBound()) << ","
                  << bound_double(checkpoint_image[11].rightBound()) << "]"
                  << " hull=" << hull_width(checkpoint_image, 12) << "\n"
                  << std::flush;
      }

#endif
      const Vector second_maximum_image = project_middle_c0(
          11, Ival(0), capd::poincare::PlusMinus, false, 0);
      const DirectLcScalars second_maximum_sc =
          evaluate_direct_lc(second_maximum_image, family);
      if (!(second_maximum_sc.potential.rightBound() <
            (2 * family.u0).leftBound()) ||
          !direct_lc_residual_excludes_brake(second_maximum_image)) {
        throw std::runtime_error(
            "direct-LC second maximum lacks strictness or brake separation");
      }
      std::cout << "DIRECT_LC_EVENT_PROBE kind=second_maximum tp=["
                << bound_double(second_maximum_image[9].leftBound()) << ","
                << bound_double(second_maximum_image[9].rightBound()) << "]"
                << " UoverU0=["
                << bound_double(
                       (second_maximum_sc.potential / family.u0).leftBound())
                << ","
                << bound_double(
                       (second_maximum_sc.potential / family.u0).rightBound())
                << "] z=["
                << bound_double(second_maximum_image[2].leftBound()) << ","
                << bound_double(second_maximum_image[2].rightBound()) << "]+["
                << bound_double(second_maximum_image[3].leftBound()) << ","
                << bound_double(second_maximum_image[3].rightBound()) << "]i"
                << " P=["
                << bound_double(second_maximum_image[7].leftBound()) << ","
                << bound_double(second_maximum_image[7].rightBound()) << "]x["
                << bound_double(second_maximum_image[8].leftBound()) << ","
                << bound_double(second_maximum_image[8].rightBound()) << "]"
                << " hull=" << hull_width(second_maximum_image, 12) << "\n"
                << std::flush;
      std::cout << "PASS_TIED_SECOND_MAXIMUM_INTERVAL u=["
                << p << "/" << q << "," << p2 << "/" << q2 << "]"
                << " method=CAPD-6.1.0-MPFR"
                << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
                << "\n";
      return 0;
    }
  }

  Map field = make_direct_lc_field();
  PhaseRunner flow(field, order, tolerance);
  const Ival t1 = Ival(1) / Ival(5);
  bool initial_phase = true;
  long steps = 0;
  double largest_hull = 0;
  for (;;) {
    const Vector before(set);
    const double w_abs = std::sqrt(std::max(
        1e-12,
        bound_double((before[0] * before[0] + before[1] * before[1])
                         .leftBound())));
    const double cap =
        std::max(1.0 / 8000.0, std::min(w_abs / 24.0, 1.0 / 100.0));
    flow.direct_move(set, cap);
    ++steps;
    const Vector enclosure = set.getLastEnclosure();
    const Vector snapshot(set);
    const DirectLcScalars sc = evaluate_direct_lc(enclosure, family);
    if (!(sc.selected_radius.leftBound() > 0)) {
      std::cerr << "FAIL possible selected collision in direct-LC prefix"
                << " tp=" << to_double(snapshot[9]) << "\n";
      return 1;
    }
    if (!(sc.r12_squared.leftBound() > 0) ||
        !(sc.r23_squared.leftBound() > 0)) {
      std::cerr << "FAIL possible unselected collision in direct-LC prefix"
                << " tp=" << to_double(snapshot[9]) << "\n";
      return 1;
    }
    if (initial_phase) {
      if (!(sc.potential.rightBound() < (2 * family.u0).leftBound())) {
        std::cerr << "FAIL direct-LC initial potential bound"
                  << " tp=" << to_double(snapshot[9]) << "\n";
        return 1;
      }
      if (snapshot[9].leftBound() > t1.rightBound()) {
        initial_phase = false;
      }
    } else if (contains_zero(sc.i_dot) &&
               !(sc.potential.leftBound() > family.u0.rightBound()) &&
               !(sc.kinetic.leftBound() > 0) &&
               !direct_lc_residual_excludes_brake(enclosure)) {
      std::cerr << "FAIL uncovered direct-LC brake residual step"
                << " tp=" << to_double(snapshot[9]) << "\n";
      return 1;
    }
    largest_hull = std::max(largest_hull, hull_width(snapshot, 12));
    if (steps % 500 == 0) {
      std::cout << "direct_lc tp=" << to_double(snapshot[9])
                << " steps=" << steps
                << " hull_width=" << hull_width(snapshot, 12)
                << " retries=" << flow.capped_retries << "\n"
                << std::flush;
    }
    if (snapshot[9].leftBound() >= prefix_end) {
      std::cout << "PASS_TIED_DIRECT_LC_INTERVAL_PREFIX u=["
                << p << "/" << q << "," << p2 << "/" << q2
                << "] t_end=" << prefix_end << " reached_tp="
                << to_double(snapshot[9]) << " steps=" << steps
                << " max_hull_width=" << largest_hull << "\n";
      return 0;
    }
    if (steps > 200000) {
      std::cerr << "FAIL direct-LC prefix step limit\n";
      return 1;
    }
  }
}

}  // namespace

int main(int argc, char** argv) {
  const bool second_maximum_mode =
      argc > 1 && std::string(argv[1]) == "ilcmax2";
  const bool first_maximum_mode =
      argc > 1 &&
      (std::string(argv[1]) == "ilcmax" || second_maximum_mode);
  const bool direct_lc_mode =
      argc > 1 &&
      (std::string(argv[1]) == "ilcprefix" || first_maximum_mode);
  const bool prefix_mode =
      argc > 1 && (std::string(argv[1]) == "iprefix" || direct_lc_mode);
  if (prefix_mode && argc < 7) {
    std::cerr << "usage: burrau_lc_certificate_capd"
                 " {iprefix|ilcprefix|ilcmax|ilcmax2} P Q P2 Q2 TEND"
                 " [PREC TOL ORDER]\n";
    return 2;
  }
  const int precision = prefix_mode
                            ? (argc > 7 ? std::atoi(argv[7]) : 512)
                            : (argc > 1 ? std::atoi(argv[1]) : 512);
  const double tolerance = prefix_mode
                               ? (argc > 8 ? std::atof(argv[8]) : 1e-110)
                               : (argc > 2 ? std::atof(argv[2]) : 1e-110);
  const int order = prefix_mode
                        ? (argc > 9 ? std::atoi(argv[9]) : 80)
                        : (argc > 3 ? std::atoi(argv[3]) : 80);
  const double prefix_end = prefix_mode ? std::atof(argv[6]) : 0.0;
  capd::MpFloat::setDefaultPrecision(precision);
  try {
    Ival u_param = Ival(1) / Ival(3);
    long p = 1, q = 3, p2 = 1, q2 = 3;
    if (prefix_mode) {
      p = std::atol(argv[2]);
      q = std::atol(argv[3]);
      p2 = std::atol(argv[4]);
      q2 = std::atol(argv[5]);
      const Ival lower = Ival(p) / Ival(q);
      const Ival upper = Ival(p2) / Ival(q2);
      u_param = Ival(lower.leftBound(), upper.rightBound());
      if (!(u_param.leftBound() < u_param.rightBound()) ||
          !(u_param.leftBound() > 0) ||
          !(u_param.rightBound() < 1)) {
        std::cerr << "FAIL invalid Euclid-parameter interval\n";
        return 2;
      }
    }
    const Family family = make_family(u_param);
    if (direct_lc_mode) {
      return run_direct_lc_prefix(
          u_param, p, q, p2, q2, prefix_end, order, tolerance,
          first_maximum_mode, second_maximum_mode);
    }
    const int construction_rate = prefix_mode ? 20 : 400;
    const int construction_exponent = prefix_mode ? 10 : 380;
    const double construction_tolerance =
        prefix_mode ? std::min(tolerance, 1e-14) : 1e-112;
    const int construction_order = prefix_mode ? std::max(order, 30) : 70;
    Map physical_field = make_physical_field();
    Map lc_field = make_lc_field();
    Map exit_field = make_exit_field(construction_rate);
    const Ival eps_exit =
        Ival(-1, 1) * (Ival(1) / Ival(10)) /
        exp(Ival(construction_exponent));
    for (int i = 1; i <= 8; ++i) {
      exit_field.setParameter("e" + std::to_string(i), eps_exit);
    }

    Vector initial(19);
    for (int i = 0; i < 19; ++i) initial[i] = Ival(0);
    initial[0] = Ival(1);
    initial[18] = u_param;
    Set set(initial);
    {
      Map graph_field = make_initial_graph_field();
      PhaseRunner graph(graph_field, std::max(order, 40), tolerance);
      const Ival graph_start = set.getCurrentTime();
      const Ival graph_target = graph_start + Ival(1);
      while (graph.step(graph_target, set)) {
      }
      const Ival duration = set.getCurrentTime() - graph_start;
      if (!(duration.leftBound() <= 1 && duration.rightBound() >= 1)) {
        std::cerr << "FAIL initial graph construction duration\n";
        return 1;
      }
      const Vector post_graph(set);
      if (!(post_graph[18].leftBound() <= u_param.leftBound()) ||
          !(post_graph[18].rightBound() >= u_param.rightBound())) {
        std::cerr << "FAIL initial graph lost Euclid parameter\n";
        return 1;
      }
    }

    const Ival t1 = Ival(1) / Ival(4);
    const double escape_check_start = 11.5;
    // Zone thresholds: enter below 1/1000 (only the t=3.166 encounter,
    // r13 ~ 8.3e-5, goes that deep; the t=0.376 encounter bottoms at
    // 2.8e-3), exit above 1/500; brake-free zone bound
    // |g| < 1/4 < m1 m3 / U0 = 240/769.
    const Ival rho_in_sq = Ival(1) / Ival(6400);   // enter below 1/80
    const Ival rho_out = Ival(1) / Ival(50);       // exit above 1/50
    const Ival zone_bound = Ival(1) / Ival(4);
    if (!(zone_bound.rightBound() <
          (family.a / family.u0).leftBound())) {
      std::cerr << "FAIL LC zone is not uniformly brake-free\n";
      return 1;
    }

    long steps = 0;
    long event_steps = 0;
    double min_event_kinetic = 1e300;
    bool initial_phase = true;
    long lc_passages = 0;
    bool certified = false;
    Ival final_margin;

    std::cout << std::setprecision(17);

    // Physical phases interleaved with at most one LC passage.
    std::unique_ptr<PhaseRunner> phys(
        new PhaseRunner(physical_field, order, tolerance));
    Ival phys_target = set.getCurrentTime() + Ival(25);
    std::unique_ptr<Set> last_inbound_outside;

    for (;;) {
      const bool more = phys->step(phys_target, set);
      ++steps;
      const Vector enclosure = set.getLastEnclosure();
      const Vector snapshot(set);
      const Ival tp = snapshot[17];
      const Scalars sc = evaluate_scalars(enclosure, family, initial_phase);

      if (initial_phase) {
        if (!(sc.potential.rightBound() < (2 * family.u0).leftBound())) {
          std::cerr << "FAIL initial-window potential bound at tp="
                    << to_double(tp) << "\n";
          return 1;
        }
        if (tp.leftBound() > t1.rightBound()) initial_phase = false;
      } else {
        if (!step_excludes_brake(sc) &&
            !positions_exclude_brake(enclosure, family)) {
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

      if (prefix_mode && tp.leftBound() >= prefix_end) {
        certified = true;
        std::cout << "prefix endpoint reached at tp=" << to_double(tp)
                  << "\n";
        break;
      }

      if (!prefix_mode && bound_double(tp.rightBound()) > escape_check_start) {
        if (escape_certificate_fires(snapshot, &final_margin)) {
          certified = true;
          std::cout << "escape certificate fired at tp=" << to_double(tp)
                    << " margin=" << bound_double(final_margin.leftBound())
                    << "\n";
          break;
        }
      }
      if (!prefix_mode && bound_double(tp.leftBound()) > 14.5) {
        std::cerr << "FAIL tp exceeded 14.5 without escape certificate\n";
        return 1;
      }
      if (!more) {
        std::cerr << "FAIL phase clock bound reached\n";
        return 1;
      }

      // Zone entry test on the post-step snapshot.
      const Ival gsq = pair_g_sq(snapshot, family);
      const Ival gx_now = snapshot[2] + family.alpha * snapshot[0];
      const Ival gy_now = snapshot[3] + family.alpha * snapshot[1];
      const Ival gdx_now = snapshot[6] + family.alpha * snapshot[4];
      const Ival gdy_now = snapshot[7] + family.alpha * snapshot[5];
      const Ival g_radial_now =
          2 * (gx_now * gdx_now + gy_now * gdy_now);
      if (gsq.leftBound() > rho_in_sq.rightBound() &&
          g_radial_now.rightBound() < 0) {
        last_inbound_outside.reset(new Set(set));
      }
      if (gsq.rightBound() < rho_in_sq.leftBound()) {
        if (!last_inbound_outside) {
          std::cerr << "FAIL no certified outside state for LC entry map\n";
          return 1;
        }
        const Ival audited_entry_end = set.getCurrentTime();
        Set aligned_entry(*last_inbound_outside);
        Solver entry_section_solver(physical_field, order);
        entry_section_solver.setAbsoluteTolerance(tolerance);
        entry_section_solver.setRelativeTolerance(tolerance);
        const std::string pden = "(1+2*ww-ww^2)";
        const std::string alpha = "(2*ww/" + pden + ")";
        NonlinearSection entry_section(
            std::string(kVars) + "fun:(y1+" + alpha +
            "*x1)^2+(y2+" + alpha + "*x2)^2-1/6400;");
        PoincareMap entry_map(
            entry_section_solver, entry_section,
            capd::poincare::PlusMinus);
        entry_map.setMaxReturnTime(10.0);
        Ival entry_return_time;
        const Vector entry_image =
            entry_map(aligned_entry, entry_return_time);
        if (!(entry_return_time.rightBound() <
              audited_entry_end.leftBound())) {
          std::cerr << "FAIL physical audit does not cover LC entry time\n";
          return 1;
        }
        set = Set(entry_image);
        const Vector entry_snapshot(set);
        const Ival entry_gsq = pair_g_sq(entry_snapshot, family);
        const Ival entry_gx =
            entry_snapshot[2] + family.alpha * entry_snapshot[0];
        const Ival entry_gy =
            entry_snapshot[3] + family.alpha * entry_snapshot[1];
        const Ival entry_gdx =
            entry_snapshot[6] + family.alpha * entry_snapshot[4];
        const Ival entry_gdy =
            entry_snapshot[7] + family.alpha * entry_snapshot[5];
        const Ival entry_radial =
            2 * (entry_gx * entry_gdx + entry_gy * entry_gdy);
        const Ival entry_target = Ival(1) / Ival(6400);
        if (!(entry_gsq.leftBound() <= entry_target.leftBound() &&
              entry_gsq.rightBound() >= entry_target.rightBound()) ||
            !(entry_radial.rightBound() < 0)) {
          std::cerr << "FAIL LC Poincare entry section or orientation\n";
          return 1;
        }
        last_inbound_outside.reset();
        ++lc_passages;
        if (lc_passages > 60) {
          std::cerr << "FAIL too many LC passages\n";
          return 1;
        }
        std::cout << "LC Poincare entry at tp="
                  << to_double(entry_snapshot[17])
                  << " |g|^2=" << bound_double(entry_gsq.rightBound())
                  << " hull_width=" << hull_width(entry_snapshot, 19) << "\n"
                  << std::flush;

        // Entry-branch selection by the sign of gx (form B is valid for
        // any g off the positive real axis, i.e. whenever gy != 0 or
        // gx < 0; form A off the negative axis).
        const Ival gx = entry_snapshot[2] + family.alpha * entry_snapshot[0];
        const Ival gy = entry_snapshot[3] + family.alpha * entry_snapshot[1];
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
          Map entry_field = make_entry_field(form_a, construction_rate);
          const Ival eps_entry =
              Ival(-1, 1) * (Ival(1) / Ival(10)) /
              exp(Ival(construction_exponent));
          for (int i = 1; i <= 9; ++i) {
            entry_field.setParameter("f" + std::to_string(i), eps_entry);
          }
          PhaseRunner entry(entry_field, construction_order,
                            construction_tolerance);
          const Vector construction_initial(set);
          const Ival construction_start = set.getCurrentTime();
          const Ival target = construction_start + Ival(1);
          while (entry.step(target, set)) {
          }
          // ITimeMap may declare completion when the current time interval
          // merely overlaps the target.  Therefore the nominal target
          // difference is not a proved lower duration.  Audit against the
          // actual post-flow lower endpoint instead.
          const Ival duration_lower(
              set.getCurrentTime().leftBound() -
              construction_start.rightBound());
          audit_entry_damped_write(
              construction_initial, form_a, family, construction_rate,
              eps_entry,
              duration_lower);
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
            for (int i = 8; i < 19; ++i) {
              std::cout << " v" << i << "="
                        << bound_double(post_entry[i].leftBound());
            }
            std::cout << "\n" << std::flush;
          }
        }

        // LC passage.
        {
          const Set section_initial(set);
          PhaseRunner lc(lc_field, order, tolerance);
          // Small sigma-steps keep each step's swept enclosure of w well
          // inside a disc that excludes w = 0 (|w| ~ 9e-3 at closest
          // approach, |dw/dsigma| ~ 1), so the per-step no-collision check
          // certifies the strong collision-free statement.  Direct solver
          // moves make the cap actually bind.
          long lc_steps = 0;
          for (;;) {
            // Adaptive sigma cap: sweep stays well inside a disc excluding
            // w = 0 (sweep ~ cap * |z| with |z| <~ 1, guard factor ~20).
            const Vector pre_snap(set);
            const double w_abs = std::sqrt(std::max(
                1e-12,
                bound_double((pre_snap[8] * pre_snap[8] +
                              pre_snap[9] * pre_snap[9]).leftBound())));
            const double lc_cap =
                std::max(1.0 / 4000.0, std::min(w_abs / 20.0, 1.0 / 100.0));
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
                        << " hull_width=" << hull_width(lc_snap, 19)
                        << " retries=" << lc.capped_retries << "\n"
                        << std::flush;
              break;
            }
            if (!lc_more) {
              std::cerr << "FAIL LC phase hit sigma bound without exit\n";
              return 1;
            }
          }

          // The fixed-sigma audit above proves that every trajectory stays
          // collision-free until it has crossed |g|=rho_out outward.  It is
          // deliberately not used as the propagated state: parameter values
          // cross that section at different sigma times, and retaining a
          // common clock injects the nearly-flow time-shift direction into
          // the interval hull.  Recompute the same exit as an oriented
          // Poincare map from the saved entry set.
          const Ival audited_end = set.getCurrentTime();
          set = section_initial;
          Solver section_solver(lc_field, order);
          section_solver.setAbsoluteTolerance(tolerance);
          section_solver.setRelativeTolerance(tolerance);
          NonlinearSection exit_section(
              std::string(kVars) +
              "fun:(wr^2+wi^2)-1/50;");
          PoincareMap exit_map(
              section_solver, exit_section, capd::poincare::MinusPlus);
          exit_map.setMaxReturnTime(10.0);
          Ival return_time;
          const Vector section_image = exit_map(set, return_time);
          if (!(return_time.rightBound() < audited_end.leftBound())) {
            std::cerr << "FAIL LC collision audit does not cover section time\n";
            return 1;
          }
          set = Set(section_image);
          const Vector section_state(set);
          const Ival section_radius =
              section_state[8] * section_state[8] +
              section_state[9] * section_state[9];
          const Ival section_radial =
              2 * (section_state[8] * section_state[10] +
                   section_state[9] * section_state[11]);
          if (!section_radius.contains(Ival(1) / Ival(50)) ||
              !(section_radial.leftBound() > 0)) {
            std::cerr << "FAIL LC Poincare exit section or orientation"
                      << " radius=["
                      << bound_double(section_radius.leftBound()) << ","
                      << bound_double(section_radius.rightBound()) << "]"
                      << " radial=["
                      << bound_double(section_radial.leftBound()) << ","
                      << bound_double(section_radial.rightBound()) << "]"
                      << " return=["
                      << bound_double(return_time.leftBound()) << ","
                      << bound_double(return_time.rightBound()) << "]\n";
            return 1;
          }
          std::cout << "LC Poincare exit at tp="
                    << to_double(section_state[17])
                    << " hull_width=" << hull_width(section_state, 19)
                    << " return_time_width="
                    << bound_double(return_time.rightBound() -
                                    return_time.leftBound())
                    << "\n" << std::flush;
        }

        // Exit construction after a boundedness check.
        {
          const Vector pre(set);
          for (int i = 0; i < 19; ++i) {
            if (!(pre[i].rightBound() < 100 && pre[i].leftBound() > -100)) {
              std::cerr << "FAIL exit boundedness check\n";
              return 1;
            }
          }
          // The damped exit flow has decay rate 400; its integration
          // tolerance caps the precision of the written physical state,
          // so it must sit below the main tolerance.  At order 70 the
          // stiff flow still takes ~1e-3 steps: ~1000 steps total.
          PhaseRunner exitr(exit_field, construction_order,
                            construction_tolerance);
          const Vector construction_initial(set);
          const Ival construction_start = set.getCurrentTime();
          const Ival target = construction_start + Ival(1);
          while (exitr.step(target, set)) {
          }
          const Ival duration_lower(
              set.getCurrentTime().leftBound() -
              construction_start.rightBound());
          audit_exit_damped_write(
              construction_initial, family, construction_rate, eps_exit,
              duration_lower);
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
    if (prefix_mode) {
      std::cout << "PASS_TIED_LC_INTERVAL_PREFIX u=[" << p << "/" << q
                << "," << p2 << "/" << q2 << "] t_end=" << prefix_end
                << "\n";
    } else {
      std::cout << "PASS_BURRAU_LC\n";
    }
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "FAIL exception: " << error.what() << "\n";
    return 1;
  }
}
