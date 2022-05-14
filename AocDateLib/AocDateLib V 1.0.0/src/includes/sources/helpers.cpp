
#include <iostream>
#include <ctime>
#include <string>
#include <cmath>
#include "../strptime/includes/strptime.hpp"
#include "./headers/helpers.hpp"
#include "../aocDate.hpp"

using u_int = unsigned int;


//SOME USEFUL HELPERS

bool is_bissextile(unsigned int year) {
  if((year % 4 == 0 || (year % 400 == 0 && year % 100 == 0))) return true;
  return false;
}

bool check_date(const date& date_record) {
  if(date_record.d_mon > 12 || date_record.d_mon < 1) return false;
  if(date_record.d_year > MAX_YEAR || date_record.d_year < MIN_YEAR) return false;
  if(is_bissextile(date_record.d_year) && date_record.d_mon == 2) {
    if(date_record.d_day > 29 || date_record.d_day < 1) return false;
  }
  else if(date_record.d_mon == 2 && (date_record.d_day > 28 || date_record.d_day < 1)) return false;
  else if((date_record.d_mon == 11 || date_record.d_mon == 4 || date_record.d_mon == 6 || date_record.d_mon == 9) && 
          date_record.d_day > 30 || date_record.d_day < 1
          ) return false;
  else if(date_record.d_day > 31 || date_record.d_day < 1) return false;
  if(date_record.d_hour > 24 || date_record.d_min > 60 || date_record.d_sec > 60) return false;
 
  return true;
}

unsigned int get_day_week(u_int y, int m, u_int d) {
  m -= 2;
  if(m == -1) m = 11;
  else if(m == 0) m = 12;
  if(m > 12 || m < -1) return -1;
  std::string string_year{std::to_string(y)};
  int century{std::stoi(string_year.substr(0, 2))}, year{std::stoi(string_year.substr(2, 2))};
  if(m == 11 || m == 12) year--;
  unsigned long dn = (d + std::floor(2.6 * m - 0.2) - 2 * century + year + std::floor(year / 4) + std::floor(century / 4));
  return dn % 7;
}

date date_now() {
  std::time_t t = std::time(0);
  std::tm* now = std::localtime(&t);
  return date{
    static_cast<unsigned int>(now->tm_sec), 
    static_cast<unsigned int>(now->tm_min), 
    static_cast<unsigned int>(now->tm_hour), 
    static_cast<unsigned int>(now->tm_mday), 
    static_cast<unsigned int>(now->tm_mon + 1), 
    static_cast<unsigned int>(now->tm_year + 1900)
  };
}

void make_error(Date& error_date) {
  error_date = Date{DATE_ERROR};
}














































































