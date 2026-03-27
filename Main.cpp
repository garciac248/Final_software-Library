//HEEYY I'm making this change
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <unordered_map>
using namespace std;
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------

class Book {
private:
    string Author;
    string Title;
    string Genre;
    int ISBN;
    bool isCheckedOut;

public:
    Book(){
        Author = "Unknown";
        Title = "Unknown";
        Genre = "Unknown";
        ISBN = 0;
        isCheckedOut = false;
    }
    Book(string a, string t, string g, int isbn){
        Author = a;
        Title = t;
        Genre = g;
        ISBN = isbn;
        isCheckedOut = false;
    }
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

    // Method to print book details
    void printBookDetails() const {
        cout << "Author: " << Author << "\n"
             << "Title: " << Title << "\n"
             << "Genre: " << Genre << "\n"
             << "ISBN: " << ISBN << "\n"
             << "Checked Out: " << (isCheckedOut ? "Yes" : "No") << "\n\n\n";
    }

    ~Book(){};
};

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
class Librarian {
private:
    string Name;
    string DOB; 
    int Age;
    string Email;

public:
    Librarian()
    {   Name = "";
        DOB = "";
        Age = 0;
        Email = "";   }
    Librarian(string name, string dob, int age, string email)
    {   Name = name;
        DOB = dob;
        Age = age;
        Email = email;   
    }

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

    // Update book details, this function needs to be redone so that it accesses the datastructure in library class
   /* void updateBookDetails(const Book& updatedBook) {
        for (auto& book : bookCollection) {
            if (book.getISBN() == updatedBook.getISBN()) {
                book = updatedBook;
                return;
            }
        }
        cout << "Book not found in the collection.\n";
    }*/

    // Print librarian information
    void printLibrarianInfo() const {
        cout << "Name: " << Name << "\n"
             << "Date of Birth: " << DOB << "\n"
             << "Age: " << Age << "\n"
             << "Email: " << Email << "\n\n";
    }

    ~Librarian(){};
};

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
class Student {
private:
    string Name;
    int Id;
    int Age;
    string Email;
    Book CurrentBooksCheckedOut[5];//array for books checked out
    int NumOfBooks;
public:
    Student(string name,int age, int id, string email){
        Name = name;
        Id = id;
        Age = age;
        Email = email;
        NumOfBooks = 0;
    }
    // Getter functions
    string getName() {return Name;}
    int getId() {return Id;}
    int getAge(){return Age;}
    string getEmail() {return Email;}
    int getNumOfBooksCheckedOut() {return NumOfBooks;}

    // Setter functions
    void setName(string& n) {Name = n;}
    void setAge(int a){Age = a;}
    void setId(int i) {Id = i;}
    void setEmail(string& e) {Email = e;}

    void studentDetails()
    {
        cout << "Student name is: " << Name << "\n";
        cout << "Student age is: " << Age << "\n";
        cout << "Student id is:  " << Id << "\n";
        cout << "Student email is: " << Email << "\n";
    }

    ~Student(){};
};

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//BST for Student
struct Node {
    Student student;      // Store the student object
    Node* left;    // Pointer to the left child
    Node* right;   // Pointer to the right child

    Node(Student s) : student(s), left(nullptr), right(nullptr) {}
};
class StudentBST {
private:
    Node* root;

    // Helper function to insert a student node recursively
    Node* insert(Node* node, Student s) {
        if (node == nullptr) {
            return new Node(s);
        }
        if (s.getId() < node->student.getId()) {
            node->left = insert(node->left, s);
        } else if (s.getId() > node->student.getId()) {
            node->right = insert(node->right, s);
        }
        return node;
    }

    // Helper function to search for a student node by ID
    Student* search(Node* node, int id) {
        if (node == nullptr) {
            return nullptr;
        }
        if (id == node->student.getId()) {
            return &(node->student);
        }
        if (id < node->student.getId()) {
            return search(node->left, id);
        } else {
            return search(node->right, id);
        }
    }

