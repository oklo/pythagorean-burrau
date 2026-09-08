// Rigorous nonperiodicity certificate for a closed real parameter tile of the
// tied Pythagorean family inside the prompt-ejection window near u = 0.40,
// integrated in the project's pair-{1,3} Levi-Civita chart with u carried as
// a frozen state coordinate (regularized time synchronizes the {1,3} passage
// across the tile, which defeats the fixed-clock representation).
//
// Mathematical basis (paper/sections/reductions.tex and docs/):
//   * validated-cover criterion (Corollary): launch window U < 2 U0, then on
//     every accepted-step enclosure at least one of  K > 0,  dI/dt != 0,
//     (z, P) != 0  (LC brake residual, docs/FABLE_EVENT_REDUCTION.md);
//   * terminal escape lemma, phase-robust form (docs/FABLE_MIDDLE_ESCAPE.md
//     section 3a) with binary {1,3} (masses A and 1, M = A+1), escaper body 2
//     (mass B): the transported LC energy hh is the inner specific energy,
//     so only hh and the outer variables (G, P) enter.  Checked on the set
//     hull, hence for every fiber of the tile at once.
//   * every intervening sigma-time is covered by the step enclosures; the LC
//     chart is regular wherever the unselected separations are positive,
//     which is verified on every step.
//
// Chart, field, launch graph and scalar audits are copied from the committed
// src/fable/verification/middle_escape_endgame_capd.cpp (pair-{1,3} direct
// LC chart), retargeted to CAPD's native double interval types.
//
// Usage: iso_window_lc_capd P Q P2 Q2 [ORDER TOL TP_MAX TP_SWITCH1 TP_SWITCH2 MIN_MARGIN]
// The terminal check is accepted at the first sigma-step whose hull margin
// exceeds MIN_MARGIN (any positive margin is rigorous; the floor is prudence).
// Chart itinerary: pair-{1,3} from launch to physical time TP_SWITCH1, pair-{2,3}
// through the {2,3} passage to TP_SWITCH2, then pair-{1,3} to the terminal check.
// Output ends with PASS_ISO_WINDOW_LC or FAIL ...; fail-closed.
// Dependency pin: CAPD 6.1.0 commit 731079217a9254ea2948d742df2b170895effe7f,
// NATIVE build (-frounding-math -D__USE_NATIVE__).

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "capd/capdlib.h"

