#ifndef __FILTER__
#define __FILTER__

#include "Hotel.hpp"
#include "Exceptions.hpp"
#include <string>

#define MIN_RATING 1
#define MAX_RATING 5

typedef std::vector<std::string> info_parts_t;
typedef std::vector<Hotel*> hotels_t;

class Filter
{
public:
  virtual void add_filter(info_parts_t given_filter) = 0;
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

class CityFilter : public Filter
{
public:
  ~CityFilter();
  CityFilter(hotels_t given_hotels);
  void add_filter(info_parts_t given_filter);
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

class RatingRange : public Filter
{
public:
  ~RatingRange();
  RatingRange(hotels_t given_hotels);
  void add_filter(info_parts_t given_filter);
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

class AveragePriceRange : public Filter
{
public:
  ~AveragePriceRange();
  AveragePriceRange(hotels_t given_hotels);
  void add_filter(info_parts_t given_filter);
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

class FreeRooms : public Filter
{
public:
  ~FreeRooms();
  FreeRooms(hotels_t given_hotels);
  void add_filter(info_parts_t given_filter);
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};


#endif
