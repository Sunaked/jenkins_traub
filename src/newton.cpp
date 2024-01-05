#include "newton.h"

std::complex<double> newton(
    std::complex<double> x_0,
    std::function<std::complex<double>(std::complex<double>)> function,
    std::function<std::complex<double>(std::complex<double>)> first_derivative,
    double epsilon, int max_iterations) {
  std::complex<double> x_i = x_0;
  int num_iterations = 0;
  std::complex<double> x_i_next = x_i - (function(x_i) / first_derivative(x_i));
  num_iterations++;

  while (abs(x_i_next - x_i) > epsilon && num_iterations < max_iterations) {
    x_i = x_i_next;
    x_i_next = x_i - (function(x_i) / first_derivative(x_i));
    num_iterations++;
  }

  return x_i;
}
