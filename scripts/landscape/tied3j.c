/* Taylor-series integrator for the tied Pythagorean free-fall family in
 * pair-adapted Jacobi coordinates (selected pair vector X, third-body vector Y),
 * with chart switching to the currently closest pair.  Ordinary double-precision
 * numerics, NOT a certificate.  Records syzygy sequence (middle body letters),
 * z-extrema (Montgomery normalized area), I-maxima, K-minima per inter-syzygy arc,
 * stutters, and an escape/collision verdict using the paper's escape lemma.
 * Usage: tied3j u [tmax] [order] [collision_threshold]
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXN 44
static int N = 26;
static double TOL = 1e-18;
static double m[3], Mtot;
static int pi_, pj_, pk_;              /* selected pair (i,j), third k; (i,j,k) cyclic */
static double ca, cb;                  /* a = m_i/M_ij, b = m_j/M_ij */
static double Mij;
static double TAU = 1.0;

/* Taylor arrays: X, Y and velocities; D[0]=X, D[1]=D_ik=Y+bX, D[2]=D_jk=Y-aX */
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
        for (p = 0; p < 3; p++) {
            double s = 0;
            for (k = 0; k <= n; k++) s += D[k][p][0] * D[n - k][p][0] + D[k][p][1] * D[n - k][p][1];
            W[n][p] = s;
        }
        for (p = 0; p < 3; p++) {
            if (n == 0) S[0][p] = pow(W[0][p], -1.5);
            else { double s = 0; const double al = -1.5;
                for (k = 1; k <= n; k++) s += (al * k - (n - k)) * W[k][p] * S[n - k][p];
                S[n][p] = s / (n * W[0][p]); }
        }
        for (p = 0; p < 3; p++) for (c = 0; c < 2; c++) { double s = 0; for (k = 0; k <= n; k++) s += D[k][p][c] * S[n - k][p]; P[n][p][c] = s; }
        /* accelerations: Xdd = -Mij P0 + mk (P2 - P1); Ydd = -(M/Mij)(mi P1 + mj P2) */
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

typedef struct { double Delta, Ddot, sumr2, z, zdot, I, Idot, K, U, Udot, rmin, r[3]; int pmin; } Diag;

/* diagnostics from pair-adapted coordinates (labels: D0=X=q_j-q_i, D1=q_k-q_i, D2=q_k-q_j) */
static void diag(double x[2], double y[2], double vx[2], double vy[2], Diag *d) {
    double dd[3][2] = {{x[0], x[1]}, {y[0] + cb * x[0], y[1] + cb * x[1]}, {y[0] - ca * x[0], y[1] - ca * x[1]}};
    double vv[3][2] = {{vx[0], vx[1]}, {vy[0] + cb * vx[0], vy[1] + cb * vx[1]}, {vy[0] - ca * vx[0], vy[1] - ca * vx[1]}};
    /* signed area of labelled triangle: (i,j,k) cyclic so (q_j-q_i)x(q_k-q_i) = (q2-q1)x(q3-q1) */
    d->Delta = 0.5 * (dd[0][0] * dd[1][1] - dd[0][1] * dd[1][0]);
    d->Ddot = 0.5 * (vv[0][0] * dd[1][1] - vv[0][1] * dd[1][0] + dd[0][0] * vv[1][1] - dd[0][1] * vv[1][0]);
    double sr = 0, srd = 0; d->rmin = 1e300;
    /* pair masses: D0 pair (i,j), D1 pair (i,k), D2 pair (j,k) */
    double pm[3] = {m[pi_] * m[pj_], m[pi_] * m[pk_], m[pj_] * m[pk_]};
    double U = 0, Ud = 0;
    for (int p = 0; p < 3; p++) {
        double r2 = dd[p][0] * dd[p][0] + dd[p][1] * dd[p][1], rd = dd[p][0] * vv[p][0] + dd[p][1] * vv[p][1];
        d->r[p] = sqrt(r2); sr += r2; srd += 2 * rd;
        U += pm[p] / d->r[p]; Ud -= pm[p] * rd / (r2 * d->r[p]);
        if (d->r[p] < d->rmin) { d->rmin = d->r[p]; d->pmin = p; }
    }
    d->sumr2 = sr; d->z = 4 * sqrt(3.0) * d->Delta / sr;
    d->zdot = 4 * sqrt(3.0) * (d->Ddot * sr - d->Delta * srd) / (sr * sr);
    double mu1 = m[pi_] * m[pj_] / Mij, mu2 = m[pk_] * Mij / Mtot;
    d->I = mu1 * (x[0] * x[0] + x[1] * x[1]) + mu2 * (y[0] * y[0] + y[1] * y[1]);
    d->Idot = 2 * (mu1 * (x[0] * vx[0] + x[1] * vx[1]) + mu2 * (y[0] * vy[0] + y[1] * vy[1]));
    d->K = 0.5 * (mu1 * (vx[0] * vx[0] + vx[1] * vx[1]) + mu2 * (vy[0] * vy[0] + vy[1] * vy[1]));
    d->U = U; d->Udot = Ud;
}