namespace {

typedef capd::interval Ival;
typedef capd::IMap Map;
typedef capd::IOdeSolver Solver;
typedef capd::IVector Vector;
typedef capd::IMatrix Matrix;
typedef capd::C0TripletonSet Set;

struct Family {
  Ival a, b, m12, total, mu1, mu2, u0, alpha, beta, m13, inv_m13, ag, bg;
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

const char* kDirectLcVars = "var:wr,wi,zr,zi,hh,cgx,cgy,cpx,cpy,tp,ww,jd;";

// Pair-{1,3} direct Levi-Civita field: g = q3 - q1 = w^2, dt = |w|^2 dsigma,
// z = dw/dsigma, hh = LC pair energy, G = q2 - C13, P = dG/dt, tp physical
// time, ww = u frozen, jd = dI/dt.  Verbatim from the committed driver.
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
  const std::string d23x = "(cgx+(" + inv_m13 + "-1)*" + gx + ")";
  const std::string d23y = "(cgy+(" + inv_m13 + "-1)*" + gy + ")";
  const std::string r12sq = "(" + d21x + "^2+" + d21y + "^2)";
  const std::string r23sq = "(" + d23x + "^2+" + d23y + "^2)";
  const std::string ir12 = "(" + r12sq + "*sqrt(" + r12sq + "))";
  const std::string ir23 = "(" + r23sq + "*sqrt(" + r23sq + "))";
  const std::string fx = "(" + mb + "*(" + d23x + "/" + ir23 + "-" + d21x + "/" + ir12 + "))";
  const std::string fy = "(" + mb + "*(" + d23y + "/" + ir23 + "-" + d21y + "/" + ir12 + "))";
  const std::string gddx = "(-" + total_over_m13 + "*(" + ma + "*" + d21x + "/" + ir12 + "+" + d23x + "/" + ir23 + "))";
  const std::string gddy = "(-" + total_over_m13 + "*(" + ma + "*" + d21y + "/" + ir12 + "+" + d23y + "/" + ir23 + "))";
  const std::string ab = "(" + ma + "*" + mb + ")";
  const std::string u0 = "(" + ab + "+1/" + ab + ")";
  const std::string jd_sigma = "(2*(" + ab + "*" + w2 + "/sqrt(" + r12sq + ")+" + ma + "+" + mb + "*" + w2 + "/sqrt(" + r23sq + "))-4*" + u0 + "*" + w2 + ")";
  return Map(std::string(kDirectLcVars) + "fun:zr,zi," + "(hh/2)*wr+(" + w2 + "/2)*(wr*" + fx + "+wi*" + fy + ")," + "(hh/2)*wi+(" + w2 + "/2)*(wr*" + fy + "-wi*" + fx + ")," + "2*((wr*zr-wi*zi)*" + fx + "+(wr*zi+wi*zr)*" + fy + ")," + w2 + "*cpx," + w2 + "*cpy," + w2 + "*" + gddx + "," + w2 + "*" + gddy + "," + w2 + ",0," + jd_sigma + ";");
}

// Exact tied launch in the chart as a function of ww (verbatim).
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
  const std::string tied_yx = "(2*ww*(1-ww^2)*(ww^2+2*ww-1)/(" + qden + "^2*" + pden + "))";
  const std::string tied_yy = "(2*ww*(1-ww^2)/" + qden + "^2)";
  const std::string gx = "(" + mb + "^2)";
  const std::string gy = "(" + ma + "*" + mb + ")";
  const std::string wr = "sqrt((" + mb + "+" + gx + ")/2)";
  const std::string wi = "(" + gy + "/(2*" + wr + "))";
  const std::string hh = "(-" + m13 + "/" + mb + ")";
  const std::string cgx = "(" + ag + "+" + bg + "*" + tied_yx + ")";
  const std::string cgy = "(" + bg + "*" + tied_yy + ")";
  (void)alpha;
  return Map(std::string(kDirectLcVars) + "fun:" + wr + "," + wi + ",0,0," + hh + "," + cgx + "," + cgy + ",0,0,0,0,0;");
}

bool contains_zero(const Ival& x) { return !(x.leftBound() > 0) && !(x.rightBound() < 0); }

double hull_width(const Vector& s, int n) {
  double w = 0;
  for (int i = 0; i < n; ++i) w = std::max(w, s[i].rightBound() - s[i].leftBound());
  return w;
}

struct DirectLcScalars {
  Ival selected_radius;  // |g| = r13 (not squared)
  Ival r12_squared, r23_squared, potential, i_dot, kinetic;
};

DirectLcScalars evaluate_direct_lc(const Vector& s, const Family& f) {
  DirectLcScalars out;
  const Ival &wr = s[0], &wi = s[1];
  const Ival gx = wr * wr - wi * wi;
  const Ival gy = 2 * wr * wi;
  out.selected_radius = wr * wr + wi * wi;
  const Ival gdx = 2 * (wr * s[2] - wi * s[3]) / out.selected_radius;
  const Ival gdy = 2 * (wr * s[3] + wi * s[2]) / out.selected_radius;
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
  out.i_dot = s[11];
  out.kinetic = (f.mu1 * (xd_x * xd_x + xd_y * xd_y) + f.mu2 * (yd_x * yd_x + yd_y * yd_y)) / 2;
  out.potential = Ival(0);
  if (out.selected_radius.leftBound() > 0 && out.r12_squared.leftBound() > 0 && out.r23_squared.leftBound() > 0) {
    out.potential = f.a * f.b / sqrt(out.r12_squared) + f.a / out.selected_radius + f.b / sqrt(out.r23_squared);
  }
  return out;
}


