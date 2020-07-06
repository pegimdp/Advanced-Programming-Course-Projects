#ifndef AUTHOR_HPP
#define AUTHOR_HPP "AUTHOR_HPP"
#include "Date.hpp"
#include "compare.hpp"
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
class Author
{
public:
  Author(std::string i, std::string n, std::string g, std::string m, std::string d, std::string y,int yob, std::string pob, std::vector<std::string> gens);
  std::string get_id() { return id; }
  std::string get_name() { return name; }
  int get_year_of_birth() { return year_of_birth; }
  std::string get_place_of_birth() { return place_of_birth; }
  Date get_member_since() { return member_since; }
  std::vector<std::string> get_genres() { return genres; }
  void print_sorted_genres();

private:
  std::string id;
  std::string name;
  std::string gender;
  Date member_since;
  int year_of_birth;
  std::string place_of_birth;
  std::vector<std::string> genres;
};
#endif
