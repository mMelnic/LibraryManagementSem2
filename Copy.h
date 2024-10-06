#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "Book.h"

class Copy {
	std::string copy_id;
	static int nextCopy_id;
	bool availability;
	const Book& book;

public:
	Copy(const Book& book);
	std::string generate_copyId(); // Method to generate a unique ID consisting of 3 letters and 3 digits
	const std::string get_copyId() const;
	bool setAvail(bool availability);
	bool is_avail() const;
};