// Pair-{2,3} direct Levi-Civita field (verbatim from the committed driver):
// g = q3 - q2 = w^2, G = q1 - C23.
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
  const std::string d13x = "(cgx+(" + inv_m23 + "-1)*" + gx + ")";
  const std::string d13y = "(cgy+(" + inv_m23 + "-1)*" + gy + ")";
  const std::string r12sq = "(" + d12x + "^2+" + d12y + "^2)";
  const std::string r13sq = "(" + d13x + "^2+" + d13y + "^2)";
  const std::string ir12 = "(" + r12sq + "*sqrt(" + r12sq + "))";
  const std::string ir13 = "(" + r13sq + "*sqrt(" + r13sq + "))";
  const std::string fx = "(" + ma + "*(" + d13x + "/" + ir13 + "-" + d12x + "/" + ir12 + "))";
  const std::string fy = "(" + ma + "*(" + d13y + "/" + ir13 + "-" + d12y + "/" + ir12 + "))";
  const std::string gddx = "(-" + total_over_m23 + "*(" + mb + "*" + d12x + "/" + ir12 + "+" + d13x + "/" + ir13 + "))";
  const std::string gddy = "(-" + total_over_m23 + "*(" + mb + "*" + d12y + "/" + ir12 + "+" + d13y + "/" + ir13 + "))";
  const std::string ab = "(" + ma + "*" + mb + ")";
  const std::string u0 = "(" + ab + "+1/" + ab + ")";
  const std::string jd_sigma = "(2*(" + ab + "*" + w2 + "/sqrt(" + r12sq + ")+" + mb + "+" + ma + "*" + w2 + "/sqrt(" + r13sq + "))-4*" + u0 + "*" + w2 + ")";
  return Map(std::string(kDirectLcVars) + "fun:zr,zi," + "(hh/2)*wr+(" + w2 + "/2)*(wr*" + fx + "+wi*" + fy + ")," + "(hh/2)*wi+(" + w2 + "/2)*(wr*" + fy + "-wi*" + fx + ")," + "2*((wr*zr-wi*zi)*" + fx + "+(wr*zi+wi*zr)*" + fy + ")," + w2 + "*cpx," + w2 + "*cpy," + w2 + "*" + gddx + "," + w2 + "*" + gddy + "," + w2 + ",0," + jd_sigma + ";");
}

// Exact chart switch pair-{1,3} -> pair-{2,3}.  Form A lift w_r = sqrt((|g|+g_x)/2)
// (valid off the negative real g-axis); Form B lift w_i = sqrt((|g|-g_x)/2)
// (valid off the positive real axis).  Verbatim from the committed driver.
Map make_pair13_to_pair23_map(bool form_b) {
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
  std::string new_wr, new_wi;
  if (form_b) {
    new_wi = "sqrt((" + abs_g + "-" + gx + ")/2)";
    new_wr = "(" + gy + "/(2*" + new_wi + "))";
  } else {
    new_wr = "sqrt((" + abs_g + "+" + gx + ")/2)";
    new_wi = "(" + gy + "/(2*" + new_wr + "))";
  }
  const std::string new_zr = "((" + new_wr + "*" + gdx + "+" + new_wi + "*" + gdy + ")/2)";
  const std::string new_zi = "((" + new_wr + "*" + gdy + "-" + new_wi + "*" + gdx + ")/2)";
  const std::string new_h = "((" + gdx + "^2+" + gdy + "^2)/2-" + m23 + "/" + abs_g + ")";
  const std::string new_gx = "(-" + old_xx + "-" + inv_m23 + "*" + gx + ")";
  const std::string new_gy = "(-" + old_xy + "-" + inv_m23 + "*" + gy + ")";
  const std::string new_px = "(-" + old_xdx + "-" + inv_m23 + "*" + gdx + ")";
  const std::string new_py = "(-" + old_xdy + "-" + inv_m23 + "*" + gdy + ")";
  return Map(std::string(kDirectLcVars) + "fun:" + new_wr + "," + new_wi + "," + new_zr + "," + new_zi + "," + new_h + "," + new_gx + "," + new_gy + "," + new_px + "," + new_py + ",tp,ww,jd;");
}

