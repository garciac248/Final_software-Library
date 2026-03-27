#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Librarian {
private:
    string Name;
    string DOB; 
    int Age;
    string Email;
    vector<Book> bookCollection;

public:
    // Getters
    string getName() const { return Name; }
    string getDateOfBirth() const { return DOB; }
    int getAge() const { return Age; }
    string getEmail() const { return Email; }

    // Setters
    void setName(const string& n) { Name = n; }
    void setDateOfBirth(const string& d) { DOB = d; }
    void setAge(int a) { Age = a; }
    void setEmail(const string& e) { Email = e; }

    // Add a book to the collection
    void addBook(const Book& b) {
        bookCollection.push_back(b);
    }

    // Remove a book from the collection
    void removeBook(const Book& b) {
    auto it = find_if(bookCollection.begin(), bookCollection.end(),[&b](const Book& book) { return book.getISBN() == b.getISBN(); });
    if (it != bookCollection.end()) {
        bookCollection.erase(it);
        cout << "Book removed.\n";
    } else {
        cout << "Book not found.\n";
    }
    }

    // Update book details
    void updateBookDetails(const Book& updatedBook) {
        for (auto& book : bookCollection) {
            if (book.getISBN() == updatedBook.getISBN()) {
                book = updatedBook;
                return;
            }
        }
        cout << "Book not found in the collection.\n";
    }

    // Print librarian information
    void printLibrarianInfo() const {
        cout << "Name: " << Name << "\n"
             << "Date of Birth: " << DOB << "\n"
             << "Age: " << Age << "\n"
             << "Email: " << Email << "\n";
    }
};

