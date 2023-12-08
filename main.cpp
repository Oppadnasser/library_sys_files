#include "mainFunctions.cpp"


int main() {
    char choice;
    while (true) {
        cout <<"\nwelcome to our library system :) \nAvailable Options :\n"
               "1- Add New Author\n"
               "2- Add New Book \n"
               "3- Update Author Name (Author ID) \n"
               "4- Update Book Title (ISBN) \n"
               "5- Delete Book (ISBN) \n"
               "6- Delete Author (Author ID) \n"
               "7- Print Author (Author ID) \n"
               "8- Print Book (ISBN) \n"
               "9- Write Query \n"
               "0- Exit\n";
        cout << "\nchoose from options above: \n";
        cin >> choice;

        switch (choice) {
            case '1':
                addNewAuthor();
                break;

            case '2':
                addNewBook();
                break;

            case '3': {
                int authorId;
                string newname;
                cout << "enter the author id:";
                cin >> authorId;
                cout << "enter new name:";
                cin >> newname;
                updateAuthorName(authorId, newname);
                break;
            }
            case '4': {
                int bookISBN;
                cout << "enter the book ISBN:";
                cin >> bookISBN;
                string newtitle;
                cout << "Please enter new title:";
                cin >> newtitle;
                updateBookTitle(bookISBN ,newtitle);
                break;
            }
            case '5': {
                int bookISBN;
                cout << "enter the book ISBN:";
                cin >> bookISBN;
                deleteBook(bookISBN);
                break;
            }
            case '6': {
                int authorID;
                cout << "enter the author ID:";
                cin >> authorID;
                deleteAuthor(authorID);
                break;
            }
            case '7': {
                int authorID;
                cout << "enter the author ID:";
                cin >> authorID;
                printAuthor(authorID);
                break;
            }
            case '8': {
                int bookISBN;
                cout << "enter the book ISBN:";
                cin >> bookISBN;
                printBook(bookISBN);
                break;
            }
            case '9':
                writeQuery();
                break;

            case '0': {
                Exit();
                break;
            }

            default:
                cout << "\nyour choice should be between 1 to 10 \n";
                break;
        }
    }
}
//int main(){
//    vector<int> t = search(3000 , "../indexing/PIDB.txt");
//    for(int a : t){
//        cout << a <<'\n';
//    }
////    delete_tuple_in_index(138 , "../indexing/PIDB.txt");
//}