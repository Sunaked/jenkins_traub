#include <iostream>
#include "JenkinsTraub.hpp"

void Test_0()
{
  double op[3] = { 1.0, 2.0, 3.0 };
  double zeror[3];
  double zeroi[3];
  JenkinsTraub jt;
  int num_of_roots = jt.Solve(op, 2, zeror, zeroi);
  std::cout << "TEST 0 ============================\n";
  std::cout << "Roots found: " << num_of_roots << "\n";
  if(num_of_roots > 0)
  {
    for (size_t i = 0; i < num_of_roots; i++)
    {
      std::cout << "Root [" << i << "]: " << zeror[i] << (zeroi[i] > 0 ? " +": " ") << zeroi[i] << "i;\n";
    }
  }
  std::cout << "===================================\n";
}

void Test_1()
{
  double op[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
  double zeror[10];
  double zeroi[10];
  JenkinsTraub jt;
  int num_of_roots = jt.Solve(op, 9, zeror, zeroi);
  std::cout << "TEST 1 ============================\n";
  std::cout << "Roots found: " << num_of_roots << "\n";
  if(num_of_roots > 0)
  {
    for (size_t i = 0; i < num_of_roots; i++)
    {
      std::cout << "Root [" << i << "]: " << zeror[i] << (zeroi[i] > 0 ? " +": " ") << zeroi[i] << "i;\n";
    }
  }
  std::cout << "===================================\n";
}

int main(int argc, char const *argv[]) 
{
  
  Test_0();
  Test_1();

  return 0;
}
