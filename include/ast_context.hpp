#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace ast {

class Context;

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

    std::string get_line_content() const {
        return line_content;
    }

    unsigned get_line_number() const {
        return line_number;
    }

    virtual std::string get_assembly() const {
        return "";
    }

    virtual void execute(Context &ctxt) const = 0;
};
// An object of class Context is passed between ast nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).


class Context{
private:
    unsigned pc;//program counter
    //CHANGE TO TEMPLATE VARIABLE
    std::unordered_map<std::string,int32_t> register_map; //map of register names to content of registers
    std::vector<std::shared_ptr<Instruction>> instruction_list; // shared pointers to a vector of instructions
    std::unordered_map<std::string, unsigned> label_map; //map of labels to instruction lines
public:
    Context() : pc(0){}

    int32_t get_register(std::string name){

        std::cerr << "getRegister(" << name << ")\n";
        if (!register_map.count(name)){
            throw std::runtime_error("getRegister("+name+") : Register does not exist");
        }
        return register_map[name];
    }

    //Change to templated aswell
    void set_register(std::string name, int32_t value){
        register_map[name] = value;
    }

    void pc_plus_one(){
        pc++;
    }

    void jump(std::string label){

        std::cerr << "jump(" << label << ")\n";
        if (!label_map.count(label)){
            throw std::runtime_error("jump("+label+") : Label does not exist");
        }
        pc = label_map[label];
    }

    void step(){
        if(pc >= instruction_list.size() ){
            throw std::runtime_error("step : program counter out of range");
        }
        assert(instruction_list.at(pc));

        //CHANGE THIS TO LOGGING CLASS WHEN CREATED
        std::cerr << "Exec " << instruction_list[pc]->get_line_number() << ":" << instruction_list[pc]->get_assembly() << ", {";
        for(auto x : register_map){
            std::cerr << " " << x.first << ":" << x.second;
        }
        std::cerr << "}\n";

        instruction_list.at(pc)->execute(*this);

    }

    void add_instruction(const std::string &line);
};
} // namespace ast

