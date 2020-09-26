#ifndef __UTRIP_H__
#define __UTRIP_H__

#include "Exceptions.hpp"
#include "Hotel.hpp"
#include "Macros.hpp"
#include "Filter.hpp"
#include "User.hpp"
#include "Weights.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

typedef std::vector<std::string> essential_command_parts_t;
typedef std::vector<std::string> input_line_t;
typedef std::vector<Hotel*> hotels_t;
typedef std::vector<User*> users_t;

class Utrip
{
public:
  Utrip();
  void logout(void);
  void get_all_hotels(void);
  void identify_input(std::string given_input);
  void read_hotels(std::string file_address);
  void read_average_ratings(std::string file_address);
  void apply_hotels_default_price_filter_if_possible(void);
  void login(email_t given_email,password_t given_password);
  void signup(email_t given_email, username_t given_username, password_t given_password);
private:
  User* current_user;
  Weights* rating_weights;
  hotels_t hotels;
  hotels_t filtered_hotels;
  users_t users;
  bool hotels_sorted;
  bool any_filter_activated;
  void delete_filters(void);
  void delete_reserves(std::string reservation_id);
  void parse_default_price_filter(info_parts_t command_line);
  void increase_user_money(float given_money);
  void get_current_users_reserves(void);
  void get_commands(info_parts_t command_line);
  void post_commands(info_parts_t command_line);
  void add_hotel(std::string given_hotel);
  void add_hotel_average_rating(std::string given_rating);
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
  void parse_sort_command(info_parts_t command_line);
  void get_manual_weights(void);
  void parse_manual_weights_command(info_parts_t command_line);
  void parse_deactivate_manuals(info_parts_t command_line);
  void set_filtered_hotels(hotels_t given_hotels, bool activation_state);
  void sort_filtered_hotels_by_ascending_property(std::string given_property);
  void sort_filtered_hotels_by_descending_property(std::string given_property);
  void add_comment_to_hotel(std::string hotel_id, std::string comment);
  void add_ratings_to_hotel_and_user(essential_command_parts_t command_parts);
  void add_user(email_t given_email, username_t given_username, password_t given_password);
  bool filter_hotels_by_city(info_parts_t command_line);
  bool filter_hotels_by_default(void);
  bool filter_hotels_by_rating(info_parts_t command_line);
  bool filter_hotels_by_average_price(info_parts_t command_line);
  bool filter_hotels_by_free_rooms(info_parts_t command_line);
  int find_comment_index(Hotel* given_hotel, User* given_user);
  Hotel* find_hotel_by_id(std::string id);
  User* find_user_by_email(email_t given_email);
  User* find_user_by_username(username_t given_username);
  info_parts_t separate_parts(std::string connected_parts,char delimiter);
  info_parts_t find_essential_info_parts(const int& num_of_info_parts, const info_parts_t& given_essentials, info_parts_t given_command_line);
  void add_current_users_reservation(std::string hotel_id, std::string room_type, int quantity, int check_in, int check_out);
  void calc_current_users_personal_rating_for_filtered_hotels(void);
  bool find_essential_command_parts(essential_command_parts_t& given_essentials, info_parts_t command_line);
};

#endif
