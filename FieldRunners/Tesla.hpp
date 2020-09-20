#ifndef TESLA_HPP
#define TESLA_HPP

#include "Tower.hpp"
#include "src/rsdl.hpp"

#define FIRST_TESLA_FILE_PATH "Assets/towers/tesla1.png"
#define SECOND_TESLA_FILE_PATH "Assets/towers/tesla2.png"
#define THIRD_TESLA_FILE_PATH "Assets/towers/tesla3.png"
#define TESLA_SQUARE_STRING "Gatling"
#define TESLA_ATTACK_TIME_INTERVAL 1000
#define TESLA_FIRING_RANGE 150
#define TESLA_CONSTRUCTION_COST 55
#define TESLA_UPGRADE_COST 40
#define TESLA_INITIAL_DAMAGE_POWER 35
#define TESLA_UPDATE_DAMAGE_POWER 35



class Tesla : public Tower
{
public:
  Tesla(Window* w, Background* b, Point p);
  void add_to_board_squares(void);
  void display_tower(void);
  void upgrade_tower();
  //void shoot_enemy();

private:
  Point position;
  Window* window;
  Background* background;
  int level;
  int damage;
  std::string current_tesla_file_path;

};

#endif
