#include <iostream>
using namespace std;
void func1(char *q);
int main(){
    char array[] = "abcdef";
    char *p; // pointer p is created
    cout << "initial array: " << array << endl;
    p = array; // p points at the entire array but only from the beginning element, which is a
    *p = 'x'; // the value within the address of what p is pointing at is now set to x, so a becomes x
    p = &array[1]; // p is now pointing to the second element in the array which is b
    p++; // p is now pointing to the third element which is c;
    *p = 'x'; // third element is now changed to x
    p = &array[3]; // p now points to the fourth element in the array, which is d
    p[2] = 'x'; // two elements on from the fourth element where p points, is now changed to x, which is the last element f
    p--; // p now points to the third element from the fourth, which is c;
    func1(p); // function call, fourth element, d, is changed to x
    func1(array); // on from the beginning of array, incremented one, which is the second element b, changed to x
    func1(&array[3]); // on from the address of the fourth element, incremented one, which is the fifth element e, changed to x
    cout << "final array: " << array << endl;
}
void func1(char *q){ // pointer q as an argument with data type char
    q++; // changes where q points to
    *q = 'x'; // the value within the address of what p is pointing at is now set to x
}
