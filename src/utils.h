#ifndef UTILS
#define UTILS

#include <eigen3/Eigen/Dense>


inline Eigen::VectorXcd convertToEigenVectorXcd(const std::vector<std::complex<double>> &stdVector)
{
  Eigen::VectorXcd eigenVector(stdVector.size());
  for (size_t i = 0; i < stdVector.size(); ++i) { eigenVector[i] = stdVector[i]; }
  return eigenVector;
}

inline std::vector<std::complex<double>> convertToVectorFromEigenVectorXcd(const Eigen::VectorXcd &eigenVector)
{
  std::vector<std::complex<double>> vec(eigenVector.size());
  for (size_t i = 0; i < eigenVector.size(); ++i) { vec[i] = eigenVector[i]; }
  return vec;
}

#endif// UTILS
