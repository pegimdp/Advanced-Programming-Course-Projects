#ifndef REVIEW_HPP
#define REVIEW_HPP
#include "Book.hpp"
#include "User.hpp"
#include "Date.hpp"
#include <string>
class Review
{
public:
  Review(std::string i, Book* b,User* user, int r, std::string m, std::string d, std::string y, int nol);
  Book* get_book() { return book; }
  User* get_user() { return user; }
  int get_rating() { return rating; }
  int get_number_of_likes() { return number_of_likes; }
  void print_review();

private:
  std::string id;
  Book* book;
  User* user;
  int rating;
  Date review_date;
  int number_of_likes;
};
#endif
