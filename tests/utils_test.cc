#include "utils.h"
#include <complex>
#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>
#include <vector>


// Test case
TEST(ConvertToEigenVectorXcdTest, BasicAssertions)
{
  std::vector<std::complex<double>> stdVector = { { 1.0, 2.0 }, { 3.0, 4.0 }, { 5.0, 6.0 } };
  Eigen::VectorXcd expected(3);
  expected << std::complex<double>(1.0, 2.0), std::complex<double>(3.0, 4.0), std::complex<double>(5.0, 6.0);


  // Inline functions should be implemented inside header files, only this way it could be tested
  Eigen::VectorXcd result = /* inline */ convertToEigenVectorXcd(stdVector);

  ASSERT_EQ(result.size(), expected.size());
  for (int i = 0; i < result.size(); ++i) { EXPECT_EQ(result[i], expected[i]); }
}

TEST(ConvertToVectorFromEigenVectorXcdTest, ConvertsCorrectly)
{
  Eigen::VectorXcd eigenVector(3);
  eigenVector << std::complex<double>(1.0, 2.0), std::complex<double>(3.0, 4.0), std::complex<double>(5.0, 6.0);

  std::vector<std::complex<double>> expected = { { 1.0, 2.0 }, { 3.0, 4.0 }, { 5.0, 6.0 } };

  std::vector<std::complex<double>> result = convertToVectorFromEigenVectorXcd(eigenVector);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) { EXPECT_EQ(result[i], expected[i]); }
}

// Test case
TEST(AddElementAtBeginningTest, AddsElementCorrectly)
{
  Eigen::VectorXcd originalVector(2);
  originalVector << std::complex<double>(1.0, 2.0), std::complex<double>(3.0, 4.0);

  std::complex<double> newElement(5.0, 6.0);

  Eigen::VectorXcd result = addElementAtBeginning(originalVector, newElement);

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], newElement);
  for (int i = 0; i < originalVector.size(); ++i) { EXPECT_EQ(result[i + 1], originalVector[i]); }
}
