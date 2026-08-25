"""Exact squared-mutual-distance equations for the planar three-body problem."""

from __future__ import annotations

from collections import defaultdict
from functools import lru_cache
from itertools import product

import sympy as sp


def squared_distance_accelerations() -> dict[str, sp.Expr]:
    m1, m2, m3 = sp.symbols("m1 m2 m3", positive=True)
    x, y, z = sp.symbols("x y z", positive=True)
    v23, v31, v12 = sp.symbols("v23sq v31sq v12sq", nonnegative=True)
    x_second = (
        2 * v23
        - 2 * (m2 + m3) / sp.sqrt(x)
        - m1 * ((x + z - y) / z ** sp.Rational(3, 2) + (x + y - z) / y ** sp.Rational(3, 2))
    )
    y_second = (
        2 * v31
        - 2 * (m3 + m1) / sp.sqrt(y)
        - m2 * ((y + x - z) / x ** sp.Rational(3, 2) + (y + z - x) / z ** sp.Rational(3, 2))
    )
    z_second = (
        2 * v12
        - 2 * (m1 + m2) / sp.sqrt(z)
        - m3 * ((z + y - x) / y ** sp.Rational(3, 2) + (z + x - y) / x ** sp.Rational(3, 2))
    )
    return {"x_second": x_second, "y_second": y_second, "z_second": z_second}


def torque_history_ratio_identity() -> sp.Expr:
    """Residual in ``h'=(f/A)(k-h)`` for two accumulated torque rates."""
    numerator_integral, denominator_integral = sp.symbols("B A", positive=True)
    numerator_rate, denominator_rate = sp.symbols("g f", positive=True)
    history_ratio = numerator_integral / denominator_integral
    instantaneous_ratio = numerator_rate / denominator_rate
    quotient_derivative = (
        numerator_rate * denominator_integral
        - numerator_integral * denominator_rate
    ) / denominator_integral**2
    return sp.factor(
        quotient_derivative
        - denominator_rate
        / denominator_integral
        * (instantaneous_ratio - history_ratio)
    )


def ordered_history_centrifugal_reduction() -> tuple[
    tuple[sp.Expr, sp.Expr], tuple[sp.Symbol, ...]
]:
    """Return the two scaled centrifugal gaps in ``(Z, eta)`` variables.

    Here ``x=r23/r12``, ``y=r31/r12``,
    ``Z=ell23**2/r12``, and
    ``eta=(m/n)(-ell31/ell23)``.  The weighted pair-angular-momentum
    identity at zero total momentum and angular momentum supplies
    ``ell12=-(1-eta)ell23/m``.
    """
    mass_1, mass_2, side_23, side_31, amplitude, history_ratio = sp.symbols(
        "m n x y Z eta", positive=True
    )
    first_gap = amplitude * (
        (1 - history_ratio) ** 2 / mass_1**2 - side_23**-3
    )
    second_gap = amplitude * (
        side_23**-3
        - mass_2**2
        * history_ratio**2
        / (mass_1**2 * side_31**3)
    )
    return (
        (first_gap, second_gap),
        (mass_1, mass_2, side_23, side_31, amplitude, history_ratio),
    )


def ordered_history_shape_time_rhs() -> tuple[
    tuple[sp.Expr, sp.Expr], tuple[sp.Symbol, ...]
]:
    """Return ``(W_s, eta_s)`` in Newtonian shape time ``ds=dt/R**(3/2)``."""
    mass_1, side_31, twice_area, amplitude, ratio, current = sp.symbols(
        "m y delta W eta k", positive=True
    )
    scale_rate = sp.symbols("sigma", real=True)
    torque_source = mass_1 * twice_area * (side_31**-3 - 1)
    amplitude_rhs = torque_source - scale_rate * amplitude / 2
    ratio_rhs = torque_source * (current - ratio) / amplitude
    return (
        (amplitude_rhs, ratio_rhs),
        (
            mass_1,
            side_31,
            twice_area,
            scale_rate,
            amplitude,
            ratio,
            current,
        ),
    )


@lru_cache(maxsize=1)
def log_torque_shape_threshold() -> tuple[
    sp.Expr, sp.Expr, tuple[sp.Symbol, ...]
]:
    """Return ``A`` and ``h`` in ``(log k)_s=(W/delta) A (eta-h)``."""
    mass_1, mass_2, side_23, side_31 = sp.symbols(
        "m n x y", positive=True
    )
    kernel = (
        -mass_2 * side_23**5
        - mass_2 * side_23**3 * side_31**2
        + mass_2 * side_23**3
        + mass_2 * side_23**2
        + 2 * mass_2 * side_31**5
        - mass_2 * side_31**2
        - mass_2
        + side_23**5 * side_31**2
        - side_23**3 * side_31**4
        + side_23**3 * side_31**2
        - side_23**2 * side_31**5
        + side_31**7
        + side_31**5
        - 2 * side_31**2
    )
    threshold = sp.factor(
        side_31**2
        * (
            2 * mass_1 * side_23**5
            - mass_1 * side_23**2 * side_31**3
            - mass_1 * side_23**2
            - mass_1 * side_31**5
            + mass_1 * side_31**3
            + mass_1 * side_31**2
            - mass_1
            + side_23**7
            - side_23**5 * side_31**2
            + side_23**5
            - side_23**4 * side_31**3
            + side_23**2 * side_31**5
            + side_23**2 * side_31**3
            - 2 * side_23**2
        )
        / (side_23**2 * kernel)
    )
    coefficient = sp.factor(
        -3
        * kernel
        / (
            2
            * mass_1
            * side_31**2
            * (side_23 - 1)
            * (side_31 - 1)
            * (side_23**2 + side_23 + 1)
            * (side_31**2 + side_31 + 1)
        )
    )
    return coefficient, threshold, (mass_1, mass_2, side_23, side_31)


@lru_cache(maxsize=1)
def log_torque_shape_rate_identity() -> sp.Expr:
    """Residual in the exact algebraic first-derivative threshold identity."""
    coefficient, threshold, variables = log_torque_shape_threshold()
    mass_1, mass_2, side_23, side_31 = variables
    amplitude, history_ratio, area = sp.symbols(
        "W eta delta", positive=True
    )
    scale_rate = sp.symbols("sigma", real=True)
    apex_x = (side_31**2 + 1 - side_23**2) / 2
    ell_23 = amplitude
    ell_31 = -(mass_2 / mass_1) * history_ratio * amplitude
    ell_12 = -(1 - history_ratio) * amplitude / mass_1
    velocity_3_y = (
        area * scale_rate
        - (apex_x - 1) * ell_12
        - ell_23
        + ell_31
    )
    velocity_3_x = (apex_x * velocity_3_y - ell_31) / area
    shape_23_rate = (
        (
            (apex_x - 1) * (velocity_3_x - scale_rate)
            + area * (velocity_3_y - ell_12)
        )
        / side_23
        - side_23 * scale_rate
    )
    shape_31_rate = (
        (apex_x * velocity_3_x + area * velocity_3_y) / side_31
        - side_31 * scale_rate
    )
    log_rate = 3 * (
        shape_31_rate / (side_31 * (1 - side_31**3))
        - shape_23_rate / (side_23 * (1 - side_23**3))
    )
    residual = sp.together(
        area * log_rate / amplitude
        - coefficient * (history_ratio - threshold)
    )
    numerator, denominator = sp.fraction(residual)
    area_squared = sp.factor(side_31**2 - apex_x**2)
    reduced_numerator = sp.expand(numerator).subs(area**2, area_squared)
    return sp.factor(reduced_numerator / denominator)


@lru_cache(maxsize=1)
def ordered_shape_log_torque_kernel() -> tuple[
    sp.Expr, tuple[sp.Symbol, ...]
]:
    """Return the signed linear-coefficient kernel on the ordered cube."""
    coefficient, _, physical_variables = log_torque_shape_threshold()
    mass_1, mass_2, side_23, side_31 = physical_variables
    # Remove the manifestly positive factors from A; this leaves -kernel.
    kernel = sp.factor(
        coefficient
        * 2
        * mass_1
        * side_31**2
        * (side_23 - 1)
        * (side_31 - 1)
        * (side_23**2 + side_23 + 1)
        * (side_31**2 + side_31 + 1)
        / 3
    )
    triangle_scale, order_split, parameter = sp.symbols(
        "t w v", nonnegative=True
    )
    tied_parameter = (sp.sqrt(2) - 1) * parameter
    substitution = {
        mass_1: (1 - tied_parameter**2) / (1 + tied_parameter**2),
        mass_2: 2 * tied_parameter / (1 + tied_parameter**2),
        side_23: 1 - triangle_scale * order_split / 2,
        side_31: 1 - triangle_scale + triangle_scale * order_split / 2,
    }
    return (
        sp.factor(sp.together(kernel.subs(substitution))),
        (triangle_scale, order_split, parameter),
    )


