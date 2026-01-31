#include "ast_direct_declarator.hpp"

/*

outputs {identifier}: to the stream
identifier is declared in the constructor of DirectDeclarator

*/

namespace ast {

void DirectDeclarator::EmitRISC(std::ostream& stream, Context& context) const {
  identifier_->EmitRISC(stream, context);
  stream << ":" << std::endl;
}

void DirectDeclarator::Print(std::ostream& stream) const {
  identifier_->Print(stream);
}

}  // namespace ast
