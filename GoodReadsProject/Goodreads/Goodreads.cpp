#include "Goodreads.hpp"

Goodreads::Goodreads()
{
  std::vector<User> current_users{};
  std::vector<Book> current_books{};
  std::vector<Author> current_authors{};
  std::vector<Review> current_reviews{};
  users = current_users;
  books = current_books;
  authors = current_authors;
  reviews = current_reviews;
}

void Goodreads::identify_input(std::string command)
{
  std::vector<std::string> input_commands = separate_parts(command, SPACE);
  if(input_commands[0].compare("show_author_info") == 0)
    show_author_info(input_commands[1]);
  else if(input_commands[0].compare("show_sorted_shelf") == 0)
    show_sorted_shelf(input_commands[1], input_commands[2], input_commands[3]);
  else if(input_commands[0].compare("credit") == 0)
    show_users_credit(input_commands[1]);
  else if(input_commands[0].compare("best_book") == 0)
    show_the_best_book();
  else if(input_commands[0].compare("best_reviewer") == 0)
    show_the_best_reviewer();
  else if(input_commands[0].compare("recommend_first_approach") == 0)
    recommend_first_approach(input_commands[1]);

}

std::vector<std::string> Goodreads::separate_parts(std::string connected_parts,char delimiter)
 {
   std::vector<std::string> separated;
   std::stringstream connected(connected_parts);
   std::string each_part;
   while(getline(connected, each_part, delimiter))
     separated.push_back(each_part);
   return separated;
 }

Author* Goodreads::find_author_by_id(std::string id)
{
  for(int i = 0; i < authors.size(); i++)
  {
    if(authors[i].get_id().compare(id) == 0)
      return &authors[i];
  }
}

Book* Goodreads::find_book_by_id(std::string id)
{
  for(int i = 0; i < books.size(); i++)
  {
    if(books[i].get_id() == id)
      return &books[i];
  }
}

User* Goodreads::find_user_by_id(std::string id)
{
  for(int i = 0; i < users.size(); i++)
  {
    if(users[i].get_id() == id)
      return &users[i];
  }

}

std::vector<Author*> Goodreads::authors_vec(std::vector<std::string> authors_ids)
{
  std::vector<Author*> authors;
  for(int i=0; i < authors_ids.size(); i++)
    authors.push_back(find_author_by_id(authors_ids[i]));
  return authors;
}

std::vector<Book*> Goodreads::books_vec(std::vector<std::string> books_ids)
{
  std::vector<Book*> books;
  for(int i=0; i < books_ids.size(); i++)
    books.push_back(find_book_by_id(books_ids[i]));
  return books;
}


Date Goodreads::read_date(std::string date_string)
{
  std::istringstream date(date_string);
  std::string part;
  int count  = 0 ;
  std::string m, d, y;
  while(date >> part)
  {
    if (count == 0)
      m = part;
    else if(count == 1)
      d = part;
    else if(count == 2)
      y = part;
    count++;
  }
  return Date(m, d, y);
}

User Goodreads::add_user(std::string user_line)
{
  std::vector<std::string> this_user = separate_parts(user_line, COMMA);
  std::vector<std::string> users_date = separate_parts(this_user[3], SPACE);
  return User(this_user[0], this_user[1], this_user[2], users_date[0], users_date[1], users_date[2]
        , authors_vec(separate_parts(this_user[4], DOLLAR_SIGN)), separate_parts(this_user[5], DOLLAR_SIGN)
        , books_vec(separate_parts(this_user[6], DOLLAR_SIGN)), books_vec(separate_parts(this_user[7], DOLLAR_SIGN))
        , books_vec(separate_parts(this_user[8], DOLLAR_SIGN)));
}

void Goodreads::read_users(std::string infile_path)
{
  std::ifstream inp_users(infile_path);
  std::string line;
  getline(inp_users, line);
  while(getline(inp_users, line))
    users.push_back(add_user(line));
  inp_users.close();
}

Author Goodreads::add_author(std::string author_line)
{
  std::vector<std::string> this_author = separate_parts(author_line, COMMA);
  return Author(this_author[0], this_author[1], this_author[2], read_date(this_author[3]).get_month(), read_date(this_author[3]).get_day()
              ,read_date(this_author[3]).get_year(), stoi(this_author[4]), this_author[5], separate_parts(this_author[6], DOLLAR_SIGN));

}

