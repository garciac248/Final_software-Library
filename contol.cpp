#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Placeholder implementations for other classes
class Student {
public:
    string name;
    Student(string n) : name(n) {}
};

class Book {
public:
    string title;
    Book(string t) : title(t) {}
};

class Librarian {
public:
    string name;
    Librarian(string n) : name(n) {}
};

// Updated Interface Class with Smart Pointers
class Interface {
private:
    shared_ptr<Student> creatingAccount;
    shared_ptr<Book> searchingBook;
    shared_ptr<Book> checkingOutBook;
    bool bookStatus;
    shared_ptr<Librarian> librarianAccount;

public:
    // Constructor
    Interface() : bookStatus(false) {}

    // Getters
    shared_ptr<Student> getCreatingAccount() const {
        return creatingAccount;
    }

    shared_ptr<Book> getSearchingBook() const {
        return searchingBook;
    }

    shared_ptr<Book> getCheckingOutBook() const {
        return checkingOutBook;
    }

    bool getBookStatus() const {
        return bookStatus;
    }

    shared_ptr<Librarian> getLibrarianAccount() const {
        return librarianAccount;
    }

    // Setters
    void setCreatingAccount(shared_ptr<Student> ca) {
        creatingAccount = ca;
    }

    void setSearchingBook(shared_ptr<Book> sb) {
        searchingBook = sb;
    }

    void setCheckingOutBook(shared_ptr<Book> cob) {
        checkingOutBook = cob;
    }

    void setBookStatus(bool status) {
        bookStatus = status;
    }

    void setLibrarianAccount(shared_ptr<Librarian> la) {
        librarianAccount = la;
    }
};

int main() {
    // Example usage of the Interface class
    Interface libraryInterface;

    auto student = make_shared<Student>("John Doe");
    auto book = make_shared<Book>("The Great Gatsby");
    auto librarian = make_shared<Librarian>("Jane Smith");

    libraryInterface.setCreatingAccount(student);
    libraryInterface.setSearchingBook(book);
    libraryInterface.setLibrarianAccount(librarian);
    libraryInterface.setBookStatus(true);

    cout << "Creating account for: " << libraryInterface.getCreatingAccount()->name << endl;
    cout << "Searching for book: " << libraryInterface.getSearchingBook()->title << endl;
    cout << "Librarian account: " << libraryInterface.getLibrarianAccount()->name << endl;
    cout << "Book status: " << (libraryInterface.getBookStatus() ? "Available" : "Not Available") << endl;

    return 0;
}
