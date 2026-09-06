.DEFAULT_GOAL := help
PYTHON ?= .venv/bin/python
TECTONIC ?= tectonic
TECTONIC_CACHE_DIR ?= /private/tmp/burrau-tectonic
export TECTONIC_CACHE_DIR

.PHONY: help check test audit paper paper-check figures

help:
	@echo 'make check        Full Python tests and stored-evidence/layout audits'
	@echo 'make test         Python regression suite (not full CAPD replays)'
	@echo 'make audit        Layout, preservation hashes, and 100 stored middle tiles'
	@echo 'make paper        Rebuild paper/main.pdf; does not deploy it'
	@echo 'make paper-check  Build in a temporary directory; preserve reviewed PDF'
	@echo 'make figures      Regenerate formula/atlas vector figures (requires uv)'
	@echo 'Environment: uv sync --all-groups; Tectonic is a separate prerequisite'

check: test audit

test:
	$(PYTHON) -m pytest -q

audit:
	$(PYTHON) scripts/audit_project_layout.py
	$(PYTHON) scripts/audit_fable_middle_campaign.py

paper:
	$(TECTONIC) --keep-logs paper/main.tex

paper-check:
	$(PYTHON) scripts/check_paper_build.py --tectonic '$(TECTONIC)'

figures:
	uv run --no-project --with numpy --with matplotlib python paper/make_figures.py
