#ifndef GLUE_HPP
#define GLUE_HPP

#include "Tower.hpp"
#include "src/rsdl.hpp"

#define FIRST_GLUE_FILE_PATH "Assets/towers/glue1.png"
#define SECOND_GLUE_FILE_PATH "Assets/towers/glue2.png"
#define THIRD_GLUE_FILE_PATH "Assets/towers/glue3.png"
#define GLUE_SQUARE_STRING "Gatling"
#define GLUE_ATTACK_TIME_INTERVAL 1000
#define GLUE_FIRING_RANGE 150
#define GLUE_CONSTRUCTION_COST 55
#define GLUE_UPGRADE_COST 40
#define GLUE_INITIAL_DAMAGE_POWER 35
#define GLUE_UPDATE_DAMAGE_POWER 35



class Glue : public Tower
{
public:
  Glue(Window* w, Background* b, Point p);
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
  std::string current_glue_file_path;

};

#endif
