#include "utils.h"


Eigen::VectorXcd addElementAtBeginning(const Eigen::VectorXcd &originalVector, const std::complex<double> &newElement)
{
  Eigen::VectorXcd extendedVector(originalVector.size() + 1);
  extendedVector[0] = newElement;
  extendedVector.tail(originalVector.size()) = originalVector;
  return extendedVector;
}
