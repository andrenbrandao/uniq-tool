#include "absl/flags/parse.h"
#include "get_unique.h"
#include <cstring>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  std::vector<char *> args = absl::ParseCommandLine(argc, argv);

  if (args.size() == 1 || strcmp(args[1], "-") == 0) {
    GetUnique(std::cin, std::cout);
    return 0;
  }

  std::string filename = args[1];
  std::ifstream file{filename};
  if (!file) {
    std::cerr << "Could not open file " + filename << '\n';
    return 1;
  }

  GetUnique(file, std::cout);
  return 0;
}
