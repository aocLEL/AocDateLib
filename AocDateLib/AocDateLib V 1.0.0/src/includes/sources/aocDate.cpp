#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <span>
#include <vector>
#include <ctime>
#include "../aocDate.hpp"
#include "../strptime/includes/strptime.hpp"
#include "./headers/helpers.hpp"
#include "./headers/errors.hpp"

#define MAX_FORMAT_LENGTH 80
#define SECS_IN_DAY 86400

using u_int = unsigned int;
using u_short = unsigned short;


bool is_winter_time(const std::time_t& ts, unsigned int year) {
  u_int march_day{}, october_day{};
  for(size_t i{24}; i <= 31; i++) {
    if(get_day_week(year, 3, i) == 0) {
      march_day = i;
      break;
    }
  }
  for(size_t i{24}; i <= 31; i++) {
    if(get_day_week(year, 10, i) == 0) {
      october_day = i;
      break;
    }
  }
  std::time_t ts_limit1{Date{year, 3, march_day}.get_ts() + static_cast<std::time_t>(std::pow(60, 2))}, ts_limit2{Date{year, 10, october_day}.get_ts() + static_cast<std::time_t>(std::pow(60, 2))};
  if(ts <= ts_limit1 || ts > ts_limit2) return true;
  return false;
  
}

bool is_winter_time(unsigned int year, unsigned int month, unsigned int day) {
  u_int march_day{}, october_day{};
  for(size_t i{24}; i <= 31; i++) {
    if(get_day_week(year, 3, i) == 0) {
      march_day = i;
      break;
    }
  }
  for(size_t i{24}; i <= 31; i++) {
    if(get_day_week(year, 10, i) == 0) {
      october_day = i;
      break;
    }
  }
  return (month < 3 || month > 10) || ((month == 3 && day <= march_day) || (month == 10 && day > october_day));
}

std::time_t negts(u_int y, u_int m, u_int d) {
    y -= m <= 2;
    const std::time_t era = (y >= 0 ? y : y-399) / 400;
    const u_int yoe = static_cast<u_int>(y - era * 400);      
    const u_int doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d-1;  
    const u_int doe = yoe * 365 + yoe/4 - yoe/100 + doy;         
    return era * 146097 + static_cast<std::time_t>(doe) - 719468;
}

std::shared_ptr<struct std::tm> init_tm(const Date& date) {
  auto time_data {std::make_shared<struct std::tm>()};
  time_data->tm_year = date.get_year() - 1900;
  time_data->tm_mon = date.get_month() - 1;
  time_data->tm_mday = date.get_day();
  time_data->tm_hour = date.get_hour();
  time_data->tm_min = date.get_min();
  time_data->tm_sec = date.get_sec();
  time_data->tm_isdst = 1;
  return time_data;
}


std::shared_ptr<date> init_date(const std::time_t& ts) {
  struct std::tm* time_data {std::localtime(&ts)};
  std::shared_ptr<date> date_data{new date};
  date_data->d_year = time_data->tm_year + 1900;
  date_data->d_mon = time_data->tm_mon + 1;
  date_data->d_day = time_data->tm_mday;
  date_data->d_hour = time_data->tm_hour;
  date_data->d_min = time_data->tm_min;
  date_data->d_sec = time_data->tm_sec;
  return date_data;
}


void init_Date(Date& __date, const date& time_data) {
    __date.m_year = time_data.d_year;
    __date.m_month = time_data.d_mon;
    __date.m_day = time_data.d_day;
    __date.m_hour = time_data.d_hour;
    __date.m_minutes = time_data.d_min;
    __date.m_seconds = time_data.d_sec;
    __date.m_ts = calc_ts(__date);
}



void Date::set_now() {
  date now_date{date_now()};
  m_day = now_date.d_day;
  m_month = now_date.d_mon;
  m_year = now_date.d_year;
  m_hour = now_date.d_hour;
  m_minutes = now_date.d_min;
  m_seconds = now_date.d_sec;
  m_ts = calc_ts(*this);
}

Date::Date(u_int year, u_int month, u_int day, u_int hour, u_int minutes, u_int seconds, const std::string& format) {
  date time_data{seconds, minutes, hour, day, month, year};
  if(check_date(time_data)) {
    init_Date(*this, time_data);
    m_format = format;
  }
  else {
    make_error(*this);
  }
}

Date::Date(const std::string& string_date, const std::string& format) {
  date parsed_date{strptime(string_date, format)};
  if(check_date(parsed_date)) {
    init_Date(*this, parsed_date);
    m_format = format;
  }
  else {
    make_error(*this);
  }
}

Date::Date(const char* string_date, const char* format) {
  date parsed_date{strptime(string_date, format)};
  if(check_date(parsed_date)) {
    init_Date(*this, parsed_date);
    m_format = std::string{format};
  }
  else {
    make_error(*this);
  }
}

Date::Date(const date& time_data) {
  if(check_date(time_data)) {
    init_Date(*this, time_data);
  }
  else {
    make_error(*this);
  }
}

Date::Date(const std::time_t& ts) {
  if(ts > TS_MAX || ts < OP_TS_MIN) {
    make_error(*this);
    return;
  }
  std::shared_ptr<date> time_data{init_date(ts)};
  if(check_date(*time_data)) {
    std::cout << "INITZIALIZING DATE" << std::endl;
    init_Date(*this, *time_data);
  }
  else {
    make_error(*this);
  }
}

Date::Date() {
  this->set_now();
}


u_int Date::get_day() const {
  return m_day;
}
u_int Date::get_month() const {
  return m_month;
}
u_int Date::get_year() const {
  return m_year;
}
u_int Date::get_hour() const {
  return m_hour;
}
u_int Date::get_min() const {
  return m_minutes;
}
u_int Date::get_sec() const {
  return m_seconds;
}

