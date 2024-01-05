#include <cmath>
#include <functional>
#include <vector>
#include <iostream>
#include <complex>
#include <stdexcept>
#include <algorithm>

std::pair<std::vector<std::complex<double>>, std::complex<double>> synthetic_division(const std::vector<std::complex<double>>& coefficients, std::complex<double> s) {
    std::vector<std::complex<double>> deflated(coefficients.size() - 1);
    deflated[0] = coefficients[0];

    for (size_t i = 1; i < coefficients.size() - 1; ++i) {
        deflated[i] = coefficients[i] + deflated[i - 1] * s;
    }

    std::complex<double> evaluation = coefficients.back() + deflated.back() * s;

    return {deflated, evaluation};
}

std::function<std::complex<double>(std::complex<double>)> evaluate(const std::vector<std::complex<double>>& coefficients) {
    return [coefficients](std::complex<double> s) {
        return synthetic_division(coefficients, s).second;
    };
}

std::complex<double> newton(std::complex<double> x_0, std::function<std::complex<double>(std::complex<double>)> function, std::function<std::complex<double>(std::complex<double>)> first_derivative, double epsilon, int max_iterations) {
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

int main() {
    // Example usage
    std::vector<std::complex<double>> modified_coefficients = {1, -8, 5, 14};
    std::vector<std::complex<double>> modified_derivative = {3, -16, 5};

    auto mod_function = evaluate(modified_coefficients);
    auto mod_derivative = evaluate(modified_derivative);

    std::complex<double> x_0 = 1;
    std::complex<double> beta = newton(x_0, mod_function, mod_derivative, 0.01, 500);

    std::cout << "Beta: " << beta << std::endl;

    return 0;
}