void Goodreads::read_authors(std::string infile_path)
{
  std::ifstream inp_authors(infile_path);
  std::vector<Author> file_authors{};
  std::string line;
  getline(inp_authors, line);
  while(getline(inp_authors, line))
    authors.push_back(add_author(line));

}

Book Goodreads::add_book(std::string book_line)
{
  std::vector<std::string> this_book = separate_parts(book_line, COMMA);
  return Book(this_book[0], this_book[1], find_author_by_id(this_book[2]), this_book[3]);

}

void Goodreads::read_books(std::string infile_path)
{
  std::ifstream inp_books(infile_path);
  std::string line;
  getline(inp_books, line);
  while(getline(inp_books, line))
    books.push_back(add_book(line));
}

std::vector<Book*> Goodreads::find_books_by_author(std::string author_id)
{
  std::vector<Book*> authors_books;
  for(int i = 0; i < books.size(); i++)
  {
    if(books[i].get_author()->get_id().compare(author_id) == 0 )
      authors_books.push_back(&books[i]);
  }
  return authors_books;
}

Review Goodreads::add_review(std::string review_line)
{
  std::vector<std::string> this_review = separate_parts(review_line, COMMA);
  std::vector<std::string> review_date = separate_parts(this_review[4], SPACE);
  return Review(this_review[0], find_book_by_id(this_review[1]), find_user_by_id(this_review[2])
                , stoi(this_review[3]), review_date[0], review_date[1], review_date[2], stoi(this_review[5]));
}

void Goodreads::read_reviews(std::string infile_path)
{
  std::ifstream inp_reviews(infile_path);
  std::string line;
  getline(inp_reviews, line);
  while(getline(inp_reviews, line))
    reviews.push_back(add_review(line));
}

std::vector<Review> Goodreads::find_users_reviews(std::string users_id)
{
  std::vector<Review> users_reviews{};
  for(int i = 0; i < reviews.size(); i++)
  {
    if(reviews[i].get_user()->get_id().compare(users_id) == 0 )
      users_reviews.push_back(reviews[i]);
  }
  return users_reviews;
}

void Goodreads::show_author_info(std::string author_id)
{
  Author* this_author;
  this_author = find_author_by_id(author_id);
  std::cout << "id: " << this_author->get_id() << "\n"
       << "Name: " << this_author->get_name() << "\n"
       << "Year of Birth: " << this_author->get_year_of_birth() << "\n"
       << "Place of Birth: " << this_author->get_place_of_birth() << "\n"
       << "Member Since: " << this_author->get_member_since().get_month() << " "
       << this_author->get_member_since().get_day() << " " << this_author->get_member_since().get_year() << "\n";
       std::cout << "Genre: ";
       this_author->print_sorted_genres();
      std::cout << "\n" << "Books:" << std::endl;
      for(int i = 0; i < find_books_by_author(author_id).size(); i++)
      {
        std::cout << "id: " << find_books_by_author(author_id)[i]->get_id()
             << " Title: " << find_books_by_author(author_id)[i]->get_title() << std::endl ;
      }
}

void Goodreads::show_sorted_shelf(std::string user_id, std::string shelf_type, std::string genre)
{
  User* this_user = find_user_by_id(user_id);
  this_user->show_lexically_sorted_shelf(shelf_type, genre);
  std::cout << "\n";
}

float Goodreads::calculate_users_credit(std::string users_id)
{
  int number_of_reviews = reviews.size();
  int number_of_user_reviews = find_users_reviews(users_id).size();
  float second_fraction = (float)number_of_user_reviews/(float)number_of_reviews;
  int total_number_of_likes = number_of_likes_in_reviews(reviews);
  int number_of_user_reviews_likes = number_of_likes_in_reviews(find_users_reviews(users_id));
  float first_fraction = (float)number_of_user_reviews_likes / (float) total_number_of_likes;
  return CREDIT_QUOTIENT * (first_fraction + second_fraction);
}

