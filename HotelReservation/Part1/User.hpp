#ifndef __USER_H__
#define __USER_H__

#include "Exceptions.hpp"
#include "Hotel.hpp"
#include "Reservation.hpp"
#include <vector>
#include <string>
#include <iostream>

#define EMPTY "Empty"

typedef std::string email_t;
typedef std::string username_t;
typedef std::string password_t;
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
  Reservation* find_reservation(int reservation_id);
  Reservation* add_reservation(std::string hotel_id, std::string room_type, int quantity, float total_cost, int checkin_day, int checkout_day);
  void set_reservation_room_indices(Reservation* given_reservation, std::vector<int> indices);
  email_t email;
  username_t username;
protected:
  password_t password;
  turnover_t all_turnovers;
  float wallet_money;
  int current_reservation_id;
  reservations_t reservations;
  int find_reservation_index(int reservation_id);
};
#endif
