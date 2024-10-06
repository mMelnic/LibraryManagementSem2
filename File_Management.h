#pragma once
#include "Book.h"
#include "Borrowed_Book.h"

// Function to convert user-defined objects to string, mainly Book and BorrowedBook objects
template<typename T>
std::string object_to_string(const T& object);
void create_file_if_not_exists(const std::string& filename);
void add_books_to_file(const std::vector<Book*>& books, const std::string& filename);
std::vector<Book*> load_books_from_file(const std::string& filename);
void add_borrowedBooks_to_file(const std::vector<Reader*>& readers, const std::string& filename);
std::vector<BorrowedBook*> load_borrowedBooks_from_file(Reader& reader, const std::vector<Book*>& library_collection, const std::string& filename);
std::vector<Reader*> load_readers_from_file(const std::string& filename);

template<typename T>
inline std::string object_to_string(const T& object)
{
    std::ostringstream ss;
    ss << object;
    // Convert the contents of the string stream to a string and return it
    return ss.str();
}