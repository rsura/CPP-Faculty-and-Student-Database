#include "Faculty.h"

using namespace std;

Faculty::Faculty(){
    id = 0;
    setName("");
    setLevel("");
    setDepartment("");
    advisees = new GenLinkedList<unsigned int>();
}

Faculty::Faculty(unsigned int id1, string name1, string level1, string department1){
    id = 0; // in case the setter for id is weird because the int has not been defined yet
    setId(id1);
    setName(name1);
    setLevel(level1);
    setDepartment(department1);
    advisees = new GenLinkedList<unsigned int>();
}

Faculty::~Faculty(){
    delete advisees;
}

void Faculty::setId(unsigned int id1){
    if (id > 0) {
        throw runtime_error("ERROR: Can't change faculty member's ID once set");
    }
    id = id1;
}

unsigned int Faculty::getId(){
    if (id == 0) {
        throw runtime_error("ERROR: Faculty member's ID has not been set");
    }
    return id;
}

void Faculty::setName(string name1){
    name = name1;
}

string Faculty::getName(){
    if (name == "") {
        throw runtime_error("ERROR: Faculty member's name has not been set");
    }
    return name;
}

void Faculty::setLevel(string level1){
    level = level1;
}

string Faculty::getLevel(){
    if (level == "") {
        throw runtime_error("ERROR: Faculty member's level has not been set");
    }
    return level;
}

void Faculty::setDepartment(string department1){
    department = department1;
}

string Faculty::getDepartment(){
    if (level == "") {
        throw runtime_error("ERROR: Faculty member's department has not been set");
    }
    return department;
}

void Faculty::addAdvisee(Student*& newStudent){
    advisees->insertBack(/*REPLACE THIS WITH SOME LOGIC OF IF THE STUDENT HAS THEM AS THE FACULTY*/0);
    advisees->sort();
}

bool Faculty::removeAdvisee(unsigned int studId){
    if (advisees->find(studId) < 0) {
        return false;
    }
    advisees->removeNode(advisees->find(studId));
}

bool operator==(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() == rhs.getId());
}

bool operator!=(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() != rhs.getId());
}

bool operator>=(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() >= rhs.getId());
}

bool operator<=(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() <= rhs.getId());
}

bool operator>(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() > rhs.getId());
}

bool operator<(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() < rhs.getId());
}

ostream& operator<<(ostream& os, Faculty& fac){
    try{
        fac.getId();
        fac.getName();
    } catch (runtime_error &e){
        return os; // empty ostream because the faculty member has no ID or name, so it's an empty faculty to print
    }

    os << setfill('-') << setw(40) << "" << endl;
    os << setfill('*') << setw(12) << "" << " Faculty Member " << setfill('*') << setw(12) << "" << setfill(' ') << endl;

    os << "|" << setw(20) << right << "ID: " << fac.getId() << endl;
    os << "|" << setw(20) << right << "Name: " << fac.getName() << endl;
    try{
        os << "|" << setw(20) << right << "Level: " << fac.getLevel() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "Level: " << "(NOT SET)" << endl;
    }
    try{
        os << "|" << setw(20) << right << "Department: " << fac.getDepartment() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "Department: " << "(NOT SET)" << endl;
    }

    os << setfill('-') << setw(40) << "" << endl;
    os << setfill(' ');

    return os;
}

ostream& operator<<(ostream& os, Faculty*& fac){
    os << *fac;

    return os;
}
