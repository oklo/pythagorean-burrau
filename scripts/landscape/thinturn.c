/* Thin-limit outer-turn probe.  Integrates the tied family in pair-{1,3}
 * adapted Jacobi coordinates (no chart switching) and reports, at every local
 * maximum of rho=|Y| (an "outer turn", where the outer body is momentarily at
 * rest radially), the pair angular momentum l13 = X x Xdot, the outer
 * Wronskian Y x Ydot, the kinetic energy, and the separations.
 * A brake requires l13 = 0 exactly, so l13 bounded away from zero at every
 * turn excludes brakes there.  Ordinary double numerics.
 * Usage: thinturn u tmax [order]
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXN 44
static int N = 30;
static double TOL = 1e-19;
static double m[3], Mtot, TAU = 1.0;
/* fixed chart: pair (0,2) = bodies 1,3; complement 1 = body 2 */
static const int PI_ = 0, PJ_ = 2, PK_ = 1;
static double ca, cb, Mij;
static double X[MAXN + 2][2], Y[MAXN + 2][2], VX[MAXN + 2][2], VY[MAXN + 2][2];
static double D[MAXN + 2][3][2], W[MAXN + 2][3], S[MAXN + 2][3], P[MAXN + 2][3][2];

static void taylor(double x[2], double y[2], double vx[2], double vy[2]) {
    int n, k, p, c;
    for (c = 0; c < 2; c++) { X[0][c] = x[c]; Y[0][c] = y[c]; VX[0][c] = vx[c]; VY[0][c] = vy[c]; }
    for (n = 0; n <= N; n++) {
        if (n > 0) for (c = 0; c < 2; c++) { X[n][c] = TAU * VX[n - 1][c] / n; Y[n][c] = TAU * VY[n - 1][c] / n; }
        for (c = 0; c < 2; c++) { D[n][0][c] = X[n][c]; D[n][1][c] = Y[n][c] + cb * X[n][c]; D[n][2][c] = Y[n][c] - ca * X[n][c]; }
        for (p = 0; p < 3; p++) { double s = 0; for (k = 0; k <= n; k++) s += D[k][p][0] * D[n - k][p][0] + D[k][p][1] * D[n - k][p][1]; W[n][p] = s; }
        for (p = 0; p < 3; p++) {
            if (n == 0) S[0][p] = pow(W[0][p], -1.5);
            else { double s = 0; for (k = 1; k <= n; k++) s += (-1.5 * k - (n - k)) * W[k][p] * S[n - k][p]; S[n][p] = s / (n * W[0][p]); }
        }
        for (p = 0; p < 3; p++) for (c = 0; c < 2; c++) { double s = 0; for (k = 0; k <= n; k++) s += D[k][p][c] * S[n - k][p]; P[n][p][c] = s; }
        for (c = 0; c < 2; c++) {
            VX[n + 1][c] = TAU * (-Mij * P[n][0][c] + m[PK_] * (P[n][2][c] - P[n][1][c])) / (n + 1);
            VY[n + 1][c] = TAU * (-(Mtot / Mij) * (m[PI_] * P[n][1][c] + m[PJ_] * P[n][2][c])) / (n + 1);
        }
    }
}
static void evalpoly(double h, double x[2], double y[2], double vx[2], double vy[2]) {
    for (int c = 0; c < 2; c++) {
        double sx = X[N][c], sy = Y[N][c], svx = VX[N][c], svy = VY[N][c];
        for (int n = N - 1; n >= 0; n--) { sx = sx * h + X[n][c]; sy = sy * h + Y[n][c]; svx = svx * h + VX[n][c]; svy = svy * h + VY[n][c]; }
        x[c] = sx; y[c] = sy; vx[c] = svx; vy[c] = svy;
    }
}
static double stepsize(void) {
    double hmin = 1e300;
    double sx = sqrt(X[0][0] * X[0][0] + X[0][1] * X[0][1]), sy = sqrt(Y[0][0] * Y[0][0] + Y[0][1] * Y[0][1]);
    if (sx > 1) sx = 1; if (sy > 1) sy = 1; if (sx < 1e-13) sx = 1e-13; if (sy < 1e-13) sy = 1e-13;
    for (int c = 0; c < 2; c++) {
        double vals[4] = {fabs(X[N][c]) / sx, fabs(Y[N][c]) / sy, fabs(X[N - 1][c]) / sx, fabs(Y[N - 1][c]) / sy};
        int ords[4] = {N, N, N - 1, N - 1};
        for (int q = 0; q < 4; q++) if (vals[q] > 0) { double h = pow(TOL / vals[q], 1.0 / ords[q]); if (h < hmin) hmin = h; }
    }
    return 0.85 * hmin;
}
static double rhodot_of(double y[2], double vy[2]) { return (y[0] * vy[0] + y[1] * vy[1]) / sqrt(y[0] * y[0] + y[1] * y[1]); }

