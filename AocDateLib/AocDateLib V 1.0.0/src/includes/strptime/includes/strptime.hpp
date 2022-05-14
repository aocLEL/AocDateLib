#pragma once

//MY OWN strptime() FUNCTION

typedef struct {
  unsigned int d_sec;  /* Seconds (0-60) */
  unsigned int d_min;  /* Minutes (0-59) */
  unsigned int d_hour; /* Hours (0-23) */
  unsigned int d_day; /* Day of the month (1-31) */
  unsigned int d_mon;  /* Month (0-11) */
  unsigned int d_year; /* Year - 1900 */
} date;


date strptime(const char *string, const char *format = "%d/%m/%Y %H:%M:%S");
date strptime(const std::string &string, const std::string& format = "%d/%m/%Y %H:%M:%S");