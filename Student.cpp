/**
 * Implementation File: Student.cpp
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 6
 */

#include "Student.h"

using namespace std;

/**
 * Default constructor - creates a default student
 */
Student::Student(){
    id = 0; // in case the setter for id is weird because the int has not been defined yet
    setName("");
    setLevel("");
    setMajor("");
    setGpa(0.00);
    setAdvisorId(0);
}

/**
 * Overloaded constructor - creates a student from all the member variables
 *
 * @param an unsigned int representing the student's ID
 * @param a string representing the student's name
 * @param a string representing the student's level
 * @param a string representing the student's major
 * @param a double representing the student's GPA. Throws an error if not between 0.00 and 4.00
 * @param an unsigned int representing the advisor's ID
 */
Student::Student(unsigned int id1, string name1, string level1, string major1, double gpa1, unsigned int advisorId1){
    id = 0; // in case the setter for id is weird because the int has not been defined yet
    setId(id1);
    setName(name1);
    setLevel(level1);
    setMajor(major1);
    setGpa(gpa1);
    setAdvisorId(advisorId1);
}

/**
 * Overloaded constructor - creates a student from a string of values. Throws a
 * runtime_error if the string of values are not properly set.
 *
 * @param a string in comma separated values of the student's attributes
 */
Student::Student(string fileLine){
    id = 0; // in case the setter for id is weird because the int has not been defined yet
    FileProcessor *fp = new FileProcessor();
    string tempStrValue = fp->nextValueInString(fileLine, ",");
    try{ // setting ID
        int tempId = stoi(tempStrValue);
        if (tempId <= 0) {
            throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to create an ID for this student, because it is a negative number or zero.\nFailed to create student record.");
        }
        setId(tempId);
    } catch (out_of_range &e){
        throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to create an ID for this student, because it is too large to be an ID.\nFailed to create student record.");
    } catch (invalid_argument &e){
        throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to create an ID for this student, because it is not a valid number.\nFailed to create student record.");
    } catch (runtime_error &e){
        delete fp;
        throw runtime_error(e.what());
    }

    tempStrValue = fp->nextValueInString(fileLine, ",");
    try{ // setting name
        if(fp->isEmptyString(tempStrValue)){
            throw runtime_error("ERROR: No name specified in the database for this student.\nFailed to create student record.");
        }
        setName(tempStrValue);
    } catch (runtime_error &e){
        delete fp;
        throw runtime_error(e.what());
    }

    tempStrValue = fp->nextValueInString(fileLine, ",");
    try{ // setting level
        if(fp->isEmptyString(tempStrValue)){
            throw runtime_error("ERROR: No level specified in the database for this student.\nFailed to create student record.");
        }
        setLevel(tempStrValue);
    } catch (runtime_error &e){
        delete fp;
        throw runtime_error(e.what());
    }

    tempStrValue = fp->nextValueInString(fileLine, ",");
    try{ // setting major
        if(fp->isEmptyString(tempStrValue)){
            throw runtime_error("ERROR: No major specified in the database for this student.\nFailed to create student record.");
        }
        setMajor(tempStrValue);
    } catch (runtime_error &e){
        delete fp;
        throw runtime_error(e.what());
    }

    tempStrValue = fp->nextValueInString(fileLine, ",");
    try{ // setting GPA
        double tempGpa = stod(tempStrValue);
        if (tempGpa < 0 || tempGpa > 4.0) {
            throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to add a GPA for this student, because student's gpa has to be set within the range of: 0 ≤ GPA ≤ 4.00.\nFailed to create student record.");
        }
        setGpa(tempGpa);
    } catch (out_of_range &e){
        throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to add a GPA for this student, because it is too large to be a GPA.\nFailed to create student record.");
    } catch (invalid_argument &e){
        throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to add a GPA for this student, because it is not a valid number.\nFailed to create student record.");
    } catch (runtime_error &e){
        delete fp;
        throw runtime_error(e.what());
    }

    tempStrValue = fp->nextValueInString(fileLine, ",");
    try{ // setting advisor ID
        int tempAdvisorId = stoi(tempStrValue);
        if (tempAdvisorId <= 0) {
            throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to add a GPA for this student, because it is a negative number.\nFailed to create student record.");
        }
        setAdvisorId(tempAdvisorId);
    } catch (out_of_range &e){
        throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to add a GPA for this student, because it is too large to be an ID.\nFailed to create student record.");
    } catch (invalid_argument &e){
        throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to add a GPA for this student, because it is not a valid number.\nFailed to create student record.");
    } catch (runtime_error &e){
        delete fp;
        throw runtime_error(e.what());
    }

    delete fp;
}

