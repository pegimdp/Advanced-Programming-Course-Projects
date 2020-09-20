#ifndef STUBBORN_RUNNER_HPP
#define STUBBORN_RUNNER_HPP

#include "Enemy.hpp"
#include "src/rsdl.hpp"

#define STUBBORN_RUNNER_FILE_PATH "Assets/enemies/stubborn-runner.png"
#define STUBBORN_RUNNER_INITIAL_HEALTH_UNITS 400
#define STUBBORN_RUNNER_SPEED 30
#define STUBBORN_RUNNER_KILLING_GOLD_UNITS 10
#define STUBBORN_RUNNER_WINNING_HEART_DECREASE 4

class StubbornRunner : public Enemy
{
public:
  StubbornRunner(Window* w, Background* b, int square_x_index, int square_y_index);
  void add_to_board_squares(void);
  void move_towards_square(Point p);
  void appear(void);
  int health;
  Point position;
private:
  Window* window;
  //Point position;
  Background* background;
  float velocity;
  int x_velocity;
  int y_velocity;
};

#endif
