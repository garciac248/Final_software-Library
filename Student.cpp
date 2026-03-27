#include <iostream>
#include <string>
#include <list>
#include <vector>


class Library
{
private:
    vector <Book> BooksInventory;//vecotr of books in library - fast searching
    unordered_map<int, Student> StudentsHashTable; // key will be student id
    StudentBST studentBST;
    Librarian LibrarianList[5]; //max 5 librarians at a time

public:
    bool getBookSatus() { return true; }
    int NumOfBooks = 0; // added this so variable can work 
    Book CurrentBooksCheckedOut[5]; // added this so the array can work

    vector<Book>& getBooksInventory() // added this function so BooksInventory can be acces
    {
        return BooksInventory;
    }

    void printBookInventory() const
    {
        if (BooksInventory.empty())
        {
            cout << "No books in the inventory.\n";
        }
        else
        {
            for (const auto& book : BooksInventory)
            {
                book.printBookDetails();
            }
        }
    }
    void displayStudentBST() {
        cout << "\nFollowing are the current students in the Library!!\n";
        studentBST.display();
    }
    void printLibrarianList() {
        cout << "\nFollowing are the current Librarians in the Library!! \n";
        for (int i = 0; i < 5; i++) {
            if (LibrarianList[i].getAge() != 0) {
                LibrarianList[i].printLibrarianInfo();
            }
        }
        cout << "\n\n";
    }

    void AddALibrarian(Librarian& l) {
        for (int i = 0; i < 5; i++) {
            if (LibrarianList[i].getAge() == 0) {
                LibrarianList[i].setName(l.getName());
                LibrarianList[i].setAge(l.getAge());
                LibrarianList[i].setDateOfBirth(l.getDateOfBirth());
                LibrarianList[i].setEmail(l.getEmail());
                break;
            }
            if (i == 4) {
                cout << "\nCannot add a librarian because 5 librarians already exist.\n";
            }
        }


    }

    void removeTheLibrarian(string name) {
        for (int i = 0; i < 5; i++) {
            if (LibrarianList[i].getName() == name) {
                LibrarianList[i].setName("");
                LibrarianList[i].setAge(0);
                LibrarianList[i].setDateOfBirth("");
                LibrarianList[i].setEmail("");
            }

        }
    }

    void AddAStudent(Student s) {
        studentBST.insert(s);
    }

    void removeStudent(int id) {
        studentBST.deleteStudent(id);
    }

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
    bool searchStudent(int id)//needs to return a student object from data structure
    {
        //		if (Student.getId() = id)
        {
            return true;
        }
        //		else
        {
            return false;
        }
    }
    bool searchLibrarian(string name)//needs to return a librarian object from data structure
    {
        //		if (Librarian.getName() == name)
        { return true; }
        //	    else
        { return false; }
    }
    //Book searchBook(string bookName){}//needs to return a book from the data structure

//Student menu function start here
    void searchbook(Library& l1) {
        int isbn;
        cout << "Enter ISBN to search: ";
        cin >> isbn;

        
        const vector<Book>& inventory = l1.getBooksInventory();
        auto it = find_if(inventory.begin(), inventory.end(),
            [isbn](const Book& book) { return book.getISBN() == isbn; });

        if (it != inventory.end()) {
            cout << "Book found:\n";
            it->printBookDetails();
        }
        else {
            cout << "Book with ISBN " << isbn << " not found.\n";
        }
    }

    void checkoutbook(Library& l1) {
        int isbn;
        cout << "Enter ISBN to checkout: ";
        cin >> isbn;

        const vector<Book>& inventory = l1.getBooksInventory();
        auto it = find_if(inventory.begin(), inventory.end(),
            [isbn](const Book& book) { return book.getISBN() == isbn; });

        if (it == inventory.end()) {
            cout << "Book with ISBN " << isbn << " not found in the library.\n";
            return;
        }

        if (it->getCheckOutStatus()) {
            cout << "Book with ISBN " << isbn << " is already checked out.\n";
            return;
        }

        if (NumOfBooks >= 5) {
            cout << "You have reached the limit of checked-out books.\n";
            return;

        }
        cout << "Book checked out successfully.\n";
    }

 

    void returnbook(Library& l1) 
    {
        int isbn;
        cout << "Enter ISBN to return: ";
        cin >> isbn;

        bool found = false;


        for (int i = 0; i < NumOfBooks; i++) {
            if (CurrentBooksCheckedOut[i].getISBN() == isbn) {
                found = true;
                l1.returningBook(isbn);
                cout << "Book returned successfully.\n";
                break;
            }
        }

        if (!found) {
            cout << "You have not checked out a book with ISBN " << isbn << ".\n";
        }
    }
    // Added this function so that returnbook function works
    void returningBook(int isbn) 
    {
        auto it = find_if(BooksInventory.begin(), BooksInventory.end(),
            [isbn](const Book& book) { return book.getISBN() == isbn; });
        if (it != BooksInventory.end()) {
            it->setCheckOutStatus(false);
        }
    }
};

void StudentMenu(Student& student, Library& l1)
{
    
    int x;
    cout << "\nWelcome Student!\n";
    cout << "1. Search a book \n2. checkout a book\n3. return a book\n4. Display Student Details\n";
    cin >> x;

    switch(x)
    {
      case 1:
          l1.searchbook(l1);
          break;
      case 2:
          l1.checkoutbook(l1);
          break;
      case 3:
          l1.returnbook(l1);
          break;
      case 4:
          student.studentDetails();
          break;
    }
}

int main()
{
    Admin admin = Admin("Abdul", 21, "03-03-2003", "609-214-0658", "Anjuma3@uhv.edu");
    Student student = Student("Carlos", 21, 12345, "carlos.gmail.com");
    Library l1 = Library();

    

    int x;
    cout << "WELCOME TO THE LIBRARY SOFTWARE\n\t";
    cout << "Enter 1 for admin.\n\tEnter 2 for librarian.\n\tEnter 3 for Student.";
    cin >> x;

    switch (x)
    {
    case 1:
        AdminMenu(admin, l1);
        break;
    case 2:
        LibrarianMenu(l1);
        break;
    case 3:
        StudentMenu(student,l1);
        break;
    default:
        cout << "Invalid Input, Run the software again!";
        break;
    }

    return 0;
}


void returnbook(Library& l1) {
    int isbn;
    cout << "Enter ISBN to return: ";
    cin >> isbn;

    bool found = false;

    for (int i = 0; i < NumOfBooks; ++i) {
        if (CurrentBooksCheckedOut[i].getISBN() == isbn) {
            found = true;

            // Find and update the book in the library inventory
            auto it = find_if(l1.BooksInventory.begin(), l1.BooksInventory.end(),
                [isbn](const Book& book) { return book.getISBN() == isbn; });

            if (it != l1.BooksInventory.end()) {
                it->setCheckOutStatus(false);
                cout << "Book returned successfully.\n";
            } else {
                cout << "Book not found in the library inventory.\n";
            }

            // Remove the book from CurrentBooksCheckedOut
            for (int j = i; j < NumOfBooks - 1; ++j) {
                CurrentBooksCheckedOut[j] = CurrentBooksCheckedOut[j + 1];
            }
            NumOfBooks--;  // Reduce the number of checked-out books
            break;         // Exit the loop early as the book is processed
        }
    }

    if (!found) {
        cout << "Book with ISBN " << isbn << " not found in your checked-out list.\n";
    }
