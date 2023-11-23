#include <iostream>
#include "book.h"
#include "Author.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

int AddId(char filename[],  string id){
    // fixed length for record is 26 15 for(id) 1 for delimiter and 10 for RNN
    string I;
    int RNN;
    bool added = false;
    int Old_records = 0 , deleted_records = 0;
    ofstream newindex("../indexing/temp.txt");
    ifstream file1(filename);
    file1 >> Old_records >> deleted_records;
    file1.seekg(1 , ios::cur);
    newindex << Old_records+1 << ' ' << deleted_records << '\n';
    while(getline(file1 , I , '|')){
        size_t startpos = I.find_first_not_of(' ');
        if(startpos != string::npos){
            I.erase(0 , startpos);
        }
        if(I == id){
            newindex.close();
            remove("/indexing/temp.txt");
            return -1;
        }
        file1 >> RNN;
        file1.seekg(1 , ios::cur);
        if(!added && I > id){
            newindex << setw(15) << id << '|' << setw(10) << deleted_records+Old_records << '\n';
            newindex << setw(15) << I << '|' << setw(10) << RNN << '\n';
            added = true;
        }
        else {
            newindex << setw(15) << I << '|' << setw(10) << RNN << '\n';
        }
    }
    if(!added){
        newindex << setw(15) << id << '|' << setw(10) << deleted_records+Old_records << '\n';
    }
    file1.close();
    newindex.close();
    remove(filename);
    rename("../indexing/temp.txt" , filename);
    return deleted_records+Old_records;

}


void addNewAuthor() {
    fstream file1;
    file1.open("Authors.txt" ,  ios::app);
    if(!file1.is_open()){
        ofstream f("Authors.txt");
        f << 0 << ' ' << 0 << '\n';
        f.close();
        file1.open("Authors.txt" ,  ios::app);
    }
    char name[30] , address[30] , Authorid[15];
    cout << "Please Enter Author name:";
    cin.ignore();
    cin.getline(name , 30);
    cout << "Please enter Author address:";
    cin.getline(address , 30);
    cout << "Please enter Author ID:";
    cin.getline(Authorid , 15);
    if(AddId("../indexing/PIDA.txt" , Authorid  ) != -1){
        file1<<setw(16) <<  Authorid << '|' << setw(30) << name << '|' << setw(30) <<  address << "\n";
    }
    else{
        cout << "this Author ID was used \n failed to add Author";
    }
    file1.close();
}

void addNewBook() {
    char Title[30] , authorId[15] , ISBN[15] ;
    fstream file1("books.txt" , ios::app);
    if(!file1.is_open()){
        ofstream file("books.txt");
        file.close();
        file1.open("books.txt" , ios::app);
    }
    cout << "Please Enter Book Title:";
    cin.ignore();
    cin.getline(Title , 30);
    cout << "Please Enter Book ISBN";
    cin.getline(ISBN , 15);
    cout << "Please Enter Author Id of this book:";
    cin.getline(authorId , 15);
    if(AddId("../indexing/PIDB.txt" , ISBN) != -1){
        file1 << setw(16) << ISBN << '|'<< setw(30)  << Title << '|' << setw(15) << authorId << '\n';
    }
    else{
        cout << "this book ISBN used\nfailed to add this book!";
    }
//    while(getline(file1 , IS , '|') && getline(file1 , T, '|') && getline(file1 , AID ) ){
//
//        size_t startpos = IS.find_first_not_of(' ');
//        if(startpos != string::npos){
//            IS.erase(0 , startpos);
//        }
//        if(IS == ISBN){
//            cout << "This ISBN was used to another book!\nfailed to add this book!\n";
//            file1.close();
//            file2.close();
//            remove("temp.txt");
//            return;
//        }
//        if( !added && ISBN < IS ){
//            file2 << setw(15) << ISBN << '|'<< setw(30)  << Title << '|' << setw(15) << authorId << '\n';
//            added = true;
//        }
//        file2 << setw(15) << IS << '|' << T << '|' << AID << '\n';
//    }
//    if(!added){
//        file2 << setw(15) << ISBN << '|'<< setw(30)  << Title << '|' << setw(15) << authorId << '\n';
//    }
    file1.close();
//    file2.close();
//    remove("books.txt");
//    rename("temp.txt" , "books.txt");
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