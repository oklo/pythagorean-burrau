// General multi-chart Levi-Civita certificate for a closed real parameter tile
// (or a single rational point) of the tied Pythagorean family.
//
// This generalizes iso_window_lc_capd.cpp: any of the three selected-pair
// charts {12, 13, 23} may be used, in any order, with exact algebraic chart
// switches at prescribed physical times, and the terminal escape lemma is
// applied with the current chart's pair as the binary and its complement as
// the escaper.  The mathematical basis, per-step audits, launch enclosure,
// mean-value switch and fail-closed policy are identical to that file (and
// to docs/ISO_WINDOW_INTERVAL.md); only the chart bookkeeping is generic.
//
// Chart p = (i,j) with complement k: state (wr,wi,zr,zi,hh,cgx,cgy,cpx,cpy,tp,ww,jd),
//   g = q_j - q_i = w^2, dt = |w|^2 dsigma, z = dw/dsigma, hh = |g'|^2/2 - M_ij/|g|,
//   G = q_k - (m_i q_i + m_j q_j)/M_ij, P = dG/dt, tp = physical time, ww = u, jd = dI/dt.
//
// Usage: window_lc_capd P Q P2 Q2 ITINERARY [ORDER TOL TP_MAX MIN_MARGIN [PRECISION_BITS (MP build)]]
//   ITINERARY = "13@0,23@0.5025,13@0.575"  (chart@switch physical time; first
//   entry is the launch chart; last chart's complement is the escaper).
//   P/Q == P2/Q2 gives a point certificate for that exact rational.
// Output ends with PASS_WINDOW_LC or FAIL ...
// Dependency pin: CAPD 6.1.0 commit 731079217a9254ea2948d742df2b170895effe7f,
// NATIVE build (-frounding-math -D__USE_NATIVE__).

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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
typedef capd::MpIVector Vector;
typedef capd::MpIMatrix Matrix;
typedef capd::MpC0TripletonSet Set;
inline double LB(const Ival& x) { return toDouble(x.leftBound()); }
inline double UB(const Ival& x) { return toDouble(x.rightBound()); }
inline Ival midpoint(const Ival& x) { return Ival((x.leftBound() + x.rightBound()) / 2); }
#else
typedef capd::interval Ival;
typedef capd::IMap Map;
typedef capd::IOdeSolver Solver;
typedef capd::IVector Vector;
typedef capd::IMatrix Matrix;
typedef capd::C0TripletonSet Set;
inline double LB(const Ival& x) { return x.leftBound(); }
inline double UB(const Ival& x) { return x.rightBound(); }
inline Ival midpoint(const Ival& x) { return Ival((x.leftBound() + x.rightBound()) / 2); }
#endif

const char* kVars = "var:wr,wi,zr,zi,hh,cgx,cgy,cpx,cpy,tp,ww,jd;";

// mass symbol strings in terms of ww = u
const std::string kQ = "(1+ww^2)";
const std::string kMass[3] = {"((1-ww^2)/" + kQ + ")", "(2*ww/" + kQ + ")", "(1)"};

struct Chart {
  int i, j, k;  // 0-based body indices, i<j, k complement
};

Chart chart_of(int code) {
  if (code == 12) return {0, 1, 2};
  if (code == 13) return {0, 2, 1};
  if (code == 23) return {1, 2, 0};
  throw std::runtime_error("unknown chart code");
}
int code_of(const Chart& c) { return (c.i + 1) * 10 + (c.j + 1); }

std::string Mij(const Chart& c) { return "(" + kMass[c.i] + "+" + kMass[c.j] + ")"; }
std::string Mtot() { return "(" + kMass[0] + "+" + kMass[1] + "+1)"; }

// Strings for the physical relative vectors in chart c (positions relative to q_i,
// velocities), given the state names.
struct ChartExpr {
  std::string gx, gy, gdx, gdy, dkix, dkiy, dkjx, dkjy, dkidx, dkidy, dkjdx, dkjdy, w2;
};

