#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include "Book.h"
#include "Student.h"
#include "Admin.h"
#include "Library.h"

class Interface {
private:
    Student* creatingAccount;
    Book* searchingBook;
    Book* checkingOutBook;
    bool bookStatus;
    Librarian* librarianAccount;

public:
    // Constructor
    Interface() : creatingAccount(nullptr), searchingBook(nullptr), 
                  checkingOutBook(nullptr), bookStatus(false), librarianAccount(nullptr) {}

    // Getters
    Student* getCreatingAccount() const {
        return creatingAccount;
    }

    Book* getSearchingBook() const {
        return searchingBook;
    }

    Book* getCheckingOutBook() const {
        return checkingOutBook;
    }

    bool getBookStatus() const {
        return bookStatus;
    }

    Librarian* getLibrarianAccount() const {
        return librarianAccount;
    }

    // Setters
    void setCreatingAccount(Student* ca) {
        creatingAccount = ca;
    }

    void setSearchingBook(Book* sb) {
        searchingBook = sb;
    }

    void setCheckingOutBook(Book* cob) {
        checkingOutBook = cob;
    }

    void setBookStatus(bool status) {
        bookStatus = status;
    }

    void setLibrarianAccount(Librarian* la) {
        librarianAccount = la;
    }
};
