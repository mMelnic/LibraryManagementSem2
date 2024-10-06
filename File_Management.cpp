#include "File_Management.h"

void create_file_if_not_exists(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        // If the file doesn't exist create a new one
        std::ofstream newFile(filename);
        if (!newFile.is_open())
        {
            throw std::runtime_error("Unable to create file: " + filename);
        }
        // Close the new file
        newFile.close();
        // Reopen the file for reading
        file.open(filename, std::ios::in);
    }
    file.close();
}

void add_books_to_file(const std::vector<Book*>& books, const std::string& filename)
{
    try
    {
        std::ofstream file(filename, std::ios::out); // open file in output mode
        if (!file.is_open())
            throw std::runtime_error("Could not open file " + filename);
        for (auto book : books)
        {
            std::string book_info = object_to_string(*book);
            if (book_info.empty())
                throw std::runtime_error("Could not convert book to string");
            file << book_info << std::endl;
            if (!file)
                throw std::runtime_error("Could not write to the file " + filename);
        }
        file.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

std::vector<Book*> load_books_from_file(const std::string& filename)
{
    std::vector<Book*> books;
    try
    {
        create_file_if_not_exists(filename);
        std::ifstream input_file(filename);
        if (!input_file.is_open())
            throw std::runtime_error("Could not open file " + filename);
        std::string fileline;
        while (std::getline(input_file, fileline))
        {
            Book* book = nullptr;
            try
            {
                // Extracting book information from a file line
                std::stringstream ss(fileline);
                std::string title, author, genre, isbn, nrCopies_str, nrPages_str, rating_str;
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, genre, ',');
                getline(ss, isbn, ',');
                getline(ss, rating_str, ',');
                getline(ss, nrPages_str, ',');
                getline(ss, nrCopies_str);

                int nrCopies = std::stoi(nrCopies_str);
                int nrPages = std::stoi(nrPages_str);
                double rating = std::stod(rating_str);

                // Creating a new Book object and adding it to the vector
                book = new Book(title, author, genre, isbn, nrCopies, nrPages, rating);
                books.push_back(book);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error processing line. " << e.what() << std::endl;
                delete book;
                continue;
            }
        }
        input_file.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading the books from file. " << e.what() << std::endl;
    }
    return books;
}

void add_borrowedBooks_to_file(const std::vector<Reader*>& readers, const std::string& filename)
{
    std::ofstream file(filename, std::ios::out);
    try
    {
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open file for writing: " + filename);
        }
        
        for (const auto& reader : readers)
        {
            for (const auto& borrowedBook : reader->get_borrowed_books())
            {
                try
                {
                    // Converting the borrowed book object to a string representation
                    std::string bookString = object_to_string(*borrowedBook);
                    // Writing the username of the reader and the book information to the file
                    file << reader->getUsername() << "," << bookString << std::endl;
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
        file.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error writing borrowed books to file: " << e.what() << std::endl;
    }
}

std::vector<BorrowedBook*> load_borrowedBooks_from_file(Reader& reader, const std::vector<Book*>& library_collection, const std::string& filename)
{
    std::vector<BorrowedBook*> borrowed_books;
    int lineCount = 1;
    std::string line;
    try
    {
        create_file_if_not_exists(filename);
        std::ifstream file(filename);

        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open file: " + filename);
        }
        while (getline(file, line))
        {
            std::istringstream ss(line);
            std::string username, bookString;
            getline(ss, username, ',');
            getline(ss, bookString);
            if (reader.getUsername() == username)
            {
                try
                {
                    // Extracting the book information from the bookString
                    std::istringstream book_ss(bookString);
                    std::string title, author, isbn, copyId;
                    getline(book_ss, title, ',');
                    getline(book_ss, author, ',');
                    getline(book_ss, isbn, ',');
                    getline(book_ss, copyId);

                    // Finding the corresponding book and copy in the library_collection vector using the extracted information
                    Book* book = nullptr;
                    Copy* copy = nullptr;
                    for (const auto& library_book : library_collection)
                    {
                        if (library_book->getTitle() == title && library_book->getAuthor() == author && library_book->get_ISBN() == isbn)
                        {
                            book = library_book;
                            break;
                        }
                    }
                    if (book != nullptr)
                    {
                        for (const auto& library_copy : book->getCopies())
                        {
                            if (library_copy->get_copyId() == copyId)
                            {
                                copy = library_copy;
                                copy->setAvail(false);
                                break;
                            }
                        }
                    }

                    if (book == nullptr || copy == nullptr)
                    {
                        throw std::runtime_error("Error at line " + std::to_string(lineCount) + ": Unable to find book or copy.");
                    }
                    else if (book != nullptr && copy != nullptr) // If the book and copy exist create a new BorrowedBook object and add it to the vector

                    {
                        BorrowedBook* borrowedBook = new BorrowedBook(copy, &reader, book);
                        borrowed_books.push_back(borrowedBook);
                    }
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                    // Continue to the next line if an error occurs
                    continue;
                }
            }
            lineCount++;
        }
        file.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
    return borrowed_books;
}

std::vector<Reader*> load_readers_from_file(const std::string& filename)
{
    std::vector<Reader*> readers;
    try
    {
        create_file_if_not_exists(filename);
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open file for reading.");
        }
        std::string line;
        int lineNum = 1;
        // Read each line from the file
        while (std::getline(file, line))
        {
            try
            {
                std::istringstream ss(line);
                std::string username, password, email;

                // Extracting the username, password, and email from the line
                if (std::getline(ss, username, ',') &&
                    std::getline(ss, password, ',') &&
                    std::getline(ss, email))
                {
                    // Creating a new Reader object with the extracted information
                    Reader* reader = new Reader(username, password, email);
                    readers.push_back(reader);
                }
                else
                {
                    // Throw an error if the line has an invalid format
                    throw std::runtime_error("Invalid format in line " + std::to_string(lineNum));
                }
            }
            catch (std::exception& e)
            {
                std::cerr << "Error reading line from file: " << e.what() << std::endl;
                continue;
            }
            lineNum++;
        }
        file.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading the readers from file. " << e.what() << std::endl;
    }
    return readers;
}