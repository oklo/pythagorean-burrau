/* Mass-side family integrator: masses (m1,m2,1), initial positions
 * q1=(-1/2,0), q2=(1/2,0), q3=(x,y) with x=(m2^2-m1^2)/2, y=sqrt(m2^2-(x+1/2)^2),
 * all at rest.  Taylor integrator in pair-adapted Jacobi coordinates with chart
 * switching (same scheme as tied3j.c).  Prints the labelled CM-frame state at
 * time t, the complete Hopf brake residual, kinetic energy, and the nearest
 * K-minimum event.  Ordinary double numerics.
 * Usage: ms3 m1 m2 t [order]
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXN 44
static int N = 26;
static double TOL = 1e-18;
static double m[3], Mtot;
static int pi_, pj_, pk_;
static double ca, cb, Mij, TAU = 1.0;
static double X[MAXN + 2][2], Y[MAXN + 2][2], VX[MAXN + 2][2], VY[MAXN + 2][2];
static double D[MAXN + 2][3][2], W[MAXN + 2][3], S[MAXN + 2][3], P[MAXN + 2][3][2];

static void setpair(int p) {
    static const int I[3] = {0, 1, 2}, J[3] = {1, 2, 0};
    pi_ = I[p]; pj_ = J[p]; pk_ = 3 - pi_ - pj_;
    Mij = m[pi_] + m[pj_]; ca = m[pi_] / Mij; cb = m[pj_] / Mij;
}
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
            VX[n + 1][c] = TAU * (-Mij * P[n][0][c] + m[pk_] * (P[n][2][c] - P[n][1][c])) / (n + 1);
            VY[n + 1][c] = TAU * (-(Mtot / Mij) * (m[pi_] * P[n][1][c] + m[pj_] * P[n][2][c])) / (n + 1);
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
    if (sx > 1) sx = 1; if (sy > 1) sy = 1; if (sx < 1e-12) sx = 1e-12; if (sy < 1e-12) sy = 1e-12;
    for (int c = 0; c < 2; c++) {
        double vals[4] = {fabs(X[N][c]) / sx, fabs(Y[N][c]) / sy, fabs(X[N - 1][c]) / sx, fabs(Y[N - 1][c]) / sy};
        int ords[4] = {N, N, N - 1, N - 1};
        for (int q = 0; q < 4; q++) if (vals[q] > 0) { double h = pow(TOL / vals[q], 1.0 / ords[q]); if (h < hmin) hmin = h; }
    }
    return 0.85 * hmin;
}
static void to_cartesian(double x[2], double y[2], double vx[2], double vy[2], double q[3][2], double v[3][2]) {
    for (int c = 0; c < 2; c++) {
        double cm = -(m[pk_] / Mtot) * y[c], cmv = -(m[pk_] / Mtot) * vy[c];
        q[pk_][c] = (Mij / Mtot) * y[c]; v[pk_][c] = (Mij / Mtot) * vy[c];
        q[pi_][c] = cm - cb * x[c]; v[pi_][c] = cmv - cb * vx[c];
        q[pj_][c] = cm + ca * x[c]; v[pj_][c] = cmv + ca * vx[c];
    }
}
static void from_cartesian(double q[3][2], double v[3][2], double x[2], double y[2], double vx[2], double vy[2]) {
    for (int c = 0; c < 2; c++) {
        x[c] = q[pj_][c] - q[pi_][c]; vx[c] = v[pj_][c] - v[pi_][c];
        y[c] = q[pk_][c] - (m[pi_] * q[pi_][c] + m[pj_] * q[pj_][c]) / Mij;
        vy[c] = v[pk_][c] - (m[pi_] * v[pi_][c] + m[pj_] * v[pj_][c]) / Mij;
    }
}
static double rmin_of(double x[2], double y[2], int *pmin) {
    double dd[3][2] = {{x[0], x[1]}, {y[0] + cb * x[0], y[1] + cb * x[1]}, {y[0] - ca * x[0], y[1] - ca * x[1]}};
    double best = 1e300; *pmin = 0;
    for (int p = 0; p < 3; p++) { double r = sqrt(dd[p][0] * dd[p][0] + dd[p][1] * dd[p][1]); if (r < best) { best = r; *pmin = p; } }
    return best;
}
static double kinetic(double vx[2], double vy[2]) {
    double mu1 = m[pi_] * m[pj_] / Mij, mu2 = m[pk_] * Mij / Mtot;
    return 0.5 * (mu1 * (vx[0] * vx[0] + vx[1] * vx[1]) + mu2 * (vy[0] * vy[0] + vy[1] * vy[1]));
}
static double udot(double x[2], double y[2], double vx[2], double vy[2]) {
    double dd[3][2] = {{x[0], x[1]}, {y[0] + cb * x[0], y[1] + cb * x[1]}, {y[0] - ca * x[0], y[1] - ca * x[1]}};
    double vv[3][2] = {{vx[0], vx[1]}, {vy[0] + cb * vx[0], vy[1] + cb * vx[1]}, {vy[0] - ca * vx[0], vy[1] - ca * vx[1]}};
    double pm[3] = {m[pi_] * m[pj_], m[pi_] * m[pk_], m[pj_] * m[pk_]}, Ud = 0;
    for (int p = 0; p < 3; p++) { double r2 = dd[p][0] * dd[p][0] + dd[p][1] * dd[p][1], rd = dd[p][0] * vv[p][0] + dd[p][1] * vv[p][1]; Ud -= pm[p] * rd / (r2 * sqrt(r2)); }
    return Ud;
}

int main(int argc, char **argv) {
    double m1 = atof(argv[1]), m2 = atof(argv[2]), tfin = atof(argv[3]);
    if (argc > 4) N = atoi(argv[4]);
    m[0] = m1; m[1] = m2; m[2] = 1.0; Mtot = m1 + m2 + 1;
    double xx = (m2 * m2 - m1 * m1) / 2, yy2 = m2 * m2 - (xx + 0.5) * (xx + 0.5);
    if (yy2 <= 0) { printf("{\"error\":\"degenerate triangle\"}\n"); return 1; }
    double q[3][2] = {{-0.5, 0}, {0.5, 0}, {xx, sqrt(yy2)}}, v[3][2] = {{0, 0}, {0, 0}, {0, 0}};
    double cx = 0, cy = 0; for (int i = 0; i < 3; i++) { cx += m[i] * q[i][0]; cy += m[i] * q[i][1]; }
    for (int i = 0; i < 3; i++) { q[i][0] -= cx / Mtot; q[i][1] -= cy / Mtot; }
    double r01 = 1, r12 = m1, r20 = m2; int p0 = 0; if (r12 < r01 && r12 <= r20) p0 = 1; if (r20 < r01 && r20 < r12) p0 = 2;
    setpair(p0);
    double x[2], y[2], vx[2], vy[2]; from_cartesian(q, v, x, y, vx, vy);
    double t = 0; int pm; double rmin_g = rmin_of(x, y, &pm);
    double xn[2], yn[2], vxn[2], vyn[2];
    /* nearest K-min tracking */
    double Ud0 = udot(x, y, vx, vy);
    double kmin_t = -1, kmin_K = 1e300;
    while (t < tfin) {
        double rr = rmin_of(x, y, &pm); double tau = 0.5 * sqrt(rr * rr * rr / Mtot); TAU = tau < 1 ? tau : 1.0;
        taylor(x, y, vx, vy);
        double h = stepsize() * TAU; if (h > 0.05) h = 0.05; if (t + h > tfin) h = tfin - t;
        evalpoly(h / TAU, xn, yn, vxn, vyn);
        double Ud1 = udot(xn, yn, vxn, vyn);
        if (t + h > 0.2 && Ud0 < 0 && Ud1 > 0) {
            double a = 0, b = h, xa[2], ya[2], vxa[2], vya[2];
            for (int it = 0; it < 60; it++) { double c = 0.5 * (a + b); evalpoly(c / TAU, xa, ya, vxa, vya); if (udot(xa, ya, vxa, vya) > 0) b = c; else a = c; }
            evalpoly(0.5 * (a + b) / TAU, xa, ya, vxa, vya);
            double K = kinetic(vxa, vya);
            if (K < kmin_K) { kmin_K = K; kmin_t = t + 0.5 * (a + b); }
        }
        t += h; memcpy(x, xn, sizeof(x)); memcpy(y, yn, sizeof(y)); memcpy(vx, vxn, sizeof(vx)); memcpy(vy, vyn, sizeof(vy)); Ud0 = Ud1;
        rr = rmin_of(x, y, &pm); if (rr < rmin_g) rmin_g = rr;
        if (rr < 1e-10) { printf("{\"error\":\"collision\",\"t\":%.6f}\n", t); return 1; }
        /* chart switch */
        { double dd[3][2] = {{x[0], x[1]}, {y[0] + cb * x[0], y[1] + cb * x[1]}, {y[0] - ca * x[0], y[1] - ca * x[1]}};
          double r0 = sqrt(dd[0][0] * dd[0][0] + dd[0][1] * dd[0][1]);
          if (pm != 0 && rr < 0.8 * r0) {
              double qq[3][2], vv[3][2]; to_cartesian(x, y, vx, vy, qq, vv);
              int gi = (pm == 1) ? pi_ : pj_, gk = pk_;
              int gp = (gi == 0 && gk == 1) || (gi == 1 && gk == 0) ? 0 : ((gi == 1 && gk == 2) || (gi == 2 && gk == 1) ? 1 : 2);
              setpair(gp); from_cartesian(qq, vv, x, y, vx, vy);
          } }
    }
    double qq[3][2], vv[3][2]; to_cartesian(x, y, vx, vy, qq, vv);
    /* Hopf residual with Jacobi vectors X=q2-q1, Y=q3-(m1 q1+m2 q2)/(m1+m2) */
    double Xh[2], Yh[2], VXh[2], VYh[2], M12 = m[0] + m[1];
    for (int c = 0; c < 2; c++) { Xh[c] = qq[1][c] - qq[0][c]; VXh[c] = vv[1][c] - vv[0][c]; Yh[c] = qq[2][c] - (m[0] * qq[0][c] + m[1] * qq[1][c]) / M12; VYh[c] = vv[2][c] - (m[0] * vv[0][c] + m[1] * vv[1][c]) / M12; }
    double B1 = Xh[0] * VXh[0] + Xh[1] * VXh[1] - Yh[0] * VYh[0] - Yh[1] * VYh[1];
    double B2 = VXh[0] * Yh[0] + VXh[1] * Yh[1] + Xh[0] * VYh[0] + Xh[1] * VYh[1];
    double B3 = VXh[0] * Yh[1] - VXh[1] * Yh[0] + Xh[0] * VYh[1] - Xh[1] * VYh[0];
    double K = kinetic(vx, vy);
    printf("{\"m1\":%.17g,\"m2\":%.17g,\"t\":%.17g,\"B\":[%.17g,%.17g,%.17g],\"K\":%.17g,\"rmin\":%.4g,\"kmin_t\":%.9f,\"kmin_K\":%.6g,\"q\":[[%.17g,%.17g],[%.17g,%.17g],[%.17g,%.17g]],\"v\":[[%.17g,%.17g],[%.17g,%.17g],[%.17g,%.17g]]}\n",
           m1, m2, tfin, B1, B2, B3, K, rmin_g, kmin_t, kmin_K, qq[0][0], qq[0][1], qq[1][0], qq[1][1], qq[2][0], qq[2][1], vv[0][0], vv[0][1], vv[1][0], vv[1][1], vv[2][0], vv[2][1]);
    return 0;
}