// Exact chart switch pair-{2,3} -> pair-{1,3} (velocity form of h), with the
// same Form A / Form B lift choice.  Verbatim structure from the committed driver.
Map make_pair23_to_pair13_map(bool form_b) {
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
  std::string new_wr, new_wi;
  if (form_b) {
    new_wi = "sqrt((" + abs_g + "-" + gx + ")/2)";
    new_wr = "(" + gy + "/(2*" + new_wi + "))";
  } else {
    new_wr = "sqrt((" + abs_g + "+" + gx + ")/2)";
    new_wi = "(" + gy + "/(2*" + new_wr + "))";
  }
  const std::string new_zr = "((" + new_wr + "*" + gdx + "+" + new_wi + "*" + gdy + ")/2)";
  const std::string new_zi = "((" + new_wr + "*" + gdy + "-" + new_wi + "*" + gdx + ")/2)";
  const std::string new_h = "((" + gdx + "^2+" + gdy + "^2)/2-" + m13 + "/" + abs_g + ")";
  const std::string d12x = "(cgx+" + inv_m23 + "*" + old_gx + ")";
  const std::string d12y = "(cgy+" + inv_m23 + "*" + old_gy + ")";
  const std::string d12dx = "(cpx+" + inv_m23 + "*" + old_gdx + ")";
  const std::string d12dy = "(cpy+" + inv_m23 + "*" + old_gdy + ")";
  const std::string new_gx = "(-" + d12x + "-" + inv_m13 + "*" + gx + ")";
  const std::string new_gy = "(-" + d12y + "-" + inv_m13 + "*" + gy + ")";
  const std::string new_px = "(-" + d12dx + "-" + inv_m13 + "*" + gdx + ")";
  const std::string new_py = "(-" + d12dy + "-" + inv_m13 + "*" + gdy + ")";
  return Map(std::string(kDirectLcVars) + "fun:" + new_wr + "," + new_wi + "," + new_zr + "," + new_zi + "," + new_h + "," + new_gx + "," + new_gy + "," + new_px + "," + new_py + ",tp,ww,jd;");
}

// Scalars in the pair-{2,3} chart: selected_radius = r23, r12_squared, r23_squared
// slot holds r13^2 (named generically below as unselected squares).
DirectLcScalars evaluate_pair23_lc(const Vector& s, const Family& f) {
  DirectLcScalars out;
  const Ival &wr = s[0], &wi = s[1];
  const Ival gx = wr * wr - wi * wi;
  const Ival gy = 2 * wr * wi;
  out.selected_radius = wr * wr + wi * wi;
  const Ival m23 = f.b + 1;
  const Ival inv_m23 = 1 / m23;
  const Ival gdx = 2 * (wr * s[2] - wi * s[3]) / out.selected_radius;
  const Ival gdy = 2 * (wr * s[3] + wi * s[2]) / out.selected_radius;
  const Ival d12x = s[5] + inv_m23 * gx;
  const Ival d12y = s[6] + inv_m23 * gy;
  const Ival d13x = s[5] + (inv_m23 - 1) * gx;
  const Ival d13y = s[6] + (inv_m23 - 1) * gy;
  out.r12_squared = d12x * d12x + d12y * d12y;
  out.r23_squared = d13x * d13x + d13y * d13y;  // r13^2 in this chart
  const Ival pair_mu = f.b / m23;
  const Ival complement_mu = f.a * m23 / f.total;
  out.i_dot = s[11];
  out.kinetic = (pair_mu * (gdx * gdx + gdy * gdy) + complement_mu * (s[7] * s[7] + s[8] * s[8])) / 2;
  out.potential = Ival(0);
  if (out.selected_radius.leftBound() > 0 && out.r12_squared.leftBound() > 0 && out.r23_squared.leftBound() > 0) {
    out.potential = f.a * f.b / sqrt(out.r12_squared) + f.b / out.selected_radius + f.a / sqrt(out.r23_squared);
  }
  return out;
}

