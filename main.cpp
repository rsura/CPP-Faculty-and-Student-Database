/**
 * Main Implementation File: main.cpp
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
 * This main method creates an interaction between a user and a database of students and
 * faculty members. The database saves to a file for future use, and is read from at the
 * beginning of the program to continue to interact with.
 *
 * @param Command line parameters, separated by a space
 * @return Exit code (1 if something went wrong, 0 if program executed smoothly)
 */
int main(int argc, char **argv) {
    Simulation *sm = new Simulation();
    sm->run();
    delete sm;

    return 0;
}