from __future__ import annotations

import pytest

from scripts.run_affine_middle_campaign import make_tile


def test_exact_shared_endpoint_tiles():
    first = make_tile(1, 290_000, 1_000_000)
    second = make_tile(2, 290_000, 1_000_000)
    assert first.left == "290001/1000000"
    assert first.right == "290002/1000000"
    assert first.right == second.left
    assert first.filename == "affine_tile_001_290001_290002.log"


@pytest.mark.parametrize("index", [-1, -100])
def test_negative_tile_index_is_rejected(index: int):
    with pytest.raises(ValueError, match="nonnegative"):
        make_tile(index, 290_000, 1_000_000)


def test_nonpositive_denominator_is_rejected():
    with pytest.raises(ValueError, match="positive"):
        make_tile(0, 290_000, 0)
