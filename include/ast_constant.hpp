#pragma once

/*

This is an ast node in namespace ast, each node has a private value and the constructor takes in that value
The class is an IntConstant
It has 2 functions:
1. EmitRISC which takes in an output stream to output to and context of type Context -> ?
2. Print which takes in a stream

they are both void return types and marked as const override so they are written somewhere else.

Context is an undefined class at the moment but each ast node essentially has context to do with stuff like function scope and variables,
we can use this information in the future after we build the context class and add stuff to it.


*/

#include "ast_node.hpp"

namespace ast {

class IntConstant : public Node {
 private:
  int value_;

 public:
  IntConstant(int value) : value_(value) {}

  void EmitRISC(std::ostream& stream, Context& context) const override;
  void Print(std::ostream& stream) const override;
};

}  // namespace ast
