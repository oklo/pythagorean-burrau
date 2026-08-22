import sympy as sp

from src.symbolic.reduced_system import (
    normalized_initial_reduced_coordinates,
    reduced_expressions,
    symbols,
)


def test_initial_curve_in_reduced_coordinates() -> None:
    expr = reduced_expressions()
    coordinate_symbols = symbols()
    initial = normalized_initial_reduced_coordinates()
    substitution = {coordinate_symbols[key]: value for key, value in initial.items() if key != "u"}
    a, b = initial["m1"], initial["m2"]

    assert sp.simplify(expr["r12"].subs(substitution) - 1) == 0
    r13 = expr["r13"].subs(substitution)
    r23 = expr["r23"].subs(substitution)
    # Squaring avoids SymPy's inability to encode the additional assumption u < 1.
    assert sp.simplify(r13**2 - b**2) == 0
    assert sp.simplify(r23**2 - a**2) == 0
    assert sp.simplify(expr["I"].subs(substitution) - a * b) == 0
    initial_potential = a * b + a / b + b / a
    assert sp.simplify(initial_potential - (a * b + 1 / (a * b))) == 0
    assert sp.simplify(expr["K_reduced"].subs(substitution)) == 0
