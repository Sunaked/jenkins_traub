#include "next_step.h"
#include <algorithm>
#include <cmath>
#include <complex>
#include <eigen3/Eigen/Dense>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

Eigen::VectorXcd convertToEigenVectorXcd(const std::vector<std::complex<double>>& stdVector) {
    Eigen::VectorXcd eigenVector(stdVector.size());
    for (size_t i = 0; i < stdVector.size(); ++i) {
        eigenVector[i] = stdVector[i];
    }
    return eigenVector;
}

std::vector<std::complex<double>> convertToVectorFromEigenVectorXcd(const Eigen::VectorXcd& eigenVector) {
    std::vector<std::complex<double>> vec(eigenVector.size());
    for (size_t i = 0; i < eigenVector.size(); ++i) {
        vec[i] = eigenVector[i];
    }
    return vec;
}

std::function<std::complex<double>(std::complex<double>)>
evaluate(const std::vector<std::complex<double>> &coefficients) {
  return [coefficients](std::complex<double> s) {
    return synthetic_division(convertToEigenVectorXcd(coefficients), s).second;
  };
}

std::vector<std::complex<double>>
stage1(const std::vector<std::complex<double>> &a,
       const std::vector<std::complex<double>> &H_lambda, double epsilon,
       int max_iterations) {
  std::vector<std::complex<double>> H_bar_lambda(H_lambda.size());
  std::transform(
      H_lambda.begin(), H_lambda.end(), H_bar_lambda.begin(),
      [&H_lambda](std::complex<double> val) { return val / H_lambda[0]; });

  int num_iterations = 0;
  for (num_iterations = 0; num_iterations < max_iterations; ++num_iterations) {
    try {
      // next_step needs to be implemented
      H_bar_lambda = next_step(a, H_bar_lambda, 0, epsilon, false);
    } catch (std::exception &e) {
      break;
    }
  }

  return {H_bar_lambda, num_iterations};
}

