#include "Borrowed_Book.h"

BorrowedBook::BorrowedBook(Copy* copy, Reader* borrower, Book* book) : copy(copy), borrower(borrower), book(book) {}

Copy* BorrowedBook::getCopy() const
{
	return copy;
}

const Reader* BorrowedBook::getReader() const
{
	return borrower;
}

Book* BorrowedBook::getBook() const
{
	return book;
}

std::ostream& operator<<(std::ostream& os, const BorrowedBook& borrowedBook)
{
    os << borrowedBook.book->getTitle() << ","
        << borrowedBook.book->getAuthor() << ","
        << borrowedBook.book->get_ISBN() << ","
        << borrowedBook.copy->get_copyId();
    return os;
}