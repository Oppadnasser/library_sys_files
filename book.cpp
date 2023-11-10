//
// Created by oppad on 11/10/2023.
//

#include "book.h"

book::book(string isbn, string title, string author_id) {
    strcpy(ISBN , isbn.c_str());
    strcpy(Book_Title , title.c_str());
    strcpy(Author_Id , author_id.c_str());
}

void book::Set_Isbn(string val) {
    strcpy(ISBN , val.c_str());
}

void book::Set_title(string val) {
    strcpy(Book_Title , val.c_str());
}

void book::Set_Author_Id(string val) {
    strcpy(Author_Id , val.c_str());
}

void book::Get_Isbn(char (&val)[]) {
    strcpy(val , ISBN);
}

void book::Get_Title(char (&val)[]) {
    strcpy(val ,Book_Title);
}

void book::Get_Author_id(char (&val)[]) {
    strcpy(val , Author_Id);
}

