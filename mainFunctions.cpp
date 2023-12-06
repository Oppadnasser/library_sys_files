#include <iostream>
#include "book.h"
#include "Author.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#define tuple_length 27
using namespace std;

// { place of att in secondary file , last offset}
vector<int> search_secondary(string id , char file_name[])
{
    vector<int> temp = {-1 , -1};
    ifstream file1(file_name , ios::in | ios ::binary);
    if(!file1.is_open()){
        ofstream f(file_name , ios::out | ios::binary);
        f.close();
        return temp;
    }
    file1.seekg(0 , ios::end);
    int start = 0;
    int end = (file1.tellg() /27)-1;
    while(end >= start){
        int mid = (start + end)/2;
        file1.seekg((mid * 27) , ios::beg);
        string Id ; // ID means attribute
        int offset;
//        file1 >> Id;
        getline(file1 , Id , '|');
        size_t startpos = Id.find_first_not_of(' ');
        if(startpos != string::npos){
            Id.erase(0 , startpos);
        }
        file1.seekg(1 , ios::cur);
        file1 >> offset;
        if(Id == id){
            temp[1] = offset;
            temp[0] = mid*27;
            return temp;
        }
        if(Id < id){
            start = mid+1;
        }
        else{
            end = mid-1;
        }
    }

    return temp;
}
bool AddAttribute(char filename[],  string val , int offset , int location , string Id){
    int place;
    bool added = false;
    int preoffset = -1;
    string line;
    string attribute;
    if(filename == "../indexing/SNA.txt"){
        fstream file("../indexing/listA.txt" , ios::in | ios::app | ios::binary);
        file << setw(30) << Id <<' '<< setw(10) << offset << '\n';
        file.seekg(0, ios::end);
        place = file.tellp();
        file.close();
    }
    else{
        fstream file("../indexing/listB.txt" , ios::app | ios::binary);
        file << setw(30) << Id << ' ' << setw(10) << offset << '\n';
        file.seekg(0, ios::end);
        place = file.tellp();
        file.close();
    }
    place-= 42;
    ifstream secondarfile(filename , ios::in | ios::binary);
    if(!secondarfile.is_open()){
        ofstream f(filename , ios::out | ios::binary);
        f.close();
        secondarfile.open(filename , ios::in | ios::binary);
    }
    ofstream tempfile("../indexing/tempfile.txt" , ios::out|ios::binary);
    if(location == -1){
        while(getline(secondarfile , attribute , '|')){ //read all records in index file
            size_t startpos = attribute.find_first_not_of(' ');
            if(startpos != string::npos){
                attribute.erase(0 , startpos);
            }
            secondarfile >> preoffset;
            secondarfile.seekg(1 , ios::cur);
            if(!added && attribute > val){ // if record to be added is less than specific id in index file
                tempfile << setw(15) << val << '|' << setw(10) << place << '\n';// add it first
                tempfile << setw(15) << attribute << '|' << setw(10) << preoffset << '\n'; // then add another record
                added = true;
            }
            else {
                tempfile << setw(15) << attribute << '|' << setw(10) << preoffset << '\n';
            }
        }
        if(!added){
            tempfile << setw(15) << val << '|' << setw(10) << place << '\n';
        }
    }
    else{
        while(secondarfile.tellg() != location){
            getline(secondarfile, line);
            tempfile << line << '\n';
        }
        secondarfile >> attribute;
        secondarfile >> preoffset;
        secondarfile.seekg(1 , ios::cur);
        tempfile << setw(16) << attribute << setw(10) << place << '\n';
        while(getline(secondarfile, line)){
            tempfile << line << '\n';
        }

    }
    secondarfile.close();
    tempfile.close();
    remove(filename);
    rename("../indexing/tempfile.txt" , filename);

    return true;

}
void DeleteAttribute(char filename[],  string val , int location_in_S , int last_offset , string Id){
    fstream list_file;
    bool verified = false;
    string line , id;
    int preoffset  , off, location_to_delete;
    fstream secondary_file(filename , ios::in | ios::binary);
    ofstream tempS("../indexing/tempS.txt" , ios::out | ios::binary);
    ofstream templist("../indexing/tempL.txt" , ios::out | ios::binary);
    if(filename == "../indexing/SAIDB.txt")
        list_file.open("../indexing/listB.txt" , ios::in | ios::binary);
    else
        list_file.open("../indexing/listA.txt", ios::in | ios::binary);
    while(secondary_file.tellg() != location_in_S){
        getline(secondary_file , line);
        tempS << line << '\n';
    }
    list_file.seekg(last_offset);
    while(true){
    location_to_delete = list_file.tellg();
    list_file >> id >> preoffset;
    if(id == Id){
        break;
    }
    list_file.seekg(preoffset);
    }
    list_file.seekg(0 , ios::beg);
    while(list_file.tellg() != location_to_delete){
        getline(list_file , line);
        templist << line << '\n';
    }
    getline(list_file , line);
    while(list_file >> id >> off){
        if(!verified && off == location_to_delete){
            templist << setw(30) << id  << setw(11) << preoffset << '\n';
            verified = true;
        }
        else{
            if(off > location_to_delete)
                off-=42;
            templist << setw(30) << id << setw(11) << off << '\n';
        }
        list_file.seekg(1 , ios::cur);
    }
    getline(secondary_file , line , '|');
    int temp;
    secondary_file >> temp;
    secondary_file.seekg(1 , ios::cur);
    if(temp == location_to_delete){
        if(preoffset != -1){
            tempS << line << '|' << setw(10) << preoffset << '\n';
        }
    }
    else{
        tempS << line << '|' << setw(10) << temp << '\n';
    }
    while(getline(secondary_file , line)){
        tempS << line << '\n';
    }
    tempS.close();
    templist.close();
    secondary_file.close();
    list_file.close();
    if(filename == "../indexing/SAIDB.txt"){
        remove("../indexing/listB.txt");
        rename("../indexing/tempL.txt" ,"../indexing/listB.txt");
    }
    else{
        remove("../indexing/listA.txt");
        rename("../indexing/tempL.txt" ,"../indexing/listA.txt");
    }
    remove(filename);
    rename("../indexing/tempS.txt" , filename);
    tempS.open("../indexing/tempS.txt" , ios::out | ios::binary);
    secondary_file.open(filename , ios::in | ios::binary);
    while(secondary_file >> line >> off){
        if(off > location_to_delete)
            off-=42;
        tempS << setw(16) << line << setw(10) << off << '\n';
    }
    tempS.close();
    secondary_file.close();
    remove(filename);
    rename("../indexing/tempS.txt" , filename);

}
bool sortbysec(const pair<int,int> &a,const pair<int,int> &b)
{
    return (a.second < b.second);
}
//add id for specific index file
bool AddId(char filename[],  string id , int offset){ // offset is the offset of new record
    // fixed length for record is 26 15 for(id) 1 for delimiter and 10 for offset
    string I; // I is the Ids in index file
    int off; // offsets of records in index file
    bool added = false; // to check if new record is added or not
    ofstream newindex("../indexing/temp1.txt" , ios::out |ios::binary);
    ifstream file1(filename , ios::in | ios::binary);
    while(getline(file1 , I , '|')){ //read all records in index file
        size_t startpos = I.find_first_not_of(' ');
        if(startpos != string::npos){
            I.erase(0 , startpos);
        }
        if(I == id){ // check if this id was used
            newindex.close();
            remove("../indexing/temp1.txt");
            return false;
        }
        file1 >> off;
        file1.seekg(1 , ios::cur);
        if(!added && stoi(I) > stoi(id)){ // if record to be added is less than specific id in index file
            newindex << setw(15) << id << '|' << setw(10) << offset << '\n';// add it first
            newindex << setw(15) << I << '|' << setw(10) << off << '\n'; // then add another record
            added = true;
        }
        else {
            newindex << setw(15) << I << '|' << setw(10) << off << '\n';
        }
    }
    if(!added){
        newindex << setw(15) << id << '|' << setw(10) << offset << '\n';
    }
    file1.close();
    newindex.close();
    remove(filename);
    rename("../indexing/temp1.txt" , filename);
    return true;

}
void addtoavaillist(vector<pair<int, int>> &vec , string s){
    s = s.substr(1 , s.length()-1);
    int i = 0;
    string offset , size;
    for(; s[i] != '|';i++){
        offset +=s[i];
    }
    i++;
    for(; s[i] != '|';i++){
        size +=s[i];
    }
    vec.push_back(make_pair(stoi(offset) , stoi(size)));

}
// when you search for an id it will return the offset in file itself and file index
//vec[record location in index file , record location in data file
vector<int> search(int id , char file_name[])
{
    vector<int> temp{-1 , -1};
    ifstream file1(file_name , ios::in | ios ::binary);
    file1.seekg(0 , ios::end);
    int start = 0;
    int end = (file1.tellg() / tuple_length)-1;
    while(end >= start){
        int mid = (start + end)/2;
        file1.seekg((mid * tuple_length) , ios::beg);
        int Id , offset;
        file1 >> Id;
        file1.seekg(1 , ios::cur);
        file1 >> offset;
        if(Id == id){
            temp[0] = mid*tuple_length ;
            temp[1] = offset;
            return temp;
        }
        if(Id < id){
            start = mid+1;
        }
        else{
            end = mid-1;
        }
    }

    return temp;
}
// update the record offset to set new offset in index file
// tuple location is location that retrieved from search function in first index in vector
void update_offset(string id , int num , char filename[]){
    int Id = stoi(id); //this Id used to search function
    vector t = search(Id , filename);
    int location = t[0];                                                    //start location of record to be updated
    ifstream file1(filename , ios::in | ios::binary);
    ofstream file2("../indexing/temp2.txt" , ios::out | ios::binary);
    string line;
    while(file1.tellg() != location){ // take all records before record to updated
        getline(file1 , line);
        file2 << line << '\n';
    }
    getline(file1 , line , '|');                //line is id for updated record
    int ID;                                                  //ID is the old offset
    file1>> ID;
    file1.seekg(1, ios::cur);
    ID+=num;                                                //increase or decrease offset
    file2 << line << '|' << setw(10) << ID << '\n';      // write record after update
    while(getline(file1 , line)){                   //write all records after updated record
        file2 << line << '\n';
    }
    file1.close();
    file2.close();
    remove(filename);
    rename("../indexing/temp2.txt" , filename);
}

