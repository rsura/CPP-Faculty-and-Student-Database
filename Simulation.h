#ifndef SIMULATION_H
#define SIMULATION_H

#include "Faculty.h"
#include "Student.h"
#include "RollbackStack.h"

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

        // BSTs of students and faculty
        BST<Student> *masterStudent;
        BST<Faculty> *masterFaculty;

        // file names of the student file and faculty file
        string studentFile;
        string facultyFile;
};

#endif