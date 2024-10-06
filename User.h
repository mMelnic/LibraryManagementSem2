#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Book.h"

class User {
	std::string username;
	std::string password;
	std::string email_address;

public:
	User() {};
	User(std::string username, std::string password, std::string email);
	std::string getUsername() const;
	std::string getEmail() const;
	std::string getPassword() const;
	void display_all_books(const std::vector<Book*>& books) const;
	// Method to create an account by adding user credentials to a file
	void create_account(const std::string& filename) const;
	// Method to check if the user credentials exist in a database file
	bool authenticate_user(const std::string& filename) const;
};