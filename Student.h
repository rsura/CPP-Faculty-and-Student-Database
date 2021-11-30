#ifndef STUDENT_H
#define STUDENT_H

#include "GenLinkedList.h"
#include "BST.h"
#include <iomanip>

using namespace std;

class Student{
    public:
        // constructors and destructor
        Student();
        Student(unsigned int id1, string name1, string level1, string major1, double gpa1, unsigned int advisorId1);
        ~Student();

        // accessors and mutators
        void setId(unsigned int id1);
        unsigned int getId();
        void setName(string name1);
        string getName();
        void setLevel(string level1);
        string getLevel();
        void setMajor(string major1);
        string getMajor();
        void setGpa(double gpa1);
        double getGpa();
        void setAdvisorId(unsigned int advisorId1); // prompt that they want to change the advisor if already existing advisor ID
        unsigned int getAdvisorId();

        // Overloaded operators
        friend bool operator==(Student& lhs, Student& rhs);
        friend bool operator!=(Student& lhs, Student& rhs);
        friend bool operator>=(Student& lhs, Student& rhs);
        friend bool operator<=(Student& lhs, Student& rhs);
        friend bool operator>(Student& lhs, Student& rhs);
        friend bool operator<(Student& lhs, Student& rhs);
        friend ostream& operator<<(ostream& os, Student& fac);
        friend ostream& operator<<(ostream& os, Student*& fac);

    private:
        unsigned int id;
        string name;
        string level;
        string major;
        double gpa;
        unsigned int advisorId;
};

#endif