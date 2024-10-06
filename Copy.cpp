#include "Copy.h"

int Copy::nextCopy_id = 0;

Copy::Copy(const Book& book):book(book), availability(true)
{
	try
	{
		copy_id = generate_copyId();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::string Copy::generate_copyId()
{
	if (copy_id == "ZZZ999")
	{
		throw std::runtime_error("Maximum number of copies has been reached."); // maybe create custom exception and handle it
	}
	int num = nextCopy_id++; // Retrieves the next copy ID and increments the counter
	char letterPart[3] = { (num / (1000 * 26 * 26)) % 26 + 'A', (num / (1000 * 26)) % 26 + 'A', (num / 1000) % 26 + 'A' }; // Computes the letter part of the copy ID based on the counter
	copy_id = letterPart[0];
	copy_id += letterPart[1];
	copy_id += letterPart[2];

	std::ostringstream ss;
	ss << std::setfill('0') << std::setw(3) << (num % 1000);
	std::string numericalPart = ss.str();
	copy_id += numericalPart;
	return copy_id;
}

const std::string Copy::get_copyId() const
{
	return copy_id;
} 

bool Copy::setAvail(bool availability)
{
	return this->availability = availability;
}

bool Copy::is_avail() const
{
	return availability;
}