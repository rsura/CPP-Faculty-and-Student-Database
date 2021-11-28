#ifndef FACULTY_H
#define FACULTY_H

#include "GenLinkedList.h"
#include "BST.h"
using namespace std;

class Faculty{
    public:
        // constructors and destructors
        Faculty();
        Faculty(unsigned int id1, string name1, string level1, string department1);
        ~Faculty();

        // accessors and mutators
        void setId(unsigned int id1);
        unsigned int getId();
        void setName(string name1);
        string getName();
        void setLevel(string level1);
        string getLevel();
        void setDepartment(string department1);
        string getDepartment();
        bool addAdvisee(Student* newStudent);
        bool removeAdvisee(unsigned int studId);

        // Overloaded operators
        friend bool operator==(Faculty& lhs, Faculty& rhs);
        friend bool operator>=(Faculty& lhs, Faculty& rhs);
        friend bool operator<=(Faculty& lhs, Faculty& rhs);
        friend bool operator>(Faculty& lhs, Faculty& rhs);
        friend bool operator<(Faculty& lhs, Faculty& rhs);
        friend ostream& operator<<(ostream& os, Faculty& fac);
        friend ostream& operator<<(ostream& os, Faculty*& fac);


    private:
        unsigned int id;
        string name;
        string level;
        string department;
        GenLinkedList<unsigned int> *advisees;
};

#endif