/**
 * Destructor
 */
Student::~Student(){
    // nothing to delete
}

/**
 * Mutator - sets the ID of the student
 *
 * @param an unsigned int representing the student's ID
 */
void Student::setId(unsigned int id1){
    if (id > 0) {
        throw runtime_error("ERROR: Can't change student's ID once set");
    }
    id = id1;
}

/**
 * Accessor - gets the ID of the student
 *
 * @return an unsigned int representing the student's ID
 */
unsigned int Student::getId(){
    if (id == 0) {
        throw runtime_error("ERROR: Student's ID has not been set");
    }
    return id;
}

/**
 * Mutator - sets the name of the student
 *
 * @param a string representing the student's name
 */
void Student::setName(string name1){
    name = name1;
}

/**
 * Accessor - gets the name of the student
 *
 * @return a string representing the student's name
 */
string Student::getName(){
    if (name == "") {
        throw runtime_error("ERROR: Student's name has not been set");
    }
    return name;
}

/**
 * Mutator - sets the level of the student
 *
 * @param a string representing the student's level
 */
void Student::setLevel(string level1){
    level = level1;
}

/**
 * Accessor - gets the level of the student
 *
 * @return a string representing the student's level
 */
string Student::getLevel(){
    if (level == "") {
        throw runtime_error("ERROR: Student's level has not been set");
    }
    return level;
}

/**
 * Mutator - sets the major of the student
 *
 * @param a string representing the student's major
 */
void Student::setMajor(string major1){
    major = major1;
}

/**
 * Accessor - gets the major of the student
 *
 * @return a string representing the student's major
 */
string Student::getMajor(){
    if (major == "") {
        throw runtime_error("ERROR: Student's major has not been set");
    }
    return major;
}

/**
 * Mutator - sets the GPA of the student. Throws an error if gpa is not between 0.00 and 4.00
 *
 * @param a double representing the student's GPA
 */
void Student::setGpa(double gpa1){
    if (gpa1 < 0.00 || gpa1 > 4.00) {
        throw runtime_error("ERROR: Student's gpa has to be set within the range of: 0 ≤ GPA ≤ 4.00");
    }
    gpa = gpa1;
}

/**
 * Accessor - gets the GPA of the student
 *
 * @return a double representing the student's GPA
 */
double Student::getGpa(){
    if (gpa == 0.00) {
        throw runtime_error("ERROR: Student's gpa has not been set");
    }
    return gpa;
}

/**
 * Mutator - sets the ID of the student's advisor
 *
 * @param an unsigned int representing the student's advisor's ID
 */
void Student::setAdvisorId(unsigned int advisorId1){
    advisorId = advisorId1;
}

/**
 * Accessor - gets the ID of the student's advisor
 *
 * @return an unsigned int representing the student's advisor's ID
 */
unsigned int Student::getAdvisorId(){
    return advisorId;
}

/**
 * Operator overloading for == using IDs
 *
 * @param Student 1 to be compared
 * @param Student 2 to be compared
 * @return a bool representing if Student 1 equals Student 2
 */
bool operator==(Student& lhs, Student& rhs){
    return (lhs.getId() == rhs.getId());
}

/**
 * Operator overloading for != using IDs
 *
 * @param Student 1 to be compared
 * @param Student 2 to be compared
 * @return a bool representing if Student 1 is not equal to Student 2
 */
bool operator!=(Student& lhs, Student& rhs){
    return (lhs.getId() != rhs.getId());
}

