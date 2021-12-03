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
#include <unistd.h> // includes micro sleep function (usleep)

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
        void addNewStudent();
        void deleteStudent();
        void addNewFaculty();
        void deleteFaculty();
        void changeStudAdvisor();
        void removeFacultyAdvisee();
        void rollbackLastChange();
        void saveAndQuit();

        // helper methods
        unsigned int getValidId(string s);
        void displayOptions();
        void setUp();
        void removeCommas(string& s);

        // BSTs of students and faculty
        BST<Student> *masterStudent;
        BST<Faculty> *masterFaculty;

        // file names of the student file and faculty file
        string studentFile;
        string facultyFile;
};

#endif