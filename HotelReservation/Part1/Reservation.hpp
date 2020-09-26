#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include <string>
#include <vector>
#include <iostream>

#define ID "id"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define COLON ':'
#define COST "cost"
#define HOTEL "hotel"
#define QUANTITY "quantity"
#define ROOM "room"
#define SPACE ' '

class Reservation
{
public:
  Reservation(int id_, std::string hotel_id_, std::string room_type_
              , int quantity_, float cost_, int check_in_, int check_out_);
  void print_reservation(void);
  void set_rooms_indices(std::vector<int> given_indices);
  int id;
  std::string hotel_id;
  std::string room_type;
  int check_in;
  int check_out;
  int cost;
  std::vector<int> rooms_indices;
private:
  int quantity;
};


#endif
