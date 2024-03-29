/**
 * Header File: Faculty.h
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 6
 */

#ifndef FACULTY_H // header guards
#define FACULTY_H

#include "GenLinkedList.h"
#include "bst.h"
#include "FileProcessor.h"
#include "Student.h"
#include <iomanip>
using namespace std;

class Faculty{
    public:
        // constructors and destructor
        Faculty();
        Faculty(unsigned int id1, string name1 = "", string level1 = "", string department1 = "");
        Faculty(string fileLine);
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

        void addAdvisee(unsigned int studId);
        bool removeAdvisee(unsigned int studId);
        string getAdviseeIds();
        GenLinkedList<unsigned int> getAllAdvisees();

        // Overloaded operators
        friend bool operator==(Faculty& lhs, Faculty& rhs);
        friend bool operator!=(Faculty& lhs, Faculty& rhs);
        friend bool operator>=(Faculty& lhs, Faculty& rhs);
        friend bool operator<=(Faculty& lhs, Faculty& rhs);
        friend bool operator>(Faculty& lhs, Faculty& rhs);
        friend bool operator<(Faculty& lhs, Faculty& rhs);
        friend ostream& operator<<(ostream& os, Faculty& fac);
        friend ostream& operator<<(ostream& os, Faculty*& fac);
        friend ostream& operator>>(Faculty& fac, ostream& os);
        friend ostream& operator>>(Faculty*& fac, ostream& os);

    private:
        unsigned int id;
        string name;
        string level;
        string department;
        GenLinkedList<unsigned int> advisees;
};

#endif