@lru_cache(maxsize=1)
def ordered_shape_log_torque_kernel_bernstein_coefficients() -> tuple[
    sp.Expr, ...
]:
    """Exact Bernstein certificate for positivity of the linear kernel."""
    kernel, variables = ordered_shape_log_torque_kernel()
    numerator, _ = sp.fraction(kernel)
    return _tensor_bernstein_coefficients(numerator, variables)


@lru_cache(maxsize=1)
def initial_log_torque_threshold_gap() -> tuple[sp.Expr, sp.Symbol]:
    """Return ``h(initial shape)-k(initial shape)`` on the tied family."""
    _, threshold, variables = log_torque_shape_threshold()
    mass_1, mass_2, side_23, side_31 = variables
    parameter = sp.symbols("u", positive=True)
    tied_mass_1 = (1 - parameter**2) / (1 + parameter**2)
    tied_mass_2 = 2 * parameter / (1 + parameter**2)
    substitution = {
        mass_1: tied_mass_1,
        mass_2: tied_mass_2,
        side_23: tied_mass_1,
        side_31: tied_mass_2,
    }
    initial_current_ratio = (
        tied_mass_1**-3 - 1
    ) / (tied_mass_2**-3 - 1)
    return (
        sp.factor(threshold.subs(substitution) - initial_current_ratio),
        parameter,
    )


@lru_cache(maxsize=1)
def ordered_shape_log_torque_threshold_gap_core() -> tuple[
    sp.Expr, tuple[sp.Symbol, ...]
]:
    """Return a positive-denominator-equivalent core for ``h-k``."""
    _, threshold, physical_variables = log_torque_shape_threshold()
    mass_1, mass_2, side_23, side_31 = physical_variables
    current_ratio = (
        side_31**3 * (1 - side_23**3)
        / (side_23**3 * (1 - side_31**3))
    )
    gap_numerator, _ = sp.fraction(
        sp.factor(sp.together(threshold - current_ratio))
    )
    triangle_scale, order_split, parameter = sp.symbols(
        "t w v", nonnegative=True
    )
    tied_parameter = (sp.sqrt(2) - 1) * parameter
    substitution = {
        mass_1: (1 - tied_parameter**2) / (1 + tied_parameter**2),
        mass_2: 2 * tied_parameter / (1 + tied_parameter**2),
        side_23: 1 - triangle_scale * order_split / 2,
        side_31: 1 - triangle_scale + triangle_scale * order_split / 2,
    }
    return (
        sp.factor(sp.together(gap_numerator.subs(substitution))),
        (triangle_scale, order_split, parameter),
    )


@lru_cache(maxsize=1)
def ordered_shape_log_torque_threshold_gap_bernstein_coefficients() -> tuple[
    sp.Expr, ...
]:
    """Exact Bernstein certificate for ``h>k`` on the ordered cube."""
    core, variables = ordered_shape_log_torque_threshold_gap_core()
    numerator, _ = sp.fraction(core)
    return _tensor_bernstein_coefficients(numerator, variables)


@lru_cache(maxsize=1)
def log_torque_threshold_contact_terms() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, tuple[sp.Symbol, ...]
]:
    """Return ``P,S,h`` in ``W*delta*(eta-h)_s=P-Z*S`` at contact."""
    _, threshold, variables = log_torque_shape_threshold()
    mass_1, mass_2, side_23, side_31 = variables
    history_ratio = sp.symbols("eta", positive=True)
    area_squared = sp.factor(
        side_31**2
        - ((side_31**2 + 1 - side_23**2) / 2) ** 2
    )
    scaled_23_rate = sp.factor(
        (
            -2 * history_ratio * mass_2 * side_23**2
            + history_ratio * side_23**4
            - history_ratio * side_23**2 * side_31**2
            - history_ratio * side_23**2
            - mass_1 * side_23**2
            - mass_1 * side_31**2
            + mass_1
            - side_23**4
            + side_23**2 * side_31**2
            + side_23**2
        )
        / (2 * mass_1 * side_23)
    )
    scaled_31_rate = sp.factor(
        (
            -history_ratio * mass_2 * side_23**2
            - history_ratio * mass_2 * side_31**2
            + history_ratio * mass_2
            + history_ratio * side_23**2 * side_31**2
            - history_ratio * side_31**4
            + history_ratio * side_31**2
            - 2 * mass_1 * side_31**2
            - side_23**2 * side_31**2
            + side_31**4
            - side_31**2
        )
        / (2 * mass_1 * side_31)
    )
    threshold_shape_rate = sp.factor(
        (
            sp.diff(threshold, side_23) * scaled_23_rate
            + sp.diff(threshold, side_31) * scaled_31_rate
        ).subs(history_ratio, threshold)
    )
    current_ratio = (
        side_23**-3 - 1
    ) / (side_31**-3 - 1)
    history_source = sp.factor(
        mass_1
        * area_squared
        * (side_31**-3 - 1)
        * (current_ratio - threshold)
    )
    return (
        history_source,
        threshold_shape_rate,
        threshold,
        variables,
    )


@lru_cache(maxsize=1)
def _radial_gravity_terms() -> tuple[tuple[sp.Expr, ...], tuple[sp.Symbol, ...]]:
    """Return unscaled radial gravity terms for tied masses."""
    expressions = squared_distance_accelerations()
    m1, m2, m3 = sp.symbols("m1 m2 m3", positive=True)
    x, y, z = sp.symbols("x y z", positive=True)
    v23, v31, v12 = sp.symbols("v23sq v31sq v12sq", nonnegative=True)
    r23, r31, r12 = sp.symbols("a b c", positive=True)
    u = sp.symbols("u", positive=True)
    mass_a = (1 - u**2) / (1 + u**2)
    mass_b = 2 * u / (1 + u**2)
    substitution = {
        m1: mass_a,
        m2: mass_b,
        m3: 1,
        x: r23**2,
        y: r31**2,
        z: r12**2,
        v23: 0,
        v31: 0,
        v12: 0,
    }
    gravity_23 = expressions["x_second"].subs(substitution) / (2 * r23)
    gravity_31 = expressions["y_second"].subs(substitution) / (2 * r31)
    gravity_12 = expressions["z_second"].subs(substitution) / (2 * r12)
    return (gravity_12, gravity_23, gravity_31), (r23, r31, r12, u)


@lru_cache(maxsize=1)
def _radial_gravity_gaps() -> tuple[sp.Expr, sp.Expr, tuple[sp.Symbol, ...]]:
    """Return unscaled g12-g23 and g23-g31 for tied masses."""
    gravity, variables = _radial_gravity_terms()
    gravity_12, gravity_23, gravity_31 = gravity
    return gravity_12 - gravity_23, gravity_23 - gravity_31, variables


@lru_cache(maxsize=1)
def ordered_shape_gravity_gap() -> tuple[sp.Expr, tuple[sp.Symbol, ...]]:
    """Return g_23-g_31 on the ordered-triangle/fundamental-parameter cube."""
    _, second_gap, physical_variables = _radial_gravity_gaps()
    r23, r31, r12, u = physical_variables
    triangle_scale, order_split, parameter = sp.symbols(
        "t w v", nonnegative=True
    )
    cube_substitution = {
        r23: 1 - triangle_scale * order_split / 2,
        r31: 1 - triangle_scale + triangle_scale * order_split / 2,
        r12: 1,
        u: (sp.sqrt(2) - 1) * parameter,
    }
    gap = sp.factor(
        sp.together(second_gap.subs(cube_substitution))
    )
    return gap, (triangle_scale, order_split, parameter)


