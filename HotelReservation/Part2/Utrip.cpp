#include "Utrip.hpp"

Utrip::Utrip()
{
  current_user = NULL;
  hotels = {};
  filtered_hotels = {};
  users = {};
  any_filter_activated = false;
  hotels_sorted = false;
  rating_weights = new Weights();
}

void Utrip::identify_input(std::string given_input)
{
  info_parts_t command_line = separate_parts(given_input, SPACE);
  if(command_line.size() > 1)
    if(command_line[0].compare(GET_COMMAND) == 0)
      this->get_commands(info_parts_t(command_line.begin()+1, command_line.end()));
    else if(command_line[0].compare(POST_COMMAND) == 0)
      this->post_commands(info_parts_t(command_line.begin()+1, command_line.end()));
    else if(command_line[0].compare(DELETE_COMMAND) == 0)
      this->parse_delete_commands(info_parts_t(command_line.begin()+1, command_line.end()));
    else
      throw InvalidRequest();
  else
    throw InvalidRequest();
}

void Utrip::get_commands(info_parts_t command_line)
{
  if(command_line[0].compare(WALLET) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_turnovers_command(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(HOTELS) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_specific_hotel_command(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(COMMENTS) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_get_comments(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(RATINGS) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_get_ratings(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(MANUAL_WEIGHTS) == 0)
    get_manual_weights();
  else if(command_line[0].compare(HOTELS) == 0)
    get_all_hotels();
  else if(command_line[0].compare(RESERVES) == 0)
    get_current_users_reserves();
  else
    throw InvalidCommand();
}

void Utrip::post_commands(info_parts_t command_line)
{
  if(command_line[0].compare(SIGNUP) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_signup_command(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(LOGIN) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_login_command(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(LOGOUT) == 0)
    logout();
  else if(command_line[0].compare(WALLET) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_money_amount_command(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(FILTERS) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_filters(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(RESERVES) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_reservation_command(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(COMMENTS) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_hotel_comment(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(RATINGS) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_hotel_ratings(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(DEFAULT_PRICE_FILTER) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_default_price_filter(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(SORT) == 0 && command_line.size() >= 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_sort_command(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(MANUAL_WEIGHTS) == 0 && command_line.size() > 4 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_manual_weights_command(info_parts_t(command_line.begin()+2, command_line.end()));
  else if(command_line[0].compare(MANUAL_WEIGHTS) == 0 && command_line.size() == 4 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_deactivate_manuals(info_parts_t(command_line.begin()+2, command_line.end()));
  else
    throw InvalidCommand();
}

void Utrip::parse_delete_commands(info_parts_t command_line)
{
  if(command_line[0].compare(FILTERS) == 0)
    delete_filters();
  else if(command_line[0].compare(RESERVES) == 0 && command_line.size() > 2 && command_line[1].compare(QUESTION_MARK) == 0)
    parse_delete_reserves(info_parts_t(command_line.begin()+2, command_line.end()));
  else
    throw InvalidCommand();
}

void Utrip::read_hotels(std::string file_address)
{
  std::ifstream all_hotels(file_address);
  std::string this_hotel;
  std::getline(all_hotels, this_hotel);
  while(std::getline(all_hotels, this_hotel))
    this->add_hotel(this_hotel);
  set_filtered_hotels(hotels, false);
  all_hotels.close();
}

void Utrip::read_average_ratings(std::string file_address)
{
  std::ifstream all_ratings(file_address);
  std::string this_rating;
  std::getline(all_ratings, this_rating);
  while(std::getline(all_ratings, this_rating))
    this->add_hotel_average_rating(this_rating);
}

void Utrip::set_filtered_hotels(hotels_t given_hotels, bool activation_state)
{
  filtered_hotels = {};
  for(auto hotel:given_hotels)
    filtered_hotels.push_back(hotel);
  any_filter_activated = activation_state;
}

info_parts_t Utrip::find_essential_info_parts(const int& num_of_info_parts, const info_parts_t& given_essentials, info_parts_t given_command_line)
{
  if(given_command_line.size() != num_of_info_parts)
    throw InvalidRequest();
  info_parts_t found_essentials = {};
  for(int part = 0; part < given_essentials.size(); part++)
  {
    info_parts_t::iterator it = std::find(given_command_line.begin(), given_command_line.end(), given_essentials[part]);
    if(it != given_command_line.end() && it++ != given_command_line.end())
      found_essentials.push_back(*it);
    else
      throw InvalidRequest();
  }
  return found_essentials;
}

void Utrip::parse_signup_command(info_parts_t command_line)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_SIGNUP_INFO_PARTS, {EMAIL, USERNAME, PASSWORD}, command_line);
  signup(essential_parts[0], essential_parts[1], essential_parts[2]);
}

void Utrip::parse_sort_command(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_SORT_INFO_PARTS, {PROPERTY, ORDER}, command_line);
  if(essential_parts[1].compare(ASCENDING) == 0)
    sort_filtered_hotels_by_ascending_property(essential_parts[0]);
  else if(essential_parts[1].compare(DESCENDING) == 0)
    sort_filtered_hotels_by_descending_property(essential_parts[0]);
  else
    throw InvalidRequest();
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::parse_manual_weights_command(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_MANUAL_WEIGHTS_INFO_PARTS, {ACTIVE, TRUE_, LOCATION, CLEANLINESS, STAFF, FACILITIES, VALUE_FOR_MONEY}, command_line);
  essential_parts = info_parts_t(essential_parts.begin() + 2, essential_parts.end());
  weights_t all_weights = {};
  for(int part = 0; part < essential_parts.size(); part++)
  {
    if(!(1 <= std::stof(essential_parts[part]) && std::stof(essential_parts[part]) <= 5))
      throw InvalidRequest();
    all_weights.push_back(std::stof(essential_parts[part]));
  }
  rating_weights->manual_weights_activated = true;
  rating_weights->set_manual_weights(all_weights);
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::parse_deactivate_manuals(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  info_parts_t essential_parts = find_essential_info_parts(TWO, {ACTIVE, FALSE_}, command_line);
  rating_weights->manual_weights_activated = false;
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::parse_login_command(info_parts_t command_line)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_LOGIN_INFO_PARTS, {EMAIL, PASSWORD}, command_line);
  login(essential_parts[0], essential_parts[1]);
}

void Utrip::parse_delete_reserves(info_parts_t command_line)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_DELETE_RESERVES_INFO_PARTS, {ID}, command_line);
  delete_reserves(essential_parts[0]);
}

void Utrip::parse_default_price_filter(info_parts_t command_line)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_DEFAULT_FILTER_INFO_PARTS, {ACTIVE}, command_line);
  if(essential_parts[0].compare(TRUE_) == 0)
    apply_hotels_default_price_filter_if_possible();
  else if(essential_parts[0].compare(FALSE_) == 0)
    current_user->hotels_default_filter_turned_off = true;
  else
    throw InvalidRequest();
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::parse_money_amount_command(info_parts_t money_amount)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_MONEY_AMOUNT_INFO_PARTS, {AMOUNT}, money_amount);
  increase_user_money(std::stof(essential_parts[0]));
}

void Utrip::parse_turnovers_command(info_parts_t turnovers_count)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_TURNOVERS_INFO_PARTS, {COUNT}, turnovers_count);
  current_user->get_last_turnovers(std::stoi(essential_parts[0]));
}

void Utrip::parse_specific_hotel_command(info_parts_t hotel_id)
{
  if(!current_user)
    throw InvalidAccess();
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_SPECIFIC_HOTEL_INFO_PARTS, {ID}, hotel_id);
  Hotel* this_hotel = this->find_hotel_by_id(essential_parts[0]);
  this_hotel->print_hotel_specific_info();
}

void Utrip::parse_filters(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  bool filtered = false;
  try
  {
    if(!filtered)
      filtered = filter_hotels_by_city(command_line);
  }
  catch(std::exception& ex)
  {
    ;
  }
  try
  {
    if(!filtered)
      filtered = filter_hotels_by_rating(command_line);
  }
  catch(std::exception& ex)
  {
    ;
  }
  try
  {
    if(!filtered)
      filtered = filter_hotels_by_average_price(command_line);
  }
  catch(std::exception& ex)
  {
    ;
  }
  try
  {
    if(!filtered)
      filtered = filter_hotels_by_free_rooms(command_line);
  }
  catch(std::exception& ex)
  {
    ;
  }
  if(!filtered)
    std::cout << "True";
    //throw InvalidRequest();
}

void Utrip::parse_get_comments(info_parts_t hotel_id)
{
  if(!current_user)
    throw InvalidAccess();
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_GET_COMMENTS_INFO_PARTS, {HOTEL}, hotel_id);
  info_parts_t::iterator it = std::find(hotel_id.begin(), hotel_id.end(), HOTEL);
  Hotel* this_hotel = this->find_hotel_by_id(essential_parts[0]);
  this_hotel->print_comments();
}

void Utrip::parse_get_ratings(info_parts_t hotel_id)
{
  if(!current_user)
    throw InvalidAccess();
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_GET_RATINGS_INFO_PARTS, {HOTEL}, hotel_id);
  Hotel* this_hotel = this->find_hotel_by_id(essential_parts[0]);
  this_hotel->average_rating->print_rating();
}

void Utrip::get_manual_weights(void)
{
  if(!current_user)
    throw InvalidAccess();;
  if(rating_weights->manual_weights_activated)
    rating_weights->print_manual_weights();
  else
    std::cout << ACTIVE << SPACE << FALSE_ << std::endl;
}

void Utrip::parse_reservation_command(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_RESERVATION_COMMAND_INFO_PARTS, {HOTEL, TYPE, QUANTITY, CHECK_IN, CHECK_OUT}, command_line);
  add_current_users_reservation(essential_parts[0], essential_parts[1], std::stoi(essential_parts[2]), std::stoi(essential_parts[3])
                                , std::stoi(essential_parts[4]));
}

void Utrip::parse_hotel_ratings(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_HOTEL_RATINGS_INFO_PARTS, {HOTEL, LOCATION, CLEANLINESS, STAFF, FACILITIES, VALUE_FOR_MONEY, OVERALL_RATING}, command_line);
  add_ratings_to_hotel_and_user(essential_parts);
}

