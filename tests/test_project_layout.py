import hashlib
from pathlib import Path

import pytest

from scripts.audit_project_layout import (
    AuditError,
    assert_unchanged,
    audit,
    audit_links,
    audit_paper,
)


def test_current_project_is_self_contained_and_preserved() -> None:
    result = audit(Path(__file__).resolve().parents[1])
    assert result["paper_sources"] >= 9
    assert result["paper_figures"] >= 3
    assert result["legacy_records"] == 52  # 51 originals plus the deduplicated image
    assert result["branch_snapshot_files"] > 0


def test_hash_audit_rejects_modified_source(tmp_path: Path) -> None:
    source = tmp_path / "source.txt"
    source.write_text("original")
    expected = hashlib.sha256(source.read_bytes()).hexdigest()
    assert_unchanged(source, expected)
    source.write_text("changed")
    with pytest.raises(AuditError, match="hash mismatch"):
        assert_unchanged(source, expected)


def test_link_audit_rejects_missing_local_target(tmp_path: Path) -> None:
    guide = tmp_path / "README.md"
    guide.write_text("[external](https://example.com)\n[missing](no-such-file.md)")
    with pytest.raises(AuditError, match="Broken local link"):
        audit_links(guide, tmp_path)


def test_link_audit_rejects_sibling_dependency(tmp_path: Path) -> None:
    guide = tmp_path / "README.md"
    guide.write_text("[old project](../legacy)")
    with pytest.raises(AuditError, match="leaves repository"):
        audit_links(guide, tmp_path)


def test_paper_audit_follows_inputs_and_rejects_missing_figure(tmp_path: Path) -> None:
    main = tmp_path / "main.tex"
    main.write_text(r"\input{section}")
    (tmp_path / "section.tex").write_text(r"\includegraphics[width=1cm]{figure.pdf}")
    with pytest.raises(AuditError, match="Missing paper graphic"):
        audit_paper(main, tmp_path)
    (tmp_path / "figure.pdf").write_bytes(b"test placeholder")
    assert audit_paper(main, tmp_path) == (2, 1)


def test_paper_audit_rejects_sibling_input(tmp_path: Path) -> None:
    main = tmp_path / "main.tex"
    main.write_text(r"\input{../old-paper}")
    with pytest.raises(AuditError, match="leaves repository"):
        audit_paper(main, tmp_path)
