//
// Created by oppad on 11/10/2023.
//
#ifndef LIBRARY_SYSTEM_WITH_FILES_AUTHOR_H
#define LIBRARY_SYSTEM_WITH_FILES_AUTHOR_H
#include <iostream>
#include <cstring>
#define record_length 74
using namespace std;


class Author {
private:
    char ID[15];
    char Name[30];
    char Address[30];
public:
    Author(string id = "" , string name = "" , string address = "" );
    void Get_Id(char (&val)[]);
    void Get_Name(char (&val)[]);
    void Get_Address(char (&val)[]);
    void Set_Name(string val);
    void Set_Id(string id);
    void Set_Address(string address);

};


#endif //LIBRARY_SYSTEM_WITH_FILES_AUTHOR_H
