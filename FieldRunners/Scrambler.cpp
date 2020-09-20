#include "Scrambler.hpp"

Scrambler::Scrambler(Window* w, Background* b, int square_x_index, int square_y_index)
{
  window = w;
  background = b;
  health = SCRAMBLER_INITIAL_HEALTH_UNITS;
  position = background->return_top_left_corner(square_x_index, square_y_index);
  x_velocity = y_velocity = SCRAMBLER_SPEED;
  health = SCRAMBLER_INITIAL_HEALTH_UNITS;
}

void Scrambler::appear(void)
{
  window->draw_img(SCRAMBLER_FILE_PATH, Rectangle(position, SQUARE_SIDE_LENGTH, SQUARE_SIDE_LENGTH));
}

void Scrambler::move_towards_square(Point p)
{
  int x_distance = background->find_x_distance(position, p);
  int y_distance = background->find_y_distance(position, p);
  if(abs(x_distance) < SQUARE_SIDE_LENGTH)
    this->x_velocity = 0;
  if(abs(y_distance) < SQUARE_SIDE_LENGTH)
    this->y_velocity = 0;
  this->change_x_direction_if_necessary(x_distance);
  this->change_y_direction_if_necessary(y_distance);
  position.x += x_velocity;
  position.y += y_velocity;
  this->check_reached_sides();

}
