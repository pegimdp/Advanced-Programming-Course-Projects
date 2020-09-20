#ifndef SUPER_TROOPER_HPP
#define SUPER_TROOPER_HPP

#include "Enemy.hpp"
#include "src/rsdl.hpp"

#define SUPER_TROOPER_FILE_PATH "Assets/enemies/supertrooper.png"
#define SUPER_TROOPER_INITIAL_HEALTH_UNITS 500
#define SUPER_TROOPER_SPEED 25
#define SUPER_TROOPER_KILLING_GOLD_UNITS 8
#define SUPER_TROOPER_WINNING_HEART_DECREASE 4

class SuperTrooper : public Enemy
{
public:
  SuperTrooper(Window* w, Background* b, int square_x_index, int square_y_index);
  void add_to_board_squares(void);
  void move_towards_square(Point p);
  void appear(void);
  float health;
private:
  Window* window;
  Point position;
  Background* background;
  int x_velocity;
  int y_velocity;
};

#endif