int Goodreads::number_of_likes_in_reviews(std::vector<Review> given_reviews)
{
  int likes = 0 ;
  for(int current_review = 0; current_review < given_reviews.size(); current_review++)
    likes += given_reviews[current_review].get_number_of_likes();
  return likes;
}

void Goodreads::show_users_credit(std::string users_id)
{
  float users_credit = calculate_users_credit(users_id);;
  printf("%.6f", users_credit);
  std::cout << "\n";
}

float Goodreads::book_average_rating(std::string books_id)
{
  float ratings_sum  = 0;
  float num_of_ratings = 0;
  for(int i = 0; i < reviews.size(); i++)
  {
    if(reviews[i].get_book()->get_id().compare(books_id) == 0)
    {
      ratings_sum += reviews[i].get_rating();
      num_of_ratings += 1;
    }
  }
  return ratings_sum/num_of_ratings;
}

Book* Goodreads::find_the_best_book()
{
  float best_average_rating = 0;
  Book* best_book;
  Book* this_book;
  float this_average;
  for(int review = 0; review < reviews.size(); review++)
  {
    this_book = reviews[review].get_book();
    this_average = book_average_rating(reviews[review].get_book()->get_id());
    if(this_average > best_average_rating)
    {
      best_average_rating = this_average;
      best_book = this_book;
    }
  }
  return best_book;
}

void Goodreads::show_the_best_book()
{
  Book* the_best_book = find_the_best_book();
  the_best_book->print_book(false);
  printf("%.2f",book_average_rating(the_best_book->get_id()));
  std::cout << "\n";
}

User* Goodreads::find_best_reviewer()
{
  int most_num_of_likes = 0;
  User* best_reviewer;
  int number_of_user_reviews_likes;
  for(int i = 0; i < users.size(); i++)
  {
    number_of_user_reviews_likes = number_of_likes_in_reviews(find_users_reviews(users[i].get_id()));
    if(number_of_user_reviews_likes > most_num_of_likes)
    {
      most_num_of_likes = number_of_user_reviews_likes;
      best_reviewer = &users[i];
    }
  }
  return best_reviewer;
}
void Goodreads::show_the_best_reviewer()
{
  User* best_reviewer = find_best_reviewer();
  best_reviewer->print_user();
  std::cout << "Number of Likes: " << number_of_likes_in_reviews(find_users_reviews(best_reviewer->get_id())) << std::endl;
}

std::vector<Review> Goodreads::find_book_reviews(std::string book_id)
{
  std::vector<Review> books_reviews{};
  for(int i = 0; i < reviews.size(); i++)
  {
    if(reviews[i].get_book()->get_id().compare(book_id) == 0 )
      books_reviews.push_back(reviews[i]);
  }
  return books_reviews;
}

float Goodreads::calculate_book_rating(Book* given_book)
{
  std::vector<Review> reviews_of_book = find_book_reviews(given_book->get_id());
  float numerator = 0;
  for(int review = 0 ;review < reviews_of_book.size(); review++)
  {
    numerator += (float)reviews_of_book[review].get_rating() * (float)calculate_users_credit(reviews_of_book[review].get_user()->get_id());
  }
  float denominator = (float)reviews_of_book.size();
  if(denominator == 0)
    return 0;
  return numerator/denominator;
}

float Goodreads::calculate_book_score(User* given_user, Book* given_book)
{
  float given_book_rating = calculate_book_rating(given_book);
  float book_score = given_book_rating ;
  if(given_user->is_in_favorite_genres(given_book->get_genre()))
    book_score += FAVE_BOOK_SCORE;
  return book_score;
}

void Goodreads::recommend_first_approach(std::string users_id)
{
  User* given_user = find_user_by_id(users_id);
  float current_book_score = 0;
  float highest_score = 0;
  Book* most_proper_book;
  for(int book = 0; book < books.size(); book++)
  {
    current_book_score = calculate_book_score(given_user, &books[book]);
    if(current_book_score > highest_score)
    {
      most_proper_book = &books[book];
      highest_score = current_book_score;
    }
  }
  std::vector<Review> proper_book_reviews = find_book_reviews(most_proper_book->get_id());
  most_proper_book->print_book(false);
  std::cout <<"Reviews:\n";
  for(int i = 0; i < proper_book_reviews.size(); i++)
    proper_book_reviews[i].print_review();
}
