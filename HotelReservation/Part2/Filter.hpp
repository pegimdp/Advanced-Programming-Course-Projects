#ifndef __FILTER_H__
#define __FILTER_H__

#include "Hotel.hpp"
#include "Exceptions.hpp"
#include "Macros.hpp"
#include <string>

typedef std::vector<std::string> info_parts_t;
typedef std::vector<Hotel*> hotels_t;

class Filter
{
public:
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

class CityFilter : public Filter
{
public:
  CityFilter(hotels_t given_hotels);
  void add_filter(info_parts_t given_filter);
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

class RatingRange : public Filter
{
public:
  RatingRange(hotels_t given_hotels);
  void add_filter(info_parts_t given_filter);
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

class AveragePriceRange : public Filter
{
public:
  AveragePriceRange(hotels_t given_hotels);
  void add_filter(info_parts_t given_filter);
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

class FreeRooms : public Filter
{
public:
  FreeRooms(hotels_t given_hotels);
  void add_filter(info_parts_t given_filter);
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

class DefaultFilter : public Filter
{
public:
  DefaultFilter(hotels_t given_hotels);
  void add_filter(float sample_mean, float sample_standard_deviation);
  hotels_t get_hotels(void);
private:
  hotels_t hotels;
};

#endif
