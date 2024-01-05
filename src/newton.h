#ifndef NEWTON
#define NEWTON

#include <complex>
#include <functional>
#include <iostream>

std::complex<double> newton(
    std::complex<double> x_0,
    std::function<std::complex<double>(std::complex<double>)> function,
    std::function<std::complex<double>(std::complex<double>)> first_derivative,
    double epsilon, int max_iterations);

#endif // NEWTON
