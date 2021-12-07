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

/**
 * Default constructor - creates a new simulation
 */
Simulation::Simulation(){
    masterStudent = new BST<Student>();
    masterFaculty = new BST<Faculty>();
    rb = new Rollback<string>(5); // rollback of last 5 operations
}

/**
 * Destructor
 */
Simulation::~Simulation(){
    delete masterStudent;
    delete masterFaculty;
    delete rb;
}

/**
 * Runs the simulation with all the 15 options, including saving and quitting as
 * well as quitting without saving any changes
 */
void Simulation::run(){
    setUp();
    bool exit = false;
    string selectedOption;
    string validation;
    int optionNumber;
    while(!exit){
        displayOptions();
        getline(cin, selectedOption);
        if (FileProcessor::isEmptyString(selectedOption)) { // empty option selected
            cerr << "ERROR: No input. Instructions will be repeated again." << endl;
            usleep(1000000);
            continue;
        } else {
            try{ // selected option number found from stoi()
                optionNumber = stoi(selectedOption);
            } catch (exception &e) { // if some error happened, the user will just redo
                cerr << "ERROR: Not a valid way of writing an option. Instructions will be repeated again." << endl;
                continue;
            }
            try{
                switch (optionNumber) { // all the possible options
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
                        saveAndQuit();
                        exit = true;
                        break;
                    case 15: // added a exit without saving option, in case the user was just messing around
                        cout << "Are you sure you want to quit without saving changes? Type \"YES\" in all CAPS to confirm this, or type anything else to continue the program.\n--->\t";
                        getline(cin, validation);
                        if (validation == "YES") {
                            exit = true;
                            cout << "Exiting the program without saving changes..." << endl;
                        } else {
                            cout << "Continuing the program. Your changes to the database are still intact." << endl;
                        }
                        usleep(1000000);
                        break;
                    default:
                        cerr << "ERROR: Not a valid option number. Instructions will be repeated again." << endl;
                        usleep(1000000);
                        break;
                }
            } catch (exception &e){ // if any method throws an error that I didn't handle, it will be caught
                cerr << "ERROR: An unkown error occurred. Instructions will be repeated." << endl;
            }
        }
    }
}

/**
 * Sets everything up with reading the student and faculty database files
 */
