#ifndef RUNNER_HPP
#define RUNNER_HPP

#include "Enemy.hpp"
#include "src/rsdl.hpp"

#define RUNNER_FILE_PATH "Assets/enemies/runner.png"
#define RUNNER_INITIAL_HEALTH_UNITS 250
#define RUNNER_SPEED 50
#define RUNNER_KILLING_GOLD_UNITS 6
#define RUNNER_WINNING_HEART_DECREASE 1

class Background;
class Runner : public Enemy
{
public:
  Runner(Window* w, Background* b, int square_x_index, int square_y_index);
  void add_to_board_squares(void);
  void move_towards_square(Point p);
  void appear(void);
  Point position;
  float health;
private:
  Window* window;
  //Point position;
  Background* background;
  float velocity;
  int x_velocity;
  int y_velocity;

};

#endif
