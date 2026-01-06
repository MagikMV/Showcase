/* queue.cpp
 *
 * Miguel Villanueva
 * January 31, 2022
 */

#include <iostream>
#include "queue.h"
using namespace std;

enum season {spring, summer, fall, winter};

int main()
{
    season current = spring;

    if(current != summer)
	cout << "Powerful" << endl;
}
