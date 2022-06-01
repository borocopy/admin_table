#ifndef __ADMIN_H__
#define __ADMIN_H__
#include <vector>
#include <queue>
#include "Table.h"
#include "Group.h"

using namespace std;

class Admin
{
	private:
		vector<Table*>	tables;
		queue<Group*>		live_queue;
		vector<Group*>	reservations;

		void enqueue_group(Group* group);
		void dequeue_group();
		void add_reservation(Group* group);
	public:
		Admin(vector<int> tables_desc);
		~Admin();

		void assign_table(Group* group);
}

#endif
