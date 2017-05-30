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
#ifndef AMCPP_EMPLOYEE_HPP
#define AMCPP_EMPLOYEE_HPP

#include <experimental/ranges/utility>
#include <ios>
#include <iosfwd>
#include <string>
#include <string_view>

namespace amcpp {
   namespace ranges = std::experimental::ranges;

   class Employee {
   public:
      Employee() = default;

      Employee(const int id, std::string surname, std::string first_name, const double salary)
         : id_{id},
           surname_{ranges::move(surname)},
           first_name_{ranges::move(first_name)},
           salary_{salary}
      {}

      Employee(const int id, const std::string_view surname, const std::string_view first_name,
         const double salary)
         : id_{id},
           surname_{surname.data()},
           first_name_{first_name.data()},
           salary_{salary}
      {}

      Employee(std::istream&, std::ios_base::openmode = std::ios_base::in);

      int id() const noexcept
      {
         return id_;
      }

      const std::string& surname() const noexcept
      {
         return surname_;
      }

      const std::string& first_name() const noexcept
      {
         return first_name_;
      }

      double salary() const noexcept
      {
         return salary_;
      }
   private:
      int id_;
      std::string surname_;
      std::string first_name_;
      double salary_;

      [[noreturn]] void io_failure(const std::string& member, const std::string& mode = "read")
      {
         throw std::ios_base::failure{"Unable to " + mode + ' ' + member};
      }

      void read_binary(std::istream&);
      void read_text(std::istream&);
   };

   std::ostream& write(std::ostream&, const Employee&);
   std::ostream& operator<<(std::ostream&, const Employee&);
   std::istream& operator>>(std::istream&, Employee&);
} // namespace amcpp

#endif // AMCPP_EMPLOYEE_HPP