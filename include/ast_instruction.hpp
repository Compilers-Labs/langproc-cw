#pragma once
#include "ast_context.hpp"
#include <cstdint>
#include <string>
#include <vector>

//ast instruction definiton

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

//Overriding the class functions per ISA instruction
class ConstInstruction : public Instruction {
private:
    std::string rDst;
    int32_t value;
public:
    ConstInstruction(unsigned index, std::string line, std::string dst, int32_t val)
        : Instruction(index, line), rDst(dst), value(val) {}

    std::string get_assembly() const override;


    void execute(Context &ctxt) const override;
};

class InputInstruction : public Instruction {
private:
    std::string rDst;
public:
    InputInstruction(unsigned index, std::string line, std::string dst)
        : Instruction(index, line), rDst(dst) {}

    std::string get_assembly() const override;

    void execute(Context &ctxt) const override;
};

class ParamInstruction : public Instruction {
private:
    std::string rDst;
    unsigned slot;
public:
    static std::vector<int32_t> args;

    ParamInstruction(unsigned index, std::string line, std::string dst, unsigned s)
        : Instruction(index, line), rDst(dst), slot(s) {}

    std::string get_assembly() const override;

    void execute(Context &ctxt) const override;
};

// Initialize the static member
std::vector<int32_t> ParamInstruction::args; // ??

class OutputInstruction : public Instruction {
private:
    std::string rSrc;
public:
    OutputInstruction(unsigned index, std::string line, std::string src)
        : Instruction(index, line), rSrc(src) {}

    void execute(Context &ctxt) const override;
};

class HaltInstruction : public Instruction {
private:
    std::string rSrc;
public:
    HaltInstruction(unsigned index, std::string line, std::string src)
        : Instruction(index, line), rSrc(src) {}

    void execute(Context &ctxt) const override;
};

class AddInstruction : public Instruction {
private:
    std::string rDst, rA, rB;
public:
    AddInstruction(unsigned index, std::string line, std::string dst, std::string a, std::string b)
        : Instruction(index, line), rDst(dst), rA(a), rB(b) {}

    std::string get_assembly() const override;

    void execute(Context &ctxt) const override;
};

class BranchEqualsInstruction : public Instruction {
private:
    std::string label, rA, rB;
public:
    BranchEqualsInstruction(unsigned index, std::string line, std::string a, std::string b, std::string lbl)
        : Instruction(index, line), label(lbl), rA(a), rB(b) {}

    void execute(Context &ctxt) const override;
};

}; // namespace ast
