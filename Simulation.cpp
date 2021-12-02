/**
 * Implementation File: Simulation.cpp
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 6
 */

#include "Simulation.h"

using namespace std;

Simulation::Simulation(){
    masterStudent = new BST<Student>();
    masterFaculty = new BST<Faculty>();
}

Simulation::~Simulation(){
    delete masterStudent;
    delete masterFaculty;
}

void Simulation::run(){

}

void Simulation::printAllStudents(){
    masterStudent->printNodes();
}

void Simulation::printAllFaculty(){
    masterFaculty->printNodes();
}

void Simulation::printStudent(){

}

void Simulation::printFaculty(){

}

void Simulation::printStudAdvisor(){

}

void Simulation::printFacultyAdvisees(){

}

bool Simulation::addNewStudent(){
    return true; // temporary
}

bool Simulation::deleteStudent(){
    return true; // temporary
}

bool Simulation::addNewFaculty(){
    return true; // temporary
}

bool Simulation::deleteFaculty(){
    return true; // temporary
}

bool Simulation::changeStudAdvisor(){
    return true; // temporary
}

bool Simulation::removeFacultyAdvisee(){
    return true; // temporary
}

bool Simulation::rollbackLastChange(){
    return true; // temporary
}

void Simulation::saveAndQuit(){

}

/**
 * Helper function - removes commas in a string passed by reference
 *
 * @param any string. If the string has no commas, nothing will be modified
 */
void Simulation::removeCommas(string& s){
    for (int i = 0; i < s.length(); i++) { // remove potential commas in the string, since db stores it as csv
        if (s[i] == ',') {
            s = s.substr(0,i) + s.substr(i+1);
        }
    }
}
