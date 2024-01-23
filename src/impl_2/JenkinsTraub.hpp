#ifndef EE6A8B2F_613F_4546_86D5_48B37A48B86B
#define EE6A8B2F_613F_4546_86D5_48B37A48B86B

#include "math.h"

class JenkinsTraub
{
private:
    void Quad(double a, double b1, double c, double *sr, double *si, double *lr, double *li);
    void Fxshfr(int l2, int *nz);
    void Quadit(double *uu, double *vv, int *nz);
    void Realit(double sss, int *nz, int *iflag);
    void Calcsc(int *type);
    void Nextk(int *type);
    void Newest(int type, double *uu, double *vv);
    void Quadsd(int n, double *u, double *v, double *p, double *q, double *a, double *b);
    double *p, *qp, *k, *qk, *svk;
    double sr, si, u, v, a, b, c, d, a1, a2;
    double a3, a6, a7, e, f, g, h, szr, szi, lzr, lzi;
    double eta, are, mre;
    int n, nn, nmi, zerok;
public:
    /**
     * solves polynomial with 'op' coefficients and writes answers to 'zeror' and 'zeroi'
    */
    int Solve(double *op, int degree, double *zeror, double *zeroi);
};


#endif /* EE6A8B2F_613F_4546_86D5_48B37A48B86B */
