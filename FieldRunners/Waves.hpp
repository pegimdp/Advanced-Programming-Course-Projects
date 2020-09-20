#ifndef WAVES_HPP
#define WAVES_HPP

#include "Background.hpp"
#include "Enemy.hpp"
#include "Runner.hpp"
#include "StubbornRunner.hpp"
#include "SuperTrooper.hpp"
#include "Scrambler.hpp"
#include "src/rsdl.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#define TIME_DELAY_BETWEEN_ENEMIES 500
#define TIME_DELAY_BETWEEN_WAVES 30000
#define RUNNER_ORDER 0
#define STUBBORN_RUNNER_ORDER 1
#define SUPER_TROOPER_ORDER 2
#define SCRAMBLER_ORDER 3
#define ENEMIES_TYPES 4
class Background;
class Waves
{
public:
  Waves(Window* w, Background* b);
  void is_in_level(void);
  void read_waves_path(void);
  void read_number_of_enemies_in_all_waves(void);
  void display_waves_path(void);
  void initialize_all_waves(void);
  void activate_all_waves(void);
  std::vector<int> read_number_of_enemies_in_wave(std::string given_wave);
  std::vector<std::vector<Enemy*>> enemies_in_all_waves;
private:
  Window* window;
  Background* background;
  int number_of_waves;
  std::vector<Point> waves_path_positions;
  std::vector<std::vector<int>> number_of_enemies_in_all_waves;
  void reset_all_enemies(void);
  void activate_wave_enemies(int wave_number);
  void move_enemy_along_wave_path(Enemy* this_enemy);
  void initialize_wave_runners(int wave_number, std::vector<Enemy*> given_wave_enemies);
  void initialize_wave_stubborn_runners(int wave_number, std::vector<Enemy*> given_wave_enemies);
  void initialize_wave_super_troppers(int wave_number, std::vector<Enemy*> given_wave_enemies);
  void initialize_wave_scramblers(int wave_number, std::vector<Enemy*> given_wave_enemies);
  void initialize_wave_enemies(int wave_number, std::vector<Enemy*> given_wave_enemies);
};

#endif
