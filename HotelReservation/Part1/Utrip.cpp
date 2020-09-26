#include "Utrip.hpp"

Utrip::Utrip()
{
  current_user = NULL;
  hotels = {};
  filtered_hotels = {};
  users = {};
}

Utrip::~Utrip()
{
  delete current_user;
  for(auto hotel:hotels)
    delete hotel;
  for(auto user:users)
    delete user;
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
  set_filtered_hotels(hotels);
}

void Utrip::set_filtered_hotels(hotels_t given_hotels)
{
  filtered_hotels = {};
  for(auto hotel:given_hotels)
    filtered_hotels.push_back(hotel);
}

void Utrip::parse_signup_command(info_parts_t command_line)
{
  if(command_line.size() != NUM_OF_SIGNUP_INFO_PARTS)
    throw InvalidRequest();
  info_parts_t essential_parts = {EMAIL, USERNAME, PASSWORD};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
    throw InvalidRequest();
  signup(essential_parts[0], essential_parts[1], essential_parts[2]);
}

void Utrip::parse_login_command(info_parts_t command_line)
{
  if(command_line.size() != NUM_OF_LOGIN_INFO_PARTS)
    throw InvalidRequest();
  info_parts_t essential_parts = {EMAIL, PASSWORD};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
    throw InvalidRequest();
  login(essential_parts[0], essential_parts[1]);
}

void Utrip::parse_delete_reserves(info_parts_t command_line)
{
  if(command_line.size() != NUM_OF_DELETE_RESERVES_INFO_PARTS)
    throw InvalidRequest();
  info_parts_t essential_parts = {ID};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
    throw InvalidRequest();
  delete_reserves(essential_parts[0]);
}

void Utrip::parse_money_amount_command(info_parts_t money_amount)
{
  if(money_amount.size() != NUM_OF_MONEY_AMOUNT_INFO_PARTS)
    throw InvalidRequest();
  info_parts_t::iterator it = std::find(money_amount.begin(), money_amount.end(), AMOUNT);
  if(it != money_amount.end())
    increase_user_money(std::stof(*(++it)));
  else
    throw InvalidRequest();
}

void Utrip::parse_turnovers_command(info_parts_t turnovers_count)
{
  if(turnovers_count.size() != NUM_OF_TURNOVERS_INFO_PARTS)
    throw InvalidRequest();
  info_parts_t::iterator it = std::find(turnovers_count.begin(), turnovers_count.end(), COUNT);
  if(it != turnovers_count.end())
    current_user->get_last_turnovers(std::stoi(*(++it)));
  else
    throw InvalidRequest();
}

void Utrip::parse_specific_hotel_command(info_parts_t hotel_id)
{
  if(hotel_id.size() != NUM_OF_SPECIFIC_HOTEL_INFO_PARTS)
    throw InvalidRequest();
  if(!current_user)
    throw InvalidAccess();
  info_parts_t::iterator it = std::find(hotel_id.begin(), hotel_id.end(), ID);
  if(it != hotel_id.end() && it++ != hotel_id.end())
  {
    Hotel* this_hotel = this->find_hotel_by_id(*it);
    this_hotel->print_hotel_specific_info();
  }
  else
    throw InvalidRequest();
}

void Utrip::parse_filters(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  bool filtered = false;
  if(!filtered)
    filtered = filter_hotels_by_city(command_line);
  if(!filtered)
    filtered = filter_hotels_by_rating(command_line);
  if(!filtered)
    filtered = filter_hotels_by_average_price(command_line);
  if(!filtered)
    filtered = filter_hotels_by_free_rooms(command_line);
  if(!filtered)
    throw InvalidRequest();
}

void Utrip::parse_get_comments(info_parts_t hotel_id)
{
  if(hotel_id.size() != NUM_OF_GET_COMMENTS_INFO_PARTS)
    throw InvalidRequest();
  if(!current_user)
    throw InvalidAccess();
  info_parts_t::iterator it = std::find(hotel_id.begin(), hotel_id.end(), HOTEL);
  if(it != hotel_id.end() && it++ != hotel_id.end())
  {
    Hotel* this_hotel = this->find_hotel_by_id(*it);
    this_hotel->print_comments();
  }
  else
    throw InvalidRequest();
}

void Utrip::parse_get_ratings(info_parts_t hotel_id)
{
  if(hotel_id.size() != NUM_OF_GET_RATINGS_INFO_PARTS)
    throw InvalidRequest();
  if(!current_user)
    throw InvalidAccess();
  info_parts_t::iterator it = std::find(hotel_id.begin(), hotel_id.end(), HOTEL);
  if(it != hotel_id.end() && it++ != hotel_id.end())
  {
    Hotel* this_hotel = this->find_hotel_by_id(*it);
    this_hotel->print_average_ratings();
  }
  else
    throw InvalidRequest();
}

void Utrip::parse_reservation_command(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  if(command_line.size() != NUM_OF_RESERVATION_COMMAND_INFO_PARTS)
    throw InvalidRequest();
  info_parts_t essential_parts = {HOTEL, TYPE, QUANTITY, CHECK_IN, CHECK_OUT};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
    throw InvalidRequest();
  add_current_users_reservation(essential_parts[0], essential_parts[1], std::stoi(essential_parts[2])
                                      , std::stoi(essential_parts[3]), std::stoi(essential_parts[4]));
}

