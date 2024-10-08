#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "get_unique.h"
#include <cstring>
#include <fstream>
#include <iostream>

ABSL_FLAG(bool, c, false, "prefix lines by the number of occurrences");
ABSL_FLAG(bool, d, false, "only print duplicate lines, one for each group");
ABSL_FLAG(bool, u, false, "only print unique lines");

int main(int argc, char **argv) {
  absl::SetProgramUsageMessage(
      "Filter adjacent matching lines from INPUT (or standard input), writing "
      "to OUTPUT (or standard output).\n\nSample usage: uniq input.txt");
  std::vector<char *> args = absl::ParseCommandLine(argc, argv);
  Config config = {.count = absl::GetFlag(FLAGS_c),
                   .repeated = absl::GetFlag(FLAGS_d),
                   .unique = absl::GetFlag(FLAGS_u)};

  if (args.size() == 1) {
    GetUnique(std::cin, std::cout, config);
    return 0;
  }

  std::istream *input = &std::cin;
  std::ostream *output = &std::cout;

  std::string input_filename = args[1];
  std::ifstream input_file;
  if (input_filename != "-") {
    input_file.open(input_filename);

    if (!input_file) {
      std::cerr << "Could not open file " << input_filename << '\n';
      return 1;
    }

    input = &input_file;
  }

  std::ofstream output_file;
  if (args.size() == 3) {
    std::string output_filename = args[2];
    output_file.open(output_filename);

    if (!output_file) {
      std::cerr << "Could not open file " << output_filename << '\n';
      return 1;
    }
    output = &output_file;
  }

  GetUnique(*input, *output, config);
  return 0;
}
