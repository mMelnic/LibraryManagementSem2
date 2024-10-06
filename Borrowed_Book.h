#pragma once
#include "Reader.h"
#include "Copy.h"

class BorrowedBook {
    Copy* const copy;
    const Reader* const borrower;
    Book* const book;

public:
    BorrowedBook(Copy* copy, Reader* borrower, Book* book);
    Copy* getCopy() const;
    const Reader* getReader() const;
    Book* getBook() const;
    // Operator to print a BorrowedBook object to an output stream
    friend std::ostream& operator<<(std::ostream& os, const BorrowedBook& borrowedBook);
};