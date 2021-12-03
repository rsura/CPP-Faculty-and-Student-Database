/**
 * Header File: Student.h
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 6
 */

#ifndef STUDENT_H // header guards
#define STUDENT_H

#include "GenLinkedList.h"
#include "bst.h"
#include "FileProcessor.h"
#include <iomanip>

using namespace std;

class Student{
    public:
        // constructors and destructor
        Student();
        Student(unsigned int id1, string name1 = "", string level1 = "", string major1 = "", double gpa1 = 0, unsigned int advisorId1 = 0);
        Student(string fileLine);
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
        void setAdvisorId(unsigned int advisorId1);
        unsigned int getAdvisorId();

        // Overloaded operators
        friend bool operator==(Student& lhs, Student& rhs);
        friend bool operator!=(Student& lhs, Student& rhs);
        friend bool operator>=(Student& lhs, Student& rhs);
        friend bool operator<=(Student& lhs, Student& rhs);
        friend bool operator>(Student& lhs, Student& rhs);
        friend bool operator<(Student& lhs, Student& rhs);
        friend ostream& operator<<(ostream& os, Student& stud);
        friend ostream& operator<<(ostream& os, Student*& stud);
        friend ostream& operator>>(Student& stud, ostream& os);
        friend ostream& operator>>(Student*& stud, ostream& os);

    private:
        unsigned int id;
        string name;
        string level;
        string major;
        double gpa;
        unsigned int advisorId;
};

#endif