ChartExpr chart_expr(const Chart& c) {
  ChartExpr e;
  e.w2 = "(wr^2+wi^2)";
  e.gx = "(wr^2-wi^2)";
  e.gy = "(2*wr*wi)";
  e.gdx = "(2*(wr*zr-wi*zi)/" + e.w2 + ")";
  e.gdy = "(2*(wr*zi+wi*zr)/" + e.w2 + ")";
  const std::string aj = "(" + kMass[c.j] + "/" + Mij(c) + ")";  // m_j/M_ij
  const std::string ai = "(" + kMass[c.i] + "/" + Mij(c) + ")";  // m_i/M_ij
  e.dkix = "(cgx+" + aj + "*" + e.gx + ")";
  e.dkiy = "(cgy+" + aj + "*" + e.gy + ")";
  e.dkjx = "(cgx-" + ai + "*" + e.gx + ")";
  e.dkjy = "(cgy-" + ai + "*" + e.gy + ")";
  e.dkidx = "(cpx+" + aj + "*" + e.gdx + ")";
  e.dkidy = "(cpy+" + aj + "*" + e.gdy + ")";
  e.dkjdx = "(cpx-" + ai + "*" + e.gdx + ")";
  e.dkjdy = "(cpy-" + ai + "*" + e.gdy + ")";
  return e;
}

Map make_field(const Chart& c) {
  const ChartExpr e = chart_expr(c);
  const std::string rki2 = "(" + e.dkix + "^2+" + e.dkiy + "^2)";
  const std::string rkj2 = "(" + e.dkjx + "^2+" + e.dkjy + "^2)";
  const std::string iki = "(" + rki2 + "*sqrt(" + rki2 + "))";
  const std::string ikj = "(" + rkj2 + "*sqrt(" + rkj2 + "))";
  const std::string mk = kMass[c.k];
  const std::string fx = "(" + mk + "*(" + e.dkjx + "/" + ikj + "-" + e.dkix + "/" + iki + "))";
  const std::string fy = "(" + mk + "*(" + e.dkjy + "/" + ikj + "-" + e.dkiy + "/" + iki + "))";
  const std::string tot_over = "(" + Mtot() + "/" + Mij(c) + ")";
  const std::string gddx = "(-" + tot_over + "*(" + kMass[c.i] + "*" + e.dkix + "/" + iki + "+" + kMass[c.j] + "*" + e.dkjx + "/" + ikj + "))";
  const std::string gddy = "(-" + tot_over + "*(" + kMass[c.i] + "*" + e.dkiy + "/" + iki + "+" + kMass[c.j] + "*" + e.dkjy + "/" + ikj + "))";
  const std::string ab = "(" + kMass[0] + "*" + kMass[1] + ")";
  const std::string u0 = "(" + ab + "+1/" + ab + ")";
  // |w|^2 * (2U - 4U0), U = m_i m_j/|g| + m_i m_k/|d_ki| + m_j m_k/|d_kj|, |g| = |w|^2
  const std::string jd_sigma = "(2*(" + kMass[c.i] + "*" + kMass[c.j] + "+" + e.w2 + "*(" + kMass[c.i] + "*" + mk + "/sqrt(" + rki2 + ")+" + kMass[c.j] + "*" + mk + "/sqrt(" + rkj2 + ")))-4*" + u0 + "*" + e.w2 + ")";
  return Map(std::string(kVars) + "fun:zr,zi," + "(hh/2)*wr+(" + e.w2 + "/2)*(wr*" + fx + "+wi*" + fy + ")," + "(hh/2)*wi+(" + e.w2 + "/2)*(wr*" + fy + "-wi*" + fx + ")," + "2*((wr*zr-wi*zi)*" + fx + "+(wr*zi+wi*zr)*" + fy + ")," + e.w2 + "*cpx," + e.w2 + "*cpy," + e.w2 + "*" + gddx + "," + e.w2 + "*" + gddy + "," + e.w2 + ",0," + jd_sigma + ";");
}

// lift helpers: (wr, wi) from (gx, gy) with Form A or B
void lift_strings(const std::string& gx, const std::string& gy, bool form_b, std::string& wr, std::string& wi) {
  const std::string abs_g = "sqrt(" + gx + "^2+" + gy + "^2)";
  if (form_b) {
    wi = "sqrt((" + abs_g + "-" + gx + ")/2)";
    wr = "(" + gy + "/(2*" + wi + "))";
  } else {
    wr = "sqrt((" + abs_g + "+" + gx + ")/2)";
    wi = "(" + gy + "/(2*" + wr + "))";
  }
}

