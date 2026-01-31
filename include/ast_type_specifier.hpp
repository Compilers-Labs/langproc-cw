#pragma once

/*

We have an enum here TypeSpecifier which for now only has INT

Then we have a templated operator function of type LogStream for the operator <<
this takes a LogStream by ref and a TypeSpecifier

Inside is a lambda function which takes in this type specifier
if the type specifier is of type int then it returns the string "int", otherwise an error is thrown

then the function returns logstream << the lamda function.

so e.g if i did:

TypeSpecifier t = TypeSpecifier INT
std::cout << t

this would output int to the console.

*/


#include <stdexcept>
#include <string_view>

namespace ast {

enum class TypeSpecifier { INT };

template <typename LogStream>
LogStream& operator<<(LogStream& ls, const TypeSpecifier& type) {
  const auto TypeToString = [&type] {
    switch (type) {
      case TypeSpecifier::INT:
        return "int";
    }
    throw std::runtime_error("Unexpected type specifier");
  };
  return ls << TypeToString();
}

}  // namespace ast