    // Helper function for in-order traversal
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << "Student ID: " << node->student.getId() 
                 << ", Name: " << node->student.getName()
                 << ", Age: "<< node->student.getAge()
                 << ", Email: "<< node->student.getEmail() << endl;
            inorder(node->right);
        }
    }

    // Helper function to find the minimum value node
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Helper function to delete a node
    Node* deleteNode(Node* node, int id) {
        if (node == nullptr) return node;

        // Search for the node to be deleted
        if (id < node->student.getId()) {
            node->left = deleteNode(node->left, id);
        } else if (id > node->student.getId()) {
            node->right = deleteNode(node->right, id);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor
            Node* temp = minValueNode(node->right);
            node->student = temp->student;
            node->right = deleteNode(node->right, temp->student.getId());
        }
        return node;
    }

public:
    StudentBST() : root(nullptr) {}

    void insert(Student s) {
        root = insert(root, s);
    }

    Student* search(int id) {
        return search(root, id);
    }

    void deleteStudent(int id) {
        root = deleteNode(root, id);
    }

    void display() {
        inorder(root);
        cout << endl;
    }
};

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
class Library
{
	private:
	vector <Book> BooksInventory;//vecotr of books in library - fast searching
	unordered_map<int, Student> StudentsHashTable; // key will be student id
    StudentBST studentBST; 
	Librarian LibrarianList[5]; //max 5 librarians at a time

public: 
    bool getBookSatus(){return true; }
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

    void displayStudentBST(){
        cout<< "\nFollowing are the current students in the Library!!\n";
        studentBST.display();
    }
    void printLibrarianList(){
        cout<<"\nFollowing are the current Librarians in the Library!! \n"; 
        for(int i=0; i<5; i++){
            if(LibrarianList[i].getAge() != 0){
               LibrarianList[i].printLibrarianInfo(); }
        }
        cout << "\n\n";
    }

    void AddALibrarian(Librarian& l){
        for(int i=0; i<5; i++){
            if(LibrarianList[i].getAge() == 0){
                LibrarianList[i].setName(l.getName());
                LibrarianList[i].setAge(l.getAge());
                LibrarianList[i].setDateOfBirth(l.getDateOfBirth());
                LibrarianList[i].setEmail(l.getEmail());
                break;
            }
            if(i==4){
                cout << "\nCannot add a librarian because 5 librarians already exist.\n";
            }
        }


    }
    
    void removeTheLibrarian(string name){
        for(int i=0; i<5; i++){
            if(LibrarianList[i].getName() == name){
                LibrarianList[i].setName("");
                LibrarianList[i].setAge(0);
                LibrarianList[i].setDateOfBirth("");
                LibrarianList[i].setEmail("");
            }
            
        }
    }

    void AddAStudent(Student s){
        studentBST.insert(s);
    }
    
