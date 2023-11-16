#include <iostream>
#include "book.h"
#include "Author.h"
#include <fstream>
#include <sstream>
using namespace std;

void addNewAuthor() {
    ifstream file1("Authors.txt");
    ofstream file2("temp.txt");
    int Old_records = -1 , deleted_records = -1;
    file1 >> Old_records >> deleted_records;
    int id = Old_records+1;
    string name , address;
    cout << "Please Enter Author name:";
    cin >> name;
    cout << "Please enter Author address:";
    cin >> address;
    file1.seekg(0);
    string line;
    getline(file1 , line);
    size_t pos = line.find(to_string(Old_records));
    line.replace(pos , to_string(Old_records).length() , to_string(id));
    file2 << line << '\n';
    while(getline(file1 , line)){
        file2 << line << '\n';
    }
    file2<< id << ' ' << name << ' ' << address;
    file1.close();
    file2.close();
    remove("Authors.txt");
    rename("temp.txt" , "Authors.txt");
}

void addNewBook() {
    string Title , authorId , line;
    int ISBN;
    bool added = false;
    ifstream file1("books.txt");
    ofstream file2("temp.txt");
    cout << "Please Enter Book Title:";
    cin >> Title;
    cout << "Please Enter Book ISBN";
    cin >> ISBN;
    cout << "Please Enter Author Id of this book:";
    cin >> authorId;
    while(getline(file1 , line)){
        stringstream ss(line);
        string  b , c;
        int a;
        ss >> a >> b >> c;
        if(a == ISBN){
            cout << "This ISBN was used to another book!\nfailed to add this book!\n";
            file1.close();
            file2.close();
            remove("temp.txt");
            return;
        }
        if( !added && ISBN < a ){
            file2 << ISBN << ' ' << Title << ' ' << authorId << '\n';
            added = true;
        }
        file2 << line << '\n';
    }
    if(!added){
        file2 << ISBN << ' ' << Title << ' ' << authorId << '\n';
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