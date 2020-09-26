#include "Hotel.hpp"

Hotel::Hotel(std::string unique_i, std::string name, int hotel_rating, std::string overview
      , amenities_t amenities, std::string city_, float latitude_, float longitude_
      , std::string image_url_, int num_of_standard_rooms, int num_of_deluxe_rooms
      , int num_of_luxury_rooms, int num_of_premium_rooms, float standard_room_price
      , float deluxe_room_price, float luxury_room_price, float premium_room_price)
{
  unique_id = unique_i;
  property_name = name;
  hotel_star_rating = hotel_rating;
  hotel_overview = overview;
  property_amenities = amenities;
  city = city_;
  latitude = latitude_;
  longitude = longitude_;
  image_url = image_url_;
  all_ratings = {};
  all_comments = {};
  current_user_personal_rating = 0;
  standard_info = { num_of_standard_rooms, standard_room_price };
  deluxe_info = { num_of_deluxe_rooms, deluxe_room_price };
  luxury_info = { num_of_luxury_rooms, luxury_room_price };
  premium_info = { num_of_premium_rooms, premium_room_price };
  all_rooms_info = {standard_info, deluxe_info, luxury_info, premium_info};
  initialize_specific_rooms(standard_rooms, standard_info, S);
  initialize_specific_rooms(deluxe_rooms, deluxe_info, D);
  initialize_specific_rooms(luxury_rooms, luxury_info, L);
  initialize_specific_rooms(premium_rooms, premium_info, P);
  calc_total_num_of_rooms();
  calc_average_room_price();
}

void Hotel::print_comments(void)
{
  for(auto comment:all_comments)
    std::cout << comment[0] << COLON << SPACE << comment[1] << std::endl;
}

void Hotel::print_hotel_general_info(void)
{
  std::cout << unique_id << SPACE << property_name << SPACE << hotel_star_rating
            << SPACE << city << SPACE << total_number_of_rooms << SPACE
            << std::fixed << std::setprecision(2) << average_room_price  << SPACE << std::endl;
}

void Hotel::print_hotel_specific_info(void)
{
  std::cout << unique_id << std::endl << property_name << std::endl
           << STAR << COLON << SPACE << hotel_star_rating << std::endl
           << OVERVIEW << COLON << SPACE << hotel_overview << std::endl;
  print_feature<amenities_t>(AMENITIES, property_amenities, VERTICAL_LINE);
  std::cout << CITY << COLON << SPACE << city << std::endl
            << LATITUDE << COLON << SPACE << std::fixed << std::setprecision(2) << latitude << std::endl
            << LONGITUDE << COLON << SPACE << longitude << std::endl << std::setprecision(0);
  print_feature<std::vector<int>>(NUM_OF_ROOMS, number_of_rooms, SPACE);
  print_feature<std::vector<float>>(PRICE, all_rooms_price, SPACE);
  std::cout << SPACE;
}

void Hotel::initialize_specific_rooms(std::vector<room_info_t>& specific_rooms, hotel_rooms_info_t room_info, char specific_char)
{
  specific_rooms = {};
  for(int room = 0; room < room_info.number_of_rooms; room++)
  {
    room_info_t this_room_info;
    this_room_info.name = (specific_char + std::to_string(room+1));
    this_room_info.timetable = initialize_time_table();
    specific_rooms.push_back(this_room_info);
  }
}

void Hotel::calc_total_num_of_rooms(void)
{
  total_number_of_rooms = 0;
  number_of_rooms = {};
  for(int room = 0; room < all_rooms_info.size(); room++)
  {
    number_of_rooms.push_back(all_rooms_info[room].number_of_rooms);
    total_number_of_rooms += all_rooms_info[room].number_of_rooms;
  }
}

void Hotel::calc_average_room_price(void)
{
  float sum = 0;
  int num_of_nonzero_price_rooms = 0;
  all_rooms_price = {};
  for(int room = 0; room < all_rooms_info.size(); room++)
  {
    if(all_rooms_info[room].price != 0)
    {
      sum += all_rooms_info[room].price;
      num_of_nonzero_price_rooms += 1;
    }
    all_rooms_price.push_back(all_rooms_info[room].price);
  }
  average_room_price = sum/num_of_nonzero_price_rooms;
  if(num_of_nonzero_price_rooms == 0)
    average_room_price = 0;
}

template<typename T>
void Hotel::print_feature(std::string feature_name, T features, char delimiter)
{
  std::cout << feature_name << COLON << SPACE;
  for(int count = 0; count < features.size(); count++)
  {
    std::cout << features[count];
    if(count != features.size()-1)
      std::cout << delimiter;
  }
  std::cout << std::endl;
}

room_timetable_t Hotel::initialize_time_table(void)
{
  room_timetable_t timetable = {};
  for(int day = 0; day < NUM_OF_DAYS_IN_MONTH; day++)
    timetable.push_back(EMPTY_ROOM_CODE);
  return timetable;
}

hotel_rooms_info_t Hotel::find_room_type(std::string room_type)
{
  if(room_type.compare(STANDARD) == 0)
    return standard_info;
  else if(room_type.compare(DELUXE) == 0)
    return deluxe_info;
  else if(room_type.compare(LUXURY) == 0)
    return luxury_info;
  else
    return premium_info;
}

