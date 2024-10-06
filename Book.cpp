#include "Book.h"
#include "Copy.h"

Book::Book(std::string title, std::string author, std::string genre, std::string isbn, int nrCopies, int nrPages, double rating) : 
	title(title), author(author), genre(genre), isbn(isbn), nrCopies(nrCopies), nrPages(nrPages), rating(rating)
{
	copies.reserve(nrCopies);
	for (int i = 0; i < nrCopies; i++)
	{
		copies.push_back(new Copy(*this));
	}
}

Book::Book(const Book& newBook) : title(newBook.title), author(newBook.author),
genre(newBook.genre), rating(newBook.rating), nrCopies(newBook.nrCopies), nrPages(newBook.nrPages)
{
	copies.reserve(newBook.nrCopies);
	for (int i = 0; i < newBook.nrCopies; i++)
	{
		copies.push_back(new Copy(*this));
	}
}

Book::~Book()
{
	for (const auto& copy : copies)
	{
		delete copy;
	}
	copies.clear();
}

void Book::setTitle(std::string title)
{
	this->title = title;
}

std::string Book::getTitle() const
{
	return title;
}

void Book::setAuthor(std::string author)
{
	this->author = author;
}

std::string Book::getAuthor() const
{
	return author;
}

void Book::setGenre(std::string genre)
{
	this->genre = genre;
}

std::string Book::getGenre() const
{
	return genre;
}

std::string Book::get_ISBN() const
{
	return isbn;
}

void Book::setRating(double rating)
{
	this->rating = rating;
}

double Book::getRating() const
{
	return rating;
}

void Book::set_nrCopies(int nrCopies)
{
	this->nrCopies = nrCopies;
}

int Book::get_nrCopies() const
{
	return nrCopies;
}

void Book::set_nrPages(int nrPages)
{
	this->nrPages = nrPages;
}

int Book::get_nrPages() const
{
	return nrPages;
}

std::vector<Copy*> Book::getCopies() const
{
	return copies;
}

void Book::add_copy()
{
	Copy* copy = new Copy(*this);
	copies.push_back(copy);
}

void Book::delete_book_copies(int number)
{
	try
	{
		if (number > copies.size()) 
		{
			throw std::invalid_argument("Cannot remove more copies than there exist in the library!");
		}
		else 
		{
			int copies_removed = 0;
			while (copies_removed < number) // loop to delete 'number' number of copies
			{
				Copy* copy_to_be_removed = copies.back();
				copies.pop_back();
				delete copy_to_be_removed; //delete the dynamically allocated pointer
				copies_removed++;
			}
			std::cout << "Copies removed successfully!" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

int Book::count_available_copies() const
{
	int availableCopies = 0;
	for (const auto& copy : copies)
	{
		if (copy->is_avail()) availableCopies++;
	}
	return availableCopies;
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
	os << book.title << ","
		<< book.author << ","
		<< book.genre << ","
		<< book.isbn << ","
		<< book.rating << ","
		<< book.nrPages << ","
		<< book.nrCopies;
	return os;
}

void Book::printBook() const {
	std::cout << "Title: " << title << std::endl;
	std::cout << "Author: " << author << std::endl;
	std::cout << "Genre: " << genre << std::endl;
	std::cout << "ISBN: " << isbn << std::endl;
	std::cout << "Rating: " << rating << std::endl;
	std::cout << "Number of Pages: " << nrPages << std::endl;
	std::cout << "Number of Copies: " << nrCopies << std::endl;
	std::cout << "Available Copies: " << count_available_copies() << std::endl;
}

double Book::calculate_rating(double new_rating) const
{
	static int total_num_ratings = 0;
	static double total_rating = 0.0;
	total_num_ratings += 1;
	total_rating += new_rating;
	return total_rating / total_num_ratings;
}