std::pair<std::vector<std::complex<double>>, int>
stage2(const std::vector<std::complex<double>> &a,
       const std::vector<std::complex<double>> &H_lambda,
       std::complex<double> s, double epsilon, int max_iterations) {
  std::complex<double> t = std::complex<double>(INFINITY, 0), t_prev = t,
                       t_prev_prev;
  int num_iterations = 0;
  std::vector<std::complex<double>> H_bar_lambda(H_lambda.size());
  std::transform(
      H_lambda.begin(), H_lambda.end(), H_bar_lambda.begin(),
      [&H_lambda](std::complex<double> val) { return val / H_lambda[0]; });

  while (true) {
    t_prev_prev = t_prev;
    t_prev = t;

    try {
      H_bar_lambda = next_step(a, H_bar_lambda, s, epsilon);
    } catch (std::exception &e) {
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

std::tuple<std::vector<std::complex<double>>, std::complex<double>, int>
stage3(const std::vector<std::complex<double>> &a,
       const std::vector<std::complex<double>> &H_L, std::complex<double> s,
       double epsilon, int max_iterations) {
  auto polynomial = evaluate(a);
  std::vector<std::complex<double>> H_bar_coefficients(H_L.size());
  std::transform(H_L.begin(), H_L.end(), H_bar_coefficients.begin(),
                 [&H_L](std::complex<double> val) { return val / H_L[0]; });
  auto H_bar = evaluate(H_bar_coefficients);

  std::complex<double> s_L = s - polynomial(s) / H_bar(s);
  std::vector<std::complex<double>> H_bar_lambda = H_bar_coefficients;
  std::complex<double> s_lambda = s_L,
                       s_lambda_prev = std::complex<double>(INFINITY, 0);
  int num_iterations = 0;

  while (abs(s_lambda - s_lambda_prev) > epsilon &&
         num_iterations < max_iterations) {
    std::vector<std::complex<double>> p, h_bar;
    std::complex<double> p_at_s_lambda, h_bar_at_s_lambda;

    // std::tie(p, p_at_s_lambda) = synthetic_division(a, s_lambda);
    auto p_ = synthetic_division(convertToEigenVectorXcd(a), s_lambda);
    // std::tie(h_bar, h_bar_at_s_lambda) = synthetic_division(H_bar_lambda, s_lambda);

    //NEDD FIX
    auto h_bar_ = synthetic_division(convertToEigenVectorXcd(H_bar_lambda), s_lambda); //---
    h_bar.insert(h_bar.begin(), 0);//---

    if (abs(p_at_s_lambda) < epsilon) {//---
      return {H_bar_lambda, s_lambda, num_iterations};//---
    }

    std::vector<std::complex<double>> H_bar_lambda_next = p;
    for (size_t i = 0; i < p.size(); ++i) {
      H_bar_lambda_next[i] -= (p_at_s_lambda / h_bar_at_s_lambda) * h_bar[i];
    }
    auto H_bar_next = evaluate(H_bar_lambda_next);

    num_iterations++;

    s_lambda_prev = s_lambda;
    s_lambda = s_lambda - p_at_s_lambda / H_bar_next(s_lambda);
    H_bar_lambda = H_bar_lambda_next;
  }

  if (num_iterations >= max_iterations) {
    std::cerr << "Stage 3 could not converge after " << num_iterations
              << " iterations" << std::endl;
    throw std::logic_error("Too many iterations");
  }

  return {H_bar_lambda, s_lambda, num_iterations};
}

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

std::pair<std::vector<std::complex<double>>, std::complex<double>>
jenkins_traub_inner(const std::vector<std::complex<double>> &coefficients,
                    double epsilon, int max_iterations,
                    bool do_stage_one = true) {
  // Handle special cases
  if (!coefficients.empty() &&
      coefficients.back() == std::complex<double>(0, 0)) {
    return {coefficients, std::complex<double>(0, 0)};
  }

  if (coefficients.size() < 2) {
    return {};
  }

  std::vector<std::complex<double>> a = coefficients;

  // Scale coefficients so leading coefficient is 1
  if (a.front() != std::complex<double>(1, 0)) {
    std::complex<double> leading_coeff = a.front();
    for (auto &coeff : a) {
      coeff /= leading_coeff;
    }
  }

  if (a.size() == 2) {
    return {{}, -a.back() / a.front()};
  }

  // Compute H^0, the derivative of the polynomial
  std::vector<std::complex<double>> H_0(a.size() - 1);
  for (size_t i = 1; i < a.size(); ++i) {
    H_0[i - 1] = a[i] * static_cast<double>(i);
  }

  std::vector<std::complex<double>> H_lambda = H_0;
  std::complex<double> s_lambda;

  // Stage 1
  if (do_stage_one) {
    H_lambda = stage1(a, H_0, epsilon, 5);
    std::cout << "Done with Stage 1." << std::endl;
  }

  // Compute modified polynomial and its derivative
  std::vector<std::complex<double>> modified_coefficients = a;
  for (auto &coeff : modified_coefficients) {
    coeff = std::abs(coeff);
  }
  modified_coefficients.back() *= -1;

  std::vector<std::complex<double>> modified_derivative(
      modified_coefficients.size() - 1);
  for (size_t i = 1; i < modified_coefficients.size(); ++i) {
    modified_derivative[i - 1] =
        modified_coefficients[i] * static_cast<double>(i);
  }

  auto mod_function = evaluate(modified_coefficients);
  auto mod_derivative = evaluate(modified_derivative);

  // Newton's iteration to find beta
  std::complex<double> beta = newton(std::complex<double>(1, 0), mod_function,
                                     mod_derivative, 0.01, 500);

  // Random number generation for phi_random
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 2 * M_PI);

  while (true) {
    double phi_random = dis(gen);
    s_lambda = std::complex<double>(cos(phi_random), sin(phi_random)) * beta;

    try {
      std::tie(H_lambda, s_lambda) =
          stage2(a, H_lambda, s_lambda, epsilon, 100);
      std::cout << "Done with Stage 2." << std::endl;

      auto [H_bar_lambda, s_lambda_final, num_iterations] =
          stage3(a, H_lambda, s_lambda, epsilon, max_iterations);
      std::cout << "Done with Stage 3 after " << num_iterations
                << " iterations." << std::endl;
      return {H_bar_lambda, s_lambda_final};
    } catch (const std::exception &e) {
      max_iterations *= 2;
      continue;
    }
  }
}

// Assuming synthetic_division, jenkins_traub_inner are already defined

std::vector<std::complex<double>>
jenkins_traub(const std::vector<std::complex<double>> &input_coefficients,
              double epsilon, int max_iterations) {
  std::vector<std::complex<double>> coefficients = input_coefficients;
  std::vector<std::complex<double>> roots;

  // Remove leading coefficients equal to 0
  while (!coefficients.empty() &&
         coefficients.front() == std::complex<double>(0, 0)) {
    coefficients.erase(coefficients.begin());
  }

  if (coefficients.empty()) {
    std::cout << "Fed the zero polynomial. Roots are all complex numbers."
              << std::endl;
    return {};
  } else if (coefficients.size() == 1) {
    std::cout << "Fed a constant. There are no roots." << std::endl;
    return {};
  }

  for (size_t x = 0; x < coefficients.size() - 1; ++x) {
    if (coefficients.size() > 1) {
      auto [deflated, s] =
          jenkins_traub_inner(coefficients, epsilon, max_iterations);
      roots.push_back(s);
      coefficients = convertToVectorFromEigenVectorXcd(synthetic_division(convertToEigenVectorXcd(coefficients), s).first);
    }
  }

  return roots;
}

int main() {
  // Example usage
  std::vector<std::complex<double>> modified_coefficients = {1, -8, 5, 14};
  std::vector<std::complex<double>> modified_derivative = {3, -16, 5};

  auto mod_function = evaluate(modified_coefficients);
  auto mod_derivative = evaluate(modified_derivative);

  std::complex<double> x_0 = 1;
  std::complex<double> beta =
      newton(x_0, mod_function, mod_derivative, 0.01, 500);

  std::cout << "Beta: " << beta << std::endl;

  return 0;
}
