#include "Utility.h"

void Utility::get_isbn(std::string& isbn, const std::vector<Book*>& books)
{
    bool duplicate = false;
    do
    {
        try
        {
            std::cout << "Enter the ISBN number (13 digits): ";
            std::getline(std::cin, isbn);

            if (isbn.empty() || isbn.size() != 13 || !std::all_of(isbn.begin(), isbn.end(), ::isdigit))
            {
                throw std::invalid_argument("Invalid ISBN format.");
            }

            duplicate = false;
            for (auto book : books)
            {
                if (book->get_ISBN() == isbn)
                {
                    duplicate = true;
                    std::cout << "ISBN already exists in the library!" << std::endl;
                    break;
                }
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what();
            std::cout << " Please retry entering the ISBN." << std::endl;
            duplicate = true;
        }
    } while (duplicate);
}

bool Utility::username_validation(const std::string& username, const std::vector<Reader*>& readers)
{
    if (std::find_if(username.begin(), username.end(), [](char c) { return std::isspace(c); }) != username.end())
    {
        std::cout << "Error: Username cannot contain spaces." << std::endl;
        return false;
    }

    if (std::find_if(readers.begin(), readers.end(), [&](Reader* r) { return r->getUsername() == username; }) != readers.end())
    {
        std::cout << "Username already exists." << std::endl;
        return false;
    }
    return true;
}

bool Utility::password_validation(const std::string& password)
{
    if (password.empty())
    {
        std::cout << "Empty password." << std::endl;
        return false;
    }
    bool length = false, digit = false, capital_lett = false;
    if (password.length() >= 8)
    {
        length = true;
    }
    for (int i = 0; i < password.length(); i++)
    {

        if (password[i] <= '9' && password[i] >= '0')
        {
            digit = true;
        }
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            capital_lett = true;
        }
    }
    if (!(length && digit && capital_lett))
    {
        std::cout << "The password must contains at least 8 characters, 1 digit and 1 capital letter." << std::endl;
        return false;
    }
    else return true;
}

void Utility::create_librarian_account()
{
    std::string access_code;
    std::cout << "Enter the access code for administrators: " << std::endl;
    std::cin >> access_code;
    if (access_code != "IK009")
    {
        std::cout << "Access denied." << std::endl;
        return;
    }
    else if (access_code == "IK009")
    {
        std::cout << "Access allowed." << std::endl;
        std::string username, password, email;

        std::cin.ignore();
        std::cout << "Enter a username: ";
        do {
            std::getline(std::cin, username);
        } while (username.empty());

        std::cout << "Create a password: ";
        do {
            std::getline(std::cin, password);
        } while (!password_validation(password));

        std::cout << "Enter your email address: ";
        do {
            std::getline(std::cin, email);
        } while (email.empty());

        Librarian librarian(username, password, email);
        librarian.create_account("librarian_database.txt");
    }
}