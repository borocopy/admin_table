#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__
#include <iostream>
#include <vector>

using namespace std;

class UserInterface
{
	private:
		vector<string> split_string(string raw_line);
	public:
		UserInterface();
		~UserInterface();
		void get_initial_state();
		void parse_user_command();
}

#endif