def _tensor_bernstein_coefficients(
    numerator: sp.Expr, variables: tuple[sp.Symbol, ...]
) -> tuple[sp.Expr, ...]:
    polynomial = sp.Poly(numerator, *variables)
    degrees = tuple(polynomial.degree(variable) for variable in variables)
    coefficients = dict(polynomial.terms())
    for axis, degree in enumerate(degrees):
        grouped: defaultdict[tuple[int, ...], dict[int, sp.Expr]] = defaultdict(
            dict
        )
        for exponent, value in coefficients.items():
            other = exponent[:axis] + exponent[axis + 1 :]
            grouped[other][exponent[axis]] = value
        transformed: dict[tuple[int, ...], sp.Expr] = {}
        for other, power_line in grouped.items():
            for order in range(degree + 1):
                value = sum(
                    coefficient
                    * sp.binomial(order, exponent)
                    / sp.binomial(degree, exponent)
                    for exponent, coefficient in power_line.items()
                    if exponent <= order
                )
                key = other[:axis] + (order,) + other[axis:]
                # Only rational binomial factors are introduced here.  An
                # expansion keeps coefficients in canonical Q(sqrt(2)) form
                # and is dramatically faster than general-purpose simplify
                # for the four-dimensional certificate below.
                transformed[key] = sp.expand(value)
        coefficients = transformed
    return tuple(
        coefficients[order]
        for order in product(*(range(degree + 1) for degree in degrees))
    )


def _clear_tied_syzygy_polynomial(
    expression: sp.Expr,
    physical_variables: tuple[sp.Symbol, sp.Symbol, sp.Symbol],
) -> tuple[sp.Expr, tuple[sp.Symbol, sp.Symbol]]:
    """Pull a polynomial in ``(m,n,y)`` back to the tied syzygy square.

    The square coordinates are

    ``u=(sqrt(2)-1)*v`` and ``y=n*z/(m+n)``.

    All omitted factors are positive on ``0<v<=1, 0<z<1``.  This is the
    torque-compatible ordered-syzygy domain because the collinear torque
    ratio is less than one exactly when ``y<n/(m+n)``.
    """
    mass_1, mass_2, side_31 = physical_variables
    polynomial = sp.Poly(sp.expand(expression), mass_1, mass_2, side_31)
    parameter, syzygy_fraction = sp.symbols("v z", nonnegative=True)
    tied_parameter = (sp.sqrt(2) - 1) * parameter
    mass_denominator = 1 + tied_parameter**2
    mass_1_numerator = 1 - tied_parameter**2
    mass_2_numerator = 2 * tied_parameter
    mass_sum_numerator = mass_1_numerator + mass_2_numerator
    maximum_mass_degree = max(
        exponent[0] + exponent[1] for exponent, _ in polynomial.terms()
    )
    maximum_side_degree = polynomial.degree(side_31)
    cleared = sum(
        coefficient
        * mass_1_numerator ** exponent[0]
        * mass_2_numerator ** (exponent[1] + exponent[2])
        * syzygy_fraction ** exponent[2]
        * mass_denominator
        ** (maximum_mass_degree - exponent[0] - exponent[1])
        * mass_sum_numerator
        ** (maximum_side_degree - exponent[2])
        for exponent, coefficient in polynomial.terms()
    )
    return sp.expand(cleared), (parameter, syzygy_fraction)


@lru_cache(maxsize=1)
def ordered_shape_gravity_bernstein_coefficients() -> tuple[sp.Expr, ...]:
    """Exact tensor Bernstein certificate for ``ordered_shape_gravity_gap``."""
    gap, variables = ordered_shape_gravity_gap()
    numerator, _ = sp.fraction(gap)
    return _tensor_bernstein_coefficients(numerator, variables)


@lru_cache(maxsize=1)
def ordered_obtuse_gravity_first_gap() -> tuple[sp.Expr, tuple[sp.Symbol, ...]]:
    """Return g_12-g_23 on a rectangle containing every ordered obtuse shape."""
    first_gap, _, physical_variables = _radial_gravity_gaps()
    r23, r31, r12, u = physical_variables
    depth, order_split, parameter = sp.symbols("s w v", nonnegative=True)
    lower_scale = 2 - sp.sqrt(2)
    triangle_scale = lower_scale + (1 - lower_scale) * depth
    cube_substitution = {
        r23: 1 - triangle_scale * order_split / 2,
        r31: 1 - triangle_scale + triangle_scale * order_split / 2,
        r12: 1,
        u: (sp.sqrt(2) - 1) * parameter,
    }
    gap = sp.factor(sp.together(first_gap.subs(cube_substitution)))
    return gap, (depth, order_split, parameter)


@lru_cache(maxsize=1)
def ordered_obtuse_gravity_first_bernstein_coefficients() -> tuple[sp.Expr, ...]:
    """Exact tensor Bernstein certificate for the first gravitational gap."""
    gap, variables = ordered_obtuse_gravity_first_gap()
    numerator, _ = sp.fraction(gap)
    return _tensor_bernstein_coefficients(numerator, variables)


@lru_cache(maxsize=1)
def ordered_obtuse_log_torque_ratio_gravity_curvature() -> tuple[
    sp.Expr, tuple[sp.Symbol, ...]
]:
    """Return the gravity contribution to ``(log k)''`` on the obtuse cube."""
    gravity, physical_variables = _radial_gravity_terms()
    gravity_12, gravity_23, gravity_31 = gravity
    r23, r31, r12, u = physical_variables
    depth, order_split, parameter = sp.symbols("s w v", nonnegative=True)
    lower_scale = 2 - sp.sqrt(2)
    triangle_scale = lower_scale + (1 - lower_scale) * depth
    side_23 = 1 - triangle_scale * order_split / 2
    side_31 = 1 - triangle_scale + triangle_scale * order_split / 2
    tied_parameter = (sp.sqrt(2) - 1) * parameter
    substitution = {
        r23: side_23,
        r31: side_31,
        r12: 1,
        u: tied_parameter,
    }
    radial_12 = gravity_12.subs(substitution)
    radial_23 = gravity_23.subs(substitution)
    radial_31 = gravity_31.subs(substitution)
    ratio_23_second = radial_23 - side_23 * radial_12
    ratio_31_second = radial_31 - side_31 * radial_12
    curvature = sp.factor(
        sp.together(
            3 * ratio_31_second / (side_31 * (1 - side_31**3))
            - 3 * ratio_23_second / (side_23 * (1 - side_23**3))
        )
    )
    return curvature, (depth, order_split, parameter)


@lru_cache(maxsize=1)
def ordered_obtuse_log_torque_ratio_gravity_bernstein_coefficients() -> tuple[
    sp.Expr, ...
]:
    """Exact Bernstein coefficients for the gravity curvature numerator."""
    curvature, variables = ordered_obtuse_log_torque_ratio_gravity_curvature()
    numerator, _ = sp.fraction(curvature)
    return _tensor_bernstein_coefficients(numerator, variables)


@lru_cache(maxsize=1)
def _generic_ordered_syzygy_first_gap_energy_margin() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, tuple[sp.Symbol, ...]
]:
    """Generic sharp first-gap energy margin on an ordered syzygy.

    The variables are masses ``m,n`` and ``y=r31/r12``; ``r23/r12=1-y``.
    """
    mass_1, mass_2, side_31 = sp.symbols("m n q", positive=True)
    side_23 = 1 - side_31
    torque_ratio = sp.factor(
        side_31
        * (mass_1 + side_23)
        / (side_23 * (mass_2 + side_31))
    )
    kinetic_coefficient = sp.factor(
        mass_2
        * (
            mass_1 * mass_2
            + mass_1 * side_31**2
            + mass_2 * side_31**2
            - 2 * mass_2 * side_31
            + mass_2
        )
        / (
            mass_1
            * side_23**2
            * (mass_2 + side_31) ** 2
        )
    )
    potential = (
        mass_1 * mass_2 + mass_2 / side_23 + mass_1 / side_31
    )
    centrifugal_coefficient = sp.factor(
        (1 - torque_ratio) ** 2 / mass_1**2 - 1 / side_23**3
    )
    expressions = squared_distance_accelerations()
    m1, m2, m3 = sp.symbols("m1 m2 m3", positive=True)
    x_squared, y_squared, r12_squared = sp.symbols("x y z", positive=True)
    v23, v31, v12 = sp.symbols("v23sq v31sq v12sq", nonnegative=True)
    substitution = {
        m1: mass_1,
        m2: mass_2,
        m3: 1,
        x_squared: side_23**2,
        y_squared: side_31**2,
        r12_squared: 1,
        v23: 0,
        v31: 0,
        v12: 0,
    }
    gravity_gap = (
        expressions["z_second"].subs(substitution) / 2
        - expressions["x_second"].subs(substitution) / (2 * side_23)
    ).subs(
        {
            sp.Abs(side_31 - 1): 1 - side_31,
            sp.Abs(side_31**2 - 1): 1 - side_31**2,
        }
    )
    margin = sp.factor(
        sp.cancel(
            gravity_gap
            + 2
            * potential
            * centrifugal_coefficient
            / kinetic_coefficient
        )
    )
    return (
        margin,
        kinetic_coefficient,
        torque_ratio,
        (mass_1, mass_2, side_31),
    )


