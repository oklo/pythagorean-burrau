// Rigorous nonperiodicity certificate for a real parameter tile of the tied
// Pythagorean family in the prompt-ejection window near u = 0.40.
//
// Mathematical basis (paper/sections/reductions.tex):
//   * Corollary (validated-cover criterion): if U < 2 U0 on a launch window
//     [0, t_L] (so that dI/dt < 0 there), every later time up to t_* is
//     covered by a validated enclosure on which K > 0 or dI/dt != 0, and the
//     terminal enclosure satisfies the escape lemma, then the tied solution
//     has no second labelled brake and is nonperiodic.
//   * Lemma (terminal escape certificate) with binary {3,1}, escaper body 2,
//     evaluated on the terminal hull, hence fiberwise for every u in the tile.
//   * Brake-event identities: K = 0 exactly at a labelled brake (L = P = 0),
//     so K > 0 on an enclosure excludes a brake on the whole step.
//
// Coordinates: selected pair {1,2} Jacobi vectors X = q2 - q1,
// Y = q3 - (A q1 + B q2)/(A+B), their velocities, and u carried as a state
// variable with u' = 0 (masses A(u), B(u), 1 enter the field through u).
// No Levi-Civita regularization is needed: in the certified window every pair
// separation stays above ~2e-3 (numerically), and the certificate checks
// positivity of all three separations on every step enclosure.
//
// Initial set: exact tied launch curve over the closed tile [P/Q, P2/Q2],
// represented as a correlated tripleton x + C r0 + r via the mean value
// theorem: L(u) in L(um) + DL([a,b]) (u - um), with C = mid(DL([a,b])) and the
// residual (DL([a,b]) - C)(u - um) plus the rounding width of L(um) put in r.
//
// Usage: iso_window_capd P Q P2 Q2 [T_STAR ORDER TOL CAP_CEILING]
// Output ends with PASS_ISO_WINDOW or FAIL ...; fail-closed on any exception.
// Dependency pin: CAPD 6.1.0 commit 731079217a9254ea2948d742df2b170895effe7f,
// NATIVE interval build (-frounding-math -D__USE_NATIVE__).

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
typedef capd::ITimeMap TimeMap;
typedef capd::IVector Vector;
typedef capd::IMatrix Matrix;
typedef capd::C0TripletonSet Set;

const int kDim = 9;  // xr, xi, yr, yi, vxr, vxi, vyr, vyi, u

Map make_field() {
  const std::string q = "(1+u^2)";
  const std::string A = "((1-u^2)/" + q + ")";
  const std::string B = "(2*u/" + q + ")";
  const std::string AB = "(" + A + "+" + B + ")";
  const std::string M = "(" + AB + "+1)";
  const std::string cb = "(" + B + "/" + AB + ")";  // m_j / M_ij, j = 2
  const std::string ca = "(" + A + "/" + AB + ")";  // m_i / M_ij, i = 1
  const std::string d13r = "(yr+" + cb + "*xr)";
  const std::string d13i = "(yi+" + cb + "*xi)";
  const std::string d23r = "(yr-" + ca + "*xr)";
  const std::string d23i = "(yi-" + ca + "*xi)";
  const std::string r12sq = "(xr^2+xi^2)";
  const std::string r13sq = "(" + d13r + "^2+" + d13i + "^2)";
  const std::string r23sq = "(" + d23r + "^2+" + d23i + "^2)";
  const std::string i12 = "(" + r12sq + "*sqrt(" + r12sq + "))";
  const std::string i13 = "(" + r13sq + "*sqrt(" + r13sq + "))";
  const std::string i23 = "(" + r23sq + "*sqrt(" + r23sq + "))";
  // Xdd = -(A+B) X/|X|^3 + m3 (d23/|d23|^3 - d13/|d13|^3), m3 = 1
  const std::string axr = "(-" + AB + "*xr/" + i12 + "+(" + d23r + "/" + i23 + "-" + d13r + "/" + i13 + "))";
  const std::string axi = "(-" + AB + "*xi/" + i12 + "+(" + d23i + "/" + i23 + "-" + d13i + "/" + i13 + "))";
  // Ydd = -(M/(A+B)) (A d13/|d13|^3 + B d23/|d23|^3)
  const std::string ayr = "(-(" + M + "/" + AB + ")*(" + A + "*" + d13r + "/" + i13 + "+" + B + "*" + d23r + "/" + i23 + "))";
  const std::string ayi = "(-(" + M + "/" + AB + ")*(" + A + "*" + d13i + "/" + i13 + "+" + B + "*" + d23i + "/" + i23 + "))";
  return Map("var:xr,xi,yr,yi,vxr,vxi,vyr,vyi,u;fun:vxr,vxi,vyr,vyi," + axr + "," + axi + "," + ayr + "," + ayi + ",0;");
}

