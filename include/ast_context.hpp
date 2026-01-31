#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace ast {

class Instruction;
// An object of class Context is passed between ast nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).


class Context
{
private:
    unsigned pc;//program counter
    //CHANGE TO TEMPLATE VARIABLE
    std::unordered_map<std::string,int32_t> register_map; //map of register names to content of registers
    std::vector<std::shared_ptr<Instruction>> instruction_list; // shared pointers to a vector of instructions
    std::unordered_map<std::string, unsigned> label_map; //map of labels to instruction lines
public:
    Context() : pc(0){}

    int32_t getRegister(std::string name){

        std::cerr << "getRegister(" << name << ")\n";
        if (!register_map.count(name)){
            throw std::runtime_error("getRegister("+name+") : Register does not exist");
        }
        return register_map[name];
    }


    void setRegister(std::string name, int32_t value);

    void PCPlusOne();

    void jump(std::string label);

    void step();

    void add_instruction(const std::string &line);
};
} // namespace ast