@lru_cache(maxsize=1)
def ordered_syzygy_longitudinal_kinetic_decomposition() -> tuple[
    dict[str, sp.Expr], tuple[sp.Symbol, ...]
]:
    """Diagonalize longitudinal kinetic energy on an ordered syzygy.

    Here ``R=r12``, ``q=r31/R``, ``sigma=R_s/R`` and ``Q=q_s`` in
    Newtonian shape time ``ds=dt/R**(3/2)``.  The returned quantity
    ``scaled_longitudinal`` is ``2*K_parallel*R``.
    """
    mass_1, mass_2, side_31, scale = sp.symbols(
        "m n q R", positive=True
    )
    scale_rate, shape_rate = sp.symbols("sigma Q", real=True)
    total_mass = mass_1 + mass_2 + 1
    side_23 = 1 - side_31
    inertia_core = sp.factor(
        mass_1 * mass_2
        + mass_1 * side_31**2
        + mass_2 * side_23**2
    )
    cross_core = (mass_1 + mass_2) * side_31 - mass_2

    physical_scale_rate = scale_rate / sp.sqrt(scale)
    physical_shape_rate = shape_rate / scale ** sp.Rational(3, 2)
    relative_12 = physical_scale_rate
    relative_13 = (
        side_31 * physical_scale_rate + scale * physical_shape_rate
    )
    velocity_1 = sp.factor(
        -(mass_2 * relative_12 + relative_13) / total_mass
    )
    velocity_2 = velocity_1 + relative_12
    velocity_3 = velocity_1 + relative_13
    twice_longitudinal = sp.factor(
        mass_1 * velocity_1**2
        + mass_2 * velocity_2**2
        + velocity_3**2
    )
    scaled_longitudinal = sp.factor(scale * twice_longitudinal)
    diagonal = sp.factor(
        inertia_core
        / total_mass
        * (scale_rate + cross_core * shape_rate / inertia_core) ** 2
        + mass_1 * mass_2 * shape_rate**2 / inertia_core
    )
    inertia = sp.factor(scale**2 * inertia_core / total_mass)
    inertia_derivative = sp.factor(
        2
        * sp.sqrt(scale)
        * (inertia_core * scale_rate + cross_core * shape_rate)
        / total_mass
    )
    dilational_shape_form = sp.factor(
        scale * inertia_derivative**2 / (4 * inertia)
        + mass_1 * mass_2 * shape_rate**2 / inertia_core
    )
    return (
        {
            "inertia_core": inertia_core,
            "cross_core": cross_core,
            "velocity_1": velocity_1,
            "velocity_2": velocity_2,
            "velocity_3": velocity_3,
            "scaled_longitudinal": scaled_longitudinal,
            "diagonal": diagonal,
            "inertia": inertia,
            "inertia_derivative": inertia_derivative,
            "dilational_shape_form": dilational_shape_form,
            "diagonal_residual": sp.factor(scaled_longitudinal - diagonal),
            "dilational_residual": sp.factor(
                diagonal - dilational_shape_form
            ),
        },
        (mass_1, mass_2, side_31, scale, scale_rate, shape_rate),
    )


@lru_cache(maxsize=1)
def ordered_syzygy_torque_energy_threshold() -> tuple[
    dict[str, sp.Expr], tuple[sp.Symbol, ...]
]:
    """Return the exact energy deficit equivalent to ``Z<ZJ`` at syzygy."""
    torque_data, torque_variables = _generic_ordered_syzygy_torque_thresholds()
    mass_1, mass_2, side_31 = torque_variables
    _, kinetic_coefficient, _, kinetic_variables = (
        _generic_ordered_syzygy_first_gap_energy_margin()
    )
    kinetic_mass_1, kinetic_mass_2, kinetic_side_31 = kinetic_variables
    kinetic_coefficient = kinetic_coefficient.subs(
        {
            kinetic_mass_1: mass_1,
            kinetic_mass_2: mass_2,
            kinetic_side_31: side_31,
        }
    )
    scale = sp.symbols("R", positive=True)
    side_23 = 1 - side_31
    shape_potential = sp.factor(
        mass_1 * mass_2 + mass_2 / side_23 + mass_1 / side_31
    )
    initial_potential = sp.factor(
        mass_1 * mass_2 + 1 / (mass_1 * mass_2)
    )
    critical_scale = sp.factor(
        (
            shape_potential
            - kinetic_coefficient * torque_data["ZJ"] / 2
        )
        / initial_potential
    )
    longitudinal_deficit = sp.factor(
        2 * (shape_potential - initial_potential * scale)
        - kinetic_coefficient * torque_data["ZJ"]
    )
    return (
        {
            "F": sp.factor(kinetic_coefficient),
            "U": shape_potential,
            "U0": initial_potential,
            "ZJ": torque_data["ZJ"],
            "critical_scale": critical_scale,
            "longitudinal_deficit": longitudinal_deficit,
            "deficit_residual": sp.factor(
                longitudinal_deficit
                - 2 * initial_potential * (critical_scale - scale)
            ),
        },
        (mass_1, mass_2, side_31, scale),
    )


@lru_cache(maxsize=1)
def ordered_syzygy_critical_scale_monotonicity_core() -> tuple[
    sp.Expr, tuple[sp.Symbol, ...]
]:
    """Cleared numerator proving that ``RJ`` decreases with syzygy ``q``.

    Only the positive factors ``m*n`` are removed from the numerator of
    ``dRJ/dq`` before pulling it back by
    ``u=(sqrt(2)-1)*v`` and ``q=n*z/(m+n)``.  The derivative denominator is
    a product of positive factors and the square of the already certified
    contact-denominator core.
    """
    threshold, variables = ordered_syzygy_torque_energy_threshold()
    mass_1, mass_2, side_31, _ = variables
    derivative = sp.factor(sp.diff(threshold["critical_scale"], side_31))
    numerator, _ = sp.fraction(derivative)
    numerator_core = sp.factor(numerator / (mass_1 * mass_2))
    return _clear_tied_syzygy_polynomial(
        numerator_core, (mass_1, mass_2, side_31)
    )


@lru_cache(maxsize=1)
def ordered_syzygy_critical_scale_monotonicity_bernstein_coefficients() -> tuple[
    sp.Expr, ...
]:
    """Exact tensor-Bernstein certificate for ``dRJ/dq<0``."""
    core, variables = ordered_syzygy_critical_scale_monotonicity_core()
    return _tensor_bernstein_coefficients(core, variables)


@lru_cache(maxsize=1)
def ordered_syzygy_small_longitudinal_sign_witness() -> tuple[
    dict[str, sp.Expr], tuple[sp.Symbol, ...]
]:
    """Strict gap/dilation signs with arbitrarily small longitudinal energy.

    The direction is multiplied by an arbitrary ``epsilon>0``.  It proves
    that signs of both side-gap rates and ``I_dot`` cannot provide the
    positive coercive lower bound required by ``Z<ZJ``.
    """
    kinetic, variables = ordered_syzygy_longitudinal_kinetic_decomposition()
    mass_1, mass_2, side_31, scale, scale_rate, shape_rate = variables
    epsilon = sp.symbols("epsilon", positive=True)
    inertia_core = kinetic["inertia_core"]
    torque_margin = mass_2 - (mass_1 + mass_2) * side_31
    lower_slope = (1 - 2 * side_31) / 2
    upper_slope = inertia_core / torque_margin
    slope = sp.factor((lower_slope + upper_slope) / 2)
    substitution = {
        scale_rate: -epsilon,
        shape_rate: -epsilon * slope,
    }
    side_31_rate = sp.factor(
        side_31 * substitution[scale_rate] + substitution[shape_rate]
    )
    second_gap_rate = sp.factor(
        (1 - 2 * side_31) * substitution[scale_rate]
        - 2 * substitution[shape_rate]
    )
    dilation_core = sp.factor(
        inertia_core * substitution[scale_rate]
        + kinetic["cross_core"] * substitution[shape_rate]
    )
    return (
        {
            "torque_margin": torque_margin,
            "lower_slope": lower_slope,
            "upper_slope": upper_slope,
            "slope": slope,
            "slope_interval_numerator": sp.factor(
                2 * inertia_core
                - torque_margin * (1 - 2 * side_31)
            ),
            "side_31_rate": side_31_rate,
            "second_gap_rate": second_gap_rate,
            "dilation_core": dilation_core,
            "scaled_longitudinal": sp.factor(
                kinetic["scaled_longitudinal"].subs(substitution)
            ),
        },
        (mass_1, mass_2, side_31, scale, epsilon),
    )


