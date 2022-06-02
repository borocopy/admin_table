#ifndef __APP_H__
#define __APP_H__
#include <iostream>
#include "Node.h"

using namespace std;

class App: public Node
{
	private:
		int tick;
		
		void process_command();
	public:
		App(Node* parent): Node(parent);
		~App();
		
		void exec_app();
};

#endif
