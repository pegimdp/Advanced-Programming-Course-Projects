#ifndef GOODREADS_HPP
#define GOODREADS_HPP
#include "User.hpp"
#include "Author.hpp"
#include "Book.hpp"
#include "Date.hpp"
#include "Review.hpp"
#include "compare.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#define COMMA ','
#define DOLLAR_SIGN '$'
#define SPACE ' '
#define CREDIT_QUOTIENT 0.5
#define FAVE_BOOK_SCORE 5
#define USERS_FILE_PATH "users.csv"
#define AUTHORS_FILE_PATH "authors.csv"
#define BOOKS_FILE_PATH "books.csv"
#define REVIEWS_FILE_PATH "reviews.csv"
#define FOLLOW_EDGES_FILE_PATH "follow_edges.csv"

class Goodreads
{
public:
  Goodreads();
  void identify_input(std::string command);
  void show_author_info(std::string author_id);
  void show_sorted_shelf(std::string user_id, std::string shelf_type, std::string genre);
  void show_users_credit(std::string users_id);
  void show_the_best_book();
  void show_the_best_reviewer();
  void recommend_first_approach(std::string users_id);
  void read_users(std::string infile_path);
  void read_authors(std::string infile_path);
  void read_books(std::string infile_path);
  void read_reviews(std::string infile_path);
private:
  std::vector<User> users;
  std::vector<Author> authors;
  std::vector<Book> books;
  std::vector<Review> reviews;
  Author* find_author_by_id(std::string id);
  Book* find_the_best_book();
  Book* find_book_by_id(std::string id);
  User* find_user_by_id(std::string id);
  User* find_best_reviewer();
  Date read_date(std::string date_string);
  User add_user(std::string user_line);
  Author add_author(std::string author_line);
  Book add_book(std::string book_line);
  Review add_review(std::string review_line);
  std::vector<Author*> authors_vec(std::vector<std::string> authors_ids);
  std::vector<Book*> books_vec(std::vector<std::string> books_ids);
  std::vector<Book*> find_books_by_author(std::string author_id);
  std::vector<Review> find_users_reviews(std::string users_id);
  std::vector<Review> find_book_reviews(std::string book_id);
  std::vector<std::string> separate_parts(std::string connected_parts,char delimiter);
  int number_of_likes_in_reviews(std::vector<Review> given_reviews);
  float calculate_users_credit(std::string users_id);
  float book_average_rating(std::string books_id);
  float calculate_book_rating(Book* given_book);
  float calculate_book_score(User* given_user, Book* given_book);

};
#endif