@lru_cache(maxsize=1)
def ordered_syzygy_first_gap_energy_numerator() -> tuple[
    sp.Expr, tuple[sp.Symbol, ...]
]:
    """Positive-denominator-cleared numerator on the tied syzygy square."""
    generic_margin, _, _, generic_variables = (
        _generic_ordered_syzygy_first_gap_energy_margin()
    )
    mass_1, mass_2, side_31 = generic_variables
    generic_numerator, _ = sp.fraction(generic_margin)
    polynomial = sp.Poly(generic_numerator, mass_1, mass_2, side_31)
    parameter, syzygy_fraction = sp.symbols("v z", nonnegative=True)
    tied_parameter = (sp.sqrt(2) - 1) * parameter
    mass_denominator = 1 + tied_parameter**2
    mass_1_numerator = 1 - tied_parameter**2
    mass_2_numerator = 2 * tied_parameter
    mass_sum_numerator = mass_1_numerator + mass_2_numerator
    maximum_mass_degree = max(
        exponent[0] + exponent[1] for exponent, _ in polynomial.terms()
    )
    maximum_side_degree = polynomial.degree(side_31)
    cleared = sum(
        coefficient
        * mass_1_numerator ** exponent[0]
        * mass_2_numerator ** (exponent[1] + exponent[2])
        * syzygy_fraction ** exponent[2]
        * mass_denominator
        ** (maximum_mass_degree - exponent[0] - exponent[1])
        * mass_sum_numerator
        ** (maximum_side_degree - exponent[2])
        for exponent, coefficient in polynomial.terms()
    )
    return sp.expand(cleared), (parameter, syzygy_fraction)


@lru_cache(maxsize=1)
def ordered_syzygy_first_gap_energy_bernstein_coefficients() -> tuple[
    sp.Expr, ...
]:
    """Exact Bernstein certificate for the ordered-syzygy first gap."""
    numerator, variables = ordered_syzygy_first_gap_energy_numerator()
    return _tensor_bernstein_coefficients(numerator, variables)


@lru_cache(maxsize=1)
def _generic_ordered_syzygy_torque_thresholds() -> tuple[
    dict[str, sp.Expr], tuple[sp.Symbol, ...]
]:
    """Exact torque-contact data on the ordered syzygy ``x+y=1``.

    The variables are masses ``m,n`` and ``y=r31/r12``.  The strict
    pre-syzygy torque signs give ``0<eta<1``, which on this face is
    equivalent to ``0<y<n/(m+n)``.
    """
    history_source, shape_source, threshold, variables = (
        log_torque_threshold_contact_terms()
    )
    mass_1, mass_2, side_23, side_31 = variables
    syzygy_side_23 = 1 - side_31
    torque_ratio = sp.factor(
        side_31
        * (mass_1 + syzygy_side_23)
        / (syzygy_side_23 * (mass_2 + side_31))
    )
    threshold_residual = sp.factor(
        threshold.subs(side_23, syzygy_side_23) - torque_ratio
    )
    syzygy_history_source = sp.factor(
        history_source.subs(side_23, syzygy_side_23)
    )
    syzygy_shape_source = sp.factor(
        shape_source.subs(side_23, syzygy_side_23)
    )
    apex_x = (side_31**2 + 1 - side_23**2) / 2
    area_squared = sp.factor(side_31**2 - apex_x**2)
    reduced_history_source = sp.factor(sp.cancel(history_source / area_squared))
    reduced_shape_source = sp.factor(sp.cancel(shape_source / area_squared))
    # Both contact terms contain the same exact area-squared factor.  Removing
    # it gives a path-independent rational extension to the syzygy face.
    contact_limit = sp.factor(
        (reduced_history_source / reduced_shape_source).subs(
            side_23, syzygy_side_23
        )
    )
    centrifugal_coefficient = sp.factor(
        syzygy_side_23**-3
        - mass_2**2
        * torque_ratio**2
        / (mass_1**2 * side_31**3)
    )
    gravity_gap = sp.factor(
        mass_2
        - mass_1
        + (2 * mass_1 + 1) / side_31**2
        - (2 * mass_2 + 1) / syzygy_side_23**2
    )
    second_gap_threshold = sp.factor(
        gravity_gap / (-centrifugal_coefficient)
    )
    threshold_difference = sp.factor(
        sp.together(second_gap_threshold - contact_limit)
    )
    return (
        {
            "eta": torque_ratio,
            "h_minus_eta": threshold_residual,
            "P": syzygy_history_source,
            "S": syzygy_shape_source,
            "P_reduced": reduced_history_source,
            "S_reduced": reduced_shape_source,
            "area_squared": area_squared,
            "ZJ": contact_limit,
            "C2": centrifugal_coefficient,
            "G2": gravity_gap,
            "Z2": second_gap_threshold,
            "Z2_minus_ZJ": threshold_difference,
        },
        (mass_1, mass_2, side_31),
    )


@lru_cache(maxsize=1)
def ordered_syzygy_torque_amplitude_sign_cores() -> tuple[
    dict[str, sp.Expr], tuple[sp.Symbol, ...]
]:
    """Return five cleared sign cores proving ``1<ZJ<Z2``.

    On the tied syzygy square the signs are respectively
    ``N_J<0``, ``D_J>0``, ``E_2<0``, ``Q>0``, and the numerator of
    ``ZJ-1`` is positive.  Manifest factors then give ``ZJ>1``, ``C2<0``,
    and ``Z2-ZJ>0``.
    """
    data, variables = _generic_ordered_syzygy_torque_thresholds()
    mass_1, mass_2, side_31 = variables
    contact_numerator, contact_denominator = sp.fraction(data["ZJ"])
    contact_numerator_core = sp.factor(
        contact_numerator
        / (
            2
            * mass_1**2
            * (mass_2 + side_31) ** 2
            * (side_31 - 1)
            * (side_31**2 - side_31 + 2)
        )
    )
    contact_denominator_core = sp.factor(
        contact_denominator
        / (
            side_31
            * (
                mass_1 * mass_2
                + mass_1 * side_31**2
                + mass_2 * side_31**2
                - 2 * mass_2 * side_31
                + mass_2
            )
        )
    )
    second_numerator, _ = sp.fraction(data["C2"])
    second_coefficient_core = sp.factor(-second_numerator)
    difference_numerator, _ = sp.fraction(data["Z2_minus_ZJ"])
    difference_core = sp.factor(
        difference_numerator
        / (
            -mass_1**2
            * (mass_2 + side_31) ** 2
            * (side_31 - 1)
            * (2 * side_31 - 1)
        )
    )
    unit_margin_numerator, _ = sp.fraction(sp.factor(data["ZJ"] - 1))
    physical_cores = {
        "contact_numerator": contact_numerator_core,
        "contact_denominator": contact_denominator_core,
        "second_coefficient": second_coefficient_core,
        "difference": difference_core,
        "unit_margin": unit_margin_numerator,
    }
    cleared: dict[str, sp.Expr] = {}
    cube_variables: tuple[sp.Symbol, ...] | None = None
    for name, expression in physical_cores.items():
        cleared_expression, current_variables = _clear_tied_syzygy_polynomial(
            expression, variables
        )
        cleared[name] = cleared_expression
        if cube_variables is None:
            cube_variables = current_variables
        else:
            assert current_variables == cube_variables
    assert cube_variables is not None
    return cleared, cube_variables


@lru_cache(maxsize=1)
def ordered_syzygy_torque_amplitude_bernstein_coefficients() -> dict[
    str, tuple[sp.Expr, ...]
]:
    """Exact tensor-Bernstein certificates for the five amplitude cores."""
    cores, variables = ordered_syzygy_torque_amplitude_sign_cores()
    return {
        name: _tensor_bernstein_coefficients(core, variables)
        for name, core in cores.items()
    }


