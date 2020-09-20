#include "FieldRunners.hpp"
#define DElAY_TIME 1000

FieldRunners::FieldRunners(void)
{
  window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
  background = new Background(window);
  last_clicked_used = true;
  waves = new Waves(window, background);
  waves->read_waves_path();
  waves->read_number_of_enemies_in_all_waves();
  waves->initialize_all_waves();

  towers = {};
  sr = new Scrambler(window, background, 0, 0);
}

void FieldRunners::draw_game(void)
{
  background->draw_background(BACKGROUND_PATH);
  this->display_towers();
  waves->display_waves_path();
  sr->appear();
  waves->activate_all_waves();
}

void FieldRunners::update_game()
{
  while(window->has_pending_event())
  {
		Event event = window->poll_for_event();
    Event::EventType event_type = event.get_type();
		switch(event_type)
    {
			case Event::EventType::QUIT:
				exit(0);
				break;
			case Event::EventType::LCLICK:
        last_clicked_point = event.get_mouse_position();
        last_clicked_used = false;
        break;
      case Event::EventType::KEY_PRESS:
        this->identify_key(event, last_clicked_point);
        break;
    }
	}
  sr->move_towards_square(background->return_top_left_corner(3,1));
  window->update_screen();
  delay(DElAY_TIME);
}

void FieldRunners::identify_key(const Event& event, Point mouse_clicked_position)
{
  char pressed_key;
  if(event.get_type() == Event::KEY_PRESS)
    pressed_key = event.get_pressed_key();
  if(last_clicked_used == false)
  {
    last_clicked_used = true;
    if(pressed_key == 'g')
      this->process_g_key(mouse_clicked_position);
    else if(pressed_key == 'm')
      this->process_m_key(mouse_clicked_position);
    else if(pressed_key == 't')
      this->process_t_key(mouse_clicked_position);
    else if(pressed_key == 'l')
      this->process_l_key(mouse_clicked_position);
    else if(pressed_key == 'u')
      this->process_u_key(mouse_clicked_position);
  }

}

void FieldRunners::process_g_key(Point clicked_position)
{
  if(background->is_in_board(clicked_position))
  {
    clicked_position = background->find_square_top_left_corner(clicked_position);
    Gatling* this_gatling = new Gatling(window, background, clicked_position);
    towers.push_back(this_gatling);
  }
}

void FieldRunners::process_m_key(Point clicked_position)
{
  if(background->is_in_board(clicked_position))
  {
    clicked_position = background->find_square_top_left_corner(clicked_position);
    Missile* this_missile = new Missile(window, background, clicked_position);
    towers.push_back(this_missile);
  }
}

void FieldRunners::process_t_key(Point clicked_position)
{
  if(background->is_in_board(clicked_position))
  {
    clicked_position = background->find_square_top_left_corner(clicked_position);
    Tesla* this_tesla = new Tesla(window, background, clicked_position);
    towers.push_back(this_tesla);
  }
}

void FieldRunners::process_l_key(Point clicked_position)
{
  if(background->is_in_board(clicked_position))
  {
    clicked_position = background->find_square_top_left_corner(clicked_position);
    Glue* this_glue = new Glue(window, background, clicked_position);
    towers.push_back(this_glue);
  }
}

void FieldRunners::process_u_key(Point clicked_position)
{
  int x_index = background->find_square_x_index(background->find_square_top_left_corner(clicked_position).x);
  int y_index = background->find_square_y_index(background->find_square_top_left_corner(clicked_position).y);
  if(background->towers_board[x_index][y_index])
  {
    background->towers_board[x_index][y_index]->upgrade_tower();
  }
}

void FieldRunners::display_towers(void)
{
  for(int tower = 0; tower < towers.size(); tower++)
    towers[tower]->display_tower();
}