    void removeStudent(int id){
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

    void checkoutbook(Library& l1)
    {
       // NumOfBooks;
        
        int isbn;
        cout << "Enter ISBN to checkout: ";
        cin >> isbn;

        auto& inventory = l1.getBooksInventory(); 
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

        
        it->setCheckOutStatus(true);
        NumOfBooks++; 
        cout << "Book checked out successfully.\n";
    }

    void displayCheckedOutBooks()  
    {
        
        cout <<"You" << " have checked out " << NumOfBooks << " book(s).\n";
    }

void returnbook(Library& l1) 
{
    int isbn;
    cout << "Enter ISBN to return: ";
    cin >> isbn;

    bool found;

    auto it = find_if(l1.BooksInventory.begin(), l1.BooksInventory.end(),
        [isbn](const Book& book) { return book.getISBN() == isbn; });

    if (it != l1.BooksInventory.end()) {
        it->setCheckOutStatus(false);
        cout << "Book returned successfully.\n";
    }
    else {
        cout << "Book not found in the library inventory.\n";
    }

    
    for (int j = 5; j < NumOfBooks - 1; ++j) {
        CurrentBooksCheckedOut[j] = CurrentBooksCheckedOut[j + 1];
    }
    NumOfBooks--;  


    if (found == false)
    {
        cout << "NOt checked out" << endl;
    }

}


    void updateBookStatus(int isbn, bool newStatus) 
    {
        auto it = find_if(BooksInventory.begin(), BooksInventory.end(), [isbn](const Book& book) { return book.getISBN() == isbn; });

        if (it != BooksInventory.end()) 
        {
            it->setCheckOutStatus(newStatus);
            cout << "Book with ISBN " << isbn << " has been updated to " << (newStatus ? "is checked out." : "is available.") << "\n";
        }
        else 
        {
            cout << "Book with ISBN " << isbn << " is not in the inventory.\n";
        }
    }
};

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
class Admin {
private:
    string Name;
    int Age;
    string DOB; // Date of birth, assuming it is an integer (e.g., YYYYMMDD)
    string PhoneNumber;
    string Email;

public:
    Admin(string name, int age, string dob, string phone, string email)
    {
        Name = name;
        Age = age;
        DOB = dob;
        PhoneNumber = phone;
        Email = email;
    }
    // Getter functions
    string getName() {return Name;}
    int getAge() {return Age;}
    string getDateOfBirth() {return DOB;}
    string getPhoneNumber() {return PhoneNumber;}
    string getEmail() {return Email;}

    // Setter functions
    void setName(const string& n) {Name = n;}
    void setAge(int a) {Age = a;}
    void setDateOfBirth(string d) {DOB = d;}
    void setPhoneNumber(const string& p) {PhoneNumber = p;}
    void setEmail(const string& e) {Email = e;}

    void handleLibrarianCreation(Library& l1) {
         string name, dob, email;
        int age;
        cout << "\nEnter the Librarian name: ";
        cin >> name;
        cout << "\nEnter the Librarian Date of Birth: ";
        cin >> dob;
        cout << "\nEnter the Librarian Age: ";
        cin >> age;
        cout << "\nEnter the Librarian Email: ";
        cin >> email;
        cout<< "\n\n";
        Librarian l = Librarian(name, dob, age, email);
        
        //add this librarian to data structure in Library class.
            l1.AddALibrarian(l);
    }

    void RemoveALibrarian(Library& l1){
        string name; 
        cout << "Enter the name for librarian that you would like to remove: \n";
        cin >> name;

        l1.removeTheLibrarian(name);
        //remove this librarian from the librarianlist in library class using name 
        //then delete this librarian object.

    }

    void HandleStudentCreation(Library& l1) {
         string name, email;
        int age, id;
        cout << "\nEnter the Student's name: ";
        cin >> name;
        cout << "\nEnter the Student's age: ";
        cin >> age;
        cout << "\nEnter the Student's Id (5 digit #####): ";
        cin >> id;
        cout << "\nEnter the Student's Email: ";
        cin >> email;
        Student s = Student(name, age, id, email);

        //add this student to the datastructure studentlist in library class.
        l1.AddAStudent(s);
    }

    void RemoveAStudent(Library l1) { 
        int id;
        cout << "\nEnter the id for Student you would like to remove: \n";
        cin >> id;
        l1.removeStudent(id);
    }

