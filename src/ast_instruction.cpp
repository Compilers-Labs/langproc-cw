#include "ast_instruction.hpp"

namespace ast {

//instruction impelmenetation methods modified from lab 3
std::string Instruction::get_line_content() const {
    return line_content;
}

unsigned Instruction::get_line_number() const {
    return line_number;
}

std::string Instruction::get_assembly() const {
    return "";
}

//context implementation methods modified from lab 3
int32_t Context::get_register(std::string name) {
    std::cerr << "getRegister(" << name << ")\n";
    if (!register_map.count(name)){
        throw std::runtime_error("getRegister("+name+") : Register does not exist");
    }
    return register_map[name];
}

//Overriding the class functions per ISA instruction
class ConstInstruction : public Instruction {
private:
    std::string rDst;
    int32_t value;
public:
    ConstInstruction(unsigned index, std::string line, std::string dst, int32_t val)
        : Instruction(index, line), rDst(dst), value(val) {}

    std::string get_assembly() const override
    { return "const " + rDst + " " + std::to_string(value); }

    void execute(Context &ctxt) const override {
        ctxt.set_register(rDst, value);
        ctxt.pc_plus_one();
    }
};

class InputInstruction : public Instruction {
private:
    std::string rDst;
public:
    InputInstruction(unsigned index, std::string line, std::string dst)
        : Instruction(index, line), rDst(dst) {}

    std::string get_assembly() const override { return "input " + rDst; }

    void execute(Context &ctxt) const override {
        int32_t value;
        if (!(std::cin >> value)) throw std::runtime_error("Invalid input");
        ctxt.set_register(rDst, value);
        ctxt.pc_plus_one();
    }
};

class ParamInstruction : public Instruction {
private:
    std::string rDst;
    unsigned slot;
public:
    static std::vector<int32_t> args;

    ParamInstruction(unsigned index, std::string line, std::string dst, unsigned s)
        : Instruction(index, line), rDst(dst), slot(s) {}

    std::string get_assembly() const override { return "param " + rDst + " " + std::to_string(slot); }

    void execute(Context &ctxt) const override {
        int32_t value = args.at(slot);
        ctxt.set_register(rDst, value);
        ctxt.pc_plus_one();
    }
};

// Initialize the static member
std::vector<int32_t> ParamInstruction::args;

class OutputInstruction : public Instruction {
private:
    std::string rSrc;
public:
    OutputInstruction(unsigned index, std::string line, std::string src)
        : Instruction(index, line), rSrc(src) {}

    void execute(Context &ctxt) const override {
        std::cout << ctxt.get_register(rSrc) << std::endl;
        ctxt.pc_plus_one();
    }
};

class HaltInstruction : public Instruction {
private:
    std::string rSrc;
public:
    HaltInstruction(unsigned index, std::string line, std::string src)
        : Instruction(index, line), rSrc(src) {}

    void execute(Context &ctxt) const override {
        exit(ctxt.get_register(rSrc));
    }
};

class AddInstruction : public Instruction {
private:
    std::string rDst, rA, rB;
public:
    AddInstruction(unsigned index, std::string line, std::string dst, std::string a, std::string b)
        : Instruction(index, line), rDst(dst), rA(a), rB(b) {}

    std::string get_assembly() const override { return "add " + rDst + " " + rA + " " + rB; }

    void execute(Context &ctxt) const override {
        int32_t val = ctxt.get_register(rA) + ctxt.get_register(rB);
        ctxt.set_register(rDst, val);
        ctxt.pc_plus_one();
    }
};

class BranchEqualsInstruction : public Instruction {
private:
    std::string label, rA, rB;
public:
    BranchEqualsInstruction(unsigned index, std::string line, std::string a, std::string b, std::string lbl)
        : Instruction(index, line), label(lbl), rA(a), rB(b) {}

    void execute(Context &ctxt) const override {
        if(ctxt.get_register(rA) == ctxt.get_register(rB)){
            ctxt.jump(label);
        } else {
            ctxt.pc_plus_one();
        }
    }
};

