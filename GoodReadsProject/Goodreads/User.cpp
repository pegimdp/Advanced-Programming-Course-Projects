#include "User.hpp"
User::User(std::string i, std::string n, std::string pob, std::string m, std::string d, std::string y, std::vector<Author*> fav_aus, std::vector<std::string> fav_genres
    , std::vector<Book*> wtr, std::vector<Book*> cr, std::vector<Book*> r)
    :member_since(m, d, y)
{
  id = i;
  name = n;
  place_of_birth = pob;
  favorite_authors = fav_aus;
  favorite_genres = fav_genres;
  want_to_read = wtr;
  currently_reading = cr;
  read = r;
}

std::vector<Book*> User::find_shelf_type(std::string shelf_type)
{
  std::vector<Book*> this_shelf;
  if(shelf_type.compare("want_to_read") == 0)
    this_shelf = want_to_read;
  else if(shelf_type.compare("currently_reading") == 0)
    this_shelf = currently_reading;
  else if(shelf_type.compare("read") == 0)
    this_shelf = read;
  return this_shelf;
}

Book* User::find_book_by_title(std::string book_title, std::string shelf_type)
{
  std::vector<Book*> current_shelf = find_shelf_type(shelf_type);
  for(int i = 0; i < current_shelf.size(); i++)
  {
    if(current_shelf[i]->get_title().compare(book_title) == 0)
      return current_shelf[i];
  }
}

std::vector<std::string> User::find_titles(std::string shelf_type)
{
  std::vector<Book*> this_shelf = find_shelf_type(shelf_type);
  std::vector<std::string> shelf_titles{};
  for(int book = 0; book < this_shelf.size(); book++)
    shelf_titles.push_back(this_shelf[book]->get_title());
  return shelf_titles;
}

void User::show_lexically_sorted_shelf(std::string shelf_type, std::string genre)
{
  std::vector<std::string> given_shelf_titles = find_titles(shelf_type);
  std::sort(given_shelf_titles.begin(), given_shelf_titles.end(), compare_by_name);
  Book* this_book;
  for(int i = 0; i < given_shelf_titles.size(); i++)
  {
    this_book = find_book_by_title(given_shelf_titles[i], shelf_type);
    if(genre.compare(this_book->get_genre()) == 0)
      this_book->print_book();
  }
  for(int i = 0; i < given_shelf_titles.size(); i++)
  {
    this_book = find_book_by_title(given_shelf_titles[i], shelf_type);
    if(genre.compare(this_book->get_genre()) != 0)
      this_book->print_book();
  }
}
std::vector<std::string> User::find_fave_authors_names(std::vector<Author*> fave_authors)
{
  std::vector<std::string> authors_names{};
  for(int author = 0; author < fave_authors.size(); author++)
    authors_names.push_back(fave_authors[author]->get_name());
  return authors_names;
}

std::vector<std::string> User::find_fave_authors_ids(std::vector<Author*> fave_authors)
{
  std::vector<std::string> authors_ids{};
  for(int author = 0; author < fave_authors.size(); author++)
    authors_ids.push_back(fave_authors[author]->get_id());
  return authors_ids;
}

std::vector<Author*> User::sort_favorite_authors()
{
  std::vector<Author*> new_fave_authors{};
  std::vector<std::string> authors_ids = find_fave_authors_ids(favorite_authors);
  std::sort(authors_ids.begin(), authors_ids.end(), compare_by_id);
  for(int i = 0; i < authors_ids.size(); i++)
  {
    for(int j = 0; j < favorite_authors.size(); j++)
    {
      if(authors_ids[i].compare(favorite_authors[j]->get_id()) == 0)
      {
        new_fave_authors.push_back(favorite_authors[j]);
        break;
      }
    }
  }
  return new_fave_authors;
}


void User::print_user()
{
  std::cout << "id: " << id << "\n"
            << "Name: " << name << "\n"
            <<"Place of Birth: " << place_of_birth << "\n"
            << "Member Since: " << member_since.get_month() << " " << member_since.get_day() << " " << member_since.get_year() << "\n"
            << "Favorite Genres:";
  std::sort(favorite_genres.begin(), favorite_genres.end(), compare_by_name);
  for(int i = 0 ;i < favorite_genres.size(); i++)
    std::cout << " " << favorite_genres[i] ;
  std::vector<Author*> sorted_fave_authors = sort_favorite_authors();
  std::cout << "\n" << "Favorite Authors: " << sorted_fave_authors[0]->get_name();
  for(int i = 1;i < sorted_fave_authors.size(); i++)
    std::cout << ", " << sorted_fave_authors[i]->get_name();
  std::cout << "\n" << "Number of Books in Read Shelf: " << read.size()
            << "\n" << "Number of Books in Want to Read Shelf: " << want_to_read.size()
            << "\n" << "Number of Books in Currently Reading Shelf: " << currently_reading.size()
            << "\n" ;
}

bool User::is_in_favorite_genres(std::string given_genre)
{
  for(int genre = 0; genre < favorite_genres.size(); genre++)
  {
    if(favorite_genres[genre].compare(given_genre) == 0)
      return true;
  }
}
