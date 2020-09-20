#include "Tesla.hpp"

Tesla::Tesla(Window* w, Background* b, Point p)
{
  level = 0;
  window = w;
  background = b;
  position = p;
  damage = TESLA_INITIAL_DAMAGE_POWER;
  current_tesla_file_path = FIRST_TESLA_FILE_PATH;
  this->display_tower();
  this->add_to_board_squares();
}

void Tesla::add_to_board_squares(void)
{
  int x_index = background->find_square_x_index(position.x);
  int y_index = background->find_square_y_index(position.y);
  background->towers_board[x_index][y_index];
}

void Tesla::display_tower(void)
{
  window->draw_img(current_tesla_file_path, Rectangle(position, SQUARE_SIDE_LENGTH, SQUARE_SIDE_LENGTH));
}

void Tesla::upgrade_tower(void)
{
  current_tesla_file_path = SECOND_TESLA_FILE_PATH;
}
