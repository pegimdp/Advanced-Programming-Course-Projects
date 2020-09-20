#include "Glue.hpp"

Glue::Glue(Window* w, Background* b, Point p)
{
  level = 0;
  window = w;
  background = b;
  position = p;
  damage = GLUE_INITIAL_DAMAGE_POWER;
  current_glue_file_path = FIRST_GLUE_FILE_PATH;
  this->display_tower();
  this->add_to_board_squares();
}

void Glue::add_to_board_squares(void)
{
  int x_index = background->find_square_x_index(position.x);
  int y_index = background->find_square_y_index(position.y);
  background->towers_board[x_index][y_index];
}

void Glue::display_tower(void)
{
  window->draw_img(current_glue_file_path, Rectangle(position, SQUARE_SIDE_LENGTH, SQUARE_SIDE_LENGTH));
}

void Glue::upgrade_tower(void)
{
  current_glue_file_path = SECOND_GLUE_FILE_PATH;
}
