#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ast_constant.hpp"
#include "ast_context.hpp"
#include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"
#include "ast_identifier.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp" // dont think this is needed because ast node is included in pretty much all of the above
#include "ast_type_specifier.hpp" //nor this but its fine, these are nice to have to know what we are generally including

ast::NodePtr ParseAST(std::string file_name); //finally we have t
