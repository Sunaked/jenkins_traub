#include <cmath>
#include <functional>
#include <vector>
#include <iostream>
#include <complex>
#include <stdexcept>
#include <algorithm>

// Function to perform synthetic division and return remainder
double synthetic_division(const std::vector<double>& coefficients, double s) {
    double remainder = coefficients[0];
    for (size_t i = 1; i < coefficients.size(); ++i) {
        remainder = remainder * s + coefficients[i];
    }
    return remainder;
}

// Function to evaluate a polynomial with given coefficients
std::function<double(double)> evaluate(const std::vector<double>& coefficients) {
    return [&coefficients](double s) { return synthetic_division(coefficients, s); };
}

// Newton-Raphson method to find the root of a polynomial
double newton(double x_0, const std::function<double(double)>& function,
              const std::function<double(double)>& first_derivative,
              double epsilon, int max_iterations) {
    double x_i = x_0;
    int num_iterations = 0;
    double x_i_next = x_i - function(x_i) / first_derivative(x_i);
    num_iterations++;

    while (std::abs(x_i_next - x_i) > epsilon && num_iterations < max_iterations) {
        x_i = x_i_next;
        x_i_next = x_i - function(x_i) / first_derivative(x_i);
        num_iterations++;
    }

    return x_i;
}

std::vector<std::complex<double>> stage1(const std::vector<std::complex<double>>& a, const std::vector<std::complex<double>>& H_lambda, double epsilon, int max_iterations) {
    std::vector<std::complex<double>> H_bar_lambda(H_lambda.size());
    std::transform(H_lambda.begin(), H_lambda.end(), H_bar_lambda.begin(), [&H_lambda](std::complex<double> val) { return val / H_lambda[0]; });

    int num_iterations = 0;
    for (num_iterations = 0; num_iterations < max_iterations; ++num_iterations) {
        try {
            // next_step needs to be implemented
            std::tie(H_bar_lambda, ignore) = next_step(a, H_bar_lambda, 0, epsilon, false);
        } catch (std::exception&  e) {
            break;
        }
    }

    return {H_bar_lambda, num_iterations};
}

std::pair<std::vector<std::complex<double>>, int> stage2(const std::vector<std::complex<double>>& a, const std::vector<std::complex<double>>& H_lambda, std::complex<double> s, double epsilon, int max_iterations) {
    std::complex<double> t = std::complex<double>(INFINITY, 0), t_prev = t, t_prev_prev;
    int num_iterations = 0;
    std::vector<std::complex<double>> H_bar_lambda(H_lambda.size());
    std::transform(H_lambda.begin(), H_lambda.end(), H_bar_lambda.begin(), [&H_lambda](std::complex<double> val) { return val / H_lambda[0]; });

    while (true) {
        t_prev_prev = t_prev;
        t_prev = t;

        try {
            std::tie(H_bar_lambda, t) = next_step(a, H_bar_lambda, s, epsilon);
        } catch (std::exception& e) {
            break;
        }

        num_iterations++;

        bool condition1 = abs(t_prev - t_prev_prev) <= 0.5 * abs(t_prev_prev);
        bool condition2 = abs(t - t_prev) <= 0.5 * abs(t_prev);
        bool condition3 = num_iterations > max_iterations;

        if ((condition1 && condition2) || condition3) {
            break;
        }
    }

    return {H_bar_lambda, num_iterations};
}

std::tuple<std::vector<std::complex<double>>, std::complex<double>, int> stage3(const std::vector<std::complex<double>>& a, const std::vector<std::complex<double>>& H_L, std::complex<double> s, double epsilon, int max_iterations) {
    std::vector<std::complex<double>> polynomial = evaluate(a);
    std::vector<std::complex<double>> H_bar_coefficients(H_L.size());
    std::transform(H_L.begin(), H_L.end(), H_bar_coefficients.begin(), [&H_L](std::complex<double> val) { return val / H_L[0]; });
    std::vector<std::complex<double>> H_bar = evaluate(H_bar_coefficients);

    std::complex<double> s_L = s - polynomial(s) / H_bar(s);
    std::vector<std::complex<double>> H_bar_lambda = H_bar_coefficients;
    std::complex<double> s_lambda = s_L, s_lambda_prev = std::complex<double>(INFINITY, 0);
    int num_iterations = 0;

    while (abs(s_lambda - s_lambda_prev) > epsilon && num_iterations < max_iterations) {
        std::vector<std::complex<double>> p, h_bar;
        std::complex<double> p_at_s_lambda, h_bar_at_s_lambda;

        std::tie(p, p_at_s_lambda) = synthetic_division(a, s_lambda);
        std::tie(h_bar, h_bar_at_s_lambda) = synthetic_division(H_bar_lambda, s_lambda);
        h_bar.insert(h_bar.begin(), 0);

        if (abs(p_at_s_lambda) < epsilon) {
            return {H_bar_lambda, s_lambda, num_iterations};
        }

        std::vector<std::complex<double>> H_bar_lambda_next = p;
        for (size_t i = 0; i < p.size(); ++i) {
            H_bar_lambda_next[i] -= (p_at_s_lambda / h_bar_at_s_lambda) * h_bar[i];
        }
        std::vector<std::complex<double>> H_bar_next = evaluate(H_bar_lambda_next);

        num_iterations++;

        s_lambda_prev = s_lambda;
        s_lambda = s_lambda - p_at_s_lambda / H_bar_next(s_lambda);
        H_bar_lambda = H_bar_lambda_next;
    }

    if (num_iterations >= max_iterations) {
        std::cerr << "Stage 3 could not converge after " << num_iterations << " iterations" << std::endl;
        throw std::logic_error("huy");
    }

    return {H_bar_lambda, s_lambda, num_iterations};
}

int main() {
    // Example usage
    std::vector<double> modified_coefficients = {1, -8, 5, 14};
    std::vector<double> modified_derivative = {3, -16, 5};

    auto mod_function = evaluate(modified_coefficients);
    auto mod_derivative = evaluate(modified_derivative);

    double x_0 = 1;
    double beta = newton(x_0, mod_function, mod_derivative, 0.01, 500);
    printf("beta is: %f", beta); // 2.000000
}

