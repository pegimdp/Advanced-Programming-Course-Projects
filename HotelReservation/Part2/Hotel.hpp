#ifndef __HOTEL_H__
#define __HOTEL_H__

#include "Exceptions.hpp"
#include "Rating.hpp"
#include "Macros.hpp"
#include "User.hpp"
#include "Weights.hpp"
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

typedef std::vector<Rating*> ratings_t;

class Weights;
class User;
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
  std::string property_name;
  int hotel_star_rating;
  float average_room_price;
  ratings_t all_ratings;
  Rating* average_rating;
  std::vector<float> all_rooms_price;
  hotel_rooms_info_t standard_info;
  hotel_rooms_info_t deluxe_info;
  hotel_rooms_info_t luxury_info;
  hotel_rooms_info_t premium_info;
  void add_comment(std::string the_user, std::string comment);
  void calc_user_personal_rating(User* given_user, Weights* given_weights);
  float current_user_personal_rating;
  void print_comments(void);
  void print_hotel_general_info(void);
  void print_hotel_specific_info(void);
  std::vector<int> find_rooms_indices(std::vector<room_info_t> available_rooms);
  int find_number_of_free_rooms(std::string room_type, int checkin_day, int checkout_day);
  void free_rooms(std::string given_type, std::vector<int> room_indices, int checkin, int checkout);
  std::vector<int>  reserve_rooms(std::string given_type, std::vector<int> given_rooms_indices, int checkin, int checkout);
  float find_room_price(std::string room_type);
  float find_reservation_cost(std::string room_type, int quantity, int checkin, int checkout);
  std::vector<int> find_available_rooms_indices(std::string room_type, int quantity, int checkin, int checkout);
private:
  std::string hotel_overview;
  amenities_t property_amenities;
  float latitude;
  float longitude;
  std::string image_url;
  comments_t all_comments;
  std::vector<room_info_t> standard_rooms;
  std::vector<room_info_t> deluxe_rooms;
  std::vector<room_info_t> luxury_rooms;
  std::vector<room_info_t> premium_rooms;
  int total_number_of_rooms;
  std::vector<int> number_of_rooms;
  std::vector<hotel_rooms_info_t> all_rooms_info;
  room_timetable_t initialize_time_table(void);
  float calc_weighted_average_of_manual_ratings(Weights* given_weights);
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
