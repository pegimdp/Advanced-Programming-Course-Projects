#include "Date.hpp"
#include "User.hpp"
#include "Author.hpp"
#include "Book.hpp"
#include "Goodreads.hpp"
#include <iostream>
#include <string>
#include<string.h>
class User;
class Author;
class Book;
class Review;
class Goodreads;
using namespace std;

vector<Review> read_reviews(string infile_path);
Goodreads read_goodreads(string infile_path);

using namespace std;


int main(int argc,char* argv[])
{
  string folder_name = argv[1];
  Goodreads goodreads;
  goodreads.read_authors(folder_name + "/" + AUTHORS_FILE_PATH);
  goodreads.read_books(folder_name + "/" + BOOKS_FILE_PATH);
  goodreads.read_users(folder_name + "/" + USERS_FILE_PATH);
  goodreads.read_reviews(folder_name + "/" + REVIEWS_FILE_PATH);
  string input;
  while(getline(cin, input))
  {
    goodreads.identify_input(input);
  }

}