void Simulation::setUp(){
    cout << "\nHello there! Welcome to the Student and Faculty Database Program!" << endl;
    usleep(1000000);
    cout << "Currently reading from existing database files..." << endl;
    usleep(500000);

    FileProcessor *fp = new FileProcessor();
    try{ // reading master faculty database
        fp->setReadFileName("facultyTable");
        while (!fp->eof()) {
            string fileLine = fp->getNextLine();
            if (fp->isEmptyString(fileLine)) {
                continue;
            }
            try{ // creating faculty member if not already in database
                Faculty f1(fileLine);
                if (!masterFaculty->contains(f1)) {
                    masterFaculty->insert(f1);
                }
            } catch (runtime_error &e){
                cerr << "ERROR: Failed to create faculty member from this line:\n\t\"" << fileLine << "\"" << endl;
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
            try{ // creating student if not already in database and their advisor is in the database
                Student s1(fileLine);
                if (!masterStudent->contains(s1)) {
                    if (masterFaculty->contains(Faculty(s1.getAdvisorId()))) {
                        masterStudent->insert(s1);
                        (masterFaculty->find(Faculty(s1.getAdvisorId())))->addAdvisee(s1.getId());
                    } else {
                        throw runtime_error("ERROR: No faculty member in database with ID #" + to_string(s1.getAdvisorId()));
                    }
                }
            } catch (runtime_error &e){
                cerr << "ERROR: Failed to create student from this line:\n\t\"" << fileLine << "\"\n\t-> Reason: " << e.what() << endl;
            }
        }
    } catch (runtime_error &e){
        // fail quietly. Student database doesn't exist yet, and that's ok
    }
    delete fp;
    usleep(500000);
}

/**
 * Displays all the possible options for the program. There are 15 in all, and 2
 * of the options can exit the program (other than hitting ctrl c)
 */
void Simulation::displayOptions(){
     // The sleeping in between is so that a huge block of text isn't being printed all at once
     // The same reason goes for all the other sleep functions throughout this Simulation
    long pauseTimeBtwn = 500000 / 16;
    cout << "Here are the possible options for interacting with the database:" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t1.  🖨️  Print all students and their information (sorted by ascending id #)" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t2.  🖨️  Print all faculty and their information (sorted by ascending id #)" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t3.  🖨️  Find and display student information given the students id" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t4.  🖨️  Find and display faculty information given the faculty id" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t5.  🖨️  Given a student’s id, print the name and info of their faculty advisor" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t6.  🖨️  Given a faculty id, print ALL the names and info of his/her advisees." << endl;
    usleep(pauseTimeBtwn);
    cout << "\t7.  ➕ Add a new student" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t8.  ↩️  Delete a student given the id" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t9.  ➕ Add a new faculty member" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t10. ↩️  Delete a faculty member given the id." << endl;
    usleep(pauseTimeBtwn);
    cout << "\t11. 🔃 Change a student’s advisor given the student id and the new faculty id." << endl;
    usleep(pauseTimeBtwn);
    cout << "\t12. ↩️  Remove an advisee from a faculty member given the ids" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t13. 🔄 Undo last change" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t14. 💾 Save and quit" << endl;
    usleep(pauseTimeBtwn);
    cout << "\t15. ❗ Quit without saving changes" << endl;
    usleep(pauseTimeBtwn);
    cout << "Please type the number corresponding to the option that you would like to choose:" << endl;
    cout << "--->\t";
}

/**
 * Prints all the students in ascending order by ID. ID doesn't represent any hierarchy
 * for order, but is just a way to order the students. If the student database is empty
 * it will print a message stating that it's empty.
 */
void Simulation::printAllStudents(){
    if (masterStudent->isEmpty()) { // nothing to print in the student database
        cout << "Student database is empty. Nothing to print." << endl;
        usleep(1000000);
        return;
    }

    cout << "Printing information of all students..." << endl;
    usleep(500000);
    masterStudent->printNodes();
    usleep(1000000);
}

/**
 * Prints all the faculty in ascending order by ID. ID doesn't represent any hierarchy
 * for order, but is just a way to order the faculty members. If the faculty database
 * is empty it will state that the faculty database is empty.
 */
void Simulation::printAllFaculty(){
    if (masterFaculty->isEmpty()) { // nothing to print in the faculty database
        cout << "Faculty database is empty. Nothing to print." << endl;
        usleep(1000000);
        return;
    }

    cout << "Printing information of all faculty members..." << endl;
    usleep(500000);
    masterFaculty->printNodes();
    usleep(1000000);
}

/**
 * Prints the info of a certain student given their ID. If the student database is
 * empty or there doesn't exist a student with the entered ID, it will state that,
 * but the error is handled.
 */
void Simulation::printStudent(){
    if (masterStudent->isEmpty()) { // saves the trouble of trying to print a student's info if database is empty for it
        cout << "Student database is empty. It wouldn't be possible to print any student's information." << endl;
        usleep(1000000);
        return;
    }

    cout << "What is the ID of the student that you would like to print?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);

    try{
        unsigned int referenceId = getValidId(tempStrValue);
        if (masterStudent->contains(Student(referenceId))) { // prints only if the student exists and error if doesn't exist
            cout << *(masterStudent->find(Student(referenceId))) << endl;
        } else {
            cerr << "ERROR: No student found with the ID #" << referenceId << endl;
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

/**
 * Prints the info of a certain faculty member given their ID. If the faculty database
 * is empty or there doesn't exist a faculty member with the entered ID, it will
 * state that, but the error is handled.
 */
void Simulation::printFaculty(){
    if (masterFaculty->isEmpty()) { // saves the trouble of trying to print a faculty member's info if database is empty for it
        cout << "Faculty database is empty. It wouldn't be possible to print any faculty member's information." << endl;
        usleep(1000000);
        return;
    }

    cout << "What is the ID of the faculty member that you would like to print?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);

    try{
        unsigned int referenceId = getValidId(tempStrValue);
        if (masterFaculty->contains(Faculty(referenceId))) { // prints only if the student exists and error if doesn't exist
            cout << *(masterFaculty->find(Faculty(referenceId))) << endl;
        } else {
            cerr << "ERROR: No faculty member found with the ID #" << referenceId << endl;
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

/**
 * Prints the info of a certain faculty member given the student's ID. If the student
 * doesn't exist in the database, it will state that, but the error is handled.
 */
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

        if (masterStudent->contains(Student(referenceId))) { // prints student's advisor if the student exists
            unsigned int advisorId = (masterStudent->find(Student(referenceId)))->getAdvisorId();

            // prints student's advisor if the student's advisor exists
            if (masterFaculty->contains(Faculty(advisorId))) {
                cout << "Printing the advisor info of the student with ID #" << referenceId << endl;
                usleep(500000);
                cout << *(masterFaculty->find(Faculty(advisorId))) << endl;
            } else { // shouldn't happen if program is used properly, but there in case
                throw runtime_error("ERROR: Student's advisor doesn't exist in the faculty database.");
            }
        } else {
            cerr << "ERROR: No student found with the ID #" << referenceId << endl;
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

/**
 * Prints the info of all advisees of a certain faculty member given the faculty
 * member's ID. If the faculty member doesn't exist in the database or the faculty
 * member has no advisees, it will state that, but the error is handled.
 */
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
            if (advisees.getSize() == 0) { // not an error, but will leave the try block
                throw runtime_error("This faculty member has no advisees. Nothing will be printed.");
            }
            cout << "Printing info of all advisees of faculty member with ID #" << referenceId << endl;
            usleep(500000);

            // iterates through the advisee list and finds their data from the bst to print
            for (int i = 0; i < advisees.getSize(); ++i) {
                unsigned int studId = *(advisees.returnData(i));
                if (masterStudent->contains(Student(studId))) { // prints if student exists
                    cout << *(masterStudent->find(Student(studId))) << endl;
                } else { // removes from advisee list if student doesn't exist anymore for some reason
                    masterFaculty->find(Faculty(referenceId))->removeAdvisee(studId);
                }
            }
        } else {
            cerr << "ERROR: No faculty member found with the ID #" << referenceId << endl;
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

/**
 * Creates a new student from given prompts of their advisor id, their own id,
 * their name, level, major, and GPA. If the student with the inputted ID already
 * exists in the database, it will exit the method.
 */
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

    // prompting ID of the student's advisor, since it is a dependent field
    cout << "What is the ID of the advisor that this student is going to be under?\n--->\t";
    getline(cin, tempStrValue);
    FileProcessor::isEmptyString(tempStrValue);
    try{
        newFacultyId = getValidId(tempStrValue);
        if (!masterFaculty->contains(Faculty(newFacultyId))) {
            string s = "ERROR: No faculty member with the ID #" + to_string(newFacultyId) + " found in the database.";
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Terminating student creation." << endl;
        usleep(1000000);
        return;
    }

    // prompting student's ID
    cout << "New student's ID:\n--->\t";
    getline(cin, tempStrValue);
    FileProcessor::isEmptyString(tempStrValue);
    try{
        newStudId = getValidId(tempStrValue);
        if (masterStudent->contains(Student(newStudId))) {
            string s = "ERROR: Student with the ID #" + to_string(newStudId) + " already exists in the database.";
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Terminating student creation." << endl;
        usleep(1000000);
        return;
    }

    // string fields are removing commas and leading and trailing spaces because
    // they would not be ideal when storing and reading in a CSV format

    cout << "New student's name:\n--->\t";
    getline(cin, newName);
    removeCommas(newName);
    if (FileProcessor::isEmptyString(newName)) {
        cerr << "ERROR: Empty string provided for name.\nFailed to create student." << endl;
        usleep(1000000);
        return;
    }

    cout << "New student's level:\n--->\t";
    getline(cin, newLevel);
    removeCommas(newLevel);
    if (FileProcessor::isEmptyString(newLevel)) {
        cerr << "ERROR: Empty string provided for level.\nFailed to create student." << endl;
        usleep(1000000);
        return;
    }

    cout << "New student's major:\n--->\t";
    getline(cin, newMajor);
    removeCommas(newMajor);
    if (FileProcessor::isEmptyString(newMajor)) {
        cerr << "ERROR: Empty string provided for major.\nFailed to create student." << endl;
        usleep(1000000);
        return;
    }

    cout << "New student's GPA:\n--->\t";
    getline(cin, tempStrValue);
    try{
        newGpa = stod(tempStrValue);
        if (newGpa < 0 || newGpa > 4.0) { // range check for GPA
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
        masterFaculty->find(Faculty(newFacultyId))->addAdvisee(newStudId); // adds advisee to the faculty member when student got created
        ostringstream os; // rollback stuff
        os << "StudentDelete: ";
        s1 >> os;
        rb->push(os.str());
    } catch (exception &e){
        cerr << "ERROR: Something went wrong when trying to create a new faculty member." << endl;
    }
    usleep(1000000);
}

/**
 * Deletes a student from given prompt of the student to-be-deleted's id. If there
 * is no student with the inputted ID in the database, it will delete nothing. If
 * the student database itself is empty, it will state that you can't delete any
 * more students
 */
void Simulation::deleteStudent(){
    if (masterStudent->isEmpty()) { // can't delete if there are no students
        cout << "Student database is empty. It wouldn't be possible to delete any student from the database." << endl;
        usleep(1000000);
        return;
    }
    cout << "What is the ID of the student that you would like to delete?\n--->\t";
    string tempStrValue;
    getline(cin, tempStrValue);
    try{
        unsigned int referenceId = getValidId(tempStrValue);
        if (masterStudent->contains(Student(referenceId))) { // deletes the student if they exist in the database
            Student s1 = *(masterStudent->find(Student(referenceId)));
            unsigned int studAdvisor = s1.getAdvisorId();

            ostringstream os; // rollback stuff
            os << "StudentAdd: ";
            s1 >> os;
            rb->push(os.str());

            masterStudent->deleteNode(Student(referenceId));
            cout << "Success! Deleted the student with ID #" << referenceId << endl;
            usleep(500000);
            if (masterFaculty->contains(Faculty(studAdvisor))) { // referential integrity
                masterFaculty->find(Faculty(studAdvisor))->removeAdvisee(referenceId);
                cout << "Also, removed the student from the list of the advisees for the advisor with ID #" << studAdvisor << endl;
            }

        } else {
            cerr << "ERROR: No student found in the database with the ID #" << referenceId << endl;
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
    }
    usleep(1000000);
}

/**
 * Creates a new faculty member from given prompts of their own id, name, level,
 * major, and GPA. If the faculty member with the inputted ID already exists in
 * the database, it will exit the method.
 */
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
    FileProcessor::isEmptyString(tempStrValue); // trims trailing and leading spaces

    try{
        newFacultyId = getValidId(tempStrValue);
        if (masterFaculty->contains(Faculty(newFacultyId))) {
            string s = "ERROR: Faculty member with the ID #" + to_string(newFacultyId) + " already exists in the database.";
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        cerr << "Terminating faculty member creation." << endl;
        usleep(1000000);
        return;
    }

    // string fields are removing commas and leading and trailing spaces because
    // they would not be ideal when storing and reading in a CSV format

    cout << "New faculty member's name:\n--->\t";
    getline(cin, newName);
    removeCommas(newName);
    if (FileProcessor::isEmptyString(newName)) {
        cerr << "ERROR: Empty string provided for name.\nFailed to create faculty member." << endl;
        usleep(1000000);
        return;
    }

    cout << "New faculty member's level:\n--->\t";
    getline(cin, newLevel);
    removeCommas(newLevel);
    if (FileProcessor::isEmptyString(newLevel)) {
        cerr << "ERROR: Empty string provided for level.\nFailed to create faculty member." << endl;
        usleep(1000000);
        return;
    }

    cout << "New faculty member's department:\n--->\t";
    getline(cin, newDepartment);
    removeCommas(newDepartment);
    if (FileProcessor::isEmptyString(newDepartment)) {
        cerr << "ERROR: Empty string provided for department.\nFailed to create faculty member." << endl;
        usleep(1000000);
        return;
    }

    // doesn't prompt for any advisees, since as the program continues, it's being handled

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

/**
 * Deletes a faculty member from given prompts the faculty member to-be-deleted's
 * id. If there is no faculty member with the inputted ID in the database, it will
 * delete nothing. If the faculty member database itself is empty, it will state
 * that you can't delete any more students.
 */
void Simulation::deleteFaculty(){
    if (masterFaculty->isEmpty()) { // can't delete faculty if there isn't any faculty member
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
        if (!masterFaculty->contains(Faculty(deletingFacultyId))) { // can't delete a faculty member without the id
            string s = "ERROR: No faculty member found in the database with the ID #" + to_string(deletingFacultyId);
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    GenLinkedList<unsigned int> replaceAdvisors = masterFaculty->find(Faculty(deletingFacultyId))->getAllAdvisees();
    if (replaceAdvisors.getSize() == 0) {
        ostringstream os; // rollback stuff if advisor has no advisees
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
    try{ // replacement advisor
        newFacultyId = getValidId(tempStrValue);
        if (deletingFacultyId == newFacultyId) {
            throw runtime_error("ERROR: The two faculty IDs that you inputted are the same.");
        }
        if (!masterFaculty->contains(Faculty(newFacultyId))) {
            string s = "ERROR: No faculty member found in the database with the ID #" + to_string(newFacultyId) + " to replace faculty member with ID #" + to_string(deletingFacultyId);
            s += "\nWill not delete Faculty member with ID #" + to_string(deletingFacultyId);
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    for (int i = 0; i < replaceAdvisors.getSize(); ++i) { // iterates through to replace the students' advisor with another
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

/**
 * Changes a student's advisor from the given prompts the ID of the student who
 * wants to change their advisor and the ID of the new advisor that they want to
 * change to.
 */
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

    try{ // student's id
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

    try{ // replacement student advisor
        newFacultyId = getValidId(tempStrValue);
        if (studCurrAdvisor == newFacultyId) {
            throw runtime_error("ERROR: The two faculty IDs that you inputted are the same.");
        }
        if (!masterFaculty->contains(Faculty(newFacultyId))) {
            string s = "ERROR: No faculty member found in the database with the ID #" + to_string(newFacultyId); + "\" to replace faculty member with ID #" + to_string(studCurrAdvisor);
            throw runtime_error(s);
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    ostringstream os; // extra credit rollback stuff
    os << "StudAdvisorChnge: ";
    *(masterStudent->find(Student(studId))) >> os;
    rb->push(os.str());

    masterStudent->find(Student(studId))->setAdvisorId(newFacultyId);
    masterFaculty->find(Faculty(newFacultyId))->addAdvisee(studId);

    if (masterFaculty->contains(Faculty(studCurrAdvisor))) { // in case the student has a bad faculty ID, somehow
        masterFaculty->find(Faculty(studCurrAdvisor))->removeAdvisee(studId);
    }

    cout << "Successfully changed the advisor for student with ID #" << studId << " to the advisor with ID #" << newFacultyId << endl;

    usleep(1000000);
}

/**
 * Removes an advisee from the list of advisees from the prompted faculty ID and
 * student ID. Since the student has no advisor, after being removed, it needs a
 * new advisor, and the user is prompted to provide a valid faculty member ID other
 * than the one they typed earlier to let the change happen. Same functionality as
 * the changeStudAdvisor() method, but order of the prompts are different
 */
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

    cout << "What is the ID of the faculty member that you would like to delete an advisee for?\n--->\t";
    getline(cin, tempStrValue);

    try{ // advisor id that wants to remove an advisee
        facultyId = getValidId(tempStrValue);
        if (!masterFaculty->contains(Faculty(facultyId))) {
            throw runtime_error("ERROR: No faculty member found in the database with the ID #" + to_string(facultyId));
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    GenLinkedList<unsigned int> facAdvisees = masterFaculty->find(Faculty(facultyId))->getAllAdvisees();

    cout << "What is the ID of the advisee for this faculty member that you would like to remove?\n--->\t";
    getline(cin, tempStrValue);

    try{ // advisee id to remove from advisor list
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

    try{ // replacement advisor for that student
        newFacultyId = getValidId(tempStrValue);
        if (!masterFaculty->contains(Faculty(newFacultyId))) {
            throw runtime_error("ERROR: No faculty member found in the database with the ID #" + to_string(newFacultyId));
        }
        if (newFacultyId == facultyId) {
            throw runtime_error("ERROR: The two faculty IDs that you inputted are the same.");
        }
    } catch (runtime_error &e){
        cerr << e.what() << endl;
        usleep(1000000);
        return;
    }

    ostringstream os; // extra credit rollback stuff
    os << "AddAdviseeBack: ";
    *(masterStudent->find(Student(adviseeId))) >> os;
    rb->push(os.str());

    masterFaculty->find(Faculty(facultyId))->removeAdvisee(adviseeId);
    masterStudent->find(Student(adviseeId))->setAdvisorId(newFacultyId);
    masterFaculty->find(Faculty(newFacultyId))->addAdvisee(adviseeId);

    cout << "Successfully removed student with ID #" << adviseeId << " from the advisee list of faculty member with ID #" << facultyId << endl;
    cout << "The student got a new advisor with ID #" << newFacultyId << endl;
    usleep(1000000);
}

/**
 * Undoes the last 5 changes that modified the BST, including adding/deleting a
 * faculty member or student, changing a student's advisor, and removing a faculty
 * member's advisee. If more than 5 changes have been undone or there haven't been
 * enough changes to the BST to undo, it will tell the user that there's nothing
 * else to undo.
 */
void Simulation::rollbackLastChange(){
    if (rb->isEmpty()) { // can't undo more than 5 changes or if there isn't many changes, can't undo that
        cerr << "ERROR: Can't undo any more changes." << endl;
        cerr << "Maxmimum number of consecutive undos at a time is 5, and if less than 5 changes to the database have been made so far, it can only undo those changes" << endl;
        usleep(1000000);
        return;
    }
    string instruction = rb->pop();
    string operationType = FileProcessor::nextValueInString(instruction, ": ");
    // the operation to do is the opposite of what happened (in the string of operationType)
    if (operationType == "StudentDelete") { // undoing the add student
        Student s1(instruction);
        masterFaculty->find(Faculty(s1.getAdvisorId()))->removeAdvisee(s1.getId());
        masterStudent->deleteNode(s1);
        cout << "Successfully undid the change of adding a student with ID #" << s1.getId() << endl;
    } else if (operationType == "StudentAdd") { // undoing the delete student
        Student s1(instruction);
        masterStudent->insert(s1);
        masterFaculty->find(Faculty(s1.getAdvisorId()))->addAdvisee(s1.getId());
        cout << "Successfully undid the change of deleting a student with ID #" << s1.getId() << endl;
    } else if (operationType == "FacultyDelete"){ // undoing the add faculty
        Faculty f1(instruction);
        masterFaculty->deleteNode(f1);
        cout << "Successfully undid the change of adding a faculty member with ID #" << f1.getId() << endl;
    } else if (operationType == "FacultyAdd"){ // undoing the delete faculty
        Faculty f1(instruction);
        for (int i = 0; i < 4; ++i) { // removes everything, but the advisee list from the instruction
            FileProcessor::nextValueInString(instruction, ",");
        }
        GenLinkedList<unsigned int> adviseesToUndo;
        while (instruction != "") {
            try{
                adviseesToUndo.insertBack(stoi(FileProcessor::nextValueInString(instruction, ",")));
            } catch (exception &e){
                cerr << "ERROR: No student" << endl;
            }
        }
        masterFaculty->insert(f1);
        if (!adviseesToUndo.isEmpty()) {
            for (int i = 0; i < adviseesToUndo.getSize(); ++i) {
                unsigned int tempAdviseeId = *(adviseesToUndo.returnData(i));
                unsigned int oldAdvisorId = masterStudent->find(Student(tempAdviseeId))->getAdvisorId();
                masterFaculty->find(Faculty(oldAdvisorId))->removeAdvisee(tempAdviseeId);
                masterStudent->find(Student(tempAdviseeId))->setAdvisorId(f1.getId());
                masterFaculty->find(Faculty(f1.getId()))->addAdvisee(tempAdviseeId);
            }
        }
        cout << "Successfully undid the change of deleting a faculty member with ID #" << f1.getId() << " and added the students back to that advisor" << endl;
    }
    // undoing the change of student advisor or removing an advisee from an advisor
    else if (operationType == "StudAdvisorChnge" || operationType == "AddAdviseeBack") {
        Student s1(instruction);
        Student *stud = masterStudent->find(s1);
        masterFaculty->find(Faculty(stud->getAdvisorId()))->removeAdvisee(s1.getId());
        stud->setAdvisorId(s1.getAdvisorId());
        masterFaculty->find(Faculty(s1.getAdvisorId()))->addAdvisee(s1.getId());
        if (operationType == "StudAdvisorChnge") {
            cout << "Successfully undid the change of changing the advisor for the student with ID #" << s1.getId() << endl;
        } else {
            cout << "Successfully undid the change of removing an advisee for the faculty member with ID #" << masterFaculty->find(Faculty(s1.getAdvisorId()))->getId() << endl;
        }
    } else { // if it somehow doesn't work
        cerr << "ERROR: Invalid operation type" << endl;
    }
    usleep(1000000);
}

/**
 * Saves the program into the corresponding database files and quits the program
 * gracefully. There is also another option in the simulation that quits without
 * saving changes, and nothing from the BST is modified.
 */
void Simulation::saveAndQuit(){
    FileProcessor *fp = new FileProcessor();

    // gets the preorder nodes of the students, so that the bst structure remains intact
    GenLinkedList<Student*>* saveStudents = masterStudent->getPreOrderNodes();
    ostringstream studentsFile;
    for (int i = 0; i < saveStudents->getSize(); ++i) {
        *(saveStudents->returnData(i)) >> studentsFile; // overloaded operator for file input
    }
    fp->setWriteFileName("studentTable");
    fp->write(studentsFile.str());

    // gets the preorder nodes of the faculty, so that the bst structure remains intact
    GenLinkedList<Faculty*>* saveFaculty = masterFaculty->getPreOrderNodes();
    ostringstream facultyFile;
    for (int i = 0; i < saveFaculty->getSize(); ++i) {
        *(saveFaculty->returnData(i)) >> facultyFile; // overloaded operator for file input
    }
    fp->setWriteFileName("facultyTable");
    fp->write(facultyFile.str());

    delete fp;

    cout << "Saving changes and exiting program. Thank you." << endl;
    usleep(1000000);
}

/**
 * Gets a valid ID from a string input. It removes any commas for std::stoi() to
 * properly function. Throws a runtime_error if any of the following conditions
 * are true: the string provided is empty or unidentifiable as a number, the value
 * is 0 or negative (which is not valid for an ID number), or the number is too
 * large to be an ID, which should ideally be 7 or 8 numbers at most.
 */
unsigned int Simulation::getValidId(string s){
    removeCommas(s); // removes commas, like if a number is 1,234,567
    try{
        if (FileProcessor::isEmptyString(s)) { // no input
            throw runtime_error("ERROR: No value for ID provided.");
        }
        int tempId = stoi(s);
        if (tempId <= 0) { // zero or negative number
            throw runtime_error("ERROR: " + s + " is a zero or negative number.");
        }
        unsigned int referenceId = tempId;
        return referenceId;
    } catch (out_of_range &e){ // not in scope of int
        throw runtime_error("ERROR: " + s + " is too large to be an ID.");
    } catch (invalid_argument &e){ // giberrish that's not numbers
        throw runtime_error("ERROR: " + s + " is not a valid number.");
    } catch (runtime_error &e){ // throws a runtime_error out of these four possibilities
        throw runtime_error(e.what());
    }
}

/**
 * Helper function - removes commas in a string passed by reference
 *
 * @param any string. If the string has no commas, nothing will be modified
 */
void Simulation::removeCommas(string& s){
    for (int i = 0; i < s.length(); ++i) { // remove potential commas in the string, since db stores it as csv
        if (s[i] == ',') {
            s = s.substr(0,i) + s.substr(i+1);
        }
    }
}
