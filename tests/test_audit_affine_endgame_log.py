from __future__ import annotations

from pathlib import Path

import pytest

from scripts.audit_affine_endgame_log import CAPD_COMMIT, EXPECTED_LEGS, audit_log

ROOT = Path(__file__).resolve().parents[1]


def _complete_synthetic_log() -> str:
    rows = [
        "ENDGAME_PARAMS precision_bits=160 tolerance=1e-24 order=32 "
        "sync_exchange=0 sync_preswitch=0 structured_form_b=0 "
        "sync_pair23=0 structured_section=0 graph_pair23_sync=1 "
        "graph_tangent_split=0 graph_c2=1 graph_pg2=1 "
        "graph_affine_remainder=1 graph_exchange_sandwich=0 "
        "graph_fixed_energy_h=0 graph_exchange_sync=0 "
        "graph_exchange_energy_project=0 "
        "graph_exchange_invariant_project=0 "
        "graph_exchange_velocity_project=0 "
        "driver=middle_escape_endgame_capd/v26-affine-remainder-test"
    ]
    rows.extend(
        f"ENDGAME_LEG {label} hull=1e-3 parameter_spread=9e-4 "
        f"quadratic_spread=1e-5 defect=1e-6 generators={index}"
        for index, label in enumerate(EXPECTED_LEGS, start=1)
    )
    rows.extend(
        [
            "ENDGAME_MAXIMUM max1 UoverU0=[1,1.1]",
            "ENDGAME_MAXIMUM max2 UoverU0=[1,1.1]",
            "ENDGAME_MAXIMUM max3 UoverU0=[1,1.1]",
            "TERMINAL inf_d=1",
            "TERMINAL inf_rhodot=2",
            "TERMINAL inf_Erho=0.1",
            "TERMINAL sup_h=-9 sup_Delta=1 inf_margin=4",
            "PASS_MIDDLE_ESCAPE_ENDGAME u=[29/100,2900001/10000000] "
            "t_terminal=77/20 eta=4 method=CAPD-6.1.0-MPFR "
            f"capd_commit={CAPD_COMMIT}",
        ]
    )
    return "\n".join(rows)


def test_complete_certificate_is_accepted():
    result = audit_log(_complete_synthetic_log(), "29/100", "2900001/10000000")
    assert result["legs"] == len(EXPECTED_LEGS)
    assert result["terminal_margin"] == 4


def test_wrong_exact_right_endpoint_is_rejected():
    with pytest.raises(ValueError, match="wrong exact rational endpoints"):
        audit_log(_complete_synthetic_log(), "29/100", "2900002/10000000")


def test_wrong_precision_is_rejected():
    bad_log = _complete_synthetic_log().replace("precision_bits=160", "precision_bits=80")
    with pytest.raises(ValueError, match="precision_bits=160"):
        audit_log(bad_log, "29/100", "2900001/10000000")


def test_committed_affine_summary_is_not_mistaken_for_a_full_log():
    summary = (ROOT / "data/middle_affine_pg2_width_1e12_summary.log").read_text()
    with pytest.raises(ValueError, match="ENDGAME_PARAMS"):
        audit_log(summary, "29/100", "290000000001/1000000000000")


def test_failure_marker_is_fail_closed():
    with pytest.raises(ValueError, match="failure marker"):
        audit_log("FAIL_MIDDLE_ESCAPE_ENDGAME", "29/100", "1/3")
