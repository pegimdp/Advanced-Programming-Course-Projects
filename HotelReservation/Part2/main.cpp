#include "Utrip.hpp"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  Utrip utrip;
  utrip.read_hotels(argv[ONE]);
  utrip.read_average_ratings(argv[TWO]);
  std::string input_line;
  while(getline(cin,input_line))
  {
    try
    {
      utrip.identify_input(input_line);
      utrip.apply_hotels_default_price_filter_if_possible();
    }
    catch(std::exception& ex)
    {
      std::cout << ex.what();
    }

  }
}
