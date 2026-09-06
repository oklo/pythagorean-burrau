// Parameterized Poincare-section graph prototype for the middle interval.
//
// Implements and benchmarks the first-order graph step (Theorem PG1) and
// the second-order graph step (Theorem PG2) of
// docs/FABLE_PARAMETER_GRAPH_AUDIT.md:
//
//   PG1:  X(u) in x + T d + E,          d = u - u_c in [-r, r]
//   PG2:  X(u) in x + T d + Q d^2 + E
//
// with Poincare-return updates
//
//   PG1:  T' = [DP] T,   E' = (P(x)^ - mid) + [DP] E
//   PG2:  T' = DP(x) T + 2 [D2P][T,E]
//         Q' = DP(x) Q + [D2P][T,T] + 2 [D2P][Q,E]
//         E' = (P(x)^ - mid) + DP(x) E + [D2P][E,E]
//             + 2 [D2P][T,Q] D^3 + [D2P][Q,Q] D^4
//
// both followed by intersection sharpening against the independent
// C0-image enclosure minus x' + T' D (+ Q' D^2), exact re-imposition of
// the section row and the frozen-parameter row, and an independent
// correlated C0 audit tube carrying the collision-separation and
// brake-exclusion checks through the latest return (Theorem C'
// covering).  Chart switches use the same formulas with the algebraic
// map's derivative/Hessian (CAPD Map::operator()(x,df,hf), degree 2).
//
// Machinery (Family, LC fields, switch maps, PhaseRunner, scalars,
// launch graph) is copied verbatim from the committed
// burrau_lc_certificate_capd.cpp lineage, as in
// middle_escape_endgame_capd.cpp.  The protected files are not touched.
//
// Usage:
//   parameter_graph_capd MODE P Q P2 Q2 [PREC TOL ORDER]
// MODE: 1 = PG1 everywhere; 2 = PG1 for the launch leg values, PG2 for
// every Poincare and switch update.  The benchmark itinerary (post
// Form-B pair-{2,3} wr-ladder, then tp=77/20, then the phase-robust
// terminal certificate evaluated BOTH on the final geometric section
// graph (per-fiber times) and on the fixed-time hull) is hardwired; see
// docs/FABLE_PARAMETER_GRAPH_HANDOFF.md.
//
// Dependency pin: CAPD 6.1.0, commit
// 731079217a9254ea2948d742df2b170895effe7f, MP build.

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "capd/mpcapdlib.h"

