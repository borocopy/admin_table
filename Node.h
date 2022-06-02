#ifndef NODE_H_
#define NODE_H_
#include <string>
#include <vector>

class Node;
typedef void (Node::*Handler)(std::string);
typedef void (Node::*Signal)(std::string&);
#define SIG_M(signal_fn) (Signal)(&signal_fn)
#define HDR_M(handler_fn) (Handler)(&handler_fn)

class Node {
 private:
  Node* parent;
  std::vector<Node*> children;

  enum CommandType {
    RESERVE,
  };
  struct Command;
  struct SignalStruct;
  std::vector<SignalStruct*> connections;

  void add_child(Node* child);
  void remove_child(Node* child);

 public:
  explicit Node(Node* parent);
  ~Node();

  Node* get_parent();
  std::vector<Node*> get_children();

  void set_parent(Node* new_parent);

  virtual Signal get_signal_emitter();
  virtual Handler get_signal_handler();

  void emit(Signal signal_fn, std::string& payload);
  void add_connection(Signal signal_fn, Handler handler_fn, Node* target);
  void remove_connection(Signal signal_fn, Handler handler_fn, Node* target);
};

#endif  // NODE_H_
