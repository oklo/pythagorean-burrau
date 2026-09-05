# Pythagorean problem: source audit

Research and source inspection: 2026-09-05. These entries distinguish an
original text that was inspected from a bibliographic lead. Publication
years are used in the paper rather than dates when an old scan was uploaded.
The initial-condition restriction matters: “free-fall problem” in later
literature is often much broader than the exact tied integer right triangle.

## Meissel and Burrau

[Burrau's original article](https://adsabs.harvard.edu/pdf/1913AN....195..113B),
*Numerische Berechnung eines Spezialfalles des Dreikörperproblems*,
Astronomische Nachrichten **195** (1913), columns 113–118;
[DOI](https://doi.org/10.1002/asna.19131950602).
The ADS scan has three image pages, each containing two journal columns.

- Column 113 explicitly recalls an **1893 conversation with Meissel** and
  his expectation of periodic motion. The spelling is **Ernst Meissel**,
  not Meisel. Burrau is Carl Burrau.
- The same column gives the zero initial velocities, masses, and opposite
  distances, and describes the numerical-method motivation.
- Column 117 ends the numerical table at **t=3.35**.
- Column 118 credits **Sigurd Kristensen** and dates Burrau's account
  Copenhagen, **9 March 1913**.

Both first and last pages were visually inspected. The account is primary
first-person evidence for the conversation, recorded twenty years later;
it is not Meissel's own surviving statement. No separate publication of
that 1893 conjecture was located. Meissel's earlier work on zero-velocity
three-body series and later archival accounts were not used to move the
specific 3–4–5 proposal to an earlier date.

## Szebehely and the question of dormancy

[Szebehely's original PNAS paper](https://doi.org/10.1073/pnas.58.1.60),
*Burrau's Problem of Three Bodies*, **58** (1967), 60–65.
The full facsimile was recovered from
[the PostScript copy on Laughlin's course site](https://www.ucolick.org/~laugh/oxide/projects/szebehely2.ps).
That file has a cover plus six scanned article pages. Its ASCII85/CCITT
image streams were extracted and OCR'd locally; all six article pages
were read, with image inspection available for ambiguous OCR.

Pages 60 and 64, note 2, document Szebehely's initiation of the revival
and the 1966 Yale/NASA/ETH computations. Page 61 distinguishes older related
examples. **The paper does not identify how Szebehely first learned of
Burrau's problem.** Neither this account nor the complete-solution AJ
paper establishes a personal conduit. “Clemence communicated the paper”
is a publication submission credit, not evidence that he introduced the
problem to Szebehely. No such claim was inserted.

There is direct original evidence of awareness before the revival:

- [Strömgren 1919](https://articles.adsabs.harvard.edu/pdf/1919MNRAS..80...12S),
  *A New Class of Periodic Solutions in the General Problem of Three
  Bodies*, MNRAS **80**, 12–22. Full scan and extracted text inspected;
  the first scan page shares space with the preceding eclipse article.
  It develops related periodic solutions, not a continuation of the exact
  Pythagorean release.
- [Zumkley 1941](https://articles.adsabs.harvard.edu/pdf/1941AN....272...66Z),
  *Ein numerisch gerechneter Spezialfall des allgemeinen Dreikörperproblems
  in vereinfachter Behandlung*, AN **272**, 66–76. The first page was
  visually inspected: it explicitly cites Burrau 1913 among the known
  numerical studies and states that its own three masses are all one.
  It describes a slide-rule computation. This establishes continued
  awareness, while the unequal Pythagorean masses are absent.
- Garcia's **1966** extension of Zumkley's table is cited in Szebehely's
  PNAS reference 22. That report itself was **not obtained**; the paper
  attributes the information to Szebehely rather than pretending that
  Garcia's original report was inspected.

The inspected sources do not establish an intervening extension of the
**exact** 3–4–5 integration between 1913 and 1966. This is a bounded search
finding, not proof that no such work exists. A conclusive personal history
of Szebehely's rediscovery would require correspondence or another explicit
first-person source; no unsupported story is supplied.

## The 1967 resolution and nearby periodic orbits

[Szebehely and Peters, Complete Solution](https://articles.adsabs.harvard.edu/pdf/1967AJ.....72..876S),
AJ **72** (1967), 876–883. Full original article inspected through ADS;
its eight-page PostScript facsimile is also available as
[szebehely1.ps](https://www.ucolick.org/~laugh/oxide/projects/szebehely1.ps).
The paper was received 16 May 1967. Page 876 describes the preceding
research groups; page 878 explains where Burrau's calculation ended.
The escaper has mass **3**; the binary contains **4 and 5**. Follow this
original description when later retellings disagree. “Complete solution”
here is the authors' numerical/asymptotic conclusion, not a claim that
modern outward-rounded interval certificates existed in 1967.

[Szebehely and Peters, A New Periodic Solution](https://adsabs.harvard.edu/pdf/1967AJ.....72.1187S),
AJ **72** (1967), 1187–1190. The original abstract explicitly states a
binary collision and distances only approximately 3,4,5. Its periodicity
is therefore outside the classical collision-free exact-geometry problem.

[Standish 1970](https://link.springer.com/chapter/10.1007/978-94-010-3323-7_34),
*New Periodic Orbits in the General Problem of Three Bodies*, in
Giacaglia (ed.), *Periodic Orbits, Stability and Resonances*, pp. 375–381.
The publisher's original chapter metadata and abstract were inspected.
The full seven-page chapter is not claimed read. Li and Liao explicitly
identify their `F1(0.6,0.8,1)` with Standish's collisionless orbit.

## Tanikawa, Montgomery, and current work

| Primary source | What it supports; inspection scope |
|---|---|
| [Tanikawa, Umehara & Abe 1995](https://link.springer.com/article/10.1007/BF00692285) | Systematic numerical search for binary/triple collision orbits. Original publisher abstract and bibliography inspected; not full subscription text. |
| [Tanikawa 2000](https://link.springer.com/article/10.1023/A:1008313912013) | Continued search and structure of free-fall initial-value space. Original publisher abstract inspected. Correct spelling: **Kiyotaka Tanikawa**. |
| [Moeckel, Montgomery & Venturelli 2012](https://www-users.cse.umn.edu/~rmoeckel/research/BrakeSyzygy13.2.pdf) | Rigorous brake-to-syzygy framework and isosceles periodic collision construction. Author manuscript; DOI 10.1007/s00205-012-0502-y. |
| [Montgomery, Dropping Bodies](https://arxiv.org/abs/2207.02582) | Author's 2022 preprint, published 2023 in Mathematical Intelligencer, DOI 10.1007/s00283-022-10252-4. Brake-orbit reversal and modern motivation. This arXiv identifier belongs to **Montgomery**, not to Szebehely's 1967 article, despite a miscitation in the later bibliography. |
| [Li & Liao 2019, author-hosted published PDF](https://sjliao.sjtu.edu.cn/__local/B/0D/48/5F829F37A0DCC8FAD972B6E698C_A0F02F89_1137C5.pdf?e=.pdf) | Full paper inspected. **316 total, 313 new**, not 316 new. Numerical period/separation cutoffs and unequal-mass seeds; no assertion of exact Pythagorean periodicity. |
| [Hristov et al. 2024](https://arxiv.org/abs/2308.16159) | 2023 author preprint; journal publication CMDA 136, 7 (2024). 24,582 initial conditions, 12,409 distinct equal-mass solutions, at stated period cutoff. Those counts are not interchangeable. |
| [Rantala et al. 2020](https://academic.oup.com/mnras/article/492/3/4131/5706852) | Full original publisher text, especially §5.2: Pythagorean benchmark of the `mstar` regularized integrator. |
| [Chitan, Mylläri & Haque 2022](https://arxiv.org/abs/2011.03046) | Original author paper on relativistic Pythagorean triples; published MNRAS 509, 1919–1928. Its equations differ from the exact Newtonian conjecture. |
| [Chitan, Mylläri & Valtonen 2025](https://www.utupub.fi/server/api/core/bitstreams/b08c61c9-e39b-4853-ac69-80833a45be23/content) | Original published paper, *The influence of spin in black hole triplets*, Astronomy and Computing 51, 100933. This is the published successor to earlier spin preprints. |

The literature search did **not** establish that the all-integer tied-right
nonperiodicity conjecture was formulated by Tanikawa or Montgomery. The
introduction presents it as the specific conjecture investigated by this
project, distinguishing it from Meissel's original periodicity expectation.

Original source files used during review are kept temporarily outside the
repository; links and the `pythagorean-history-source-hashes.json` SHA-256 manifest provide provenance without adding
complete third-party papers to the project.
