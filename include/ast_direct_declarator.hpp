#pragma once

/*

DirectDeclarator inherits from our ast node class, it takes in a NodePtr and uses std::move to move (a unique pointer?) into its own private version...

*/


#include "ast_node.hpp"

namespace ast {

class DirectDeclarator : public Node {
 private:
  NodePtr identifier_;

 public:
  DirectDeclarator(NodePtr identifier) : identifier_(std::move(identifier)) {};

  void EmitRISC(std::ostream& stream, Context& context) const override;
  void Print(std::ostream& stream) const override;
};

}  // namespace ast
