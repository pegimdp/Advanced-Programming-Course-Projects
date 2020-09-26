#include "Reservation.hpp"

Reservation::Reservation(int id_, std::string hotel_id_, std::string room_type_
            , int quantity_, float cost_, int check_in_, int check_out_)
{
  id = id_;
  hotel_id = hotel_id_;
  room_type = room_type_;
  quantity = quantity_;
  cost = cost_;
  check_in = check_in_;
  check_out = check_out_;
  rooms_indices = {};
}

void Reservation::print_reservation(void)
{
  std::cout << ID << COLON << SPACE << id << SPACE << HOTEL << COLON << SPACE << hotel_id << SPACE << ROOM << COLON << SPACE << room_type
            << SPACE << QUANTITY << COLON << SPACE << quantity << SPACE << COST << COLON << SPACE << cost << SPACE << CHECK_IN  << SPACE
            << check_in << SPACE << CHECK_OUT << SPACE << check_out << std::endl;
}

void Reservation::set_rooms_indices(std::vector<int> given_indices)
{
  rooms_indices = given_indices;
}
