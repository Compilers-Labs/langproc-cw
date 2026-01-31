#pragma once

/*

We include the ast node and type specifier

Then we declare a new class FunctionDefinition which inherits the ats node.
This takes in a TypeSpecifier, NodePtr declarator and NodePtr Compound_statement

This is to be determined what they do but I would assume that the node pointers point to:
Declarator -> paramaters?
compound_statement -> next ats node for inside the function?

The TypeSpecifier is probably the return type of the function

*/


#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

class FunctionDefinition : public Node {
 private:
  const TypeSpecifier declaration_specifiers_;
  NodePtr declarator_;
  NodePtr compound_statement_;

 public:
  FunctionDefinition(TypeSpecifier declaration_specifiers, NodePtr declarator,
                     NodePtr compound_statement)
      : declaration_specifiers_(declaration_specifiers),
        declarator_(std::move(declarator)),
        compound_statement_(std::move(compound_statement)) {};

  void EmitRISC(std::ostream& stream, Context& context) const override;
  void Print(std::ostream& stream) const override;
};

}  // namespace ast
