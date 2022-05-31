#ifndef __TABLE_H__
#define __TABLE_H__

using namespace std;

class Table
{
	private:
		int capacity;
		int occupied;
	public:
		Table(int capacity);

		int get_capacity();
		bool is_occupied();


}

#endif
