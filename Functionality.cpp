#include "Functionality.h"

int print_mainMenu()
{
	std::cout << "Welcome to the Library Management System" << std::endl << std::endl;
	std::cout << "1. I am a librarian." << std::endl; // after that create account and login and then functionality
	std::cout << "2. I am a reader." << std::endl; // create account and login then functionality
	std::cout << "3. Exit." << std::endl << std::endl;
	int choice;
	std::cout << "Enter your choice: " << std::endl;
	std::cout << "> ";
	std::cin >> choice;
	std::cout << std::endl;
	return choice;
}
int librarianMenu()
{
	std::cout << "1. Add a book to the library." << std::endl;
	std::cout << "2. Delete a book from the library." << std::endl;
	std::cout << "3. Update the details of a book." << std::endl;
	std::cout << "4. Display all the books in the library." << std::endl;
	std::cout << "5. Return to the main menu." << std::endl;
	int choice;
	std::cout << "> ";
	std::cin >> choice;
	std::cout << std::endl;
	return choice;
}
int readerMenu()
{
	std::cout << "1. Borrow a book." << std::endl;
	std::cout << "2. Return a book." << std::endl;
	std::cout << "3. Search a book by title." << std::endl;
	std::cout << "4. Search book by author" << std::endl;
	std::cout << "5. View the library collection of books." << std::endl; // or view bestsellers
	std::cout << "6. View my borrowed books." << std::endl;
	std::cout << "7. Return to Reader menu" << std::endl;
	int choice;
	std::cout << "> ";
	std::cin >> choice;
	std::cout << std::endl;
	return choice;
}
int smallMenu()
{
	std::cout << "1. Create an account" << std::endl;
	std::cout << "2. Log in" << std::endl;
	std::cout << "3. Return to main menu" << std::endl;
	int choice;
	std::cout << "> ";
	std::cin >> choice;
	std::cout << std::endl;
	return choice;
}