// Exact tied launch as a map of u (velocities zero): used for value and
// derivative enclosures.
Map make_launch() {
  const std::string q = "(1+u^2)";
  const std::string A = "((1-u^2)/" + q + ")";
  const std::string B = "(2*u/" + q + ")";
  const std::string AB = "(" + A + "+" + B + ")";
  // Y0 = ((B^2-A^2)/2 - (B-A)/(2(A+B)), A B)
  const std::string y0r = "((" + B + "^2-" + A + "^2)/2-(" + B + "-" + A + ")/(2*" + AB + "))";
  const std::string y0i = "(" + A + "*" + B + ")";
  return Map("var:u;fun:1,0," + y0r + "," + y0i + ",0,0,0,0,u;");
}

struct Scalars {
  Ival r12sq, r13sq, r23sq, K, U, U0, Idot, A, B;
};

Scalars evaluate(const Vector& s) {
  Scalars sc;
  const Ival u = s[8];
  const Ival q = 1 + u * u;
  sc.A = (1 - u * u) / q;
  sc.B = 2 * u / q;
  const Ival AB = sc.A + sc.B;
  const Ival M = AB + 1;
  const Ival cb = sc.B / AB, ca = sc.A / AB;
  const Ival xr = s[0], xi = s[1], yr = s[2], yi = s[3];
  const Ival vxr = s[4], vxi = s[5], vyr = s[6], vyi = s[7];
  const Ival d13r = yr + cb * xr, d13i = yi + cb * xi;
  const Ival d23r = yr - ca * xr, d23i = yi - ca * xi;
  sc.r12sq = xr * xr + xi * xi;
  sc.r13sq = d13r * d13r + d13i * d13i;
  sc.r23sq = d23r * d23r + d23i * d23i;
  const Ival mu1 = sc.A * sc.B / AB;
  const Ival mu2 = AB / M;
  sc.K = (mu1 * (vxr * vxr + vxi * vxi) + mu2 * (vyr * vyr + vyi * vyi)) / 2;
  sc.U = sc.A * sc.B / sqrt(sc.r12sq) + sc.A / sqrt(sc.r13sq) + sc.B / sqrt(sc.r23sq);
  sc.U0 = sc.A * sc.B + 1 / (sc.A * sc.B);
  sc.Idot = 2 * (mu1 * (xr * vxr + xi * vxi) + mu2 * (yr * vyr + yi * vyi));
  return sc;
}

// Terminal escape lemma with binary {3,1} (masses 1 and A), escaper body 2
// (mass B).  Inner vector x = q1 - q3 = -d13, outer y = q2 - C31 = X - d13/(A+1).
// Returns the best (largest) inner-energy margin over the eta list, or a
// negative number if no eta certifies.
double terminal_margin(const Vector& s, double* eta_used, double* details) {
  const Ival u = s[8];
  const Ival q = 1 + u * u;
  const Ival A = (1 - u * u) / q;
  const Ival B = 2 * u / q;
  const Ival AB = A + B;
  const Ival cb = B / AB;
  const Ival xr = s[0], xi = s[1], yr = s[2], yi = s[3];
  const Ival vxr = s[4], vxi = s[5], vyr = s[6], vyi = s[7];
  const Ival d13r = yr + cb * xr, d13i = yi + cb * xi;
  const Ival vd13r = vyr + cb * vxr, vd13i = vyi + cb * vxi;
  const Ival M = A + 1, mc = B;
  const Ival r = sqrt(d13r * d13r + d13i * d13i);
  const Ival e = (vd13r * vd13r + vd13i * vd13i) / 2 - M / r;
  const Ival oyr = xr - d13r / M, oyi = xi - d13i / M;
  const Ival ovr = vxr - vd13r / M, ovi = vxi - vd13i / M;
  const Ival rho = sqrt(oyr * oyr + oyi * oyi);
  const Ival rhodot = (oyr * ovr + oyi * ovi) / rho;
  double best = -1e300;
  const double etas[6] = {1, 1.5, 2, 3, 4, 6};
  for (int k = 0; k < 6; ++k) {
    const Ival eta(etas[k]);
    const Ival R = M / eta;
    const Ival s0 = rho - R;
    if (!(s0.leftBound() > 0) || !(rhodot.leftBound() > 0)) continue;
    const Ival delta = rhodot * rhodot / 2 - (M + mc) / s0;
    if (!(delta.leftBound() > 0)) continue;
    const Ival allowance = mc * sqrt(2 * M * R) / (sqrt(2 * delta) * s0 * s0);
    const Ival margin = -eta - e - allowance;
    if (margin.leftBound() > best) {
      best = margin.leftBound();
      *eta_used = etas[k];
      details[0] = s0.leftBound();
      details[1] = rhodot.leftBound();
      details[2] = delta.leftBound();
      details[3] = e.rightBound();
      details[4] = allowance.rightBound();
    }
  }
  return best;
}

