#include <string>
#include <vector>

std::vector<std::string> GetUnique(std::vector<std::string> lines) {
  std::vector<std::string> result;
  result.push_back(lines[0]);

  for (uint64_t i = 1; i < lines.size(); i++) {
    if (lines[i] != lines[i - 1]) {
      result.push_back(lines[i]);
    }
  }

  return result;
}
