#include "Runner.hpp"

Runner::Runner(Window* w, Background* b, int square_x_index, int square_y_index)
{
  window = w;
  background = b;
  health = RUNNER_INITIAL_HEALTH_UNITS;
  velocity = RUNNER_SPEED;
  position = background->return_top_left_corner(square_x_index, square_y_index);
  x_velocity = y_velocity = RUNNER_SPEED;
}

void Runner::appear(void)
{
  window->draw_img(RUNNER_FILE_PATH, Rectangle(position, SQUARE_SIDE_LENGTH, SQUARE_SIDE_LENGTH));
}
