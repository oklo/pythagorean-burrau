from pathlib import Path

from scripts.audit_fable_middle_campaign import audit_archive, audit_summary


def test_summary_and_archived_campaign_records_match_exactly() -> None:
    root = Path(__file__).resolve().parents[1]
    summary = audit_summary(root / "data/fable/middle_escape_endgame_campaign_1e8.log")
    archive = audit_archive(root / "data/fable/middle_escape_endgame_campaign_1e8_logs.tar.gz")
    assert sorted(summary) == sorted(archive)
