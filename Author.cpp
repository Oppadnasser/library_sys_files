//
// Created by oppad on 11/10/2023.
//

#include "Author.h"
Author::Author(string id, string name, string address) {
    strcpy(ID , id.c_str());
    strcpy(Name , name.c_str());
    strcpy(Address , address.c_str());
}
void Author::Get_Id(char (&val)[]) {
    strcpy(val , ID);
}

void Author::Get_Name(char (&val)[]) {
    strcpy(val , Name);
}

void Author::Get_Address(char (&val)[]) {
    strcpy(val, Address);
}

void Author::Set_Name(string val) {
    strcpy(Name, val.c_str());
}
void Author::Set_Id(string id) {
    strcpy(ID , id.c_str());
}
void Author::Set_Address(string address) {
    strcpy(Address , address.c_str());
}