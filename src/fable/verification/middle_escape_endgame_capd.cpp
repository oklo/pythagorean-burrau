// Rigorous middle-interval endgame certificate: from the tied launch through
// a terminal binary--escaper certificate after physical time 4.3, for a real
// parameter interval near u = 0.29.  The default C0 pipeline evaluates the
// terminal certificate fiberwise on the first passing step; the retained
// experimental C1 pipeline uses a fixed physical-time section at 9/2.
//
// Mathematical basis:
//   docs/FABLE_EVENT_REDUCTION.md   (Theorem C covering certificate)
//   docs/ESCAPE_CRITERIA.md         (terminal binary--escaper theorem)
//   docs/FABLE_MIDDLE_ESCAPE.md     (pair-{2,3} chart form (T) and the
//                                    phase-robust corollary)
//   docs/MIDDLE_FIRST_MAXIMUM_INTERVAL.md (committed prefix machinery)
//
// The correlated mean-value graph machinery (Family, LC fields, chart
// switch, PhaseRunner, DirectCorrelatedGraph, C1 Poincare projection) is
// copied verbatim from the committed
// src/fable/verification/burrau_lc_certificate_capd.cpp; that file is the
// primary worker's and is not modified.  New in this file:
//
//   * make_pair23_to_pair13_map(): exact chart switch back to the
//     pair-{1,3} chart (Form A lift, valid where g13_x > 0, as holds at the
//     default tp >= 7/4 switch);
//   * make_pair13_to_pair23_map_form_b(): the Form-B variant of the
//     committed switch (w_i = sqrt((|g|-g_x)/2)), required near tp = 7/2
//     where g23 lies near the negative real axis and Form A degenerates;
//   * project_graph(): the committed C1 Poincare projection with a
//     STRENGTHENED per-step audit.  Every accepted-step enclosure must
//     satisfy the full Theorem C brake-exclusion disjunction
//         J != 0  or  K > 0  or  U > U0  or  (z, P) excludes 0,
//     except inside a post-maximum window where U < 2 U0 is verified
//     instead: there ddot I < 0 makes J strictly decreasing from its exact
//     zero on the section, so no other zero of J (hence no brake) exists in
//     the window.  Collision separations must be positive on every step.
//     A leg that cannot be covered aborts the whole run (fail closed).
//   * an itinerary that continues past the committed first maximum:
//     switch back to pair-{1,3} after tp = 7/4, traverse the second minimum
//     (deep {1,3} passage near t = 1.92), second maximum, third minimum
//     (t = 2.925), third maximum, fourth minimum (the exchange scattering
//     near t = 3.469 where r23 also dips to ~0.03), switch to pair-{2,3}
//     with Form B near tp = 7/2, and project to the time section tp = 9/2;
//   * the phase-robust terminal check evaluated on the graph hull at
//     tp = 9/2 (eta = 4, binary {2,3}, escaper 1), using only the
//     transported h and the outer variables G, P per the corollary, plus a
//     dump of the box in the stdin format of middle_escape_terminal_capd
//     for independent re-verification.
//
// A default C0 PASS therefore proves, for EVERY real u in the input interval:
// the classical solution is collision-free from launch through that fiber's
// terminal certificate state, every intervening collision-free time is
// covered by a verified brake-exclusion enclosure, and the terminal state
// satisfies the escape-or-inner-collision theorem.  By Theorem C and its
// fiberwise-cover corollary no second labelled brake exists at any
// collision-free time, i.e. the tied solution is nonperiodic for every real
// parameter in the interval.
//
// Usage:
//   middle_escape_endgame_capd P Q P2 Q2 [PREC TOL ORDER]
// e.g.  middle_escape_endgame_capd 29 100 29001 100000 160 1e-24 32
// The committed first-maximum theorem split [29/100, 14501/50000] at
// 29001/100000; run each subtile separately.
//
// Dependency pin: CAPD 6.1.0, commit
// 731079217a9254ea2948d742df2b170895effe7f, MP build (compile with
// -DFABLE_MP flags via scripts/fable_run_capd_middle_endgame.sh).

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "capd/dynsys/DynSysMap.h"
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
typedef capd::MpC2Rect2Set C2Set;
typedef capd::MpIHessian Hessian;
typedef capd::MpIC2OdeSolver C2Solver;
typedef capd::MpICoordinateSection CoordinateSection;
typedef capd::MpIPoincareMap PoincareMap;
typedef capd::MpIC2PoincareMap C2PoincareMap;

double bound_double(const capd::MpFloat& x) { return toDouble(x); }
double to_double(const Ival& x) { return bound_double(x.rightBound()); }

Ival square_interval(const Ival& value) {
  return capd::intervals::sqr(value);
}

// CAPD Hessian objects store factorial-normalized homogeneous Taylor
// coefficients: H(i,j,j)=D_jj/2 and H(i,j,k)=D_jk for j<k.  Consequently
// this is Q_H(v)=D^2[v,v]/2, with each unordered pair evaluated once.
Vector homogeneous_quadratic(const Hessian& coefficients,
                             const Vector& vector) {
  const int domain = vector.dimension();
  const int image = coefficients.imageDimension();
  Vector result(image);
  for (int i = 0; i < image; ++i) {
    for (int j = 0; j < domain; ++j) {
      result[i] += coefficients(i, j, j) * square_interval(vector[j]);
      for (int k = j + 1; k < domain; ++k) {
        result[i] += coefficients(i, j, k) * vector[j] * vector[k];
      }
    }
  }
  return result;
}

// Polarization C_H(v,w)=Q_H(v+w)-Q_H(v)-Q_H(w)=D^2[v,w].
Vector polarized_quadratic(const Hessian& coefficients,
                           const Vector& left, const Vector& right) {
  const int domain = left.dimension();
  const int image = coefficients.imageDimension();
  Vector result(image);
  for (int i = 0; i < image; ++i) {
    for (int j = 0; j < domain; ++j) {
      result[i] += Ival(2) * coefficients(i, j, j) * left[j] * right[j];
      for (int k = j + 1; k < domain; ++k) {
        result[i] += coefficients(i, j, k) *
                     (left[j] * right[k] + right[j] * left[k]);
      }
    }
  }
  return result;
}

// Select point interval coefficients and move the discarded interval width,
// multiplied by the complete monomial range, into an additive spill.
Vector midpoint_coefficients(const Vector& raw, const Ival& monomial,
                             Vector& spill) {
  const int dimension = raw.dimension();
  Vector point(dimension);
  spill = Vector(dimension);
  for (int i = 0; i < dimension; ++i) {
    point[i] = raw[i].mid();
    spill[i] = (raw[i] - point[i]) * monomial;
  }
  return point;
}

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
Map make_direct_lc_field() {
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
             w2 + "*" + gddy + "," + w2 + ",0," + jd_sigma + ";");
}

// Direct Levi--Civita field for selected pair {2,3}, with
// g=q3-q2 and complement G=q1-C23.  The state layout is unchanged.
Map make_pair23_lc_field() {
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
             w2 + "*" + gddy + "," + w2 + ",0," + jd_sigma + ";");
}

