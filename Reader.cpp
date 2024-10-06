#include "Reader.h"
#include "Borrowed_Book.h"

Reader::Reader(std::string username, std::string password, std::string email) : 
    User(username, password, email) {}

Reader::Reader(const Reader& other) : User(other)
{
    for (const auto& borrowed_book : other.borrowed_books) {
        borrowed_books.push_back(new BorrowedBook(*borrowed_book));
    }
}

Reader::~Reader()
{
    for (const auto& book : borrowed_books) { 
        delete book;
    }
    borrowed_books.clear();
}

std::vector<BorrowedBook*> Reader::get_borrowed_books() const
{
    return borrowed_books;
}

void Reader::set_borrowed_books(const std::vector<BorrowedBook*> borrowed_books)
{
    this->borrowed_books = borrowed_books;
}

std::vector<Book*> Reader::search_by_title(const std::string& title, const std::vector<Book*>& library)
{
    std::vector<Book*> matching_books;
    for (const auto& book : library)
    {
        if (book->getTitle() == title)
        {
            matching_books.push_back(book);
        }
    }
    return matching_books;
}

std::vector<Book*> Reader::search_by_author(const std::string& author, const std::vector<Book*>& library)
{
    if (author.empty())
    {
        throw std::invalid_argument("Author name cannot be empty.");
    }

    std::vector<Book*> matches;
    for (const auto& book : library)
    {
        if (book != nullptr && book->getAuthor() == author)
        {
            matches.push_back(book);
        }
    }

    if (matches.empty())
    {
        std::cout << "No matches found." << std::endl;
    }
    return matches;
}

bool Reader::borrow_book(Book* book)
{
    // looking for the first available copy
    Copy* copy_to_borrow = nullptr;
    for (const auto& copy : book->getCopies())
    {
        if (copy->is_avail()) {
            copy_to_borrow = copy;
            break;
        }
    }
    if (copy_to_borrow == nullptr)
    {
        std::cerr << "No available copies of " << book->getTitle() << " by " << book->getAuthor() << std::endl;
        return false;
    }

    copy_to_borrow->setAvail(false);
    borrowed_books.push_back(new BorrowedBook(copy_to_borrow, this, book));

    return true;
}

bool Reader::return_book(BorrowedBook* borrowed)
{
    try
    {
        rate_book(borrowed);
        borrowed->getCopy()->setAvail(true);

        for (auto iterator = borrowed_books.begin(); iterator != borrowed_books.end(); iterator++)
        {
            if (*iterator == borrowed)
            {
                delete (*iterator);
                borrowed_books.erase(iterator);
                return true;
            }
        }
        throw std::runtime_error("Borrowed book not found in your list of borrowed books");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

void Reader::rate_book(BorrowedBook* borrowed)
{
    char answer;
    std::cout << "Would you like to rate this book? (y/n) ";
    do {
        std::cin >> answer;
        answer = tolower(answer);
    } while (answer != 'y' && answer != 'n');

    if (answer == 'y')
    {
        double reader_rating;
        bool valid_input = false;
        do {
            std::cout << "Enter your rating on a scale from 0 to 5: ";
            std::cin >> reader_rating;

            valid_input = std::cin.good() && reader_rating >= 0 && reader_rating <= 5;
            if (!valid_input)
            {
                std::cout << "Please enter a number between 0 and 5." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (!valid_input);

        double current_rating = borrowed->getBook()->calculate_rating(reader_rating);
        borrowed->getBook()->setRating(current_rating);
    }
}

void Reader::display_borrowed_books() const
{
    std::cout << "You have borrowed " << borrowed_books.size() << " books:" << std::endl << std::endl;
    for (const auto& borrowed_book : borrowed_books)
    {
        borrowed_book->getBook()->printBook();
        std::cout << std::endl;
    }
}