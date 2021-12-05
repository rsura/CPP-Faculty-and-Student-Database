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
    rb = new Rollback<string>(5);
}

Simulation::~Simulation(){
    delete masterStudent;
    delete masterFaculty;
    delete rb;
}

void Simulation::run(){
    setUp();
    bool exit = false;
    while(!exit){
        displayOptions();
        string selectedOption;
        getline(cin, selectedOption);
        int optionNumber;
        if (FileProcessor::isEmptyString(selectedOption)) {
            cerr << "ERROR: No input. Instructions will be repeated again." << endl;
            usleep(1000000);
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
                    usleep(1000000);
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
                    // *(masterFaculty->find(Faculty(s1.getAdvisorId()))) >> cout;
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
        unsigned int referenceId = getValidId(tempStrValue);
        if (masterStudent->contains(Student(referenceId))) {
            cout << *(masterStudent->find(Student(referenceId))) << endl;
        } else {
            cerr << "ERROR: No student found with the ID: \"" << referenceId << "\"" << endl;
        }
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
        unsigned int referenceId = getValidId(tempStrValue);
        if (masterFaculty->contains(Faculty(referenceId))) {
            cout << *(masterFaculty->find(Faculty(referenceId))) << endl;
        } else {
            cerr << "ERROR: No faculty member found with the ID: \"" << referenceId << "\"" << endl;
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

void Simulation::printStudAdvisor(){
    if (masterStudent->isEmpty()) {
        cout << "Student database is empty. It wouldn't be possible to print any student's advisor's information." << endl;
        usleep(1000000);
        return;
    }
    cout << "What is the ID of the student that you would like to print their advisor's info of?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);
    try{
        unsigned int referenceId = getValidId(tempStrValue);
        if (masterStudent->contains(Student(referenceId))) {
            unsigned int advisorId = (masterStudent->find(Student(referenceId)))->getAdvisorId();
            if (masterFaculty->contains(Faculty(advisorId))) {
                cout << "Printing the advisor info of the student with ID #" << referenceId << endl;
                usleep(500000);
                cout << *(masterFaculty->find(Faculty(advisorId))) << endl;
            } else { // shouldn't happen if program is used properly, but there in case
                throw runtime_error("ERROR: Student's advisor doesn't exist in the faculty database.");
            }
        } else {
            cerr << "ERROR: No student found with the ID: \"" << referenceId << "\"" << endl;
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

void Simulation::printFacultyAdvisees(){
    if (masterFaculty->isEmpty()) {
        cout << "Faculty database is empty. It wouldn't be possible to print any faculty member's information." << endl;
        usleep(1000000);
        return;
    }
    cout << "What is the ID of the faculty member that you would like to print all of their advisee's info of?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);
    try{
        unsigned int referenceId = getValidId(tempStrValue);
        if (masterFaculty->contains(Faculty(referenceId))) {
            GenLinkedList<unsigned int> advisees = masterFaculty->find(Faculty(referenceId))->getAllAdvisees();
            if (advisees.getSize() == 0) {
                throw runtime_error("This faculty member has no advisees. Nothing will be printed.");
            }
            cout << "Printing info of all advisees of faculty member with ID #" << referenceId << endl;
            usleep(500000);
            for (int i = 0; i < advisees.getSize(); ++i) {
                unsigned int studId = *(advisees.returnData(i));
                if (masterStudent->contains(Student(studId))) {
                    cout << *(masterStudent->find(Student(studId))) << endl;
                } else {
                    masterFaculty->find(Faculty(referenceId))->removeAdvisee(studId);
                }
            }
        } else {
            cerr << "ERROR: No faculty member found with the ID: \"" << referenceId << "\"" << endl;
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

void Simulation::addNewStudent(){
    unsigned int newFacultyId;
    unsigned int newStudId;
    string newName;
    string newLevel;
    string newMajor;
    double newGpa;
    string tempStrValue;

    cout << "Creating a new student. Please follow the following prompts." << endl;
    usleep(500000);

    cout << "What is the ID of the advisor that this student is going to be under?\n--->\t";
    getline(cin, tempStrValue);
    FileProcessor::isEmptyString(tempStrValue);
    try{
        newFacultyId = getValidId(tempStrValue);
        if (!masterFaculty->contains(Faculty(newFacultyId))) {
            string s = "ERROR: No faculty member with the ID: \"" + to_string(newFacultyId) + "\" found in the database.";
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Terminating student creation." << endl;
        usleep(1000000);
        return;
    }

    cout << "New student's ID:\n--->\t";
    getline(cin, tempStrValue);
    FileProcessor::isEmptyString(tempStrValue);
    try{
        newStudId = getValidId(tempStrValue);
        if (masterStudent->contains(Student(newStudId))) {
            string s = "ERROR: Student with the ID: \"" + to_string(newStudId) + "\" already exists in the database.";
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Terminating student creation." << endl;
        usleep(1000000);
        return;
    }

    cout << "New student's name:\n--->\t";
    getline(cin, newName);
    if (FileProcessor::isEmptyString(newName)) {
        cerr << "ERROR: Empty string provided for name.\nFailed to create student." << endl;
        usleep(1000000);
        return;
    }
    removeCommas(newName);

    cout << "New student's level:\n--->\t";
    getline(cin, newLevel);
    if (FileProcessor::isEmptyString(newLevel)) {
        cerr << "ERROR: Empty string provided for level.\nFailed to create student." << endl;
        usleep(1000000);
        return;
    }
    removeCommas(newLevel);

    cout << "New student's major:\n--->\t";
    getline(cin, newMajor);
    if (FileProcessor::isEmptyString(newMajor)) {
        cerr << "ERROR: Empty string provided for major.\nFailed to create student." << endl;
        usleep(1000000);
        return;
    }
    removeCommas(newMajor);

    cout << "New student's GPA:\n--->\t";
    getline(cin, tempStrValue);
    try{
        newGpa = stod(tempStrValue);
        if (newGpa < 0 || newGpa > 4.0) {
            throw runtime_error("ERROR: Can't use your input of \"" + tempStrValue + "\" to add a GPA for this student, because student's gpa has to be set within the range of: 0 ≤ GPA ≤ 4.00.\nFailed to create student record.");
        }
    } catch (out_of_range &e){
        cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to add a GPA for this student, because it is too large to be a GPA.\nFailed to create student record.") << endl;
        usleep(1000000);
        return;
    } catch (invalid_argument &e){
        cerr << ("ERROR: Can't use your input of \"" + tempStrValue + "\" to add a GPA for this student, because it is not a valid number.\nFailed to create student record.") << endl;
        usleep(1000000);
        return;
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    try{
        Student s1(newStudId, newName, newLevel, newMajor, newGpa, newFacultyId);
        masterStudent->insert(s1);
        cout << "Success! Added a new student with the following info:" << endl;
        cout << s1 << endl;
        masterFaculty->find(Faculty(newFacultyId))->addAdvisee(newStudId);
        ostringstream os; // rollback stuff
        os << "StudentDelete: ";
        s1 >> os;
        rb->push(os.str());
    } catch (exception &e){
        cerr << "ERROR: Something went wrong when trying to create a new faculty member." << endl;
    }
    usleep(1000000);
}

void Simulation::deleteStudent(){
    if (masterStudent->isEmpty()) {
        cout << "Student database is empty. It wouldn't be possible to delete any student from the database." << endl;
        usleep(1000000);
        return;
    }
    cout << "What is the ID of the student that you would like to delete?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);
    try{
        unsigned int referenceId = getValidId(tempStrValue);
        if (masterStudent->contains(Student(referenceId))) {
            Student s1 = *(masterStudent->find(Student(referenceId)));
            unsigned int studAdvisor = s1.getAdvisorId();
            ostringstream os; // rollback stuff
            os << "StudentAdd: ";
            s1 >> os;
            rb->push(os.str());
            masterStudent->deleteNode(Student(referenceId));
            cout << "Success! Deleted the student with ID #" << referenceId << endl;
            usleep(500000);
            if (masterFaculty->contains(Faculty(studAdvisor))) {
                masterFaculty->find(Faculty(studAdvisor))->removeAdvisee(referenceId);
                cout << "Also, removed the student from the list of the advisees for the advisor with ID #" << studAdvisor << endl;
            }

        } else {
            cerr << "ERROR: No student found in the databse with the ID: \"" << referenceId << "\"" << endl;
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

void Simulation::addNewFaculty(){
    unsigned int newFacultyId;
    string newName;
    string newLevel;
    string newDepartment;
    string tempStrValue;

    cout << "Creating a new faculty member. Please follow the following prompts." << endl;
    usleep(500000);
    cout << "New faculty member's ID:\n--->\t";
    getline(cin, tempStrValue);
    FileProcessor::isEmptyString(tempStrValue);
    try{
        newFacultyId = getValidId(tempStrValue);
        if (masterFaculty->contains(Faculty(newFacultyId))) {
            string s = "ERROR: Faculty member with the ID: \"" + to_string(newFacultyId) + "\" already exists in the database.";
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Terminating faculty member creation." << endl;
        usleep(1000000);
        return;
    }

    cout << "New faculty member's name:\n--->\t";
    getline(cin, newName);
    if (FileProcessor::isEmptyString(newName)) {
        cerr << "ERROR: Empty string provided for name.\nFailed to create faculty member." << endl;
        usleep(1000000);
        return;
    }
    removeCommas(newName);

    cout << "New faculty member's level:\n--->\t";
    getline(cin, newLevel);
    if (FileProcessor::isEmptyString(newLevel)) {
        cerr << "ERROR: Empty string provided for level.\nFailed to create faculty member." << endl;
        usleep(1000000);
        return;
    }
    removeCommas(newLevel);

    cout << "New faculty member's department:\n--->\t";
    getline(cin, newDepartment);
    if (FileProcessor::isEmptyString(newDepartment)) {
        cerr << "ERROR: Empty string provided for department.\nFailed to create faculty member." << endl;
        usleep(1000000);
        return;
    }
    removeCommas(newDepartment);

    try{
        Faculty f1(newFacultyId, newName, newLevel, newDepartment);
        masterFaculty->insert(f1);
        cout << "Success! Added a new faculty member with the following info:" << endl;
        cout << f1 << endl;
        ostringstream os; // rollback stuff
        os << "FacultyDelete: ";
        f1 >> os;
        rb->push(os.str());
    } catch (exception &e){
        cerr << "ERROR: Something went wrong when trying to create a new faculty member." << endl;
    }
    usleep(1000000);

}

void Simulation::deleteFaculty(){
    if (masterFaculty->isEmpty()) {
        cout << "Faculty database is empty. It wouldn't be possible to delete any faculty member from the database." << endl;
        usleep(1000000);
        return;
    }
    cout << "What is the ID of the faculty member that you would like to delete?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);
    unsigned int deletingFacultyId;
    try{
        deletingFacultyId = getValidId(tempStrValue);
        if (!masterFaculty->contains(Faculty(deletingFacultyId))) {
            string s = "ERROR: No faculty member found in the databse with the ID: \"" + to_string(deletingFacultyId) + "\"";
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    GenLinkedList<unsigned int> replaceAdvisors = masterFaculty->find(Faculty(deletingFacultyId))->getAllAdvisees();
    if (replaceAdvisors.getSize() == 0) {
        ostringstream os; // rollback stuff
        os << "FacultyAdd: ";
        *(masterFaculty->find(Faculty(deletingFacultyId))) >> os;
        rb->push(os.str());
        masterFaculty->deleteNode(Faculty(deletingFacultyId));
        cout << "Success! Deleted faculty member with ID #" << to_string(deletingFacultyId) << ". Since they have no dependent advisees, no students will be affected by this deletion." << endl;
        usleep(1000000);
        return;
    }

    cout << "Now that faculty member with ID #" << deletingFacultyId << " is going to be deleted, their advisees need a new advisor." << endl;
    cout << "What is the ID of the faculty member that you would like to replace all their advisees' advisor for?\n--->\t";
    getline(cin, tempStrValue);
    unsigned int newFacultyId;
    try{
        newFacultyId = getValidId(tempStrValue);
        if (deletingFacultyId == newFacultyId) {
            throw runtime_error("ERROR: The two faculty IDs that you inputted are the same.");
        }
        if (!masterFaculty->contains(Faculty(newFacultyId))) {
            string s = "ERROR: No faculty member found in the databse with the ID #" + to_string(newFacultyId) + " to replace faculty member with ID #" + to_string(deletingFacultyId);
            s += "\nWill not delete Faculty member with ID #" + to_string(deletingFacultyId);
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    for (int i = 0; i < replaceAdvisors.getSize(); ++i) {
        unsigned int tempId = *(replaceAdvisors.returnData(i));
        if (masterStudent->contains(Student(tempId))) {
            masterStudent->find(Student(tempId))->setAdvisorId(newFacultyId);
            int tempAdvisorId = masterStudent->find(Student(tempId))->getAdvisorId();
            masterFaculty->find(Faculty(tempAdvisorId))->addAdvisee(tempId);
        }
    }
    ostringstream os; // rollback stuff
    os << "FacultyAdd: ";
    *(masterFaculty->find(Faculty(deletingFacultyId))) >> os;
    rb->push(os.str());
    masterFaculty->deleteNode(Faculty(deletingFacultyId));
    cout << "Success! Deleted faculty member with ID #" << to_string(deletingFacultyId) << " and transfered their advisees to faculty member with ID #" << to_string(newFacultyId) << endl;
    usleep(1000000);
}

void Simulation::changeStudAdvisor(){
    if (masterStudent->isEmpty()) {
        cout << "Student database is empty. It wouldn't be possible to change any student's advisor, because there are no students in the database." << endl;
        usleep(1000000);
        return;
    }

    unsigned int studId;
    unsigned int studCurrAdvisor;
    unsigned int newFacultyId;

    cout << "What is the ID of the student who you would like to change advisor for?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);
    try{
        studId = getValidId(tempStrValue);
        if (!masterStudent->contains(Student(studId))) {
            throw runtime_error("ERROR: No student found with the ID #" + to_string(studId));
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }
    studCurrAdvisor = masterStudent->find(Student(studId))->getAdvisorId();
    cout << "Student with ID #" << studId << " currently has an advisor with ID #" << studCurrAdvisor << endl;

    cout << "What is the ID of the faculty member that you would like to replace the student's advisor for?\n--->\t";
    getline(cin, tempStrValue);
    try{
        newFacultyId = getValidId(tempStrValue);
        if (studCurrAdvisor == newFacultyId) {
            throw runtime_error("ERROR: The two faculty IDs that you inputted are the same.");
        }
        if (!masterFaculty->contains(Faculty(newFacultyId))) {
            string s = "ERROR: No faculty member found in the databse with the ID #" + to_string(newFacultyId); + "\" to replace faculty member with ID #" + to_string(studCurrAdvisor);
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    masterStudent->find(Student(studId))->setAdvisorId(newFacultyId);
    masterFaculty->find(Faculty(newFacultyId))->addAdvisee(studId);

    if (masterFaculty->contains(Faculty(studCurrAdvisor))) { // in case the student has a bad faculty ID
        masterFaculty->find(Faculty(studCurrAdvisor))->removeAdvisee(studId);
    }

    cout << "Successfully changed the advisor for student with ID #" << studId << " to the advisor with ID #" << newFacultyId << endl;

    usleep(1000000);
}

void Simulation::removeFacultyAdvisee(){
    if (masterStudent->isEmpty()) {
        cout << "Student database is empty, so it wouldn't be possible to remove any advisees from a given advisor" << endl;
        usleep(1000000);
        return;
    }

    string tempStrValue;
    unsigned int facultyId;
    unsigned int adviseeId;
    unsigned int newFacultyId;

    cout << "What is the ID of the faculty member that you would like to replace the student's advisor for?\n--->\t";
    getline(cin, tempStrValue);
    try{
        facultyId = getValidId(tempStrValue);
        if (!masterFaculty->contains(Faculty(facultyId))) {
            throw runtime_error("ERROR: No faculty member found in the databse with the ID #" + to_string(facultyId));
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    GenLinkedList<unsigned int> facAdvisees = masterFaculty->find(Faculty(facultyId))->getAllAdvisees();

    cout << "What is the ID of the advisee for this faculty member that you would like to remove?\n--->\t";
    getline(cin, tempStrValue);
    try{
        adviseeId = getValidId(tempStrValue);
        if (!masterStudent->contains(Student(adviseeId))) {
            throw runtime_error("ERROR: No student found in the database with the ID #" + to_string(adviseeId));
        }
        if (facAdvisees.find(adviseeId) < 0) {
            throw runtime_error("ERROR: Faculty member with ID #" + to_string(facultyId) + " has no advisee (student) with ID #" + to_string(adviseeId));
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    cout << "The advisee that was removed needs a new advisor as a replacement." << endl;
    cout << "What is the ID of the advisee's new advisor (faculty member)?\n--->\t";
    getline(cin, tempStrValue);
    try{
        newFacultyId = getValidId(tempStrValue);
        if (!masterFaculty->contains(Faculty(newFacultyId))) {
            throw runtime_error("ERROR: No faculty member found in the databse with the ID #" + to_string(newFacultyId));
        }
        if (newFacultyId == facultyId) {
            throw runtime_error("ERROR: The two faculty IDs that you inputted are the same.");
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    masterFaculty->find(Faculty(facultyId))->removeAdvisee(adviseeId);
    masterStudent->find(Student(adviseeId))->setAdvisorId(newFacultyId);
    masterFaculty->find(Faculty(newFacultyId))->addAdvisee(adviseeId);

    cout << "Successfully removed student with ID #" << adviseeId << " from the advisee list of faculty member with ID #" << facultyId << endl;
    cout << "The student got a new advisor with ID #" << newFacultyId << endl;
    usleep(1000000);

}

void Simulation::rollbackLastChange(){
    if (rb->isEmpty()) {
        cerr << "ERROR: Can't undo any more changes." << endl;
        cerr << "Maxmimum number of consecutive undos at a time is 5, and if less than 5 changes to the database have been made so far, it can only undo those changes" << endl;
        usleep(1000000);
        return;
    }
    string instruction = rb->pop();
    string operationType = FileProcessor::nextValueInString(instruction, ": ");
    if (operationType == "StudentDelete") {
        Student s1(instruction);
        masterFaculty->find(Faculty(s1.getAdvisorId()))->removeAdvisee(s1.getId());
        masterStudent->deleteNode(s1);
        cout << "Successfully undid the change of adding a student with ID #" << s1.getId() << endl;
    } else if (operationType == "StudentAdd") {
        Student s1(instruction);
        masterStudent->insert(s1);
        masterFaculty->find(Faculty(s1.getAdvisorId()))->addAdvisee(s1.getId());
        cout << "Successfully undid the change of deleting a student with ID #" << s1.getId() << endl;
    } else if (operationType == "FacultyDelete"){
        Faculty f1(instruction);
        masterFaculty->deleteNode(f1);
        cout << "Successfully undid the change of adding a faculty member with ID #" << f1.getId() << endl;
    } else if (operationType == "FacultyAdd"){
        Faculty f1(instruction);
        GenLinkedList<unsigned int> adviseesToUndo = f1.getAllAdvisees();
        masterFaculty->insert(f1);
        if (!adviseesToUndo.isEmpty()) {
            for (int i = 0; i < adviseesToUndo.getSize(); i++) {
                unsigned int tempAdviseeId = *(adviseesToUndo.returnData(i));
                unsigned int oldAdvisorId = masterStudent->find(Student(tempAdviseeId))->getAdvisorId();
                masterFaculty->find(Faculty(oldAdvisorId))->removeAdvisee(tempAdviseeId);
                masterStudent->find(Student(tempAdviseeId))->setAdvisorId(f1.getId());
            }
        }
        cout << "Successfully undid the change of deleting a faculty member with ID #" << f1.getId() << endl;
    }
    usleep(1000000);
}

void Simulation::saveAndQuit(){
    cout << "Saving changes and exiting program. Thank you." << endl;
    usleep(500000);
}

unsigned int Simulation::getValidId(string s){
    try{
        if (FileProcessor::isEmptyString(s)) {
            throw runtime_error("ERROR: No value for ID provided.");
        }
        int tempId = stoi(s);
        if (tempId <= 0) {
            throw runtime_error("ERROR: " + s + " is a zero or negative number.");
        }
        unsigned int referenceId = tempId;
        return referenceId;
    } catch (out_of_range &e){
        throw runtime_error("ERROR: " + s + " is too large to be an ID.");
    } catch (invalid_argument &e){
        throw runtime_error("ERROR: " + s + " is not a valid number.");
    } catch (runtime_error &e){
        throw runtime_error(e.what());
    }
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
