#ifndef NEXT_STEP
#define NEXT_STEP

#include <eigen3/Eigen/Dense>
#include "synthetic_division.h"
#include <stdexcept>

Eigen::VectorXd next_step(const Eigen::VectorXd &a,
                          const Eigen::VectorXd &H_bar_lambda, double s,
                          double epsilon, bool generate_t = true);

#endif // NEXT_STEP
