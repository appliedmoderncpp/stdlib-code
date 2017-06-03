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
#include <fstream>
#include <iosfwd>
#include <string>

namespace amcpp::io {
   std::ostream& write(std::ostream& o, const std::string& s)
   {
      o.write(byte_cast(s.size()), sizeof(s.size()));
      o.write(s.data(), s.size());
      return o;
   }

   std::istream& read(std::istream& in, std::string& s)
   {
      if (auto size = decltype(s.size()){}; in.read(byte_cast(size), sizeof(size))) {
         s = std::string(size, '\0');
         in.read(s.data(), s.size());
      }

      return in;
   }
   
   namespace fs = std::experimental::filesystem;

   template <typename T>
   T from_file(const fs::path& path, std::ios_base::openmode open = std::ios_base::in)
   {
      if (auto in = std::ifstream{path, open}) {
         return T{in, open};
      }
      else {
         throw std::ios_base::failure{"Could not read from file " + path.string() + '"'};
      }
   }

   template <typename T>
   void to_file(const T& t, const fs::path& path, std::ios_base::openmode open = std::ios_base::out)
   {
      if (auto o = std::ofstream{path, open}) {
         if (open & std::ios_base::binary)
            write(o, t);
         else
            o << t;
      }
      else {
         throw std::ios_base::failure{"Could not write to file " + path.string() + '"'};
      }
   }
} // namespace amcpp::io

#endif // AMCPP_IO_HPP