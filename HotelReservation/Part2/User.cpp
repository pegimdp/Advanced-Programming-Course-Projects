#include "User.hpp"
#include <iostream>
User::User(email_t email_, username_t username_, password_t password_)
{
  email = email_;
  username = username_;
  password = password_;
  given_ratings = {};
  wallet_money = 0;
  all_turnovers = {0};
  reservations = {};
  current_reservation_id = 0;
  hotels_default_filter_turned_off = false;
  default_price_filter_applied = false;
}

void User::cancel_reservation(int reservation_id)
{
  int this_reservation_index = find_reservation_index(reservation_id);
  increase_wallet_money(reservations[this_reservation_index]->cost/2);
  reservations.erase(reservations.begin()+this_reservation_index);
}

void User::increase_wallet_money(float given_money)
{
  if(given_money <= 0)
    throw InvalidRequest();
  wallet_money += given_money;
  all_turnovers.push_back(wallet_money);
}

void User::decrease_wallet_money(float given_money)
{
  if(given_money >= wallet_money)
    throw CreditShortage();
  wallet_money -= given_money;
  all_turnovers.push_back(wallet_money);
}

void User::get_last_turnovers(int given_num_of_turnovers)
{
  if(given_num_of_turnovers < 0)
    throw InvalidRequest();
  int number_of_turnovers = given_num_of_turnovers;
  if(given_num_of_turnovers > all_turnovers.size())
    number_of_turnovers = all_turnovers.size();
  for(auto turnover = all_turnovers.rbegin(); turnover < all_turnovers.rbegin() + number_of_turnovers; turnover++)
    std::cout << *turnover << std::endl;
}

Reservation* User::add_reservation(std::string hotel_id, std::string room_type, int room_price, int quantity, float total_cost, int checkin_day, int checkout_day)
{
  decrease_wallet_money(total_cost);
  current_reservation_id += 1;
  Reservation* this_reservation = new Reservation(current_reservation_id, hotel_id, room_type, room_price, quantity, total_cost, checkin_day, checkout_day);
  reservations.push_back(this_reservation);
  return this_reservation;
}

void User::get_reserves(void)
{
  if(reservations.size() == 0)
  {
    std::cout << EMPTY << std::endl;
    return;
  }
  for(reservations_t::reverse_iterator it = reservations.rbegin(); it != reservations.rend(); it++)
    it[0]->print_reservation();
}

int User::find_reservation_index(int reservation_id)
{
  for(int index = 0; index < reservations.size(); index++)
  {
    if(reservations[index]->id == reservation_id)
      return index;
  }
  throw InvalidCommand();
}

Reservation* User::find_reservation(int reservation_id)
{
  for(int index = 0; index < reservations.size(); index++)
  {
    if(reservations[index]->id == reservation_id)
      return reservations[index];
  }
  throw InvalidCommand();
}

void User::set_reservation_room_indices(Reservation* reservation_, std::vector<int> indices)
{
  reservation_->set_rooms_indices(indices);
}

int User::calc_num_of_reserved_rooms(void)
{
  return std::accumulate(reservations.begin(), reservations.end(), 0, [](const int& acc, const Reservation* data) { return acc + data->quantity; });
}

float User::calc_sample_room_cost_mean(void)
{
  float all_rooms_cost = std::accumulate(reservations.begin(), reservations.end(), 0, [](const int& acc, const Reservation* data) { return acc + (data->room_price * data->quantity); });
  return all_rooms_cost/calc_num_of_reserved_rooms();
}

float User::calc_sample_cost_standard_deviation(void)
{
  float s = sqrt(std::accumulate(reservations.begin(), reservations.end(), 0, [&](const int& acc, const Reservation* data) { return acc + data->quantity * pow((data->room_price - calc_sample_room_cost_mean()), TWO); })
              /(calc_num_of_reserved_rooms() - 1));
  return s;
}

bool User::has_enough_reserves_for_default_filter(void)
{
  if(reservations.size() >= MIN_RESERVATIONS_FOR_DEFAULT_FILTER)
    return true;
  else
    return false;
}

void User::logout(void)
{
  default_price_filter_applied = false;
  hotels_default_filter_turned_off = false;
}
