# Handoff: one project, one question

Continue with Greg Laughlin in `/Users/greglaughlin/Projects/pythagorean-burrau`,
branch `master`, private remote `https://github.com/oklo/pythagorean-burrau.git`.
The sole research objective is to prove the Pythagorean nonperiodicity
conjecture or establish an exact counterexample. Inspect Git status first;
do not overwrite unrelated work or start a long campaign from an old queue.

## Read first

1. [Current status](STATUS.md) and [research plan](RESEARCH_PLAN.md).
2. [Working paper guide](../paper/README.md), `paper/main.tex`, and relevant
   section inputs. The reviewed `paper/main.pdf` is the primary interim product.
3. [Proof obligations](PROOF_OBLIGATIONS.md), [ledger](PROOF_LEDGER.md), and
   [failed routes](FAILED_ROUTES.md).
4. [Persistent memory](PERSISTENT_RESEARCH_MEMORY.md) for editorial preferences;
   [project review](PROJECT_REVIEW_2026-09-06.md) for consolidation and audit limits.

## Do not lose these distinctions

- **2026-09-07 additions.** (i) No second brake at or before the first
  syzygy is now a theorem for every real `u` and all masses (time reversal
  plus Montgomery's syzygy theorem); later brakes are stutters at the
  `z`-extremum of their arc and fixed points of `R∘P` on the syzygy section
  (`SYZYGY_REVERSAL_STRUCTURE.md`, `paper/sections/reversal.tex`).
  (ii) A global double-precision landscape scan and a mass–side periodic
  atlas (`scripts/landscape/`, `data/mass_side_periodic_atlas.json`)
  are ORDINARY NUMERICAL EVIDENCE; the smallest right-angle defect found is
  `−3.3e-6`, nonzero. (iii) The prompt-ejection window `[0.3916, 0.4094]`
  has a validated tile certificate (`src/fable/verification/iso_window_lc_capd.cpp`,
  `scripts/run_iso_window_campaign.py`, `docs/ISO_WINDOW_INTERVAL.md`);
  the campaign completed 2026-09-07: 25,900 gap-free PASS tiles, audited and
  cross-replayed, so the window theorem is PROVED BY COMPUTER-ASSISTED
  ARGUMENT (records in `data/fable/iso_window/`). Point certificates for
  (7,24,25), (9,40,41), (36,77,85) are in `data/fable/point_certs/`
  (`SMALL_TRIPLE_CERTIFICATES.md`); multiprecision runs for u=1/6, 3/13, 1/3
  were in progress at handoff and count only if their logs end in PASS. The reviewed PDF sent to Richard Montgomery is archived
  as `paper/archive/main-2026-09-06-sent-to-montgomery.pdf`.

- Both integer and stronger real conjectures remain open. No exact tied-right
  periodic candidate is known. F30 has a nonzero right-angle defect.
- The accepted all-time middle interval is `[0.29,0.2900000101]`.
  `[0.29,0.29002]` is first-maximum only. The wider affine all-time candidate
  `[0.29,0.290002]` still needs its inclusion-algebra audit.
- Near-isosceles exclusion has an existential cutoff; thin-family density
  is measured by `n`, not all primitive triples. First-turn exclusion does
  not control all later returns; real collision parameters are not known rational.
- The forced-lag sufficient lemma needs a terminal weighted bound. Its old
  unweighted version is disproved. Closing a first-arc lemma would still
  leave an all-time gap. Read [the correction](FORCED_LAG_ENDPOINT_CORRECTION.md).
- A recovered `PASS_BURRAU_LC` log is not a newly accepted 3–4–5 theorem.
  Follow [the audit/replay gate](FABLE_BURRAU_THEOREM.md); the historical
  source lacks the main verifier's explicit damped-write duration gate.

## Layout and preservation

The sibling `burrau` directory is now `archive/legacy-burrau`. Two old Fable
worktrees have been removed; their complete histories are on GitHub as
`archive/fable-global-2026-09-06` and `archive/fable-middle-2026-09-06`.
Selected recovered records are under `archive/branch-snapshots`. Old campaign
handoffs, run reports, and replaced guides live under `archive/history`.
They are provenance, not active instructions or current theorem statements.
Do not recreate sibling agent-specific roots. See [the archive index](../archive/README.md).

## Paper and verification

The paper is *The Pythagorean Three-Body Conjecture*, 31 pages in the reviewed
September 6 build. Its principal companion material is already integrated.
Keep the technical substance and genuine lay-accessible opening; preserve
the approved title, abstract opening, epigraph layout, figures, and the
explicitly subjective 10% counterexample-existence assessment. Detailed
preferences are in persistent memory. The earlier 30-page ceiling was relaxed.

Run `make check` after meaningful changes. `make paper` rebuilds the working
PDF; `make paper-check` tests the build in a temporary directory without
changing the reviewed PDF. These checks do not replay all CAPD certificates.
No script automatically publishes to Oklo. The stable public PDF and its
backup are documented in [the publication record](OKLO_PUBLICATION_2026-09-06.md).
The unrelated dirty `oklo-org` checkout is outside this research cleanup.

Choose the next bounded task from the current research plan or Greg's newest
request. End it with an evidence-labelled result, the precise remaining gap,
and synchronized paper/ledger updates if any claim genuinely changes.
