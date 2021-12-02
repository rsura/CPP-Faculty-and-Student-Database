/**
 * Implementation File: FileProcessor.cpp
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 5 (This file is from Assignment 4)
 */

#include "FileProcessor.h"

using namespace std;

/**
 * Default constructor
 */
FileProcessor::FileProcessor(){}

/**
 * Destructor
 */
FileProcessor::~FileProcessor(){
    if(fileReader.is_open()){
        fileReader.close();
    }
    if(fileWriter.is_open()){
        fileWriter.close();
    }
}

/**
 * Sets the read file name to the given string. If no such file exists, it throws an error
 *
 * @param string representing the file name (or file path if in a different folder)
 */
void FileProcessor::setReadFileName(string name){
    if(fileReader.is_open()){ // if there was another file being read before, it will close it
        fileReader.close();
    }
    readFileName = name;
    fileReader.open(name);
    if(!fileReader.is_open()){ // if file doesn't exist
        string errorMessage = "ERROR: No file found with the name of \"" + readFileName + "\"\n";
        errorMessage += "Please check if the file is in the wrong directory, has the proper reading permissions or if you have provided the extension for the file name";
        throw runtime_error(errorMessage);
    }
}

/**
 * Sets the write file name to the given string. If it's unable to create such file
 * for some reason, then it will throw an error
 *
 * @param string representing the file name (or file path if in a different folder)
 */
void FileProcessor::setWriteFileName(string name){
    if(fileWriter.is_open()){ // if there was another file being written to before, it will close it
        fileWriter.close();
    }
    writeFileName = name;
    fileWriter.open(name);
    if(!fileWriter.is_open()){
        string errorMessage = "ERROR: Unable to create a file named \"" + writeFileName + "\"\n";
        throw runtime_error(errorMessage);
    }
}

/**
 * Gets the next line in the file from the read file name to the given string. If it's unable to create such file
 * for some reason, then it will throw an error
 *
 * @return string representing the next line in the read in file
 */
string FileProcessor::getNextLine(){
    if(!fileReader.is_open()){ // if file doesn't exist
        string errorMessage = "ERROR: No file name was provided to read from";
        throw runtime_error(errorMessage);
    }
    string line;
    if (!fileReader.eof()){ // if the file is not at the end, get the line
        getline(fileReader, line);
        return line;
    }
    if(fileReader.is_open()){ // closes the file reader if the file has reached the end
        fileReader.close();
    }
    throw runtime_error("ERROR: File has reached the end!");
}

/**
 * Writes a new string in the write file without going to the next line. If the
 * write file hasn't been declared to be opened, then it will throw an error
 *
 * @param string representing what to add to the file
 */
void FileProcessor::write(string line){
    if(!fileWriter.is_open()){ // if file hasn't been created
        string errorMessage = "ERROR: No file name was provided to write to";
        throw runtime_error(errorMessage);
    }
    fileWriter << line;
}

/**
 * Writes a new string in the write file and goes to the next line. If the
 * write file hasn't been declared to be opened, then it will throw an error
 *
 * @param string representing what to add to the file
 */
void FileProcessor::writeLine(string line){
    if(!fileWriter.is_open()){ // if file hasn't been created
        string errorMessage = "ERROR: No file name was provided to write to";
        throw runtime_error(errorMessage);
    }
    fileWriter << line << endl;
}

/**
 * Checks if the string passed in is empty or not. Trims the string of leading
 * and trailing spaces because it's passed by reference.
 *
 * @param a string (passed by reference) containing the content
 * @return boolean representing if the string was empty (it is still empty if it contained spaces and tabs)
 */
bool FileProcessor::isEmptyString(string& name){
    int len = name.length();
    while(name[0] == ' ' || name[0] == '\t'){ // trims beginning of the string's spaces
        name = name.substr(1,len);
        --len;
    }

    if (len <= 0) {
        return true;
    }

    while(name[len - 1] == ' ' || name[len - 1] == '\t'){ // trims beginning of the string's spaces
        name = name.substr(0,len - 1);
        --len;
    }

    return len <= 0;
}

/**
 * Returns the next value in a string before a delimiter. Modifies the passed string by reference
 * from the first delimiter onwards and returns the first part of the string.
 *
 * @param string with delimiters
 * @param string representing the delimiter
 * @return a string representing the next value of the string before the delimiter
 */
string FileProcessor::nextValueInString(string& s, string delimiter){
    isEmptyString(s); // trims trailing and leading spaces
    int index = -1;
    for (int i = 0; i < (s.length() - delimiter.length()); i++) {
        if (s.substr(i, delimiter.length()) == delimiter) {
            index = i;
            break;
        }
    }
    if (index > -1) {
        string nextValue = s.substr(0,index);
        s = s.substr(nextValue.length() + delimiter.length());
        isEmptyString(nextValue);
        return nextValue;
    }

    string nextValue = s;
    s = "";
    return nextValue;
}

/**
 * Checks if the file being read from has reached the end. If the
 * read file hasn't been declared to be opened, then it will throw an error
 *
 * @return boolean representing if the file reached the end
 */
bool FileProcessor::eof(){
    if(!fileReader.is_open()){ // if file doesn't exist
        string errorMessage = "ERROR: No file name was provided to read from, and hence, can't check if the file has reached the end";
        throw runtime_error(errorMessage);
    }
    return fileReader.eof(); // uses the built in end of file function
}
