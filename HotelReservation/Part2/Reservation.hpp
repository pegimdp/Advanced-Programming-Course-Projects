#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include "Macros.hpp"
#include <string>
#include <vector>
#include <iostream>

class Reservation
{
public:
  Reservation(int id_, std::string hotel_id_, std::string room_type_, int room_price_
              , int quantity_, float cost_, int check_in_, int check_out_);
  void print_reservation(void);
  void set_rooms_indices(std::vector<int> given_indices);
  int id;
  std::string hotel_id;
  std::string room_type;
  int room_price;
  int check_in;
  int check_out;
  int cost;
  int quantity;
  std::vector<int> rooms_indices;
};


#endif
