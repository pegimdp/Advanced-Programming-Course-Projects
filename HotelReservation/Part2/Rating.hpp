#ifndef __RATING_H__
#define __RATING_H__

#include "Exceptions.hpp"
#include "Macros.hpp"
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

typedef std::vector<float> rating_parts_t;

class User;
class Rating
{
public:
  Rating(std::string hotel_id_, float location, float cleanliness, float staff, float facilities
        , float value_for_money, float overall_rating, std::string username_);
  void print_rating(void);
  rating_parts_t ratings;
  std::string hotel_id;
  std::string users_username;
};


#endif
