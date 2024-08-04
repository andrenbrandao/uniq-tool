#include "get_unique.h"
#include <iostream>

void GetUnique(std::istream &input_stream, std::ostream &output_stream) {
  std::string str_read;
  std::string last_str;

  while (std::getline(input_stream, str_read)) {
    if (str_read != last_str) {
      output_stream << str_read << "\n";
    }

    last_str = str_read;
  }
}
