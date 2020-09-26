#ifndef __HOTEL_H__
#define __HOTEL_H__

#define AMENITIES "amenities"
#define CITY "city"
#define CLEANLINESS "cleanliness"
#define COLON ':'
#define COMMA ','
#define DELUXE "deluxe"
#define EMPTY_ROOM_CODE 0
#define FACILITIES "facilities"
#define RESERVED_ROOM_CODE 1
#define LATITUDE "latitude"
#define LOCATION "location"
#define LONGITUDE "longitude"
#define LUXURY "luxury"
#define NUM_OF_ROOMS "#rooms"
#define NUM_OF_DAYS_IN_MONTH 30
#define OVERALL_RATING "overall rating"
#define OVERVIEW "overview"
#define PREMIUM "premium"
#define PRICE "price"
#define SPACE ' '
#define STAFF "staff"
#define STANDARD "standard"
#define STAR "star"
#define VALUE_FOR_MONEY "value for money"
#define VERTICAL_LINE '|'

#include "Exceptions.hpp"
#include "User.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>


typedef std::vector<int> room_timetable_t;
typedef std::vector<std::string> info_parts_t;
typedef std::vector<std::string> amenities_t;
typedef std::vector<std::vector<std::string>> comments_t;

typedef struct HotelRoomsInfo
{
  int number_of_rooms;
  float price;
}hotel_rooms_info_t;

typedef struct RoomInfo
{
  std::string name;
  room_timetable_t timetable;
}room_info_t;

typedef struct scores
{
  std::string users_username;
  float location;
  float cleanliness;
  float staff;
  float facilities;
  float value_for_money;
  float overall_rating;
}scores_t;


class Hotel
{
public:
  Hotel(std::string unique_i, std::string name, int hotel_rating, std::string overview
        , amenities_t amenities, std::string city_, float latitude_, float longitude_
        , std::string image_url_, int num_of_standard_rooms, int num_of_deluxe_rooms
        , int num_of_luxury_rooms, int num_of_premium_rooms, float standard_room_price
        , float deluxe_room_price, float luxury_room_price, float premium_room_price);
  std::string city;
  std::string unique_id;
  int hotel_star_rating;
  float average_room_price;
  std::vector<scores_t> all_scores;
  std::vector<float> all_rooms_price;
  void add_comment(std::string the_user, std::string comment);
  void print_comments(void);
  void print_average_ratings(void);
  void print_hotel_general_info(void);
  void print_hotel_specific_info(void);
  std::vector<int> find_rooms_indices(std::vector<room_info_t> available_rooms);
  int find_number_of_free_rooms(std::string room_type, int checkin_day, int checkout_day);
  void free_rooms(std::string given_type, std::vector<int> room_indices, int checkin, int checkout);
  std::vector<int>  reserve_rooms(std::string given_type, std::vector<int> given_rooms_indices, int checkin, int checkout);
  float find_reservation_cost(std::string room_type, int quantity, int checkin, int checkout);
  std::vector<int> find_available_rooms_indices(std::string room_type, int quantity, int checkin, int checkout);
private:
  std::string property_name;
  std::string hotel_overview;
  amenities_t property_amenities;
  float latitude;
  float longitude;
  std::string image_url;
  comments_t all_comments;
  scores_t average_rating;
  hotel_rooms_info_t standard_info;
  hotel_rooms_info_t deluxe_info;
  hotel_rooms_info_t luxury_info;
  hotel_rooms_info_t premium_info;
  std::vector<room_info_t> standard_rooms;
  std::vector<room_info_t> deluxe_rooms;
  std::vector<room_info_t> luxury_rooms;
  std::vector<room_info_t> premium_rooms;
  int total_number_of_rooms;
  std::vector<int> number_of_rooms;
  std::vector<hotel_rooms_info_t> all_rooms_info;
  room_timetable_t initialize_time_table(void);
  void calc_average_rating(void);
  void calc_total_num_of_rooms(void);
  void calc_average_room_price(void);
  template<typename T>
  void print_feature(std::string feature_name, T features, char delimiter);
  bool is_room_available(std::string room_type, int room_index, int checkin, int checkout);
  hotel_rooms_info_t find_room_type(std::string type);
  std::vector<room_info_t>& identify_rooms(std::string room_type);
  bool is_valid_room_type(std::string given_type);
  bool is_valid_reservation_date(int checkin, int checkout);
  void initialize_specific_rooms(std::vector<room_info_t>& specific_rooms, hotel_rooms_info_t room_info, char specific_char);
};
#endif