// to delete id from index file and
void delete_tuple_in_index(int id , char filename[]){
    ifstream file(filename);
    string line;
    ofstream file2("../indexing/newindex.txt" , ios::out | ios::binary);
    vector t = search(id,filename);
    while(file.tellg() != t[0]){ // write all records before the record to be deleted
        getline(file , line);
        file2 << line << '\n';
    }
    getline(file , line); // to ignore adding deleted tuple
    while(getline(file , line)){        // write all records after the record to be deleted
        file2 << line << '\n';
    }
    file.close();
    file2.close();
    remove(filename);
    rename("../indexing/newindex.txt" , filename);
}

void addNewAuthor(){
    fstream file1;
    string AVIL_List;
    file1.open("Authors.txt" ,  ios:: in|ios::binary);
    if(!file1.is_open()){
        ofstream f("Authors.txt" , ios::out | ios::binary);
        f << -1 <<  '\n';
        f.close();
        file1.open("Authors.txt" ,  ios::in|ios::binary);
    }
    char name[30] , address[30] , Authorid[15];
    cout << "Please Enter Author name:";
    cin.ignore();
    cin.getline(name , 30);
    cout << "Please enter Author address:";
    cin.getline(address , 30);
    cout << "Please enter Author ID:";
    cin.getline(Authorid , 15);
    {
        vector<int> vec = search(stoi(Authorid) , "../indexing/PIDA.txt");
        if(vec[0] != -1){
            cout << "this Author ID was used:";
            file1.close();
            return;
        }
    }
    int record_size = 0;
    record_size= strlen(Authorid) + strlen(name) + strlen(address);
    name[strlen(name)] = '\0';
    Authorid[strlen(Authorid)] = '\0';
    address[strlen(address)] = '\0';
    file1 >> AVIL_List; // check if there is any records was deleted
    file1.seekg(1 , ios::cur);
    string record = Authorid;
    record+="|";
    record+= name;
    record+= "|";
    record+=address;
    record+="|";
    record_size+=5;
    if(AVIL_List =="-1"){
        int start = file1.tellg();
        file1.close();
        file1.open("Authors.txt" ,  ios:: in| ios::app|ios::binary);
        file1.seekg(0 , ios::end);
        int offset = file1.tellp();
        offset -= start;
        if (AddId("../indexing/PIDA.txt", Authorid , offset)) {
            file1 << setw(record_size-1) <<record << record_size<< "\n";
        } else {
            cout << "this Author ID was used \n failed to add Author";
            file1.close();
            return;
        }
        file1.close();
    }
    else {
        vector<pair<int, int>> availlist;
        while (AVIL_List != "-1") {
            addtoavaillist(availlist, AVIL_List);
            file1 >> AVIL_List;
        }
        file1.seekg(1, ios::cur);
        int start = file1.tellg();
        pair<int, int> place = make_pair(0, 0); // place{offset , size}
        for (auto a: availlist) {
            if (a.second >= record_size) {
                place = a;
                break;
            }
        }
        if (place.first == 0 && place.second == 0) {
            int start = file1.tellg();
            file1.close();
            file1.open("Authors.txt", ios::in | ios::app | ios::binary);
            file1.seekg(0, ios::end);
            int offset = file1.tellp();
            offset -= start;
            if (AddId("../indexing/PIDA.txt", Authorid, offset)) {
                file1 << setw(record_size - 1) << record << record_size << "\n";
            } else {
                cout << "this Author ID was used \n failed to add Author";
            }
            file1.close();
        } else {
            ofstream newfile("temp.txt", ios::out | ios::binary);
            for (auto a: availlist) {
                if (a.second != place.second) {
                    newfile << '*' << a.first << '|' << a.second << '|' << ' ';
                }
            }
            newfile << -1 << '\n';
            while (file1.tellg() != start + place.first) { // write all previous records without change in offset
                string line;
                getline(file1, line);
                newfile << line << '\n';
            }
            string line;                          // line deleted and replacement with new record
            getline(file1, line);
            while (record_size < place.second) {
                record += '/';
                record_size++;
            }
            newfile << setw(record_size - 1) << record << record_size << '\n';

            while (getline(file1, line)) {
                newfile << line << '\n';
            }
            AddId("../indexing/PIDA.txt", Authorid, place.first);
            file1.close();
            newfile.close();
            remove("Authors.txt");
            rename("temp.txt", "Authors.txt");
        }
    }
    vector<int> tem = search_secondary(name , "../indexing/SNA.txt");
    AddAttribute("../indexing/SNA.txt",name,tem[1] , tem[0], Authorid);

}
void deleteAuthor(int ID) {
    //temp {location index  , location data file}
    vector<int> temp = search(ID , "../indexing/PIDA.txt");
    if(temp[0] == -1){
        cout << "invalid Author id";
        return;
    }
    fstream data_file("Authors.txt" , ios::in | ios::binary);
    fstream newfile("temp.txt" , ios::out | ios::binary);
    vector<pair<int,int>> availlist;
    string AVIL_List;
    data_file >> AVIL_List;
    while(AVIL_List != "-1"){
        addtoavaillist(availlist , AVIL_List);
        data_file >> AVIL_List;
    }
    pair<int , int> n;
    n.first = temp[1];
    data_file.seekg(1 , ios::cur);
    int start = data_file.tellg();
    int offset = temp[1]; // offset is location of record to be deleted
    data_file.seekg(start+offset);
    string l1 , line , id; // to check length of each avail list if there differentiate
    getline(data_file , line);
    n.second = line.length() -1;
    availlist.push_back(n);
    sort(availlist.begin(), availlist.end() , sortbysec);
    for(auto a : availlist){
            newfile << '*' << a.first << '|' << a.second << '|' << ' ';
    }
    newfile << -1 << '\n';
    data_file.seekg(start , ios::beg);
    while(data_file.tellg() != offset+start){ // write all records before record to be deleted
        getline(data_file , line);
        newfile << line << '\n';
    }
    string val;
    int s = 0;
    getline(data_file , val , '|');
    s+=val.length();
    getline(data_file , val , '|');
    s+=val.length();
    s+=2;
    data_file.seekg(-s , ios::cur);
    getline(data_file , line);
    size_t startpos = line.find_first_not_of(' ');
    if(startpos != string::npos){
        line.erase(0 , startpos);
    }// record to be deleted
    n.second = line.length();
    newfile << "*" <<line << '\n';  // mark as readed and add previous AVIL_LIST
    while(getline(data_file , line)){
        newfile << line << '\n';
    }
    delete_tuple_in_index(ID,"../indexing/PIDA.txt"); // delete the indexing of deleted record
    data_file.close();
    newfile.close();
    remove("Authors.txt");
    rename("temp.txt" , "Authors.txt");
    temp = search_secondary(val , "../indexing/SNA.txt");
    DeleteAttribute("../indexing/SNA.txt",  val ,temp[0] , temp[1] , to_string(ID));
}

