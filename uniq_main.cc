#include "absl/flags/parse.h"
#include "get_unique.h"
#include <cstring>
#include <fstream>
#include <iostream>

void PrintUnique(std::istream &input_stream, std::ostream &output_stream) {
  std::vector<std::string> lines;
  std::string str_read{};

  while (std::getline(input_stream, str_read)) {
    lines.push_back(str_read);
  }

  for (const std::string &line : GetUnique(lines)) {
    output_stream << line << std::endl;
  }
}

int main(int argc, char **argv) {
  std::vector<char *> args = absl::ParseCommandLine(argc, argv);

  if (args.size() == 1 || strcmp(args[1], "-") == 0) {
    PrintUnique(std::cin, std::cout);
    return 0;
  }

  std::string filename = args[1];
  std::ifstream file{filename};
  if (!file) {
    std::cerr << "Could not open file " + filename << '\n';
    return 1;
  }

  PrintUnique(file, std::cout);
  return 0;
}