// Rigorous mean-value image of a tripleton under an algebraic chart map
// (verbatim from the committed driver).
Set mean_value_switch(const Set& set, Map& transformation) {
  const Vector x = set.get_x();
  Vector hull(set);
  hull = capd::vectalg::intervalHull(hull, x);
  const Matrix c_matrix = set.get_C();
  const Vector r0 = set.get_r0();
  const int dimension = hull.dimension();
  const Vector b_part = set.get_B() * set.get_r();
  const Vector q_part = set.m_Q * set.m_q;
  Vector remainder(dimension);
  for (int i = 0; i < dimension; ++i) {
    if (!capd::intervals::intersection(b_part[i], q_part[i], remainder[i])) {
      throw std::runtime_error("empty tripleton remainder intersection");
    }
  }
  const Vector image_x = transformation(x);
  const Matrix derivative = transformation.derivative(hull);
  const Matrix dc = derivative * c_matrix;
  const Vector d_remainder = derivative * remainder;
  Matrix dc_mid(dimension, dimension);
  Vector spill(dimension);
  for (int i = 0; i < dimension; ++i) {
    spill[i] = Ival(0);
    for (int j = 0; j < dimension; ++j) {
      const Ival mid = (Ival(dc[i][j].leftBound()) + Ival(dc[i][j].rightBound())) / 2;
      dc_mid[i][j] = mid;
      spill[i] += (dc[i][j] - mid) * r0[j];
    }
  }
  Vector new_x(dimension), new_r(dimension);
  for (int i = 0; i < dimension; ++i) {
    const Ival mid = (Ival(image_x[i].leftBound()) + Ival(image_x[i].rightBound())) / 2;
    new_x[i] = mid;
    new_r[i] = d_remainder[i] + (image_x[i] - mid) + spill[i];
  }
  return Set(new_x, dc_mid, r0, new_r, set.getCurrentTime());
}

// Choose the square-root lift for the target pair vector g = (gx, gy):
// Form A when (|g|+gx)/2 is bounded further from zero than (|g|-gx)/2.
bool choose_form_b(const Ival& gx, const Ival& gy) {
  const Ival abs_g = sqrt(gx * gx + gy * gy);
  const Ival arg_a = (abs_g + gx) / 2, arg_b = (abs_g - gx) / 2;
  return arg_b.leftBound() > arg_a.leftBound();
}

bool lc_residual_excludes_brake(const Vector& s) {
  // physical pair velocity 2 w z / |w|^2 and complementary velocity P:
  // a labelled brake forces zr = zi = Px = Py = 0.
  return !contains_zero(s[2]) || !contains_zero(s[3]) || !contains_zero(s[7]) || !contains_zero(s[8]);
}

