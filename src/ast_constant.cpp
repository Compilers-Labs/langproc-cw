#include "ast_constant.hpp"

/*

This configures the IntConstant command RISC to be "li a0, value" which stores value in a0
Print does nothing

*/
namespace ast {

void IntConstant::EmitRISC(std::ostream& stream, Context&) const {
  stream << "li a0, " << value_ << std::endl;
}

void IntConstant::Print(std::ostream& stream) const { stream << value_; }

}  // namespace ast