double width(const Vector& v) {
  double w = 0;
  for (int i = 0; i < kDim; ++i) w = std::max(w, v[i].rightBound() - v[i].leftBound());
  return w;
}

int run(long p, long q, long p2, long q2, double t_star, int order, double tol, double argc_cap_ceiling) {
  std::cout << std::setprecision(17);
  const Ival a = Ival(p) / Ival(q);
  const Ival b = Ival(p2) / Ival(q2);
  if (!(a.rightBound() < b.leftBound())) throw std::runtime_error("empty or inverted tile");
  const Ival tile = Ival(a.leftBound(), b.rightBound());
  const Ival um = Ival((a.leftBound() + b.rightBound()) / 2);
  const Ival delta = Ival(-1, 1) * (b.rightBound() - a.leftBound()) / 2;
  std::cout << "TILE u in [" << tile.leftBound() << "," << tile.rightBound() << "] width=" << (tile.rightBound() - tile.leftBound()) << "\n";

  // Launch set via the mean value theorem.
  Map launch = make_launch();
  Vector arg_m(1), arg_t(1);
  arg_m[0] = um;
  arg_t[0] = tile;
  Vector Lm = launch(arg_m);
  Matrix DLt = launch.derivative(arg_t);  // 9 x 1
  Vector x(kDim), r0(kDim), r(kDim);
  Matrix C = Matrix::Identity(kDim);
  for (int i = 0; i < kDim; ++i) {
    const double xm = (Lm[i].leftBound() + Lm[i].rightBound()) / 2;
    x[i] = Ival(xm);
    const Ival dcol = DLt(i + 1, 1);
    const double cm = (dcol.leftBound() + dcol.rightBound()) / 2;
    C(i + 1, 1) = Ival(cm);
    r[i] = (Lm[i] - Ival(xm)) + (dcol - Ival(cm)) * delta;
    r0[i] = Ival(0);
  }
  r0[0] = delta;
  // sanity: the u coordinate must be exactly the tile
  Set set(x, C, r0, r);
  {
    const Vector hull(set);
    if (!(hull[8].leftBound() <= tile.leftBound() && hull[8].rightBound() >= tile.rightBound()))
      throw std::runtime_error("launch set does not contain the tile in u");
    std::cout << "LAUNCH hull width=" << width(hull) << " u-hull=[" << hull[8].leftBound() << "," << hull[8].rightBound() << "]\n";
  }

  Map field = make_field();
  Solver solver(field, order);
  solver.setAbsoluteTolerance(tol);
  solver.setRelativeTolerance(tol);
  // Direct solver steps with an explicit step cap tied to the closest pair
  // separation (free-fall time scale / 40): without it the rough enclosure
  // through a close passage silently poisons the set.
  bool launch_phase = true;
  long steps = 0;
  double max_hull = 0, min_sep = 1e300, min_K = 1e300, t_launch_end = 0;
  const double cap_ceiling = argc_cap_ceiling;
  for (;;) {
    const double t_now = set.getCurrentTime().rightBound();
    if (t_now >= t_star) break;
    const Vector pre(set);
    const Scalars pre_sc = evaluate(pre);
    const double pre_sep = std::sqrt(std::max(1e-12, std::min(std::min(pre_sc.r12sq.leftBound(), pre_sc.r13sq.leftBound()), pre_sc.r23sq.leftBound())));
    double cap = std::min(cap_ceiling, pre_sep * std::sqrt(pre_sep) / 40.0);
    cap = std::min(cap, t_star - t_now);
    solver.setMaxStep(Ival(cap));
    set.move(solver);
    ++steps;
    const Vector enc = set.getLastEnclosure();
    const Scalars sc = evaluate(enc);
    const double sep = std::min(std::min(sc.r12sq.leftBound(), sc.r13sq.leftBound()), sc.r23sq.leftBound());
    if (!(sep > 0)) throw std::runtime_error("possible collision at step " + std::to_string(steps));
    min_sep = std::min(min_sep, std::sqrt(sep));
    const bool concave = sc.U.rightBound() < (2 * sc.U0).leftBound();
    const bool kinetic = sc.K.leftBound() > 0;
    const bool idot = !(sc.Idot.leftBound() <= 0 && sc.Idot.rightBound() >= 0);
    bool failed = false;
    if (launch_phase) {
      if (!concave) {
        if (!(kinetic || idot)) failed = true;
        launch_phase = false;
        t_launch_end = set.getCurrentTime().leftBound();
      }
    } else if (!(kinetic || idot)) {
      failed = true;
    }
    const Vector hull(set);
    max_hull = std::max(max_hull, width(hull));
    if (!launch_phase) min_K = std::min(min_K, sc.K.leftBound());
    if (std::getenv("ISO_VERBOSE") && (steps % 50 == 0 || failed)) {
      std::cout << "STEP " << steps << " t=" << set.getCurrentTime().leftBound() << " hull=" << width(hull)
                << " enc=" << width(enc) << " K=[" << sc.K.leftBound() << "," << sc.K.rightBound() << "] Idot=["
                << sc.Idot.leftBound() << "," << sc.Idot.rightBound() << "] sep=" << std::sqrt(sep) << " U/U0=" << (sc.U / sc.U0).rightBound() << " cap=" << cap << "\n";
    }
    if (failed) throw std::runtime_error("brake obstruction lost at step " + std::to_string(steps) + " t=" + std::to_string(set.getCurrentTime().leftBound()));
    if (steps > 400000) throw std::runtime_error("step limit");
  }
  const Vector final_hull(set);
  const Ival tf = set.getCurrentTime();
  if (!(tf.rightBound() >= t_star)) throw std::runtime_error("terminal time not reached");
  const double t_final = tf.leftBound();
  double eta = 0, det[5] = {0, 0, 0, 0, 0};
  const double margin = terminal_margin(final_hull, &eta, det);
  std::cout << "STEPS " << steps << " launch_window_end=" << t_launch_end << " min_separation=" << min_sep
            << " min_K_after_launch=" << min_K << " max_hull_width=" << max_hull << " final_hull_width=" << width(final_hull) << "\n";
  std::cout << "TERMINAL t=" << t_final << " eta=" << eta << " s0>" << det[0] << " rhodot>" << det[1] << " delta>" << det[2]
            << " e<" << det[3] << " allowance<" << det[4] << " margin=" << margin << "\n";
  if (!(margin > 0)) throw std::runtime_error("terminal escape certificate failed");
  std::cout << "PASS_ISO_WINDOW [" << p << "/" << q << "," << p2 << "/" << q2 << "] t_star=" << t_star << " margin=" << margin << "\n";
  return 0;
}

}  // namespace

int main(int argc, char** argv) {
  if (argc < 5) {
    std::cerr << "usage: iso_window_capd P Q P2 Q2 [T_STAR ORDER TOL]\n";
    return 2;
  }
  try {
    const long p = std::atol(argv[1]), q = std::atol(argv[2]), p2 = std::atol(argv[3]), q2 = std::atol(argv[4]);
    const double t_star = argc > 5 ? std::atof(argv[5]) : 3.0;
    const int order = argc > 6 ? std::atoi(argv[6]) : 20;
    const double tol = argc > 7 ? std::atof(argv[7]) : 1e-14;
    const double capc = argc > 8 ? std::atof(argv[8]) : 0.02;
    return run(p, q, p2, q2, t_star, order, tol, capc);
  } catch (const std::exception& e) {
    std::cout << "FAIL " << e.what() << "\n";
    return 1;
  }
}