// Phase-robust terminal escape check, binary {1,3}, escaper 2 (eta list).
double terminal_margin(const Vector& s, const Family& f, double* eta_used, double* det) {
  const Ival M = f.m13, mc = f.b;
  const Ival h = s[4];
  const Ival gx = s[5], gy = s[6], px = s[7], py = s[8];
  const Ival rho = sqrt(gx * gx + gy * gy);
  const Ival rhodot = (gx * px + gy * py) / rho;
  double best = -1e300;
  const double etas[7] = {1, 1.5, 2, 3, 4, 6, 8};
  for (int k = 0; k < 7; ++k) {
    const Ival eta(etas[k]);
    const Ival R = M / eta;
    const Ival s0 = rho - R;
    if (!(s0.leftBound() > 0) || !(rhodot.leftBound() > 0)) continue;
    const Ival delta = rhodot * rhodot / 2 - (M + mc) / s0;
    if (!(delta.leftBound() > 0)) continue;
    const Ival allowance = mc * sqrt(2 * M * R) / (sqrt(2 * delta) * s0 * s0);
    const Ival margin = -eta - h - allowance;
    if (margin.leftBound() > best) {
      best = margin.leftBound();
      *eta_used = etas[k];
      det[0] = s0.leftBound(); det[1] = rhodot.leftBound(); det[2] = delta.leftBound(); det[3] = h.rightBound(); det[4] = allowance.rightBound();
    }
  }
  return best;
}

Set make_launch_set(const Ival& u_range) {
  const int n = 12;
  const Ival u_center = Ival((u_range.leftBound() + u_range.rightBound()) / 2);
  Vector center_input(n), range_input(n);
  for (int i = 0; i < n; ++i) { center_input[i] = Ival(0); range_input[i] = Ival(0); }
  center_input[10] = u_center;
  range_input[10] = u_range;
  Map launch_map = make_direct_lc_initial_graph_field();
  const Vector anchor_image = launch_map(center_input);
  const Matrix launch_derivative = launch_map.derivative(range_input);
  const Ival deviation = u_range - u_center;
  Vector x(n), r0(n), r(n);
  Matrix c = Matrix::Identity(n), b = Matrix::Identity(n);
  for (int row = 0; row < n; ++row) {
    const double xm = (anchor_image[row].leftBound() + anchor_image[row].rightBound()) / 2;
    Ival raw = launch_derivative[row][10];
    if (row == 10) { raw = Ival(1); }
    const double cm = (raw.leftBound() + raw.rightBound()) / 2;
    x[row] = Ival(xm);
    c[row][0] = Ival(cm);
    r[row] = (anchor_image[row] - Ival(xm)) + (raw - Ival(cm)) * deviation;
    if (row == 10) r[row] = Ival(0);
    r[row] = capd::intervals::intervalHull(r[row], Ival(0));
    r0[row] = Ival(0);
  }
  x[10] = u_center;
  r0[0] = deviation;
  return Set(x, c, r0, b, r, Ival(0));
}

