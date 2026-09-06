# Oklo manuscript publication — September 6, 2026

The final “is here” link in [Add Astra](https://oklo.org/2026/09/05/add-astra/)
serves the stable URL:

https://oklo.org/wp-content/uploads/2026/09/pythagorean-burrau-interim-report.pdf

On September 6, the old 22-page draft was replaced by the reviewed 31-page
*The Pythagorean Three-Body Conjecture*, including the latest epigraph alignment,
“A simple plan” heading, rationality discussion, and F30 trajectory figure.
The post text and link URL were unchanged.

## Exact artifacts

| Artifact | Location | SHA-256 |
| --- | --- | --- |
| Current published PDF | `paper/main.pdf` | `d2b50b0152d37ee0f65c3aebb39dbd771d19439187783ad5cd9e9062868c9f79` |
| Previous public PDF | `paper/archive/oklo-interim-report-2026-09-05.pdf` | `b8feddc674e74708875de595c531783ec65dd20a7d5a22c04f005de584c56444` |

The current file is 2,081,206 bytes, 31 pages, dated September 6. The prior
file is 1,379,471 bytes, 22 pages, dated September 5. A fresh HTTPS download
after deployment returned HTTP 200 and matched both the staged PDF and the
research manuscript. The prior download's hash matched the server file before
replacement. No new build was performed during the final preservation step.

## Local mirror and procedure

The site workspace is `/Users/greglaughlin/Projects/oklo-org`; its `HANDOFF.md`
documents access and deployment. It has no configured GitHub remote. Its
publication artifacts are in `artifacts/blog/add-astra/`, and the upload mirror
is `wp-content/uploads/2026/09/pythagorean-burrau-interim-report.pdf`.
This record and the old PDF are also in the private research repository for
GitHub preservation. Unrelated dirty site files were not staged or deployed.

For a future explicitly requested publication update:

1. Inspect the actual post link and back up its current PDF.
2. Build and inspect the new manuscript locally; stage that PDF in the Oklo
   upload mirror. Do not deploy unrelated theme or database changes.
3. From the Oklo workspace, dry-run and then execute the single-file upload:

```sh
rsync -av --dry-run --itemize-changes -e 'ssh -o BatchMode=yes -o ConnectTimeout=15' wp-content/uploads/2026/09/pythagorean-burrau-interim-report.pdf oklo:public_html/wp-content/uploads/2026/09/pythagorean-burrau-interim-report.pdf
rsync -av --itemize-changes -e 'ssh -o BatchMode=yes -o ConnectTimeout=15' wp-content/uploads/2026/09/pythagorean-burrau-interim-report.pdf oklo:public_html/wp-content/uploads/2026/09/pythagorean-burrau-interim-report.pdf
```

4. Download through the public URL and compare SHA-256 with the staged PDF;
   confirm page count and the unchanged post link. A successful rsync alone
   is not public-download verification.

The default sandbox connection was reset; approved network escalation allowed
SSH/rsync. No password or private key contents were read or copied. Rollback,
if requested, consists of redeploying the explicitly named previous PDF to the
same destination. Do not perform a site-wide sync or reset.
