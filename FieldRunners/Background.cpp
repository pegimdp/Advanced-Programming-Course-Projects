#include "Background.hpp"

Background::Background(Window* w)
{
  window = w;
  this->initialize_squares_corners();
  this->initialize_towers_board();
  this->initialize_enemies_board();
}

void Background::initialize_towers_board(void)
{
  std::vector<std::vector<Tower*>> this_board = {};
  for(int width = 0; width < NUMBER_OF_SQUARES_IN_WIDTH; width++)
  {
    std::vector<Tower*> this_column = {};
    for(int heigth = 0; heigth < NUMBER_OF_SQUARES_IN_HEIGTH; heigth++)
      this_column.push_back(nullptr);
    this_board.push_back(this_column);
  }
  this->towers_board = this_board;
}

void Background::initialize_enemies_board(void)
{
  std::vector<std::vector<Enemy*>> this_board = {};
  for(int width = 0; width < NUMBER_OF_SQUARES_IN_WIDTH; width++)
  {
    std::vector<Enemy*> this_column;
    for(int heigth = 0; heigth < NUMBER_OF_SQUARES_IN_HEIGTH; heigth++)
      this_column.push_back(nullptr);
    this_board.push_back(this_column);
  }
  this->enemies_board = this_board;
}

bool Background::is_in_board(Point position)
{
  if(position.x >= BOARD_TOP_LEFT_X && position.x <= BOARD_TOP_LEFT_X + NUMBER_OF_SQUARES_IN_WIDTH * SQUARE_SIDE_LENGTH &&
     position.y >= BOARD_TOP_LEFT_Y && position.y <= BOARD_TOP_LEFT_Y + NUMBER_OF_SQUARES_IN_HEIGTH * SQUARE_SIDE_LENGTH)
     return true;
  else
    return false;
}

int Background::find_square_x_index(float x_coordinate)
{
  int x_position = x_coordinate;
  x_position -= BOARD_TOP_LEFT_X;
  for(int subtractor = 0; subtractor < NUMBER_OF_SQUARES_IN_WIDTH; subtractor++)
  {
    if(x_position >= 0 && x_position < 60)
      return subtractor;
    x_position -= SQUARE_SIDE_LENGTH;
  }
}

int Background::find_square_y_index(float y_coordinate)
{
  int y_position = y_coordinate;
  y_position -= BOARD_TOP_LEFT_Y;
  for(int subtractor = 0; subtractor < NUMBER_OF_SQUARES_IN_HEIGTH; subtractor++)
  {
    if(y_position >= 0 && y_position < 60)
      return subtractor;
    y_position -= SQUARE_SIDE_LENGTH;
  }
}

int Background::find_x_distance(Point p_one, Point p_two)
{
  return (p_two.x - p_one.x);

}

int Background::find_y_distance(Point p_one, Point p_two)
{
  return (p_two.y - p_one.y);
}

Point Background::find_square_center(Point corner_point)
{
  float center_x = corner_point.x;
  float center_y = corner_point.y;
  center_x += SQUARE_SIDE_LENGTH/2;
  center_y += SQUARE_SIDE_LENGTH/2;
  return Point(center_x, center_y);
}

Point Background::find_square_top_left_corner(Point position)
{
  int square_x_position = this->find_square_x_index(position.x);
  int square_y_position = this->find_square_y_index(position.y);
  Point corner(BOARD_TOP_LEFT_X, BOARD_TOP_LEFT_Y);
  corner.x += square_x_position * SQUARE_SIDE_LENGTH;
  corner.y += square_y_position * SQUARE_SIDE_LENGTH;
  return corner;
}

Point Background::return_top_left_corner(int x_index, int y_index)
{
  Point answer(0, 0);
  answer.x = BOARD_TOP_LEFT_X + x_index * SQUARE_SIDE_LENGTH;
  answer.y = BOARD_TOP_LEFT_Y + y_index * SQUARE_SIDE_LENGTH;
  return answer;
}

void Background::add_to_enemies_board(int x_index , int y_index , Enemy* e)
{
  enemies_board[x_index][y_index] = e;
}

void Background::draw_background(std::string background_file_path)
{
  window->draw_img(background_file_path);
}

void Background::initialize_squares_corners(void)
{
  int x_value = BOARD_TOP_LEFT_X;
  squares_corners = {};
  for(int width = 0; width < NUMBER_OF_SQUARES_IN_WIDTH; width++)
  {
    squares_corners.push_back(this->initialize_squares_corners_y_value(x_value));
    x_value += SQUARE_SIDE_LENGTH;
  }
}

std::vector<Point> Background::initialize_squares_corners_y_value(int given_x_value)
{
  std::vector<Point> this_line = {};
  int y_value = BOARD_TOP_LEFT_Y;
  for(int heigth = 0; heigth < NUMBER_OF_SQUARES_IN_HEIGTH; heigth++)
  {
    this_line.push_back(Point(given_x_value, y_value));
    y_value += SQUARE_SIDE_LENGTH;
  }
  return this_line;
}

void Background::draw_line_on_square(Point square_corner)
{
  int first_x = square_corner.x;
  int second_x = square_corner.x + SQUARE_SIDE_LENGTH;
  int sides_y = square_corner.y + SQUARE_SIDE_LENGTH/2;
  window->draw_line(Point(first_x, sides_y), Point(second_x, sides_y), WHITE);
}

bool Background::is_tower_square_empty(int x_index, int y_index)
{
  if(towers_board[x_index][y_index])
    return false;
  return true;
}

bool Background::is_enemy_square_empty(int x_index, int y_index)
{
  if(enemies_board[x_index][y_index])
    return false;
  return true;
}

float Background::find_distance(Point one, Point two)
{
  return sqrt(pow(one.x-two.x, 2) + pow(one.y - two.y, 2));
}