int run(long p, long q, long p2, long q2, int order, double tol, double tp_max, double tp_switch1, double tp_switch2, double min_margin) {
  std::cout << std::setprecision(17);
  const Ival a = Ival(p) / Ival(q);
  const Ival b = Ival(p2) / Ival(q2);
  if (!(a.rightBound() < b.leftBound())) throw std::runtime_error("empty or inverted tile");
  const Ival u_range(a.leftBound(), b.rightBound());
  const Family family = make_family(u_range);
  std::cout << "TILE u in [" << u_range.leftBound() << "," << u_range.rightBound() << "] width=" << (u_range.rightBound() - u_range.leftBound()) << "\n";
  Set set = make_launch_set(u_range);
  {
    const Vector hull(set);
    if (!(hull[10].leftBound() <= u_range.leftBound() && hull[10].rightBound() >= u_range.rightBound()))
      throw std::runtime_error("launch set does not contain the tile in u");
    std::cout << "LAUNCH hull width=" << hull_width(hull, 12) << "\n";
  }
  Map fields[2] = {make_direct_lc_field(), make_pair23_lc_field()};
  const Ival two_u0 = 2 * family.u0;
  bool launch_phase = true;
  long steps = 0, retries = 0;
  double max_hull = 0, min_unselected = 1e300, min_selected = 1e300, min_K = 1e300, tp_launch_end = 0;
  const bool verbose = std::getenv("ISO_VERBOSE") != nullptr;
  const double switch_times[2] = {tp_switch1, tp_switch2};
  for (int phase = 0; phase < 3; ++phase) {
    const bool pair23 = (phase == 1);
    if (phase > 0) {
      // choose lift form from the target pair vector on the hull, then switch
      const Vector hull(set);
      const Family fh = family;
      Ival gx, gy;
      if (phase == 1) {
        const Ival wr = hull[0], wi = hull[1];
        const Ival ogx = wr * wr - wi * wi, ogy = 2 * wr * wi;
        const Ival xx = hull[5] + fh.inv_m13 * ogx, xy = hull[6] + fh.inv_m13 * ogy;
        gx = ogx - xx; gy = ogy - xy;  // g23 = g13 - X13
      } else {
        const Ival wr = hull[0], wi = hull[1];
        const Ival ogx = wr * wr - wi * wi, ogy = 2 * wr * wi;
        const Ival inv_m23 = 1 / (fh.b + 1);
        gx = -(hull[5] + (inv_m23 - 1) * ogx); gy = -(hull[6] + (inv_m23 - 1) * ogy);  // g13 = -(d13)
      }
      const bool form_b = choose_form_b(gx, gy);
      Map transformation = (phase == 1) ? make_pair13_to_pair23_map(form_b) : make_pair23_to_pair13_map(form_b);
      set = mean_value_switch(set, transformation);
      const Vector switched(set);
      const DirectLcScalars sc = pair23 ? evaluate_pair23_lc(switched, family) : evaluate_direct_lc(switched, family);
      if (!(sc.selected_radius.leftBound() > 0) || !(sc.r12_squared.leftBound() > 0) || !(sc.r23_squared.leftBound() > 0))
        throw std::runtime_error("switch lost separation");
      std::cout << "SWITCH to " << (pair23 ? "pair23" : "pair13") << " form=" << (form_b ? "B" : "A") << " tp=[" << switched[9].leftBound() << "," << switched[9].rightBound() << "] hull=" << hull_width(switched, 12) << "\n";
    }
    Solver solver(fields[pair23 ? 1 : 0], order);
    solver.setAbsoluteTolerance(tol);
    solver.setRelativeTolerance(tol);
    for (;;) {
      const Vector before(set);
      const DirectLcScalars pre = pair23 ? evaluate_pair23_lc(before, family) : evaluate_direct_lc(before, family);
      if (!(pre.selected_radius.leftBound() > 0) || !(pre.r12_squared.leftBound() > 0) || !(pre.r23_squared.leftBound() > 0))
        throw std::runtime_error("lost pre-step separation");
      const double w_abs = std::sqrt(std::max(1e-12, pre.selected_radius.leftBound()));
      const double unselected = std::sqrt(std::max(1e-12, std::min(pre.r12_squared.leftBound(), pre.r23_squared.leftBound())));
      const double w2_lower = std::max(1e-12, pre.selected_radius.leftBound());
      const double unselected_cap = unselected * std::sqrt(unselected) / (40.0 * w2_lower);
      double cap = std::max(1.0 / 20000.0, std::min(std::min(w_abs / 24.0, unselected_cap), 1.0 / 100.0));
      for (;;) {
        Set backup(set);
        try {
          solver.setMaxStep(Ival(cap));
          set.move(solver);
          break;
        } catch (const std::exception&) {
          set = backup;
          if (++retries > 200000 || cap < 1e-14) throw;
          cap /= 2;
        }
      }
      ++steps;
      const Vector enc = set.getLastEnclosure();
      const DirectLcScalars sc = pair23 ? evaluate_pair23_lc(enc, family) : evaluate_direct_lc(enc, family);
      if (!(sc.selected_radius.leftBound() > 0) || !(sc.r12_squared.leftBound() > 0) || !(sc.r23_squared.leftBound() > 0))
        throw std::runtime_error("possible collision at step " + std::to_string(steps));
      min_selected = std::min(min_selected, sc.selected_radius.leftBound());
      min_unselected = std::min(min_unselected, std::sqrt(std::min(sc.r12_squared.leftBound(), sc.r23_squared.leftBound())));
      const bool concave = sc.potential.rightBound() < two_u0.leftBound();
      const bool obstructed = sc.kinetic.leftBound() > 0 || !contains_zero(sc.i_dot) || lc_residual_excludes_brake(enc);
      bool failed = false;
      if (launch_phase) {
        if (!concave) {
          launch_phase = false;
          tp_launch_end = enc[9].leftBound();
          if (!obstructed) failed = true;
        }
      } else if (!obstructed) {
        failed = true;
      }
      const Vector hull(set);
      max_hull = std::max(max_hull, hull_width(hull, 12));
      if (!launch_phase) min_K = std::min(min_K, sc.kinetic.leftBound());
      if (verbose && (steps % 100 == 0 || failed)) {
        std::cout << "STEP " << steps << " phase=" << phase << " tp=[" << hull[9].leftBound() << "," << hull[9].rightBound() << "] hull=" << hull_width(hull, 12)
                  << " K=[" << sc.kinetic.leftBound() << "," << sc.kinetic.rightBound() << "] sel=" << sc.selected_radius.leftBound()
                  << " unsel=" << std::sqrt(std::min(sc.r12_squared.leftBound(), sc.r23_squared.leftBound())) << " cap=" << cap << "\n";
      }
      if (failed) throw std::runtime_error("brake obstruction lost at step " + std::to_string(steps) + " tp=" + std::to_string(hull[9].leftBound()));
      if (phase < 2 && hull[9].leftBound() >= switch_times[phase]) break;
      if (phase == 2 && !launch_phase && hull[9].leftBound() > 0.6) {
        double eta = 0, det[5] = {0, 0, 0, 0, 0};
        const double margin = terminal_margin(hull, family, &eta, det);
        if (margin > min_margin) {
          std::cout << "STEPS " << steps << " retries=" << retries << " launch_window_end_tp=" << tp_launch_end << " min_selected=" << min_selected
                    << " min_unselected=" << min_unselected << " min_K_after_launch=" << min_K << " max_hull_width=" << max_hull << "\n";
          std::cout << "TERMINAL tp=[" << hull[9].leftBound() << "," << hull[9].rightBound() << "] eta=" << eta << " s0>" << det[0] << " rhodot>" << det[1]
                    << " delta>" << det[2] << " h<" << det[3] << " allowance<" << det[4] << " margin=" << margin << "\n";
          std::cout << "PASS_ISO_WINDOW_LC [" << p << "/" << q << "," << p2 << "/" << q2 << "] margin=" << margin << "\n";
          return 0;
        }
      }
      if (hull[9].leftBound() > tp_max) throw std::runtime_error("terminal check never passed before tp_max");
      if (steps > 400000) throw std::runtime_error("step limit");
    }
  }
  throw std::runtime_error("unreachable");
}

}  // namespace

int main(int argc, char** argv) {
  if (argc < 5) {
    std::cerr << "usage: iso_window_lc_capd P Q P2 Q2 [ORDER TOL TP_MAX]\n";
    return 2;
  }
  try {
    const long p = std::atol(argv[1]), q = std::atol(argv[2]), p2 = std::atol(argv[3]), q2 = std::atol(argv[4]);
    const int order = argc > 5 ? std::atoi(argv[5]) : 20;
    const double tol = argc > 6 ? std::atof(argv[6]) : 1e-14;
    const double tp_max = argc > 7 ? std::atof(argv[7]) : 6.0;
    const double sw1 = argc > 8 ? std::atof(argv[8]) : 0.5025;
    const double sw2 = argc > 9 ? std::atof(argv[9]) : 0.575;
    const double min_margin = argc > 10 ? std::atof(argv[10]) : 0.05;
    return run(p, q, p2, q2, order, tol, tp_max, sw1, sw2, min_margin);
  } catch (const std::exception& e) {
    std::cout << "FAIL " << e.what() << "\n";
    return 1;
  }
}
