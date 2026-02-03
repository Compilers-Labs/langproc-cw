#pragma once
#include "ast_context.hpp"
#include <string>

namespace ast {

class Instruction{
private:
    unsigned line_number;
    std::string line_content;
protected:
    Instruction(unsigned _line_number, std::string _line_content)
        : line_number(_line_number),
        line_content(_line_content)
{}

public:
    virtual ~Instruction(){}

    std::string get_line_content() const;

    unsigned get_line_number() const;

    virtual std::string get_assembly() const;

    virtual void execute(Context &ctxt) const = 0;
};

}