// Exact tied launch in chart c as a function of ww.  Positions
// q1=(-1/2,0), q2=(1/2,0), q3=((B^2-A^2)/2, AB); velocities zero.
Map make_launch(const Chart& c) {
  const std::string A = kMass[0], B = kMass[1];
  const std::string qx[3] = {"(-1/2)", "(1/2)", "((" + B + "^2-" + A + "^2)/2)"};
  const std::string qy[3] = {"(0)", "(0)", "(" + A + "*" + B + ")"};
  const std::string gx = "(" + qx[c.j] + "-" + qx[c.i] + ")";
  const std::string gy = "(" + qy[c.j] + "-" + qy[c.i] + ")";
  std::string wr, wi;
  lift_strings(gx, gy, false, wr, wi);
  const std::string abs_g = "sqrt(" + gx + "^2+" + gy + "^2)";
  const std::string hh = "(-" + Mij(c) + "/" + abs_g + ")";
  const std::string cx = "((" + kMass[c.i] + "*" + qx[c.i] + "+" + kMass[c.j] + "*" + qx[c.j] + ")/" + Mij(c) + ")";
  const std::string cy = "((" + kMass[c.i] + "*" + qy[c.i] + "+" + kMass[c.j] + "*" + qy[c.j] + ")/" + Mij(c) + ")";
  const std::string Gx = "(" + qx[c.k] + "-" + cx + ")";
  const std::string Gy = "(" + qy[c.k] + "-" + cy + ")";
  return Map(std::string(kVars) + "fun:" + wr + "," + wi + ",0,0," + hh + "," + Gx + "," + Gy + ",0,0,0,ww,0;");
}

// Exact chart switch c -> d.  Physical vectors relative to q_i (chart c) are
// q_i = 0, q_j = g, q_k = d_ki, with velocities 0, g', d_ki'.
Map make_switch(const Chart& c, const Chart& d, bool form_b) {
  const ChartExpr e = chart_expr(c);
  std::string px[3], py[3], vx[3], vy[3];
  px[c.i] = "(0)"; py[c.i] = "(0)"; vx[c.i] = "(0)"; vy[c.i] = "(0)";
  px[c.j] = e.gx; py[c.j] = e.gy; vx[c.j] = e.gdx; vy[c.j] = e.gdy;
  px[c.k] = e.dkix; py[c.k] = e.dkiy; vx[c.k] = e.dkidx; vy[c.k] = e.dkidy;
  const std::string ngx = "(" + px[d.j] + "-" + px[d.i] + ")";
  const std::string ngy = "(" + py[d.j] + "-" + py[d.i] + ")";
  const std::string ngdx = "(" + vx[d.j] + "-" + vx[d.i] + ")";
  const std::string ngdy = "(" + vy[d.j] + "-" + vy[d.i] + ")";
  std::string nwr, nwi;
  lift_strings(ngx, ngy, form_b, nwr, nwi);
  const std::string nzr = "((" + nwr + "*" + ngdx + "+" + nwi + "*" + ngdy + ")/2)";
  const std::string nzi = "((" + nwr + "*" + ngdy + "-" + nwi + "*" + ngdx + ")/2)";
  const std::string abs_g = "sqrt(" + ngx + "^2+" + ngy + "^2)";
  const std::string nh = "((" + ngdx + "^2+" + ngdy + "^2)/2-" + Mij(d) + "/" + abs_g + ")";
  const std::string cx = "((" + kMass[d.i] + "*" + px[d.i] + "+" + kMass[d.j] + "*" + px[d.j] + ")/" + Mij(d) + ")";
  const std::string cy = "((" + kMass[d.i] + "*" + py[d.i] + "+" + kMass[d.j] + "*" + py[d.j] + ")/" + Mij(d) + ")";
  const std::string cvx = "((" + kMass[d.i] + "*" + vx[d.i] + "+" + kMass[d.j] + "*" + vx[d.j] + ")/" + Mij(d) + ")";
  const std::string cvy = "((" + kMass[d.i] + "*" + vy[d.i] + "+" + kMass[d.j] + "*" + vy[d.j] + ")/" + Mij(d) + ")";
  const std::string nGx = "(" + px[d.k] + "-" + cx + ")";
  const std::string nGy = "(" + py[d.k] + "-" + cy + ")";
  const std::string nPx = "(" + vx[d.k] + "-" + cvx + ")";
  const std::string nPy = "(" + vy[d.k] + "-" + cvy + ")";
  return Map(std::string(kVars) + "fun:" + nwr + "," + nwi + "," + nzr + "," + nzi + "," + nh + "," + nGx + "," + nGy + "," + nPx + "," + nPy + ",tp,ww,jd;");
}

