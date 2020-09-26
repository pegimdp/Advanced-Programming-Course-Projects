#include "Utrip.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  Utrip utrip;
  utrip.read_hotels(argv[1]);
  std::string input_line;
  while(getline(cin, input_line))
  {
    try
    {
      utrip.identify_input(input_line);
    }
    catch(std::exception& ex)
    {
      std::cout << ex.what();
    }
  }
}
