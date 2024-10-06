#pragma once
#include<algorithm>
#include"Book.h"
#include"Reader.h"
#include"Librarian.h"

class Utility {
public:
    // Function to prompt the user to enter a non-empty string
    static void get_details(std::string& str, const std::string& prompt);
    // Function to prompt the user to enter positive numbers
    static inline void get_numbers(int& number, const std::string& prompt);
    // Function to prompt the user to enter a valid ISBN number: non-empty, 13-digits long, without duplicates
	static void get_isbn(std::string& isbn, const std::vector<Book*>& books);
    // Function to check for duplicate usernames
	static bool username_validation(const std::string& username, const std::vector<Reader*>& readers);
    // Function to impose requirements on the password creation
	static bool password_validation(const std::string& password);
    // Function to create a librarian account only if the access code is known
	static void create_librarian_account();
};

inline void Utility::get_details(std::string& str, const std::string& prompt)
{
    do {
        std::cout << prompt;
        std::getline(std::cin, str);
    } while (str.empty());
}

inline void Utility::get_numbers(int& number, const std::string& prompt)
{
    do {
        std::cout << prompt;
        std::cin >> number;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Invalid input! Please enter a number." << std::endl;
            number = 0;
        }
    } while (number <= 0);
}