void addNewBook() {
//    char Title[30] , authorId[15] , ISBN[15] ;
    fstream file1;
    string AVIL_List;
    int counter = 0;
    file1.open("books.txt" ,  ios:: in|ios::binary);
    if(!file1.is_open()){
        ofstream f("books.txt" , ios::out | ios::binary);
        f << -1 <<  '\n';
        f.close();
        file1.open("books.txt" ,  ios::in|ios::binary);
    }
    char Title[30] , authorId[15] , ISBN[15];
    cout << "Please Enter book title:";
    cin.ignore();
    cin.getline(Title , 30);
    cout << "Please enter Author id for this book:";
    cin.getline(authorId , 15);
    cout << "Please enter book ISBN:";
    cin.getline(ISBN , 15);
    int record_size = 0;
    record_size= strlen(ISBN) + strlen(Title) + strlen(authorId);
    Title[strlen(Title)] = '\0';
    ISBN[strlen(ISBN)] = '\0';
    authorId[strlen(authorId)] = '\0';
    file1 >> AVIL_List; // check if there is any records was deleted
    file1.seekg(1 , ios::cur);
    string record =  ISBN;
    record+="|";
    record+= Title;
    record+= "|";
    record+=authorId;
    record+="|";
    record_size+=5;
    if(AVIL_List =="-1"){
        int start = file1.tellg();
        file1.close();
        file1.open("books.txt" ,  ios:: in| ios::app|ios::binary);
        file1.seekg(0 , ios::end);
        int offset = file1.tellp();
        offset -= start;
        if (AddId("../indexing/PIDB.txt", ISBN , offset)) {
            file1 << setw(record_size-1) <<record << record_size<< "\n";
        } else {
            cout << "this Book ISBN was used \n failed to add Book";
            file1.close();
            return;
        }
    }
    else {
        vector<pair<int, int>> availlist;
        while (AVIL_List != "-1") {
            addtoavaillist(availlist, AVIL_List);
            file1 >> AVIL_List;
        }
        file1.seekg(1, ios::cur);
        int start = file1.tellg();
        pair<int, int> place = make_pair(0, 0); // place{offset , size}
        for (auto a: availlist) {
            if (a.second >= record_size) {
                place = a;
                break;
            }
        }
        if (place.first == 0 && place.second == 0) {
            int start = file1.tellg();
            file1.close();
            file1.open("books.txt", ios::in | ios::app | ios::binary);
            file1.seekg(0, ios::end);
            int offset = file1.tellp();
            offset -= start;
            if (AddId("../indexing/PIDB.txt", ISBN, offset)) {
                file1 << setw(record_size - 1) << record << record_size << "\n";
            } else {
                cout << "this ISBN was used \n failed to add book";
                file1.close();
                return;
            }
            file1.close();
        } else {
            ofstream newfile("temp.txt", ios::out | ios::binary);
            for (auto a: availlist) {
                if (a.second != place.second) {
                    newfile << '*' << a.first << '|' << a.second << '|' << ' ';
                }
            }
            newfile << -1 << '\n';
            while (file1.tellg() != start + place.first) { // write all previous records without change in offset
                string line;
                getline(file1, line);
                newfile << line << '\n';
            }
            string line;                          // line deleted and replacement with new record
            getline(file1, line);
            while (record_size < place.second) {
                record += '/';
                record_size++;
            }
            newfile << setw(record_size - 1) << record << record_size << '\n';

            while (getline(file1, line)) {
                newfile << line << '\n';
            }
            AddId("../indexing/PIDB.txt", ISBN, place.first);
            file1.close();
            newfile.close();
            remove("books.txt");
            rename("temp.txt", "books.txt");
        }
    }
    vector<int> tem = search_secondary(authorId , "../indexing/SAIDB.txt");
    AddAttribute("../indexing/SAIDB.txt",authorId,tem[1] , tem[0], ISBN);
}