void Utrip::parse_hotel_comment(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_HOTEL_COMMENT_INFO_PARTS, {HOTEL, COMMENT}, command_line);
  add_comment_to_hotel(essential_parts[0], essential_parts[1]);
}

void Utrip::signup(email_t given_email, username_t given_username, password_t given_password)
{
  User* this_user = this->find_user_by_email(given_email);
  if(this_user)
    throw InvalidRequest();
  this_user = this->find_user_by_username(given_username);
  if(this_user)
    throw InvalidRequest();
  this->add_user(given_email, given_username, given_password);
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::login(email_t given_email,password_t given_password)
{
  if(current_user == NULL)
    current_user = new User();
  else if(current_user->email.compare(given_email) == 0)
    throw InvalidRequest();
  User* this_user = this->find_user_by_email(given_email);
  if(this_user == NULL)
    throw InvalidRequest();
  else
    current_user = this_user;
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::increase_user_money(float given_money)
{
  if(current_user)
    current_user->increase_wallet_money(given_money);
  else
    throw InvalidAccess();
  std::cout << OK_MESSAGE << std::endl;
}

bool compare_hotels(Hotel* first, Hotel* second)
{
  return (first->unique_id.compare(second->unique_id) < 0);
}

void Utrip::get_all_hotels(void)
{
  if(!current_user)
    throw InvalidAccess();
  if(filtered_hotels.size() == 0)
  {
      std::cout << EMPTY << std::endl;
      return;
  }
  if(current_user->default_price_filter_applied)
    std::cout << DEFAULT_PRICE_FILTER_GET_HOTELS_MESSAGE << std::endl;
  if(!hotels_sorted)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), compare_hotels);
  for(auto hotel:filtered_hotels)
    hotel->print_hotel_general_info();

}