void mainMenu_functionality()
{
	try {
		// Load the book collection from a file
		std::vector<Book*> library_collection = load_books_from_file("books.txt");
		// Continue displaying the main menu until the user chooses to exit
		while (true)
		{
			int menu_choice;
			menu_choice = print_mainMenu();

			switch (menu_choice) {
			case 1: { //librarians
				librarian_account(library_collection);
			} break;
			case 2: { //readers
				reader_account(library_collection);
			} break;
			case 3: { //exit
				std::cout << "Exiting main menu." << std::endl;
				// Deallocate memory for each book in the library collection
				for (const auto& book : library_collection)
				{
					delete book;
				}
				return;
			} break;
			default:
				break;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred while loading books: " << e.what() << std::endl;
	}
}

void librarian_functionality(Librarian& librarian, std::vector<Book*>& libraryBooks)
{
	bool exit_loop = true;
	while (exit_loop)
	{
		int librarian_choice = librarianMenu();
		switch (librarian_choice)
		{
		case 1: {
			std::cin.ignore();
			librarian.add_book_to_library(libraryBooks);
			add_books_to_file(libraryBooks, "books.txt");
		} break;
		case 2: {
			// Check if the library is empty before deleting a book
			if (libraryBooks.empty())
			{
				std::cout << "The library is empty." << std::endl << std::endl;
				break;
			}
			librarian.delete_book_from_library(libraryBooks);
			add_books_to_file(libraryBooks, "books.txt");
		} break;
		case 3: {
			// Check if the library is empty before updating book details
			if (libraryBooks.empty())
			{
				std::cout << "The library is empty." << std::endl << std::endl;
				break;
			}
			librarian.update_book_details(libraryBooks);
			add_books_to_file(libraryBooks, "books.txt");
		} break;
		case 4: {
			std::cout << "The library contains " << libraryBooks.size() << " books." << std::endl << std::endl;
			librarian.display_all_books(libraryBooks);
		} break;
		case 5: {
			exit_loop = false;
			std::cout << std::endl;
		} break;
		default: std::cout << "Enter a valid number." << std::endl;
			break;
		}
	}
}

void reader_functionality(Reader& reader, const std::vector<Book*>& libraryBooks, const std::vector<Reader*>& readers)
{
	while (true)
	{
		int reader_choice = readerMenu();
		switch (reader_choice)
		{
		case 1: {
			std::cout << "The library contains " << libraryBooks.size() << " books." << std::endl << std::endl;
			reader.display_all_books(libraryBooks);
			char answer;
			std::cout << "Do you want to borrow any of the above books? (y/n) ";
			do {
				std::cin >> answer;
				answer = tolower(answer);
			} while (answer != 'y' && answer != 'n');
			if (answer == 'y')
			{
				std::cout << "Write the ISBN of the book you want to borrow: ";
				std::string user_ISBN;
				std::cin >> user_ISBN;
				bool isbn_found = false;
				for (const auto& book : libraryBooks)
				{
					// Checking if the ISBN entered by the user matches the ISBN of the current book in the loop
					if (!(user_ISBN.compare(book->get_ISBN())))
					{
						isbn_found = true;
						if (reader.borrow_book(book))
						{
							std::cout << "Book borrowed successfully." << std::endl;
							add_borrowedBooks_to_file(readers, "borrowed_books.txt");
						}
						else
						{
							std::cout << "No more available copies." << std::endl;
							break;
						}
					}
				}
				if (!isbn_found)
				{
					std::cout << "Book not found" << std::endl << std::endl;
				}
			}
			else if (answer == 'n') break;
		} break;
		case 2: {//
			std::cout << "Enter the ISBN of the book you want to return: ";
			std::string user_ISBN;
			std::cin >> user_ISBN;
			bool isbn_found = false;
			for (const auto& iterator : reader.get_borrowed_books())
			{
				if (user_ISBN == iterator->getBook()->get_ISBN())
				{
					isbn_found = true;
					if (reader.return_book(iterator))
					{
						std::cout << "Book returned successfully." << std::endl;
						add_books_to_file(libraryBooks, "books.txt");
						add_borrowedBooks_to_file(readers, "borrowed_books.txt");
					}
				}
			}
			if (!(isbn_found))
			{
				std::cout << "You did not borrow this book." << std::endl;
			}
		} break;
		case 3: {
			std::string title;
			std::cin.ignore();
			Utility::get_details(title, "Enter the title of the book you are looking for: ");
			std::vector<Book*> found_books_by_title = reader.search_by_title(title, libraryBooks);
			if (found_books_by_title.empty())
			{
				std::cout << " No matches found" << std::endl;
				break;
			}
			else
			{
				reader.display_all_books(found_books_by_title);
				std::string answer;
				std::cout << "Enter the ISBN of the book you want to borrow or any character if you don't want to borrow any book: ";
				std::cin >> answer;
				for (const auto& book : found_books_by_title)
				{
					if (answer == book->get_ISBN())
					{
						if (reader.borrow_book(book))
						{
							std::cout << "Book borrowed successfully." << std::endl << std::endl;
							add_borrowedBooks_to_file(readers, "borrowed_books.txt"); //has error handling inside 
						}
					}
				}
			}
		} break; //done
		case 4: {
			std::string author;
			std::cout << "Enter the author of the books you are interested in: ";
			std::cin.ignore();
			std::getline(std::cin, author);
			std::vector<Book*> found_books_by_author = reader.search_by_author(author, libraryBooks); 
			if (found_books_by_author.empty())
			{
				std::cout << " No matches found" << std::endl;
				break;
			}
			else {
				reader.display_all_books(found_books_by_author);
				std::string answer;
				std::cout << "Enter the ISBN of the book you want to borrow, if any: ";
				std::cin >> answer;
				for (const auto& book : found_books_by_author)
				{
					if (answer == book->get_ISBN())
					{
						if (reader.borrow_book(book)) {
							std::cout << "Book borrowed successfully." << std::endl << std::endl;
							add_borrowedBooks_to_file(readers, "borrowed_books.txt");
						}
					}
				}
			}
		} break;
		case 5: {
			std::cout << "The library contains " << libraryBooks.size() << " books." << std::endl << std::endl;
			reader.display_all_books(libraryBooks);
		} break;
		case 6: {
			reader.display_borrowed_books();
		} break;
		case 7: {
			return;
		} break;
		default:
			std::cout << "Invalid choice" << std::endl;
			break;
		}
	}
}

void librarian_account(std::vector<Book*>& library_collection)
{
	while (true)
	{
		std::cout << "--------LIBRARIAN MENU--------" << std::endl << std::endl;
		int choice1 = smallMenu();
		switch (choice1) { //create account
		case 1: {
			Utility::create_librarian_account();
		} break;
		case 2: { //log in
			std::cin.ignore();
			std::string username, password, email;
			std::cout << "Enter your username: ";
			do {
				std::getline(std::cin, username);
			} while (username.empty());
			std::cout << "Enter your password: ";
			do {
				std::getline(std::cin, password);
			} while (password.empty());
			std::cout << "Enter your email address: ";
			do {
				std::getline(std::cin, email);
			} while (email.empty());

			// Create a Librarian object with the provided credentials
			Librarian librarian(username, password, email);

			// Authenticate the librarian using the librarian database
			if (librarian.authenticate_user("librarian_database.txt"))
			{
				std::cout << std::endl;
				// Proceed with librarian functionality
				librarian_functionality(librarian, library_collection);
			}
			else
				std::cout << "User not found." << std::endl << std::endl;
		} break;
		case 3: { //return to main menu
			std::cout << "Returning to main menu." << std::endl;
			return;
		} break;
		default:
			std::cout << "Invalid choice" << std::endl;
			break;
		}
	}
}

void reader_account(const std::vector<Book*>& library_collection)
{
	std::vector<Reader*> readers;
	std::vector<BorrowedBook*> reader_borrowed_books;
	readers = load_readers_from_file("reader_database.txt");
	try
	{
		// Load the borrowed books for each reader from a file
		for (auto& reader : readers)
		{
			reader_borrowed_books.clear();
			try
			{
				reader_borrowed_books = load_borrowedBooks_from_file(*reader, library_collection, "borrowed_books.txt");
				reader->set_borrowed_books(reader_borrowed_books);
			}
			catch (const std::exception& e)
			{
				std::cerr << "Error loading borrowed books for reader: " << reader->getUsername() << ": " << e.what() << std::endl;
				continue;
			}
		}

		for (auto borrowedBook : reader_borrowed_books)
		{
			delete borrowedBook;
		}
		reader_borrowed_books.clear();

		while (true)
		{
			std::cout << "--------READER MENU--------" << std::endl << std::endl;
			int choice2 = smallMenu();
			std::cin.ignore();
			switch (choice2)
			{
			case 1: { // create account reader
				std::string username, password, email;
				do {
					std::cout << "Enter a username: ";
					std::getline(std::cin, username);
				} while (!Utility::username_validation(username, readers));
				std::cout << "Enter your email address: ";
				do
				{
					std::getline(std::cin, email);
				} while (email.empty());
				std::cout << "Create a password: ";
				do {
					std::getline(std::cin, password);
				} while (!Utility::password_validation(password));
				Reader* reader = new Reader(username, password, email);
				(*reader).create_account("reader_database.txt");
				readers.push_back(reader);
			} break;
			case 2: { // log in reader
				std::string username, password, email;
				std::cout << "Enter your username: ";
				do {
					std::getline(std::cin, username);
				} while (username.empty());
				std::cout << "Enter your password: ";
				do {
					std::getline(std::cin, password);
				} while (password.empty());
				std::cout << "Enter your email address: ";
				do {
					std::getline(std::cin, email);
				} while (email.empty());
				Reader authenticated_reader(username, password, email);
				if (authenticated_reader.authenticate_user("reader_database.txt"))
				{
					for (const auto& reader : readers)
					{
						if (authenticated_reader.getUsername() == reader->getUsername())
							reader_functionality(*reader, library_collection, readers);
					}
				}
				else
					std::cout << "User not found." << std::endl << std::endl;
			} break;
			case 3: {
				// Deallocate memory for readers when exiting
				for (const auto& reader : readers)
				{
					delete reader;
				}
				return;
			}
			default:
				std::cout << "Invalid choice" << std::endl;
				break;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error in reader_account function: " << e.what() << std::endl;
		// Deallocate memory for readers in case of exception
		for (auto reader : readers)
		{
			delete reader;
		}
	}
}