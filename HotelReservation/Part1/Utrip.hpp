#ifndef __UTRIP_H__
#define __UTRIP_H__

#include "Exceptions.hpp"
#include "Hotel.hpp"
#include "Filter.hpp"
#include "User.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

#define AMOUNT "amount"
#define CITY "city"
#define COMMENT "comment"
#define COMMENTS "comments"
#define COUNT "count"
#define DELETE_COMMAND "DELETE"
#define EMAIL "email"
#define EMPTY "Empty"
#define FILTERS "filters"
#define GET_COMMAND "GET"
#define HOTEL "hotel"
#define HOTELS "hotels"
#define LOGIN "login"
#define LOGOUT "logout"
#define MAX_PRICE "max_price"
#define MAX_STAR "max_star"
#define MIN_PRICE "min_price"
#define MIN_STAR "min_star"
#define NUM_OF_AVERAGE_PRICE_FILTER_INFO_PARTS 4
#define NUM_OF_DELETE_RESERVES_INFO_PARTS 2
#define NUM_OF_HOTEL_COMMENT_INFO_PARTS 4
#define NUM_OF_HOTEL_RATINGS_INFO_PARTS 14
#define NUM_OF_CITY_FILTER_INFO_PARTS 2
#define NUM_OF_GET_COMMENTS_INFO_PARTS 2
#define NUM_OF_GET_RATINGS_INFO_PARTS 2
#define NUM_OF_LOGIN_INFO_PARTS 4
#define NUM_OF_MONEY_AMOUNT_INFO_PARTS 2
#define NUM_OF_RATING_RAGE_FILTER_INFO_PARTS 4
#define NUM_OF_RESERVATION_COMMAND_INFO_PARTS 10
#define NUM_OF_SIGNUP_INFO_PARTS 6
#define NUM_OF_SPECIFIC_ROOM_IN_INTERVAL_FILTER_INFO_PARTS 8
#define NUM_OF_SPECIFIC_HOTEL_INFO_PARTS 2
#define NUM_OF_TURNOVERS_INFO_PARTS 2
#define OK_MESSAGE "OK"
#define OVERALL_RATING_COMMAND "overall_rating"
#define PASSWORD "password"
#define POST_COMMAND "POST"
#define QUANTITY "quantity"
#define QUESTION_MARK "?"
#define RATINGS "ratings"
#define RESERVES "reserves"
#define SIGNUP "signup"
#define SPACE ' '
#define TYPE "type"
#define USERNAME "username"
#define VALUE_FOR_MONEY_COMMAND "value_for_money"
#define WALLET "wallet"

typedef std::vector<std::string> essential_command_parts_t;
typedef std::vector<std::string> input_line_t;
typedef std::vector<Hotel*> hotels_t;
typedef std::vector<User*> users_t;

class Utrip
{
public:
  Utrip();
  ~Utrip();
  void logout(void);
  void get_all_hotels(void);
  void identify_input(std::string given_input);
  void read_hotels(std::string file_address);
  void login(email_t given_email,password_t given_password);
  void signup(email_t given_email, username_t given_username, password_t given_password);
private:
  User* current_user;
  hotels_t hotels;
  hotels_t filtered_hotels;
  users_t users;
  void delete_filters(void);
  void delete_reserves(std::string reservation_id);
  void increase_user_money(float given_money);
  void get_current_users_reserves(void);
  void get_commands(info_parts_t command_line);
  void post_commands(info_parts_t command_line);
  void add_hotel(std::string given_hotel);
  void parse_delete_filters(info_parts_t command_line);
  void parse_filters(info_parts_t command_line);
  void parse_delete_reserves(info_parts_t command_line);
  void parse_delete_commands(info_parts_t command_line);
  void parse_get_comments(info_parts_t hotel_id);
  void parse_get_ratings(info_parts_t hotel_id);
  void parse_specific_hotel_command(info_parts_t hotel_id);
  void parse_turnovers_command(info_parts_t turnovers_count);
  void parse_money_amount_command(info_parts_t money_amount);
  void parse_reservation_command(info_parts_t command_line);
  void parse_signup_command(info_parts_t command_line);
  void parse_login_command(info_parts_t command_line);
  void parse_hotel_comment(info_parts_t command_line);
  void parse_hotel_ratings(info_parts_t command_line);
  void set_filtered_hotels(hotels_t given_hotels);
  void add_comment_to_hotel(std::string hotel_id, std::string comment);
  void add_ratings_to_hotel(essential_command_parts_t command_parts);
  void add_user(email_t given_email, username_t given_username, password_t given_password);
  bool user_has_commented(Hotel* given_hotel, User* given_user);
  bool filter_hotels_by_city(info_parts_t command_line);
  bool filter_hotels_by_rating(info_parts_t command_line);
  bool filter_hotels_by_average_price(info_parts_t command_line);
  bool filter_hotels_by_free_rooms(info_parts_t command_line);
  int find_comment_index(Hotel* given_hotel, User* given_user);
  Hotel* find_hotel_by_id(std::string id);
  User* find_user_by_email(email_t given_email);
  User* find_user_by_username(username_t given_username);
  info_parts_t separate_parts(std::string connected_parts,char delimiter);
  void add_current_users_reservation(std::string hotel_id, std::string room_type, int quantity, int check_in, int check_out);
  bool find_essential_command_parts(essential_command_parts_t& given_essentials, info_parts_t command_line);
};

#endif
