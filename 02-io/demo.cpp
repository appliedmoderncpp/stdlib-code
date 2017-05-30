// Applied Modern C++: Exploring the Standard Library
//
// A course that introduces the C++ Standard Library
//
// Copyright Christopher Di Bella 2017
//
// All rights reserved. Please do not publically reproduce this code.
//
// Project home: https://github.com/applied-modern-cpp/stdlib-code.git
//
#include "amcpp/employee.hpp"
#include <gsl/gsl>
#include <iostream>
#include <string>

constexpr double operator""_aud(const long double d) noexcept
{
   return gsl::narrow_cast<double>(d);
}

int main()
{
   std::cout << Employee{} << '\n';

   using namespace std::string_literals;
   std::cout << Employee{1, "Di Bella", "Christopher", 12345.67_aud} << '\n';

   //std::cout << Employee{std::cin} << '\n';
   //to_file<Employee>(from_file<Employee>("employee"), "employee_binary", std::ios_base::binary);
   //std::cout << from_file<Employee>("employee_binary", std::ios_base::binary) << '\n';
}