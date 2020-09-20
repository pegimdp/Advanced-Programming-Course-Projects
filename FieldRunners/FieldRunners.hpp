#ifndef FIELDRUNNERS_HPP
#define FIELDRUNNERS_HPP
#include "src/rsdl.hpp"
#include "Tower.hpp"
#include "Gatling.hpp"
#include "Missile.hpp"
#include "Tesla.hpp"
#include "Glue.hpp"
#include "Enemy.hpp"
#include "Runner.hpp"
#include "StubbornRunner.hpp"
#include "SuperTrooper.hpp"
#include "Scrambler.hpp"
#include "Background.hpp"
#include "Waves.hpp"
#include <string>
#include <vector>
#include <iostream>

#define GAME_NAME "Field Runners"
#define WINDOW_WIDTH 1365
#define WINDOW_HEIGHT 1024


class FieldRunners
{
public:
  FieldRunners(void);
  void draw_game(void);
  void update_game(void);
private:
  Scrambler* sr;
  Window* window;
  Background* background;
  Waves* waves;
  std::vector<Tower*> towers;
  Point last_clicked_point;
  bool last_clicked_used;
  void display_towers(void);
  void process_g_key(Point clicked_position);
  void process_m_key(Point clicked_position);
  void process_t_key(Point clicked_position);
  void process_l_key(Point clicked_position);
  void process_u_key(Point clicked_position);
  void identify_key(const Event& event, Point mouse_clicked_position);
};
#endif
