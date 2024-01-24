#ifndef BASESOLVER_H
#define BASESOLVER_H

#include <complex>
#include <vector>

template<typename T> class BaseSolver
{
public:
  /**
   * \brief Find the roots of a polynomial.
   * \param coeff Polynomials coefficients.
   * \param roots Vector to store the roots.
   * \param conv Vector to store convergence status of each root.
   * \param itmax Maximum number of iterations.
   */
  virtual void
    operator()(std::vector<T> &coeff, std::vector<std::complex<T>> &roots, std::vector<int> &conv, int itmax) = 0;
};

#endif
