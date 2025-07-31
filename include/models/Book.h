#pragma once
#include <string>
#include <vector>

class Copy;
using std::string;
class Book {
	std::string title, author, genre, isbn;
	double rating;
	int nrCopies, nrPages;
	std::vector<Copy*> copies;

public:
	Book(std::string title, std::string author, std::string genre, std::string isbn, int nrCopies, int nrPages, double rating = 0.0);
	Book(const Book& newBook);
	~Book();

	// Setters and getters
	void setTitle(std::string title);
	std::string getTitle() const;
	void setAuthor(std::string author);
	std::string getAuthor() const;
	void setGenre(std::string genre);
	std::string getGenre() const;
	std::string get_ISBN() const;
	void setRating(double rating);
	double getRating() const;
	void set_nrCopies(int nrCopies);
	int get_nrCopies() const;
	void set_nrPages(int nrPages);
	int get_nrPages() const;
	std::vector<Copy*> getCopies() const;

	// Methods to modify the copies vector by adding or deleting copies
	void add_copy();
	void delete_book_copies(int number);

	int count_available_copies() const;

	// Operator to print a Book object to an output stream
	friend std::ostream& operator<<(std::ostream& os, const Book& book);

	void printBook() const;

	// Method to calculate the average rating of a book
	double calculate_rating(double new_rating) const;
};