void deleteBook(int ISBN) {
    //temp {location index  , location data file}
    vector<int> temp = search(ISBN , "../indexing/PIDB.txt");
    if(temp[0] == -1){
        cout << "invalid book ISBN";
        return;
    }
    fstream data_file("books.txt" , ios::in | ios::binary);
    fstream newfile("temp.txt" , ios::out | ios::binary);
    vector<pair<int,int>> availlist;
    string AVIL_List;
    data_file >> AVIL_List;
    while(AVIL_List != "-1"){
        addtoavaillist(availlist , AVIL_List);
        data_file >> AVIL_List;
    }
    pair<int , int> n;
    n.first = temp[1];
    data_file.seekg(1 , ios::cur);
    int start = data_file.tellg();
    int offset = temp[1]; // offset is location of record to be deleted
    data_file.seekg(start+offset);
    string l1 , l2 , line; // to check length of each avail list if there differentiate
    getline(data_file , line);
    n.second = line.length() -1;
    availlist.push_back(n);
    sort(availlist.begin(), availlist.end() , sortbysec);
    for(auto a : availlist){
        newfile << '*' << a.first << '|' << a.second << '|' << ' ';
    }
    newfile << -1 << '\n';
    data_file.seekg(start , ios::beg);
    while(data_file.tellg() != offset+start){ // write all records before record to be deleted
        getline(data_file , line);
        newfile << line << '\n';
    }
    string val;
    int s = 0;
    getline(data_file , val , '|');
    s+=val.length();
    getline(data_file , val , '|');
    s+=val.length();
    getline(data_file , val , '|');
    s+=val.length();
    s+=3;
    data_file.seekg(-s , ios::cur);
    getline(data_file , line);
    size_t startpos = line.find_first_not_of(' ');
    if(startpos != string::npos){
        line.erase(0 , startpos);
    }// record to be deleted
    n.second = line.length();
    newfile << "*" <<line << '\n';  // mark as readed and add previous AVIL_LIST
    // all offset's records after deleted record will increase by
    while(getline(data_file , line)){
        newfile << line << '\n';
    }
    delete_tuple_in_index(ISBN,"../indexing/PIDB.txt"); // delete the indexing of deleted record
    data_file.close();
    newfile.close();
    remove("books.txt");
    rename("temp.txt" , "books.txt");
    temp = search_secondary(val , "../indexing/SAIDB.txt");
    DeleteAttribute("../indexing/SAIDB.txt",val , temp[0] ,temp[1] , to_string(ISBN));
}