/**
 * Operator overloading for >= using IDs
 *
 * @param Student 1 to be compared
 * @param Student 2 to be compared
 * @return a bool representing if Student 1 is greater than or equal to Student 2
 */
bool operator>=(Student& lhs, Student& rhs){
    return (lhs.getId() >= rhs.getId());
}

/**
 * Operator overloading for <= using IDs
 *
 * @param Student 1 to be compared
 * @param Student 2 to be compared
 * @return a bool representing if Student 1 is less than or equal to Student 2
 */
bool operator<=(Student& lhs, Student& rhs){
    return (lhs.getId() <= rhs.getId());
}

/**
 * Operator overloading for > using IDs
 *
 * @param Student 1 to be compared
 * @param Student 2 to be compared
 * @return a bool representing if Student 1 is greater than Student 2
 */
bool operator>(Student& lhs, Student& rhs){
    return (lhs.getId() > rhs.getId());
}

/**
 * Operator overloading for < using IDs
 *
 * @param Student 1 to be compared
 * @param Student 2 to be compared
 * @return a bool representing if Student 1 is less than Student 2
 */
bool operator<(Student& lhs, Student& rhs){
    return (lhs.getId() < rhs.getId());
}

/**
 * Operator overloading for <<
 *
 * @param an ostream like std::cout
 * @param a student
 * @return the same ostream that was passed in
 */
ostream& operator<<(ostream& os, Student& stud){
    try{
        stud.getId();
        stud.getName();
    } catch (runtime_error &e){
        return os; // empty ostream because the student has no ID or name, so it's an empty student to print
    }
    os << setfill('-') << setw(41) << "" << endl;
    os << setfill('*') << setw(16) << "" << " Student " << setfill('*') << setw(16) << "" << setfill(' ') << endl;

    os << "|" << setw(20) << right << "ID: " << stud.getId() << endl;
    os << "|" << setw(20) << right << "Name: " << stud.getName() << endl;
    try{
        stud.getLevel();
        os << "|" << setw(20) << right << "Level: " << stud.getLevel() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "Level: " << "(NOT SET)" << endl;
    }
    try{
        stud.getMajor();
        os << "|" << setw(20) << right << "Major: " << stud.getMajor() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "Major: " << "(NOT SET)" << endl;
    }
    try{
        stud.getGpa();
        os << "|" << setw(20) << right << "GPA: " << fixed << setprecision(2) << stud.getGpa() << resetiosflags(ios::showbase) << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "GPA: " << "(NOT SET)" << endl;
    }

    try{
        stud.getAdvisorId();
        os << "|" << setw(20) << right << "Advisor's ID: " << stud.getAdvisorId() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "Advisor's ID: " << "(NOT SET)" << endl;
    }
    os << setfill('-') << setw(41) << "" << endl;
    os << setfill(' ');

    return os;
}

/**
 * Operator overloading for <<
 *
 * @param an ostream like std::cout
 * @param a pointer to a student object
 * @return the same ostream that was passed in
 */
ostream& operator<<(ostream& os, Student*& stud){
    os << *stud;

    return os;
}

/**
 * Operator overloading for >>, to get a csv of the student's info
 *
 * @param a student
 * @param an ostream like std::cout
 * @return the same ostream that was passed in
 */
ostream& operator>>(Student& stud, ostream& os){
    try{
        stud.getId();
        stud.getName();
        stud.getLevel();
        stud.getMajor();
        stud.getGpa();
        stud.getAdvisorId();
    } catch (exception &e){
        return os;
    }
    os << stud.getId() << ", " << stud.getName() << ", " << stud.getLevel() << ", ";
    os << stud.getMajor() << ", " << stud.getGpa() << ", " << stud.getAdvisorId() << endl;
    return os;
}

/**
 * Operator overloading for >>, to get a csv of the student's info
 *
 * @param a pointer to a student object
 * @param an ostream like std::cout
 * @return the same ostream that was passed in
 */
ostream& operator>>(Student*& stud, ostream& os){
    *stud >> os;
    return os;
}