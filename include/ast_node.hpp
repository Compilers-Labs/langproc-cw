#pragma once

/*

Node, NodePtr and NodeList are defined here
1.
Node is a class with virtual (overridable) functions: constructor, EmitRISC, Print

2.
NodePtr is just defined as a unique ptr, Msg for Yichan: UniquePtr is just a pointer that can only be assgigned to one thing at one time
and it auto deletes when it goes out of scope

3.
NodeList inherits from node and takes in a first node which it pushes into a priv vector
an extra function pushback is in this which will (in the future decleration) add to the vec

*/


#include <iostream>
#include <memory>
#include <vector>

#include "ast_context.hpp"

namespace ast {

class Node {
 public:
  virtual ~Node() {}
  virtual void EmitRISC(std::ostream& stream, Context& context) const = 0;
  virtual void Print(std::ostream& stream) const = 0;
};

// If you don't feel comfortable using std::unique_ptr, you can switch NodePtr
// to be defined as a raw pointer instead here and your project should still
// compile, although you'll need to add destructors to avoid leaking memory (and
// get rid of the now unnecessary std::move-s)
using NodePtr = std::unique_ptr<const Node>;

class NodeList : public Node {
 private:
  std::vector<NodePtr> nodes_;

 public:
  NodeList(NodePtr first_node) { nodes_.push_back(std::move(first_node)); }

  void PushBack(NodePtr item);
  virtual void EmitRISC(std::ostream& stream, Context& context) const override;
  virtual void Print(std::ostream& stream) const override;
};

}  // namespace ast
