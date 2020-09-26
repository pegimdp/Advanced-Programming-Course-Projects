#include "Filter.hpp"

hotels_t Filter::get_hotels(void)
{
  return hotels;
}

CityFilter::~CityFilter(void)
{
  for(auto hotel:hotels)
    delete hotel;
}

CityFilter::CityFilter(hotels_t given_hotels)
{
  hotels = given_hotels;
}

void CityFilter::add_filter(info_parts_t given_filter)
{
  std::string given_city;
  for(const auto &piece : given_filter) given_city += piece;
  hotels_t new_hotels = {};
  for(auto hotel:hotels)
  {
    if(hotel->city.compare(given_city) == 0)
      new_hotels.push_back(hotel);
  }
  hotels = new_hotels;
}

hotels_t CityFilter::get_hotels(void)
{
  return hotels;
}

RatingRange::~RatingRange(void)
{
  for(auto hotel:hotels)
    delete hotel;
}

RatingRange::RatingRange(hotels_t given_hotels)
{
  hotels = given_hotels;
}

void RatingRange::add_filter(info_parts_t given_filter)
{
  float min_rating = std::stof(given_filter[0]);
  float max_rating = std::stof(given_filter[1]);
  hotels_t new_hotels = {};
  if(min_rating > max_rating || min_rating < MIN_RATING || max_rating > MAX_RATING)
    throw InvalidRequest();
  for(auto hotel:hotels)
  {
    if(min_rating <= hotel->hotel_star_rating &&  hotel->hotel_star_rating <= max_rating)
      new_hotels.push_back(hotel);
  }
  hotels = new_hotels;
}

hotels_t RatingRange::get_hotels(void)
{
  return hotels;
}

AveragePriceRange::~AveragePriceRange()
{
  for(auto hotel:hotels)
    delete hotel;
}

AveragePriceRange::AveragePriceRange(hotels_t given_hotels)
{
  hotels = given_hotels;
}

void AveragePriceRange::add_filter(info_parts_t given_filter)
{
  float min_price = std::stof(given_filter[0]);
  float max_price = std::stof(given_filter[1]);
  if(max_price < min_price || min_price < 0)
    throw InvalidRequest();
  hotels_t new_hotels = {};
  for(auto hotel:hotels)
  {
    if(min_price <= hotel->average_room_price &&  hotel->average_room_price <= max_price)
      new_hotels.push_back(hotel);
  }
  hotels = new_hotels;
}

hotels_t AveragePriceRange::get_hotels(void)
{
  return hotels;
}

FreeRooms::~FreeRooms(void)
{
  for(auto hotel:hotels)
    delete hotel;
}

FreeRooms::FreeRooms(hotels_t given_hotels)
{
  hotels = given_hotels;
}

void FreeRooms::add_filter(info_parts_t given_filter)
{
  std::string given_type = given_filter[0];
  if(given_type.compare(STANDARD) != 0 && given_type.compare(DELUXE) != 0 &&
     given_type.compare(LUXURY) != 0 && given_type.compare(PREMIUM) != 0)
     throw InvalidRequest();
  int quantity = std::stoi(given_filter[1]);
  if(quantity < 0)
    throw InvalidRequest();
  int check_in = std::stoi(given_filter[2]);
  int check_out = std::stoi(given_filter[3]);
  if(check_in > check_out || check_in < 0 || check_out > NUM_OF_DAYS_IN_MONTH)
    throw InvalidRequest();
  hotels_t new_hotels = {};
  for(auto hotel:hotels)
  {
    if(quantity <= hotel->find_number_of_free_rooms(given_type, check_in, check_out))
      new_hotels.push_back(hotel);
  }
  hotels = new_hotels;
}

hotels_t FreeRooms::get_hotels(void)
{
  return hotels;
}
