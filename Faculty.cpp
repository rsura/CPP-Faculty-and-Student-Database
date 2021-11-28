#include "Faculty.h"

using namespace std;

Faculty::Faculty(){
    setId(0);
    setName("Foo Bar VII of England");
    setLevel("No Level");
    setDepartment("Computer Science");
    advisees = new GenLinkedList<unsigned int>();
}

Faculty::Faculty(unsigned int id1, string name1, string level1, string department1){
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
    id = id1;
}

unsigned int Faculty::getId(){
    return id;
}

void Faculty::setName(string name1){
    name = name1;
}

string Faculty::getName(){
    return name;
}

void Faculty::setLevel(string level1){
    level = level1;
}

string Faculty::getLevel(){
    return level;
}

void Faculty::setDepartment(string department1){
    department = department1;
}

string Faculty::getDepartment(){
    return department;
}

bool Faculty::addAdvisee(Student* newStudent){
    advisees.insertBack(newStudent->getId());
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
    os << "Faculty Member:" << endl;
    os << "ID: " << fac.getId() << endl;
    os << "Name: " << fac.getName() << endl;
    os << "Level: " << fac.getLevel() << endl;
    os << "Department: " << fac.getDepartment() << endl;
}

ostream& operator<<(ostream& os, Faculty*& fac){

}

