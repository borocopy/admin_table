#include "../includes/Base.h"

struct Base::SignalStruct {
  Signal signal_fn;
  Handler handler_fn;
  Base* target;

  SignalStruct(Signal signal_fn, Handler handler_fn, Base* target)
      : signal_fn(signal_fn), handler_fn(handler_fn), target(target) {}
};

Base::Base(Base* new_parent) {
  parent = new_parent;

  if (parent != nullptr) {
    this->parent->add_child(this);
  }
}

Base::~Base() {
  if (parent != nullptr) parent->remove_child(this);

  for (Base* child : children) {
    delete child;
  }
}

Base* Base::get_parent() { return this->parent; }

std::vector<Base*> Base::get_children() { return this->children; }

void Base::set_parent(Base* new_parent) {
  if (this->parent != nullptr) {
    this->parent->remove_child(this);
  }

  this->parent = new_parent;
  this->parent->add_child(this);
}

void Base::add_child(Base* child) { this->children.push_back(child); }

void Base::remove_child(Base* child) {
  for (int i = 0; i < children.size(); i++) {
    if (children[i] == child) {
      children.erase(children.begin() + i);
      return;
    }
  }
}

void Base::add_connection(Signal signal_fn, Handler handler_fn, Base* target) {
  struct SignalStruct* connection =
      new SignalStruct(signal_fn, handler_fn, target);
  connections.push_back(connection);
}

void Base::emit(Base::Signal signal_fn, Base::Command cid, std::string payload) {
  (this->*signal_fn)(cid, payload);

  for (Base::SignalStruct* current : connections) {
    Base* target = current->target;
    if (current->signal_fn == signal_fn) {
      Base::Handler handler_fn = current->handler_fn;
      (target->*handler_fn)(cid, payload);
    }
  }
}
