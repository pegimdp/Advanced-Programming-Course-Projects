#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "Tower.hpp"
#include "src/rsdl.hpp"

#define FIRST_MISSILE_FILE_PATH "Assets/towers/missile1.png"
#define SECOND_MISSILE_FILE_PATH "Assets/towers/missile2.png"
#define THIRD_MISSILE_FILE_PATH "Assets/towers/missile3.png"
#define MISSILE_SQUARE_STRING "Missile"
#define MISSILE_ATTACK_TIME_INTERVAL 3000
#define MISSILE_CONSTRUCTION_COST 70
#define MISSILE_FIRING_RANGE 50
#define MISSILE_UPGRADE_COST 60
#define MISSILE_INITIAL_DAMAGE_POWER 75
#define MISSILE_UPDATE_DAMAGE_POWER 75



class Missile : public Tower
{
public:
  Missile(Window* w, Background* b, Point p);
  void add_to_board_squares(void);
  void display_tower(void);
  void upgrade_tower();

private:
  Point position;
  Window* window;
  Background* background;
  int level;
  int damage;
  std::string current_missile_file_path;
};

#endif
