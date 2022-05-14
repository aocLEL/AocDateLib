#include <iostream>
#include <string>
#include <cstring>
#include "strptime.hpp"
#include "../../sources/headers/errors.hpp"
#include <cstdlib>

#define DATE_STRING_LIMIT 30

date strptime(const char *string, const char *format) {
  char *c_string{new char[std::strlen(string) + 2]()};
  std::strcat(c_string, " ");
  std::strcat(c_string, string);
  char *c_format{new char[std::strlen(format) + 2]()};
  std::strcat(c_format, " ");
  std::strcat(c_format, format);
  date date_record{0, 0, 0, 0, 0, 0};
  try {
    const char *_iterator{c_string};
    const char *format_iterator{c_format};
    while (*_iterator != '\0') {
      if (*_iterator == ' ' || *_iterator == '/' || *_iterator == '-' || *_iterator == '.' || *_iterator == ':') {
        while (*format_iterator != ' ' && *format_iterator != '/' && *format_iterator != '-' && *format_iterator != '.' && *format_iterator != ':') format_iterator++;
        if(*format_iterator != *_iterator) throw date_errors::err_3;
        if (*(format_iterator + 1) == '%') {
          switch (std::string date_value; *(format_iterator + 2)) {
          case 'd':
          case 'm':
          case 'H':
          case 'M':
          case 'S':
            for (size_t i{1}; i <= 2; i++) {
              if (isdigit(*(_iterator + i)))
                date_value.push_back(*(_iterator + i));
            }
            if(date_value == "")
              date_value.push_back(0);
            switch(*(format_iterator + 2))  {
              case 'd':
                date_record.d_day = std::stoi(date_value);
                break;
              case 'm':
                date_record.d_mon = std::stoi(date_value);
                break;
              case 'H':
                date_record.d_hour = std::stoi(date_value);
                break;
              case 'M':
                date_record.d_min = std::stoi(date_value);
                break;
              case 'S':
                date_record.d_sec = std::stoi(date_value);
                break;
              default:
                break;
            }
            break;
          case 'Y':
            for (size_t i{1}; i <= 4; i++) {
              if (isdigit(*(_iterator + i)))
                date_value.push_back(*(_iterator + i));
            }
            if(date_value == "")
              date_value.push_back(0);
            date_record.d_year = std::stoi(date_value);
            break;
          default:
            break;
          }
        }
        _iterator++;
        format_iterator++;
      }
      _iterator++;
    }
  } catch(const std::exception& e) {
    std::cerr << date_errors::err_1 << string << std::endl;
  } catch(const std::string& s) {
    std::cerr << s << "DATE: " << string << " FORMAT: " << format << std::endl;
  }
  delete c_string;
  delete c_format;
  return date_record;
}

date strptime(const std::string &string, const std::string& format) {
  return strptime(string.c_str(), format.c_str());
}