struct Masses {
  Ival m[3], M;
};
Masses masses_of(const Ival& u) {
  Masses ms;
  const Ival q = 1 + u * u;
  ms.m[0] = (1 - u * u) / q;
  ms.m[1] = 2 * u / q;
  ms.m[2] = Ival(1);
  ms.M = ms.m[0] + ms.m[1] + ms.m[2];
  return ms;
}

struct Scalars {
  Ival sel, rki2, rkj2, K, U, U0, idot;
  Ival gx, gy, dkix, dkiy;  // for lift-form selection
};

Scalars evaluate(const Vector& s, const Chart& c, const Masses& ms) {
  Scalars o;
  const Ival wr = s[0], wi = s[1];
  o.gx = wr * wr - wi * wi;
  o.gy = 2 * wr * wi;
  o.sel = wr * wr + wi * wi;
  const Ival Mij = ms.m[c.i] + ms.m[c.j];
  const Ival aj = ms.m[c.j] / Mij, ai = ms.m[c.i] / Mij;
  const Ival gdx = 2 * (wr * s[2] - wi * s[3]) / o.sel;
  const Ival gdy = 2 * (wr * s[3] + wi * s[2]) / o.sel;
  o.dkix = s[5] + aj * o.gx; o.dkiy = s[6] + aj * o.gy;
  const Ival dkjx = s[5] - ai * o.gx, dkjy = s[6] - ai * o.gy;
  o.rki2 = o.dkix * o.dkix + o.dkiy * o.dkiy;
  o.rkj2 = dkjx * dkjx + dkjy * dkjy;
  const Ival mu_ij = ms.m[c.i] * ms.m[c.j] / Mij, mu_G = ms.m[c.k] * Mij / ms.M;
  o.K = (mu_ij * (gdx * gdx + gdy * gdy) + mu_G * (s[7] * s[7] + s[8] * s[8])) / 2;
  o.idot = s[11];
  const Ival ab = ms.m[0] * ms.m[1];
  o.U0 = ab + 1 / ab;
  o.U = Ival(0);
  if (LB(o.sel) > 0 && LB(o.rki2) > 0 && LB(o.rkj2) > 0) {
    o.U = ms.m[c.i] * ms.m[c.j] / o.sel + ms.m[c.i] * ms.m[c.k] / sqrt(o.rki2) + ms.m[c.j] * ms.m[c.k] / sqrt(o.rkj2);
  }
  return o;
}

bool contains_zero(const Ival& x) { return !(LB(x) > 0) && !(UB(x) < 0); }
bool residual_excludes_brake(const Vector& s) {
  return !contains_zero(s[2]) || !contains_zero(s[3]) || !contains_zero(s[7]) || !contains_zero(s[8]);
}
double hull_width(const Vector& s) {
  double w = 0;
  for (int i = 0; i < 12; ++i) w = std::max(w, UB(s[i]) - LB(s[i]));
  return w;
}

