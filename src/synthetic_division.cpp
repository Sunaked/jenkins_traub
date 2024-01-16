#include "synthetic_division.h"

std::pair<Eigen::VectorXcd, std::complex<double>> synthetic_division(const Eigen::VectorXcd &coefficients,
  std::complex<double> s)
{
  int n = coefficients.size();
  Eigen::VectorXcd deflated(n - 1);

  deflated(0) = coefficients(0);

  for (int i = 1; i < n - 1; ++i) { deflated(i) = coefficients(i) + deflated(i - 1) * s; }

  std::complex<double> evaluation = coefficients(n - 1) + deflated(n - 2) * s;

  return std::make_pair(deflated, evaluation);
}
