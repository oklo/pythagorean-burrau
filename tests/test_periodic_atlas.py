"""Physical consistency checks for the construction integrator."""

import numpy as np
import pytest
from scipy.integrate import solve_ivp

from src.dynamics.cartesian import center_initial_state, right_hand_side
from src.dynamics.periodic_atlas import (
    cartesian,
    change_chart,
    integrate_atlas,
    local_jacobian,
    shooting_atlas,
)
from src.dynamics.periodic_shooting import PAIRS, algebra, initial_state


@pytest.mark.parametrize("pair", list(PAIRS))
def test_short_physical_flow_matches_cartesian(pair):
    p = np.array([0.14, 0.48, 0.06, 0.6, 0.8])
    masses = np.r_[p[3:], 1.0]
    _, initial = center_initial_state(masses, np.array([[-0.5, 0], [0.5, 0], p[:2]]))
    direct = solve_ivp(
        right_hand_side, (0, p[2]), initial, args=(masses,), method="DOP853", rtol=3e-13, atol=3e-15
    )
    state, _, end_pair, _, _ = integrate_atlas(p, start_pair=pair)
    q, v = cartesian(state, masses, end_pair)
    np.testing.assert_allclose(np.r_[q.ravel(), v.ravel()], direct.y[:, -1], atol=3e-12, rtol=0)


@pytest.mark.parametrize("old,new", [(a, b) for a in PAIRS for b in PAIRS if a != b])
def test_chart_map_pushes_forward_physical_vector_field(old, new):
    p = np.array([0.14, 0.48, 0.1, 0.6, 0.8])
    state = initial_state(p, old)
    # Use a nonzero-velocity state on the exact LC constraint leaf.
    state[2:4] = [0.1, -0.13]
    i, j, _ = PAIRS[old]
    masses = np.r_[p[3:], 1.0]
    state[4] = (2 * (state[2:4] @ state[2:4]) - masses[i] - masses[j]) / (state[:2] @ state[:2])
    state[7:9] = [0.2, 0.07]
    inputs = np.r_[state, p[3:]]
    target = change_chart(inputs, old, new)
    jac = local_jacobian(lambda z: change_chart(z, old, new), inputs)
    f = np.asarray(algebra(old)[0](*inputs)).ravel()
    g = np.asarray(algebra(new)[0](*target, *p[3:])).ravel()
    ratio = (state[:2] @ state[:2]) / (target[:2] @ target[:2])
    np.testing.assert_allclose(jac[:, :10] @ f, ratio * g, rtol=3e-13, atol=3e-13)


def test_all_parameter_variations_before_encounter():
    p = np.array([0.14, 0.48, 0.06, 0.6, 0.8])
    _, jac, _ = shooting_atlas(p)
    for column in range(5):
        plus, minus = p.copy(), p.copy()
        plus[column] += 1e-6
        minus[column] -= 1e-6
        fp, _, _ = shooting_atlas(plus, variational=False)
        fm, _, _ = shooting_atlas(minus, variational=False)
        np.testing.assert_allclose(jac[:, column], (fp - fm) / 2e-6, atol=2e-9, rtol=2e-8)


def test_switching_variations_agree_across_initial_charts():
    p = np.array(
        [
            0.26771975983456,
            0.426628756230577,
            1.41333000451887,
            0.485763528493199,
            0.878297059817055,
        ]
    )
    f, j, a = shooting_atlas(p, start_pair="23")
    g, k, b = shooting_atlas(p, start_pair="13")
    assert a["switches"] and b["switches"]

    # Different LC lift signs are permissible; compare physical endpoint derivatives.
    def physical_endpoint(atlas, jac_unused, start):
        state, tangent, pair, _, _ = integrate_atlas(p, start_pair=start)

        def velocity(values):
            return cartesian(values[:10], np.r_[values[10:], 1.0], pair)[1].ravel()

        local = local_jacobian(velocity, np.r_[state, p[3:]])
        result = local[:, :10] @ tangent
        result[:, 3:] += local[:, 10:]
        return result

    np.testing.assert_allclose(
        physical_endpoint(a, j, "23"), physical_endpoint(b, k, "13"), atol=3e-8, rtol=3e-9
    )
    assert max(abs(f)) < 1e-5 and max(abs(g)) < 1e-5


def test_no_spurious_jacobian_without_variations():
    _, jac, _ = shooting_atlas([0.14, 0.48, 0.06, 0.6, 0.8], variational=False)
    assert jac is None
