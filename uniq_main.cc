#include "absl/flags/parse.h"
#include "get_unique.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  std::vector<char *> args = absl::ParseCommandLine(argc, argv);
  std::string filename = args[1];

  std::ifstream file{filename};
  if (!file) {
    std::cerr << "Could not open file " + filename << '\n';
    return 1;
  }

  std::vector<std::string> lines;
  std::string str_read{};
  while (std::getline(file, str_read)) {
    lines.push_back(str_read);
  }

  for (const std::string &line : GetUnique(lines)) {
    std::cout << line << std::endl;
  }

  return 0;
}
