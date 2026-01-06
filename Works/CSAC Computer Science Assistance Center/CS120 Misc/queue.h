/* queue.h
 *
 * Miguel Villanueva
 * January 31, 2022
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iostream>
#include <string>
using namespace std;

enum Condition {success, fail, underflow, overflow};

class Queue
{
    private:
		int end, head;
		int size;
		string *array;
    public:
		Queue(int s)
		{
			head = end = -1;
			size = s;
			array = new string[s];
		}
		bool empty();
		Condition push(string name);
		Condition pop();
		Condition front(string &first);
		void print();
};

#endif
