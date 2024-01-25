#ifndef EE6A8B2F_613F_4546_86D5_48B37A48B86B
#define EE6A8B2F_613F_4546_86D5_48B37A48B86B

#include <cmath>
#include <vector>

template<typename T> class JenkinsTraub
{
private:
  static void Quad(T a, T b1, T c, T *sr, T *si, T *lr, T *li);
  static void Fxshfr(int l2, int *nz);
  static void Quadit(T *uu, T *vv, int *nz);
  static void Realit(T sss, int *nz, int *iflag);
  static void Calcsc(int *type);
  static void Nextk(int *type);
  static void Newest(int type, T *uu, T *vv);
  static void Quadsd(int n, T *u, T *v, T *p, T *q, T *a, T *b);
  static inline T *p, *qp, *k, *qk, *svk;
  static inline T sr, si, u, v, a, b, c, d, a1, a2;
  static inline T a3, a6, a7, e, f, g, h, szr, szi, lzr, lzi;
  static inline T eta, are, mre;
  static inline int n, nn, nmi, zerok;

public:
  /**
   * solves polynomial with 'op' coefficients and writes answers to 'zeror' and 'zeroi'
   */
  static int Solve(T *op, int degree, T *zeror, T *zeroi);

  /**
   * solves polynomial with 'op' coefficients and writes answers to 'zeror' and 'zeroi'
   */
  static int Solve(std::vector<T> op, int degree, std::vector<T> &zeror, std::vector<T> &zeroi);
};


#endif /* EE6A8B2F_613F_4546_86D5_48B37A48B86B */
