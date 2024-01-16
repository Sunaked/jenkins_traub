#ifndef UTILS
#define UTILS

#include <eigen3/Eigen/Dense>


// Inline functions should be implemented inside header files, only this way it could be tested
inline Eigen::VectorXcd convertToEigenVectorXcd(const std::vector<std::complex<double>> &stdVector)
{
  Eigen::VectorXcd eigenVector(stdVector.size());
  for (size_t i = 0; i < stdVector.size(); ++i) { eigenVector[i] = stdVector[i]; }
  return eigenVector;
}

// Inline functions should be implemented inside header files, only this way it could be tested
inline std::vector<std::complex<double>> convertToVectorFromEigenVectorXcd(const Eigen::VectorXcd &eigenVector)
{
  std::vector<std::complex<double>> vec(eigenVector.size());
  for (size_t i = 0; i < eigenVector.size(); ++i) { vec[i] = eigenVector[i]; }
  return vec;
}

Eigen::VectorXcd addElementAtBeginning(const Eigen::VectorXcd &originalVector, const std::complex<double> &newElement);

#endif// UTILS
