//
// Created by oppad on 11/10/2023.
//

#ifndef LIBRARY_SYSTEM_WITH_FILES_BOOK_H
#define LIBRARY_SYSTEM_WITH_FILES_BOOK_H
#include <iostream>
#include <cstring>
using namespace std;

class book {
private:
    char ISBN[15];
    char Book_Title[30];
    char Author_Id[15];
public:
    book(string isbn= "" , string title="" , string author_id = "");
    void Set_Isbn(string val);
    void Set_title(string val);
    void Set_Author_Id(string val);
    void Get_Isbn(char (&val)[]);
    void Get_Title(char (&val)[]);
    void Get_Author_id(char (&val)[]);

};


#endif //LIBRARY_SYSTEM_WITH_FILES_BOOK_H
