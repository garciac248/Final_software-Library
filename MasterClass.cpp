#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//------------------------------------------------------------------------------------------------------------------------
// Book Class
//------------------------------------------------------------------------------------------------------------------------
class Book {
private:
    string Author;
    string Title;
    string Genre;
    int ISBN;
    bool isCheckedOut;

public:
    Book() : Author("Unknown"), Title("Unknown"), Genre("Unknown"), ISBN(0), isCheckedOut(false) {}
    Book(string a, string t, string g, int isbn) : Author(a), Title(t), Genre(g), ISBN(isbn), isCheckedOut(false) {}

    // Getters
    string getAuthor() const { return Author; }
    string getTitle() const { return Title; }
    string getGenre() const { return Genre; }
    int getISBN() const { return ISBN; }
    bool getCheckOutStatus() const { return isCheckedOut; }

    // Setters
    void setAuthor(const string& a) { Author = a; }
    void setTitle(const string& t) { Title = t; }
    void setGenre(const string& g) { Genre = g; }
    void setISBN(int n) { ISBN = n; }
    void setCheckOutStatus(bool s) { isCheckedOut = s; }

    // Print book details
    void printBookDetails() const {
        cout << "Author: " << Author << "\n"
            << "Title: " << Title << "\n"
            << "Genre: " << Genre << "\n"
            << "ISBN: " << ISBN << "\n"
            << "Checked Out: " << (isCheckedOut ? "Yes" : "No") << "\n\n";
    }
};

//------------------------------------------------------------------------------------------------------------------------
// Student Class
//------------------------------------------------------------------------------------------------------------------------
class Student {
private:
    string Name;
    int Id;
    int Age;
    string Email;

public:
    Student(string name = "Unknown", int age = 0, int id = 0, string email = "Unknown")
        : Name(name), Id(id), Age(age), Email(email) {}

    // Getters
    string getName() const { return Name; }
    int getId() const { return Id; }
    int getAge() const { return Age; }
    string getEmail() const { return Email; }

    // Setters
    void setName(const string& n) { Name = n; }
    void setAge(int a) { Age = a; }
    void setId(int i) { Id = i; }
    void setEmail(const string& e) { Email = e; }
};

//------------------------------------------------------------------------------------------------------------------------
// Librarian Class
//------------------------------------------------------------------------------------------------------------------------
class Librarian {
private:
    string Name;
    string DOB;
    int Age;
    string Email;

public:
    Librarian(string name = "Unknown", string dob = "Unknown", int age = 0, string email = "Unknown")
        : Name(name), DOB(dob), Age(age), Email(email) {}

    // Getters
    string getName() const { return Name; }
    string getDateOfBirth() const { return DOB; }
    int getAge() const { return Age; }
    string getEmail() const { return Email; }

    // Print librarian information
    void printLibrarianInfo() const 
    {
        cout << "Name: " << Name << "\n"
            << "Date of Birth: " << DOB << "\n"
            << "Age: " << Age << "\n"
            << "Email: " << Email << "\n\n";
    }
    void addBooks(Library &l1)
    {
        string author, title, genre;
        int isbn;
        cout << "Enter Author: ";
        cin >> author;
        cout << "Enter Title: ";
        cin >> title;
        cout << "Enter Genre: ";
        cin >> genre;
        cout << "Enter ISBN: ";
        cin >> isbn;
        Book b = Book(author, title, genre, isbn);
        l1.addBookToInventory(b);
    }

    void removeBooks(Library &l1)
    {
        int isbn;
        cout << "Enter ISBN of book to remove: ";
        cin >> isbn;
        l1.removeBookFromInventory(isbn);
    }

    void printInventory(Library &l1)
    {
        l1.printBookInventory();
    }
};

//------------------------------------------------------------------------------------------------------------------------
// Admin Class
//------------------------------------------------------------------------------------------------------------------------
class Admin {
private:
    string Name;
    int Age;
    string DOB;
    string PhoneNumber;
    string Email;

public:
    Admin(string name = "Admin", int age = 30, string dob = "01/01/1990", string phone = "000-000-0000", string email = "admin@example.com")
        : Name(name), Age(age), DOB(dob), PhoneNumber(phone), Email(email) {}

    // Getters
    string getName() const { return Name; }
    int getAge() const { return Age; }
    string getDateOfBirth() const { return DOB; }
    string getPhoneNumber() const { return PhoneNumber; }
    string getEmail() const { return Email; }
};

//------------------------------------------------------------------------------------------------------------------------
// Library Class
//------------------------------------------------------------------------------------------------------------------------
class Library {
private:
    Admin admin;
    unordered_map<int, Student> StudentsHashTable; // Key is student ID
    vector<Book> BooksInventory;                  // Inventory of books
    vector<Librarian> LibrarianList;              // List of librarians (max 5)

public:
    // Methods for Book Management
    void addBookToInventory(const Book& book) {
        BooksInventory.push_back(book);
        cout << "Book added to inventory successfully.\n";
    }

    void removeBookFromInventory(int isbn) {
        auto it = find_if(BooksInventory.begin(), BooksInventory.end(),
            [isbn](const Book& b) { return b.getISBN() == isbn; });
        if (it != BooksInventory.end()) {
            BooksInventory.erase(it);
            cout << "Book removed from inventory.\n";
        }
        else {
            cout << "Book not found in inventory.\n";
        }
    }

    bool checkoutBook(int isbn) {
        for (auto& book : BooksInventory) {
            if (book.getISBN() == isbn && !book.getCheckOutStatus()) {
                book.setCheckOutStatus(true);
                return true;
            }
        }
        return false;
    }

