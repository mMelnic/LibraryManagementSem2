#include "User.h"

User::User(std::string username, std::string password, std::string email) : username(username), password(password), email_address(email) {}

std::string User::getUsername() const
{
	return username;
}

std::string User::getEmail() const
{
	return email_address;
}

std::string User::getPassword() const
{
	return password;
}

void User::display_all_books(const std::vector<Book*>& books) const
{
	for (const auto& book : books)
	{
		book->printBook();
		std::cout << std::endl;
	}
}

void User::create_account(const std::string& accounts_file) const
{
	try
	{
		std::ofstream userFile(accounts_file, std::ios::app);
		if (!userFile.is_open())
			throw std::runtime_error("File cannot be opened! Unable to create an account.");
		userFile << username << "," << password << "," << email_address << std::endl;
		std::cout << "Account was created successfully." << std::endl;
		userFile.close();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

bool User::authenticate_user(const std::string& accounts_file) const
{
	bool user_authenticated = false;
	std::string fileLine;
	try
	{
		std::ifstream userFile(accounts_file);
		if (!userFile.is_open()) 
		{
			throw std::runtime_error("File" + accounts_file + "could not be opened");
		}
		while (getline(userFile, fileLine))
		{
			try
			{
				std::istringstream ss(fileLine);
				std::string database_username, database_password;
				getline(ss, database_username, ',');
				getline(ss, database_password, ',');
				if (username == database_username && password == database_password) {
					userFile.close();
					std::cout << "Login successful." << std::endl;
					user_authenticated = true;
					break;
				}
			}
			catch (const std::exception& e)
			{
				std::cerr << "Error while reading line: " << e.what() << std::endl;
			}
		}
		userFile.close();
		if (!user_authenticated)
			throw std::runtime_error("Invalid username or password.");
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return user_authenticated;
}