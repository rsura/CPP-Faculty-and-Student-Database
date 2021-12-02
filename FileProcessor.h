/**
 * Header File: FileProcessor.h
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 5 (This file is from Assignment 4)
 */

#ifndef FILEPROCESSOR_H // header guards
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>

using namespace std;

class FileProcessor{
    public:
        FileProcessor();
        ~FileProcessor();
        void setReadFileName(string name); // for reading files
        void setWriteFileName(string name); // for writing files
        string getNextLine();
        void write(string line); // printing a string to the file without going to the next line
        void writeLine(string line); // printing a string to the file
        bool isEmptyString(string& name); // if the string taken is empty
        string nextValueInString(string& s, string delimiter);
        bool eof(); // if the file has reached the end
    private:
        string readFileName;
        string writeFileName;
        ifstream fileReader;
        ofstream fileWriter;
};

#endif
