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
    setUp();
    bool exit = false;
    while(!exit){
        displayOptions();
        string selectedOption;
        getline(cin, selectedOption);
        FileProcessor fp;
        int optionNumber;
        if (fp.isEmptyString(selectedOption)) {
            cerr << "ERROR: No input. Instructions will be repeated again." << endl;
            continue;
        } else {
            try{
                optionNumber = stoi(selectedOption);
            } catch (exception &e) {
                cerr << "ERROR: Not a valid way of writing an option. Instructions will be repeated again." << endl;
                continue;
            }
            switch (optionNumber) {
                case 1:
                    printAllStudents();
                    break;
                case 2:
                    printAllFaculty();
                    break;
                case 3:
                    printStudent();
                    break;
                case 4:
                    printFaculty();
                    break;
                case 5:
                    printStudAdvisor();
                    break;
                case 6:
                    printFacultyAdvisees();
                    break;
                case 7:
                    addNewStudent();
                    break;
                case 8:
                    deleteStudent();
                    break;
                case 9:
                    addNewFaculty();
                    break;
                case 10:
                    deleteFaculty();
                    break;
                case 11:
                    changeStudAdvisor();
                    break;
                case 12:
                    removeFacultyAdvisee();
                    break;
                case 13:
                    rollbackLastChange();
                    break;
                case 14:
                    exit = true;
                    break;
                default:
                    cerr << "ERROR: Not a valid option number. Instructions will be repeated again." << endl;
                    break;
            }
        }
    }
    saveAndQuit();
}

void Simulation::setUp(){
    cout << "Hello there! Welcome to the Student and Faculty Database Program!" << endl;
    FileProcessor *fp = new FileProcessor();

    try{ // reading master faculty database
        fp->setReadFileName("facultyTable");
        while (!fp->eof()) {
            string fileLine = fp->getNextLine();
            if (fp->isEmptyString(fileLine)) {
                continue;
            }
            try{
                if (!masterFaculty->contains(Faculty(fileLine))) {
                    masterFaculty->insert(Faculty(fileLine));
                }
            } catch (runtime_error &e){
                // fail quietly. We don't need error message on start up if the file has incorrect lines
            }
        }
    } catch (runtime_error &e){
        // fail quietly. Faculty database doesn't exist yet, and that's ok
    }

    try{ // reading master student database
        fp->setReadFileName("studentTable");
        while (!fp->eof()) {
            string fileLine = fp->getNextLine();
            if (fp->isEmptyString(fileLine)) {
                continue;
            }
            try{
                Student s1(fileLine);
                if (!masterStudent->contains(s1) && masterFaculty->contains(Faculty(s1.getAdvisorId()))) {
                    masterStudent->insert(s1);
                    (masterFaculty->find(Faculty(s1.getAdvisorId())))->addAdvisee(s1.getId());
                }
            } catch (runtime_error &e){
                // fail quietly. We don't need error message on start up if the file has incorrect lines
            }
        }
    } catch (runtime_error &e){
        // fail quietly. Student database doesn't exist yet, and that's ok
    }
    delete fp;
}

void Simulation::displayOptions(){
    long pauseTimeBtwn = 500000 / 16;
    cout << "Here are the possible options for interacting with the database:" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t1. Print all students and their information (sorted by ascending id #)" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t2. Print all faculty and their information (sorted by ascending id #)" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t3. Find and display student information given the students id" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t4. Find and display faculty information given the faculty id" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t5. Given a student’s id, print the name and info of their faculty advisor" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t6. Given a faculty id, print ALL the names and info of his/her advisees." << endl;
    usleep(pauseTimeBtwn);
    cout << "\t7. Add a new student" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t8. Delete a student given the id" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t9. Add a new faculty member" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t10. Delete a faculty member given the id." << endl;
    usleep(pauseTimeBtwn);
    cout << "\t11. Change a student’s advisor given the student id and the new faculty id." << endl;
    usleep(pauseTimeBtwn);
    cout << "\t12. Remove an advisee from a faculty member given the ids" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t13. Undo last change ↺" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t14. Save and quit" << endl;
    usleep(pauseTimeBtwn);
    cout << "Please type the number corresponding to the option that you would like to choose:" << endl;
    usleep(pauseTimeBtwn);
    cout << "--->\t";
    usleep(pauseTimeBtwn);
}

void Simulation::printAllStudents(){
    if (masterStudent->isEmpty()) {
        cout << "Student database is empty. Nothing to print." << endl;
        usleep(1000000);
        return;
    }
    cout << "Printing information of all students..." << endl;
    usleep(500000);
    masterStudent->printNodes();
    usleep(1000000);
}

void Simulation::printAllFaculty(){
    if (masterFaculty->isEmpty()) {
        cout << "Faculty database is empty. Nothing to print." << endl;
        usleep(1000000);
        return;
    }
    cout << "Printing information of all faculty members..." << endl;
    usleep(500000);
    masterFaculty->printNodes();
    usleep(1000000);
}

void Simulation::printStudent(){
    if (masterStudent->isEmpty()) {
        cout << "Student database is empty. It wouldn't be possible to print any student's information." << endl;
        usleep(1000000);
        return;
    }
    cout << "What is the ID of the student that you would like to print?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);
    try{
        FileProcessor fp;
        if (fp.isEmptyString(tempStrValue)) {
            throw runtime_error("ERROR: No value for student ID provided.");
        }
        int tempId = stoi(tempStrValue);
        if (tempId <= 0) {
            throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to print the student's info, because it is a negative number or zero.");
        }
        unsigned int referenceId = tempId;
        if (masterStudent->contains(Student(referenceId))) {
            cout << *(masterStudent->find(Student(referenceId))) << endl;
        } else {
            cerr << "ERROR: No student found with the ID: \"" << referenceId << "\"" << endl;
        }
    } catch (out_of_range &e){
        cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to print the student's info, because it is too large to be an ID.") << endl;
    } catch (invalid_argument &e){
        cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to print the student's info, because it is not a valid number.") << endl;
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

void Simulation::printFaculty(){
    if (masterFaculty->isEmpty()) {
        cout << "Faculty database is empty. It wouldn't be possible to print any faculty member's information." << endl;
        usleep(1000000);
        return;
    }
    cout << "What is the ID of the faculty member that you would like to print?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);
    try{
        FileProcessor fp;
        if (fp.isEmptyString(tempStrValue)) {
            throw runtime_error("ERROR: No value for faculty ID provided.");
        }
        int tempId = stoi(tempStrValue);
        if (tempId <= 0) {
            throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to print the faculty member's info, because it is a negative number or zero.");
        }
        unsigned int referenceId = tempId;
        if (masterFaculty->contains(Faculty(referenceId))) {
            cout << *(masterFaculty->find(Faculty(referenceId))) << endl;
        } else {
            cerr << "ERROR: No faculty member found with the ID: \"" << referenceId << "\"" << endl;
        }
    } catch (out_of_range &e){
        cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to print the faculty member's info, because it is too large to be an ID.") << endl;
    } catch (invalid_argument &e){
        cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to print the faculty member's info, because it is not a valid number.") << endl;
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
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
    cout << "Exiting program. Thank you." << endl;
    usleep(1000000);
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
