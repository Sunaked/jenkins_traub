#include "find_polynomial_roots_jenkins_traub.hpp"
#include "polynomial.hpp"

#include "src/framework.h"

#include "src/ttmath/ttmath.h"

#include <iostream>

#ifndef NUMBER
#define NUMBER float
#endif

#ifndef DEGREE
#define DEGREE 30// polynomial degree
#endif

#ifndef N_TESTS
#define N_TESTS 10000// count of tests
#endif
// Generator params. If all N_*_ROOTS are zero, then generator will create only simple roots
#ifndef N_PAIRS_OF_COMPLEX_ROOTS
#define N_PAIRS_OF_COMPLEX_ROOTS 0
#endif
#ifndef N_CLUSTERED_ROOTS
#define N_CLUSTERED_ROOTS 0
#endif
#ifndef N_MULTIPLE_ROOTS
#define N_MULTIPLE_ROOTS DEGREE
#endif
// Used only for clustered roots
#ifndef MAX_DISTANCE_BETWEEN_CLUSTERED
#define MAX_DISTANCE_BETWEEN_CLUSTERED 1e-5
#endif
#ifndef ROOT_SWEEP_LOW
#define ROOT_SWEEP_LOW 5.0
#endif
#ifndef ROOT_SWEEP_HIGH
#define ROOT_SWEEP_HIGH 10.0
#endif
#ifndef TRIES
#define TRIES 80// For how many iterations Laguerre should trying to solve polynomial
#endif

#ifndef EXPONENT
#define EXPONENT 4// Exponent for big NUMBER notation
#endif
#ifndef MANTISSA
#define MANTISSA 32// Mantissa for big NUMBER notation
#endif


template<typename T> inline void printVec(const std::vector<T> &vec)
{
  for (auto &i : vec) std::cout << i << " ";
  std::cout << "\n";
}


constexpr int mantissa = 32;// Mantissa for big number notation
constexpr int exponent = 4;// Exponent for big number notation


using big = ttmath::Big<exponent, mantissa>;

int main()
{


  // Generator stuff
  // int rv,// status of comparing roots
  //   N_roots_found_this_test, N_roots_gt_this_test,// amount of found roots in each test & gt roots
  //   N_true_roots_lost = 0, N_fake_roots_added = 0,// total counters of {lost, fake} roots aover all tests
  //   N_roots_gt_all_tests_ae_worst = 0,
  //   N_roots_found_all_tests_ae_worst =
  //     0,// {ground truth, found} NUMBER of roots of the worst polynomial for absolute error
  //   N_roots_gt_all_tests_re_worst = 0,
  //   N_roots_found_all_tests_re_worst =
  //     0;// {ground truth, found} NUMBER of roots of the worst polynomial for relative error
  //
  // std::vector<NUMBER> roots(DEGREE, 0.0), roots_found_this_test(DEGREE), a(DEGREE + 1, 0.0),// current polynomial
  //   roots_gt_all_tests_ae_worst(DEGREE), roots_found_all_tests_ae_worst(DEGREE),
  //   coefficients_all_tests_ae_worst(
  //     DEGREE + 1),// {gt roots, found roots, coefficients} of the worst polynomial for absolute error
  //   roots_gt_all_tests_re_worst(DEGREE), roots_found_all_tests_re_worst(DEGREE),
  //   coefficients_all_tests_re_worst(
  //     DEGREE + 1);// {gt roots, found roots, coefficients} of the worst polynomial for relative error
  //
  // NUMBER ae_this_test_worst,
  //   ae_all_tests_worst = static_cast<NUMBER>(-1.0L),// absolute error: an impossible value that will be updated for
  //   sure re_this_test_worst, re_all_tests_worst = static_cast<NUMBER>(-1.0L);// relative error: an impossible value
  //   that will be updated for sure
  std::cout << "Hello world\n";
  int l = 5;
  std::vector<double> roots(l, 0.0);
  std::vector<double> a(l + 1, 0.0);
  generate_polynomial<double, exponent, mantissa>(l, 0, 0, 0, 1e-5, -1.0, 1.0, roots, a);

  std::cout << "\nFRAMEWORK ROOTS:\n";
  for (auto &el : roots) { std::cout << "(x-(" << el << "))"; }

  std::cout << "\nFRAMEWORK COEFFS:\n";
  for (auto &el : a) { std::cout << el << ','; }


  // try {
  //   for (int i = 0; i < N_TESTS; ++i) {
  //     roots_found_this_test.clear();
  //     N_roots_gt_this_test = generate_polynomial<NUMBER, EXPONENT, MANTISSA>(DEGREE,
  //       N_PAIRS_OF_COMPLEX_ROOTS,
  //       N_CLUSTERED_ROOTS,
  //       N_MULTIPLE_ROOTS,
  //       MAX_DISTANCE_BETWEEN_CLUSTERED,
  //       ROOT_SWEEP_LOW,
  //       ROOT_SWEEP_HIGH,
  //       roots,
  //       a);
  //     std::cout << "GENERATED POLY & ROOTS:\n";
  //     printVec(a);
  //     printVec(roots);
  //     // Polynomial<NUMBER> pol(a);
  //
  //     std::vector<std::complex<NUMBER>> solved_roots(DEGREE);
  //     std::vector<int> conv(DEGREE);
  //
  //     // pol.setSolver(solver);
  //     // pol.solve(solved_roots, conv, TRIES);
  //
  //     std::cout << "found roots: ";
  //     std::for_each(solved_roots.begin(),
  //       solved_roots.end(),
  //       [&roots_found_this_test](std::complex<NUMBER> x) {// solved_roots = b_roots
  //         std::cout << x.real() << "; ";
  //         roots_found_this_test.push_back(x.real());
  //       });
  //   }
  // } catch (...) {
  //   std::cerr << "catch!\n";
  // }

  return 0;
}
