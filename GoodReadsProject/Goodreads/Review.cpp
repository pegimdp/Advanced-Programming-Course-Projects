#include "Review.hpp"
Review::Review(std::string i, Book* b,User* u, int r, std::string m, std::string d, std::string y, int nol)
:review_date(m, d, y)
{
  id = i;
  book = b;
  user = u;
  rating = r;
  number_of_likes = nol;
}
void Review::print_review()
{
  std::cout << "id: " << id << " "
            << "Rating: " << rating << " "
            << "Likes: "  << number_of_likes << " "
            << "Date: " << review_date.get_month() << " "
                        << review_date.get_day() << " "
                        << review_date.get_year() << "\n";
}
