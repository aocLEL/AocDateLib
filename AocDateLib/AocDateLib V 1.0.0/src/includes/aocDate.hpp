/*
AocDateLib, INCLUDE FILE

***************************************************************************************
this library was been developed from Notari Antonio (alias aocLeL) 14 years old.
Copyright 2022
All rights are reserved
***************************************************************************************
*/

#pragma once


#include <string>
#include <span>
#include <vector>
#include <ctime>
#include "./strptime/includes/strptime.hpp"


//HEART OF THE PROJECT
class Date {
  public:
  //CONSTRUCTORS
    explicit Date(unsigned int year, unsigned int month, unsigned int day, unsigned int hour = 0, unsigned int minutes = 0, unsigned int seconds = 0, const std::string& format = "%d/%m/%Y %H:%M:%S");
    explicit Date(const std::string& string_date, const std::string& format = "%d/%m/%Y %H:%M:%S");
    explicit Date(const char* string_date, const char* format = "%d/%m/%Y %H:%M:%S");
    explicit Date(const date& time_data);
    explicit Date(const std::time_t& ts);
    explicit Date();
  //UTILITIES
    friend void init_Date(Date& __date, const date& time_data);
    friend std::time_t calc_ts(const Date& date);
    static bool check_date_string(const std::string& string_date, const std::string& format = "%d/%m/%Y %H:%M:%S") {return (Date{string_date} != Date{1900, 1, 1, 0, 0, 0});}
  // GETTERS & SETTERS
    unsigned int get_month() const;
    unsigned int get_year() const;
    unsigned int get_day() const;
    unsigned int get_hour() const;
    unsigned int get_min() const;
    unsigned int get_sec() const;
    std::string get_string_date() const;
    std::string get_format() const;
    void set_month(unsigned int month);
    void set_year(unsigned int year);
    void set_day(unsigned int day);
    void set_hour(unsigned int hour);
    void set_min(unsigned int min);
    void set_sec(unsigned int sec);
    time_t get_ts() const; 
    void set_now();  
      
  //OPERATORS PROTOTYPES
    std::strong_ordering operator<=>(const Date& __date) const;
    std::strong_ordering operator<=>(const std::string& string_date) const;
    std::strong_ordering operator<=>(const char* string_date) const;
    bool operator==(const Date& __date) const;
    bool operator==(const std::string& string_date) const;
    bool operator==(const char* string_date) const;
    bool operator!=(const Date& __date) const;
    bool operator!=(const std::string& string_date) const;
    bool operator!=(const char* string_date) const;
    Date& operator+=(const unsigned long long time_value);
    Date& operator-=(const unsigned long long time_value);
    Date operator+(const unsigned long long time_value);
    friend Date operator+(const unsigned long long time_value, const Date& __date);
    Date operator-(const unsigned long long time_value);
    friend Date operator-(const unsigned long long time_value, const Date& __date);
  private:
    unsigned int m_month;
    unsigned int m_year;
    unsigned int m_day;
    unsigned int m_hour;
    unsigned int m_minutes;
    unsigned int m_seconds;  
    std::time_t m_ts;
    std::string m_format{"%d/%m/%Y %H:%M:%S"};
};

std::ostream& operator<<(std::ostream& stream, const Date& date);

//LITERALS
namespace date_literals {
  unsigned long long operator"" _y(unsigned long long years); 
  unsigned long long operator"" _m(unsigned long long months); 
  unsigned long long operator"" _d(unsigned long long days); 
  unsigned long long operator"" _h(unsigned long long hours); 
  unsigned long long operator"" _M(unsigned long long minutes); 
  unsigned long long operator"" _s(unsigned long long seconds); 
};

namespace date_array {
  const size_t npos{18446744073709551615};
  size_t get_min(const std::span<const Date>&& date_arr, const size_t s_index = 0);
  size_t get_max(const std::span<const Date>&& date_arr, const size_t s_index = 0);
  size_t find_date(const std::span<const Date>&& date_arr, const Date &date, const size_t s_index = 0);
  size_t find_date(const std::span<const Date>&& date_arr, const std::string& string_date, const size_t s_index = 0, const std::string format = "%d/%m/%Y %H:%M:%S");
  std::vector<Date> get_dates(const std::span<Date>&& date_arr, const size_t year, const size_t month = npos, const size_t day = npos, const size_t hour = npos, const size_t minute = npos, const size_t second = npos, const size_t s_index = 0);
}
