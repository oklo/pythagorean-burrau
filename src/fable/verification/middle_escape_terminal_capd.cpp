// Interval terminal binary--escaper checker in the pair-{2,3} Levi--Civita
// chart, for the middle-interval program.
//
// Mathematical basis: docs/FABLE_MIDDLE_ESCAPE.md (chart-form theorem (T))
// mapping the pair-{2,3} chart onto the terminal escape theorem of
// docs/ESCAPE_CRITERIA.md with binary {2,3} and escaper body 1.  Given an
// interval box (u, wr, wi, zr, zi, Gx, Gy, Px, Py[, h]) and a rational
// eta > 0, the checker proves with outward-rounded interval arithmetic the
// strict inequalities
//
//   inf |w|^2 > 0,  inf |G|^2 > 0,  inf d > 0,  inf rhodot > 0,
//   inf Erho > 0,   inf(-eta - E23 - Delta) > 0,
//
// where M = (1+u)^2/(1+u^2), Mtot = 2(1+u)/(1+u^2), A = (1-u^2)/(1+u^2),
// E23 = (2|z|^2 - M)/|w|^2 (intersected with the transported h when given),
// R = M/eta, d = |G| - R, rhodot = G.P/|G|, Erho = rhodot^2/2 - Mtot/d,
// Delta = A sqrt(2 M R)/(sqrt(2 Erho) d^2).
//
// A PASS proves, for EVERY real parameter and state in the box: bodies 2,3
// remain a bound binary (r23 < R for all later times), body 1 escapes with
// rhodot >= sqrt(2 inf Erho) permanently, the only possible future classical
// singularity is an inner {2,3} collision, and in either alternative no
// later labelled brake exists (ESCAPE_CRITERIA.md; FABLE_EVENT_REDUCTION.md
// Theorem C terminal alternative).  Every guard fails closed.
//
// Phase-robust mode (--phase-robust): the inner-binary phase decorrelates
// across a parameter tile long before the terminal time, so the (w, z) hull
// of a correlated interval box can be wide or even contain w = 0 while the
// transported pair energy h and the outer variables (G, P) stay tight.  The
// corollary proved in docs/FABLE_MIDDLE_ESCAPE.md shows the certificate
// needs only (h, G, P): from h < -eta every surviving solution has
// r = M/(|gdot|^2/2 - h) <= M/(-h) < M/eta = R unconditionally, and a
// parameter whose solution actually reaches w = 0 at or before the section
// ended in an inner {2,3} collision, which is the theorem's tolerated
// alternative.  In this mode the h pair is REQUIRED, E23 is taken from h
// alone (no algebraic intersection), the w/z guards are skipped, and the
// PASS line is marked PHASE_ROBUST.  The (w, z) bounds must still be the
// enclosure produced by the rigorous propagation of the same box; they are
// simply not used.
//
// Mirrored labelling (--binary13): checks the same theorem for binary {1,3}
// with escaper body 2 (M = A + 1 = 2/(1+u^2), escaper mass B), with the box
// given in the pair-{1,3} chart of kDirectLcVars (g = q3 - q1,
// G = q2 - C13, P = dG/dt).  Ordinary numerics show this is the labelling
// that fires on the lower-adjacent parameter range near u = 0.2895, where
// the endgame hierarchy flips and body 2 is ejected instead of body 1.
//
// Input (stdin, whitespace separated): first eta, then lower/upper bound
// pairs for u, wr, wi, zr, zi, Gx, Gy, Px, Py, then optionally a pair for
// the transported pair energy h.  Every token must be an integer, an exact
// decimal (converted exactly to a rational), or a rational "p/q"; bounds
// are therefore enclosed exactly, with all rounding done by interval
// arithmetic.
//
// Dependency pin: CAPD 6.1.0, commit 731079217a9254ea2948d742df2b170895effe7f,
// built with -DCAPD_INTERVAL_TYPE=NATIVE; scripts/fable_run_capd_middle_escape.sh
// automates the build checks and forwards stdin.

#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "capd/capdlib.h"

