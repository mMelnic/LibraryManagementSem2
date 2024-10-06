#include "Librarian.h"

Librarian::Librarian(std::string username, std::string password, std::string email): User(username, password, email) {}

void Librarian::add_book_to_library(std::vector<Book*>&books)
{
	std::string title, author, genre, isbn;
	int nrCopies, nrPages;
    Utility::get_details(title, "Enter the title: ");
    Utility::get_details(author, "Enter the author: ");
    Utility::get_details(genre, "Enter the genre: ");
    Utility::get_isbn(isbn, books);
    Utility::get_numbers(nrCopies, "Enter the number of copies: ");
    Utility::get_numbers(nrPages, "Enter the number of pages: ");
    std::cin.ignore();

    Book* book = new Book(title, author, genre, isbn, nrCopies, nrPages);
    books.push_back(book);
    std::cout << "Book added successfully!" << std::endl << std::endl;
}

void Librarian::delete_book_from_library(std::vector<Book*>& books)
{
    string isbn_to_delete;
    std::cout << "Enter the ISBN number of the book to be deleted" << std::endl;
    std::cin >> isbn_to_delete;
    bool book_found = false;
    for (auto iterator = books.begin(); iterator != books.end(); ++iterator)
    {
        if (!((*iterator)->get_ISBN().compare(isbn_to_delete)))
        {
            book_found = true;
            delete (*iterator); // deleting the book (copies are deleted correctly bcs of destructor
            books.erase(iterator); //deleting the pointer, avoiding undefined behavior since iterator first incremented
            std::cout << "Book removed successfully!" << std::endl << std::endl;
            break;
        }
    }
    if (!book_found)
        std::cout << "Book not found!" << std::endl;
}

void Librarian::update_book_details(std::vector<Book*>& books)
{
    string isbn_to_update;
    std::cout << "Enter the ISBN number of the book you want to update" << std::endl;
    std::cin >> isbn_to_update;
    bool book_found = false;
    for (auto iterator = books.begin(); iterator != books.end(); ++iterator)
    {
        if (!((*iterator)->get_ISBN().compare(isbn_to_update)))
        {
            book_found = true;
            std::string new_title, new_author, new_genre;
            int new_nrCopies, new_nrPages;
            std::cin.ignore();
            Utility::get_details(new_title, "Enter new title: ");
            Utility::get_details(new_author, "Enter new author: ");
            Utility::get_details(new_genre, "Enter new genre: ");
            Utility::get_numbers(new_nrCopies, "Enter new number of copies: ");
            Utility::get_numbers(new_nrPages, "Enter new number of pages: ");
            std::cin.ignore();

            (*iterator)->setTitle(new_title);
            (*iterator)->setAuthor(new_author);
            (*iterator)->setGenre(new_genre);
            (*iterator)->set_nrPages(new_nrPages);

            //update the copies vector
            int current_nrCopies = (*iterator)->get_nrCopies();
            if (new_nrCopies > current_nrCopies)
            {
                int nr_copies_to_add = new_nrCopies - current_nrCopies;
                for (int i = 0; i < nr_copies_to_add; i++)
                {
                    (*iterator)->add_copy();
                }
            }
            else if (new_nrCopies < current_nrCopies)
            {
                int nr_copies_to_delete = current_nrCopies - new_nrCopies;
                (*iterator)->delete_book_copies(nr_copies_to_delete);
            }
            (*iterator)->set_nrCopies(new_nrCopies);
            std::cout << "Book updated successfully!" << std::endl << std::endl;
            return;
        }
    }
    if (!book_found)
    {
        std::cout << "Book not found!" << std::endl;
    }
}