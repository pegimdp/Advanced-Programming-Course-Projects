#ifndef __USER_H__
#define __USER_H__

#include "Exceptions.hpp"
#include "Hotel.hpp"
#include "Reservation.hpp"
#include "Macros.hpp"
#include "Rating.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <numeric>
#include <cmath>

typedef std::string email_t;
typedef std::string username_t;
typedef std::string password_t;
typedef std::vector<Rating*> ratings_t;
typedef std::vector<float> turnover_t;
typedef std::vector<Reservation*> reservations_t;

class User
{
public:
  User(void) {}
  User(email_t email_, username_t username_, password_t password_);
  void cancel_reservation(int reservation_id);
  void increase_wallet_money(float given_money);
  void get_last_turnovers(int given_num_of_turnovers);
  void get_reserves(void);
  float calc_sample_room_cost_mean(void);
  float calc_sample_cost_standard_deviation(void);
  bool has_enough_reserves_for_default_filter(void);
  Reservation* find_reservation(int reservation_id);
  Reservation* add_reservation(std::string hotel_id, std::string room_type, int room_price, int quantity, float total_cost, int checkin_day, int checkout_day);
  void set_reservation_room_indices(Reservation* given_reservation, std::vector<int> indices);
  bool hotels_default_filter_turned_off;
  bool default_price_filter_applied;
  void logout(void);
  email_t email;
  username_t username;
  ratings_t given_ratings;
protected:
  password_t password;
  turnover_t all_turnovers;
  float wallet_money;
  int current_reservation_id;
  reservations_t reservations;
  void decrease_wallet_money(float given_money);
  int calc_num_of_reserved_rooms(void);
  int find_reservation_index(int reservation_id);
};
#endif
