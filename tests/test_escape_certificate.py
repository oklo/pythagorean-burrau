import numpy as np

from src.dynamics.escape_certificate import evaluate_escape_certificate


def test_strongly_outgoing_bound_binary_is_certified() -> None:
    certificate = evaluate_escape_certificate(
        1.0,
        1.0,
        0.1,
        inner_vector=np.array([0.1, 0.0]),
        inner_velocity=np.array([0.0, 0.0]),
        outer_vector=np.array([10.0, 0.0]),
        outer_velocity=np.array([1.0, 0.0]),
        eta=2.0,
    )
    assert certificate.certified
    assert certificate.speed_floor > 0
    assert certificate.inner_energy_margin > 0


def test_inward_outer_motion_is_not_certified() -> None:
    certificate = evaluate_escape_certificate(
        1.0,
        1.0,
        0.1,
        inner_vector=np.array([0.1, 0.0]),
        inner_velocity=np.array([0.0, 0.0]),
        outer_vector=np.array([10.0, 0.0]),
        outer_velocity=np.array([-1.0, 0.0]),
        eta=2.0,
    )
    assert not certificate.certified


def test_certificate_rejects_wrong_vector_shape() -> None:
    try:
        evaluate_escape_certificate(1, 1, 1, [1], [0, 0], [5, 0], [1, 0], 1)
    except ValueError as error:
        assert "shape (2,)" in str(error)
    else:
        raise AssertionError("wrong-dimensional input was accepted")
