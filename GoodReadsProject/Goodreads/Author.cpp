#include "Author.hpp"

Author::Author(std::string i, std::string n, std::string g, std::string m, std::string d, std::string y,int yob, std::string pob, std::vector<std::string> gens)
:member_since(m, d, y)
{
  id = i;
  name = n;
  gender = g;
  year_of_birth = yob;
  place_of_birth = pob;
  genres = gens;
}

void Author::print_sorted_genres()
{
  std::sort(genres.begin(), genres.end(), compare_by_name);
  for(int i = 0; i < genres.size(); i++)
    std::cout << genres[i];
}
