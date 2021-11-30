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

}

bool Simulation::deleteStudent(){

}

bool Simulation::addNewFaculty(){

}

bool Simulation::deleteFaculty(){

}

bool Simulation::changeStudAdvisor(){

}

bool Simulation::removeFacultyAdvisee(){

}

bool Simulation::rollbackLastChange(){

}

void Simulation::saveAndQuit(){

}
