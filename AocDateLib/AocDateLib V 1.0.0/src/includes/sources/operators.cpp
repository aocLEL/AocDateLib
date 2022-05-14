#include <iostream>
#include <string>
#include <cmath>
#include <compare>
#include "../aocDate.hpp"
#include "../strptime/includes/strptime.hpp"
#include "./headers/helpers.hpp"

#define YEAR 365
#define MONTH 30

using u_64 = unsigned long long;

//COMPARISON OPERATORS

std::strong_ordering Date::operator<=>(const Date& __date) const {
  return get_ts() <=> __date.get_ts();
}

std::strong_ordering Date::operator<=>(const std::string& string_date) const {
  return get_ts() <=> Date{string_date, this->m_format}.get_ts();
}

std::strong_ordering Date::operator<=>(const char* string_date) const {
  return get_ts() <=> Date{string_date, this->m_format.c_str()}.get_ts();
}

bool Date::operator==(const Date& __date) const {
  return get_ts() == __date.get_ts();
}

bool Date::operator==(const std::string& string_date) const {
  return get_ts() == Date{string_date, this->m_format}.get_ts();
}

bool Date::operator==(const char* string_date) const {
  return get_ts() == Date{string_date, this->m_format.c_str()}.get_ts();
}

bool Date::operator!=(const Date& __date) const {
  return get_ts() != __date.get_ts();
}

bool Date::operator!=(const std::string& string_date) const {
  return get_ts() != Date{string_date, this->m_format}.get_ts();
}

bool Date::operator!=(const char* string_date) const {
  return get_ts() != Date{string_date, this->m_format.c_str()}.get_ts();
}

//LITERALS

u_64 date_literals::operator"" _y(const u_64 years) {
  return ((YEAR * years) * 24) * std::pow(60, 2);
}

u_64 date_literals::operator"" _m(const u_64 months) {
  return ((MONTH * months) * 24) * std::pow(60, 2);
}

u_64 date_literals::operator"" _d(const u_64 days) {
  return (days * 24) * std::pow(60, 2);
}

u_64 date_literals::operator"" _h(const u_64 hours) {
  return hours * std::pow(60, 2);
}

u_64 date_literals::operator"" _M(const u_64 minutes) {
  return minutes * 60;
}

u_64 date_literals::operator"" _s(const u_64 seconds) {
  return seconds; 
}


//ARITHMETIC OPERATORS

Date& Date::operator+=(const u_64 time_value) {
  std::time_t new_ts{this->get_ts() + static_cast<std::time_t>(time_value)};
  *this = Date{new_ts};
  return *this;
}
Date& Date::operator-=(const u_64 time_value) {
  std::time_t new_ts{this->get_ts() - static_cast<std::time_t>(time_value)};
  *this = Date{new_ts};
  return *this;
}
Date Date::operator+(const u_64 time_value) {
  std::time_t new_ts{this->get_ts() + static_cast<std::time_t>(time_value)};
  Date new_date{new_ts};
  return new_date;
}
Date operator+(const u_64 time_value, const Date& __date) {
  std::time_t new_ts{__date.m_ts - static_cast<std::time_t>(time_value)};
  Date new_date{new_ts};
  return new_date;
}
Date Date::operator-(const u_64 time_value) {
  std::time_t new_ts{this->get_ts() - static_cast<std::time_t>(time_value)};
  Date new_date{new_ts};
  return new_date;
}
Date operator-(const u_64 time_value, const Date& __date) {
  std::time_t new_ts{__date.m_ts - static_cast<std::time_t>(time_value)};
  Date new_date{new_ts};
  return new_date;
}


//<< OPERATOR

std::ostream& operator<<(std::ostream& stream, const Date& date) {
  stream << date.get_string_date();
  return stream;
}
