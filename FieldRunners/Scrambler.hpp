#ifndef SCRAMBLER_HPP
#define SCRAMBLER_HPP

#include "Enemy.hpp"
#include "src/rsdl.hpp"

#define SCRAMBLER_FILE_PATH "Assets/enemies/scrambler.png"
#define SCRAMBLER_INITIAL_HEALTH_UNITS 100
#define SCRAMBLER_SPEED 90
#define SCRAMBLER_KILLING_GOLD_UNITS 4
#define SCRAMBLER_WINNING_HEART_DECREASE 2

class Scrambler : public Enemy
{
public:
  Scrambler(Window* w, Background* b, int square_x_index, int square_y_index);
  void add_to_board_squares(void);
  void move_towards_square(Point p);
  void appear(void);
  float health;
  Point position;
private:
  Window* window;
  //Point position;
  Background* background;
  int x_velocity;
  int y_velocity;

};

#endif
