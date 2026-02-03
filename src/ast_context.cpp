#include "ast_context.hpp"
#include "ast_instruction.hpp"
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace ast {

//Change to templated aswell
void Context::set_register(std::string name, int32_t value){
    register_map[name] = value;
}

void Context::pc_plus_one(){
    pc++;
}

void Context::jump(std::string label){
    std::cerr << "jump(" << label << ")\n";
    if (!label_map.count(label)){
        throw std::runtime_error("jump("+label+") : Label does not exist");
    }
    pc = label_map[label];
}

void Context::step(){
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

//add_instruction function parses input line and fills out arguments
// and push_back to instruction_list accordingly
void Context::add_instruction(const std::string &line) {
    char arg1[65]={0}, arg2[65]={0}, arg3[65]={0};
    int iarg;

    // Use instruction_list.size() instead of instructions.size()
    if(1==sscanf(line.c_str(), ":%64[_a-zA-Z0-9]", arg1)){
        if(label_map.count(arg1)){
            throw std::runtime_error("Duplicate label: " + std::string(arg1));
        }
        label_map[arg1] = instruction_list.size();
    } else if(2==sscanf(line.c_str(), "const %64s %d", arg1, &iarg)) {
        instruction_list.push_back(std::make_shared<ConstInstruction>(instruction_list.size(), line, arg1, iarg));
    } else if(1==sscanf(line.c_str(), "input %64s", arg1)) {
        instruction_list.push_back(std::make_shared<InputInstruction>(instruction_list.size(), line, arg1));
    } else if(2==sscanf(line.c_str(), "param %64s %d", arg1, &iarg)) {
        instruction_list.push_back(std::make_shared<ParamInstruction>(instruction_list.size(), line, arg1, iarg));
    } else if(1==sscanf(line.c_str(), "output %64s", arg1)) {
        instruction_list.push_back(std::make_shared<OutputInstruction>(instruction_list.size(), line, arg1));
    } else if(3==sscanf(line.c_str(), "add %64s %64s %64s", arg1, arg2, arg3)) {
        instruction_list.push_back(std::make_shared<AddInstruction>(instruction_list.size(), line, arg1, arg2, arg3));
    } else if(3==sscanf(line.c_str(), "beq %64s %64s %64s", arg1, arg2, arg3)) {
        instruction_list.push_back(std::make_shared<BranchEqualsInstruction>(instruction_list.size(), line, arg1, arg2, arg3));
    } else if(1==sscanf(line.c_str(), "halt %64s", arg1)) {
        instruction_list.push_back(std::make_shared<HaltInstruction>(instruction_list.size(), line, arg1));
    } else {
        throw std::runtime_error("Couldn't parse line: " + line);
    }
}

} // namespace ast
