# CPSC350_FA21_ASSIGNMENT6_SURA

1)  Identifying	information:
    - Full Name: Rahul Sura
    - Student ID: 2371308
    - Student Email: sura@chapman.edu
    - Course: CPSC 350-03
    - Assignment: Assignment 6

2)  Source Files:
    - bst.h
    - GenLinkedList.h
    - Rollback.h
    - Student.h
    - Student.cpp
    - Faculty.h
    - Faculty.cpp
    - FileProcessor.h
    - FileProcessor.cpp
    - Simulation.h
    - Simulation.cpp
    - main.cpp
    - Sample Database Files to work with the program:
        - studentTable
        - facultyTable

3) Known compile or runtime errors:
    - If you initialize the BST or the GenLinkedList with a pointer, comparison won't work properly. Since the nodes for each data structure are already pointers, store using objects, not pointers only, properly. If you want, you can pass in dereferenced data to the BST or just data created on the stack, since the nodes are like wrapping containers for each data structure.
    - Extra Credit: Implemented rollback for removing advisee and changing advisor

4) References:
    - Bounced ideas of how to setup this project with Shree Murthy and go about operator overloading and function creation of this simulation, including certain implementations of code
    - https://www.daniweb.com/programming/software-development/threads/40763/must-take-exactly-one-argument#post195846
    - https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
    - https://learn.zybooks.com/zybook/CHAPMANCPSC298GermanWinter2021/chapter/9/section/2
    - https://en.cppreference.com/w/cpp/types/is_pointer
    - http://www.cplusplus.com/reference/iomanip/resetiosflags/
    - https://www.programmerall.com/article/83961878333/
    - https://www.fluentcpp.com/2018/07/13/the-incredible-const-reference-that-isnt-const/
    - https://stackoverflow.com/questions/10982874/prevent-changes-to-object-returned-as-a-pointer

5) Instructions:
    - Instructions for running the assignment:
        - make all
        - ./assignment6.out

    - Instructions for removing the executable file:
        - make realclean