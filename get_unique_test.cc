#include "get_unique.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(GetUnique, RemovesConsecutiveRepeatedStrings) {
  std::istringstream input("line1\nline2\nline2\nline3");

  std::ostringstream output{};
  GetUnique(input, output);

  EXPECT_EQ(output.str(), "line1\nline2\nline3\n");
}

TEST(GetUnique, DoesNotRemoveRepeatedNonAdjacent) {
  std::istringstream input("line1\nline2\nline1\nline3");

  std::ostringstream output{};
  GetUnique(input, output);

  EXPECT_EQ(output.str(), "line1\nline2\nline1\nline3\n");
}
