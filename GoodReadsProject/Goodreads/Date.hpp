#ifndef DATE_HPP
#define DATE_HPP
#include <string>

class Date
{
public:
  Date(std::string m, std::string d, std::string y) { set_date(m, d, y); }
  std::string get_month(){ return month;}
  std::string get_day(){ return day;}
  std::string get_year(){ return year;}
  void set_date(std::string m, std::string d, std::string y);
private:
  std::string month, day, year;
};
#endif