/* escape lemma for binary = current selected pair (i,j), escaper k, using X,Y directly */
static int escape_check(double x[2], double y[2], double vx[2], double vy[2], double eta, double *margin) {
    double M = Mij, mc = m[pk_];
    double r = sqrt(x[0] * x[0] + x[1] * x[1]), rho = sqrt(y[0] * y[0] + y[1] * y[1]);
    double rhodot = (y[0] * vy[0] + y[1] * vy[1]) / rho;
    double e = 0.5 * (vx[0] * vx[0] + vx[1] * vx[1]) - M / r;
    double R = M / eta, s0 = rho - R;
    if (s0 <= 0 || rhodot <= 0) return 0;
    double delta = 0.5 * rhodot * rhodot - (M + mc) / s0;
    if (delta <= 0) return 0;
    *margin = -eta - e - mc * sqrt(2 * M * R) / (sqrt(2 * delta) * s0 * s0);
    return *margin > 0;
}

/* switch chart from current pair to pair index p (0:(0,1) 1:(1,2) 2:(2,0)) */
static void switch_pair(int p, double x[2], double y[2], double vx[2], double vy[2]) {
    /* reconstruct labelled Cartesian CM-frame positions from current chart */
    double q[3][2], v[3][2];
    for (int c = 0; c < 2; c++) {
        double cm = -(m[pk_] / Mtot) * y[c], cmv = -(m[pk_] / Mtot) * vy[c];
        q[pk_][c] = (Mij / Mtot) * y[c]; v[pk_][c] = (Mij / Mtot) * vy[c];
        q[pi_][c] = cm - cb * x[c]; v[pi_][c] = cmv - cb * vx[c];
        q[pj_][c] = cm + ca * x[c]; v[pj_][c] = cmv + ca * vx[c];
    }
    setpair(p);
    for (int c = 0; c < 2; c++) {
        x[c] = q[pj_][c] - q[pi_][c]; vx[c] = v[pj_][c] - v[pi_][c];
        y[c] = q[pk_][c] - (m[pi_] * q[pi_][c] + m[pj_] * q[pj_][c]) / Mij;
        vy[c] = v[pk_][c] - (m[pi_] * v[pi_][c] + m[pj_] * v[pj_][c]) / Mij;
    }
}

