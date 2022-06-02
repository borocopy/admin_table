#include "Node.h"

struct Node::SignalStruct
{
	Signal signal_fn;
	Handler handler_fn;
	Node* target;

	SignalStruct(Signal signal_fn, Handler handler_fn, Node* target):
		signal_fn(signal_fn), handler_fn(handler_fn), target(target) {};
};

Node::Node(Node* new_parent)
{
	parent = new_parent;
	
	if (parent != nullptr)
	{
		this->parent->add_child(this);
	}
}

Node::~Node()
{
	if (parent != nullptr)
		parent->remove_child(this);

	for (Node* child: children)
	{
		delete child;
	}
}

Node* Node::get_parent()
{
	return this->parent;
}

vector<Node*> Node::get_children()
{
	return this->children;
}

void Node::set_parent(Node* new_parent)
{
	if (this->parent != nullptr)
	{
		this->parent->remove_child(this);
	}

	this->parent = new_parent;
	this->parent->add_child(this);
}

void Node::add_child(Node* child)
{
	this->children.push_back(child);
}

void Node::remove_child(Node* child)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] == child)
		{
			children.erase(children.begin() + i);
			return;
		}
	}
}
