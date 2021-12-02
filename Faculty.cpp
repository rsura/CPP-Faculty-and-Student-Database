/**
 * Implementation File: Faculty.cpp
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 6
 */
 
#include "Faculty.h"

using namespace std;

/**
 * Default constructor - creates a default faculty member
 */
Faculty::Faculty(){
    id = 0; // in case the setter for id is weird because the int has not been defined yet
    setName("");
    setLevel("");
    setDepartment("");
    advisees = new GenLinkedList<unsigned int>();
}

/**
 * Overloaded constructor - creates a faculty member from all the member variables
 *
 * @param an unsigned int representing the faculty member's ID
 * @param a string representing the faculty member's name
 * @param a string representing the faculty member's level
 * @param a string representing the faculty member's department
 */
Faculty::Faculty(unsigned int id1, string name1, string level1, string department1){
    id = 0; // in case the setter for id is weird because the int has not been defined yet
    setId(id1);
    setName(name1);
    setLevel(level1);
    setDepartment(department1);
    advisees = new GenLinkedList<unsigned int>();
}

/**
 * Overloaded constructor - creates a faculty member from a string of values
 *
 * @param a string in comma separated values of the faculty member's attributes
 */
Faculty::Faculty(string fileLine){
    id = 0; // in case the setter for id is weird because the int has not been defined yet
    advisees = new GenLinkedList<unsigned int>();
    FileProcessor *fp = new FileProcessor();
    string tempStrValue = fp->nextValueInString(fileLine, ",");
    try{
        removeCommas(tempStrValue);
        int tempId = stoi(tempStrValue);
        if (tempId <= 0) {
            throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to create an ID for this faculty member, because it is a negative number.");
        }
        setId(tempId);
    } catch (out_of_range &e){
        cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to create an ID for this faculty member, because it is too large to be an ID.") << endl;
        cerr << "Failed to create Faculty member record." << endl;
        delete fp;
        return;
    } catch (invalid_argument &e){
        cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to create an ID for this faculty member, because it is not a valid number.") << endl;
        cerr << "Failed to create Faculty member record." << endl;
        delete fp;
        return;
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Failed to create Faculty member record." << endl;
        delete fp;
        return;
    }

    tempStrValue = fp->nextValueInString(fileLine, ",");
    try{
        removeCommas(tempStrValue);
        if(fp->isEmptyString(tempStrValue)){
            throw runtime_error("ERROR: No name specified in the database for this faculty member");
        }
        setName(tempStrValue);
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Failed to create Faculty member record." << endl;
        delete fp;
        return;
    }

    tempStrValue = fp->nextValueInString(fileLine, ",");
    try{
        removeCommas(tempStrValue);
        if(fp->isEmptyString(tempStrValue)){
            throw runtime_error("ERROR: No level specified in the database for this faculty member");
        }
        setLevel(tempStrValue);
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Failed to create Faculty member record." << endl;
        delete fp;
        return;
    }

    tempStrValue = fp->nextValueInString(fileLine, ",");
    try{
        removeCommas(tempStrValue);
        if(fp->isEmptyString(tempStrValue)){
            throw runtime_error("ERROR: No department specified in the database for this faculty member");
        }
        setDepartment(tempStrValue);
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Failed to create Faculty member record." << endl;
        delete fp;
        return;
    }

    while (fileLine != "") {
        tempStrValue = fp->nextValueInString(fileLine, ",");
        try{
            removeCommas(tempStrValue);
            int tempId = stoi(tempStrValue);
            if (tempId <= 0) {
                throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to add an advisee ID for this faculty member, because it is a negative number.");
            }
            addAdvisee(tempId);
        } catch (out_of_range &e){ // takes care of out_of_range, invalid_argument, and runtime_error
            cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to add an advisee ID for this faculty member, because it is too large to be an ID.") << endl;
            cerr << "Failed to create Faculty member record." << endl;
            delete fp;
            return;
        } catch (invalid_argument &e){
            cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to add an advisee ID for this faculty member, because it is not a valid number.") << endl;
            cerr << "Failed to create Faculty member record." << endl;
            delete fp;
            return;
        } catch (runtime_error &e){
            cerr << e.what() << endl;
            cerr << "Failed to create Faculty member record." << endl;
            delete fp;
            return;
        }
    }

    delete fp;
}

/**
 * Destructor
 */
Faculty::~Faculty(){
    delete advisees;
}

/**
 * Mutator - sets the ID of the faculty member
 *
 * @param an unsigned int representing the faculty member's ID
 */
void Faculty::setId(unsigned int id1){
    if (id > 0) {
        throw runtime_error("ERROR: Can't change faculty member's ID once set");
    }
    id = id1;
}

/**
 * Accessor - gets the ID of the faculty member
 *
 * @return an unsigned int representing the faculty member's ID
 */
unsigned int Faculty::getId(){
    if (id == 0) {
        throw runtime_error("ERROR: Faculty member's ID has not been set");
    }
    return id;
}

/**
 * Mutator - sets the name of the faculty member
 *
 * @param a string representing the faculty member's name
 */
void Faculty::setName(string name1){
    name = name1;
}

/**
 * Accessor - gets the name of the faculty member
 *
 * @return a string representing the faculty member's name
 */
string Faculty::getName(){
    if (name == "") {
        throw runtime_error("ERROR: Faculty member's name has not been set");
    }
    return name;
}