void Utrip::add_hotel(std::string given_hotel)
{
  info_parts_t all_hotel_info = separate_parts(given_hotel, COMMA);
  Hotel* this_hotel = new Hotel(all_hotel_info[0], all_hotel_info[1], std::stoi(all_hotel_info[2]), all_hotel_info[3]
                                , separate_parts(all_hotel_info[4], VERTICAL_LINE), all_hotel_info[5], std::stof(all_hotel_info[6])
                                , std::stof(all_hotel_info[7]), all_hotel_info[8], std::stoi(all_hotel_info[9]), std::stoi(all_hotel_info[10])
                                , std::stoi(all_hotel_info[11]), std::stoi(all_hotel_info[12]), std::stof(all_hotel_info[13])
                                , std::stof(all_hotel_info[14]), std::stof(all_hotel_info[15]), std::stof(all_hotel_info[16]));
  hotels.push_back(this_hotel);
}

void Utrip::add_hotel_average_rating(std::string given_rating)
{
  info_parts_t all_rating_info = separate_parts(given_rating, COMMA);
  Hotel* this_hotel = find_hotel_by_id(all_rating_info[0]);
  this_hotel->average_rating = new Rating(this_hotel->unique_id, std::stof(all_rating_info[1]), std::stof(all_rating_info[2]), std::stof(all_rating_info[3]), std::stof(all_rating_info[4])
                                          , std::stof(all_rating_info[5]), std::stof(all_rating_info[6]), ALL_USERS);
}