@lru_cache(maxsize=1)
def ordered_syzygy_endpoint_corner_blowup() -> tuple[
    dict[str, sp.Expr], tuple[sp.Symbol, ...]
]:
    """Resolve the singular equal-mass/torque-edge corner of ``ZJ`` and ``RJ``.

    Put ``u=(sqrt(2)-1)v`` and ``q=n*z/(m+n)``.  Along
    ``v=1-epsilon`` and ``z=1-lambda*epsilon``, the two thresholds have
    finite direction-dependent limits.  The returned derivative residuals
    independently recover the limits from the first directional jets of the
    exact rational functions at ``(v,z)=(1,1)``.
    """
    threshold, physical_variables = ordered_syzygy_torque_energy_threshold()
    mass_1, mass_2, side_31, _ = physical_variables
    parameter, syzygy_fraction, slope = sp.symbols(
        "v z lambda", nonnegative=True
    )
    tied_parameter = (sp.sqrt(2) - 1) * parameter
    tied_mass_1 = (1 - tied_parameter**2) / (1 + tied_parameter**2)
    tied_mass_2 = 2 * tied_parameter / (1 + tied_parameter**2)
    tied_side_31 = (
        tied_mass_2 * syzygy_fraction / (tied_mass_1 + tied_mass_2)
    )
    substitution = {
        mass_1: tied_mass_1,
        mass_2: tied_mass_2,
        side_31: tied_side_31,
    }

    corner_limits: dict[str, sp.Expr] = {}
    directional_residuals: dict[str, sp.Expr] = {}
    corner_numerators: dict[str, sp.Expr] = {}
    corner_denominators: dict[str, sp.Expr] = {}
    kappa = (28 - 3 * sp.sqrt(2)) / 11
    endpoint_values = {
        "ZJ": (
            21 * (1 + sp.sqrt(2)) / 22,
            (3836 + 2709 * sp.sqrt(2)) / 6128,
        ),
        "critical_scale": (
            (11 + 2 * sp.sqrt(2)) / 55,
            (-361 + 2273 * sp.sqrt(2)) / 3830,
        ),
    }
    for name, (zero_slope, infinite_slope) in endpoint_values.items():
        corner_limit = sp.factor(
            (zero_slope + kappa * slope * infinite_slope)
            / (1 + kappa * slope)
        )
        corner_limits[name] = corner_limit

        tied_expression = sp.together(threshold[name].subs(substitution))
        numerator, denominator = sp.fraction(tied_expression)
        corner_numerators[name] = sp.factor(
            numerator.subs({parameter: 1, syzygy_fraction: 1})
        )
        corner_denominators[name] = sp.factor(
            denominator.subs({parameter: 1, syzygy_fraction: 1})
        )
        numerator_jet = (
            sp.diff(numerator, parameter)
            + slope * sp.diff(numerator, syzygy_fraction)
        ).subs({parameter: 1, syzygy_fraction: 1})
        denominator_jet = (
            sp.diff(denominator, parameter)
            + slope * sp.diff(denominator, syzygy_fraction)
        ).subs({parameter: 1, syzygy_fraction: 1})
        directional_residuals[name] = sp.factor(
            numerator_jet - corner_limit * denominator_jet
        )

    return (
        {
            "kappa": kappa,
            "ZJ_zero_slope": endpoint_values["ZJ"][0],
            "ZJ_infinite_slope": endpoint_values["ZJ"][1],
            "ZJ_limit": corner_limits["ZJ"],
            "critical_scale_zero_slope": endpoint_values[
                "critical_scale"
            ][0],
            "critical_scale_infinite_slope": endpoint_values[
                "critical_scale"
            ][1],
            "critical_scale_limit": corner_limits["critical_scale"],
            "ZJ_directional_residual": directional_residuals["ZJ"],
            "ZJ_corner_numerator": corner_numerators["ZJ"],
            "ZJ_corner_denominator": corner_denominators["ZJ"],
            "critical_scale_directional_residual": directional_residuals[
                "critical_scale"
            ],
            "critical_scale_corner_numerator": corner_numerators[
                "critical_scale"
            ],
            "critical_scale_corner_denominator": corner_denominators[
                "critical_scale"
            ],
        },
        (parameter, syzygy_fraction, slope),
    )


@lru_cache(maxsize=1)
def ordered_syzygy_second_gap_static_obstruction() -> dict[str, sp.Expr]:
    """Exact energy-compatible syzygy state with adverse second acceleration.

    This is an ambient state, not a state asserted reachable from the Burrau
    brake.  It shows that tied masses, energy, zero momentum/angular momentum,
    the pre-syzygy pair-torque signs, and the first-crossing orientation do
    not force ``(r23-r31)'' > 0`` on the ordered-syzygy face.
    """
    parameter = sp.Rational(1, 3)
    syzygy_fraction = sp.Rational(1, 100)
    mass_1 = (1 - parameter**2) / (1 + parameter**2)
    mass_2 = 2 * parameter / (1 + parameter**2)
    side_31 = sp.factor(
        mass_2 * syzygy_fraction / (mass_1 + mass_2)
    )
    side_23 = 1 - side_31
    history_ratio = sp.factor(
        side_31
        * (mass_1 + side_23)
        / (side_23 * (mass_2 + side_31))
    )
    kinetic_coefficient = sp.factor(
        mass_2
        * (
            mass_1 * mass_2
            + mass_1 * side_31**2
            + mass_2 * side_23**2
        )
        / (
            mass_1
            * side_23**2
            * (mass_2 + side_31) ** 2
        )
    )
    potential = sp.factor(
        mass_1 * mass_2
        + mass_2 / side_23
        + mass_1 / side_31
    )
    initial_potential = sp.factor(
        mass_1 * mass_2 + 1 / (mass_1 * mass_2)
    )
    amplitude = sp.factor(
        2 * (potential - initial_potential) / kinetic_coefficient
    )
    centrifugal_coefficient = sp.factor(
        side_23**-3
        - mass_2**2
        * history_ratio**2
        / (mass_1**2 * side_31**3)
    )
    gravity_gap = sp.factor(
        mass_2
        - mass_1
        + (2 * mass_1 + 1) / side_31**2
        - (2 * mass_2 + 1) / side_23**2
    )
    second_acceleration = sp.factor(
        gravity_gap + amplitude * centrifugal_coefficient
    )
    crossing_coefficient = sp.factor(
        -(
            mass_1 * mass_2
            + mass_1 * side_31**2
            + mass_2 * side_23**2
        )
        / (mass_1 * side_23 * (mass_2 + side_31))
    )
    return {
        "u": parameter,
        "z": syzygy_fraction,
        "m1": mass_1,
        "m2": mass_2,
        "r23": side_23,
        "r31": side_31,
        "eta": history_ratio,
        "kinetic_coefficient": kinetic_coefficient,
        "potential": potential,
        "initial_potential": initial_potential,
        "amplitude": amplitude,
        "centrifugal_coefficient": centrifugal_coefficient,
        "gravity_gap": gravity_gap,
        "second_acceleration": second_acceleration,
        "crossing_coefficient": crossing_coefficient,
    }


