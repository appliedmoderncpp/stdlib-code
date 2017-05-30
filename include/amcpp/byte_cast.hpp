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
#ifndef AMCPP_BYTE_CAST_HPP
#define AMCPP_BYTE_CAST_HPP

namespace amcpp {
   // `byte_cast` originally `as_bytes`, taken from
   // 'Programming -- Principles and Practice Using C++ (Second Edition)'
   // by Bjarne Stroustrup
   template <typename T>
   char* byte_cast(T& t) noexcept
   {
      void* p = &t;
      return static_cast<char*>(p);
   }

   template <typename T>
   const char* byte_cast(const T& t) noexcept
   {
      const void* p = &t;
      return static_cast<const char*>(p);
   }
} // namespace amcpp

#endif // AMCPP_BYTE_CAST_HPP