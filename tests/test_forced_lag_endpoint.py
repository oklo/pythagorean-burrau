"""Guard the endpoint issue that invalidated the old scalar one-switch proof."""

import sympy as sp


def test_one_switch_and_zero_terminal_value_do_not_force_positivity():
    s = sp.Symbol("s", positive=True)
    a = 1 / s + 1 / (1 - s)
    w = (1 - s) * (1 + s - 3 * s**2)
    q = (1 - s) * (1 / s + 2 - 9 * s)
    integrating_factor = s / (1 - s)
    assert sp.factor(sp.diff(w, s) + a * w - q) == 0
    assert sp.factor(sp.diff(integrating_factor, s) - a * integrating_factor) == 0
    assert w.subs(s, 0) == 1
    assert w.subs(s, 1) == 0
    assert sp.limit(integrating_factor * w, s, 1, dir="-") == -1
    # All sign changes on (0,1) are determined by these polynomial roots.
    forcing_roots = sp.solve(1 + 2 * s - 9 * s**2, s)
    w_roots = sp.solve(1 + s - 3 * s**2, s)
    assert forcing_roots == [(1 + sp.sqrt(10)) / 9]
    assert w_roots == [(1 + sp.sqrt(13)) / 6]
    assert 0 < forcing_roots[0] < w_roots[0] < 1
    assert w.subs(s, sp.Rational(9, 10)) < 0