@lru_cache(maxsize=1)
def second_gap_barrier_outward_contact_obstruction() -> dict[str, sp.Expr]:
    """Exact interior state where the critical second-gap barrier points out.

    The normalized state lies on ``Z=G/(-C2)`` and satisfies the tied energy,
    zero momentum/angular momentum, the pre-syzygy torque signs, and
    decreasing positive area.  Nevertheless ``d log(Z/Zstar)/ds > 0``.
    It is not asserted reachable from the Burrau brake.
    """
    parameter = sp.Rational(1, 3)
    side_23 = sp.Rational(499, 500)
    side_31 = sp.Rational(1, 20)
    history_ratio = sp.Rational(3, 20)
    mass_1 = (1 - parameter**2) / (1 + parameter**2)
    mass_2 = 2 * parameter / (1 + parameter**2)

    _, gravity_second, physical_variables = _radial_gravity_gaps()
    physical_23, physical_31, physical_12, physical_parameter = (
        physical_variables
    )
    gravity_shape = sp.factor(
        gravity_second.subs(
            {
                physical_23: side_23,
                physical_31: side_31,
                physical_12: 1,
                physical_parameter: parameter,
            }
        )
    )
    centrifugal_coefficient = sp.factor(
        side_23**-3
        - mass_2**2
        * history_ratio**2
        / (mass_1**2 * side_31**3)
    )
    amplitude = sp.factor(-gravity_shape / centrifugal_coefficient)
    angular_amplitude = sp.sqrt(amplitude)

    apex_x = (side_31**2 + 1 - side_23**2) / 2
    twice_area = sp.sqrt(side_31**2 - apex_x**2)
    ell_23 = angular_amplitude
    ell_31 = -(mass_2 / mass_1) * history_ratio * angular_amplitude
    ell_12 = -(1 - history_ratio) * angular_amplitude / mass_1
    scale_rate = sp.symbols("sigma", real=True)
    relative_12 = sp.Matrix([scale_rate, ell_12])
    velocity_3_y = (
        twice_area * scale_rate
        - (apex_x - 1) * ell_12
        - ell_23
        + ell_31
    )
    velocity_3_x = (apex_x * velocity_3_y - ell_31) / twice_area
    relative_13 = sp.Matrix([velocity_3_x, velocity_3_y])
    total_mass = mass_1 + mass_2 + 1
    velocity_1 = -(
        mass_2 * relative_12 + relative_13
    ) / total_mass
    velocity_2 = velocity_1 + relative_12
    velocity_3 = velocity_1 + relative_13
    kinetic = sp.factor(
        (
            mass_1 * velocity_1.dot(velocity_1)
            + mass_2 * velocity_2.dot(velocity_2)
            + velocity_3.dot(velocity_3)
        )
        / 2
    )
    minimizing_scale_rate = sp.factor(
        sp.solve(sp.diff(kinetic, scale_rate), scale_rate)[0]
    )
    kinetic_minimum = sp.factor(
        kinetic.subs(scale_rate, minimizing_scale_rate)
    )
    potential = sp.factor(
        mass_1 * mass_2 + mass_2 / side_23 + mass_1 / side_31
    )
    initial_potential = sp.factor(
        mass_1 * mass_2 + 1 / (mass_1 * mass_2)
    )
    physical_scale = sp.factor(
        (potential - kinetic_minimum) / initial_potential
    )

    shape_23_rate = sp.factor(
        (
            (apex_x - 1) * (velocity_3_x - scale_rate)
            + twice_area * (velocity_3_y - ell_12)
        )
        / side_23
        - side_23 * scale_rate
    )
    shape_31_rate = sp.factor(
        (apex_x * velocity_3_x + twice_area * velocity_3_y)
        / side_31
        - side_31 * scale_rate
    )
    current_ratio = sp.factor(
        (side_23**-3 - 1) / (side_31**-3 - 1)
    )
    initial_ratio = sp.factor(
        (mass_1**-3 - 1) / (mass_2**-3 - 1)
    )
    torque_rate = sp.factor(
        mass_1
        * twice_area
        * (side_31**-3 - 1)
        / angular_amplitude
    )
    history_rate = sp.factor(
        torque_rate * (current_ratio - history_ratio)
    )

    shape_23_symbol, shape_31_symbol, ratio_symbol = sp.symbols(
        "p q eta", positive=True
    )
    symbolic_gravity = gravity_second.subs(
        {
            physical_23: shape_23_symbol,
            physical_31: shape_31_symbol,
            physical_12: 1,
            physical_parameter: parameter,
        }
    )
    symbolic_coefficient = (
        shape_23_symbol**-3
        - mass_2**2
        * ratio_symbol**2
        / (mass_1**2 * shape_31_symbol**3)
    )
    evaluation = {
        shape_23_symbol: side_23,
        shape_31_symbol: side_31,
        ratio_symbol: history_ratio,
    }
    log_barrier_rate = sp.factor(
        2 * torque_rate
        - scale_rate
        + (
            sp.diff(symbolic_coefficient, shape_23_symbol)
            / symbolic_coefficient
            - sp.diff(symbolic_gravity, shape_23_symbol)
            / symbolic_gravity
        ).subs(evaluation)
        * shape_23_rate
        + (
            sp.diff(symbolic_coefficient, shape_31_symbol)
            / symbolic_coefficient
            - sp.diff(symbolic_gravity, shape_31_symbol)
            / symbolic_gravity
        ).subs(evaluation)
        * shape_31_rate
        + (
            sp.diff(symbolic_coefficient, ratio_symbol)
            / symbolic_coefficient
        ).subs(evaluation)
        * history_rate
    )
    log_barrier_rate = sp.radsimp(
        sp.factor(log_barrier_rate.subs(scale_rate, minimizing_scale_rate))
    )
    apex_x_rate = sp.factor(
        side_31 * shape_31_rate - side_23 * shape_23_rate
    )
    area_rate = sp.factor(
        (
            side_31 * shape_31_rate
            - apex_x * apex_x_rate
        )
        / twice_area
    ).subs(scale_rate, minimizing_scale_rate)

    return {
        "u": parameter,
        "m1": mass_1,
        "m2": mass_2,
        "r23_ratio": side_23,
        "r31_ratio": side_31,
        "eta": history_ratio,
        "pythagorean_defect": 1 - side_23**2 - side_31**2,
        "twice_area_ratio": twice_area,
        "gravity_gap": gravity_shape,
        "centrifugal_coefficient": centrifugal_coefficient,
        "amplitude": amplitude,
        "ell_12": ell_12,
        "ell_23": ell_23,
        "ell_31": ell_31,
        "kinetic": kinetic,
        "scale_rate": minimizing_scale_rate,
        "kinetic_minimum": kinetic_minimum,
        "potential": potential,
        "initial_potential": initial_potential,
        "physical_scale": physical_scale,
        "current_ratio": current_ratio,
        "initial_ratio": initial_ratio,
        "history_rate": history_rate,
        "shape_23_rate": shape_23_rate.subs(
            scale_rate, minimizing_scale_rate
        ),
        "shape_31_rate": shape_31_rate.subs(
            scale_rate, minimizing_scale_rate
        ),
        "area_rate": area_rate,
        "log_barrier_rate": log_barrier_rate,
    }


@lru_cache(maxsize=1)
def _generic_first_gap_energy_margin() -> tuple[
    sp.Expr, sp.Expr, tuple[sp.Symbol, ...]
]:
    """Generic unit-``r12`` signed-torque energy margin."""
    m, n, p, q, z = sp.symbols("m n p q z", positive=True)
    expressions = squared_distance_accelerations()
    m1, m2, m3 = sp.symbols("m1 m2 m3", positive=True)
    x, y, r12_squared = sp.symbols("x y z", positive=True)
    v23, v31, v12 = sp.symbols("v23sq v31sq v12sq", nonnegative=True)
    substitution = {
        m1: m,
        m2: n,
        m3: 1,
        x: p**2,
        y: q**2,
        r12_squared: 1,
        v23: 0,
        v31: 0,
        v12: 0,
    }
    gravity = (
        expressions["z_second"].subs(substitution) / 2
        - expressions["x_second"].subs(substitution) / (2 * p)
    )
    kinetic = _pair_torque_kinetic_coefficient(m, n, p, q, z)
    potential = m * n + n / p + m / q
    centrifugal = (1 / m - z / n) ** 2 - 1 / p**3
    margin = sp.cancel(gravity + 2 * potential * centrifugal / kinetic)
    return margin, kinetic, (m, n, p, q, z)


@lru_cache(maxsize=1)
def _generic_signed_torque_first_gap_margin() -> tuple[
    sp.Expr, tuple[sp.Symbol, ...]
]:
    """Generic energy margin with the full pre-syzygy torque sign cone."""
    margin, _, variables = _generic_first_gap_energy_margin()
    m, n, p, q, z = variables
    h = sp.symbols("h", nonnegative=True)
    signed_margin = sp.cancel(margin.subs(z, n * h / m))
    return signed_margin, (m, n, p, q, h)


@lru_cache(maxsize=1)
def first_gap_static_energy_obstruction() -> tuple[
    sp.Expr, tuple[sp.Rational, ...]
]:
    """Exact interior point where the optimal static energy bound is positive.

    This disproves the proposed implication from ordered right/obtuse shape,
    the pre-syzygy torque signs, zero angular momentum, and total energy alone
    to ``(r12-r23)''<0``. It does not describe a reachable Burrau state.
    """
    depth = sp.Rational(99, 100)
    order_split = sp.Rational(1, 10**6)
    parameter = sp.Rational(99, 100)
    torque_ratio = sp.Rational(1, 10**6)
    root_two_minus_one = sp.sqrt(2) - 1
    triangle_scale = (
        2
        - sp.sqrt(2)
        + root_two_minus_one * depth
    )
    side_23 = 1 - triangle_scale * order_split / 2
    side_31 = 1 - triangle_scale + triangle_scale * order_split / 2
    tied_parameter = root_two_minus_one * parameter
    mass_1 = (1 - tied_parameter**2) / (1 + tied_parameter**2)
    mass_2 = 2 * tied_parameter / (1 + tied_parameter**2)
    margin, variables = _generic_signed_torque_first_gap_margin()
    m, n, p, q, h = variables
    value = sp.cancel(
        margin.subs(
            {
                m: mass_1,
                n: mass_2,
                p: side_23,
                q: side_31,
                h: torque_ratio,
            }
        )
    )
    return value, (depth, order_split, parameter, torque_ratio)