void Utrip::add_user(email_t given_email, username_t given_username, password_t given_password)
{
  current_user = new User(given_email, given_username, given_password);
  users.push_back(current_user);
}

Hotel* Utrip::find_hotel_by_id(std::string id)
{
  for(int hotel = 0; hotel < hotels.size(); hotel++)
  {
    if(hotels[hotel]->unique_id.compare(id) == 0)
      return hotels[hotel];
  }
  throw InvalidCommand();
}

User* Utrip::find_user_by_email(email_t given_email)
{
  for(auto user : users)
  {
    if(given_email.compare(user->email) == 0)
      return user;
  }
  return NULL;
}

User* Utrip::find_user_by_username(username_t given_username)
{
  for(auto user : users)
  {
    if(given_username.compare(user->username) == 0)
      return user;
  }
  return NULL;
}

info_parts_t Utrip::separate_parts(std::string connected_parts,char delimiter)
 {
   std::vector<std::string> separated;
   std::stringstream connected(connected_parts);
   std::string each_part;
   while(getline(connected, each_part, delimiter))
     separated.push_back(each_part);
   return separated;
 }

void Utrip::logout(void)
{
  if(current_user == NULL)
    throw InvalidAccess();
    current_user->logout();
  current_user = NULL;
  delete_filters();
}

bool Utrip::filter_hotels_by_city(info_parts_t command_line)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_CITY_FILTER_INFO_PARTS, {CITY}, command_line);
  CityFilter* this_filter = new CityFilter(filtered_hotels);
  this_filter->add_filter(essential_parts);
  set_filtered_hotels(this_filter->get_hotels(), true);
  std::cout << OK_MESSAGE << std::endl;
  return true;
}

bool Utrip::filter_hotels_by_default(void)
{
  DefaultFilter* this_filter = new DefaultFilter(hotels);
  this_filter->add_filter(current_user->calc_sample_room_cost_mean(), current_user->calc_sample_cost_standard_deviation());
  set_filtered_hotels(this_filter->get_hotels(), false);
  return true;
}

bool Utrip::filter_hotels_by_rating(info_parts_t command_line)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_HOTEL_RATINGS_INFO_PARTS, {MIN_STAR, MAX_STAR}, command_line);
  RatingRange* this_filter = new RatingRange(filtered_hotels);
  this_filter->add_filter(essential_parts);
  set_filtered_hotels(this_filter->get_hotels(), true);
  return true;
}

bool Utrip::filter_hotels_by_average_price(info_parts_t command_line)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_AVERAGE_PRICE_FILTER_INFO_PARTS, {MIN_PRICE, MAX_PRICE}, command_line);
  AveragePriceRange* this_filter = new AveragePriceRange(filtered_hotels);
  this_filter->add_filter(essential_parts);
  set_filtered_hotels(this_filter->get_hotels(), true);
  std::cout << OK_MESSAGE << std::endl;
  return true;
}

