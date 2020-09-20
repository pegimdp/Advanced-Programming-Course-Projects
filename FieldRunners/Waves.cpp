#include "Waves.hpp"

Waves::Waves(Window* w, Background* b)
{
  window = w;
  background = b;
  waves_path_positions = {};
  number_of_enemies_in_all_waves = {};
  enemies_in_all_waves = {};
}

void Waves::read_waves_path()
{
  std::string waves_path_line;
  getline(std::cin, waves_path_line);
  std::istringstream read_waves(waves_path_line);
  int x_value, y_value;
  while(read_waves >> x_value)
  {
    read_waves >> y_value;
    waves_path_positions.push_back(background->squares_corners[x_value][y_value]);
  }
}

std::vector<int> Waves::read_number_of_enemies_in_wave(std::string given_wave)
{
  std::vector<int> this_wave_enemies = {};
  std::istringstream wave_numbers(given_wave);
  int enemy_num;
  while(wave_numbers >> enemy_num)
    this_wave_enemies.push_back(enemy_num);
  return this_wave_enemies;
}

void Waves::read_number_of_enemies_in_all_waves(void)
{
  std::string this_line;
  std::vector<int> this_wave_enemies = {};
  while(getline(std::cin, this_line))
  {
    if(this_line.empty())
      break;
    this_wave_enemies = this->read_number_of_enemies_in_wave(this_line);
    number_of_enemies_in_all_waves.push_back(this_wave_enemies);
  }
  number_of_waves = number_of_enemies_in_all_waves.size();
}

void Waves::display_waves_path(void)
{
  for(int square = 0; square < waves_path_positions.size(); square++)
    background->draw_line_on_square(waves_path_positions[square]);
}

void Waves::initialize_wave_runners(int wave_number, std::vector<Enemy*> given_wave_enemies)
{
  for(int runner = 0; runner < number_of_enemies_in_all_waves[wave_number][RUNNER_ORDER]; runner++)
  {
    int x_index = background->find_square_x_index(waves_path_positions[0].x);
    int y_index = background->find_square_y_index(waves_path_positions[0].y);
    Runner* this_runner = new Runner(this->window, this->background, x_index, y_index);
    given_wave_enemies.push_back(this_runner);
  }
}

void Waves::initialize_wave_stubborn_runners(int wave_number, std::vector<Enemy*> given_wave_enemies)
{
  for(int stubborn_runner = 0; stubborn_runner < number_of_enemies_in_all_waves[wave_number][STUBBORN_RUNNER_ORDER]; stubborn_runner++)
  {
    int x_index = background->find_square_x_index(waves_path_positions[0].x);
    int y_index = background->find_square_y_index(waves_path_positions[0].y);
    StubbornRunner* this_stubborn_runner = new StubbornRunner(window, background, x_index, y_index);
    given_wave_enemies.push_back(this_stubborn_runner);
  }
}

void Waves::initialize_wave_super_troppers(int wave_number, std::vector<Enemy*> given_wave_enemies)
{
  for(int super_trooper = 0; super_trooper < number_of_enemies_in_all_waves[wave_number][SUPER_TROOPER_ORDER]; super_trooper++)
  {
    int x_index = background->find_square_x_index(waves_path_positions[0].x);
    int y_index = background->find_square_y_index(waves_path_positions[0].y);
    SuperTrooper* this_super_trooper = new SuperTrooper(window, background, x_index, y_index);
    given_wave_enemies.push_back(this_super_trooper);
  }
}

void Waves::initialize_wave_scramblers(int wave_number, std::vector<Enemy*> given_wave_enemies)
{
  for(int scrambler = 0; scrambler < number_of_enemies_in_all_waves[wave_number][SCRAMBLER_ORDER]; scrambler++)
  {
    int x_index = background->find_square_x_index(waves_path_positions[0].x);
    int y_index = background->find_square_y_index(waves_path_positions[0].y);
    Scrambler* this_scrambler = new Scrambler(window, background, x_index, y_index);
    given_wave_enemies.push_back(this_scrambler);
  }
}

void Waves::initialize_wave_enemies(int wave_number, std::vector<Enemy*> given_wave_enemies)
{
  this->initialize_wave_runners(wave_number, given_wave_enemies);
  this->initialize_wave_stubborn_runners(wave_number, given_wave_enemies);
  this->initialize_wave_super_troppers(wave_number, given_wave_enemies);
  this->initialize_wave_scramblers(wave_number, given_wave_enemies);
  random_shuffle(given_wave_enemies.begin(), given_wave_enemies.end());
}

void Waves::initialize_all_waves(void)
{
  std::vector<std::vector<Enemy*>> these_waves = {};
  for(int wave_num = 0; wave_num < number_of_waves; wave_num++)
  {
    std::vector<Enemy*> this_wave_enemies = {};
    initialize_wave_enemies(wave_num, this_wave_enemies);
    these_waves.push_back(this_wave_enemies);
  }
  enemies_in_all_waves = these_waves;
}

void Waves::activate_wave_enemies(int wave_number)
{
  for(int enemy = 0; enemy < enemies_in_all_waves[wave_number].size(); enemy++)
  {
    this->move_enemy_along_wave_path(enemies_in_all_waves[wave_number][enemy]);
    delay(TIME_DELAY_BETWEEN_ENEMIES);
  }
}

void Waves::move_enemy_along_wave_path(Enemy* this_enemy)
{
  this_enemy->appear();
  std::cout << this_enemy->health;
  for(int square = 0; square < waves_path_positions.size(); square++)
  {
   if(square == waves_path_positions.size()-1 or this_enemy->health >= 0)
       this_enemy->move_towards_square(waves_path_positions[square]);
  }
}

void Waves::activate_all_waves(void)
{
  for(int wave_num = 0; wave_num < number_of_waves; wave_num++)
    this->activate_wave_enemies(wave_num);
}

void Waves::reset_all_enemies(void)
{
  enemies_in_all_waves = {};
  for(int type = 0; type < number_of_waves; type++)
    enemies_in_all_waves.push_back({});
}
