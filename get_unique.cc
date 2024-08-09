#include "get_unique.h"
#include "absl/strings/str_cat.h"

#include <cstdint>
#include <iostream>

namespace {

class Renderer {
public:
  Renderer(const Config &config) : config_(config){};

  void execute(const std::string &line, uint64_t count,
               std::ostream &output_stream) const {
    if (config_.count) {
      printLineNumber(count, output_stream);
    }
    output_stream << line << '\n';
  }

  static void printLineNumber(uint64_t line_number,
                              std::ostream &output_stream) {
    std::string line_number_str = absl::StrCat(line_number);

    for (uint64_t i = 0; i < NUM_PADDING_LEFT - line_number_str.length() + 1;
         i++) {
      output_stream << " ";
    }
    output_stream << line_number << " ";
  }

private:
  const Config &config_;
  static constexpr int NUM_PADDING_LEFT = 6;
};

void UniqueWithCount(std::istream &input_stream, std::ostream &output_stream,
                     const Renderer &renderer) {
  std::string str_read;
  std::string last_read;
  uint64_t count = 0;

  while (std::getline(input_stream, str_read)) {
    if (str_read == last_read || count == 0) {
      count++;
      last_read = str_read;
      continue;
    }

    renderer.execute(last_read, count, output_stream);

    count = 1;
    last_read = str_read;
  }

  renderer.execute(last_read, count, output_stream);
}

void OnlyRepeated(std::istream &input_stream, std::ostream &output_stream,
                  const Renderer &renderer) {
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
      renderer.execute(last_read, count, output_stream);
    }

    count = 1;
    last_read = str_read;
  }

  if (count > 1) {
    renderer.execute(last_read, count, output_stream);
  }
}

void OnlyUnique(std::istream &input_stream, std::ostream &output_stream,
                const Renderer &renderer) {
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
      count = 1;
      last_read = str_read;
      continue;
    }

    count = 1;

    renderer.execute(last_read, count, output_stream);
    last_read = str_read;
  }

  if (count == 1) {
    renderer.execute(last_read, count, output_stream);
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

  Renderer renderer = Renderer(config);

  if (config.repeated) {
    OnlyRepeated(input_stream, output_stream, renderer);
    return;
  }

  if (config.unique) {
    OnlyUnique(input_stream, output_stream, renderer);
    return;
  }

  if (config.count) {
    UniqueWithCount(input_stream, output_stream, renderer);
    return;
  }

  Unique(input_stream, output_stream);
}