void updateAuthorName(int authorId) {}

void updateBookTitle(int ISBN) {}

void printAuthor(int ID) {}

void printBook(int ISBN) {}

vector<string> split(string stringWord, char delimiter) {
    vector<string> queryVector;
    string word = "";
    for (int i = 0; i < stringWord.length(); i++) {
        if (stringWord[i] == ';') {
            queryVector.push_back(word);
            break;
        }
        if (stringWord[i] == delimiter) {
            queryVector.push_back(word);
            word = "";
        } else {
            word = word + stringWord[i];
        }
    }
    cout<<endl;
    cout<<"Query Vector"<<endl;
    for (int i = 0; i < queryVector.size(); i++) {
        cout << "v[" << i << "]" << queryVector[i] << endl;
    }
    return queryVector;
}

void writeQuery() {
    // Select all from Authors where Author ID="xxx";
    vector <string> myQuery;
    vector <string> myQuery2;
    string wantedTubles, wantedTable, wantedAttribute, condition, value, query_1, getquery;
    cout << "Enter your query :) >>  " << endl;
    cin.ignore();
    getline(cin, query_1);
    myQuery = split(query_1, ' ');
    /// converting all to lower case
    for (int i = 0; i < myQuery.size(); i++) {
        transform(myQuery[i].begin(), myQuery[i].end(), myQuery[i].begin(), ::tolower);
    }
    getquery = myQuery[0];
    wantedTubles = myQuery[1];
    wantedTable = myQuery[3];
    condition = myQuery[5];
    wantedAttribute = condition.substr(0, condition.find("="));
    condition = condition.substr(condition.find("=")+1 , condition.length());//Select all from Authors where AuthorID=’5566';
    value = condition.substr(1, condition.length() - 2);

    condition = "=";
    cout<<"wantedTubles: "<<wantedTubles<<endl;
    cout<<"wantedTable: "<<wantedTable<<endl;
    cout<<"wantedAttribute: "<<wantedAttribute<<endl;
    cout<<"value: "<<value<<endl;
    cout<<"condition: "<<condition<<endl;

    if(getquery == "select")
    {
        if(wantedTable == "authors")
        {
            if(wantedTubles == "*" || wantedTubles == "all")
            {
                if(condition == "=") {
                    if (wantedAttribute == "authorid") {
                        int x = stoi(value);
                        int offset = search(x, "../indexing/PIDA.txt")[1];
                        if(offset == -1){
                            cout << "invalid Author id";
                            return;
                        }
                        ifstream file("Authors.txt", ios::in | ios::binary);
                        string line;
                        getline(file, line);
                        file.seekg(offset, ios::cur);
                        getline(file, line);
                        cout << "Author ID: " << line.substr(0, line.find("|")) << endl;
                        line = line.substr(line.find("|") + 1, line.length());
                        cout << "Author Name: " << line.substr(0, line.find("|")) << endl;
                        line = line.substr(line.find("|") + 1, line.length());
                        cout << "Author Address: " << line.substr(0, line.find("|")) << endl;
                        file.close();

                    }
                }

            }

        }
        else if(wantedTable == "Books")
        {
            if(wantedTubles == "*" || wantedTubles == "all")
            {
                if(condition == "=")
                {
                    if(wantedAttribute == "ISBN")
                    {
                        int x = 0;
                        stringstream geek(value);
                        geek >> x;
                        int offset = search(x , "../indexing/PIDB.txt")[1];
                        ifstream file("books.txt" , ios::in | ios::binary);
                        string line;
                        getline(file , line);
                        file.seekg(offset , ios::cur);
                        getline(file , line);
                        cout<<"ISBN: "<<line.substr(0 , line.find("|"))<<endl;
                        line = line.substr(line.find("|")+1 , line.length());
                        cout<<"Book Title: "<<line.substr(0 , line.find("|"))<<endl;
                        line = line.substr(line.find("|")+1 , line.length());
                        cout<<"Author ID: "<<line.substr(0 , line.find("|"))<<endl;
                        file.close();

                    }
                }
            }
        }
    }/*
    else if(getquery == "Delete")
    {
        if(wantedTable == "Authors")
        {
            if(condition == "=")
            {
                if(wantedAttribute == "Author_ID")
                {
                    int x = 0;
                    stringstream geek(value);
                    geek >> x;
                    deleteAuthor(x);
                }
            }
        }
        else if(wantedTable == "Books")
        {
            if(condition == "=")
            {
                if(wantedAttribute == "ISBN")
                {
                    int x = 0;
                    stringstream geek(value);
                    geek >> x;
                    deleteBook(x);
                }
            }
        }
    }
    else if(getquery == "Update")
    {
        if(wantedTable == "Authors")
        {
            if(condition == "=")
            {
                if(wantedAttribute == "Author_ID")
                {
                    int x = 0;
                    stringstream geek(value);
                    geek >> x;
                    updateAuthorName(x);
                }
            }
        }
        else if(wantedTable == "Books")
        {
            if(condition == "=")
            {
                if(wantedAttribute == "ISBN")
                {
                    int x = 0;
                    stringstream geek(value);
                    geek >> x;
                    updateBookTitle(x);
                }
            }
        }
    }
    else if(getquery == "Insert")
    {
        if(wantedTable == "Authors")
        {
            addNewAuthor();
        }
        else if(wantedTable == "Books")
        {
            addNewBook();
        }
    }
    else if(getquery == "Exit")
    {
        Exit();
    }
    else
    {
        cout<<"Invalid Query"<<endl;
    }*/


    //displayQueryResult(wantedTubles, wantedTable, wantedAttribute, condition, value);

}

void Exit() {
    cout << "GOOD BYE MY DEAR USER :)";
    exit(1);
}