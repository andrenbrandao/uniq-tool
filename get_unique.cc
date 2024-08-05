#include "get_unique.h"
#include "absl/strings/str_cat.h"

#include <cstdint>
#include <iostream>

namespace {

constexpr int NUM_PADDING_LEFT = 6;

void PrintLineNumber(uint64_t line_number, std::ostream &output_stream) {
  std::string line_number_str = absl::StrCat(line_number);

  for (uint64_t i = 0; i < NUM_PADDING_LEFT - line_number_str.length() + 1;
       i++) {
    output_stream << " ";
  }
  output_stream << line_number << " ";
}

void UniqueWithCount(std::istream &input_stream, std::ostream &output_stream) {
  std::string str_read;
  std::string last_read;
  uint64_t count = 0;

  while (std::getline(input_stream, str_read)) {
    if (str_read == last_read || count == 0) {
      count++;
      last_read = str_read;
      continue;
    }

    PrintLineNumber(count, output_stream);
    output_stream << last_read << '\n';

    count = 1;
    last_read = str_read;
  }

  PrintLineNumber(count, output_stream);
  output_stream << last_read << '\n';
}

void UniqueOnlyRepeated(std::istream &input_stream,
                        std::ostream &output_stream) {
  std::string str_read;
  std::string last_read;
  uint64_t count = 0;

  while (std::getline(input_stream, str_read)) {
    if (str_read == last_read || count == 0) {
      count++;
      last_read = str_read;
      continue;
    }

    if (count > 1) {
      output_stream << last_read << '\n';
    }

    count = 1;
    last_read = str_read;
  }

  if (count > 1) {
    output_stream << last_read << '\n';
  }
}

void Unique(std::istream &input_stream, std::ostream &output_stream) {
  std::string str_read;
  std::string last_str;

  while (std::getline(input_stream, str_read)) {
    if (str_read != last_str) {
      output_stream << str_read << '\n';
    }

    last_str = str_read;
  }
}

} // namespace

void GetUnique(std::istream &input_stream, std::ostream &output_stream,
               Config config) {
  if (config.count) {
    UniqueWithCount(input_stream, output_stream);
    return;
  }

  if (config.repeated) {
    UniqueOnlyRepeated(input_stream, output_stream);
    return;
  }

  Unique(input_stream, output_stream);
}