    void DisplayAdminDetails(){
        cout<< "Admin name is: " << Name << "\n";
        cout<< "Admin age is: " << Age << "\n";
        cout<< "Admin date of birth is: " << DOB << "\n";
        cout<< "Admin phone number is: " << PhoneNumber << "\n";
        cout<< "Admin email is: " << Email << "\n";
    }
};
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
void AdminMenu(Admin& admin, Library& l1)
{   
    bool flag = true;
    while(flag){

    int x;
    cout <<"\n\nWelcome Admin!! What Do You Want To Do.\n";
    cout <<"Enter '1' to add a Librarian to the system.\n";
    cout <<"Enter '2' to remove a Librarian from the system.\n";
    cout <<"Enter '3' to add a Student to the system.\n";
    cout <<"Enter '4' to remove a Student from the system.\n";
    cout <<"Enter '5' to display the list of librarians working.\n";
    cout <<"Enter '6' to display the list of Students in the system.\n";
    cout <<"Enter '7' to display admin details.\n";
    cout <<"Enter '8' to return to Main Menu\n";
    cin >> x;
    switch(x) 
    {
        case 1:
            admin.handleLibrarianCreation(l1);//done
            break;
        case 2:
            admin.RemoveALibrarian(l1);//done
            break;
        case 3:
            admin.HandleStudentCreation(l1);//done
            break;
        case 4:
            admin.RemoveAStudent(l1);
            
            break;
        case 5:
            l1.printLibrarianList();//done
            break;
        case 6:
            l1.displayStudentBST();//done
            break;
        case 7:
            admin.DisplayAdminDetails();//done
            break;
        case 8:
            flag = false;
            break;
        default:
            cout<<"Invalid Input,try again!!";
            break;
    }
    }

        
}

void LibrarianMenu(Library& l1)
{
    bool flag = true;
    while (flag) {

        int choice;
        cout << "\nWelcome Librarian!\n";
        cout << "1. Add a Book\n2. Remove a Book\n3. Print Book Inventory\n4. Search Book using ISBN\n5. Change Book Status\n6. Return to Main Menu\n";
        cin >> choice;

        switch (choice) {
        case 1: {
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
            break;
        }
        case 2: {
            int isbn;
            cout << "Enter ISBN of book to remove: ";
            cin >> isbn;
            l1.removeBookFromInventory(isbn);
            break;
        }
        case 3:
            l1.printBookInventory();
            break;
        case 4:
            l1.searchbook(l1);
            break;
        case 5:
        {
            int isbn;
            char option;
            bool status;

            cout << "Please enter the ISBN of the Book: ";
            cin >> isbn;
            cout << "Is this book being returned?(Y/N)";
            cin >> option;

            if (option == 'Y' || option == 'y')
            {
                status = false;
            }
            else
            {
                status = true;
            }

            l1.updateBookStatus(isbn, status);
            break;
        }
        case 6:
            flag = false;
            break;
        default:
            cout << "Invalid choice.\n";
            break;

        }
    }
}

 void StudentMenu(Library& l1)
{
    bool flag = true;
    while(flag){

    int x;
    cout << "\nWelcome Student!\n";
    cout << "1. Search a book \n2. checkout a book\n3. return a book\n4. Number of books checkout\n5.Return to Main Menu\n";
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
          l1.displayCheckedOutBooks();
          break;
      case 5:
        flag = false;
        break;
      default:
        cout << "Invalid choice.\n";
        break;
    }
    }
}

int main()
{
    Admin admin = Admin("Abdul", 21, "03-03-2003", "609-214-0658", "Anjuma3@uhv.edu");
    Library l1 = Library();
    
	
    bool flag = true;
    while(flag){

    int x;
    cout << "WELCOME TO THE LIBRARY SOFTWARE\n\t" ; 
    cout << "Enter 1 for admin.\n\tEnter 2 for librarian.\n\tEnter 3 for Student.\n\tEnter 4 to Exit Program.\n";
    cin >> x;
    
    switch(x) 
    {
        case 1:
            AdminMenu(admin,l1);
            break;
        case 2:
            LibrarianMenu(l1);
            break;
        case 3:
            StudentMenu(l1);
            break;
        case 4:
            flag=false;
            break;
        default:
            cout<<"\tInvalid Input, Try Again!\n";
            break;
    }
    }

    return 0;
}

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