    void returnBook(int isbn) {
        for (auto& book : BooksInventory) {
            if (book.getISBN() == isbn && book.getCheckOutStatus()) {
                book.setCheckOutStatus(false);
                cout << "Book returned successfully.\n";
                return;
            }
        }
        cout << "Book not found or not checked out.\n";
    }

    void printBookInventory() const {
        if (BooksInventory.empty()) {
            cout << "No books in the inventory.\n";
        }
        else {
            for (const auto& book : BooksInventory) {
                book.printBookDetails();
            }
        }
    }

    Book getBookByISBN(int isbn) const {
        for (const auto& book : BooksInventory) {
            if (book.getISBN() == isbn) {
                return book;
            }
        }
        throw runtime_error("Book with the given ISBN not found.");
    }

    // Methods for Student Management
    void addStudent(const Student& student) {
        StudentsHashTable[student.getId()] = student;
        cout << "Student added successfully.\n";
    }

    void removeStudent(int id) {
        if (StudentsHashTable.erase(id)) {
            cout << "Student removed successfully.\n";
        }
        else {
            cout << "Student not found.\n";
        }
    }

    /**void printStudentList() const {
        if (StudentsHashTable.empty()) {
            cout << "No students in the system.\n";
        }
        else {
            for (const auto& [id, student] : StudentsHashTable) {
                cout << "ID: " << id << ", Name: " << student.getName() << "\n";
            }
        }
    }*/

    // Methods for Librarian Management
    void addLibrarian(const Librarian& librarian) {
        if (LibrarianList.size() < 5) {
            LibrarianList.push_back(librarian);
            cout << "Librarian added successfully.\n";
        }
        else {
            cout << "Maximum number of librarians reached.\n";
        }
    }

    void removeLibrarian(const string& name) {
        auto it = remove_if(LibrarianList.begin(), LibrarianList.end(),
            [&name](const Librarian& lib) { return lib.getName() == name; });
        if (it != LibrarianList.end()) {
            LibrarianList.erase(it, LibrarianList.end());
            cout << "Librarian removed successfully.\n";
        }
        else {
            cout << "Librarian not found.\n";
        }
    }

    void printLibrarianList() const {
        if (LibrarianList.empty()) {
            cout << "No librarians in the system.\n";
        }
        else {
            for (const auto& librarian : LibrarianList) {
                librarian.printLibrarianInfo();
            }
        }
    }
};

//------------------------------------------------------------------------------------------------------------------------
// Menus and Main Function
//------------------------------------------------------------------------------------------------------------------------
void AdminMenu(Library& library) {
    int choice;
    cout << "\nWelcome Admin!\n";
    cout << "1. Add Librarian\n2. Remove Librarian\n3. Add Student\n4. Remove Student\n";
    cin >> choice;

    switch (choice) {
    case 1: {
        string name, dob, email;
        int age;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter DOB: ";
        cin >> dob;
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Email: ";
        cin >> email;
        library.addLibrarian(Librarian(name, dob, age, email));
        break;
    }
    case 2: {
        string name;
        cout << "Enter Librarian Name to remove: ";
        cin >> name;
        library.removeLibrarian(name);
        break;
    }
    case 3: {
        string name, email;
        int age, id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Email: ";
        cin >> email;
        library.addStudent(Student(name, age, id, email));
        break;
    }
    case 4: {
        int id;
        cout << "Enter Student ID to remove: ";
        cin >> id;
        library.removeStudent(id);
        break;
    }
    default:
        cout << "Invalid choice.\n";
        break;
    }
}

void LibrarianMenu(Libriarian& librarian, Library& library) {
    bool flag = true;
    while (flag) 
    {
        int choice;
        cout << "\n\nWelcome Librarian! What do you want to do?\n";
        cout << "Enter '1' to add a book to the inventory.\n";
        cout << "Enter '2' to remove a book from the inventory.\n";
        cout << "Enter '3' to display the book inventory.\n";
        cout << "Enter '4' to exit.\n";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                librarian.addBooks(library);
                break;
            }
            case 2: 
            {
                librarian.removeBooks(library);
                break;
            }
        case 3:
            {
                librarian.printInventory(library);
                break;
            }
        default:
            {
                cout << "Invalid choice.\n";
                break;
            }
        }
    }  
}

void StudentMenu(Library& library) {
    int choice;
    cout << "\nWelcome Student!\n";
    cout << "1. Search Book\n2. Checkout Book\n3. Return Book\n";
    cin >> choice;

    switch (choice) {
    case 1: {
        int isbn;
        cout << "Enter ISBN to search: ";
        cin >> isbn;
        try {
            Book book = library.getBookByISBN(isbn);
            book.printBookDetails();
        }
        catch (runtime_error& e) {
            cout << e.what() << "\n";
        }
        break;
    }
    case 2: {
        int isbn;
        cout << "Enter ISBN to checkout: ";
        cin >> isbn;
        if (library.checkoutBook(isbn)) {
            cout << "Book checked out successfully.\n";
        }
        else {
            cout << "Book not available for checkout.\n";
        }
        break;
    }
    case 3: {
        int isbn;
        cout << "Enter ISBN to return: ";
        cin >> isbn;
        library.returnBook(isbn);
        break;
    }
    default:
        cout << "Invalid choice.\n";
        break;
    }
}

int main() {
    Library library;
    int userType;

    cout << "WELCOME TO THE LIBRARY SOFTWARE\n";
    cout << "Please enter from following options:\n1. Admin\n2. Librarian\n3. Student\n";
    cin >> userType;

    switch (userType) {
    case 1:
        AdminMenu(library);
        break;
    case 2:
        LibrarianMenu(library);
        break;
    case 3:
        StudentMenu(library);
        break;
    default:
        cout << "Invalid input. Exiting...\n";
        break;
    }
    return 0;
}

