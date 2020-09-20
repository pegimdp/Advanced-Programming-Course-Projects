#ifndef GATLING_HPP
#define GATLING_HPP

#include "Tower.hpp"
#include "src/rsdl.hpp"

#define FIRST_GATLING_FILE_PATH "Assets/towers/gattling1.png"
#define SECOND_GATLING_FILE_PATH "Assets/towers/gattling2.png"
#define THIRD_GATLING_FILE_PATH "Assets/towers/gattling3.png"
#define GATLING_SQUARE_STRING "Gatling"
#define GATLING_ATTACK_TIME_INTERVAL 1000
#define GATLING_FIRING_RANGE 150
#define GATLING_CONSTRUCTION_COST 55
#define GATLING_UPGRADE_COST 40
#define GATLING_INITIAL_DAMAGE_POWER 35
#define GATLING_UPDATE_DAMAGE_POWER 35



class Gatling : public Tower
{
public:
  Gatling(Window* w, Background* b, Point p);
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
  std::string current_gatling_file_path;

};

#endif