Map make_pair13_to_pair23_map() {
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
int widest_component(const Vector& s, int n) {
  int widest = 0;
  double width = -1;
  for (int i = 0; i < n; ++i) {
    const double candidate =
        bound_double(s[i].rightBound() - s[i].leftBound());
    if (candidate > width) {
      widest = i;
      width = candidate;
    }
  }
  return widest;
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

// Replace an interval tangent by a point tangent and transfer the discarded
// width times the complete parameter deviation into an additive defect.
// This is an exact Lohner-style split:
//   T_interval*delta subset T_mid*delta + tangent_spill.
Vector split_graph_tangent(const Vector& raw_tangent,
                           const Ival& deviation,
                           Vector& tangent_spill) {
  const int dimension = raw_tangent.dimension();
  if (std::getenv("FABLE_ENDGAME_GRAPH_TANGENT_SPLIT") == nullptr) {
    tangent_spill = Vector(dimension);
    return raw_tangent;
  }
  Vector point_tangent(dimension);
  tangent_spill = Vector(dimension);
  for (int i = 0; i < dimension; ++i) {
    point_tangent[i] =
        (Ival(raw_tangent[i].leftBound()) +
         Ival(raw_tangent[i].rightBound())) /
        Ival(2);
    tangent_spill[i] =
        (raw_tangent[i] - point_tangent[i]) * deviation;
  }
  return point_tangent;
}

struct DirectCorrelatedGraph {
  Vector anchor;
  Vector tangent;
  // Additive enclosure of the nonlinear/numerical graph defect.  Keeping it
  // separate prevents a previous section's anchor uncertainty from being
  // propagated as a fresh nonlinear state box at the next return.
  Vector defect;
  Ival u_range;
  Ival u_center;
  // Optional second-order coefficient in
  //   X(delta) subset anchor + tangent*delta + quadratic*delta^2 + defect.
  // It is active only when quadratic_mode is true, so the committed C1 path
  // remains bit-for-bit represented by the first five fields above.
  Vector quadratic;
  bool quadratic_mode = false;

  Set c0_set() const {
    const int dimension = anchor.dimension();
    Vector x(dimension), r0(dimension), r(dimension);
    Matrix c(dimension, dimension), b(dimension, dimension);
    for (int row = 0; row < dimension; ++row) {
      const Ival center =
          (Ival(anchor[row].leftBound()) + Ival(anchor[row].rightBound())) /
          2;
      x[row] = center;
      r[row] = defect[row] + (anchor[row] - center);
      if (quadratic_mode) {
        r[row] += quadratic[row] *
                  square_interval(u_range - u_center);
      }
      r[row] = capd::intervals::intervalHull(r[row], Ival(0));
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
      r[row] = defect[row] + (anchor[row] - center);
      if (quadratic_mode) {
        r[row] += quadratic[row] *
                  square_interval(u_range - u_center);
      }
      r[row] = capd::intervals::intervalHull(r[row], Ival(0));
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

  C2Set c2_set() const {
    const int dimension = anchor.dimension();
    Vector x(dimension), r0(dimension), r(dimension);
    Matrix c(dimension, dimension), b(dimension, dimension);
    const Ival deviation = u_range - u_center;
    const Ival deviation_squared = square_interval(deviation);
    for (int row = 0; row < dimension; ++row) {
      const Ival center = anchor[row].mid();
      x[row] = center;
      r[row] = defect[row] + (anchor[row] - center);
      if (quadratic_mode) {
        r[row] += quadratic[row] * deviation_squared;
      }
      r[row] = capd::intervals::intervalHull(r[row], Ival(0));
      r0[row] = Ival(0);
      for (int column = 0; column < dimension; ++column) {
        c[row][column] = Ival(row == column ? 1 : 0);
        b[row][column] = Ival(row == column ? 1 : 0);
      }
      c[row][0] = tangent[row];
    }
    r0[0] = deviation;
    return C2Set(x, c, r0, b, r, Ival(0));
  }

  // C2 set carrying only the formal one-parameter jet of the point
  // polynomial gamma(delta)=anchor+tangent*delta+quadratic*delta^2.
  // The C0 part contains the complete graph including the additive defect;
  // the custom C1/C2 initial data describe gamma.  The solver mask used by
  // project_graph_c2 retains all first derivatives and only Hessian (10,10).
  C2Set directional_c2_set() const {
    if (!quadratic_mode) {
      throw std::runtime_error("directional C2 set requested for C1 graph");
    }
    const int dimension = anchor.dimension();
    const Ival deviation = u_range - u_center;
    const Ival deviation_squared = square_interval(deviation);
    Vector x(dimension), r0(dimension), r(dimension);
    Matrix c(dimension, dimension), b(dimension, dimension);
    Matrix initial_derivative = Matrix::Identity(dimension);
    Hessian initial_quadratic(dimension, dimension);
    constexpr int parameter_coordinate = 10;
    for (int row = 0; row < dimension; ++row) {
      x[row] = anchor[row].mid();
      r[row] = defect[row] + (anchor[row] - x[row]) +
               quadratic[row] * deviation_squared;
      r[row] = capd::intervals::intervalHull(r[row], Ival(0));
      r0[row] = Ival(0);
      for (int column = 0; column < dimension; ++column) {
        c[row][column] = Ival(row == column ? 1 : 0);
        b[row][column] = Ival(row == column ? 1 : 0);
      }
      c[row][0] = tangent[row];
      initial_derivative[row][parameter_coordinate] =
          tangent[row] + Ival(2) * quadratic[row] * deviation;
      initial_quadratic(row, parameter_coordinate,
                        parameter_coordinate) = quadratic[row];
    }
    r0[0] = deviation;
    C2Set::C0BaseSet c0(x, c, r0, b, r);
    C2Set::C1BaseSet c1(initial_derivative);
    return C2Set(c0, c1, initial_quadratic, Ival(0));
  }

  // The directional C2 set replaces column 10 of the identity by
  // gamma'(delta).  Because the transported parameter coordinate is exactly
  // gamma'_10=1, the frame and its inverse are explicit rank-one matrices.
  Matrix directional_frame() const {
    const int dimension = anchor.dimension();
    constexpr int parameter_coordinate = 10;
    const Ival deviation = u_range - u_center;
    Matrix frame = Matrix::Identity(dimension);
    for (int row = 0; row < dimension; ++row) {
      frame[row][parameter_coordinate] =
          tangent[row] + Ival(2) * quadratic[row] * deviation;
    }
    return frame;
  }

  Matrix directional_frame_inverse() const {
    const int dimension = anchor.dimension();
    constexpr int parameter_coordinate = 10;
    const Matrix frame = directional_frame();
    if (!(frame[parameter_coordinate][parameter_coordinate].leftBound() ==
              Ival(1).leftBound()) ||
        !(frame[parameter_coordinate][parameter_coordinate].rightBound() ==
              Ival(1).rightBound())) {
      throw std::runtime_error("parameter-jet pivot is not exactly one");
    }
    Matrix inverse = Matrix::Identity(dimension);
    for (int row = 0; row < dimension; ++row) {
      if (row != parameter_coordinate) {
        inverse[row][parameter_coordinate] = -frame[row][parameter_coordinate];
      }
    }
    return inverse;
  }
};

void set_directional_c2_mask(C2Solver& solver, int dimension,
                             int parameter_coordinate) {
  using Multiindex = capd::vectalg::Multiindex;
  std::vector<Multiindex> mask;
  mask.reserve(dimension + 1);
  for (int column = 0; column < dimension; ++column) {
    Multiindex first(dimension);
    first[column] = 1;
    mask.push_back(first);
  }
  Multiindex curvature(dimension);
  curvature[parameter_coordinate] = 2;
  mask.push_back(curvature);
  solver.setMask(mask.begin(), mask.end());
}

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
  const Vector anchor_image = launch_map(center_input);
  Vector anchor(12), defect(12);
  for (int row = 0; row < 12; ++row) {
    anchor[row] =
        (Ival(anchor_image[row].leftBound()) +
         Ival(anchor_image[row].rightBound())) /
        Ival(2);
    defect[row] = anchor_image[row] - anchor[row];
  }
  const Matrix launch_derivative = launch_map.derivative(range_input);
  Vector raw_tangent(12);
  for (int row = 0; row < 12; ++row) {
    raw_tangent[row] = launch_derivative[row][10];
  }
  // The construction field freezes ww; the actual launch graph retains it.
  anchor[10] = u_center;
  defect[10] = Ival(0);
  raw_tangent[10] = Ival(1);
  Vector tangent_spill(12);
  Vector tangent = split_graph_tangent(
      raw_tangent, u_range - u_center, tangent_spill);
  for (int row = 0; row < 12; ++row) {
    defect[row] += tangent_spill[row];
    defect[row] =
        capd::intervals::intervalHull(defect[row], Ival(0));
  }
  return {anchor, tangent, defect, u_range, u_center};
}

DirectCorrelatedGraph make_quadratic_launch_graph(const Ival& u_range) {
  const Ival u_center = u_range.mid();
  const Ival deviation = u_range - u_center;
  const Ival deviation_squared = square_interval(deviation);
  Vector center_input(12), range_input(12);
  for (int i = 0; i < 12; ++i) {
    center_input[i] = Ival(0);
    range_input[i] = Ival(0);
  }
  center_input[10] = u_center;
  range_input[10] = u_range;
  Map launch_map = make_direct_lc_initial_graph_field();
  launch_map.setDegree(2);
  Matrix anchor_derivative(12, 12), range_derivative(12, 12);
  Hessian anchor_quadratic(12, 12), range_quadratic(12, 12);
  const Vector anchor_image =
      launch_map(center_input, anchor_derivative, anchor_quadratic);
  const Vector direct_image =
      launch_map(range_input, range_derivative, range_quadratic);

  Vector anchor(12), raw_tangent(12), raw_quadratic(12), defect(12);
  for (int row = 0; row < 12; ++row) {
    anchor[row] = anchor_image[row].mid();
    raw_tangent[row] = anchor_derivative[row][10];
    raw_quadratic[row] = range_quadratic(row, 10, 10);
  }
  // The construction field freezes ww; the actual launch graph retains it
  // as the exact affine parameter coordinate.
  anchor[10] = u_center;
  raw_tangent[10] = Ival(1);
  raw_quadratic[10] = Ival(0);

  Vector tangent_spill(12), quadratic_spill(12);
  const Vector tangent =
      midpoint_coefficients(raw_tangent, deviation, tangent_spill);
  const Vector quadratic = midpoint_coefficients(
      raw_quadratic, deviation_squared, quadratic_spill);
  for (int row = 0; row < 12; ++row) {
    defect[row] = (anchor_image[row] - anchor[row]) + tangent_spill[row] +
                  quadratic_spill[row];
    const Ival direct_defect = direct_image[row] - anchor[row] -
                               tangent[row] * deviation -
                               quadratic[row] * deviation_squared;
    Ival sharpened;
    if (!capd::intervals::intersection(defect[row], direct_defect,
                                        sharpened)) {
      throw std::runtime_error("empty quadratic launch defect");
    }
    defect[row] = capd::intervals::intervalHull(sharpened, Ival(0));
  }
  anchor[10] = u_center;
  defect[10] = Ival(0);
  return {anchor, tangent, defect, u_range, u_center, quadratic, true};
}
// ---- New machinery (this file only; nothing above this line differs from
// ---- the committed source except the header and typedef block). ----

// Exact chart switch pair-{2,3} -> pair-{1,3}, Form A lift (g13_x > 0).
// In the pair-{2,3} chart: g23 = w^2, d13 = q1 - q3 = G + (1/M23 - 1) g23,
// d12 = q1 - q2 = G + g23/M23.  Then g13 = q3 - q1 = -d13,
// G13 = (q2 - q1) - g13/M13 = -d12 - g13/M13, and velocities identically.
Map make_pair23_to_pair13_map(bool fixed_energy_h = false) {
  const std::string qden = "(1+ww^2)";
  const std::string ma = "((1-ww^2)/" + qden + ")";
  const std::string mb = "(2*ww/" + qden + ")";
  const std::string inv_m23 = "(" + qden + "/(1+ww)^2)";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string m13 = "(2/" + qden + ")";
  const std::string old_w2 = "(wr^2+wi^2)";
  const std::string old_gx = "(wr^2-wi^2)";
  const std::string old_gy = "(2*wr*wi)";
  const std::string old_gdx = "(2*(wr*zr-wi*zi)/" + old_w2 + ")";
  const std::string old_gdy = "(2*(wr*zi+wi*zr)/" + old_w2 + ")";
  // d13 = q1 - q3 and its velocity in the pair-{2,3} chart.
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
  const std::string new_h_velocity =
      "((" + gdx + "^2+" + gdy + "^2)/2-" + m13 + "/" + abs_g + ")";
  // d12 = q1 - q2 in the pair-{2,3} chart; G13 = -d12 - g13/M13.
  const std::string d12x = "(cgx+" + inv_m23 + "*" + old_gx + ")";
  const std::string d12y = "(cgy+" + inv_m23 + "*" + old_gy + ")";
  const std::string d12dx = "(cpx+" + inv_m23 + "*" + old_gdx + ")";
  const std::string d12dy = "(cpy+" + inv_m23 + "*" + old_gdy + ")";
  const std::string new_gx = "(-" + d12x + "-" + inv_m13 + "*" + gx + ")";
  const std::string new_gy = "(-" + d12y + "-" + inv_m13 + "*" + gy + ")";
  const std::string new_px = "(-" + d12dx + "-" + inv_m13 + "*" + gdx + ")";
  const std::string new_py = "(-" + d12dy + "-" + inv_m13 + "*" + gdy + ")";
  // On the exact tied energy leaf H=-U0, the target pair energy can be
  // reconstructed without dividing by the target separation |g13|:
  //   H = mu13*h13 + muG*|P13|^2/2 - AB/r12 - B/r23.
  // Here r23=|w23^2|=|w23|^2=old_w2.  This map is intentionally allowed to
  // project spurious off-leaf box points onto the correct energy leaf; every
  // genuine Pythagorean fiber is unchanged.
  const std::string total = "(" + ma + "+" + mb + "+1)";
  const std::string mu13 = "(" + ma + "/(" + ma + "+1))";
  const std::string mu_g13 = "(" + mb + "*(" + ma + "+1)/" + total + ")";
  const std::string ab = "(" + ma + "*" + mb + ")";
  const std::string u0 = "(" + ab + "+1/" + ab + ")";
  const std::string r12 = "sqrt(" + d12x + "^2+" + d12y + "^2)";
  const std::string new_h_energy =
      "((-" + u0 + "-(" + mu_g13 + "/2)*(" + new_px + "^2+" +
      new_py + "^2)+" + ab + "/" + r12 + "+" + mb + "/" +
      old_w2 + ")/" + mu13 + ")";
  const std::string& new_h =
      fixed_energy_h ? new_h_energy : new_h_velocity;
  return Map(std::string(kDirectLcVars) + "fun:" + new_wr + "," +
             new_wi + "," + new_zr + "," + new_zi + "," + new_h +
             "," + new_gx + "," + new_gy + "," + new_px + "," +
             new_py + ",tp,ww,jd;");
}

// The committed pair-{1,3} -> pair-{2,3} switch with the Form B square
// root (w_i = sqrt((|g|-g_x)/2), w_r = g_y/(2 w_i)), valid on g23_x < 0.
// Everything except the two lift lines is identical to the committed map.
Map make_pair13_to_pair23_map_form_b(bool fixed_energy_h = false) {
  const std::string qden = "(1+ww^2)";
  const std::string ma = "((1-ww^2)/" + qden + ")";
  const std::string mb = "(2*ww/" + qden + ")";
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
  const std::string new_wi = "sqrt((" + abs_g + "-" + gx + ")/2)";
  const std::string new_wr = "(" + gy + "/(2*" + new_wi + "))";
  const std::string new_zr =
      "((" + new_wr + "*" + gdx + "+" + new_wi + "*" + gdy + ")/2)";
  const std::string new_zi =
      "((" + new_wr + "*" + gdy + "-" + new_wi + "*" + gdx + ")/2)";
  const std::string new_h_velocity =
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
  // Fixed-energy reconstruction in the target pair-{2,3} chart:
  //   H = mu23*h23 + muG*|P23|^2/2 - AB/r12 - A/r13.
  // The unselected r13 equals old_w2 and r12=|X13|.  No target |g23|
  // denominator occurs.
  const std::string total = "(" + ma + "+" + mb + "+1)";
  const std::string mu23 = "(" + mb + "/(" + mb + "+1))";
  const std::string mu_g23 = "(" + ma + "*(" + mb + "+1)/" + total + ")";
  const std::string ab = "(" + ma + "*" + mb + ")";
  const std::string u0 = "(" + ab + "+1/" + ab + ")";
  const std::string r12 = "sqrt(" + old_xx + "^2+" + old_xy + "^2)";
  const std::string new_h_energy =
      "((-" + u0 + "-(" + mu_g23 + "/2)*(" + new_px + "^2+" +
      new_py + "^2)+" + ab + "/" + r12 + "+" + ma + "/" +
      old_w2 + ")/" + mu23 + ")";
  const std::string& new_h =
      fixed_energy_h ? new_h_energy : new_h_velocity;
  return Map(std::string(kDirectLcVars) + "fun:" + new_wr + "," +
             new_wi + "," + new_zr + "," + new_zi + "," + new_h +
             "," + new_gx + "," + new_gy + "," + new_px + "," +
             new_py + ",tp,ww,jd;");
}

// In-chart projection onto the exact tied energy leaf in pair-{1,3}
// variables.  Every genuine family fiber is fixed because H=-U0(ww);
// spurious off-energy points in the graph enclosure may move.  Unlike a
// velocity reconstruction, this formula has no selected-distance divisor.
Map make_pair13_energy_projection() {
  const std::string qden = "(1+ww^2)";
  const std::string ma = "((1-ww^2)/" + qden + ")";
  const std::string mb = "(2*ww/" + qden + ")";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string gx = "(wr^2-wi^2)";
  const std::string gy = "(2*wr*wi)";
  const std::string d12x = "(cgx+" + inv_m13 + "*" + gx + ")";
  const std::string d12y = "(cgy+" + inv_m13 + "*" + gy + ")";
  const std::string d23x =
      "(cgx+(" + inv_m13 + "-1)*" + gx + ")";
  const std::string d23y =
      "(cgy+(" + inv_m13 + "-1)*" + gy + ")";
  const std::string r12 = "sqrt(" + d12x + "^2+" + d12y + "^2)";
  const std::string r23 = "sqrt(" + d23x + "^2+" + d23y + "^2)";
  const std::string total = "(" + ma + "+" + mb + "+1)";
  const std::string mu13 = "(" + ma + "/(" + ma + "+1))";
  const std::string mu_g13 = "(" + mb + "*(" + ma + "+1)/" + total + ")";
  const std::string ab = "(" + ma + "*" + mb + ")";
  const std::string u0 = "(" + ab + "+1/" + ab + ")";
  const std::string projected_h =
      "((-" + u0 + "-(" + mu_g13 + "/2)*(cpx^2+cpy^2)+" +
      ab + "/" + r12 + "+" + mb + "/" + r23 + ")/" + mu13 + ")";
  return Map(std::string(kDirectLcVars) +
             "fun:wr,wi,zr,zi," + projected_h +
             ",cgx,cgy,cpx,cpy,tp,ww,jd;");
}

// In-chart projection onto the joint tied invariant manifold in pair-{1,3}
// variables.  First remove the spurious total-angular-momentum component of
// the complementary velocity while preserving G.P, then reconstruct h from
// H=-U0(ww), and finally reconstruct jd=dI/dt.  Every genuine tied fiber is
// fixed.  The only additional denominator is |G|^2, checked strictly before
// this map is evaluated.
Map make_pair13_joint_invariant_projection() {
  const std::string qden = "(1+ww^2)";
  const std::string ma = "((1-ww^2)/" + qden + ")";
  const std::string mb = "(2*ww/" + qden + ")";
  const std::string inv_m13 = "(" + qden + "/2)";
  const std::string total = "(" + ma + "+" + mb + "+1)";
  const std::string mu13 = "(" + ma + "/(" + ma + "+1))";
  const std::string mu_g13 = "(" + mb + "*(" + ma + "+1)/" + total + ")";
  const std::string spin = "(wr*zi-wi*zr)";
  const std::string big_g2 = "(cgx^2+cgy^2)";
  const std::string old_cross = "(cgx*cpy-cgy*cpx)";
  const std::string target_cross =
      "(-2*" + mu13 + "*" + spin + "/" + mu_g13 + ")";
  const std::string correction =
      "((" + target_cross + "-" + old_cross + ")/" + big_g2 + ")";
  const std::string projected_px = "(cpx-cgy*" + correction + ")";
  const std::string projected_py = "(cpy+cgx*" + correction + ")";

  const std::string gx = "(wr^2-wi^2)";
  const std::string gy = "(2*wr*wi)";
  const std::string d12x = "(cgx+" + inv_m13 + "*" + gx + ")";
  const std::string d12y = "(cgy+" + inv_m13 + "*" + gy + ")";
  const std::string d23x =
      "(cgx+(" + inv_m13 + "-1)*" + gx + ")";
  const std::string d23y =
      "(cgy+(" + inv_m13 + "-1)*" + gy + ")";
  const std::string r12 = "sqrt(" + d12x + "^2+" + d12y + "^2)";
  const std::string r23 = "sqrt(" + d23x + "^2+" + d23y + "^2)";
  const std::string ab = "(" + ma + "*" + mb + ")";
  const std::string u0 = "(" + ab + "+1/" + ab + ")";
  const std::string projected_h =
      "((-" + u0 + "-(" + mu_g13 + "/2)*(" + projected_px + "^2+" +
      projected_py + "^2)+" + ab + "/" + r12 + "+" + mb + "/" +
      r23 + ")/" + mu13 + ")";
  const std::string projected_jd =
      "(4*" + mu13 + "*(wr*zr+wi*zi)+2*" + mu_g13 + "*(cgx*" +
      projected_px + "+cgy*" + projected_py + "))";
  return Map(std::string(kDirectLcVars) +
             "fun:wr,wi,zr,zi," + projected_h +
             ",cgx,cgy," + projected_px + "," + projected_py +
             ",tp,ww," + projected_jd + ";");
}

DirectCorrelatedGraph transform_graph_c1(const DirectCorrelatedGraph& input,
                                         Map transformation) {
  const Vector domain(input.c0_set());
  const Vector direct_image = transformation(domain);
  const Vector anchor_image = transformation(input.anchor);
  const Matrix derivative = transformation.derivative(domain);
  const Ival deviation = input.u_range - input.u_center;
  const int dimension = input.anchor.dimension();
  const Vector raw_tangent = derivative * input.tangent;
  Vector tangent_spill(dimension);
  Vector output_tangent =
      split_graph_tangent(raw_tangent, deviation, tangent_spill);
  const Vector mapped_defect = derivative * input.defect;
  Vector output_anchor(dimension), output_defect(dimension);
  for (int i = 0; i < dimension; ++i) {
    output_anchor[i] =
        (Ival(anchor_image[i].leftBound()) +
         Ival(anchor_image[i].rightBound())) /
        Ival(2);
    output_defect[i] =
        (anchor_image[i] - output_anchor[i]) +
        mapped_defect[i] + tangent_spill[i];
    const Ival direct_defect =
        direct_image[i] - output_anchor[i] - output_tangent[i] * deviation;
    Ival sharpened;
    if (!capd::intervals::intersection(
            output_defect[i], direct_defect, sharpened)) {
      throw std::runtime_error("empty transformed graph defect");
    }
    output_defect[i] =
        capd::intervals::intervalHull(sharpened, Ival(0));
  }
  // Every chart map copies the conserved parameter coordinate ww exactly.
  output_anchor[10] = input.u_center;
  output_tangent[10] = Ival(1);
  output_defect[10] = Ival(0);
  return {output_anchor, output_tangent, output_defect,
          input.u_range, input.u_center};
}

DirectCorrelatedGraph transform_graph_c2(const DirectCorrelatedGraph& input,
                                         Map transformation) {
  if (!input.quadratic_mode) {
    throw std::runtime_error("C2 transform received a C1 graph");
  }
  transformation.setDegree(2);
  const Vector domain(input.c0_set());
  Matrix domain_derivative(12, 12), anchor_derivative(12, 12);
  Hessian domain_quadratic(12, 12), anchor_quadratic(12, 12);
  const Vector direct_image =
      transformation(domain, domain_derivative, domain_quadratic);
  const Vector anchor_image =
      transformation(input.anchor, anchor_derivative, anchor_quadratic);

  const int dimension = input.anchor.dimension();
  const Ival deviation = input.u_range - input.u_center;
  const Ival deviation_squared = square_interval(deviation);
  const Vector nonlinear_input =
      input.quadratic * deviation_squared + input.defect;
  const Vector linear_input = input.tangent * deviation;
  const Vector raw_tangent = anchor_derivative * input.tangent;
  const Vector raw_quadratic =
      anchor_derivative * input.quadratic +
      homogeneous_quadratic(domain_quadratic, input.tangent);
  const Vector mapped_defect = anchor_derivative * input.defect;
  const Vector cross_defect = polarized_quadratic(
      domain_quadratic, linear_input, nonlinear_input);
  const Vector nonlinear_defect =
      homogeneous_quadratic(domain_quadratic, nonlinear_input);

  Vector tangent_spill(dimension), quadratic_spill(dimension);
  Vector output_tangent =
      midpoint_coefficients(raw_tangent, deviation, tangent_spill);
  Vector output_quadratic = midpoint_coefficients(
      raw_quadratic, deviation_squared, quadratic_spill);
  Vector output_anchor(dimension), output_defect(dimension);
  for (int i = 0; i < dimension; ++i) {
    output_anchor[i] = anchor_image[i].mid();
    output_defect[i] = (anchor_image[i] - output_anchor[i]) +
                       mapped_defect[i] + tangent_spill[i] +
                       quadratic_spill[i] + cross_defect[i] +
                       nonlinear_defect[i];
    const Ival direct_defect = direct_image[i] - output_anchor[i] -
                               output_tangent[i] * deviation -
                               output_quadratic[i] * deviation_squared;
    Ival sharpened;
    if (!capd::intervals::intersection(output_defect[i], direct_defect,
                                        sharpened)) {
      throw std::runtime_error("empty transformed C2 graph defect");
    }
    output_defect[i] =
        capd::intervals::intervalHull(sharpened, Ival(0));
  }
  // Every chart map copies the conserved parameter coordinate ww exactly.
  output_anchor[10] = input.u_center;
  output_tangent[10] = Ival(1);
  output_quadratic[10] = Ival(0);
  output_defect[10] = Ival(0);
  return {output_anchor, output_tangent, output_defect,
          input.u_range, input.u_center, output_quadratic, true};
}

DirectCorrelatedGraph transform_graph(const DirectCorrelatedGraph& input,
                                      Map transformation) {
  return input.quadratic_mode
             ? transform_graph_c2(input, transformation)
             : transform_graph_c1(input, transformation);
}

// Per-leg J-sign / covering bookkeeping.
enum class LegMode {
  kPostMax,   // U < 2U0 window (J strictly decreasing from its section
              // zero), then J < 0 required; window itself is the covering.
  kNegative,  // J < 0 required throughout.
  kPostMin,   // U > 2U0 window (covering via U > U0), then J > 0.
  kPositive,  // J > 0 required throughout.
  kCross,     // event-crossing leg: no J sign requirement.
};

// Complete common-clock tube audit past the latest fiber return.  It is
// deliberately independent of the C1/C2 correlated graph algebra: the C0
// set proves domain containment, collision separation, and Theorem C's
// brake-exclusion covering on every accepted step.
void audit_graph_leg(const DirectCorrelatedGraph& input,
                     const Ival& interval_return, int order,
                     double tolerance, bool pair23_chart, LegMode mode,
                     const char* leg_label) {
  Set audit_set = input.c0_set();
  Map audit_field = pair23_chart ? make_pair23_lc_field()
                                 : make_direct_lc_field();
  PhaseRunner audit(audit_field, order, tolerance);
  const Family audit_family = make_family(input.u_range);
  const Ival two_u0 = 2 * audit_family.u0;
  bool in_post_max_window = mode == LegMode::kPostMax;
  bool in_post_min_window = mode == LegMode::kPostMin;
  const Ival audit_target = Ival(interval_return.rightBound());
  for (int audit_steps = 0;; ++audit_steps) {
    if (audit_steps > 200000) {
      throw std::runtime_error(std::string(leg_label) +
                               ": audit step limit");
    }
    const Vector before(audit_set);
    const DirectLcScalars pre =
        pair23_chart ? evaluate_pair23_lc(before, audit_family)
                     : evaluate_direct_lc(before, audit_family);
    if (!(pre.selected_radius.leftBound() > 0) ||
        !(pre.r12_squared.leftBound() > 0) ||
        !(pre.r23_squared.leftBound() > 0)) {
      throw std::runtime_error(std::string(leg_label) +
                               ": lost pre-step collision separation");
    }
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
    audit.direct_move(audit_set, cap);
    const Vector enclosure = audit_set.getLastEnclosure();
    const DirectLcScalars sc =
        pair23_chart ? evaluate_pair23_lc(enclosure, audit_family)
                     : evaluate_direct_lc(enclosure, audit_family);
    if (!(sc.selected_radius.leftBound() > 0) ||
        !(sc.r12_squared.leftBound() > 0) ||
        !(sc.r23_squared.leftBound() > 0)) {
      throw std::runtime_error(std::string(leg_label) +
                               ": lost collision separation");
    }
    bool covered = false;
    if (in_post_max_window &&
        sc.potential.rightBound() < two_u0.leftBound()) {
      covered = true;
    } else {
      if (in_post_max_window) {
        if (!(sc.i_dot.rightBound() < 0)) {
          throw std::runtime_error(
              std::string(leg_label) +
              ": post-maximum window exit lost J<0");
        }
        in_post_max_window = false;
      }
      covered = !contains_zero(sc.i_dot) || sc.kinetic.leftBound() > 0 ||
                sc.potential.leftBound() > audit_family.u0.rightBound() ||
                direct_lc_residual_excludes_brake(enclosure);
    }
    if (!covered) {
      throw std::runtime_error(std::string(leg_label) +
                               ": uncovered brake-exclusion step");
    }
    switch (mode) {
      case LegMode::kNegative:
        if (!(sc.i_dot.rightBound() < 0)) {
          throw std::runtime_error(std::string(leg_label) +
                                   ": lost prescribed J<0");
        }
        break;
      case LegMode::kPositive:
        if (!(sc.i_dot.leftBound() > 0)) {
          throw std::runtime_error(std::string(leg_label) +
                                   ": lost prescribed J>0");
        }
        break;
      case LegMode::kPostMin:
        if (in_post_min_window) {
          if (!(sc.potential.leftBound() > two_u0.rightBound())) {
            if (!(sc.i_dot.leftBound() > 0)) {
              throw std::runtime_error(
                  std::string(leg_label) +
                  ": post-minimum window exit lost J>0");
            }
            in_post_min_window = false;
          }
        } else if (!(sc.i_dot.leftBound() > 0)) {
          throw std::runtime_error(
              std::string(leg_label) +
              ": lost prescribed J>0 after window");
        }
        break;
      case LegMode::kPostMax:
        if (!in_post_max_window && !(sc.i_dot.rightBound() < 0)) {
          throw std::runtime_error(
              std::string(leg_label) + ": lost J<0 after post-maximum window");
        }
        break;
      case LegMode::kCross:
        break;
    }
    if (audit_set.getCurrentTime().leftBound() >=
        audit_target.rightBound()) {
      break;
    }
  }
}

// C1 Poincare projection of the correlated graph with the strengthened
// covering audit.  Identical in structure to the committed
// project_direct_graph; the audit adds the Theorem C brake-exclusion
// disjunction on every accepted step.
DirectCorrelatedGraph project_graph_c1(
    const DirectCorrelatedGraph& input, int section_coordinate,
    const Ival& section_value,
    capd::poincare::CrossingDirection direction, int order,
    double tolerance, bool pair23_chart, LegMode mode,
    const char* leg_label) {
  Map field = pair23_chart ? make_pair23_lc_field()
                           : make_direct_lc_field();
  CoordinateSection section(12, section_coordinate, section_value);
  Solver interval_solver(field, order);
  interval_solver.setAbsoluteTolerance(tolerance);
  interval_solver.setRelativeTolerance(tolerance);
  if (section_coordinate == 0) {
    const Ival strict_lower = -Ival(2) / Ival(5);
    const Ival strict_upper = -Ival(3) / Ival(10);
    const bool strict_exchange =
        !pair23_chart &&
        !(section_value.rightBound() < strict_lower.leftBound()) &&
        !(section_value.leftBound() > strict_upper.rightBound());
    interval_solver.setMaxStep(strict_exchange ? Ival(1) / Ival(2000)
                                               : Ival(1) / Ival(500));
  }
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
  const Vector raw_tangent = section_derivative * input.tangent;

  audit_graph_leg(input, interval_return, order, tolerance, pair23_chart,
                  mode, leg_label);

  CoordinateSection anchor_section(12, section_coordinate, section_value);
  Solver anchor_solver(field, order);
  anchor_solver.setAbsoluteTolerance(tolerance);
  anchor_solver.setRelativeTolerance(tolerance);
  if (section_coordinate == 0) {
    const Ival strict_lower = -Ival(2) / Ival(5);
    const Ival strict_upper = -Ival(3) / Ival(10);
    const bool strict_exchange =
        !pair23_chart &&
        !(section_value.rightBound() < strict_lower.leftBound()) &&
        !(section_value.leftBound() > strict_upper.rightBound());
    anchor_solver.setMaxStep(strict_exchange ? Ival(1) / Ival(2000)
                                             : Ival(1) / Ival(500));
  }
  PoincareMap anchor_map(anchor_solver, anchor_section, direction);
  anchor_map.setMaxReturnTime(50.0);
  Set anchor_set(input.anchor);
  Ival anchor_return;
  const Vector anchor_image = anchor_map(anchor_set, anchor_return);
  if (!interval_image[section_coordinate].contains(section_value) ||
      !anchor_image[section_coordinate].contains(section_value)) {
    throw std::runtime_error(std::string(leg_label) +
                             ": missed Poincare section");
  }
  const int dimension = input.anchor.dimension();
  const Ival deviation = input.u_range - input.u_center;
  Vector tangent_spill(dimension);
  Vector output_tangent =
      split_graph_tangent(raw_tangent, deviation, tangent_spill);
  const Vector mapped_defect = section_derivative * input.defect;
  Vector output_anchor(dimension), output_defect(dimension);
  for (int i = 0; i < dimension; ++i) {
    output_anchor[i] =
        (Ival(anchor_image[i].leftBound()) +
         Ival(anchor_image[i].rightBound())) /
        Ival(2);
    output_defect[i] =
        (anchor_image[i] - output_anchor[i]) + mapped_defect[i] +
        tangent_spill[i];
    const Ival direct_defect =
        interval_image[i] - output_anchor[i] -
        output_tangent[i] * deviation;
    Ival sharpened;
    if (!capd::intervals::intersection(
            output_defect[i], direct_defect, sharpened)) {
      throw std::runtime_error(std::string(leg_label) +
                               ": empty graph-defect intersection");
    }
    output_defect[i] =
        capd::intervals::intervalHull(sharpened, Ival(0));
  }
  output_anchor[section_coordinate] = section_value;
  output_tangent[section_coordinate] = Ival(0);
  output_defect[section_coordinate] = Ival(0);
  return {output_anchor, output_tangent, output_defect,
          input.u_range, input.u_center};
}

DirectCorrelatedGraph project_graph_c2(
    const DirectCorrelatedGraph& input, int section_coordinate,
    const Ival& section_value,
    capd::poincare::CrossingDirection direction, int order,
    double tolerance, bool pair23_chart, LegMode mode,
    const char* leg_label) {
  if (!input.quadratic_mode) {
    throw std::runtime_error("C2 projection received a C1 graph");
  }
  Map field = pair23_chart ? make_pair23_lc_field()
                           : make_direct_lc_field();

  // Propagate the formal one-variable jet of
  // gamma(delta)=x+T*delta+Q*delta^2.  The mask keeps the complete first
  // derivative matrix and only the quadratic coefficient in formal direction
  // 10, the exact conserved u coordinate.  Its initial C1 frame is the
  // identity with column 10 replaced by gamma'(delta).  Therefore the same
  // pass also encloses DP after multiplication by an explicit frame inverse;
  // no duplicate full-C1 integration is needed.
  constexpr int parameter_coordinate = 10;
  CoordinateSection directional_section(12, section_coordinate,
                                         section_value);
  C2Solver directional_solver(field, order);
  directional_solver.setAbsoluteTolerance(tolerance);
  directional_solver.setRelativeTolerance(tolerance);
  if (section_coordinate == 0) {
    const Ival strict_lower = -Ival(2) / Ival(5);
    const Ival strict_upper = -Ival(3) / Ival(10);
    const bool strict_exchange =
        !pair23_chart &&
        !(section_value.rightBound() < strict_lower.leftBound()) &&
        !(section_value.leftBound() > strict_upper.rightBound());
    directional_solver.setMaxStep(strict_exchange ? Ival(1) / Ival(2000)
                                                  : Ival(1) / Ival(500));
  }
  set_directional_c2_mask(directional_solver, 12, parameter_coordinate);
  C2PoincareMap directional_map(directional_solver, directional_section,
                                direction);
  directional_map.setMaxReturnTime(50.0);
  C2Set directional_set = input.directional_c2_set();
  Matrix directional_flow_derivative(12, 12);
  Matrix directional_section_derivative(12, 12);
  Hessian directional_flow_quadratic(12, 12);
  Hessian directional_section_quadratic(12, 12);
  Ival directional_return;
  const Vector directional_image = directional_map(
      directional_set, directional_flow_derivative,
      directional_flow_quadratic, directional_return);
  directional_map.computeDP(
      directional_image, directional_flow_derivative,
      directional_flow_quadratic, directional_section_derivative,
      directional_section_quadratic, directional_return);

  audit_graph_leg(input, directional_return, order, tolerance, pair23_chart,
                  mode, leg_label);

  CoordinateSection anchor_section(12, section_coordinate, section_value);
  Solver anchor_solver(field, order);
  anchor_solver.setAbsoluteTolerance(tolerance);
  anchor_solver.setRelativeTolerance(tolerance);
  if (section_coordinate == 0) {
    const Ival strict_lower = -Ival(2) / Ival(5);
    const Ival strict_upper = -Ival(3) / Ival(10);
    const bool strict_exchange =
        !pair23_chart &&
        !(section_value.rightBound() < strict_lower.leftBound()) &&
        !(section_value.leftBound() > strict_upper.rightBound());
    anchor_solver.setMaxStep(strict_exchange ? Ival(1) / Ival(2000)
                                             : Ival(1) / Ival(500));
  }
  PoincareMap anchor_map(anchor_solver, anchor_section, direction);
  anchor_map.setMaxReturnTime(50.0);
  C1Set anchor_set(input.anchor);
  Matrix anchor_flow_derivative(12, 12);
  Ival anchor_return;
  const Vector anchor_image =
      anchor_map(anchor_set, anchor_flow_derivative, anchor_return);
  const Matrix anchor_section_derivative =
      anchor_map.computeDP(anchor_image, anchor_flow_derivative,
                           anchor_return);
  if (!directional_image[section_coordinate].contains(section_value) ||
      !anchor_image[section_coordinate].contains(section_value)) {
    throw std::runtime_error(std::string(leg_label) +
                             ": missed C2 Poincare section");
  }

  const int dimension = input.anchor.dimension();
  const Ival deviation = input.u_range - input.u_center;
  const Ival deviation_squared = square_interval(deviation);
  const Vector raw_tangent = anchor_section_derivative * input.tangent;
  Vector raw_quadratic(dimension);
  for (int row = 0; row < dimension; ++row) {
    raw_quadratic[row] = directional_section_quadratic(
        row, parameter_coordinate, parameter_coordinate);
  }
  const Matrix domain_section_derivative =
      directional_section_derivative * input.directional_frame_inverse();
  const Vector mapped_defect = domain_section_derivative * input.defect;

  Vector tangent_spill(dimension), quadratic_spill(dimension);
  Vector output_tangent =
      midpoint_coefficients(raw_tangent, deviation, tangent_spill);
  Vector output_quadratic = midpoint_coefficients(
      raw_quadratic, deviation_squared, quadratic_spill);
  Vector output_anchor(dimension), output_defect(dimension);
  for (int i = 0; i < dimension; ++i) {
    output_anchor[i] = anchor_image[i].mid();
    output_defect[i] = (anchor_image[i] - output_anchor[i]) +
                       mapped_defect[i] + tangent_spill[i] +
                       quadratic_spill[i];
    const Ival direct_defect = directional_image[i] - output_anchor[i] -
                               output_tangent[i] * deviation -
                               output_quadratic[i] * deviation_squared;
    Ival sharpened;
    if (!capd::intervals::intersection(output_defect[i], direct_defect,
                                        sharpened)) {
      throw std::runtime_error(std::string(leg_label) +
                               ": empty C2 graph-defect intersection");
    }
    output_defect[i] =
        capd::intervals::intervalHull(sharpened, Ival(0));
  }
  // Exact coordinate-section normalization after all return-time derivatives
  // have been incorporated by computeDP.
  output_anchor[section_coordinate] = section_value;
  output_tangent[section_coordinate] = Ival(0);
  output_quadratic[section_coordinate] = Ival(0);
  output_defect[section_coordinate] = Ival(0);
  // The LC flow has ww'=0 and every section is independent of ww, so this
  // coordinate is the exact parameter pivot throughout the itinerary.
  output_anchor[10] = input.u_center;
  output_tangent[10] = Ival(1);
  output_quadratic[10] = Ival(0);
  output_defect[10] = Ival(0);
  return {output_anchor, output_tangent, output_defect,
          input.u_range, input.u_center, output_quadratic, true};
}

DirectCorrelatedGraph project_graph(
    const DirectCorrelatedGraph& input, int section_coordinate,
    const Ival& section_value,
    capd::poincare::CrossingDirection direction, int order,
    double tolerance, bool pair23_chart, LegMode mode,
    const char* leg_label) {
  return input.quadratic_mode
             ? project_graph_c2(input, section_coordinate, section_value,
                                direction, order, tolerance, pair23_chart,
                                mode, leg_label)
             : project_graph_c1(input, section_coordinate, section_value,
                                direction, order, tolerance, pair23_chart,
                                mode, leg_label);
}

Vector graph_hull(const DirectCorrelatedGraph& graph) {
  Vector hull(12);
  const Ival deviation = graph.u_range - graph.u_center;
  for (int i = 0; i < 12; ++i) {
    hull[i] = graph.anchor[i] + graph.tangent[i] * deviation +
              graph.defect[i];
    if (graph.quadratic_mode) {
      hull[i] += graph.quadratic[i] * square_interval(deviation);
    }
  }
  return hull;
}

void print_leg(const char* label, const DirectCorrelatedGraph& graph) {
  const Vector hull = graph_hull(graph);
  const Vector parameter_spread =
      graph.tangent * (graph.u_range - graph.u_center);
  Vector quadratic_spread(12);
  if (graph.quadratic_mode) {
    quadratic_spread = graph.quadratic *
                       square_interval(graph.u_range - graph.u_center);
  }
  std::cout << "ENDGAME_LEG " << label << " tp=["
            << bound_double(hull[9].leftBound()) << ","
            << bound_double(hull[9].rightBound()) << "] jd=["
            << bound_double(hull[11].leftBound()) << ","
            << bound_double(hull[11].rightBound()) << "] hull="
            << hull_width(hull, 12)
            << " parameter_spread=" << hull_width(parameter_spread, 12)
            << " quadratic_spread=" << hull_width(quadratic_spread, 12)
            << " defect=" << hull_width(graph.defect, 12)
            << " hull_component=" << widest_component(hull, 12)
            << " defect_component=" << widest_component(graph.defect, 12)
            << "\n" << std::flush;
}

void certify_strict_maximum(const DirectCorrelatedGraph& graph,
                            const Family& family, bool pair23_chart,
                            const char* label) {
  const Vector hull = graph_hull(graph);
  const DirectLcScalars sc = pair23_chart
                                 ? evaluate_pair23_lc(hull, family)
                                 : evaluate_direct_lc(hull, family);
  if (!(sc.potential.rightBound() < (2 * family.u0).leftBound())) {
    throw std::runtime_error(std::string(label) +
                             ": maximum is not certified strict (U<2U0)");
  }
  if (!direct_lc_residual_excludes_brake(hull)) {
    throw std::runtime_error(std::string(label) +
                             ": maximum residual does not exclude a brake");
  }
  std::cout << "ENDGAME_MAXIMUM " << label << " UoverU0=["
            << bound_double((sc.potential / family.u0).leftBound()) << ","
            << bound_double((sc.potential / family.u0).rightBound())
            << "]\n" << std::flush;
}

void check_switch_state(const DirectCorrelatedGraph& graph,
                        const Family& family, bool pair23_chart,
                        bool expect_positive_j, const char* label) {
  const Vector hull = graph_hull(graph);
  const DirectLcScalars sc = pair23_chart
                                 ? evaluate_pair23_lc(hull, family)
                                 : evaluate_direct_lc(hull, family);
  if (!(sc.selected_radius.leftBound() > 0) ||
      !(sc.r12_squared.leftBound() > 0) ||
      !(sc.r23_squared.leftBound() > 0)) {
    throw std::runtime_error(std::string(label) +
                             ": switch lost collision separation");
  }
  if (expect_positive_j ? !(hull[11].leftBound() > 0)
                        : !(hull[11].rightBound() < 0)) {
    throw std::runtime_error(std::string(label) +
                             ": switch lost prescribed J sign");
  }
  print_leg(label, graph);
}

// Explicitly certify the nonvanishing square-root component used by the
// exchange sandwich.  These are twice the squared lift denominators:
// Form B has 2*w_i^2=|g|-g_x, while Form A has
// 2*w_r^2=|g|+g_x.  The chart maps would fail interval evaluation if a
// denominator contained zero, but recording the strict margins makes the
// branch-domain proof independent of that implementation side effect.
void certify_pair13_to_pair23_form_b_lift(
    const DirectCorrelatedGraph& graph, const Family& family,
    const char* label) {
  const Vector hull = graph_hull(graph);
  const Ival old_gx = hull[0] * hull[0] - hull[1] * hull[1];
  const Ival old_gy = Ival(2) * hull[0] * hull[1];
  const Ival inv_m13 = Ival(1) / (family.a + Ival(1));
  const Ival old_xx = hull[5] + inv_m13 * old_gx;
  const Ival old_xy = hull[6] + inv_m13 * old_gy;
  const Ival gx = old_gx - old_xx;
  const Ival gy = old_gy - old_xy;
  const Ival margin = sqrt(gx * gx + gy * gy) - gx;
  if (!(margin.leftBound() > 0)) {
    throw std::runtime_error(std::string(label) +
                             ": Form-B lift margin is not positive");
  }
  std::cout << "ENDGAME_LIFT_MARGIN " << label << " inf_abs_g_minus_gx="
            << bound_double(margin.leftBound()) << "\n" << std::flush;
}

void certify_pair23_to_pair13_form_a_lift(
    const DirectCorrelatedGraph& graph, const Family& family,
    const char* label) {
  const Vector hull = graph_hull(graph);
  const Ival old_gx = hull[0] * hull[0] - hull[1] * hull[1];
  const Ival old_gy = Ival(2) * hull[0] * hull[1];
  const Ival inv_m23 = Ival(1) / (family.b + Ival(1));
  const Ival d13x = hull[5] + (inv_m23 - Ival(1)) * old_gx;
  const Ival d13y = hull[6] + (inv_m23 - Ival(1)) * old_gy;
  const Ival gx = -d13x;
  const Ival gy = -d13y;
  const Ival margin = sqrt(gx * gx + gy * gy) + gx;
  if (!(margin.leftBound() > 0)) {
    throw std::runtime_error(std::string(label) +
                             ": Form-A lift margin is not positive");
  }
  std::cout << "ENDGAME_LIFT_MARGIN " << label << " inf_abs_g_plus_gx="
            << bound_double(margin.leftBound()) << "\n" << std::flush;
}

// Phase-robust terminal escape check (docs/FABLE_MIDDLE_ESCAPE.md,
// corollary in section 3a): binary {2,3}, escaper 1, eta = 4, using only
// the transported h and the outer variables G, P from the graph hull.
bool terminal_phase_robust_check(const DirectCorrelatedGraph& graph) {
  const Ival eta = Ival(4);
  const Vector hull = graph_hull(graph);
  const Ival u = graph.u_range;
  const Ival one(1);
  const Ival qden = one + u * u;
  const Ival mass_a = (one - u * u) / qden;
  const Ival pair_m = (one + u) * (one + u) / qden;
  const Ival total_m = Ival(2) * (one + u) / qden;
  const Ival h = hull[4];
  const Ival gx = hull[5], gy = hull[6], px = hull[7], py = hull[8];

  std::cout << std::setprecision(17) << "TERMINAL_BOX 4 "
            << bound_double(u.leftBound()) << " "
            << bound_double(u.rightBound());
  for (int i : {0, 1, 2, 3, 5, 6, 7, 8, 4}) {
    std::cout << " " << bound_double(hull[i].leftBound()) << " "
              << bound_double(hull[i].rightBound());
  }
  std::cout << "\n" << std::flush;

  const Ival rho_sq = gx * gx + gy * gy;
  if (!(rho_sq.leftBound() > 0)) {
    std::cout << "TERMINAL_FAIL outer_distance_may_vanish\n";
    return false;
  }
  const Ival rho = sqrt(rho_sq);
  const Ival radius = pair_m / eta;
  const Ival d = rho - radius;
  std::cout << "TERMINAL inf_d=" << bound_double(d.leftBound()) << "\n";
  if (!(d.leftBound() > 0)) {
    std::cout << "TERMINAL_FAIL separation_margin_not_positive\n";
    return false;
  }
  const Ival rhodot = (gx * px + gy * py) / rho;
  std::cout << "TERMINAL inf_rhodot="
            << bound_double(rhodot.leftBound()) << "\n";
  if (!(rhodot.leftBound() > 0)) {
    std::cout << "TERMINAL_FAIL radial_speed_not_positive\n";
    return false;
  }
  const Ival e_rho = rhodot * rhodot / Ival(2) - total_m / d;
  std::cout << "TERMINAL inf_Erho="
            << bound_double(e_rho.leftBound()) << "\n";
  if (!(e_rho.leftBound() > 0)) {
    std::cout << "TERMINAL_FAIL radial_energy_not_positive\n";
    return false;
  }
  const Ival v_inf = sqrt(Ival(2) * e_rho);
  const Ival delta =
      mass_a * sqrt(Ival(2) * pair_m * radius) / (v_inf * d * d);
  const Ival margin = -eta - h - delta;
  std::cout << "TERMINAL sup_h=" << bound_double(h.rightBound())
            << " sup_Delta=" << bound_double(delta.rightBound())
            << " inf_margin=" << bound_double(margin.leftBound()) << "\n"
            << std::flush;
  if (!(margin.leftBound() > 0)) {
    std::cout << "TERMINAL_FAIL inner_energy_margin_not_positive\n";
    return false;
  }
  return true;
}

// Exception-safe step: restore the complete set representation before a
// retry.  This does not rely on a thrown CAPD move leaving its input
// untouched (in particular, an empty-intersection path may have written
// representation members before throwing).
void guarded_direct_move(PhaseRunner& runner, Set& set, double cap) {
  for (;;) {
    Set backup(set);
    try {
      runner.solver.setMaxStep(Ival(cap));
      set.move(runner.solver);
      return;
    } catch (const std::exception&) {
      set = backup;
      ++runner.capped_retries;
      if (runner.capped_retries > 200000 || cap < 1e-14) throw;
      cap /= 2;
    }
  }
}

struct SectionRemainderArm {
  Matrix basis;
  Matrix inverse;
  Vector coordinates;

  explicit SectionRemainderArm(int dimension)
      : basis(dimension, dimension),
        inverse(dimension, dimension),
        coordinates(dimension) {}
};

// Put one mean-value remainder arm [DP] B r + slack into an invertible
// point basis adapted to the coordinate section x_k=value.  The exact
// Poincare image is tangent to that section, so one column of the midpoint
// basis may be replaced by its normal e_k and the corresponding coordinate
// fixed to zero.  We try every possible replacement column and retain the
// narrowest rigorously invertible representation.
SectionRemainderArm make_section_remainder_arm(
    const Matrix& section_derivative, const Matrix& source_basis,
    const Vector& source_coordinates, const Vector& common_slack,
    const Vector& direct_image_remainder, int section_coordinate) {
  const int dimension = source_coordinates.dimension();
  const Matrix linear_arm = section_derivative * source_basis;
  Vector physical_arm = linear_arm * source_coordinates + common_slack;
  for (int i = 0; i < dimension; ++i) {
    Ival sharpened;
    if (!capd::intervals::intersection(
            physical_arm[i], direct_image_remainder[i], sharpened)) {
      throw std::runtime_error(
          "empty structured section remainder intersection");
    }
    physical_arm[i] = sharpened;
  }
  // This is an exact property of the Poincare map, not a numerical
  // narrowing: every returned point has the prescribed kth coordinate.
  physical_arm[section_coordinate] = Ival(0);

  bool found = false;
  double best_width = 0;
  SectionRemainderArm best(dimension);
  for (int pivot = 0; pivot < dimension; ++pivot) {
    Matrix basis(dimension, dimension);
    for (int i = 0; i < dimension; ++i) {
      for (int j = 0; j < dimension; ++j) {
        basis[i][j] =
            (Ival(linear_arm[i][j].leftBound()) +
             Ival(linear_arm[i][j].rightBound())) /
            Ival(2);
      }
    }
    // Replace one column by the section normal.  The other columns retain
    // the midpoint tangent geometry produced by this remainder arm.
    for (int j = 0; j < dimension; ++j) {
      basis[section_coordinate][j] = Ival(0);
    }
    for (int i = 0; i < dimension; ++i) {
      basis[i][pivot] = Ival(0);
    }
    basis[section_coordinate][pivot] = Ival(1);

    try {
      const Matrix inverse =
          capd::matrixAlgorithms::krawczykInverse(basis);
      Vector coordinates = inverse * physical_arm;
      // In this adapted basis the pivot coordinate equals the physical
      // section-normal coordinate exactly.
      coordinates[pivot] = Ival(0);
      const Vector rebuilt = basis * coordinates;
      bool contains_arm = true;
      for (int i = 0; i < dimension; ++i) {
        if (!subset(physical_arm[i], rebuilt[i])) {
          contains_arm = false;
          break;
        }
      }
      if (!contains_arm) continue;
      const double width = hull_width(rebuilt, dimension);
      if (!found || width < best_width) {
        found = true;
        best_width = width;
        best.basis = basis;
        best.inverse = inverse;
        best.coordinates = coordinates;
      }
    } catch (const std::exception&) {
      // A bad replacement column can make the tangent minor singular.  A
      // rank-(n-1) transverse Poincare derivative has another valid minor.
    }
  }
  if (!found) {
    throw std::runtime_error(
        "no invertible tangent basis for structured section image");
  }
  return best;
}

// Rebuild a C0 tripleton for a Poincare image without collapsing its two
// remainder representations.  CAPD 6.1.0's public constructor initializes
// Q from B, so install the independently validated Q arm explicitly and
// refresh m_currentSet before the next validated move.
Set make_structured_section_set(
    const Vector& new_x, const Matrix& new_c, const Vector& r0,
    const Matrix& section_derivative, const Matrix& old_b,
    const Vector& old_r, const Matrix& old_q_basis, const Vector& old_q,
    const Vector& common_slack, const Vector& direct_image_remainder,
    int section_coordinate) {
  const int dimension = new_x.dimension();
  const SectionRemainderArm b_arm = make_section_remainder_arm(
      section_derivative, old_b, old_r, common_slack,
      direct_image_remainder, section_coordinate);
  const SectionRemainderArm q_arm = make_section_remainder_arm(
      section_derivative, old_q_basis, old_q, common_slack,
      direct_image_remainder, section_coordinate);

  Set result(new_x, new_c, r0, b_arm.basis, b_arm.coordinates, Ival(0));
  result.m_Q = q_arm.basis;
  result.m_invQ = q_arm.inverse;
  result.m_q = q_arm.coordinates;

  const Vector b_part = result.get_B() * result.get_r();
  const Vector q_part = result.m_Q * result.m_q;
  Vector represented = new_x + new_c * r0;
  for (int i = 0; i < dimension; ++i) {
    Ival remainder;
    if (!capd::intervals::intersection(b_part[i], q_part[i], remainder)) {
      throw std::runtime_error(
          "empty structured tripleton remainder intersection");
    }
    represented[i] += remainder;
  }
  result.m_currentSet = represented;
  return result;
}

// Project one correlated C0 tripleton onto a transverse coordinate section
// while independently auditing the complete common-sigma tube through the
// latest validated return.  The Poincare image synchronizes the family; the
// audit is what proves collision and brake exclusion between sections.
Vector project_c0_section_with_audit(
    Set& set, int section_coordinate, const Ival& section_value,
    capd::poincare::CrossingDirection direction, bool pair23_chart,
    const Ival& u_range, int order, double tolerance) {
  Set audit_set(set);
  Map field = pair23_chart ? make_pair23_lc_field() : make_direct_lc_field();
  CoordinateSection section(12, section_coordinate, section_value);

  // Replace the tripleton's intersected remainder by its coordinatewise
  // intersection box.  The resulting doubleton is convex, contains the
  // original set and its stored center, and is therefore a valid domain for
  // a mean-value enclosure of the Poincare map.
  const Vector x = set.get_x();
  const Matrix c_matrix = set.get_C();
  const Vector r0 = set.get_r0();
  const Matrix b_matrix = set.get_B();
  const Vector b_coordinates = set.get_r();
  const Matrix q_matrix = set.m_Q;
  const Vector q_coordinates = set.m_q;
  const int dimension = x.dimension();
  const Vector b_part = b_matrix * b_coordinates;
  const Vector q_part = q_matrix * q_coordinates;
  Vector remainder(dimension);
  for (int i = 0; i < dimension; ++i) {
    if (!capd::intervals::intersection(b_part[i], q_part[i],
                                       remainder[i])) {
      throw std::runtime_error(
          "empty remainder before synchronized section");
    }
    remainder[i] = capd::intervals::intervalHull(remainder[i], Ival(0));
  }
  C1Set derivative_set(
      x, c_matrix, r0, remainder, set.getCurrentTime());
  Solver section_solver(field, order);
  section_solver.setAbsoluteTolerance(tolerance);
  section_solver.setRelativeTolerance(tolerance);
  // Exchange legs have a simultaneously close unselected pair and retain
  // the strict 1/2000 cap.  After the Form-B switch the unselected pairs are
  // separated; 1/500 still resolves the selected LC binary very finely.
  // Both are merely maximum proposed steps: CAPD validates every step, and
  // the independent tube audit below keeps its dynamic separation cap.
  const Ival section_step_cap =
      pair23_chart ? Ival(1) / Ival(500) : Ival(1) / Ival(2000);
  section_solver.setMaxStep(section_step_cap);
  PoincareMap section_map(section_solver, section, direction);
  section_map.setMaxReturnTime(50.0);
  Ival return_time;
  Matrix flow_derivative(dimension, dimension);
  const Vector section_image =
      section_map(derivative_set, flow_derivative, return_time);
  if (!section_image[section_coordinate].contains(section_value)) {
    throw std::runtime_error("synchronized C0 map missed its section");
  }
  const Matrix section_derivative = section_map.computeDP(
      section_image, flow_derivative, return_time);

  // Independently propagate the stored center to the same section.  The
  // mean-value theorem on the convex derivative_set then encloses the image
  // of the complete original tripleton while retaining its distinguished
  // parameter generator.
  Map anchor_field =
      pair23_chart ? make_pair23_lc_field() : make_direct_lc_field();
  Solver anchor_solver(anchor_field, order);
  anchor_solver.setAbsoluteTolerance(tolerance);
  anchor_solver.setRelativeTolerance(tolerance);
  anchor_solver.setMaxStep(section_step_cap);
  PoincareMap anchor_map(anchor_solver, section, direction);
  anchor_map.setMaxReturnTime(50.0);
  Set anchor_set(x, set.getCurrentTime());
  Ival anchor_return;
  const Vector anchor_image = anchor_map(anchor_set, anchor_return);
  if (!anchor_image[section_coordinate].contains(section_value)) {
    throw std::runtime_error("synchronized center missed its section");
  }

  const Matrix dc = section_derivative * c_matrix;
  const Vector d_remainder = section_derivative * remainder;
  Matrix dc_mid(dimension, dimension);
  Vector spill(dimension), new_x(dimension), new_r(dimension);
  for (int i = 0; i < dimension; ++i) {
    spill[i] = Ival(0);
    const Ival anchor_mid =
        (Ival(anchor_image[i].leftBound()) +
         Ival(anchor_image[i].rightBound())) /
        2;
    new_x[i] = anchor_mid;
    for (int j = 0; j < dimension; ++j) {
      const Ival matrix_mid =
          (Ival(dc[i][j].leftBound()) + Ival(dc[i][j].rightBound())) /
          2;
      dc_mid[i][j] = matrix_mid;
      spill[i] += (dc[i][j] - matrix_mid) * r0[j];
    }
    new_r[i] = d_remainder[i] + (anchor_image[i] - anchor_mid) + spill[i];
  }
  // Every image lies exactly on the coordinate section.  Enforce that exact
  // algebraic fact after the mean-value construction.
  new_x[section_coordinate] = section_value;
  new_r[section_coordinate] = Ival(0);
  for (int j = 0; j < dimension; ++j) {
    dc_mid[section_coordinate][j] = Ival(0);
  }
  // Intersect the mean-value remainder with the independently returned
  // coordinate enclosure of the complete Poincare image.
  const Vector image_remainder =
      section_image - new_x - dc_mid * r0;
  for (int i = 0; i < dimension; ++i) {
    Ival sharpened;
    if (!capd::intervals::intersection(new_r[i], image_remainder[i],
                                       sharpened)) {
      throw std::runtime_error(
          "empty mean-value/section-image remainder intersection");
    }
    new_r[i] = sharpened;
  }
  Vector exact_image_remainder = image_remainder;
  exact_image_remainder[section_coordinate] = Ival(0);
  const bool structured_section =
      std::getenv("FABLE_ENDGAME_STRUCTURED_SECTION") != nullptr;
  Set synchronized_set = structured_section
      ? make_structured_section_set(
            new_x, dc_mid, r0, section_derivative, b_matrix,
            b_coordinates, q_matrix, q_coordinates,
            anchor_image - new_x + spill, exact_image_remainder,
            section_coordinate)
      : Set(new_x, dc_mid, r0, new_r, Ival(0));

  const Ival audit_target = Ival(return_time.rightBound());
  Map audit_field =
      pair23_chart ? make_pair23_lc_field() : make_direct_lc_field();
  PhaseRunner audit(audit_field, order, tolerance);
  const Family family = make_family(u_range);
  long audit_steps = 0;
  for (;; ++audit_steps) {
    if (audit_steps > 300000) {
      throw std::runtime_error("synchronized section audit step limit");
    }
    const Vector before(audit_set);
    if (audit_set.getCurrentTime().leftBound() >=
        audit_target.rightBound()) {
      break;
    }
    const DirectLcScalars pre =
        pair23_chart ? evaluate_pair23_lc(before, family)
                     : evaluate_direct_lc(before, family);
    if (!(pre.selected_radius.leftBound() > 0) ||
        !(pre.r12_squared.leftBound() > 0) ||
        !(pre.r23_squared.leftBound() > 0)) {
      throw std::runtime_error(
          "synchronized section audit lost pre-step separation");
    }
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
    guarded_direct_move(audit, audit_set, cap);
    const Vector enclosure = audit_set.getLastEnclosure();
    const DirectLcScalars sc =
        pair23_chart ? evaluate_pair23_lc(enclosure, family)
                     : evaluate_direct_lc(enclosure, family);
    if (!(sc.selected_radius.leftBound() > 0) ||
        !(sc.r12_squared.leftBound() > 0) ||
        !(sc.r23_squared.leftBound() > 0)) {
      throw std::runtime_error(
          "synchronized section audit lost collision separation");
    }
    if (contains_zero(sc.i_dot) &&
        !(sc.potential.leftBound() > family.u0.rightBound()) &&
        !(sc.kinetic.leftBound() > 0) &&
        !direct_lc_residual_excludes_brake(enclosure)) {
      throw std::runtime_error(
          "synchronized section audit lost every brake obstruction");
    }
  }

  std::cout << "C0_SYNC_AUDIT section=["
            << bound_double(section_value.leftBound()) << ","
            << bound_double(section_value.rightBound()) << "] sigma_return=["
            << bound_double(return_time.leftBound()) << ","
            << bound_double(return_time.rightBound()) << "] steps="
            << audit_steps << "\n" << std::flush;

  set = synchronized_set;
  const Vector synchronized(set);
  if (!synchronized[section_coordinate].contains(section_value)) {
    throw std::runtime_error(
        "synchronized C0 set does not contain its section value");
  }
  const DirectLcScalars sync_sc =
      pair23_chart ? evaluate_pair23_lc(synchronized, family)
                   : evaluate_direct_lc(synchronized, family);
  if (!(sync_sc.selected_radius.leftBound() > 0) ||
      !(sync_sc.r12_squared.leftBound() > 0) ||
      !(sync_sc.r23_squared.leftBound() > 0)) {
    throw std::runtime_error(
        "synchronized section image lost collision separation");
  }
  return synchronized;
}

// Rigorous mean-value image of a tripleton set under an algebraic map:
// for p = x + C r0 + (B r cap ...) in a convex interval box H containing
// both p and the stored center x,
//   map(p) in map(x) + [D map](H) (C r0 + B r),
// realized as a new tripleton with C' = D C (u-correlation preserved),
// r0' = r0, and remainder r' = D B r + (map(x) - mid(map(x))).
Set mean_value_switch(const Set& set, Map& transformation) {
  const Vector x = set.get_x();
  // Include the stored center explicitly so every segment [x,p] lies in H;
  // do not rely on an undocumented promise that Vector(set) contains x.
  Vector hull(set);
  hull = capd::vectalg::intervalHull(hull, x);
  const Matrix c_matrix = set.get_C();
  const Vector r0 = set.get_r0();
  const int dimension = hull.dimension();
  // The stored remainder is intersection(B r, Q q); B can be severely
  // ill-conditioned after many steps, so the intersection is essential.
  const Vector b_part = set.get_B() * set.get_r();
  const Vector q_part = set.m_Q * set.m_q;
  Vector remainder(dimension);
  for (int i = 0; i < dimension; ++i) {
    if (!capd::intervals::intersection(b_part[i], q_part[i],
                                       remainder[i])) {
      throw std::runtime_error("empty tripleton remainder intersection");
    }
  }
  const Vector image_x = transformation(x);
  const Matrix derivative = transformation.derivative(hull);
  const Matrix dc = derivative * c_matrix;
  const Vector d_remainder = derivative * remainder;
  // The tripleton representation requires POINT matrices: split D*C into
  // its midpoint and spill the discarded widths (times r0) into the
  // remainder.
  Matrix dc_mid(dimension, dimension);
  Vector spill(dimension);
  for (int i = 0; i < dimension; ++i) {
    spill[i] = Ival(0);
    for (int j = 0; j < dimension; ++j) {
      const Ival mid = (Ival(dc[i][j].leftBound()) +
                        Ival(dc[i][j].rightBound())) / 2;
      dc_mid[i][j] = mid;
      spill[i] += (dc[i][j] - mid) * r0[j];
    }
  }
  Vector new_x(dimension), new_r(dimension);
  for (int i = 0; i < dimension; ++i) {
    const Ival mid = (Ival(image_x[i].leftBound()) +
                      Ival(image_x[i].rightBound())) / 2;
    new_x[i] = mid;
    new_r[i] = d_remainder[i] + (image_x[i] - mid) + spill[i];
  }
  return Set(new_x, dc_mid, r0, new_r, set.getCurrentTime());
}

// Apply an algebraic chart map through CAPD's native discrete-dynamical-
// system adapter.  Unlike the conservative manual image above, this retains
// both tripleton remainder representations B*r and Q*q and intersects them
// with the direct interval image before reorganization.  DynSysMap advances
// its abstract discrete clock by one; restore the incoming solver clock
// because every LC field here is autonomous and physical time is state[9].
Set structured_switch(const Set& set, Map& transformation) {
  Set image(set);
  const Ival solver_clock = set.getCurrentTime();
  capd::dynsys::DynSysMap<Map> discrete_map(transformation);
  image.move(discrete_map);
  image.setCurrentTime(solver_clock);
  return image;
}

// Phase-robust terminal margins evaluated on a state enclosure (hull of the
// current set): binary {2,3}, escaper 1, eta = 4.  Quiet unless verbose.
bool terminal_margins_pass(const Vector& hull, bool verbose) {
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
  if (!(d.leftBound() > 0)) return false;
  const Ival rhodot = (gx * px + gy * py) / rho;
  if (!(rhodot.leftBound() > 0)) return false;
  const Ival e_rho = rhodot * rhodot / Ival(2) - total_m / d;
  if (!(e_rho.leftBound() > 0)) return false;
  const Ival v_inf = sqrt(Ival(2) * e_rho);
  const Ival delta =
      mass_a * sqrt(Ival(2) * pair_m * radius) / (v_inf * d * d);
  const Ival margin = -eta - h - delta;
  if (verbose) {
    std::cout << "TERMINAL tp=[" << bound_double(hull[9].leftBound())
              << "," << bound_double(hull[9].rightBound())
              << "] inf_d=" << bound_double(d.leftBound())
              << " inf_rhodot=" << bound_double(rhodot.leftBound())
              << " inf_Erho=" << bound_double(e_rho.leftBound())
              << " sup_h=" << bound_double(h.rightBound())
              << " sup_Delta=" << bound_double(delta.rightBound())
              << " inf_margin=" << bound_double(margin.leftBound())
              << "\n" << std::flush;
    std::cout << std::setprecision(17) << "TERMINAL_BOX 4 "
              << bound_double(u.leftBound()) << " "
              << bound_double(u.rightBound());
    for (int i : {0, 1, 2, 3, 5, 6, 7, 8, 4}) {
      std::cout << " " << bound_double(hull[i].leftBound()) << " "
                << bound_double(hull[i].rightBound());
    }
    std::cout << "\n" << std::flush;
  }
  return margin.leftBound() > 0;
}

// Single correlated C0 tripleton propagation of the whole endgame with
// per-step Theorem C covering audits and three mean-value chart switches.
// No Poincare sections: every accepted step is audited, and the terminal
// certificate is evaluated on step enclosures (each real parameter needs
// only SOME collision-free certificate time, which any passing enclosure
// provides fiberwise).
int run_endgame_c0(const Ival& u_param, long p, long q, long p2, long q2,
                   int order, double tolerance) {
  const Family family = make_family(u_param);
  std::cout << std::setprecision(17);
  Set set = make_direct_launch_graph(u_param).c0_set();

  struct Phase {
    double end_time;      // physical time at which the phase ends
    bool pair23;
    const char* label;
  };
  const Phase phases[] = {
      {1.0, false, "pair13_launch"},
      {1.75, true, "pair23_first"},
      {3.5, false, "pair13_middle"},
      {4.6, true, "pair23_escape"},
  };
  Map fields[2] = {make_direct_lc_field(), make_pair23_lc_field()};
  Map switch_to_23 = make_pair13_to_pair23_map();
  Map switch_to_13 = make_pair23_to_pair13_map();
  Map switch_to_23_form_b = make_pair13_to_pair23_map_form_b();

  const Ival t1 = Ival(1) / Ival(5);
  bool initial_phase = true;
  const bool synchronize_exchange =
      std::getenv("FABLE_ENDGAME_SYNC") != nullptr;
  const bool synchronize_preswitch =
      std::getenv("FABLE_ENDGAME_PRESWITCH") != nullptr;
  const bool structured_form_b =
      std::getenv("FABLE_ENDGAME_STRUCTURED_SWITCH") != nullptr;
  const bool synchronize_pair23 =
      std::getenv("FABLE_ENDGAME_PAIR23_SYNC") != nullptr;
  if (synchronize_preswitch && !synchronize_exchange) {
    throw std::runtime_error(
        "FABLE_ENDGAME_PRESWITCH requires FABLE_ENDGAME_SYNC");
  }
  if (synchronize_pair23 &&
      (!synchronize_exchange || !synchronize_preswitch)) {
    throw std::runtime_error(
        "FABLE_ENDGAME_PAIR23_SYNC requires exchange and preswitch sync");
  }
  bool exchange_synchronized = false;
  long steps = 0;
  double largest_hull = 0;

  for (int phase_index = 0; phase_index < 4; ++phase_index) {
    const Phase& phase = phases[phase_index];
    const double phase_end_time =
        synchronize_preswitch && phase_index == 2 ? 3.48 : phase.end_time;
    if (phase_index > 0) {
      Map& transformation =
          phase_index == 1 ? switch_to_23
                           : (phase_index == 2 ? switch_to_13
                                               : switch_to_23_form_b);
      set = structured_form_b && phase_index == 3
                ? structured_switch(set, transformation)
                : mean_value_switch(set, transformation);
      const Vector switched(set);
      const DirectLcScalars sc =
          phase.pair23 ? evaluate_pair23_lc(switched, family)
                       : evaluate_direct_lc(switched, family);
      if (!(sc.selected_radius.leftBound() > 0) ||
          !(sc.r12_squared.leftBound() > 0) ||
          !(sc.r23_squared.leftBound() > 0)) {
        std::cerr << "FAIL switch into " << phase.label
                  << " lost separation\n";
        return 1;
      }
      std::cout << "C0_SWITCH " << phase.label << " tp=["
                << bound_double(switched[9].leftBound()) << ","
                << bound_double(switched[9].rightBound()) << "] hull="
                << hull_width(switched, 12) << "\n" << std::flush;
      if (synchronize_pair23 && phase_index == 3) {
        struct Pair23Section {
          Ival value;
          capd::poincare::CrossingDirection direction;
        };
        const Pair23Section pair23_sections[] = {
            {-Ival(1) / Ival(10), capd::poincare::MinusPlus},
            {-Ival(1) / Ival(20), capd::poincare::MinusPlus},
            {Ival(0), capd::poincare::MinusPlus},
            {Ival(1) / Ival(20), capd::poincare::MinusPlus},
            {Ival(1) / Ival(10), capd::poincare::MinusPlus},
            {Ival(3) / Ival(20), capd::poincare::MinusPlus},
            {Ival(1) / Ival(10), capd::poincare::PlusMinus},
            {Ival(1) / Ival(20), capd::poincare::PlusMinus},
            {Ival(0), capd::poincare::PlusMinus},
            {-Ival(1) / Ival(20), capd::poincare::PlusMinus},
            {-Ival(1) / Ival(10), capd::poincare::PlusMinus},
            {-Ival(3) / Ival(20), capd::poincare::PlusMinus},
            {-Ival(1) / Ival(10), capd::poincare::MinusPlus},
            {-Ival(1) / Ival(20), capd::poincare::MinusPlus},
            {Ival(0), capd::poincare::MinusPlus},
            {Ival(1) / Ival(20), capd::poincare::MinusPlus},
            {Ival(1) / Ival(10), capd::poincare::MinusPlus}};
        int ordinal = 0;
        for (const Pair23Section& section : pair23_sections) {
          const Vector image = project_c0_section_with_audit(
              set, 0, section.value, section.direction, true, u_param,
              order, tolerance);
          ++ordinal;
          std::cout << "C0_SYNC_PAIR23 ordinal=" << ordinal << " wr=["
                    << bound_double(image[0].leftBound()) << ","
                    << bound_double(image[0].rightBound()) << "] tp=["
                    << bound_double(image[9].leftBound()) << ","
                    << bound_double(image[9].rightBound()) << "] hull="
                    << hull_width(image, 12) << "\n" << std::flush;
        }
      }
    }
    PhaseRunner flow(fields[phase.pair23 ? 1 : 0], order, tolerance);
    for (;;) {
      const Vector before(set);
      if (synchronize_exchange && phase_index == 2 &&
          !exchange_synchronized &&
          before[9].leftBound() >= (Ival(13) / Ival(4)).rightBound()) {
        const Ival exchange_wr_sections[] = {
            -Ival(3) / Ival(5), -Ival(1) / Ival(2),
            -Ival(2) / Ival(5), -Ival(3) / Ival(10),
            -Ival(1) / Ival(5), Ival(0)};
        int ordinal = 0;
        for (const Ival& wr_section : exchange_wr_sections) {
          const Vector image = project_c0_section_with_audit(
              set, 0, wr_section, capd::poincare::MinusPlus,
              false, u_param, order, tolerance);
          const DirectLcScalars image_sc = evaluate_direct_lc(image, family);
          if (!(image[2].leftBound() > 0) ||
              !(image_sc.selected_radius.leftBound() > 0) ||
              !(image_sc.r12_squared.leftBound() > 0) ||
              !(image_sc.r23_squared.leftBound() > 0)) {
            throw std::runtime_error(
                "exchange section lost orientation or separation");
          }
          ++ordinal;
          std::cout << "C0_SYNC_EXCHANGE ordinal=" << ordinal
                    << " wr=[" << bound_double(image[0].leftBound())
                    << "," << bound_double(image[0].rightBound())
                    << "] tp=[" << bound_double(image[9].leftBound())
                    << "," << bound_double(image[9].rightBound())
                    << "] zr=[" << bound_double(image[2].leftBound())
                    << "," << bound_double(image[2].rightBound())
                    << "] hull=" << hull_width(image, 12) << "\n"
                    << std::flush;
        }
        if (synchronize_preswitch) {
          // The sixth exchange section lands immediately after the sharp
          // double encounter.  Recondition at t=3.48 and switch there, while
          // the new selected pair is farther from its next pericenter.  A
          // later section at t=3.50 left a width 4.49e-2 hull, while a
          // post-switch t=3.60 section enlarged the hull again.
          const Ival preswitch_time_sections[] = {
              Ival(87) / Ival(25)};
          int time_ordinal = 0;
          for (const Ival& time_section : preswitch_time_sections) {
            const Vector image = project_c0_section_with_audit(
                set, 9, time_section, capd::poincare::MinusPlus,
                false, u_param, order, tolerance);
            ++time_ordinal;
            std::cout << "C0_SYNC_PRE_SWITCH ordinal=" << time_ordinal
                      << " tp=[" << bound_double(image[9].leftBound())
                      << "," << bound_double(image[9].rightBound())
                      << "] hull=" << hull_width(image, 12) << "\n"
                      << std::flush;
          }
        }
        exchange_synchronized = true;
        continue;
      }
      if (before[9].leftBound() >= phase_end_time) break;
      const double w_abs = std::sqrt(std::max(
          1e-12,
          bound_double((before[0] * before[0] + before[1] * before[1])
                           .leftBound())));
      // The sigma-step must resolve the UNSELECTED pair separations too:
      // near an unselected close approach (e.g. the {2,3} conjunction at
      // t ~ 3.4515 inside the pair-{1,3} chart) a selected-pair-sized step
      // sweeps a large fraction of the unselected distance and the rough
      // enclosure of its 1/r^3 field explodes in width without throwing.
      // Physical-time budget r^{3/2}/40 (~ 1/20 of the free-fall time),
      // converted to sigma by dt = |w|^2 dsigma.
      const DirectLcScalars pre_scalars =
          phase.pair23 ? evaluate_pair23_lc(before, family)
                       : evaluate_direct_lc(before, family);
      const double unselected = std::sqrt(std::max(
          1e-12,
          std::min(bound_double(pre_scalars.r12_squared.leftBound()),
                   bound_double(pre_scalars.r23_squared.leftBound()))));
      const double w2_lower = std::max(1e-12, w_abs * w_abs);
      const double unselected_cap =
          unselected * std::sqrt(unselected) / (40.0 * w2_lower);
      const double cap = std::max(
          1.0 / 20000.0,
          std::min(std::min(w_abs / 24.0, unselected_cap), 1.0 / 100.0));
      try {
        guarded_direct_move(flow, set, cap);
      } catch (const std::exception& error) {
        std::cerr << "FAIL integrator exception in " << phase.label
                  << " at tp=[" << bound_double(before[9].leftBound())
                  << "," << bound_double(before[9].rightBound())
                  << "] hull=" << hull_width(before, 12) << ": "
                  << error.what() << "\n";
        return 1;
      }
      ++steps;
      const Vector enclosure = set.getLastEnclosure();
      const Vector snapshot(set);
      DirectLcScalars sc;
      try {
        sc = phase.pair23 ? evaluate_pair23_lc(enclosure, family)
                          : evaluate_direct_lc(enclosure, family);
      } catch (const std::exception& error) {
        std::cerr << "FAIL audit-evaluation exception in " << phase.label
                  << " at tp=[" << bound_double(snapshot[9].leftBound())
                  << "," << bound_double(snapshot[9].rightBound())
                  << "] hull=" << hull_width(snapshot, 12) << ": "
                  << error.what() << "\n";
        return 1;
      }
      if (!(sc.selected_radius.leftBound() > 0) ||
          !(sc.r12_squared.leftBound() > 0) ||
          !(sc.r23_squared.leftBound() > 0)) {
        std::cerr << "FAIL possible collision in " << phase.label
                  << " tp=" << to_double(snapshot[9]) << "\n";
        return 1;
      }
      if (initial_phase) {
        if (!(sc.potential.rightBound() < (2 * family.u0).leftBound())) {
          std::cerr << "FAIL initial potential bound tp="
                    << to_double(snapshot[9]) << "\n";
          return 1;
        }
        if (snapshot[9].leftBound() > t1.rightBound()) initial_phase = false;
      } else if (contains_zero(sc.i_dot) &&
                 !(sc.potential.leftBound() > family.u0.rightBound()) &&
                 !(sc.kinetic.leftBound() > 0) &&
                 !direct_lc_residual_excludes_brake(enclosure)) {
        std::cerr << "FAIL uncovered brake-exclusion step in " << phase.label
                  << " tp=" << to_double(snapshot[9]) << "\n";
        return 1;
      }
      largest_hull = std::max(largest_hull, hull_width(snapshot, 12));
      if (hull_width(snapshot, 12) > 10.0) {
        std::cerr << "FAIL set hull exploded in " << phase.label
                  << " tp=" << to_double(snapshot[9]) << "\n";
        return 1;
      }
      if (steps % 2000 == 0) {
        std::cout << "c0 " << phase.label << " tp="
                  << to_double(snapshot[9]) << " steps=" << steps
                  << " hull=" << hull_width(snapshot, 12) << "\n"
                  << std::flush;
      }
      if (phase_index == 3 && snapshot[9].leftBound() > 4.3 &&
          terminal_margins_pass(snapshot, false)) {
        terminal_margins_pass(snapshot, true);
        std::cout << "PASS_MIDDLE_ESCAPE_ENDGAME u=[" << p << "/" << q
                  << "," << p2 << "/" << q2 << "] terminal_tp=["
                  << bound_double(snapshot[9].leftBound()) << ","
                  << bound_double(snapshot[9].rightBound())
                  << "] eta=4 steps=" << steps
                  << " max_hull=" << largest_hull
                  << " method=CAPD-6.1.0-MPFR"
                  << " capd_commit=731079217a9254ea2948d742df2b170895effe7f"
                  << "\n";
        return 0;
      }
      if (steps > 400000) {
        std::cerr << "FAIL step limit\n";
        return 1;
      }
    }
    std::cout << "C0_PHASE_DONE " << phase.label << " steps=" << steps
              << " hull=" << hull_width(Vector(set), 12) << "\n"
              << std::flush;
  }
  std::cerr << "FAIL terminal certificate did not fire by tp=4.6\n";
  return 1;
}

int run_endgame(const Ival& u_param, long p, long q, long p2, long q2,
                int order, double tolerance) {
  const Family family = make_family(u_param);
  std::cout << std::setprecision(17);

  const bool graph_c2 =
      std::getenv("FABLE_ENDGAME_GRAPH_C2") != nullptr;
  const bool graph_fixed_energy_h =
      std::getenv("FABLE_ENDGAME_GRAPH_FIXED_ENERGY_H") != nullptr;
  const bool graph_exchange_sync =
      std::getenv("FABLE_ENDGAME_GRAPH_EXCHANGE_SYNC") != nullptr;
  const bool graph_exchange_energy_project =
      std::getenv("FABLE_ENDGAME_GRAPH_EXCHANGE_ENERGY_PROJECT") != nullptr;
  const bool graph_exchange_invariant_project =
      std::getenv("FABLE_ENDGAME_GRAPH_EXCHANGE_INVARIANT_PROJECT") != nullptr;
  DirectCorrelatedGraph graph = graph_c2
                                    ? make_quadratic_launch_graph(u_param)
                                    : make_direct_launch_graph(u_param);
  const auto MP = capd::poincare::MinusPlus;
  const auto PM = capd::poincare::PlusMinus;

  struct TimeLeg {
    long num;
    long den;
    bool pair23;
    LegMode mode;
  };

  auto run_time_leg = [&](const TimeLeg& leg) {
    const Ival value = Ival(leg.num) / Ival(leg.den);
    const std::string label = "t=" + std::to_string(leg.num) + "/" +
                              std::to_string(leg.den);
    graph = project_graph(graph, 9, value, MP, order, tolerance,
                          leg.pair23, leg.mode, label.c_str());
    print_leg(label.c_str(), graph);
  };
  auto run_event_leg = [&](bool maximum, bool pair23, const char* label) {
    graph = project_graph(graph, 11, Ival(0), maximum ? PM : MP, order,
                          tolerance, pair23, LegMode::kCross, label);
    print_leg(label, graph);
    if (maximum) {
      certify_strict_maximum(graph, family, pair23, label);
    } else {
      const Vector hull = graph_hull(graph);
      const DirectLcScalars sc =
          pair23 ? evaluate_pair23_lc(hull, family)
                 : evaluate_direct_lc(hull, family);
      if (!(sc.potential.leftBound() > (2 * family.u0).rightBound())) {
        throw std::runtime_error(std::string(label) +
                                 ": minimum is not uniformly strict");
      }
    }
  };

  // --- Committed prefix itinerary (launch through first maximum). ---
  const TimeLeg approach1[] = {
      {2, 5, false, LegMode::kPostMax},  {11, 20, false, LegMode::kNegative},
      {3, 5, false, LegMode::kNegative}, {31, 50, false, LegMode::kNegative},
      {16, 25, false, LegMode::kNegative},{33, 50, false, LegMode::kNegative},
      {17, 25, false, LegMode::kNegative},{7, 10, false, LegMode::kNegative}};
  for (const TimeLeg& leg : approach1) run_time_leg(leg);
  run_event_leg(false, false, "min1");
  const TimeLeg out1[] = {
      {17, 20, false, LegMode::kPostMin}, {9, 10, false, LegMode::kPositive},
      {19, 20, false, LegMode::kPositive},{1, 1, false, LegMode::kPositive}};
  for (const TimeLeg& leg : out1) run_time_leg(leg);
  // Chart schedule, dictated by the deep-encounter inventory at u = 0.29
  // ({1,3}@0.315, 0.767; {2,3}@1.047, 1.596; {1,3}@1.92, 2.329, 2.92;
  // the double {2,3}@3.4515 + {1,3}@3.4695; then {2,3} binary pericenters
  // from 3.5165 on): each deep encounter must lie in the window of the
  // chart that regularizes its pair.
  //   pair-13 : [0, 1]        -> switch A at tp = 1
  //   pair-23 : [1, 7/4]      -> switch back (Form A on g13) at tp = 7/4
  //   pair-13 : [7/4, 7/2]    -> Form-B switch at tp = 7/2
  //   pair-23 : [7/2, 9/2]    -> terminal
  graph = transform_graph(graph, make_pair13_to_pair23_map());
  check_switch_state(graph, family, true, true, "switch13to23_formA");
  const TimeLeg pair23_1[] = {
      {21, 20, true, LegMode::kPositive}, {11, 10, true, LegMode::kPositive},
      {23, 20, true, LegMode::kPositive}, {6, 5, true, LegMode::kPositive},
      {5, 4, true, LegMode::kPositive},   {13, 10, true, LegMode::kPositive}};
  for (const TimeLeg& leg : pair23_1) run_time_leg(leg);
  run_event_leg(true, true, "max1");

  // --- New endgame extension. ---
  // Stay in pair-23 through the deep {2,3} encounter near tp = 1.596.
  const TimeLeg post_max1[] = {
      {27, 20, true, LegMode::kPostMax}, {7, 5, true, LegMode::kNegative},
      {29, 20, true, LegMode::kNegative},{3, 2, true, LegMode::kNegative},
      {31, 20, true, LegMode::kNegative},{8, 5, true, LegMode::kNegative},
      {33, 20, true, LegMode::kNegative},{17, 10, true, LegMode::kNegative},
      {7, 4, true, LegMode::kNegative}};
  for (const TimeLeg& leg : post_max1) run_time_leg(leg);
  graph = transform_graph(graph, make_pair23_to_pair13_map());
  check_switch_state(graph, family, false, false, "switch23to13_formA");
  const TimeLeg approach2[] = {
      {9, 5, false, LegMode::kNegative},
      {37, 20, false, LegMode::kNegative},{19, 10, false, LegMode::kNegative}};
  for (const TimeLeg& leg : approach2) run_time_leg(leg);
  run_event_leg(false, false, "min2");
  const TimeLeg out2[] = {
      {39, 20, false, LegMode::kPostMin}, {2, 1, false, LegMode::kPositive},
      {21, 10, false, LegMode::kPositive},{11, 5, false, LegMode::kPositive},
      {23, 10, false, LegMode::kPositive},{12, 5, false, LegMode::kPositive},
      {5, 2, false, LegMode::kPositive},  {13, 5, false, LegMode::kPositive}};
  for (const TimeLeg& leg : out2) run_time_leg(leg);
  run_event_leg(true, false, "max2");
  const TimeLeg approach3[] = {
      {27, 10, false, LegMode::kPostMax}, {14, 5, false, LegMode::kNegative},
      {57, 20, false, LegMode::kNegative},{29, 10, false, LegMode::kNegative}};
  for (const TimeLeg& leg : approach3) run_time_leg(leg);
  run_event_leg(false, false, "min3");
  const TimeLeg out3[] = {
      {59, 20, false, LegMode::kPostMin}, {3, 1, false, LegMode::kPositive}};
  for (const TimeLeg& leg : out3) run_time_leg(leg);
  run_event_leg(true, false, "max3");
  const TimeLeg approach4_prefix[] = {
      {31, 10, false, LegMode::kPostMax}, {63, 20, false, LegMode::kNegative},
      {16, 5, false, LegMode::kNegative}, {13, 4, false, LegMode::kNegative}};
  for (const TimeLeg& leg : approach4_prefix) run_time_leg(leg);
  const bool graph_exchange_sandwich =
      std::getenv("FABLE_ENDGAME_GRAPH_EXCHANGE_SANDWICH") != nullptr;
  if (graph_exchange_sync && graph_exchange_sandwich) {
    throw std::runtime_error(
        "choose either graph exchange synchronization or chart sandwich");
  }
  if (!graph_exchange_sync) {
    const TimeLeg approach4_tail[] = {
        {33, 10, false, LegMode::kNegative},
        {67, 20, false, LegMode::kNegative},
        {17, 5, false, LegMode::kNegative}};
    for (const TimeLeg& leg : approach4_tail) run_time_leg(leg);
  }
  if (graph_exchange_sync) {
    run_time_leg({167, 50, false, LegMode::kNegative});
    const Ival first_exchange_section = -Ival(3) / Ival(5);
    const Vector exchange_entry = graph_hull(graph);
    if (!(exchange_entry[0].rightBound() <
          first_exchange_section.leftBound())) {
      throw std::runtime_error(
          "exchange synchronization did not start before first section");
    }
    // The first section occurs near tp=3.34213; the exact common-clock prefix
    // tp=167/50 remains uniformly before it on the target family and avoids
    // an otherwise needless long C2 integration in regularized time.  The
    // physical-clock family becomes almost tangent to the close pair--23
    // encounter near tp ~= 3.4515.  Synchronizing instead on successive
    // pair--13 LC coordinate sections removes that phase direction while
    // retaining the pair--13 chart needed for its own encounter near
    // tp ~= 3.4695.  This is the same gap-free itinerary already validated
    // by the correlated-C0 driver; project_graph supplies the stronger
    // directional-C2 image and independently audits every intervening tube.
    const Ival exchange_wr_sections[] = {
        first_exchange_section, -Ival(1) / Ival(2),
        -Ival(2) / Ival(5), -Ival(3) / Ival(10),
        -Ival(1) / Ival(5), Ival(0)};
    int ordinal = 0;
    for (const Ival& wr_section : exchange_wr_sections) {
      const std::string label =
          "exchange_section_" + std::to_string(++ordinal);
      graph = project_graph(graph, 0, wr_section, MP, order, tolerance,
                            false, LegMode::kNegative, label.c_str());
      print_leg(label.c_str(), graph);
      const Vector image = graph_hull(graph);
      const DirectLcScalars sc = evaluate_direct_lc(image, family);
      if (!(image[2].leftBound() > 0) ||
          !(sc.selected_radius.leftBound() > 0) ||
          !(sc.r12_squared.leftBound() > 0) ||
          !(sc.r23_squared.leftBound() > 0)) {
        throw std::runtime_error(label +
                                 ": lost orientation or separation");
      }
      if ((graph_exchange_energy_project || graph_exchange_invariant_project) &&
          ordinal >= 4) {
        const std::string projection_label =
            std::string(graph_exchange_invariant_project
                            ? "exchange_invariant_projection_"
                            : "exchange_energy_projection_") +
            std::to_string(ordinal);
        if (graph_exchange_invariant_project) {
          const Vector domain = graph_hull(graph);
          const Ival complement_radius_squared =
              square_interval(domain[5]) + square_interval(domain[6]);
          if (!(complement_radius_squared.leftBound() > 0)) {
            throw std::runtime_error(
                projection_label + ": complement Jacobi vector may vanish");
          }
          std::cout << "ENDGAME_INVARIANT_DOMAIN " << projection_label
                    << " G2=["
                    << bound_double(complement_radius_squared.leftBound())
                    << ","
                    << bound_double(complement_radius_squared.rightBound())
                    << "]\n" << std::flush;
          graph = transform_graph(
              graph, make_pair13_joint_invariant_projection());
        } else {
          graph = transform_graph(graph, make_pair13_energy_projection());
        }
        check_switch_state(graph, family, false, false,
                           projection_label.c_str());
      }
    }
  } else if (graph_exchange_sandwich) {
    // The nearby pair-{2,3} encounter occurs at tp ~= 3.4515 while the
    // selected pair-{1,3} encounter follows at tp ~= 3.4695.  A short
    // pair-{2,3} chart sandwich regularizes the first encounter without
    // abandoning the pair-{1,3} chart needed for the second.  Ordinary
    // reconnaissance selected these rational switch times, but both lifts,
    // every intervening tube, and both noncollision margins are certified
    // below by interval arithmetic.
    run_time_leg({171, 50, false, LegMode::kNegative});
    certify_pair13_to_pair23_form_b_lift(
        graph, family, "exchange_switch13to23_formB");
    graph = transform_graph(
        graph, make_pair13_to_pair23_map_form_b(graph_fixed_energy_h));
    check_switch_state(graph, family, true, false,
                       "exchange_switch13to23_formB");
    run_time_leg({173, 50, true, LegMode::kNegative});
    certify_pair23_to_pair13_form_a_lift(
        graph, family, "exchange_switch23to13_formA");
    graph = transform_graph(
        graph, make_pair23_to_pair13_map(graph_fixed_energy_h));
    check_switch_state(graph, family, false, false,
                       "exchange_switch23to13_formA");
  } else {
    run_time_leg({69, 20, false, LegMode::kNegative});
  }
  run_event_leg(false, false, "min4");
  // The {2,3} binary's first pericenter is near tp = 3.5165, so the Form-B
  // switch must happen at tp = 7/2, between the selected {1,3} pericenter
  // at 3.4695 and that first binary pericenter.
  const TimeLeg out4[] = {{7, 2, false, LegMode::kPostMin}};
  for (const TimeLeg& leg : out4) run_time_leg(leg);
  graph = transform_graph(
      graph, make_pair13_to_pair23_map_form_b(graph_fixed_energy_h));
  check_switch_state(graph, family, true, true, "switch13to23_formB");
  const bool graph_pair23_sync =
      std::getenv("FABLE_ENDGAME_GRAPH_PAIR23_SYNC") != nullptr;
  if (graph_pair23_sync) {
    struct GraphSection {
      Ival value;
      capd::poincare::CrossingDirection direction;
    };
    // Ordinary branch reconnaissance supplies only this itinerary.  Each
    // crossing below is proved by CAPD and every intervening tube is audited
    // by project_graph.  The final +3/20 crossing occurs near t=3.8416,
    // immediately before the fixed terminal time 77/20 where the ordinary
    // phase-robust margin is already comfortably positive.
    const GraphSection sections[] = {
        {-Ival(3) / Ival(20), MP}, {-Ival(1) / Ival(10), MP},
        {-Ival(1) / Ival(20), MP}, {Ival(0), MP},
        {Ival(1) / Ival(20), MP},  {Ival(1) / Ival(10), MP},
        {Ival(3) / Ival(20), MP},  {Ival(3) / Ival(20), PM},
        {Ival(1) / Ival(10), PM},  {Ival(1) / Ival(20), PM},
        {Ival(0), PM},             {-Ival(1) / Ival(20), PM},
        {-Ival(1) / Ival(10), PM}, {-Ival(3) / Ival(20), PM},
        {-Ival(3) / Ival(20), MP}, {-Ival(1) / Ival(10), MP},
        {-Ival(1) / Ival(20), MP}, {Ival(0), MP},
        {Ival(1) / Ival(20), MP},  {Ival(1) / Ival(10), MP},
        {Ival(3) / Ival(20), MP}};
    int ordinal = 0;
    for (const GraphSection& section : sections) {
      const std::string label =
          "pair23_section_" + std::to_string(++ordinal);
      graph = project_graph(graph, 0, section.value, section.direction,
                            order, tolerance, true, LegMode::kPositive,
                            label.c_str());
      print_leg(label.c_str(), graph);
    }
    run_time_leg({77, 20, true, LegMode::kPositive});
  } else {
    const TimeLeg escape_leg[] = {
        {18, 5, true, LegMode::kPositive},  {37, 10, true, LegMode::kPositive},
        {19, 5, true, LegMode::kPositive},  {39, 10, true, LegMode::kPositive},
        {4, 1, true, LegMode::kPositive},   {41, 10, true, LegMode::kPositive},
        {21, 5, true, LegMode::kPositive},  {43, 10, true, LegMode::kPositive},
        {22, 5, true, LegMode::kPositive},  {9, 2, true, LegMode::kPositive}};
    for (const TimeLeg& leg : escape_leg) run_time_leg(leg);
  }

  if (!terminal_phase_robust_check(graph)) {
    std::cout << "FAIL_MIDDLE_ESCAPE_ENDGAME u=[" << p << "/" << q << ","
              << p2 << "/" << q2 << "]\n";
    return 1;
  }
  std::cout << "PASS_MIDDLE_ESCAPE_ENDGAME u=[" << p << "/" << q << ","
            << p2 << "/" << q2 << "] t_terminal="
            << (graph_pair23_sync ? "77/20" : "9/2") << " eta=4"
            << " method=CAPD-6.1.0-MPFR"
            << " capd_commit=731079217a9254ea2948d742df2b170895effe7f\n";
  return 0;
}

}  // namespace

int main(int argc, char** argv) {
  if (argc < 5) {
    std::cerr << "usage: middle_escape_endgame_capd P Q P2 Q2"
                 " [PREC TOL ORDER]\n";
    return 2;
  }
  const long p = std::atol(argv[1]);
  const long q = std::atol(argv[2]);
  const long p2 = std::atol(argv[3]);
  const long q2 = std::atol(argv[4]);
  const int precision = argc > 5 ? std::atoi(argv[5]) : 160;
  const double tolerance = argc > 6 ? std::atof(argv[6]) : 1e-24;
  const int order = argc > 7 ? std::atoi(argv[7]) : 32;
  capd::MpFloat::setDefaultPrecision(precision);
  try {
    const Ival lower = Ival(p) / Ival(q);
    const Ival upper = Ival(p2) / Ival(q2);
    const Ival u_param = Ival(lower.leftBound(), upper.rightBound());
    if (!(u_param.leftBound() < u_param.rightBound()) ||
        !(u_param.leftBound() > 0) || !(u_param.rightBound() < 1)) {
      std::cerr << "FAIL invalid Euclid-parameter interval\n";
      return 2;
    }
    const bool synchronize_exchange =
        std::getenv("FABLE_ENDGAME_SYNC") != nullptr;
    const bool synchronize_preswitch =
        std::getenv("FABLE_ENDGAME_PRESWITCH") != nullptr;
    const bool structured_form_b =
        std::getenv("FABLE_ENDGAME_STRUCTURED_SWITCH") != nullptr;
    const bool synchronize_pair23 =
        std::getenv("FABLE_ENDGAME_PAIR23_SYNC") != nullptr;
    const bool structured_section =
        std::getenv("FABLE_ENDGAME_STRUCTURED_SECTION") != nullptr;
    const bool graph_pair23_sync =
        std::getenv("FABLE_ENDGAME_GRAPH_PAIR23_SYNC") != nullptr;
    const bool graph_tangent_split =
        std::getenv("FABLE_ENDGAME_GRAPH_TANGENT_SPLIT") != nullptr;
    const bool graph_c2 =
        std::getenv("FABLE_ENDGAME_GRAPH_C2") != nullptr;
    const bool graph_exchange_sandwich =
        std::getenv("FABLE_ENDGAME_GRAPH_EXCHANGE_SANDWICH") != nullptr;
    const bool graph_fixed_energy_h =
        std::getenv("FABLE_ENDGAME_GRAPH_FIXED_ENERGY_H") != nullptr;
    const bool graph_exchange_sync =
        std::getenv("FABLE_ENDGAME_GRAPH_EXCHANGE_SYNC") != nullptr;
    const bool graph_exchange_energy_project =
        std::getenv("FABLE_ENDGAME_GRAPH_EXCHANGE_ENERGY_PROJECT") != nullptr;
    const bool graph_exchange_invariant_project =
        std::getenv("FABLE_ENDGAME_GRAPH_EXCHANGE_INVARIANT_PROJECT") != nullptr;
    if (graph_exchange_energy_project && !graph_exchange_sync) {
      throw std::runtime_error(
          "graph exchange energy projection requires exchange synchronization");
    }
    if (graph_exchange_invariant_project && !graph_exchange_sync) {
      throw std::runtime_error(
          "graph exchange invariant projection requires exchange synchronization");
    }
    if (graph_exchange_energy_project && graph_exchange_invariant_project) {
      throw std::runtime_error(
          "choose either energy-only or joint invariant exchange projection");
    }
    std::cout << "ENDGAME_PARAMS precision_bits=" << precision
              << " tolerance=" << tolerance << " order=" << order
              << " sync_exchange=" << (synchronize_exchange ? 1 : 0)
              << " sync_preswitch=" << (synchronize_preswitch ? 1 : 0)
              << " structured_form_b=" << (structured_form_b ? 1 : 0)
              << " sync_pair23=" << (synchronize_pair23 ? 1 : 0)
              << " structured_section=" << (structured_section ? 1 : 0)
              << " graph_pair23_sync=" << (graph_pair23_sync ? 1 : 0)
              << " graph_tangent_split=" << (graph_tangent_split ? 1 : 0)
              << " graph_c2=" << (graph_c2 ? 1 : 0)
              << " graph_exchange_sandwich="
              << (graph_exchange_sandwich ? 1 : 0)
              << " graph_fixed_energy_h="
              << (graph_fixed_energy_h ? 1 : 0)
              << " graph_exchange_sync="
              << (graph_exchange_sync ? 1 : 0)
              << " graph_exchange_energy_project="
              << (graph_exchange_energy_project ? 1 : 0)
              << " graph_exchange_invariant_project="
              << (graph_exchange_invariant_project ? 1 : 0)
              << " driver=middle_escape_endgame_capd/v23-joint-invariant-2026-08-26"
              << "\n" << std::flush;
    const bool graph_mode =
        std::getenv("FABLE_ENDGAME_GRAPH") != nullptr;
    return graph_mode
               ? run_endgame(u_param, p, q, p2, q2, order, tolerance)
               : run_endgame_c0(u_param, p, q, p2, q2, order, tolerance);
  } catch (const std::exception& error) {
    std::cout << "FAIL_MIDDLE_ESCAPE_ENDGAME(exception:" << error.what()
              << ")\n";
    return 1;
  }
}
