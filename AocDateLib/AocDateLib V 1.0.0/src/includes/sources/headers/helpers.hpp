#pragma once



#include "../../aocDate.hpp"


#define MIN_YEAR 1900
#define TS_MIN -2208988800
#define OP_TS_MIN 0
#ifdef _WIN32 && sizeof(unsigned long long) == 8
  #define MAX_YEAR 2999
  #define TS_MAX 32503676399
#else
  #define MAX_YEAR 2037
  #define TS_MAX 2145913199
#endif
#define DATE_ERROR "01/01/1900"

bool check_date(const date& date_record);
date date_now();
bool is_bissextile(unsigned int year);
unsigned int get_day_week(unsigned int y, int m, unsigned int d);
void make_error(Date& error_date);