/**
 * Mutator - sets the level of the faculty member
 *
 * @param a string representing the faculty member's level
 */
void Faculty::setLevel(string level1){
    level = level1;
}

/**
 * Accessor - gets the level of the faculty member
 *
 * @return a string representing the faculty member's level
 */
string Faculty::getLevel(){
    if (level == "") {
        throw runtime_error("ERROR: Faculty member's level has not been set");
    }
    return level;
}

/**
 * Mutator - sets the department of the faculty member
 *
 * @param a string representing the faculty member's department
 */
void Faculty::setDepartment(string department1){
    department = department1;
}

/**
 * Accessor - gets the department of the faculty member
 *
 * @return a string representing the faculty member's department
 */
string Faculty::getDepartment(){
    if (department == "") {
        throw runtime_error("ERROR: Faculty member's department has not been set");
    }
    return department;
}

/**
 * Adds a student to the faculty member's list of advisees
 *
 * @param an unsigned int representing the ID of the student to be added
 */
void Faculty::addAdvisee(unsigned int studId){
    advisees->insertBack(studId);
    advisees->sort();
}

/**
 * Removes a student from the faculty member's list of advisees
 *
 * @param an unsigned int representing the ID of the student to be removed
 */
bool Faculty::removeAdvisee(unsigned int studId){
    if (advisees->find(studId) < 0) {
        return false;
    }
    advisees->removeNode(advisees->find(studId));
    return true;
}

/**
 * Gets the list of advisees in a string
 *
 * @param a string representing the IDs of the advisees, in a comma separated value format
 */
string Faculty::getAdviseeIds(){
    return advisees->getListString();
}

/**
 * Operator overloading for == using IDs
 *
 * @param Faculty member 1 to be compared
 * @param Faculty member 2 to be compared
 * @return a bool representing if member 1 equals member 2
 */
bool operator==(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() == rhs.getId());
}

/**
 * Operator overloading for != using IDs
 *
 * @param Faculty member 1 to be compared
 * @param Faculty member 2 to be compared
 * @return a bool representing if member 1 is not equal to member 2
 */
bool operator!=(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() != rhs.getId());
}

/**
 * Operator overloading for >= using IDs
 *
 * @param Faculty member 1 to be compared
 * @param Faculty member 2 to be compared
 * @return a bool representing if member 1 is greater than or equal to member 2
 */
bool operator>=(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() >= rhs.getId());
}

/**
 * Operator overloading for <= using IDs
 *
 * @param Faculty member 1 to be compared
 * @param Faculty member 2 to be compared
 * @return a bool representing if member 1 is less than or equal to member 2
 */
bool operator<=(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() <= rhs.getId());
}

/**
 * Operator overloading for > using IDs
 *
 * @param Faculty member 1 to be compared
 * @param Faculty member 2 to be compared
 * @return a bool representing if member 1 is greater than member 2
 */
bool operator>(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() > rhs.getId());
}

/**
 * Operator overloading for < using IDs
 *
 * @param Faculty member 1 to be compared
 * @param Faculty member 2 to be compared
 * @return a bool representing if member 1 is less than member 2
 */
bool operator<(Faculty& lhs, Faculty& rhs){
    return (lhs.getId() < rhs.getId());
}

/**
 * Operator overloading for <<
 *
 * @param an ostream like std::cout
 * @param a faculty member
 * @return the same ostream that was passed in
 */
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
        fac.getLevel();
        os << "|" << setw(20) << right << "Level: " << fac.getLevel() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "Level: " << "(NOT SET)" << endl;
    }
    try{
        fac.getDepartment();
        os << "|" << setw(20) << right << "Department: " << fac.getDepartment() << endl;
    } catch (runtime_error &e){
        os << "|" << setw(20) << right << "Department: " << "(NOT SET)" << endl;
    }

    os << setfill('-') << setw(40) << "" << endl;
    os << setfill(' ');

    return os;
}

/**
 * Operator overloading for <<
 *
 * @param an ostream like std::cout
 * @param a pointer to a faculty member object
 * @return the same ostream that was passed in
 */
ostream& operator<<(ostream& os, Faculty*& fac){
    os << *fac;

    return os;
}

/**
 * Operator overloading for >>
 *
 * @param a faculty member
 * @param an ostream like std::cout
 * @return the same ostream that was passed in
 */
ostream& operator>>(Faculty& fac, ostream& os){
    os << fac.getId() << ", " << fac.getName() << ", " << fac.getLevel() << ", " << fac.getDepartment();
    if (fac.getAdviseeIds() != "") {
        os << ", " << fac.getAdviseeIds();
    }
    return os;
}

/**
 * Operator overloading for >>
 *
 * @param a pointer to a faculty member object
 * @param an ostream like std::cout
 * @return the same ostream that was passed in
 */
ostream& operator>>(Faculty*& fac, ostream& os){
    *fac >> os;
    return os;
}

/**
 * Helper function - removes commas in a string passed by reference
 *
 * @param any string. If the string has no commas, nothing will be modified
 */
void Faculty::removeCommas(string& s){
    for (int i = 0; i < s.length(); i++) { // remove potential commas in the integer, since db stores it as csv
        if (s[i] == ',') {
            s = s.substr(0,i) + s.substr(i+1);
        }
    }
}