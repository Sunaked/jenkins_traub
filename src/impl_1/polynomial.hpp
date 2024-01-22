#ifndef RPOLY_PLUS_PLUS_POLYNOMIAL_H_
#define RPOLY_PLUS_PLUS_POLYNOMIAL_H_

#include <Eigen/Core>

namespace rpoly_plus_plus {

// All polynomials are assumed to be the form
//
//   sum_{i=0}^N polynomial(i) x^{N-i}.
//
// and are given by a vector of coefficients of size N + 1.

// Remove leading terms with zero coefficients.
Eigen::VectorXd RemoveLeadingZeros(const Eigen::VectorXd &polynomial_in);

// Evaluate the polynomial at x using the Horner scheme.
template<typename T> inline T EvaluatePolynomial(const Eigen::VectorXd &polynomial, const T &x)
{
  T v = 0.0;
  for (int i = 0; i < polynomial.size(); ++i) { v = v * x + polynomial(i); }
  return v;
}

// Return the derivative of the given polynomial. It is assumed that
// the input polynomial is at least of degree zero.
Eigen::VectorXd DifferentiatePolynomial(const Eigen::VectorXd &polynomial);

// Multiplies the two polynoimals together.
Eigen::VectorXd MultiplyPolynomials(const Eigen::VectorXd &poly1, const Eigen::VectorXd &poly2);

// Adds two polynomials together.
Eigen::VectorXd AddPolynomials(const Eigen::VectorXd &poly1, const Eigen::VectorXd &poly2);

// Find a root from the starting guess using Newton's method.
double FindRootIterativeNewton(const Eigen::VectorXd &polynomial,
  const double x0,
  const double epsilon,
  const int max_iterations);

}// namespace rpoly_plus_plus

#endif// RPOLY_PLUS_PLUS_POLYNOMIAL_H_