#define MAXEV 6000
int main(int argc, char **argv) {
    double u = atof(argv[1]);
    double tmax = argc > 2 ? atof(argv[2]) : 100.0;
    if (argc > 3) N = atoi(argv[3]);
    double rcoll = argc > 4 ? atof(argv[4]) : 1e-9;
    double den = 1 + u * u, A = (1 - u * u) / den, B = 2 * u / den;
    m[0] = A; m[1] = B; m[2] = 1.0; Mtot = A + B + 1;
    double q[3][2] = {{-0.5, 0}, {0.5, 0}, {(B * B - A * A) / 2, A * B}};
    /* initial chart: closest pair */
    double r01 = 1, r12 = A, r20 = B; int p0 = 0; if (r12 < r01 && r12 <= r20) p0 = 1; if (r20 < r01 && r20 < r12) p0 = 2;
    setpair(p0);
    double x[2], y[2], vx[2] = {0, 0}, vy[2] = {0, 0};
    for (int c = 0; c < 2; c++) { x[c] = q[pj_][c] - q[pi_][c]; y[c] = q[pk_][c] - (m[pi_] * q[pi_][c] + m[pj_] * q[pj_][c]) / Mij; }
    double U0 = A * B + 1 / (A * B);
    double t = 0; long nsteps = 0, nswitch = 0;
    Diag d0, d1; diag(x, y, vx, vy, &d0);
    double H0 = d0.K - d0.U, Herrmax = 0;
    double rmin_global = d0.rmin; double t_rmin = 0;
    static char syz[8192]; int nsyz = 0; syz[0] = 0; double tsyz_first = -1;
    static double ev_t[MAXEV], ev_K[MAXEV], ev_Idot[MAXEV], ev_z[MAXEV], ev_rmin[MAXEV]; static int ev_arc[MAXEV], ev_type[MAXEV]; int nev = 0; /* type 0 z-ext, 1 K-min, 2 I-max */
    int verdict = 0; double t_verdict = -1; int escaper = -1; double esc_margin = 0, esc_eta = 0;
    double first_imin_t = -1; int had_imin = 0; int arc = 0;
    double xn[2], yn[2], vxn[2], vyn[2], xa[2], ya[2], vxa[2], vya[2]; Diag da;
    while (t < tmax) {
        { double rr = d0.rmin; double tau = 0.5 * sqrt(rr * rr * rr / Mtot); TAU = tau < 1 ? tau : 1.0; }
        taylor(x, y, vx, vy);
        double hs = stepsize(); double h = hs * TAU; if (h > 0.05) h = 0.05; if (t + h > tmax) h = tmax - t;
        evalpoly(h / TAU, xn, yn, vxn, vyn); diag(xn, yn, vxn, vyn, &d1);
        if (d0.Delta * d1.Delta < 0) {
            double a = 0, b = h;
            for (int it = 0; it < 60; it++) { double c = 0.5 * (a + b); evalpoly(c / TAU, xa, ya, vxa, vya); diag(xa, ya, vxa, vya, &da); if (da.Delta * d0.Delta < 0) b = c; else a = c; }
            evalpoly(0.5 * (a + b) / TAU, xa, ya, vxa, vya); diag(xa, ya, vxa, vya, &da);
            /* middle body: distances r[0]=r_ij, r[1]=r_ik, r[2]=r_jk; middle is the one whose two distances are smallest sum... use: body i middle iff r_ij + r_ik = r_jk */
            int mid; double s0 = da.r[0] + da.r[1] - da.r[2], s1 = da.r[0] + da.r[2] - da.r[1], s2 = da.r[1] + da.r[2] - da.r[0];
            if (s0 <= s1 && s0 <= s2) mid = pi_; else if (s1 <= s2) mid = pj_; else mid = pk_;
            if (nsyz < 8000) { syz[nsyz++] = '1' + mid; syz[nsyz] = 0; }
            if (tsyz_first < 0) tsyz_first = t + 0.5 * (a + b);
            arc++;
        }
        if (t + h > 1e-3) {
            if (d0.zdot * d1.zdot < 0) {
                double a = 0, b = h;
                for (int it = 0; it < 60; it++) { double c = 0.5 * (a + b); evalpoly(c / TAU, xa, ya, vxa, vya); diag(xa, ya, vxa, vya, &da); if (da.zdot * d0.zdot < 0) b = c; else a = c; }
                evalpoly(0.5 * (a + b) / TAU, xa, ya, vxa, vya); diag(xa, ya, vxa, vya, &da);
                if (nev < MAXEV) { ev_t[nev] = t + 0.5 * (a + b); ev_K[nev] = da.K; ev_Idot[nev] = da.Idot; ev_z[nev] = da.z; ev_rmin[nev] = da.rmin; ev_arc[nev] = arc; ev_type[nev] = 0; nev++; }
            }
            if (d0.Udot < 0 && d1.Udot > 0) { /* K minimum (Kdot = Udot) */
                double a = 0, b = h;
                for (int it = 0; it < 60; it++) { double c = 0.5 * (a + b); evalpoly(c / TAU, xa, ya, vxa, vya); diag(xa, ya, vxa, vya, &da); if (da.Udot > 0) b = c; else a = c; }
                evalpoly(0.5 * (a + b) / TAU, xa, ya, vxa, vya); diag(xa, ya, vxa, vya, &da);
                if (nev < MAXEV) { ev_t[nev] = t + 0.5 * (a + b); ev_K[nev] = da.K; ev_Idot[nev] = da.Idot; ev_z[nev] = da.z; ev_rmin[nev] = da.rmin; ev_arc[nev] = arc; ev_type[nev] = 1; nev++; }
            }
            if (d0.Idot > 0 && d1.Idot < 0) {
                double a = 0, b = h;
                for (int it = 0; it < 60; it++) { double c = 0.5 * (a + b); evalpoly(c / TAU, xa, ya, vxa, vya); diag(xa, ya, vxa, vya, &da); if (da.Idot < 0) b = c; else a = c; }
                evalpoly(0.5 * (a + b) / TAU, xa, ya, vxa, vya); diag(xa, ya, vxa, vya, &da);
                if (nev < MAXEV) { ev_t[nev] = t + 0.5 * (a + b); ev_K[nev] = da.K; ev_Idot[nev] = da.Idot; ev_z[nev] = da.z; ev_rmin[nev] = da.rmin; ev_arc[nev] = arc; ev_type[nev] = 2; nev++; }
            }
            if (d0.Idot < 0 && d1.Idot > 0 && !had_imin) { had_imin = 1; first_imin_t = t + h; }
        }
        if (d1.rmin < rmin_global) { rmin_global = d1.rmin; t_rmin = t + h; }
        t += h; nsteps++;
        memcpy(x, xn, sizeof(x)); memcpy(y, yn, sizeof(y)); memcpy(vx, vxn, sizeof(vx)); memcpy(vy, vyn, sizeof(vy)); d0 = d1;
        { double he = fabs((d1.K - d1.U - H0) / H0); if (he > Herrmax) Herrmax = he; }
        if (d1.rmin < rcoll) { verdict = 2; t_verdict = t; break; }
        /* escape test for current pair as binary */
        { double best = -1e300; double beta = 0; int ok = 0;
          double etas[4] = {1, 2, 4, 8};
          for (int e = 0; e < 4; e++) { double mg; if (escape_check(x, y, vx, vy, etas[e], &mg)) { ok = 1; if (mg > best) { best = mg; beta = etas[e]; } } }
          if (ok) { verdict = 1; t_verdict = t; escaper = pk_; esc_margin = best; esc_eta = beta; break; } }
        /* chart switch if another pair is closer than selected by factor */
        if (d1.pmin != 0 && d1.r[d1.pmin] < 0.8 * d1.r[0]) {
            /* map local pair index to global pair index: D1 = (i,k), D2 = (j,k) */
            int gi = (d1.pmin == 1) ? pi_ : pj_, gk = pk_;
            int gp = (gi == 0 && gk == 1) || (gi == 1 && gk == 0) ? 0 : ((gi == 1 && gk == 2) || (gi == 2 && gk == 1) ? 1 : 2);
            switch_pair(gp, x, y, vx, vy); diag(x, y, vx, vy, &d0); nswitch++;
        }
        if (nsteps > 6000000) break;
    }
    diag(x, y, vx, vy, &d1);
    double Herr = fabs((d1.K - d1.U - H0) / H0);
    int nstut = 0; static char stut[2048]; stut[0] = 0; int sl = 0;
    for (int i = 1; i < nsyz; i++) if (syz[i] == syz[i - 1]) { nstut++; if (sl < 2000) sl += snprintf(stut + sl, 2048 - sl, "%s%d", sl ? "," : "", i); }
    /* per-arc minimum K over K-min events and z-extrema; report the global min and stutter-arc min */
    double Kmin = 1e300, Kmin_t = 0; int Kmin_arc = -1, Kmin_type = -1;
    for (int i = 0; i < nev; i++) if (ev_t[i] > 0.2 && ev_K[i] < Kmin) { Kmin = ev_K[i]; Kmin_t = ev_t[i]; Kmin_arc = ev_arc[i]; Kmin_type = ev_type[i]; }
    printf("{\"u\":%.12g,\"verdict\":%d,\"t_end\":%.6f,\"escaper\":%d,\"esc_margin\":%.4g,\"esc_eta\":%g,\"rmin\":%.4g,\"t_rmin\":%.4f,"
           "\"nsyz\":%d,\"syz\":\"%s\",\"t_syz1\":%.6f,\"t_imin1\":%.6f,\"nstut\":%d,\"stut\":\"%s\","
           "\"Kmin\":%.6g,\"Kmin_over_U0\":%.6g,\"t_Kmin\":%.5f,\"arc_Kmin\":%d,\"type_Kmin\":%d,\"U0\":%.6f,\"Herr\":%.2e,\"Herrmax\":%.2e,\"nsteps\":%ld,\"nswitch\":%ld,\"nev\":%d,\"ev\":[",
           u, verdict, t, escaper, esc_margin, esc_eta, rmin_global, t_rmin, nsyz, syz, tsyz_first, first_imin_t, nstut, stut,
           Kmin, Kmin / U0, Kmin_t, Kmin_arc, Kmin_type, U0, Herr, Herrmax, nsteps, nswitch, nev);
    /* print only events with K/U0 < 0.05 to bound output size */
    int first = 1;
    for (int i = 0; i < nev; i++) if (ev_K[i] / U0 < 0.05 && ev_t[i] > 0.2) { printf("%s[%.5f,%d,%d,%.5g,%.4g,%.4g,%.3g]", first ? "" : ",", ev_t[i], ev_arc[i], ev_type[i], ev_K[i] / U0, ev_z[i], ev_Idot[i], ev_rmin[i]); first = 0; }
    printf("]}\n");
    return 0;
}
