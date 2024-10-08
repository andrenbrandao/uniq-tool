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

TEST(GetUnique, CountNumberOfTimesLineAppear) {
  std::istringstream input("line1\nline1\nline2\nline2\nline2\nline3\nline3");

  std::ostringstream output{};
  GetUnique(input, output, {.count = true});

  EXPECT_EQ(output.str(), "      2 line1\n      3 line2\n      2 line3\n");
}

TEST(GetUnique, OnlyPrintsRepeatedLines) {
  std::istringstream input("line1\nline2\nline2\nline3\nline3");

  std::ostringstream output{};
  GetUnique(input, output, {.repeated = true});

  EXPECT_EQ(output.str(), "line2\nline3\n");
}

TEST(GetUnique, ReturnsUniqueLinesOnly) {
  std::istringstream input("line1\nline2\nline2\nline3");

  std::ostringstream output{};
  GetUnique(input, output, {.unique = true});

  EXPECT_EQ(output.str(), "line1\nline3\n");
}

TEST(GetUnique, ReturnsRepeatedLinesOnlyWithCount) {
  std::istringstream input("line1\nline2\nline2\nline3");

  std::ostringstream output{};
  GetUnique(input, output, {.count = true, .repeated = true});

  EXPECT_EQ(output.str(), "      2 line2\n");
}
