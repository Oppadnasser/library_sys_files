#include <iostream>
#include "book.h"
#include "Author.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

void addNewAuthor() {
    ifstream file1("Authors.txt");
    ofstream file2("temp.txt");
    if(!file1.is_open()){
        ofstream f("Authors.txt");
        f << 0 << ' ' << 0 << '\n';
        f.close();
        file1.open("Authors.txt" , ios::in);
    }
    int Old_records = 0 , deleted_records = 0;
    file1 >> Old_records >> deleted_records;
    Old_records++;
    char name[30] , address[30] , Authorid[15];
    bool added = false;
    cout << "Please Enter Author name:";
    cin.ignore();
    cin.getline(name , 30);
    cout << "Please enter Author address:";
    cin.getline(address , 30);
    cout << "Please enter Author ID:";
    cin.getline(Authorid , 15);
    file1.seekg(0);
    string Name , Address , Id;
    getline(file1 , Name);
    file2 << Old_records << ' ' << deleted_records << ' ' << '\n';
    while(getline(file1 , Id , '|') && getline(file1 , Name , '|') && getline(file1 , Address )){
        size_t startpos = Id.find_first_not_of(' ');
        if(startpos != string::npos){
            Id.erase(0 , startpos);
        }
        if(Id == Authorid){
            cout << "this id was exist!";
            file1.close();
            file2.close();
            remove("temp.txt");
            return;
        }
        if(!added && Authorid < Id){
            file2<<setw(15) <<  Authorid << '|' << setw(30) << name << '|' << setw(30) <<  address << "\n";
            added = true;
        }
        file2 << setw(15) << Id << '|' << Name << '|' << Address << "\n";
    }
    if(!added)
        file2<<setw(15) <<  Authorid << '|' << setw(30) << name << '|' << setw(30) <<  address << "\n";
    file1.close();
    file2.close();
    remove("Authors.txt");
    rename("temp.txt" , "Authors.txt");
}

void addNewBook() {
    char Title[30] , authorId[15] , ISBN[15] ;
    string T , AID , IS;
    bool added = false;
    ifstream file1("books.txt");
    if(!file1.is_open()){
        ofstream file("books.txt");
        file.close();
        file1.open("books.txt" , ios::in);
    }
    ofstream file2("temp.txt");
    cout << "Please Enter Book Title:";
    cin.ignore();
    cin.getline(Title , 30);
    cout << "Please Enter Book ISBN";
//    cin.ignore();
    cin.getline(ISBN , 15);
    cout << "Please Enter Author Id of this book:";
//    cin.ignore();
    cin.getline(authorId , 15);
    while(getline(file1 , IS , '|') && getline(file1 , T, '|') && getline(file1 , AID ) ){

        size_t startpos = IS.find_first_not_of(' ');
        if(startpos != string::npos){
            IS.erase(0 , startpos);
        }
        if(IS == ISBN){
            cout << "This ISBN was used to another book!\nfailed to add this book!\n";
            file1.close();
            file2.close();
            remove("temp.txt");
            return;
        }
        if( !added && ISBN < IS ){
            file2 << setw(15) << ISBN << '|'<< setw(30)  << Title << '|' << setw(15) << authorId << '\n';
            added = true;
        }
        file2 << setw(15) << IS << '|' << T << '|' << AID << '\n';
    }
    if(!added){
        file2 << setw(15) << ISBN << '|'<< setw(30)  << Title << '|' << setw(15) << authorId << '\n';
    }
    file1.close();
    file2.close();
    remove("books.txt");
    rename("temp.txt" , "books.txt");
}

void updateAuthorName(int authorId) {}

void updateBookTitle(int ISBN) {}

void deleteBook(int ISBN) {}

void deleteAuthor(int ID) {}

void printAuthor(int ID) {}

void printBook(int ISBN) {}

void writeQuery() {}

void Exit() {
    cout << "GOOD BYE MY DEAR USER :)";
    exit(1);
}