#include "compare.hpp"

bool compare_by_name(std::string firsts, std::string seconds)
{
  return firsts < seconds ;
}

bool compare_by_id(std::string first_id, std::string second_id)
{
  return stoi(first_id) < stoi(second_id);
}
bool compare_by_len(std::string first_id, std::string second_id)
{
  return first_id.length() < second_id.length();
}
