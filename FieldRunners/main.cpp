#include "FieldRunners.hpp"
#include <iostream>
#include "string"

using namespace std;



int main(void)
{
  FieldRunners game;
  while(true)
  {
    game.draw_game();
    game.update_game();
  }

}
