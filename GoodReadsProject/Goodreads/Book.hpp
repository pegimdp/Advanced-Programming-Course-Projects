#ifndef BOOK_HPP
#define BOOK_HPP "BOOK_HPP"
#include "Author.hpp"
#include <string>
#include <iostream>
class Book
{
public:
  Book(std::string i, std::string t, Author* a, std::string gen);
  std::string get_id() { return id; }
  std::string get_title() { return title; }
  Author* get_author() { return author; }
  std::string get_genre() { return genre; }
  void print_book(bool print_asterisks = true);
private:
  std::string id;
  std::string title;
  Author* author;
  std::string genre;

};
#endif
