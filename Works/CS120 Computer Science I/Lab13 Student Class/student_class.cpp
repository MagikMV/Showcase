void showProgramHeader();

#include <iostream>
#include <string>
using namespace std;
//***STUDENT CLASS***
class student
{
    private:
        string name;
        int id;
        char grade;
    public:
        student();
        void print_student();
};

int main()
{
    showProgramHeader();

    int numberOfStudents;
    cout << "How many students do you have?" << endl;
    cin >> numberOfStudents;
    student *student_ptr = new student[numberOfStudents];
    for(int i = 0; i < numberOfStudents; i++)
    {
        student_ptr->print_student();
        student_ptr += 1;
    }
}
//***PROGRAM HEADER***
void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Lab Section 6 \nApril 18, 2019 \nLab Assignment Number 13 \n" << endl;
}
//***STUDENT CONSTRUCTOR***
student::student()
{
    cout << "\nStudent's name? (First name)" << endl;
    cin >> name;
    cout << "Student's id?" << endl;
    cin >> id;
    cout << "Student's grade?" << endl;
    cin >> grade;
    if(grade != 'A' && grade!='B' && grade!='C' && grade!='D' && grade!='F')
    {
        do
        {
        cout << "Student's grade?(A,B,C,D, or F)" << endl;
        cin >> grade;
        }
        while(grade!='A' && grade!='B' && grade!='C' && grade!='D' && grade!='F');
    }
}
//***MEMBER FUNCTION FOR PRINTING STUDENT***
void student::print_student()
{
    cout << "\nStudent name: " << name << endl;
    cout << "Student id: " << id << endl;
    cout << "Student grade: " << grade << endl;
}