double terminal_margin(const Vector& s, const Chart& c, const Masses& ms, double* eta_used, double* det) {
  const Ival M = ms.m[c.i] + ms.m[c.j], mc = ms.m[c.k];
  const Ival h = s[4];
  const Ival gx = s[5], gy = s[6], px = s[7], py = s[8];
  const Ival rho = sqrt(gx * gx + gy * gy);
  const Ival rhodot = (gx * px + gy * py) / rho;
  double best = -1e300;
  const double etas[8] = {0.5, 1, 1.5, 2, 3, 4, 6, 8};
  for (int k = 0; k < 8; ++k) {
    const Ival eta(etas[k]);
    const Ival R = M / eta;
    const Ival s0 = rho - R;
    if (!(LB(s0) > 0) || !(LB(rhodot) > 0)) continue;
    const Ival delta = rhodot * rhodot / 2 - (M + mc) / s0;
    if (!(LB(delta) > 0)) continue;
    const Ival allowance = mc * sqrt(2 * M * R) / (sqrt(2 * delta) * s0 * s0);
    const Ival margin = -eta - h - allowance;
    if (LB(margin) > best) {
      best = LB(margin); *eta_used = etas[k];
      det[0] = LB(s0); det[1] = LB(rhodot); det[2] = LB(delta); det[3] = UB(h); det[4] = UB(allowance);
    }
  }
  return best;
}

Set make_launch_set(const Chart& c, const Ival& u_range) {
  const int n = 12;
  const Ival u_center = midpoint(u_range);
  Vector center_input(n), range_input(n);
  for (int i = 0; i < n; ++i) { center_input[i] = Ival(0); range_input[i] = Ival(0); }
  center_input[10] = u_center;
  range_input[10] = u_range;
  Map launch = make_launch(c);
  const Vector anchor_image = launch(center_input);
  const Matrix dl = launch.derivative(range_input);
  const Ival deviation = u_range - u_center;
  Vector x(n), r0(n), r(n);
  Matrix C = Matrix::Identity(n), B = Matrix::Identity(n);
  for (int row = 0; row < n; ++row) {
    const Ival xm = midpoint(anchor_image[row]);
    Ival raw = dl[row][10];
    if (row == 10) raw = Ival(1);
    const Ival cm = midpoint(raw);
    x[row] = xm;
    C[row][0] = cm;
    r[row] = (anchor_image[row] - xm) + (raw - cm) * deviation;
    if (row == 10) r[row] = Ival(0);
    r[row] = capd::intervals::intervalHull(r[row], Ival(0));
    r0[row] = Ival(0);
  }
  x[10] = u_center;
  r0[0] = deviation;
  return Set(x, C, r0, B, r, Ival(0));
}

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
    if (!capd::intervals::intersection(b_part[i], q_part[i], remainder[i])) throw std::runtime_error("empty tripleton remainder intersection");
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
      const Ival mid = midpoint(dc[i][j]);
      dc_mid[i][j] = mid;
      spill[i] += (dc[i][j] - mid) * r0[j];
    }
  }
  Vector new_x(dimension), new_r(dimension);
  for (int i = 0; i < dimension; ++i) {
    const Ival mid = midpoint(image_x[i]);
    new_x[i] = mid;
    new_r[i] = d_remainder[i] + (image_x[i] - mid) + spill[i];
  }
  return Set(new_x, dc_mid, r0, new_r, set.getCurrentTime());
}

// target pair vector g' on the hull, for lift-form choice
void target_pair_vector(const Vector& hull, const Chart& c, const Chart& d, const Masses& ms, Ival& gx, Ival& gy) {
  const Scalars sc = evaluate(hull, c, ms);
  Ival px[3], py[3];
  px[c.i] = Ival(0); py[c.i] = Ival(0);
  px[c.j] = sc.gx; py[c.j] = sc.gy;
  px[c.k] = sc.dkix; py[c.k] = sc.dkiy;
  gx = px[d.j] - px[d.i];
  gy = py[d.j] - py[d.i];
}

struct Leg { int chart; double tp; };

std::vector<Leg> parse_itinerary(const std::string& s) {
  std::vector<Leg> legs;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, ',')) {
    const size_t at = item.find('@');
    if (at == std::string::npos) throw std::runtime_error("itinerary entry needs chart@tp");
    legs.push_back({std::atoi(item.substr(0, at).c_str()), std::atof(item.substr(at + 1).c_str())});
  }
  if (legs.empty() || legs[0].tp != 0) throw std::runtime_error("itinerary must start with chart@0");
  return legs;
}

