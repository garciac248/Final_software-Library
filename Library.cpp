c++ code here
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Student.h"
#include "Librian.h"
#include "Book.h"
#include "Admin.h"

using namespace std;

class Library
{
	private: 
		Admin*  admin;
	Student student;
	Librarian librarian;
	BST <Book> BooksInventory;
	 hashtable <Student> StudentsHashTable
		list<Librarian> LibrarianList;
		int Librarianlimit;

public: 
	Admin getAdmin()
	{
		return Admin;
	}
	Student getStudent()
	{
		return 
	}

	Librarian getLibrarian()
	{
		return Librarian;
	}
	Book getBookSatus()
	{
		return librarian;
	}
	Student getsStudentList()
	{
		return StudentsHashTable;
	}
	void printBookInventory()
	{

	}
	bool searchStudent(int id)
	{
		if (Student.getId() = id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool searchLibrarian(string name)
	{
		if (Librarian.getName() == name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
