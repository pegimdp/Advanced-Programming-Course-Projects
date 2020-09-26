#include "Rating.hpp"

Rating::Rating(std::string hotel_id_, float location, float cleanliness, float staff, float facilities
              , float value_for_money, float overall_rating, std::string username_)
{
  hotel_id = hotel_id_;
  ratings = {};
  ratings.push_back(location);
  ratings.push_back(cleanliness);
  ratings.push_back(staff);
  ratings.push_back(facilities);
  ratings.push_back(value_for_money);
  ratings.push_back(overall_rating);
  users_username = username_;
}

void Rating::print_rating(void)
{
  std::cout << LOCATION << std::fixed << std::setprecision(TWO) << COLON << SPACE << ratings[LOCATION_INDEX] << std::endl
            << CLEANLINESS << std::fixed << std::setprecision(TWO) << COLON << SPACE << ratings[CLEANLINESS_INDEX] << std::endl
            << STAFF << COLON << SPACE << std::fixed << std::setprecision(TWO) << ratings[STAFF_INDEX] << std::endl
            << FACILITIES << COLON << SPACE << std::fixed << std::setprecision(TWO) << ratings[FACILITIES_INDEX] << std::endl
            << VALUE_FOR_MONEY << COLON << SPACE << std::fixed << std::setprecision(TWO) << ratings[VALUE_FOR_MONEY_INDEX] <<std::endl
            << OVERALL_RATING << COLON << SPACE << std::fixed << std::setprecision(TWO) << ratings[OVERALL_RATING_INDEX] << std::endl;
}