int run(long p, long q, long p2, long q2, const std::string& itin, int order, double tol, double tp_max, double min_margin) {
  std::cout << std::setprecision(17);
  const Ival a = Ival(p) / Ival(q);
  const Ival b = Ival(p2) / Ival(q2);
  if (!(UB(a) <= LB(b)) && !(p == p2 && q == q2)) throw std::runtime_error("inverted tile");
  const Ival u_range(std::min(LB(a), LB(b)), std::max(UB(a), UB(b)));
  const Masses ms = masses_of(u_range);
  const std::vector<Leg> legs = parse_itinerary(itin);
  std::cout << "TILE u in [" << LB(u_range) << "," << UB(u_range) << "] width=" << (UB(u_range) - LB(u_range)) << " itinerary=" << itin << "\n";
  Chart chart = chart_of(legs[0].chart);
  Set set = make_launch_set(chart, u_range);
  {
    const Vector hull(set);
    if (!(LB(hull[10]) <= LB(u_range) && UB(hull[10]) >= UB(u_range))) throw std::runtime_error("launch set does not contain the tile");
    std::cout << "LAUNCH chart=" << code_of(chart) << " hull width=" << hull_width(hull) << "\n";
  }
  const Ival two_u0 = 2 * (ms.m[0] * ms.m[1] + 1 / (ms.m[0] * ms.m[1]));
  bool launch_phase = true;
  long steps = 0, retries = 0;
  double max_hull = 0, min_sel = 1e300, min_unsel = 1e300, min_K = 1e300, tp_launch_end = 0;
  const bool verbose = std::getenv("ISO_VERBOSE") != nullptr;
  for (size_t leg = 0; leg < legs.size(); ++leg) {
    if (leg > 0) {
      const Chart target = chart_of(legs[leg].chart);
      const Vector hull(set);
      Ival gx, gy;
      target_pair_vector(hull, chart, target, ms, gx, gy);
      const Ival abs_g = sqrt(gx * gx + gy * gy);
      const bool form_b = LB((abs_g - gx) / 2) > LB((abs_g + gx) / 2);
      Map transformation = make_switch(chart, target, form_b);
      set = mean_value_switch(set, transformation);
      chart = target;
      const Vector switched(set);
      const Scalars sc = evaluate(switched, chart, ms);
      if (!(LB(sc.sel) > 0) || !(LB(sc.rki2) > 0) || !(LB(sc.rkj2) > 0)) throw std::runtime_error("switch lost separation");
      std::cout << "SWITCH to " << code_of(chart) << " form=" << (form_b ? "B" : "A") << " tp=[" << LB(switched[9]) << "," << UB(switched[9]) << "] hull=" << hull_width(switched) << "\n";
    }
    Map field = make_field(chart);
    Solver solver(field, order);
    solver.setAbsoluteTolerance(tol);
    solver.setRelativeTolerance(tol);
    const bool last_leg = (leg + 1 == legs.size());
    const double next_tp = last_leg ? 1e300 : legs[leg + 1].tp;
    for (;;) {
      const Vector before(set);
      const Scalars pre = evaluate(before, chart, ms);
      if (!(LB(pre.sel) > 0) || !(LB(pre.rki2) > 0) || !(LB(pre.rkj2) > 0)) throw std::runtime_error("lost pre-step separation");
      const double w_abs = std::sqrt(std::max(1e-12, LB(pre.sel)));
      const double unsel = std::sqrt(std::max(1e-12, std::min(LB(pre.rki2), LB(pre.rkj2))));
      const double w2_lower = std::max(1e-12, LB(pre.sel));
      const double unsel_cap = unsel * std::sqrt(unsel) / (40.0 * w2_lower);
      double cap = std::max(1.0 / 20000.0, std::min(std::min(w_abs / 24.0, unsel_cap), 1.0 / 100.0));
      for (;;) {
        Set backup(set);
        try { solver.setMaxStep(Ival(cap)); set.move(solver); break; }
        catch (const std::exception&) { set = backup; if (++retries > 200000 || cap < 1e-14) throw; cap /= 2; }
      }
      ++steps;
      const Vector enc = set.getLastEnclosure();
      const Scalars sc = evaluate(enc, chart, ms);
      if (!(LB(sc.sel) > 0) || !(LB(sc.rki2) > 0) || !(LB(sc.rkj2) > 0)) throw std::runtime_error("possible collision at step " + std::to_string(steps));
      min_sel = std::min(min_sel, LB(sc.sel));
      min_unsel = std::min(min_unsel, std::sqrt(std::min(LB(sc.rki2), LB(sc.rkj2))));
      const bool concave = UB(sc.U) < LB(two_u0);
      const bool obstructed = LB(sc.K) > 0 || !contains_zero(sc.idot) || residual_excludes_brake(enc);
      bool failed = false;
      if (launch_phase) {
        if (!concave) { launch_phase = false; tp_launch_end = LB(enc[9]); if (!obstructed) failed = true; }
      } else if (!obstructed) failed = true;
      const Vector hull(set);
      max_hull = std::max(max_hull, hull_width(hull));
      if (!launch_phase) min_K = std::min(min_K, LB(sc.K));
      if (verbose && (steps % 100 == 0 || failed)) {
        std::cout << "STEP " << steps << " chart=" << code_of(chart) << " tp=[" << LB(hull[9]) << "," << UB(hull[9]) << "] hull=" << hull_width(hull)
                  << " K=[" << LB(sc.K) << "," << UB(sc.K) << "] sel=" << LB(sc.sel) << " unsel=" << std::sqrt(std::min(LB(sc.rki2), LB(sc.rkj2))) << " cap=" << cap << "\n";
      }
      if (failed) throw std::runtime_error("brake obstruction lost at step " + std::to_string(steps) + " tp=" + std::to_string(LB(hull[9])));
      if (!last_leg && LB(hull[9]) >= next_tp) break;
      if (last_leg && !launch_phase) {
        double eta = 0, det[5] = {0, 0, 0, 0, 0};
        const double margin = terminal_margin(hull, chart, ms, &eta, det);
        if (margin > min_margin) {
          std::cout << "STEPS " << steps << " retries=" << retries << " launch_window_end_tp=" << tp_launch_end << " min_selected=" << min_sel
                    << " min_unselected=" << min_unsel << " min_K_after_launch=" << min_K << " max_hull_width=" << max_hull << "\n";
          std::cout << "TERMINAL chart=" << code_of(chart) << " escaper=" << (chart.k + 1) << " tp=[" << LB(hull[9]) << "," << UB(hull[9]) << "] eta=" << eta
                    << " s0>" << det[0] << " rhodot>" << det[1] << " delta>" << det[2] << " h<" << det[3] << " allowance<" << det[4] << " margin=" << margin << "\n";
          std::cout << "PASS_WINDOW_LC [" << p << "/" << q << "," << p2 << "/" << q2 << "] itinerary=" << itin << " escaper=" << (chart.k + 1) << " margin=" << margin << "\n";
          return 0;
        }
      }
      if (LB(hull[9]) > tp_max) throw std::runtime_error("terminal check never passed before tp_max");
      if (steps > 600000) throw std::runtime_error("step limit");
    }
  }
  throw std::runtime_error("unreachable");
}

}  // namespace

int main(int argc, char** argv) {
  if (argc < 6) {
    std::cerr << "usage: window_lc_capd P Q P2 Q2 ITINERARY [ORDER TOL TP_MAX MIN_MARGIN]\n";
    return 2;
  }
  try {
    const long p = std::atol(argv[1]), q = std::atol(argv[2]), p2 = std::atol(argv[3]), q2 = std::atol(argv[4]);
    const std::string itin = argv[5];
    const int order = argc > 6 ? std::atoi(argv[6]) : 12;
    const double tol = argc > 7 ? std::atof(argv[7]) : 1e-11;
    const double tp_max = argc > 8 ? std::atof(argv[8]) : 8.0;
    const double min_margin = argc > 9 ? std::atof(argv[9]) : 0.05;
#ifdef FABLE_MP
    const int precision = argc > 10 ? std::atoi(argv[10]) : 160;
    capd::MpFloat::setDefaultPrecision(precision);
    std::cout << "MP precision bits=" << precision << "\n";
#endif
    return run(p, q, p2, q2, itin, order, tol, tp_max, min_margin);
  } catch (const std::exception& e) {
    std::cout << "FAIL " << e.what() << "\n";
    return 1;
  }
}
