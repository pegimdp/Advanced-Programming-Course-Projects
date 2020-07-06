#include "Book.hpp"
Book::Book(std::string i, std::string t, Author* a, std::string gen)
{
  id = i;
  title = t;
  author = a;
  genre = gen;
}

void Book::print_book(bool print_asterisks)
{
  std::cout << "id: " << id << "\n"
            <<"Title: " << title << "\n"
            << "Genre: " << genre << "\n"
            << "Author: " << author->get_name() << std::endl;
  if(print_asterisks == true)
    std::cout << "***" << std::endl;
}
