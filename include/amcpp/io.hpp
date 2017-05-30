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
#ifndef AMCPP_IO_HPP
#define AMCPP_IO_HPP

#include <experimental/filesystem>
#include <experimental/ranges/concepts>
#include <iosfwd>

namespace amcpp::io {
   std::ostream& write(std::ostream&, const std::string&);
   std::istream& read(std::istream&, std::string&);
   
   namespace ranges = std::experimental::ranges;
   namespace fs = std::experimental::filesystem;

   template <typename T>
   requires
      ranges::Constructible<T, std::istream&, std::ios_base::openmode>()
   T from_file(const fs::path&, std::ios_base::openmode = std::ios_base::in);

   template <typename T>
   requires
      requires(T t, std::ostream& o) {{write(o, t)} -> std::ostream&;}
         or
      requires(T t, std::ostream& o) {{o << e} -> std::ostream&;}
   void to_file(const T&, fs::path&, std::ios_base::openmode = std::ios_base::out);
} // namespace amcpp::io

#endif // AMCPP_IO_HPP