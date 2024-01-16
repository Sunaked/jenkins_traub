#include <complex>
#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>


/*
 * ====================
 * Forward declaration
 * ====================
 */

std::pair<Eigen::VectorXcd, std::complex<double>> synthetic_division(const Eigen::VectorXcd &coefficients,
  std::complex<double> s);


std::complex<double> newton(std::complex<double> x_0,
  std::function<std::complex<double>(std::complex<double>)> function,
  std::function<std::complex<double>(std::complex<double>)> first_derivative,
  double epsilon,
  int max_iterations);


/*
 * ====================
 *      Tests
 * ====================
 */


TEST(SyntheticDivisionTest, CorrectOutput)
{
  Eigen::VectorXcd coefficients(4);
  coefficients << 1, -3, 2, -4;// Polynomial x^3 - 3x^2 + 2x - 4
  std::complex<double> s(2, 0);// Dividing by x - 2

  auto [deflated, evaluation] = synthetic_division(coefficients, s);

  Eigen::VectorXcd expectedDeflated(3);
  expectedDeflated << 1, -1, 0;// Expected deflated polynomial x^2 - x

  ASSERT_EQ(deflated.size(), expectedDeflated.size());
  for (int i = 0; i < deflated.size(); ++i) { EXPECT_EQ(deflated(i), expectedDeflated(i)); }

  std::complex<double> expectedEvaluation(-4);// Expected evaluation
  EXPECT_EQ(evaluation, expectedEvaluation);
}

/*
 * ====================
 *     Newton
 * ====================
 */

TEST(NewtonTest, FindsRootCorrectly)
{
  std::complex<double> initial_guess(1.5, 0.0);// Closer to the root at z = 1
  double epsilon = 1e-6;// Tolerance
  int max_iterations = 1000;// Maximum iterations

  auto function = [](std::complex<double> z) { return z * z - 1.0; };
  auto first_derivative = [](std::complex<double> z) { return 2.0 * z; };

  std::complex<double> root = newton(initial_guess, function, first_derivative, epsilon, max_iterations);

  EXPECT_NEAR(root.real(), 1.0, epsilon);
  EXPECT_NEAR(root.imag(), 0.0, epsilon);
}

// Test case for a different root of the same polynomial
TEST(NewtonTest, FindsNegativeRoot)
{
  std::complex<double> initial_guess(-2.0, 0.0);
  double epsilon = 1e-6;
  int max_iterations = 1000;

  auto function = [](std::complex<double> z) { return z * z - 1.0; };
  auto first_derivative = [](std::complex<double> z) { return 2.0 * z; };

  std::complex<double> root = newton(initial_guess, function, first_derivative, epsilon, max_iterations);

  EXPECT_NEAR(root.real(), -1.0, epsilon);
  EXPECT_NEAR(root.imag(), 0.0, epsilon);
}

// Test case for a complex polynomial
TEST(NewtonTest, FindsRootOfComplexPolynomial)
{
  std::complex<double> initial_guess(-2.0, 1.0);
  double epsilon = 1e-6;
  int max_iterations = 1000;

  auto function = [](std::complex<double> z) { return z * z + 2.0 * z + 1.0; };
  auto first_derivative = [](std::complex<double> z) { return 2.0 * z + 2.0; };

  std::complex<double> root = newton(initial_guess, function, first_derivative, epsilon, max_iterations);

  EXPECT_NEAR(root.real(), -1.0, epsilon);
  EXPECT_NEAR(root.imag(), 0.0, epsilon);
}

// Test case for a non-polynomial function
TEST(NewtonTest, FindsRootOfExponentialFunction)
{
  std::complex<double> initial_guess(1.0, 0.0);
  double epsilon = 1e-6;
  int max_iterations = 1000;

  auto function = [](std::complex<double> z) { return exp(z) - 2.0; };
  auto first_derivative = [](std::complex<double> z) { return exp(z); };

  std::complex<double> root = newton(initial_guess, function, first_derivative, epsilon, max_iterations);

  double log2 = std::log(2.0);
  EXPECT_NEAR(root.real(), log2, epsilon);
  EXPECT_NEAR(root.imag(), 0.0, epsilon);
}
