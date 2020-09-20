#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
#include "src/rsdl.hpp"
#include "Background.hpp"

#define FIRING_RATE 150
#define MILISECONDS 1000

class Background;
class Enemy
{
public:
  void add_to_enemies_board(void);
  virtual void appear(void) = 0;
  void move_towards_square(Point p);
  void check_reached_sides(void);
  void adjust_velocity(Point destination);
  void change_x_direction_if_necessary(int x_distance);
  void change_y_direction_if_necessary(int y_distance);
  float health;
private:
  Window* window;
  Background* background;
  Point position;
  float velocity;
  int x_velocity;
  int y_velocity;
};
#endif
