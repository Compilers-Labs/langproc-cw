#include "ast_function_definition.hpp"

/*

Function definition defines some directives, emits the declarator which is a node pointer to a delcerator node
then the compound_statement which is printed/ Emitted as it is a node pointer to a node list and iteratively sends to ostream.

*/

namespace ast {

void FunctionDefinition::EmitRISC(std::ostream& stream,
                                  Context& context) const {
  // Emit assembler directives.
  // TODO: these are just examples ones, make sure you understand
  // the concept of directives and correct them.
  stream << ".text" << std::endl;
  stream << ".globl f" << std::endl;

  declarator_->EmitRISC(stream, context);

  if (compound_statement_ != nullptr) {
    compound_statement_->EmitRISC(stream, context);
  }
}

void FunctionDefinition::Print(std::ostream& stream) const {
  stream << declaration_specifiers_ << " ";

  declarator_->Print(stream);
  stream << "() {" << std::endl;

  if (compound_statement_ != nullptr) {
    compound_statement_->Print(stream);
  }
  stream << "}" << std::endl;
}
}  // namespace ast
