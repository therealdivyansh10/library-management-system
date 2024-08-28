#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Base class for all users in the library
class User {
protected:
    string name;
    string userID;

public:
    User(string name, string userID) : name(name), userID(userID) {}

    virtual void viewBooks(const vector<string>& books) {
        cout << "Available books in the library:\n";
        for (const auto& book : books) {
            cout << "- " << book << endl;
        }
    }

    string getName() const {
        return name;
    }

    string getUserID() const {
        return userID;
    }
};

// Derived class for Student
class Student : public User {
public:
    Student(string name, string userID) : User(name, userID) {}

    void borrowBook(string bookName, vector<string>& borrowedBooks) {
        borrowedBooks.push_back(bookName);
        cout << name << " has borrowed the book: " << bookName << endl;
    }

    void returnBook(string bookName, vector<string>& borrowedBooks) {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), bookName), borrowedBooks.end());
        cout << name << " has returned the book: " << bookName << endl;
    }
};

// Derived class for Faculty
class Faculty : public User {
public:
    Faculty(string name, string userID) : User(name, userID) {}

    void borrowBook(string bookName, vector<string>& borrowedBooks) {
        borrowedBooks.push_back(bookName);
        cout << name << " has borrowed the book: " << bookName << endl;
    }

    void returnBook(string bookName, vector<string>& borrowedBooks) {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), bookName), borrowedBooks.end());
        cout << name << " has returned the book: " << bookName << endl;
    }
};

// Admin class that has additional privileges
class Admin : public User {
public:
    Admin(string name, string userID) : User(name, userID) {}

    void addBook(vector<string>& books, string bookName) {
        books.push_back(bookName);
        cout << "Book added: " << bookName << endl;
    }

    void deleteBook(vector<string>& books, string bookName) {
        books.erase(remove(books.begin(), books.end(), bookName), books.end());
        cout << "Book deleted: " << bookName << endl;
    }
};

// Library class that manages the entire library system
class Library {
private:
    vector<string> books;
    map<string, vector<string>> borrowedBooks;

public:
    Library() {}

    void addBook(string bookName) {
        books.push_back(bookName);
    }

    void deleteBook(string bookName) {
        books.erase(remove(books.begin(), books.end(), bookName), books.end());
    }

    void viewBooks() {
        cout << "Available books in the library:\n";
        for (const auto& book : books) {
            cout << "- " << book << endl;
        }
    }

    void borrowBook(User& user) {
        string bookName;
        cout << "Enter the name of the book you want to borrow: ";
        cin.ignore(); // To ignore any leftover newline characters
        getline(cin, bookName);

        if (find(books.begin(), books.end(), bookName) != books.end()) {
            borrowedBooks[user.getUserID()].push_back(bookName);
            books.erase(remove(books.begin(), books.end(), bookName), books.end());
            cout << user.getName() << " borrowed the book: " << bookName << endl;
        } else {
            cout << "Book not available." << endl;
        }
    }

    void returnBook(User& user) {
        string bookName;
        cout << "Enter the name of the book you want to return: ";
        cin.ignore(); // To ignore any leftover newline characters
        getline(cin, bookName);

        if (find(borrowedBooks[user.getUserID()].begin(), borrowedBooks[user.getUserID()].end(), bookName) != borrowedBooks[user.getUserID()].end()) {
            books.push_back(bookName);
            borrowedBooks[user.getUserID()].erase(remove(borrowedBooks[user.getUserID()].begin(), borrowedBooks[user.getUserID()].end(), bookName), borrowedBooks[user.getUserID()].end());
            cout << user.getName() << " returned the book: " << bookName << endl;
        } else {
            cout << "Book not borrowed by " << user.getName() << endl;
        }
    }

    void adminAddBook(Admin& admin) {
        string bookName;
        cout << "Enter the name of the book to add: ";
        cin.ignore(); // To ignore any leftover newline characters
        getline(cin, bookName);
        admin.addBook(books, bookName);
    }

    void adminDeleteBook(Admin& admin) {
        string bookName;
        cout << "Enter the name of the book to delete: ";
        cin.ignore(); // To ignore any leftover newline characters
        getline(cin, bookName);
        admin.deleteBook(books, bookName);
    }
};

int main() {
    // Creating users
    Student student1("Alice", "S001");
    Faculty faculty1("Dr. Bob", "F001");
    Admin admin("Admin", "A001");

    // Creating the library
    Library library;

    // Admin adds books
    library.adminAddBook(admin);
    library.adminAddBook(admin);
    library.adminAddBook(admin);

    // Main loop for interaction
    while (true) {
        int choice;
        cout << "\nLibrary System Menu:\n";
        cout << "1. View Books\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. Admin Add Book\n";
        cout << "5. Admin Delete Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 6) break;

        switch (choice) {
            case 1:
                library.viewBooks();
                break;
            case 2:
                // Assuming the user is a student
                library.borrowBook(student1);
                break;
            case 3:
                // Assuming the user is a student
                library.returnBook(student1);
                break;
            case 4:
                library.adminAddBook(admin);
                break;
            case 5:
                library.adminDeleteBook(admin);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
