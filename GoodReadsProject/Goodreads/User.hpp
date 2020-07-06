#ifndef USER_HPP
#define USER_HPP
#include "Date.hpp"
#include "Author.hpp"
#include "Book.hpp"
#include "compare.hpp"
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>
class User
{
public:
  User(std::string i, std::string n, std::string pob, std::string m, std::string d, std::string y, std::vector<Author*> fav_aus, std::vector<std::string> fav_genres
      , std::vector<Book*> wtr, std::vector<Book*> cr, std::vector<Book*> r);
  std::string get_id() { return id; }
  void show_lexically_sorted_shelf(std::string shelf_type, std::string genre);
  void print_user();
  bool is_in_favorite_genres(std::string given_genre);

private:
  std::string id;
  std::string name;
  std::string place_of_birth;
  Date member_since;
  Book* find_book_by_title(std::string book_title, std::string shelf_type);
  std::vector<Book*> want_to_read;
  std::vector<Book*> currently_reading;
  std::vector<Book*> read;
  std::vector<Book*> find_shelf_type(std::string shelf_type);
  std::vector<User*> followings_id;
  std::vector<User*> followers_id;
  std::vector<Author*> favorite_authors;
  std::vector<Author*> sort_favorite_authors();
  std::vector<std::string> find_titles(std::string shelf_type);
  std::vector<std::string> favorite_genres;
  std::vector<std::string> find_fave_authors_names(std::vector<Author*> fave_authors);
  std::vector<std::string> find_fave_authors_ids(std::vector<Author*> fave_authors);
};
#endif
