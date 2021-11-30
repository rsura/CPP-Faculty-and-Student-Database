#include "Student.h"

using namespace std;

Student::Student(){
    id = 0;
    setName("");
    setLevel("");
    setMajor("");
    setGpa(0.00);
    setAdvisorId(0);
}

Student::Student(unsigned int id1, string name1, string level1, string major1, double gpa1, unsigned int advisorId1){
    id = 0; // in case the setter for id is weird because the int has not been defined yet
    setId(id1);
    setName(name1);
    setLevel(level1);
    setMajor(major1);
    setGpa(gpa1);
    setAdvisorId(advisorId1);
}

Student::~Student(){

}

void Student::setId(unsigned int id1){
    if (id > 0) {
        throw runtime_error("ERROR: Can't change student's ID once set");
    }
    id = id1;
}

unsigned int Student::getId(){
    if (id == 0) {
        throw runtime_error("ERROR: Student's ID has not been set");
    }
    return id;
}

void Student::setName(string name1){
    name = name1;
}

string Student::getName(){
    if (name == "") {
        throw runtime_error("ERROR: Student's name has not been set");
    }
    return name;
}

void Student::setLevel(string level1){
    level = level1;
}

string Student::getLevel(){
    if (level == "") {
        throw runtime_error("ERROR: Student's level has not been set");
    }
    return level;
}

void Student::setMajor(string major1){
    major = major1;
}

string Student::getMajor(){
    if (major == "") {
        throw runtime_error("ERROR: Student's major has not been set");
    }
    return major;
}

void Student::setGpa(double gpa1){
    if (gpa1 < 0.00 || gpa1 > 4.00) {
        throw runtime_error("ERROR: Student's gpa has to be set within the range of: 0 ≤ GPA ≤ 4.00");
    }
    gpa = gpa1;
}

double Student::getGpa(){
    if (gpa == 0.00) {
        throw runtime_error("ERROR: Student's gpa has not been set");
    }
    return gpa;
}

void Student::setAdvisorId(unsigned int advisorId1){
    advisorId = advisorId1;
}

unsigned int Student::getAdvisorId(){
    return advisorId;
}

bool operator==(Student& lhs, Student& rhs){

}

bool operator!=(Student& lhs, Student& rhs){

}

bool operator>=(Student& lhs, Student& rhs){

}

bool operator<=(Student& lhs, Student& rhs){

}

bool operator>(Student& lhs, Student& rhs){

}

bool operator<(Student& lhs, Student& rhs){

}

ostream& operator<<(ostream& os, Student& stud){
    try{
        stud.getId();
        stud.getName();
    } catch (runtime_error &e){
        return os; // empty ostream because the student has no ID or name, so it's an empty student to print
    }
    os << setfill('-') << setw(40) << "" << endl;
    os << setfill('*') << setw(15) << "" << " Student " << setfill('*') << setw(15) << "" << setfill(' ') << endl;

    os << "|" << setw(20) << right << "ID: " << stud.getId() << endl;
    os << "|" << setw(20) << right << "Name: " << stud.getName() << endl;
    try{
        os << "|" << setw(20) << right << "Level: " << stud.getLevel() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "Level: " << "(NOT SET)" << endl;
    }
    try{
        os << "|" << setw(20) << right << "Major: " << stud.getMajor() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "Major: " << "(NOT SET)" << endl;
    }
    try{
        os << "|" << setw(20) << right << "GPA: " << stud.getGpa() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "GPA: " << "(NOT SET)" << endl;
    }
    os << setfill('-') << setw(40) << "" << endl;
    os << setfill(' ');

    return os;
}

ostream& operator<<(ostream& os, Student*& stud){
    os << *stud;

    return os;
}