namespace {

typedef capd::MpInterval Ival;
typedef capd::MpIMap Map;
typedef capd::MpIOdeSolver Solver;
typedef capd::MpITimeMap TimeMap;
typedef capd::MpIVector Vector;
typedef capd::MpIMatrix Matrix;
typedef capd::MpC0TripletonSet Set;
typedef capd::MpC1Rect2Set C1Set;
typedef capd::MpICoordinateSection CoordinateSection;
typedef capd::MpIPoincareMap PoincareMap;
// Second-order machinery.
typedef capd::MpIC2OdeSolver C2Solver;
typedef capd::MpC2Rect2Set C2Set;
typedef capd::poincare::PoincareMap<C2Solver> C2PoincareMap;
typedef C2PoincareMap::HessianType Hessian;

double bound_double(const capd::MpFloat& x) { return toDouble(x); }
double to_double(const Ival& x) { return bound_double(x.rightBound()); }

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
const char* kDirectLcVars =
    "var:wr,wi,zr,zi,hh,cgx,cgy,cpx,cpy,tp,ww,jd;";

// The same selected-pair regularization without the frozen physical/chart
// blocks.  This chart is nonsingular from the tied launch through the early
// maximum-event branch and avoids both entry and exit time-shift wrapping.
Map make_direct_lc_field(int degree = 1) {
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
  // jd = dI/dt.  Multiplication by dt/dsigma=|w|^2 cancels the selected
  // A/|g| potential term, leaving a field regular at w=0.
  const std::string jd_sigma =
      "(2*(" + ab + "*" + w2 + "/sqrt(" + r12sq + ")+" + ma +
      "+" + mb + "*" + w2 + "/sqrt(" + r23sq + "))-4*" + u0 +
      "*" + w2 + ")";
  return Map(std::string(kDirectLcVars) +
             "fun:zr,zi,"
             "(hh/2)*wr+(" + w2 + "/2)*(wr*" + fx + "+wi*" + fy + "),"
             "(hh/2)*wi+(" + w2 + "/2)*(wr*" + fy + "-wi*" + fx + "),"
             "2*((wr*zr-wi*zi)*" + fx + "+(wr*zi+wi*zr)*" + fy + "),"
             + w2 + "*cpx," + w2 + "*cpy," + w2 + "*" + gddx + "," +
             w2 + "*" + gddy + "," + w2 + ",0," + jd_sigma + ";", degree);
}

// Direct Levi--Civita field for selected pair {2,3}, with
// g=q3-q2 and complement G=q1-C23.  The state layout is unchanged.
Map make_pair23_lc_field(int degree = 1) {
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
  const std::string jd_sigma =
      "(2*(" + ab + "*" + w2 + "/sqrt(" + r12sq + ")+" + mb +
      "+" + ma + "*" + w2 + "/sqrt(" + r13sq + "))-4*" + u0 +
      "*" + w2 + ")";
  return Map(std::string(kDirectLcVars) +
             "fun:zr,zi,"
             "(hh/2)*wr+(" + w2 + "/2)*(wr*" + fx + "+wi*" + fy + "),"
             "(hh/2)*wi+(" + w2 + "/2)*(wr*" + fy + "-wi*" + fx + "),"
             "2*((wr*zr-wi*zi)*" + fx + "+(wr*zi+wi*zr)*" + fy + "),"
             + w2 + "*cpx," + w2 + "*cpy," + w2 + "*" + gddx + "," +
             w2 + "*" + gddy + "," + w2 + ",0," + jd_sigma + ";", degree);
}

Map make_pair13_to_pair23_map(int degree = 1) {
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
  return Map(std::string(kDirectLcVars) + "fun:" + new_wr + "," +
             new_wi + "," + new_zr + "," + new_zi + "," + new_h +
             "," + new_gx + "," + new_gy + "," + new_px + "," +
             new_py + ",tp,ww,jd;", degree);
}

// Exact tied launch in the direct selected-pair chart.  Since
// g=q3-q1=(B^2,AB) and |g|=B, the positive square-root branch is explicit.
Map make_direct_lc_initial_graph_field(int degree = 1) {
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
             "," + cgy + ",0,0,0,0,0;", degree);
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
double hull_width(const Vector& s, int n) {
  double w = 0;
  for (int i = 0; i < n; ++i) {
    w = std::max(w, bound_double(s[i].rightBound() - s[i].leftBound()));
  }
  return w;
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
// ---- Parameter-graph machinery (new; nothing above differs from the
// ---- committed chunks except the header block and the optional degree
// ---- parameter threaded through the field makers). ----

// Exact chart switches copied from middle_escape_endgame_capd.cpp (my own
// code, regression-tested in tests/test_middle_escape_endgame_maps.py),
// with the degree parameter added.
Map make_pair23_to_pair13_map(int degree = 1) {
  const std::string qden = "(1+ww^2)";
  const std::string inv_m23 = "(" + qden + "/(1+ww)^2)";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string m13 = "(2/" + qden + ")";
  const std::string old_w2 = "(wr^2+wi^2)";
  const std::string old_gx = "(wr^2-wi^2)";
  const std::string old_gy = "(2*wr*wi)";
  const std::string old_gdx = "(2*(wr*zr-wi*zi)/" + old_w2 + ")";
  const std::string old_gdy = "(2*(wr*zi+wi*zr)/" + old_w2 + ")";
  const std::string d13x = "(cgx+(" + inv_m23 + "-1)*" + old_gx + ")";
  const std::string d13y = "(cgy+(" + inv_m23 + "-1)*" + old_gy + ")";
  const std::string d13dx = "(cpx+(" + inv_m23 + "-1)*" + old_gdx + ")";
  const std::string d13dy = "(cpy+(" + inv_m23 + "-1)*" + old_gdy + ")";
  const std::string gx = "(-" + d13x + ")";
  const std::string gy = "(-" + d13y + ")";
  const std::string gdx = "(-" + d13dx + ")";
  const std::string gdy = "(-" + d13dy + ")";
  const std::string abs_g = "sqrt(" + gx + "^2+" + gy + "^2)";
  const std::string new_wr = "sqrt((" + abs_g + "+" + gx + ")/2)";
  const std::string new_wi = "(" + gy + "/(2*" + new_wr + "))";
  const std::string new_zr =
      "((" + new_wr + "*" + gdx + "+" + new_wi + "*" + gdy + ")/2)";
  const std::string new_zi =
      "((" + new_wr + "*" + gdy + "-" + new_wi + "*" + gdx + ")/2)";
  const std::string new_h =
      "((" + gdx + "^2+" + gdy + "^2)/2-" + m13 + "/" + abs_g + ")";
  const std::string d12x = "(cgx+" + inv_m23 + "*" + old_gx + ")";
  const std::string d12y = "(cgy+" + inv_m23 + "*" + old_gy + ")";
  const std::string d12dx = "(cpx+" + inv_m23 + "*" + old_gdx + ")";
  const std::string d12dy = "(cpy+" + inv_m23 + "*" + old_gdy + ")";
  const std::string new_gx = "(-" + d12x + "-" + inv_m13 + "*" + gx + ")";
  const std::string new_gy = "(-" + d12y + "-" + inv_m13 + "*" + gy + ")";
  const std::string new_px = "(-" + d12dx + "-" + inv_m13 + "*" + gdx + ")";
  const std::string new_py = "(-" + d12dy + "-" + inv_m13 + "*" + gdy + ")";
  return Map(std::string(kDirectLcVars) + "fun:" + new_wr + "," +
             new_wi + "," + new_zr + "," + new_zi + "," + new_h +
             "," + new_gx + "," + new_gy + "," + new_px + "," +
             new_py + ",tp,ww,jd;", degree);
}

Map make_pair13_to_pair23_map_form_b(int degree = 1) {
  const std::string qden = "(1+ww^2)";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string inv_m23 = "(" + qden + "/(1+ww)^2)";
  const std::string m23 = "((1+ww)^2/" + qden + ")";
  const std::string old_w2 = "(wr^2+wi^2)";
  const std::string old_gx = "(wr^2-wi^2)";
  const std::string old_gy = "(2*wr*wi)";
  const std::string old_gdx = "(2*(wr*zr-wi*zi)/" + old_w2 + ")";
  const std::string old_gdy = "(2*(wr*zi+wi*zr)/" + old_w2 + ")";
  const std::string old_xx = "(cgx+" + inv_m13 + "*" + old_gx + ")";
  const std::string old_xy = "(cgy+" + inv_m13 + "*" + old_gy + ")";
  const std::string old_xdx = "(cpx+" + inv_m13 + "*" + old_gdx + ")";
  const std::string old_xdy = "(cpy+" + inv_m13 + "*" + old_gdy + ")";
  const std::string gx = "(" + old_gx + "-" + old_xx + ")";
  const std::string gy = "(" + old_gy + "-" + old_xy + ")";
  const std::string gdx = "(" + old_gdx + "-" + old_xdx + ")";
  const std::string gdy = "(" + old_gdy + "-" + old_xdy + ")";
  const std::string abs_g = "sqrt(" + gx + "^2+" + gy + "^2)";
  const std::string new_wi = "sqrt((" + abs_g + "-" + gx + ")/2)";
  const std::string new_wr = "(" + gy + "/(2*" + new_wi + "))";
  const std::string new_zr =
      "((" + new_wr + "*" + gdx + "+" + new_wi + "*" + gdy + ")/2)";
  const std::string new_zi =
      "((" + new_wr + "*" + gdy + "-" + new_wi + "*" + gdx + ")/2)";
  const std::string new_h =
      "((" + gdx + "^2+" + gdy + "^2)/2-" + m23 + "/" + abs_g + ")";
  const std::string new_gx = "(-" + old_xx + "-" + inv_m23 + "*" + gx + ")";
  const std::string new_gy = "(-" + old_xy + "-" + inv_m23 + "*" + gy + ")";
  const std::string new_px = "(-" + old_xdx + "-" + inv_m23 + "*" + gdx + ")";
  const std::string new_py = "(-" + old_xdy + "-" + inv_m23 + "*" + gdy + ")";
  return Map(std::string(kDirectLcVars) + "fun:" + new_wr + "," +
             new_wi + "," + new_zr + "," + new_zi + "," + new_h +
             "," + new_gx + "," + new_gy + "," + new_px + "," +
             new_py + ",tp,ww,jd;", degree);
}

// ---------------------------------------------------------------------
// The parameterized graph  X(u) in x + T d + Q d^2 + E,  d in [-r, r].
// Rows 10 (frozen parameter ww) and, on a section, the section
// coordinate, are exact.

constexpr int kDim = 12;
constexpr int kParamRow = 10;

// Storage convention of algebraic-Map Hessians (settled at startup by a
// runtime self-test on a quadratic map; the flow-Hessian path is fixed
// Taylor-coefficient storage per the CAPD computeDP documentation).
bool g_map_hessian_is_derivative = false;

struct ParamGraph {
  Vector x, T, Q, E;
  Ival radius;    // point interval r
  Ival u_center;  // point interval u_c

  Ival delta() const {
    return Ival(-radius.rightBound(), radius.rightBound());
  }
  Ival delta2() const {
    return Ival(0, (radius * radius).rightBound());
  }
  Ival delta3() const {
    const Ival r3 = radius * radius * radius;
    return Ival(-r3.rightBound(), r3.rightBound());
  }
  Ival delta4() const {
    const Ival r4 = radius * radius * radius * radius;
    return Ival(0, (r4).rightBound());
  }
  Vector hull() const {
    Vector out(kDim);
    const Ival d = delta(), d2 = delta2();
    for (int i = 0; i < kDim; ++i) out[i] = x[i] + T[i] * d + Q[i] * d2 + E[i];
    return out;
  }
  void impose_exact_row(int row, const Ival& value, const Ival& tangent) {
    x[row] = value;
    T[row] = tangent;
    Q[row] = Ival(0);
    E[row] = Ival(0);
  }
};

double width_of(const Ival& v) {
  return bound_double(v.rightBound() - v.leftBound());
}
double max_width(const Vector& v, int n = kDim) {
  double w = 0;
  for (int i = 0; i < n; ++i) w = std::max(w, width_of(v[i]));
  return w;
}

void print_graph(const char* label, const ParamGraph& g) {
  const Vector h = g.hull();
  double tanw = 0, qw = 0;
  const Ival d = g.delta(), d2 = g.delta2();
  for (int i = 0; i < kDim; ++i) {
    tanw = std::max(tanw, width_of(g.T[i] * d));
    qw = std::max(qw, width_of(g.Q[i] * d2));
  }
  std::cout << "PGRAPH_LEG " << label << " tp=["
            << bound_double(h[9].leftBound()) << ","
            << bound_double(h[9].rightBound()) << "] hull="
            << max_width(h) << " tan=" << tanw << " q=" << qw
            << " def=" << max_width(g.E) << "\n" << std::flush;
}

// Hessian bilinear helpers.  Storage h(k,i,j) with i<=j.  The
// interpretation depends on the source: the flow path (PoincareMap
// computeDP) stores TAYLOR COEFFICIENTS (coefficient of h_i h_j in the
// expansion); the algebraic-Map path stores second DERIVATIVES.  The
// derivative flag converts: coefficient(i,j) = H(i,j) for i<j (mixed
// partial appears once), = H(i,i)/2 on the diagonal.
Vector hess_quad(const Hessian& h, const Vector& a, bool derivative_storage) {
  Vector out(kDim);
  for (int k = 0; k < kDim; ++k) {
    Ival s(0);
    for (int i = 0; i < kDim; ++i)
      for (int j = i; j < kDim; ++j) {
        Ival c = h(k, i, j);
        if (derivative_storage && i == j) c = c / Ival(2);
        s += c * a[i] * a[j];
      }
    out[k] = s;
  }
  return out;
}
Vector hess_cross(const Hessian& h, const Vector& a, const Vector& b,
                  bool derivative_storage) {
  Vector out(kDim);
  for (int k = 0; k < kDim; ++k) {
    Ival s(0);
    for (int i = 0; i < kDim; ++i)
      for (int j = i; j < kDim; ++j) {
        Ival c = h(k, i, j);
        if (derivative_storage && i == j) c = c / Ival(2);
        s += c * (a[i] * b[j] + b[i] * a[j]);
      }
    out[k] = s;
  }
  return out;
}

Vector mid_vector(const Vector& v) {
  Vector out(kDim);
  for (int i = 0; i < kDim; ++i)
    out[i] = (Ival(v[i].leftBound()) + Ival(v[i].rightBound())) / 2;
  return out;
}

// Correlated pieces for CAPD set constructors: point x, point C with the
// tangent midpoint in column kParamRow... we use column 0 of r0 as the
// parameter deviation slot, so C(:,0) = mid(T); everything else spills
// into the centered remainder.
struct SetPieces {
  Vector x0, r0, rem;
  Matrix c;
};
SetPieces graph_pieces(const ParamGraph& g) {
  SetPieces p{Vector(kDim), Vector(kDim), Vector(kDim),
              Matrix(kDim, kDim)};
  const Ival d = g.delta(), d2 = g.delta2();
  p.x0 = mid_vector(g.x);
  const Vector t_mid = mid_vector(g.T);
  for (int i = 0; i < kDim; ++i) {
    for (int j = 0; j < kDim; ++j) p.c[i][j] = Ival(i == j ? 1 : 0);
    p.c[i][0] = t_mid[i];
    p.r0[i] = Ival(0);
    p.rem[i] = (g.x[i] - p.x0[i]) + (g.T[i] - t_mid[i]) * d +
               g.Q[i] * d2 + g.E[i];
  }
  p.r0[0] = g.delta();
  return p;
}

// ---------------------------------------------------------------------
// Audit tube: independent correlated C0 propagation of the graph through
// sigma_target, carrying collision separations, the Theorem C' covering
// disjunction (with the optional launch window), the unselected-pair
// step caps, and a hull sanity guard.

void audit_tube(const ParamGraph& g, bool pair23, double sigma_target,
                bool launch_window, int order, double tolerance,
                const Family& family, const char* label) {
  SetPieces p = graph_pieces(g);
  Set set(p.x0, p.c, p.r0, p.rem);
  Map field = pair23 ? make_pair23_lc_field() : make_direct_lc_field();
  PhaseRunner flow(field, order, tolerance);
  const Ival two_u0 = 2 * family.u0;
  const Ival t1 = Ival(1) / Ival(5);
  bool in_window = launch_window;
  for (long steps = 0;; ++steps) {
    if (steps > 400000) {
      throw std::runtime_error(std::string(label) + ": audit step limit");
    }
    const Vector before(set);
    if (bound_double(set.getCurrentTime().leftBound()) >= sigma_target) break;
    const DirectLcScalars pre =
        pair23 ? evaluate_pair23_lc(before, family)
               : evaluate_direct_lc(before, family);
    const double w_abs = std::sqrt(std::max(
        1e-12, bound_double(pre.selected_radius.leftBound())));
    const double unselected = std::sqrt(std::max(
        1e-12,
        std::min(bound_double(pre.r12_squared.leftBound()),
                 bound_double(pre.r23_squared.leftBound()))));
    const double w2_lower = std::max(1e-12, w_abs * w_abs);
    const double unselected_cap =
        unselected * std::sqrt(unselected) / (40.0 * w2_lower);
    const double cap = std::max(
        1.0 / 20000.0,
        std::min(std::min(w_abs / 24.0, unselected_cap), 1.0 / 100.0));
    flow.direct_move(set, cap);
    const Vector enclosure = set.getLastEnclosure();
    const Vector snapshot(set);
    const DirectLcScalars sc =
        pair23 ? evaluate_pair23_lc(enclosure, family)
               : evaluate_direct_lc(enclosure, family);
    if (!(sc.selected_radius.leftBound() > 0) ||
        !(sc.r12_squared.leftBound() > 0) ||
        !(sc.r23_squared.leftBound() > 0)) {
      throw std::runtime_error(std::string(label) +
                               ": audit lost collision separation");
    }
    if (in_window) {
      if (!(sc.potential.rightBound() < two_u0.leftBound())) {
        if (!(sc.i_dot.rightBound() < 0)) {
          throw std::runtime_error(std::string(label) +
                                   ": launch window exit lost J<0");
        }
        in_window = false;
      }
      if (snapshot[9].leftBound() > t1.rightBound()) in_window = false;
    } else if (contains_zero(sc.i_dot) &&
               !(sc.potential.leftBound() > family.u0.rightBound()) &&
               !(sc.kinetic.leftBound() > 0) &&
               !direct_lc_residual_excludes_brake(enclosure)) {
      throw std::runtime_error(std::string(label) +
                               ": audit uncovered brake-exclusion step");
    }
    if (max_width(snapshot) > 10.0) {
      throw std::runtime_error(std::string(label) + ": audit hull exploded");
    }
  }
}

// ---------------------------------------------------------------------
// Poincare graph step (Theorems PG1 / PG2).

ParamGraph poincare_leg(const ParamGraph& g, int coord, const Ival& value,
                        capd::poincare::CrossingDirection dir, bool pair23,
                        int mode, int order, double tolerance,
                        bool launch_window, const Family& family,
                        const char* label) {
  ParamGraph out = g;
  Vector image(kDim);
  Ival return_time;

  if (mode == 1) {
    Map field = pair23 ? make_pair23_lc_field() : make_direct_lc_field();
    CoordinateSection section(kDim, coord, value);
    Solver solver(field, order);
    solver.setAbsoluteTolerance(tolerance);
    solver.setRelativeTolerance(tolerance);
    PoincareMap pm(solver, section, dir);
    pm.setMaxReturnTime(60.0);
    SetPieces p = graph_pieces(g);
    C1Set cset(p.x0, p.c, p.r0, p.rem);
    Matrix dflow(kDim, kDim);
    image = pm(cset, dflow, return_time);
    const Matrix dp = pm.computeDP(image, dflow);
    // Thin anchor.
    Map afield = pair23 ? make_pair23_lc_field() : make_direct_lc_field();
    Solver asolver(afield, order);
    asolver.setAbsoluteTolerance(tolerance);
    asolver.setRelativeTolerance(tolerance);
    PoincareMap apm(asolver, section, dir);
    apm.setMaxReturnTime(60.0);
    Set aset(g.x);
    Ival art;
    const Vector phat = apm(aset, art);
    out.x = mid_vector(phat);
    Vector t_new(kDim), e_new(kDim);
    const Vector dpT = dp * g.T;
    const Vector dpE = dp * g.E;
    const Vector dpQ = dp * g.Q;
    for (int i = 0; i < kDim; ++i) {
      t_new[i] = dpT[i];
      out.Q[i] = dpQ[i];
      e_new[i] = (phat[i] - out.x[i]) + dpE[i];
    }
    out.T = t_new;
    out.E = e_new;
  } else {
    Map field2 = pair23 ? make_pair23_lc_field(2) : make_direct_lc_field(2);
    CoordinateSection section(kDim, coord, value);
    C2Solver solver2(field2, order);
    solver2.setAbsoluteTolerance(tolerance);
    solver2.setRelativeTolerance(tolerance);
    C2PoincareMap pm2(solver2, section, dir);
    pm2.setMaxReturnTime(60.0);
    SetPieces p = graph_pieces(g);
    C2Set cset(p.x0, p.c, p.r0, p.rem);
    Matrix dflow(kDim, kDim);
    Hessian hflow(kDim, kDim);
    image = pm2(cset, dflow, hflow, return_time);
    Matrix dp(kDim, kDim);
    Hessian d2p(kDim, kDim);
    pm2.computeDP(image, dflow, hflow, dp, d2p);
    // Thin anchor with its own derivative.
    Map afield = pair23 ? make_pair23_lc_field() : make_direct_lc_field();
    Solver asolver(afield, order);
    asolver.setAbsoluteTolerance(tolerance);
    asolver.setRelativeTolerance(tolerance);
    PoincareMap apm(asolver, section, dir);
    apm.setMaxReturnTime(60.0);
    C1Set aset(g.x);
    Matrix adflow(kDim, kDim);
    Ival art;
    const Vector phat = apm(aset, adflow, art);
    const Matrix dpx = apm.computeDP(phat, adflow);
    // PG2 update (flow Hessians store Taylor coefficients).
    const bool deriv_storage = false;
    out.x = mid_vector(phat);
    const Vector dpxT = dpx * g.T;
    const Vector dpxQ = dpx * g.Q;
    const Vector dpxE = dpx * g.E;
    const Vector qTT = hess_quad(d2p, g.T, deriv_storage);
    const Vector qEE = hess_quad(d2p, g.E, deriv_storage);
    const Vector qQQ = hess_quad(d2p, g.Q, deriv_storage);
    const Vector cTE = hess_cross(d2p, g.T, g.E, deriv_storage);
    const Vector cQE = hess_cross(d2p, g.Q, g.E, deriv_storage);
    const Vector cTQ = hess_cross(d2p, g.T, g.Q, deriv_storage);
    const Ival d3 = g.delta3(), d4 = g.delta4();
    for (int i = 0; i < kDim; ++i) {
      out.T[i] = dpxT[i] + cTE[i];
      out.Q[i] = dpxQ[i] + qTT[i] + cQE[i];
      out.E[i] = (phat[i] - out.x[i]) + dpxE[i] + qEE[i] +
                 cTQ[i] * d3 + qQQ[i] * d4;
    }
  }

  // Intersection sharpening against the independent image (full range).
  const Ival d = out.delta(), d2r = out.delta2();
  for (int i = 0; i < kDim; ++i) {
    const Ival alt = image[i] - out.x[i] - out.T[i] * d - out.Q[i] * d2r;
    Ival sharpened;
    if (!capd::intervals::intersection(out.E[i], alt, sharpened)) {
      throw std::runtime_error(std::string(label) +
                               ": empty defect intersection (bug)");
    }
    out.E[i] = sharpened;
  }

  // Exact rows.
  out.impose_exact_row(coord, value, Ival(0));
  out.impose_exact_row(kParamRow, g.u_center, Ival(1));

  // Independent covering audit through the latest return.
  audit_tube(g, pair23, bound_double(return_time.rightBound()),
             launch_window, order, tolerance, family, label);

  print_graph(label, out);
  return out;
}

// ---------------------------------------------------------------------
// Algebraic chart-switch graph step (same theorems, algebraic map).

ParamGraph switch_leg(const ParamGraph& g, int which, int mode,
                      const Family& family, bool target_pair23,
                      const char* label) {
  Map f1 = which == 0 ? make_pair13_to_pair23_map()
           : which == 1 ? make_pair23_to_pair13_map()
                        : make_pair13_to_pair23_map_form_b();
  ParamGraph out = g;
  const Vector hull = g.hull();
  const Vector fx = f1(g.x);
  out.x = mid_vector(fx);

  if (mode == 1) {
    const Matrix df = f1.derivative(hull);
    const Vector dfT = df * g.T;
    const Vector dfQ = df * g.Q;
    const Vector dfE = df * g.E;
    for (int i = 0; i < kDim; ++i) {
      out.T[i] = dfT[i];
      out.Q[i] = dfQ[i];
      out.E[i] = (fx[i] - out.x[i]) + dfE[i];
    }
  } else {
    Map f2 = which == 0 ? make_pair13_to_pair23_map(2)
             : which == 1 ? make_pair23_to_pair13_map(2)
                          : make_pair13_to_pair23_map_form_b(2);
    Matrix df_hull(kDim, kDim);
    Hessian h_hull(kDim, kDim);
    f2(hull, df_hull, h_hull);
    Matrix dfx(kDim, kDim);
    f1(g.x, dfx);
    const bool deriv_storage = g_map_hessian_is_derivative;
    const Vector dfxT = dfx * g.T;
    const Vector dfxQ = dfx * g.Q;
    const Vector dfxE = dfx * g.E;
    const Vector qTT = hess_quad(h_hull, g.T, deriv_storage);
    const Vector qEE = hess_quad(h_hull, g.E, deriv_storage);
    const Vector qQQ = hess_quad(h_hull, g.Q, deriv_storage);
    const Vector cTE = hess_cross(h_hull, g.T, g.E, deriv_storage);
    const Vector cQE = hess_cross(h_hull, g.Q, g.E, deriv_storage);
    const Vector cTQ = hess_cross(h_hull, g.T, g.Q, deriv_storage);
    const Ival d3 = g.delta3(), d4 = g.delta4();
    for (int i = 0; i < kDim; ++i) {
      out.T[i] = dfxT[i] + cTE[i];
      out.Q[i] = dfxQ[i] + qTT[i] + cQE[i];
      out.E[i] = (fx[i] - out.x[i]) + dfxE[i] + qEE[i] +
                 cTQ[i] * d3 + qQQ[i] * d4;
    }
  }
  out.impose_exact_row(kParamRow, g.u_center, Ival(1));

  // Post-switch validation: separations positive on the switched hull.
  const Vector switched = out.hull();
  const DirectLcScalars sc = target_pair23
                                 ? evaluate_pair23_lc(switched, family)
                                 : evaluate_direct_lc(switched, family);
  if (!(sc.selected_radius.leftBound() > 0) ||
      !(sc.r12_squared.leftBound() > 0) ||
      !(sc.r23_squared.leftBound() > 0)) {
    throw std::runtime_error(std::string(label) +
                             ": switch lost separation");
  }
  print_graph(label, out);
  return out;
}
// ---------------------------------------------------------------------
// Startup self-tests.

// Settle the algebraic-Map Hessian storage convention on a quadratic
// map whose second derivatives are known exactly.
void selftest_map_hessian() {
  Map m("var:a,b;fun:a^2+3*a*b,b^2;", 2);
  Vector v(2);
  v[0] = Ival(0);
  v[1] = Ival(0);
  capd::MpIMatrix df(2, 2);
  capd::diffAlgebra::Hessian<Ival, 0, 0> h(2, 2);
  m(v, df, h);
  const double h00 = bound_double(h(0, 0, 0).rightBound());
  if (std::abs(h00 - 1.0) < 0.25) {
    g_map_hessian_is_derivative = false;  // stores Taylor coefficients
  } else if (std::abs(h00 - 2.0) < 0.25) {
    g_map_hessian_is_derivative = true;   // stores second derivatives
  } else {
    throw std::runtime_error("map hessian selftest: unexpected h(0,0,0)");
  }
  std::cout << "SELFTEST map_hessian_storage="
            << (g_map_hessian_is_derivative ? "derivative" : "taylor")
            << "\n" << std::flush;
  // Containment check of the PG2 switch formulas on this toy map:
  // f(a,b) = (a^2+3ab, b^2) at x=(1,2), h=(0.3 d + e) with d in [-1,1],
  // e in [-0.01,0.01]^2: verify f(x+h) for sampled points lies in the
  // updated representation.
  ParamGraph g;
  g.x = Vector(kDim);
  g.T = Vector(kDim);
  g.Q = Vector(kDim);
  g.E = Vector(kDim);
  // (toy check is 2-dimensional; done inline without ParamGraph)
  const double xs[2] = {1.0, 2.0};
  const double ts[2] = {0.3, -0.2};
  const double r = 0.5, ew = 0.01;
  Vector hull2(2);
  for (int i = 0; i < 2; ++i)
    hull2[i] = Ival(xs[i]) + Ival(ts[i]) * Ival(-r, r) + Ival(-ew, ew);
  Matrix df_hull(2, 2);
  capd::diffAlgebra::Hessian<Ival, 0, 0> h_hull(2, 2);
  m(hull2, df_hull, h_hull);
  Vector xv(2);
  xv[0] = Ival(xs[0]);
  xv[1] = Ival(xs[1]);
  Matrix dfx(2, 2);
  Map m1("var:a,b;fun:a^2+3*a*b,b^2;", 1);
  const Vector fx = m1(xv, dfx);
  // representation update (PG2, 2-dim version)
  auto quad2 = [&](const Vector& a) {
    Vector out(2);
    for (int k = 0; k < 2; ++k) {
      Ival s(0);
      for (int i = 0; i < 2; ++i)
        for (int j = i; j < 2; ++j) {
          Ival c = h_hull(k, i, j);
          if (g_map_hessian_is_derivative && i == j) c = c / Ival(2);
          s += c * a[i] * a[j];
        }
      out[k] = s;
    }
    return out;
  };
  Vector tvec(2), evec(2);
  tvec[0] = Ival(ts[0]);
  tvec[1] = Ival(ts[1]);
  evec[0] = Ival(-ew, ew);
  evec[1] = Ival(-ew, ew);
  const Vector qTT = quad2(tvec);
  const Vector qEE = quad2(evec);
  Vector cTE(2);
  for (int k = 0; k < 2; ++k) {
    Ival s(0);
    for (int i = 0; i < 2; ++i)
      for (int j = i; j < 2; ++j) {
        Ival c = h_hull(k, i, j);
        if (g_map_hessian_is_derivative && i == j) c = c / Ival(2);
        s += c * (tvec[i] * evec[j] + evec[i] * tvec[j]);
      }
    cTE[k] = s;
  }
  const Vector dfxT = dfx * tvec;
  const Vector dfxE = dfx * evec;
  // check sampled fibers
  for (double dd = -r; dd <= r; dd += r / 4) {
    for (double ee = -ew; ee <= ew; ee += ew) {
      double a = xs[0] + ts[0] * dd + ee;
      double b = xs[1] + ts[1] * dd + ee;
      double f0 = a * a + 3 * a * b, f1 = b * b;
      for (int k = 0; k < 2; ++k) {
        const Ival rep = fx[k] + (dfxT[k] + cTE[k]) * Ival(dd) +
                         (qTT[k]) * Ival(dd * dd) + dfxE[k] + qEE[k];
        const double val = k == 0 ? f0 : f1;
        // Boundary fibers can equal the enclosure bound exactly in real
        // arithmetic; allow double-rounding slack in this harness check.
        const double slack = 1e-12;
        if (!(bound_double(rep.leftBound()) - slack <= val &&
              val <= bound_double(rep.rightBound()) + slack)) {
          throw std::runtime_error("PG2 toy containment selftest FAILED");
        }
      }
    }
  }
  std::cout << "SELFTEST pg2_toy_containment=PASS\n" << std::flush;
}

// ---------------------------------------------------------------------
// Terminal certificate margins on a hull (phase-robust, eta = 4).

bool terminal_margins(const Vector& hull, const char* label) {
  const Ival eta = Ival(4);
  const Ival u = hull[10];
  const Ival one(1);
  const Ival qden = one + u * u;
  const Ival mass_a = (one - u * u) / qden;
  const Ival pair_m = (one + u) * (one + u) / qden;
  const Ival total_m = Ival(2) * (one + u) / qden;
  const Ival h = hull[4];
  const Ival gx = hull[5], gy = hull[6], px = hull[7], py = hull[8];
  const Ival rho_sq = gx * gx + gy * gy;
  if (!(rho_sq.leftBound() > 0)) return false;
  const Ival rho = sqrt(rho_sq);
  const Ival radius = pair_m / eta;
  const Ival d = rho - radius;
  const Ival rhodot = (gx * px + gy * py) / rho;
  Ival e_rho(-1), v_inf(0), delta_term(0), margin(-1);
  bool ok = d.leftBound() > 0 && rhodot.leftBound() > 0;
  if (ok) {
    e_rho = rhodot * rhodot / Ival(2) - total_m / d;
    ok = e_rho.leftBound() > 0;
  }
  if (ok) {
    v_inf = sqrt(Ival(2) * e_rho);
    delta_term = mass_a * sqrt(Ival(2) * pair_m * radius) / (v_inf * d * d);
    margin = -eta - h - delta_term;
    ok = margin.leftBound() > 0;
  }
  std::cout << "PGRAPH_TERMINAL " << label
            << " inf_d=" << bound_double(d.leftBound())
            << " inf_rhodot=" << bound_double(rhodot.leftBound())
            << " inf_Erho=" << bound_double(e_rho.leftBound())
            << " sup_h=" << bound_double(h.rightBound())
            << " inf_margin=" << bound_double(margin.leftBound())
            << (ok ? " PASS" : " FAIL") << "\n" << std::flush;
  return ok;
}

// ---------------------------------------------------------------------
// Launch graph (exact tied launch; PG1-style tangent over the range,
// which is exact by the mean value theorem applied to the algebraic
// launch map; E = 0).

ParamGraph launch_graph(const Ival& u_range) {
  const Ival u_center =
      (Ival(u_range.leftBound()) + Ival(u_range.rightBound())) / 2;
  Map launch_map = make_direct_lc_initial_graph_field();
  Vector center_input(kDim), range_input(kDim);
  for (int i = 0; i < kDim; ++i) {
    center_input[i] = Ival(0);
    range_input[i] = Ival(0);
  }
  center_input[kParamRow] = u_center;
  range_input[kParamRow] = u_range;
  ParamGraph g;
  g.x = launch_map(center_input);
  const Matrix launch_derivative = launch_map.derivative(range_input);
  g.T = Vector(kDim);
  g.Q = Vector(kDim);
  g.E = Vector(kDim);
  for (int i = 0; i < kDim; ++i) {
    g.T[i] = launch_derivative[i][kParamRow];
    g.Q[i] = Ival(0);
    g.E[i] = Ival(0);
  }
  g.u_center = u_center;
  g.radius = (Ival(u_range.rightBound()) - Ival(u_range.leftBound())) / 2;
  g.impose_exact_row(kParamRow, u_center, Ival(1));
  return g;
}

// ---------------------------------------------------------------------
// Itinerary driver.

int run_parameter_graph(const Ival& u_range, int mode, int order,
                        double tolerance) {
  const Family family = make_family(u_range);
  std::cout << std::setprecision(17);
  ParamGraph g = launch_graph(u_range);
  const auto MP = capd::poincare::MinusPlus;
  const auto PM = capd::poincare::PlusMinus;

  struct TimeLeg { long num, den; bool pair23; };
  auto tp_leg = [&](const TimeLeg& leg, bool launch_win) {
    const Ival value = Ival(leg.num) / Ival(leg.den);
    const std::string label =
        "t=" + std::to_string(leg.num) + "/" + std::to_string(leg.den);
    g = poincare_leg(g, 9, value, MP, leg.pair23, mode, order, tolerance,
                     launch_win, family, label.c_str());
  };

  // Stage 1: launch -> Form-B switch at tp = 7/2.
  const TimeLeg stage1a[] = {{2, 5, false}, {3, 5, false}, {7, 10, false},
                             {4, 5, false}, {9, 10, false}, {1, 1, false}};
  bool first = true;
  for (const TimeLeg& leg : stage1a) { tp_leg(leg, first); first = false; }
  g = switch_leg(g, 0, mode, family, true, "S1_formA_13to23");
  const TimeLeg stage1b[] = {{21, 20, true}, {11, 10, true}, {6, 5, true},
                             {13, 10, true}, {27, 20, true}, {7, 5, true},
                             {3, 2, true},  {8, 5, true},  {33, 20, true},
                             {17, 10, true}, {7, 4, true}};
  for (const TimeLeg& leg : stage1b) tp_leg(leg, false);
  g = switch_leg(g, 1, mode, family, false, "S2_formA_23to13");
  const TimeLeg stage1c[] = {{9, 5, false},  {19, 10, false}, {2, 1, false},
                             {21, 10, false}, {11, 5, false}, {23, 10, false},
                             {12, 5, false}, {5, 2, false},  {13, 5, false},
                             {27, 10, false}, {14, 5, false}, {29, 10, false},
                             {3, 1, false},  {31, 10, false}, {16, 5, false},
                             {33, 10, false}, {17, 5, false}, {69, 20, false},
                             {7, 2, false}};
  for (const TimeLeg& leg : stage1c) tp_leg(leg, false);
  g = switch_leg(g, 2, mode, family, true, "S3_formB_13to23");
  std::cout << "PGRAPH_STAGE1_DONE\n" << std::flush;

  // Benchmark: post-Form-B geometric section ladder (pair-23 chart,
  // section coordinate wr = state coordinate 0).
  struct WrLeg { long num, den; bool minus_plus; };
  const WrLeg ladder[] = {
      {-3, 20, true}, {-1, 10, true}, {-1, 20, true}, {0, 1, true},
      {1, 20, true},  {1, 10, true},  {3, 20, true},
      {3, 20, false}, {1, 10, false}, {1, 20, false}, {0, 1, false},
      {-1, 20, false}, {-1, 10, false}, {-3, 20, false},
      {-3, 20, true}, {-1, 10, true}, {-1, 20, true}, {0, 1, true},
      {1, 20, true},  {1, 10, true},  {3, 20, true}};
  int index = 0;
  for (const WrLeg& leg : ladder) {
    ++index;
    const Ival value = Ival(leg.num) / Ival(leg.den);
    const std::string label = "wr" + std::to_string(index) + "=" +
                              std::to_string(leg.num) + "/" +
                              std::to_string(leg.den) +
                              (leg.minus_plus ? "MP" : "PM");
    g = poincare_leg(g, 0, value, leg.minus_plus ? MP : PM, true, mode,
                     order, tolerance, false, family, label.c_str());
  }
  std::cout << "PGRAPH_LADDER_DONE\n" << std::flush;

  // Terminal, variant 1: per-fiber times on the final geometric section.
  const bool pass_geometric = terminal_margins(g.hull(), "geometric_section");

  // Terminal, variant 2: common fixed-time section tp = 77/20.
  bool pass_fixed = false;
  try {
    g = poincare_leg(g, 9, Ival(77) / Ival(20), MP, true, mode, order,
                     tolerance, false, family, "t=77/20");
    pass_fixed = terminal_margins(g.hull(), "fixed_time_77_20");
  } catch (const std::exception& error) {
    std::cout << "PGRAPH_FIXED_TIME_FAILED: " << error.what() << "\n";
  }

  if (pass_geometric || pass_fixed) {
    std::cout << "PGRAPH_BENCHMARK_PASS mode=" << mode << " width="
              << width_of(u_range) << " geometric="
              << (pass_geometric ? "PASS" : "fail") << " fixed="
              << (pass_fixed ? "PASS" : "fail") << "\n";
    return 0;
  }
  std::cout << "PGRAPH_BENCHMARK_FAIL mode=" << mode << " width="
            << width_of(u_range) << "\n";
  return 1;
}

}  // namespace

int main(int argc, char** argv) {
  if (argc < 6) {
    std::cerr << "usage: parameter_graph_capd MODE P Q P2 Q2"
                 " [PREC TOL ORDER]\n";
    return 2;
  }
  const int mode = std::atoi(argv[1]);
  const long p = std::atol(argv[2]);
  const long q = std::atol(argv[3]);
  const long p2 = std::atol(argv[4]);
  const long q2 = std::atol(argv[5]);
  const int precision = argc > 6 ? std::atoi(argv[6]) : 160;
  const double tolerance = argc > 7 ? std::atof(argv[7]) : 1e-24;
  const int order = argc > 8 ? std::atoi(argv[8]) : 32;
  capd::MpFloat::setDefaultPrecision(precision);
  try {
    std::cout << "PGRAPH_PARAMS mode=" << mode << " precision_bits="
              << precision << " tolerance=" << tolerance << " order="
              << order << " driver=parameter_graph_capd/2026-08-25\n"
              << std::flush;
    selftest_map_hessian();
    const Ival lower = Ival(p) / Ival(q);
    const Ival upper = Ival(p2) / Ival(q2);
    const Ival u_range = Ival(lower.leftBound(), upper.rightBound());
    if (!(u_range.leftBound() < u_range.rightBound()) ||
        !(u_range.leftBound() > 0) || !(u_range.rightBound() < 1)) {
      std::cerr << "invalid parameter interval\n";
      return 2;
    }
    return run_parameter_graph(u_range, mode, order, tolerance);
  } catch (const std::exception& error) {
    std::cout << "PGRAPH_FAIL(exception:" << error.what() << ")\n";
    return 1;
  }
}