int main(int argc, char **argv) {
    double u = atof(argv[1]), tmax = atof(argv[2]);
    if (argc > 3) N = atoi(argv[3]);
    double den = 1 + u * u, A = (1 - u * u) / den, B = 2 * u / den;
    m[0] = A; m[1] = B; m[2] = 1.0; Mtot = A + B + 1;
    Mij = m[PI_] + m[PJ_]; ca = m[PI_] / Mij; cb = m[PJ_] / Mij;
    double q[3][2] = {{-0.5, 0}, {0.5, 0}, {(B * B - A * A) / 2, A * B}};
    double cx = 0, cy = 0; for (int i = 0; i < 3; i++) { cx += m[i] * q[i][0]; cy += m[i] * q[i][1]; }
    for (int i = 0; i < 3; i++) { q[i][0] -= cx / Mtot; q[i][1] -= cy / Mtot; }
    double x[2], y[2], vx[2] = {0, 0}, vy[2] = {0, 0};
    for (int c = 0; c < 2; c++) { x[c] = q[PJ_][c] - q[PI_][c]; y[c] = q[PK_][c] - (m[PI_] * q[PI_][c] + m[PJ_] * q[PJ_][c]) / Mij; }
    double mu1 = m[PI_] * m[PJ_] / Mij, mu2 = m[PK_] * Mij / Mtot;
    double ab = A * B, U0 = ab + 1 / ab;
    double t = 0, rd0 = rhodot_of(y, vy);
    double xn[2], yn[2], vxn[2], vyn[2], xa[2], ya[2], vxa[2], vya[2];
    double eps = B, e52 = pow(eps, 2.5), e32 = pow(eps, 1.5);
    double selmin = 1e300;
    printf("# u=%.10g  B=eps=%.8g  eps^{5/2}=%.4e  eps^{3/2}=%.4e\n", u, eps, e52, e32);
    printf("# turn   t        rho      l13         l13/eps^{5/2}  YxYdot/eps^{3/2}   K/U0        r13\n");
    int nturn = 0;
    while (t < tmax && nturn < 60) {
        double r13 = sqrt(x[0] * x[0] + x[1] * x[1]);
        if (r13 < selmin) selmin = r13;
        double tau = 0.5 * sqrt(r13 * r13 * r13 / Mtot); TAU = tau < 1 ? tau : 1.0;
        taylor(x, y, vx, vy);
        double h = stepsize() * TAU; if (h > 0.05) h = 0.05; if (t + h > tmax) h = tmax - t;
        evalpoly(h / TAU, xn, yn, vxn, vyn);
        double rd1 = rhodot_of(yn, vyn);
        if (t > 1e-6 && rd0 > 0 && rd1 < 0) {   /* local maximum of rho: outer turn */
            double a = 0, b = h;
            for (int it = 0; it < 80; it++) { double c = 0.5 * (a + b); evalpoly(c / TAU, xa, ya, vxa, vya); if (rhodot_of(ya, vya) < 0) b = c; else a = c; }
            evalpoly(0.5 * (a + b) / TAU, xa, ya, vxa, vya);
            double l13 = xa[0] * vxa[1] - xa[1] * vxa[0];
            double lY = ya[0] * vya[1] - ya[1] * vya[0];
            double K = 0.5 * (mu1 * (vxa[0] * vxa[0] + vxa[1] * vxa[1]) + mu2 * (vya[0] * vya[0] + vya[1] * vya[1]));
            double rho = sqrt(ya[0] * ya[0] + ya[1] * ya[1]);
            double rr13 = sqrt(xa[0] * xa[0] + xa[1] * xa[1]);
            printf("%6d %9.4f %9.4f %12.4e %13.5f %16.5f %12.4e %10.3e\n",
                   ++nturn, t + 0.5 * (a + b), rho, l13, l13 / e52, lY / e32, K / U0, rr13);
            fflush(stdout);
        }
        t += h; memcpy(x, xn, sizeof(x)); memcpy(y, yn, sizeof(y)); memcpy(vx, vxn, sizeof(vx)); memcpy(vy, vyn, sizeof(vy)); rd0 = rd1;
        if (sqrt(x[0] * x[0] + x[1] * x[1]) < 1e-13) { printf("# inner collision at t=%.6f\n", t); break; }
    }
    printf("# min r13 over run = %.6e  (predicted first-miss 0.1355*eps^11 = %.6e)\n", selmin, 0.1355 * pow(eps, 11));
    return 0;
}
