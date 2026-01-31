#pragma once
#include <unordered_map>

namespace ast {
// An object of class Context is passed between ast nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).
class Context
{
private:
    unsigned pc;//program counter
    //map of register names to content of registers (only int in this case)
    // shared pointers to a vector of instructions
    //map of labels to instruction lines
public:
    Context()
        : pc(0)
    {}

    int32_t getRegister(std::string name);


    void setRegister(std::string name, int32_t value);

    void PCPlusOne();

    void jump(std::string label);

    void step();

    void add_instruction(const std::string &line);
};
} // namespace ast

