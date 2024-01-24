#ifndef EE6A8B2F_613F_4546_86D5_48B37A48B86B
#define EE6A8B2F_613F_4546_86D5_48B37A48B86B

#include <cmath>
#include <vector>

class JenkinsTraub
{
private:
    static void Quad(double a, double b1, double c, double *sr, double *si, double *lr, double *li);
    static void Fxshfr(int l2, int *nz);
    static void Quadit(double *uu, double *vv, int *nz);
    static void Realit(double sss, int *nz, int *iflag);
    static void Calcsc(int *type);
    static void Nextk(int *type);
    static void Newest(int type, double *uu, double *vv);
    static void Quadsd(int n, double *u, double *v, double *p, double *q, double *a, double *b);
    static inline double *p, *qp, *k, *qk, *svk;
    static inline double sr, si, u, v, a, b, c, d, a1, a2;
    static inline double a3, a6, a7, e, f, g, h, szr, szi, lzr, lzi;
    static inline double eta, are, mre;
    static inline int n, nn, nmi, zerok;
public:
    /**
     * solves polynomial with 'op' coefficients and writes answers to 'zeror' and 'zeroi'
    */
    static int Solve(double *op, int degree, double *zeror, double *zeroi);

    /**
     * solves polynomial with 'op' coefficients and writes answers to 'zeror' and 'zeroi'
    */
    static int Solve(std::vector<double> op, int degree, std::vector<double>& zeror, std::vector<double>& zeroi);
};


#endif /* EE6A8B2F_613F_4546_86D5_48B37A48B86B */
