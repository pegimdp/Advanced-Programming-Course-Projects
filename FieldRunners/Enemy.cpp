#include "Enemy.hpp"

void Enemy::add_to_enemies_board(void)
{
  int x_index = background->find_square_x_index(position.x);
  int y_index = background->find_square_y_index(position.y);
  background->add_to_enemies_board(x_index, y_index, this);
}

void Enemy::change_x_direction_if_necessary(int x_distance)
{
  if(x_distance < 0)
    x_velocity *= -1;
}

void Enemy::change_y_direction_if_necessary(int y_distance)
{
  if(y_distance < 0)
    y_velocity *= -1;
}

void Enemy::adjust_velocity(Point destination)
{
  int x_distance = background->find_x_distance(position, destination);
  int y_distance = background->find_y_distance(position, destination);
  if(abs(x_distance) < SQUARE_SIDE_LENGTH)
    this->x_velocity = 0;
  if(abs(y_distance) < SQUARE_SIDE_LENGTH)
    this->y_velocity = 0;
  this->change_x_direction_if_necessary(x_distance);
  this->change_y_direction_if_necessary(y_distance);
}


void Enemy::check_reached_sides(void)
{
  if(position.x < BOARD_TOP_LEFT_X || position.x > BOARD_TOP_LEFT_X + (NUMBER_OF_SQUARES_IN_WIDTH+1) * SQUARE_SIDE_LENGTH)
  {
    position.x -= x_velocity;
    x_velocity = 0;
  }
  if(position.y < BOARD_TOP_LEFT_Y || position.x > BOARD_TOP_LEFT_Y + (NUMBER_OF_SQUARES_IN_HEIGTH+1) * SQUARE_SIDE_LENGTH)
  {
    position.y -= y_velocity;
    y_velocity = 0;
  }

}

void Enemy::move_towards_square(Point p)
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