bool Utrip::filter_hotels_by_free_rooms(info_parts_t command_line)
{
  info_parts_t essential_parts = find_essential_info_parts(NUM_OF_SPECIFIC_ROOM_IN_INTERVAL_FILTER_INFO_PARTS, {TYPE, QUANTITY, CHECK_IN, CHECK_OUT}, command_line);
  FreeRooms* this_filter = new FreeRooms(filtered_hotels);
  this_filter->add_filter(essential_parts);
  set_filtered_hotels(this_filter->get_hotels(), true);
  std::cout << OK_MESSAGE << std::endl;
  return true;
}

void Utrip::delete_filters(void)
{
  set_filtered_hotels(hotels, false);
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::delete_reserves(std::string reservation_id)
{
  if(!current_user)
    throw InvalidAccess();
  Reservation* this_reservation = current_user->find_reservation(std::stoi(reservation_id));
  current_user->cancel_reservation(std::stoi(reservation_id));
  Hotel* this_hotel = find_hotel_by_id(this_reservation->hotel_id);
  this_hotel->free_rooms(this_reservation->room_type, this_reservation->rooms_indices, this_reservation->check_in, this_reservation->check_out);
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::add_current_users_reservation(std::string hotel_id, std::string room_type, int quantity, int check_in, int check_out)
{
  Hotel* this_hotel = find_hotel_by_id(hotel_id);
  std::vector<int> available_rooms_indices = this_hotel->find_available_rooms_indices(room_type, quantity, check_in, check_out);
  float room_price = this_hotel->find_room_price(room_type);
  float reservation_cost = this_hotel->find_reservation_cost(room_type, quantity, check_in, check_out);
  Reservation* this_reservation = current_user->add_reservation(hotel_id, room_type, room_price, quantity, reservation_cost, check_in, check_out);
  std::vector<int> reserved_indices = this_hotel->reserve_rooms(room_type, available_rooms_indices, check_in, check_out);
  current_user->set_reservation_room_indices(this_reservation, reserved_indices);
};

void Utrip::get_current_users_reserves(void)
{
  if(!current_user)
    throw InvalidAccess();
  current_user->get_reserves();
}

void Utrip::add_comment_to_hotel(std::string hotel_id, std::string comment)
{
  Hotel* given_hotel = this->find_hotel_by_id(hotel_id);
  given_hotel->add_comment(current_user->username, comment);
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::add_ratings_to_hotel_and_user(essential_command_parts_t command_parts)
{
  Hotel* given_hotel = this->find_hotel_by_id(command_parts[0]);
  Rating* this_rating = new Rating(command_parts[0], std::stof(command_parts[1]), std::stof(command_parts[2]), std::stof(command_parts[3]), std::stof(command_parts[4])
                              , std::stof(command_parts[5]), std::stof(command_parts[6]), current_user->username);
  ratings_t::iterator it1 = find_if(given_hotel->all_ratings.begin(), given_hotel->all_ratings.end(), [&](Rating* r) { return r->users_username.compare(current_user->username) == 0; } );
  ratings_t::iterator it2 = find_if(current_user->given_ratings.begin(), current_user->given_ratings.end(), [&](Rating* r) { return r->hotel_id.compare(given_hotel->unique_id) == 0; } );
  if(it1 == given_hotel->all_ratings.end())
    given_hotel->all_ratings.push_back(this_rating);
  else
    *it1 = this_rating;
  if(it2 == current_user->given_ratings.end())
    current_user->given_ratings.push_back(this_rating);
  else
    *it2 = this_rating;
  std::cout << OK_MESSAGE << std::endl;
}

void Utrip::apply_hotels_default_price_filter_if_possible(void)
{
  if(!current_user)
    return;
  if(!any_filter_activated && current_user->has_enough_reserves_for_default_filter() && !current_user->hotels_default_filter_turned_off)
  {
    any_filter_activated = filter_hotels_by_default();
    current_user->default_price_filter_applied = true;
  }
}

void Utrip::sort_filtered_hotels_by_ascending_property(std::string given_property)
{
  if(given_property.compare(ID) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->unique_id < second->unique_id; } );
  else if(given_property.compare(NAME) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->property_name < second->property_name || (first->property_name == second->property_name && first->unique_id < second->unique_id); } );
  else if(given_property.compare(STAR_RATING) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->hotel_star_rating < second->hotel_star_rating || (first->hotel_star_rating == second->hotel_star_rating && first->unique_id < second->unique_id); } );
  else if(given_property.compare(CITY) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->city < second->city || (first->city == second->city && first->unique_id < second->unique_id); } );
  else if(given_property.compare(STANDARD_ROOM_PRICE) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->standard_info.price < second->standard_info.price || (first->standard_info.price == second->standard_info.price && first->unique_id < second->unique_id); });
  else if(given_property.compare(DELUXE_ROOM_PRICE) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->deluxe_info.price < second->deluxe_info.price || (first->deluxe_info.price == second->deluxe_info.price && first->unique_id < second->unique_id); });
  else if(given_property.compare(LUXURY_ROOM_PRICE) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->luxury_info.price < second->luxury_info.price || (first->luxury_info.price == second->luxury_info.price && first->unique_id < second->unique_id); });
  else if(given_property.compare(PREMIUM_ROOM_PRICE) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->premium_info.price < second->premium_info.price || (first->premium_info.price == second->premium_info.price && first->unique_id < second->unique_id); });
  else if(given_property.compare(AVERGAE_ROOM_PRICE) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->average_room_price < second->average_room_price || (first->average_room_price == second->average_room_price && first->unique_id < second->unique_id); });
  else if(given_property.compare(RATING_PERSONAL) == 0)
  {
    calc_current_users_personal_rating_for_filtered_hotels();
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->current_user_personal_rating < second->current_user_personal_rating || (first->current_user_personal_rating == second->current_user_personal_rating && first->unique_id < second->unique_id); });
  }
  else
    throw InvalidRequest();
  hotels_sorted = true;

}

