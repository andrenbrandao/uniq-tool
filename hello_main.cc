#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "hello_world.h"
#include <iostream>

ABSL_FLAG(std::string, name, "World", "name to say hello to");

int main(int argc, char **argv) {
  absl::ParseCommandLine(argc, argv);
  HelloWorld(absl::GetFlag(FLAGS_name), std::cout);
  return 0;
}
