/**
 * Header File: Simulation.h
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 6
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "Faculty.h"
#include "Student.h"
#include "Rollback.h"

using namespace std;

class Simulation{
    public:
        Simulation();
        ~Simulation();
        void run();

    private:
        // each of the options:
        void printAllStudents();
        void printAllFaculty();
        void printStudent();
        void printFaculty();
        void printStudAdvisor();
        void printFacultyAdvisees();
        bool addNewStudent();
        bool deleteStudent();
        bool addNewFaculty();
        bool deleteFaculty();
        bool changeStudAdvisor();
        bool removeFacultyAdvisee();
        bool rollbackLastChange();
        void saveAndQuit();

        void removeCommas(string& s); // helper method

        // BSTs of students and faculty
        BST<Student> *masterStudent;
        BST<Faculty> *masterFaculty;

        // file names of the student file and faculty file
        string studentFile;
        string facultyFile;
};

#endif