@lru_cache(maxsize=1)
def torque_rate_first_return_static_obstruction() -> dict[str, sp.Expr]:
    """Exact ambient state defeating a static ``(log k)'=0`` barrier."""
    euclid_parameter = sp.Rational(2, 5)
    mass_1 = (1 - euclid_parameter**2) / (1 + euclid_parameter**2)
    mass_2 = 2 * euclid_parameter / (1 + euclid_parameter**2)
    side_23 = sp.Rational(39, 40)
    side_31 = sp.Rational(1, 30)
    alpha = mass_1 / (mass_1 + mass_2)
    beta = mass_2 / (mass_1 + mass_2)
    reduced_1 = mass_1 * mass_2 / (mass_1 + mass_2)
    reduced_2 = (mass_1 + mass_2) / (mass_1 + mass_2 + 1)
    apex_x = (side_31**2 + 1 - side_23**2) / 2
    apex_y = sp.sqrt(side_31**2 - apex_x**2)
    jacobi_x = apex_x - beta
    pair_23 = sp.Matrix([jacobi_x - alpha, apex_y])
    pair_31 = sp.Matrix([jacobi_x + beta, apex_y])
    velocity_x = sp.Integer(0)
    velocity_y = sp.Integer(-1)
    complement_x, complement_y = sp.symbols("Vx Vy", real=True)
    pair_23_velocity = sp.Matrix(
        [complement_x - alpha * velocity_x, complement_y - alpha * velocity_y]
    )
    pair_31_velocity = sp.Matrix(
        [complement_x + beta * velocity_x, complement_y + beta * velocity_y]
    )
    angular_momentum = (
        reduced_1 * velocity_y
        + reduced_2 * (jacobi_x * complement_y - apex_y * complement_x)
    )
    radial_23 = pair_23.dot(pair_23_velocity) / side_23
    radial_31 = pair_31.dot(pair_31_velocity) / side_31
    log_ratio_rate = 3 * (
        radial_31 / (side_31 * (1 - side_31**3))
        - radial_23 / (side_23 * (1 - side_23**3))
    )
    solution = sp.solve(
        [angular_momentum, log_ratio_rate],
        [complement_x, complement_y],
        dict=True,
    )[0]
    radial_23 = sp.factor(radial_23.subs(solution))
    radial_31 = sp.factor(radial_31.subs(solution))
    ell_12 = velocity_y
    ell_23 = sp.factor(
        (
            pair_23[0] * pair_23_velocity[1]
            - pair_23[1] * pair_23_velocity[0]
        ).subs(solution)
    )
    ell_31 = sp.factor(
        (
            pair_31[0] * pair_31_velocity[1]
            - pair_31[1] * pair_31_velocity[0]
        ).subs(solution)
    )

    def first_log_derivative(value: sp.Expr) -> sp.Expr:
        return 3 / (value * (1 - value**3))

    def second_log_derivative(value: sp.Expr) -> sp.Expr:
        return -3 * (1 - 4 * value**3) / (value - value**4) ** 2

    relative_rate_23 = radial_23 / side_23
    relative_rate_31 = radial_31 / side_31
    omega_12 = ell_12
    omega_23 = ell_23 / side_23**2
    omega_31 = ell_31 / side_31**2
    ratio_23_second = side_23 * (omega_23**2 - omega_12**2)
    ratio_31_second = side_31 * (omega_31**2 - omega_12**2)
    velocity_curvature = sp.factor(
        second_log_derivative(side_31)
        * (side_31 * relative_rate_31) ** 2
        + first_log_derivative(side_31) * ratio_31_second
        - second_log_derivative(side_23)
        * (side_23 * relative_rate_23) ** 2
        - first_log_derivative(side_23) * ratio_23_second
    )
    kinetic = sp.factor(
        (
            reduced_1 * (velocity_x**2 + velocity_y**2)
            + reduced_2
            * (
                solution[complement_x] ** 2
                + solution[complement_y] ** 2
            )
        )
        / 2
    )

    gravity, variables = _radial_gravity_terms()
    gravity_12, gravity_23, gravity_31 = gravity
    r23, r31, r12, u = variables
    substitution = {
        r23: side_23,
        r31: side_31,
        r12: 1,
        u: euclid_parameter,
    }
    radial_gravity_12 = gravity_12.subs(substitution)
    radial_gravity_23 = gravity_23.subs(substitution)
    radial_gravity_31 = gravity_31.subs(substitution)
    gravity_curvature = sp.factor(
        first_log_derivative(side_31)
        * (radial_gravity_31 - side_31 * radial_gravity_12)
        - first_log_derivative(side_23)
        * (radial_gravity_23 - side_23 * radial_gravity_12)
    )
    shape_potential = (
        mass_1 * mass_2 + mass_2 / side_23 + mass_1 / side_31
    )
    initial_potential = (
        mass_1 * mass_2 + 1 / (mass_1 * mass_2)
    )
    physical_scale = sp.Rational(1, 2)
    scaled_curvature_numerator = sp.factor(
        gravity_curvature
        + shape_potential * velocity_curvature / kinetic
        - physical_scale
        * initial_potential
        * velocity_curvature
        / kinetic
    )
    return {
        "angular_momentum": sp.factor(angular_momentum.subs(solution)),
        "log_ratio_rate": sp.factor(log_ratio_rate.subs(solution)),
        "ell_12": ell_12,
        "ell_23": ell_23,
        "ell_31": ell_31,
        "velocity_curvature": velocity_curvature,
        "kinetic": kinetic,
        "gravity_curvature": gravity_curvature,
        "scaled_curvature_numerator": scaled_curvature_numerator,
    }


def _pair_torque_kinetic_coefficient(
    mass_1: sp.Expr,
    mass_2: sp.Expr,
    side_23: sp.Expr,
    side_31: sp.Expr,
    torque_ratio: sp.Expr,
) -> sp.Expr:
    """Closed Gram-inverse coefficient for ``ell23=1, ell31=-ratio``.

    The third mass and ``r12`` are one. This expression is the exact result
    of minimizing twice the kinetic energy over translation-reduced
    velocities subject to total angular momentum zero and the two stated
    pair angular momenta.
    """
    m = mass_1
    n = mass_2
    p = side_23
    q = side_31
    z = torque_ratio
    numerator = (
        m**2 * n**2 * z
        - m**2 * n**2 * p**2 * z**2
        - m**2 * n**2 * p**2 * z
        - m**2 * n**2 * q**2 * z
        - m**2 * n**2 * q**2
        - m**2 * n * p**2 * z**2
        + m**2 * n * q**2 * z
        + m * n**2 * p**2 * z
        - m * n**2 * q**2
        + m**2 * n * p**4 * z**2
        - m**2 * n * p**2 * q**2 * z**2
        + m**2 * n * p**2 * q**2 * z
        - m**2 * n * q**4 * z
        - m**2 * p**2 * q**2 * z**2
        - m * n**2 * p**4 * z
        + m * n**2 * p**2 * q**2 * z
        - m * n**2 * p**2 * q**2
        + m * n**2 * q**4
        + 2 * m * n * p**2 * q**2 * z
        - n**2 * p**2 * q**2
    )
    heron_product = (
        (-1 + p - q) * (-1 + p + q) * (1 + p - q) * (1 + p + q)
    )
    denominator = m * n * heron_product * (m * n + m * q**2 + n * p**2)
    return 4 * numerator / denominator


def pair_torque_kinetic_coefficient() -> tuple[
    sp.Expr, tuple[sp.Symbol, ...]
]:
    """Return the generic optimal kinetic coefficient and its variables."""
    m, n, p, q, z = sp.symbols("m n p q z", positive=True)
    return _pair_torque_kinetic_coefficient(m, n, p, q, z), (m, n, p, q, z)
