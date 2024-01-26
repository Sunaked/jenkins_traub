#include "JenkinsTraub.cpp"
#include "JenkinsTraub.hpp"
#include "include/framework.h"
#include <algorithm>
#include <iomanip>
#include <iostream>


#include "utils.hpp"

/*

TEST 0 ============================
Roots found: 2
Root [0]: -1 +1.41421i;
Root [1]: -1 -1.41421i;
===================================
TEST 1 ============================
Roots found: 9
Root [0]: 0.921738 +0.796364i;
Root [1]: 0.921738 -0.796364i;
Root [2]: -0.465689 +1.2295i;
Root [3]: -0.465689 -1.2295i;
Root [4]: -1.33859 0i;
Root [5]: 0.310291 +1.24228i;
Root [6]: 0.310291 -1.24228i;
Root [7]: -1.09704 +0.756988i;
Root [8]: -1.09704 -0.756988i;
===================================

*/

template<typename T> void print_op(const T &op);

void Test_0()
{
  double op[3] = { 1.0, 2.0, 3.0 };
  double zeror[3];
  double zeroi[3];
  int num_of_roots = JenkinsTraub<double>::Solve(op, 2, zeror, zeroi);
  std::cout << "TEST 0 ============================\n";
  std::cout << "Roots found: " << num_of_roots << "\n";
  if (num_of_roots > 0) {
    for (size_t i = 0; i < num_of_roots; i++) {
      std::cout << "Root [" << i << "]: " << zeror[i] << (zeroi[i] > 0 ? " +" : " ") << zeroi[i] << "i;\n";
    }
  }
  std::cout << "===================================\n";
}

void Test_1()
{
  double op[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
  double zeror[10];
  double zeroi[10];
  int num_of_roots = JenkinsTraub<double>::Solve(op, 9, zeror, zeroi);
  std::cout << "TEST 1 ============================\n";
  std::cout << "Roots found: " << num_of_roots << "\n";
  if (num_of_roots > 0) {
    for (size_t i = 0; i < num_of_roots; i++) {
      std::cout << "Root [" << i << "]: " << zeror[i] << (zeroi[i] > 0 ? " +" : " ") << zeroi[i] << "i;\n";
    }
  }
  std::cout << "===================================\n";
}


void Test_0v()
{
  std::vector<double> op = { 1.0, 2.0, 3.0 };
  std::vector<double> zeror, zeroi;
  int num_of_roots = JenkinsTraub<double>::Solve(op, op.size(), zeror, zeroi);
  std::cout << "TEST 0v ============================\n";
  print_op(op);
  std::cout << "Roots found: " << num_of_roots << "\n";
  if (num_of_roots > 0) {
    for (size_t i = 0; i < num_of_roots; i++) {
      std::cout << "Root [" << i << "]: " << zeror[i] << (zeroi[i] > 0 ? " +" : " ") << zeroi[i] << "i;\n";
    }
  }
  std::cout << "===================================\n";
}

void Test_1v()
{
  std::vector<double> op = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
  std::vector<double> zeror, zeroi;
  int num_of_roots = JenkinsTraub<double>::Solve(op, op.size(), zeror, zeroi);
  std::cout << "TEST 1v ============================\n";
  print_op(op);
  std::cout << "Roots found: " << num_of_roots << "\n";
  if (num_of_roots > 0) {
    for (size_t i = 0; i < num_of_roots; i++) {
      std::cout << "Root [" << i << "]: " << zeror[i] << (zeroi[i] > 0 ? " +" : " ") << zeroi[i] << "i;\n";
    }
  }
  std::cout << "===================================\n";
}

void Test_2v()
{
  std::vector<double> op = { 5.576312106019016,
    18.62488243410351,
    -105.89974320540716,
    -562.5089223272787,
    -692.3579951742573,
    1909.2968243041091,
    11474.831044766257,
    25844.743360023815,
    20409.84088622263,
    -28342.548095425875,
    -52412.8655144021 };
  std::vector<double> zeror, zeroi;
  int num_of_roots = JenkinsTraub<double>::Solve(op, op.size(), zeror, zeroi);
  std::cout << "TEST 1v ============================\n";
  print_op(op);
  std::cout << "Roots found: " << num_of_roots << "\n";
  if (num_of_roots > 0) {
    for (size_t i = 0; i < num_of_roots; i++) {
      std::cout << "Root [" << i << "]: " << zeror[i] << (zeroi[i] > 0 ? " +" : " ") << zeroi[i] << "i;\n";
    }
  }
  std::cout << "===================================\n";
}

int main(int argc, char const *argv[])
{

  Test_0v();
  Test_1v();
  Test_2v();

  return 0;
}