namespace {

typedef capd::interval Ival;

// Exact rational parser: "123", "-0.25", "7/25" -> interval enclosure via
// exact integer construction and outward-rounded division.
Ival parse_exact(const std::string& token) {
  const auto slash = token.find('/');
  if (slash != std::string::npos) {
    const std::string num = token.substr(0, slash);
    const std::string den = token.substr(slash + 1);
    if (num.empty() || den.empty() || num.find('.') != std::string::npos ||
        den.find('.') != std::string::npos) {
      throw std::runtime_error("bad rational token: " + token);
    }
    const long long n = std::stoll(num);
    const long long d = std::stoll(den);
    if (d == 0) throw std::runtime_error("zero denominator: " + token);
    return Ival(static_cast<double>(n)) / Ival(static_cast<double>(d));
  }
  std::string body = token;
  bool negative = false;
  if (!body.empty() && (body[0] == '+' || body[0] == '-')) {
    negative = body[0] == '-';
    body = body.substr(1);
  }
  const auto dot = body.find('.');
  std::string digits = body;
  std::size_t fractional = 0;
  if (dot != std::string::npos) {
    digits = body.substr(0, dot) + body.substr(dot + 1);
    fractional = body.size() - dot - 1;
  }
  if (digits.empty() || digits.find_first_not_of("0123456789") != std::string::npos) {
    throw std::runtime_error("bad numeric token: " + token);
  }
  if (digits.size() > 15 || fractional > 15) {
    // 10^15 < 2^53: both integers below are exactly representable.
    throw std::runtime_error("token needs more than 15 digits: " + token);
  }
  long long mantissa = 0;
  for (char c : digits) mantissa = 10 * mantissa + (c - '0');
  if (negative) mantissa = -mantissa;
  long long scale = 1;
  for (std::size_t k = 0; k < fractional; ++k) scale *= 10;
  return Ival(static_cast<double>(mantissa)) / Ival(static_cast<double>(scale));
}

struct Box {
  Ival eta, u, wr, wi, zr, zi, gx, gy, px, py, h;
  bool has_h = false;
  bool phase_robust = false;
  // false: binary {2,3}, escaper 1 (pair-{2,3} chart).  true: binary {1,3},
  // escaper 2 (pair-{1,3} chart of kDirectLcVars): M = A + 1 = 2/(1+u^2),
  // escaper mass B; the theorem and all inequalities are otherwise
  // identical, with the box in the pair-{1,3} chart coordinates.
  bool binary13 = false;
};

bool read_box(std::istream& in, Box& box) {
  std::vector<std::string> tokens;
  std::string token;
  while (in >> token) tokens.push_back(token);
  if (tokens.size() != 19 && tokens.size() != 21) {
    std::cerr << "expected 19 or 21 tokens (eta + 9 or 10 bound pairs), got "
              << tokens.size() << "\n";
    return false;
  }
  std::size_t k = 0;
  auto next_scalar = [&]() { return parse_exact(tokens.at(k++)); };
  auto next_pair = [&]() {
    const Ival lo = parse_exact(tokens.at(k++));
    const Ival hi = parse_exact(tokens.at(k++));
    if (!(lo.leftBound() <= hi.rightBound())) {
      throw std::runtime_error("empty bound pair");
    }
    return Ival(lo.leftBound(), hi.rightBound());
  };
  box.eta = next_scalar();
  box.u = next_pair();
  box.wr = next_pair();
  box.wi = next_pair();
  box.zr = next_pair();
  box.zi = next_pair();
  box.gx = next_pair();
  box.gy = next_pair();
  box.px = next_pair();
  box.py = next_pair();
  if (tokens.size() == 21) {
    box.h = next_pair();
    box.has_h = true;
  }
  return true;
}

int fail(const std::string& reason) {
  std::cout << "FAIL_MIDDLE_ESCAPE_TERMINAL(" << reason << ")\n";
  return 1;
}

int check(const Box& box) {
  std::cout.precision(17);
  if (!(box.eta.leftBound() > 0)) return fail("eta_not_positive");
  if (!(box.u.leftBound() > 0) || !(box.u.rightBound() < 1)) {
    return fail("u_outside_unit_interval");
  }

  const Ival one(1);
  const Ival q = one + box.u * box.u;  // 1 + u^2 > 0
  const Ival total_m = Ival(2) * (one + box.u) / q;  // Mtot
  // Escaper mass and pair mass for the selected labelling.
  const Ival escaper_m = box.binary13
                             ? Ival(2) * box.u / q         // B
                             : (one - box.u * box.u) / q;  // A
  const Ival pair_m = box.binary13
                          ? Ival(2) / q                          // A + 1
                          : (one + box.u) * (one + box.u) / q;   // B + 1

  Ival e23;
  if (box.phase_robust) {
    // Corollary (docs/FABLE_MIDDLE_ESCAPE.md): with h < -eta certified, the
    // w/z guards are unnecessary; parameters reaching w = 0 ended in the
    // tolerated inner-collision alternative.
    if (!box.has_h) return fail("phase_robust_requires_h");
    e23 = box.h;
  } else {
    const Ival r = box.wr * box.wr + box.wi * box.wi;
    if (!(r.leftBound() > 0)) return fail("pair_distance_may_vanish");
    e23 = (Ival(2) * (box.zr * box.zr + box.zi * box.zi) - pair_m) / r;
    if (box.has_h) {
      // Transported h equals E23 along the flow; intersect for sharpness
      // and as a transport-consistency check.
      Ival intersection;
      if (!capd::intervals::intersection(e23, box.h, intersection)) {
        return fail("h_inconsistent_with_algebraic_E23");
      }
      e23 = intersection;
    }
  }

  const Ival rho_sq = box.gx * box.gx + box.gy * box.gy;
  if (!(rho_sq.leftBound() > 0)) return fail("outer_distance_may_vanish");
  const Ival rho = sqrt(rho_sq);

  const Ival radius = pair_m / box.eta;  // R = M/eta
  const Ival d = rho - radius;
  std::cout << "inf_d=" << d.leftBound() << "\n";
  if (!(d.leftBound() > 0)) return fail("separation_margin_not_positive");

  const Ival rhodot = (box.gx * box.px + box.gy * box.py) / rho;
  std::cout << "inf_rhodot=" << rhodot.leftBound() << "\n";
  if (!(rhodot.leftBound() > 0)) return fail("radial_speed_not_positive");

  const Ival e_rho = rhodot * rhodot / Ival(2) - total_m / d;
  std::cout << "inf_Erho=" << e_rho.leftBound() << "\n";
  if (!(e_rho.leftBound() > 0)) return fail("radial_energy_not_positive");

  const Ival v_inf = sqrt(Ival(2) * e_rho);
  const Ival root_arg = Ival(2) * pair_m * radius;  // 2M^2/eta > 0 always
  if (!(root_arg.leftBound() > 0)) return fail("tidal_root_not_positive");
  const Ival delta = escaper_m * sqrt(root_arg) / (v_inf * d * d);
  std::cout << "sup_Delta=" << delta.rightBound() << "\n";

  const Ival margin = -box.eta - e23 - delta;
  std::cout << "sup_E23=" << e23.rightBound() << "\n";
  std::cout << "inf_inner_margin=" << margin.leftBound() << "\n";
  if (!(margin.leftBound() > 0)) return fail("inner_energy_margin_not_positive");

  std::cout << "PASS_MIDDLE_ESCAPE_TERMINAL"
            << (box.phase_robust ? "_PHASE_ROBUST" : "")
            << (box.binary13 ? " binary={1,3} escaper=2" : " binary={2,3} escaper=1")
            << " eta=[" << box.eta.leftBound() << ","
            << box.eta.rightBound() << "] u=[" << box.u.leftBound() << ","
            << box.u.rightBound() << "]\n";
  return 0;
}

}  // namespace

int main(int argc, char** argv) {
  try {
    Box box;
    for (int i = 1; i < argc; ++i) {
      if (std::string(argv[i]) == "--phase-robust") box.phase_robust = true;
      if (std::string(argv[i]) == "--binary13") box.binary13 = true;
    }
    if (argc > 1 && std::string(argv[1]) == "--demo") {
      // Synthetic certifying box mirroring
      // tests/test_middle_escape_symbolic.py::_certifying_state at
      // u in [0.29, 0.29002]: tight slow binary, distant outgoing body 1.
      std::istringstream demo(
          "4 "
          "0.29 0.29002 "                       // u
          "0.316227766016 0.316227766017 0 0 "  // wr in sqrt(1/10), wi = 0
          "0 0 0.0316227766 0.0316227767 "      // z = conj(w) gdot/2
          "19.9 20.1 0.3 0.35 "                 // G
          "1.9 2.1 0.03 0.04");                 // P
      if (!read_box(demo, box)) return 2;
    } else {
      if (!read_box(std::cin, box)) return 2;
    }
    return check(box);
  } catch (const std::exception& error) {
    std::cout << "FAIL_MIDDLE_ESCAPE_TERMINAL(exception:" << error.what()
              << ")\n";
    return 2;
  }
}
