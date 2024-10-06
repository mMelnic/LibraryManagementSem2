#pragma once
#include "User.h"
#include "Copy.h"
#include "Utility.h"

class Librarian : public User{
public:
    Librarian() {};
    Librarian(std::string username, std::string password, std::string email);
    void add_book_to_library(std::vector<Book*>& books);
    void delete_book_from_library(std::vector<Book*>& books);
    void update_book_details(std::vector<Book*>& books);
};