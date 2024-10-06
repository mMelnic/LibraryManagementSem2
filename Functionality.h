#pragma once
#include <algorithm>
#include <iostream>
#include "Librarian.h"
#include "File_Management.h"

class Librarian;
class Reader;
class BorrowedBook;

int print_mainMenu();
int librarianMenu();
int readerMenu();
int smallMenu();
// Function to handle the main menu functionality
void mainMenu_functionality();
// Function to account for adding, deleting, updating books by librarians
void librarian_functionality(Librarian& librarian, std::vector<Book*>& libraryBooks);
// Function to account for the search, borrowing and returning of books
void reader_functionality(Reader& reader, const std::vector<Book*>& libraryBooks, const std::vector<Reader*>& readers);
void librarian_account(std::vector<Book*>& library_collection);
void reader_account(const std::vector<Book*>& library_collection);