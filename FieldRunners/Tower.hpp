#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <vector>
#include "src/rsdl.hpp"
#include "Background.hpp"

#define MAXIMUM_UPGRADE_TIMES

class Background;
class Tower
{
public:
  virtual void add_to_board_squares(void) = 0;
  virtual void display_tower(void) = 0;
  virtual void upgrade_tower() = 0;
  //virtual void shoot_enemy();
private:
  Window* window;
  Background* background;
  Point position;
  int level;
  int damage;
};
#endif