void Utrip::parse_hotel_ratings(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  if(command_line.size() != NUM_OF_HOTEL_RATINGS_INFO_PARTS)
    throw InvalidRequest();
  info_parts_t essential_parts = {HOTEL, LOCATION, CLEANLINESS, STAFF, FACILITIES, VALUE_FOR_MONEY_COMMAND, OVERALL_RATING_COMMAND};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
    throw InvalidRequest();
  add_ratings_to_hotel(essential_parts);
}

void Utrip::parse_hotel_comment(info_parts_t command_line)
{
  if(!current_user)
    throw InvalidAccess();
  if(command_line.size() != NUM_OF_HOTEL_COMMENT_INFO_PARTS)
    throw InvalidRequest();
  info_parts_t essential_parts = {HOTEL, COMMENT};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
      throw InvalidRequest();
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
  if(current_user)
  {
    if(filtered_hotels.size() == 0)
    {
      std::cout << EMPTY << std::endl;
      return;
    }
    std::sort(filtered_hotels.begin(), filtered_hotels.end(), compare_hotels);
    for(auto hotel:filtered_hotels)
      hotel->print_hotel_general_info();
  }
  else
    throw InvalidAccess();
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
  current_user = NULL;
  delete_filters();
}

bool Utrip::filter_hotels_by_city(info_parts_t command_line)
{
  info_parts_t essential_parts = {CITY};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
    return false;
  CityFilter* this_filter = new CityFilter(filtered_hotels);
  this_filter->add_filter(essential_parts);
  set_filtered_hotels(this_filter->get_hotels());
  std::cout << OK_MESSAGE << std::endl;
  return true;
}

bool Utrip::filter_hotels_by_rating(info_parts_t command_line)
{
  info_parts_t essential_parts = {MIN_STAR, MAX_STAR};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
    return false;
  RatingRange* this_filter = new RatingRange(filtered_hotels);
  this_filter->add_filter(essential_parts);
  set_filtered_hotels(this_filter->get_hotels());
  std::cout << OK_MESSAGE << std::endl;
  return true;
}

bool Utrip::filter_hotels_by_average_price(info_parts_t command_line)
{
  info_parts_t essential_parts = {MIN_PRICE, MAX_PRICE};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
    return false;
  AveragePriceRange* this_filter = new AveragePriceRange(filtered_hotels);
  this_filter->add_filter(essential_parts);
  set_filtered_hotels(this_filter->get_hotels());
  std::cout << OK_MESSAGE << std::endl;
  return true;
}

bool Utrip::filter_hotels_by_free_rooms(info_parts_t command_line)
{
  info_parts_t essential_parts = {TYPE, QUANTITY, CHECK_IN, CHECK_OUT};
  bool found_essentials = find_essential_command_parts(essential_parts, command_line);
  if(!found_essentials)
    return false;
  FreeRooms* this_filter = new FreeRooms(filtered_hotels);
  this_filter->add_filter(essential_parts);
  set_filtered_hotels(this_filter->get_hotels());
  std::cout << OK_MESSAGE << std::endl;
  return true;
}

bool Utrip::find_essential_command_parts(essential_command_parts_t& given_essentials, info_parts_t command_line)
{
  for(int part = 0; part < given_essentials.size(); part++)
  {
    info_parts_t::iterator it = std::find(command_line.begin(), command_line.end(), given_essentials[part]);
    if(it != command_line.end() && it++ != command_line.end())
      given_essentials[part] = *it;
    else
      return false;
  }
  return true;
}

void Utrip::delete_filters(void)
{
  set_filtered_hotels(hotels);
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
  float reservation_cost = this_hotel->find_reservation_cost(room_type, quantity, check_in, check_out);
  Reservation* this_reservation = current_user->add_reservation(hotel_id, room_type, quantity, reservation_cost, check_in, check_out);
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

void Utrip::add_ratings_to_hotel(essential_command_parts_t command_parts)
{
  Hotel* given_hotel = this->find_hotel_by_id(command_parts[0]);
  scores_t these_scores;
  these_scores.users_username = current_user->username;
  these_scores.location = std::stof(command_parts[1]);
  these_scores.cleanliness = std::stof(command_parts[2]);
  these_scores.staff = std::stof(command_parts[3]);
  these_scores.facilities = std::stof(command_parts[4]);
  these_scores.value_for_money = std::stof(command_parts[5]);
  these_scores.overall_rating = std::stof(command_parts[6]);
  if(user_has_commented(given_hotel, current_user))
    given_hotel->all_scores[find_comment_index(given_hotel, current_user)] = these_scores;
  given_hotel->all_scores.push_back(these_scores);
  std::cout << OK_MESSAGE << std::endl;
}

bool Utrip::user_has_commented(Hotel* given_hotel, User* given_user)
{
  for(int score = 0; score < given_hotel->all_scores.size(); score++)
  {
    if(given_hotel->all_scores[score].users_username.compare(given_user->username) == 0)
      return true;
  }
  return false;
}

int Utrip::find_comment_index(Hotel* given_hotel, User* given_user)
{
  for(int score = 0; score < given_hotel->all_scores.size(); score++)
  {
    if(given_hotel->all_scores[score].users_username.compare(given_user->username) == 0)
      return score;
  }

}
