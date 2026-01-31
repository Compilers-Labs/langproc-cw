#pragma once

/*

This is an ast node in namespace ast, each node has a private value and the constructor takes in that value
It has 2 functions:
1. EmitRISC which takes in an output stream to output to and context of type Context -> ?
2. Print which takes in a stream

they are both void return types and marked as const override so they are written somewhere else.

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
