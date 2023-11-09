#include "mainFunctions.cpp"

int main() {
    int choice;
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
               "10- Exit\n";
        cout << "\nchoose from options above: \n";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewAuthor();
                break;

            case 2:
                addNewBook();
                break;

            case 3:
                int authorId;
                cout << "enter the author id:";
                cin >> authorId;
                updateAuthorName(authorId);
                break;

            case 4: {
                int bookISBN;
                cout << "enter the book ISBN:";
                cin >> bookISBN;
                updateBookTitle(bookISBN);
                break;
            }
            case 5: {
                int bookISBN;
                cout << "enter the book ISBN:";
                cin >> bookISBN;
                deleteBook(bookISBN);
                break;
            }
            case 6: {
                int authorID;
                cout << "enter the author ID:";
                cin >> authorID;
                deleteAuthor(authorID);
                break;
            }
            case 7: {
                int authorID;
                cout << "enter the author ID:";
                cin >> authorID;
                printAuthor(authorID);
                break;
            }
            case 8: {
                int bookISBN;
                cout << "enter the book ISBN:";
                cin >> bookISBN;
                printBook(bookISBN);
                break;
            }
            case 9:
                writeQuery();
                break;

            case 10: {
                Exit();
                break;
            }

            default:
                cout << "\nyour choice should be between 1 to 10 \n";
                break;
        }
    }
}