std::string Date::get_string_date() const {
  char buffer[MAX_FORMAT_LENGTH];
  std::shared_ptr<struct std::tm> time_info{init_tm(*this)};
  std::strftime(buffer, MAX_FORMAT_LENGTH, m_format.c_str(), time_info.get());
  return std::string{buffer};
}

std::string Date::get_format() const {
  return m_format;
}


void Date::set_sec(u_int sec) {
  try {
    if(check_date(date{sec, m_minutes, m_hour, m_day, m_month, m_year})) {
      m_seconds = sec;
      m_ts = calc_ts(*this);
    } else {
      throw date_errors::err_2;
    }
  } catch(const std::string& s) {
    std::cerr << s << sec << std::endl;
  }
}

void Date::set_min(u_int min) {
  try {
    if(check_date(date{m_seconds, min, m_hour, m_day, m_month, m_year})) {
      m_minutes = min;
      m_ts = calc_ts(*this);
    } else {
      throw date_errors::err_2;
    }
  } catch(const std::string& s) {
    std::cerr << s << min << std::endl;
  }
}

void Date::set_hour(u_int hour) {
  try {
    if(check_date(date{m_seconds, m_minutes, hour, m_day, m_month, m_year})) {
      m_hour = hour;
      m_ts = calc_ts(*this);
    } else {
      throw date_errors::err_2;
    } 
  } catch(const std::string& s) {
    std::cerr << s << hour << std::endl;
  }
}

void Date::set_day(u_int day) {
  try {
    if(check_date(date{m_seconds, m_minutes, m_hour, day, m_month, m_year})) {
      m_day = day;
      m_ts = calc_ts(*this);
    } else {
      throw date_errors::err_2;
    }
  } catch(const std::string& s) {
    std::cerr << s << day << std::endl;
  }
}

void Date::set_month(u_int month) {
  try {
    if(check_date(date{m_seconds, m_minutes, m_hour, m_day, month, m_year})) {
      m_month = month;
      m_ts = calc_ts(*this);
    } else {
      throw date_errors::err_2;
    }
  } catch(const std::string& s) {
    std::cerr << s << month << std::endl;
  }
}

void Date::set_year(u_int year) {
  try {
    if(check_date(date{m_seconds, m_minutes, m_hour, m_day, m_month, year})) {
      m_year = year;
      m_ts = calc_ts(*this);
    } else {
      throw date_errors::err_2;
    }
  } catch(const std::string& s) {
    std::cerr << s << year << std::endl;
  }
}




std::time_t calc_ts(const Date& date) {
  
  if(date.m_year < 1970) {
    std::time_t c_secs{negts(date.m_year, date.m_month, date.m_day) * 24 * static_cast<std::time_t>(std::pow(60, 2))};
    c_secs -= std::pow(60, 2);
    c_secs += date.m_seconds;
    c_secs += date.m_hour * std::pow(60, 2);
    c_secs += date.m_minutes * 60;
    return c_secs;
  }
  std::shared_ptr<struct std::tm> time_info{init_tm(date)};
  
  
  std::time_t c_secs{mktime(time_info.get())};
  if(is_winter_time(date.m_year, date.m_month, date.m_day)) c_secs += std::pow(60, 2);
  return c_secs;
}

std::time_t Date::get_ts() const {
  return m_ts;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------

/*DATE_ARRAY FUNCTIONS*/

size_t date_array::get_min(const std::span<const Date>&& date_arr, const size_t s_index) {
  std::time_t curr_ts{TS_MAX + 1};
  size_t index{};
  for(size_t i{s_index}; i < std::size(date_arr); i++) {
    if(date_arr[i].get_ts() < curr_ts) {
      curr_ts = date_arr[i].get_ts();
      index = i;
    }
  }
  return index;
}

size_t date_array::get_max(const std::span<const Date>&& date_arr, const size_t s_index) {
  std::time_t curr_ts{TS_MIN - 1};
  size_t index{};
  for(size_t i{s_index}; i < std::size(date_arr); i++) {
    if(date_arr[i].get_ts() > curr_ts) {
      curr_ts = date_arr[i].get_ts();
      index = i;
    }
  }
  return index;
}

size_t date_array::find_date(const std::span<const Date>&& date_arr, const Date &date, const size_t s_index) {
  for(size_t i{s_index}; i < std::size(date_arr); i++) 
    if(date_arr[i] == date) return i;
  return date_array::npos;
}

size_t date_array::find_date(const std::span<const Date>&& date_arr, const std::string& string_date, const size_t s_index, const std::string format) {
  Date parsed_date{string_date};
  for(size_t i{s_index}; i < std::size(date_arr); i++) 
    if(date_arr[i] == parsed_date) return i;
  return date_array::npos;
}

std::vector<Date> date_array::get_dates(const std::span<Date>&& date_arr, const size_t year, const size_t month, const size_t day, const size_t hour, const size_t minute, const size_t second, const size_t s_index){
  std::vector<Date> selected_dates;
  for(size_t i{s_index}; i < std::size(date_arr); i++) {
    if(
      date_arr[i].get_year() != year || (month != date_array::npos && date_arr[i].get_month() != month) ||
  (day != date_array::npos && date_arr[i].get_day() != day) || (hour != date_array::npos && date_arr[i].get_hour() != hour)
  || (minute != date_array::npos && date_arr[i].get_min() != minute) || (second != date_array::npos && date_arr[i].get_sec() != second)
    ) continue;
    selected_dates.push_back(date_arr[i]);
  }
  return selected_dates;
}







