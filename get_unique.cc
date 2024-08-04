#include "get_unique.h"
#include <iostream>

void GetUnique(std::istream &input_stream, std::ostream &output_stream,
               Config config) {
  std::string str_read;
  std::string last_read;
  uint64_t count = 0;

  while (std::getline(input_stream, str_read)) {
    if (str_read == last_read || count == 0) {
      count++;
      last_read = str_read;
      continue;
    }

    if (config.count) {
      output_stream << count << " ";
    }

    output_stream << last_read << '\n';

    count = 1;
    last_read = str_read;
  }

  if (config.count) {
    output_stream << count << " ";
  }

  output_stream << last_read << '\n';
}
