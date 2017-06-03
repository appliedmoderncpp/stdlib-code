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

#include "byte_cast.hpp"
#include "io.hpp"
#include <iomanip>
#include <iostream>
#include <ios>
#include <iosfwd>
#include <string>
#include <string_view>

namespace amcpp {

   class Employee {
   public:
      Employee() = default;

      Employee(const int id, std::string surname, std::string first_name, const double salary)
         : id_{id},
           surname_{std::move(surname)},
           first_name_{std::move(first_name)},
           salary_{salary}
      {}

      Employee(std::istream& in, std::ios_base::openmode open = std::ios_base::in)
      {
         if (auto s = std::istream::sentry{in}) {
            if (open & std::ios_base::binary)
               read_binary(in);
            else
               read_text(in);
         }
         else {
            throw std::ios_base::failure{"Unable to reset istream object"};
         }
      }

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

      void read_binary(std::istream& in)
      {
         if (!in.read(byte_cast(id_), sizeof(id_)))
            io_failure("id");
         if (!io::read(in, surname_))
            io_failure("surname");
         if (!io::read(in, first_name_))
            io_failure("first name");
         if (!in.read(byte_cast(salary_), sizeof(salary_)))
            io_failure("salary");
      }

      void read_text(std::istream& in)
      {
         if (auto c = '0'; !(in.get(c) && c == '{'))
            io_failure("{");
         if (!(in >> id_))
            io_failure("id");
         if (auto c = '0'; !(in.get(c) && c == ','))
            io_failure(",");
         if (!getline(in, surname_, ','))
            io_failure("surname");
         if (!getline(in, first_name_, ','))
            io_failure("first name");
         if (!(in >> salary_)) {
            std::cerr << surname_ << ' ' << first_name_ << '\n';
            io_failure("salary");
         }
         if (auto c = '0'; !(in.get(c) && c == '}'))
            io_failure("}");
      }
   };

   std::ostream& write(std::ostream& o, const Employee& e)
   {
      if (auto s = std::ostream::sentry{o}) {
         o.write(byte_cast(e.id()), sizeof(e.id()));
         io::write(o, e.surname());
         io::write(o, e.first_name());
         o.write(byte_cast(e.salary()), sizeof(e.salary()));
      }

      return o;
   }

   std::ostream& operator<<(std::ostream& o, const Employee& e)
   {
      using namespace std;
      if (auto s = ostream::sentry{o}) {
         auto f = o.flags();
         auto p = o.precision();
         o << '{' << e.id() << ',' << e.surname() << ',' << e.first_name() << ','
            << std::fixed << std::setprecision(2) << e.salary() << std::setprecision(p);
         o.flags(f);
         o << '}';
      }

      return o;
   }

   std::istream& operator>>(std::istream& in, Employee& e)
   {
      e = {in};
      return in;
   }
} // namespace amcpp

#endif // AMCPP_EMPLOYEE_HPP