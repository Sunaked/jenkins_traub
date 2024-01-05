#ifndef NEXT_STEP
#define NEXT_STEP

#include <eigen3/Eigen/Dense>
#include "synthetic_division.h"
#include <stdexcept>

Eigen::VectorXcd next_step(Eigen::VectorXcd a,
                          Eigen::VectorXcd H_bar_lambda, std::complex<double> s,
                          double epsilon, bool generate_t = true);

Eigen::VectorXcd addElementAtBeginning(const Eigen::VectorXcd& originalVector, const std::complex<double>& newElement);

#endif // NEXT_STEP
