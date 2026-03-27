#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Student.h"
#include "Librarian.h"
#include "Book.h"

using namespace std;

class Admin {
private:
    string Name;
    int Age;
    int DOB; // Date of birth, assuming it is an integer (e.g., YYYYMMDD)
    string PhoneNumber;
    string Email;
    string Address;

public:
    // Getter functions
    string getName() {
        return Name;
    }

    int getAge() {
        return Age;
    }

    int getDateOfBirth() {
        return DOB;
    }

    string getPhoneNumber() {
        return PhoneNumber;
    }

    string getEmail() {
        return Email;
    }

    string getAddress() {
        return Address;
    }

    // Setter functions
    void setName(const string& n) {
        Name = n;
    }

    void setAge(int a) {
        Age = a;
    }

    void setDateOfBirth(int d) {
        DOB = d;
    }

    void setPhoneNumber(const string& p) {
        PhoneNumber = p;
    }

    void setEmail(const string& e) {
        Email = e;
    }

    void setAddress(const string& a) {
        Address = a;
    }

    // Methods for adding and removing entities
    void AddStudent(const Student& s) {
        // Add student based on Student object s
    }

    void RemoveStudent(const Student& s) {
        // Remove student based on Student object s
    }

    void AddLibrarian(const Librarian& l) {
        // Add librarian based on Librarian object l
    }

    void RemoveLibrarian(const Librarian& l) {
        // Remove librarian based on Librarian object l
    }

    void addBook(const Book& b) {
        // Add book based on Book object b
    }

    void removeBook(const Book& b) {
        // Remove book based on Book object b
    }
};