void Utrip::sort_filtered_hotels_by_descending_property(std::string given_property)
{
  if(given_property.compare(ID) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->unique_id > second->unique_id; } );
  else if(given_property.compare(NAME) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->property_name > second->property_name || (first->property_name == second->property_name && first->unique_id < second->unique_id); } );
  else if(given_property.compare(STAR_RATING) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->hotel_star_rating > second->hotel_star_rating || (first->hotel_star_rating == second->hotel_star_rating && first->unique_id < second->unique_id); } );
  else if(given_property.compare(CITY) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->city > second->city || (first->city == second->city && first->unique_id < second->unique_id); });
  else if(given_property.compare(STANDARD_ROOM_PRICE) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->standard_info.price > second->standard_info.price || (first->standard_info.price == second->standard_info.price && first->unique_id < second->unique_id); });
  else if(given_property.compare(DELUXE_ROOM_PRICE) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->deluxe_info.price > second->deluxe_info.price || (first->deluxe_info.price == second->deluxe_info.price && first->unique_id < second->unique_id); });
  else if(given_property.compare(LUXURY_ROOM_PRICE) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->luxury_info.price > second->luxury_info.price || (first->luxury_info.price == second->luxury_info.price && first->unique_id < second->unique_id); });
  else if(given_property.compare(PREMIUM_ROOM_PRICE) == 0)
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->premium_info.price > second->premium_info.price || (first->premium_info.price == second->premium_info.price && first->unique_id < second->unique_id); });
    else if(given_property.compare(AVERGAE_ROOM_PRICE) == 0)
      std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->average_room_price > second->average_room_price || (first->average_room_price == second->average_room_price && first->unique_id < second->unique_id); });
  else if(given_property.compare(RATING_PERSONAL) == 0)
  {
    calc_current_users_personal_rating_for_filtered_hotels();
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), [](const Hotel* first, const Hotel* second) { return first->current_user_personal_rating > second->current_user_personal_rating || (first->current_user_personal_rating == second->current_user_personal_rating && first->unique_id < second->unique_id); });
  }
  else
    throw InvalidRequest();
  hotels_sorted = true;
}

void Utrip::calc_current_users_personal_rating_for_filtered_hotels(void)
{
  for(auto hotel:filtered_hotels)
    hotel->calc_user_personal_rating(current_user, rating_weights);
}