std::vector<room_info_t>& Hotel::identify_rooms(std::string room_type)
{
  if(room_type.compare(STANDARD) == 0)
    return standard_rooms;
  else if(room_type.compare(DELUXE) == 0)
    return deluxe_rooms;
  else if(room_type.compare(LUXURY) == 0)
    return luxury_rooms;
  else
    return premium_rooms;
}

int Hotel::find_number_of_free_rooms(std::string room_type, int checkin_day, int checkout_day)
{
  std::vector<room_info_t>& these_rooms = identify_rooms(room_type);
  int num_of_free_rooms = 0;
  for(int room = 0; room < these_rooms.size(); room++)
  {
    if(!is_room_available(room_type, room, checkin_day, checkout_day))
      return num_of_free_rooms;
    num_of_free_rooms += 1;
  }
  return num_of_free_rooms;
}

bool Hotel::is_room_available(std::string room_type, int room_index, int checkin, int checkout)
{
  std::vector<room_info_t>& these_rooms = identify_rooms(room_type);
  for(int day = checkin-1; day < checkout; day++)
  {
    if(these_rooms[room_index].timetable[day] != EMPTY_ROOM_CODE)
      return false;
  }
  return true;
}

bool Hotel::is_valid_room_type(std::string given_type)
{
  if(given_type.compare(STANDARD) == 0 || given_type.compare(DELUXE) == 0 ||
     given_type.compare(LUXURY) == 0 || given_type.compare(PREMIUM) == 0)
     return true;
  return false;
}

bool Hotel::is_valid_reservation_date(int checkin, int checkout)
{
  if(checkin <= checkout || checkin < 1 ||checkout > NUM_OF_DAYS_IN_MONTH)
    return true;
  return false;
}

std::vector<int> Hotel::find_available_rooms_indices(std::string room_type, int quantity, int checkin, int checkout)
{
  if(!is_valid_room_type(room_type))
    throw InvalidRequest();
  if(!is_valid_reservation_date(checkin, checkout))
    throw InvalidRequest();
  if(quantity > this->find_number_of_free_rooms(room_type, checkin, checkout))
    throw RoomShortage();
  std::vector<room_info_t>& these_rooms = identify_rooms(room_type);
  int quantity_tracker = 0;
  std::vector<int> available_rooms = {};
  for(int room = 0; room < these_rooms.size(); room++)
  {
    if(quantity <= quantity_tracker)
      return available_rooms;
    if(is_room_available(room_type, room, checkin, checkout))
      available_rooms.push_back(room);
    quantity_tracker++;
  }
  return available_rooms;
}

float Hotel::find_room_price(std::string room_type)
{
  hotel_rooms_info_t this_type = find_room_type(room_type);
  return this_type.price;
}

float Hotel::find_reservation_cost(std::string room_type, int quantity, int checkin, int checkout)
{
  hotel_rooms_info_t this_type = find_room_type(room_type);
  return this_type.price * quantity * (checkout-checkin+1);
}

void Hotel::free_rooms(std::string given_type, std::vector<int> room_indices, int checkin, int checkout)
{
  std::vector<room_info_t>& these_rooms = identify_rooms(given_type);
  for(int room = 0; room < room_indices.size(); room++)
  {
    for(int day = checkin-1; day < checkout; day++)
      these_rooms[room].timetable[day] = EMPTY_ROOM_CODE;
  }
}

std::vector<int> Hotel::reserve_rooms(std::string given_type, std::vector<int> given_rooms_indices, int checkin, int checkout)
{
  std::vector<int> these_indices = {};
  std::vector<room_info_t>& these_rooms = identify_rooms(given_type);
  for(int room_index:given_rooms_indices)
  {
    room_info_t& room = these_rooms[room_index];
    for(int day = checkin-1; day < checkout; day++)
      room.timetable[day] = RESERVED_ROOM_CODE;
    std::cout << room.name << SPACE;
    these_indices.push_back(room.name[1]-'0');
  }
  std::cout << std::endl;
  return these_indices;
}

void Hotel::add_comment(std::string the_user, std::string comment)
{
  std::vector<std::string> this_comment = {the_user, comment};
  all_comments.push_back(this_comment);
}

void Hotel::calc_user_personal_rating(User* given_user, Weights* given_weights)
{
  auto it = std::find_if(all_ratings.begin(), all_ratings.end(), [&](Rating* this_rating) { return this_rating->users_username == given_user->username; } );
  if(it != all_ratings.end())
    current_user_personal_rating = it[0]->ratings[OVERALL_RATING_INDEX];
  else if(given_weights->manual_weights_activated)
    current_user_personal_rating = given_weights->calc_weighted_average_of_rating(average_rating, given_weights->manual_weights);
  else if(given_user->given_ratings.size() < MIN_NUM_OF_RATINGS_FOR_WEIGHT_ESTIMATION)
    throw InsufficientRatings();
  else
  {
    given_weights->estimate_weights_by_gradient_descent(this, given_user, GRADIENT_DESCENT_NUM_OF_STEPS);
    current_user_personal_rating = given_weights->calc_weighted_average_of_rating(average_rating, given_weights->estimated_weights);
  }
}
