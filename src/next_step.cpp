#include "next_step.h"

Eigen::VectorXcd addElementAtBeginning(const Eigen::VectorXcd &originalVector, const std::complex<double> &newElement);

Eigen::VectorXcd
  next_step(Eigen::VectorXcd a, Eigen::VectorXcd H_bar_lambda, std::complex<double> s, double epsilon, bool generate_t)
{
  // Eigen::VectorXcd p, h_bar;
  // double p_at_s, h_bar_at_s;

  auto p_ = synthetic_division(a, s);
  auto h_bar_ = synthetic_division(H_bar_lambda, s);

  if (std::abs(p_.second) < epsilon) { throw std::logic_error("too small"); }

  if (std::abs(h_bar_.second) < epsilon) { h_bar_.second += epsilon / 100; }

  std::complex<double> t = 0;
  if (generate_t) { t = s - p_.second / h_bar_.second; }

  h_bar_.first.conservativeResize(h_bar_.first.size() + 1);
  addElementAtBeginning(h_bar_.first, 0);// insert 0 at the beginning of h_bar

  return p_.first - (p_.second / h_bar_.second) * h_bar_.first;// The function now returns only the
                                                               // new polynomial, t is not returned
}
