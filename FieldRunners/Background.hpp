#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include "src/rsdl.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include <string>
#include <vector>
#include <cmath>

#define BACKGROUND_PATH "Assets/background.png"
#define NUMBER_OF_SQUARES_IN_WIDTH 19
#define NUMBER_OF_SQUARES_IN_HEIGTH 11
#define NULL_POINTER NULL
#define BOARD_TOP_LEFT_X 120
#define BOARD_TOP_LEFT_Y 175
#define SQUARE_SIDE_LENGTH 60

class Tower;
class Enemy;
class Background
{
public:
  Background(Window* w);
  bool is_in_board(Point position);
  int find_square_x_index(float x_coordinate);
  int find_square_y_index(float y_coordinate);
  int find_x_distance(Point p_one, Point p_two);
  int find_y_distance(Point p_one, Point p_two);
  Point find_square_center(Point corner_point);
  float find_distance(Point one, Point two);
  Point find_square_top_left_corner(Point position);
  Point return_top_left_corner(int x_index, int y_index);
  void add_to_enemies_board(int x_index , int y_index , Enemy* e);
  void draw_background(std::string background_file_path);
  void draw_line_on_square(Point square_corner);
  bool is_tower_square_empty(int x_index, int y_index);
  bool is_enemy_square_empty(int x_index, int y_index);
  std::vector<std::vector<Point>> squares_corners;
  std::vector<std::vector<Tower*>> towers_board;
  std::vector<std::vector<Enemy*>> enemies_board;
private:
  Window* window;
  void initialize_towers_board(void);
  void initialize_enemies_board(void);
  void initialize_squares_corners(void);
  std::vector<Point> initialize_squares_corners_y_value(int given_x_value);
};

#endif
