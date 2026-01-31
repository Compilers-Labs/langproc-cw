#include "ast_identifier.hpp"

/*

Identifier just outputs the identifier

*/

namespace ast {

void Identifier::EmitRISC(std::ostream& stream, Context&) const {
  stream << identifier_;
}
void Identifier::Print(std::ostream& stream) const { stream << identifier_; };

}  // namespace ast
