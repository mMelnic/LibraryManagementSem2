#pragma once
#include <algorithm>
#include "User.h"

class BorrowedBook;
class Reader : public User {
    std::vector<BorrowedBook*> borrowed_books;

public:
    Reader() {};
    Reader(string username, string password, string email);
    Reader(const Reader& other);
    ~Reader();

    std::vector<BorrowedBook*> get_borrowed_books() const;
    void set_borrowed_books(const std::vector<BorrowedBook*> borrowed_books);

    std::vector<Book*> search_by_title(const string& title, const std::vector<Book*>& library);
    std::vector<Book*> search_by_author(const string& author, const std::vector<Book*>& library);
    
    // Method to borrow a copy and update the borrowed books of a reader
    bool borrow_book(Book* book);
    // Method to return a copy and update the borrowed books list of a reader
    bool return_book(BorrowedBook* borrowed);
    void rate_book(BorrowedBook* borrowed);
    void display_borrowed_books() const;
};