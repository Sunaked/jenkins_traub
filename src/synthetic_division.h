#ifndef SYNTHETIC_DIVISION
#define SYNTHETIC_DIVISION

#include <complex>
#include <eigen3/Eigen/Dense>
#include <vector>

std::pair<Eigen::VectorXcd, std::complex<double>>
synthetic_division(const Eigen::VectorXcd &coefficients,
                   std::complex<double> s);

#endif // SYNTHETIC_DIVISION
