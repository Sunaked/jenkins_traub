#ifndef UTILS_HPP
#define UTILS_HPP

#include <iomanip>
#include <iostream>
#include <vector>

template<typename T> void print_op(const std::vector<T> &op)
{
  std::cout << "Polynomial: ";
  std::size_t deg = op.size();
  for (size_t i = 0; i < op.size(); i++) { std::cout << std::setw(1) << op[i] << "x^" << deg - i - 1 << " + "; }
  std::cout << "\n";
}


#endif// UTILS_HPP
