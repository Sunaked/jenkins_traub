#include "next_step.h"

Eigen::VectorXd next_step(const Eigen::VectorXd &a,
                          const Eigen::VectorXd &H_bar_lambda, double s,
                          double epsilon, bool generate_t = true) {
  Eigen::VectorXd p, h_bar;
  double p_at_s, h_bar_at_s;

  synthetic_division(a, s, p, p_at_s);
  synthetic_division(H_bar_lambda, s, h_bar, h_bar_at_s);

  if (std::abs(p_at_s) < epsilon) {
    throw RootFound();
  }

  if (std::abs(h_bar_at_s) < epsilon) {
    h_bar_at_s += epsilon / 100;
  }

  double t = 0;
  if (generate_t) {
    t = s - p_at_s / h_bar_at_s;
  }

  h_bar.conservativeResize(h_bar.size() + 1);
  h_bar(0) = 0; // insert 0 at the beginning of h_bar

  return p - (p_at_s / h_bar_at_s) * h_bar; // The function now returns only the
                                            // new polynomial, t is not returned
}
