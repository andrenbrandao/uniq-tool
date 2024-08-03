#include "get_unique.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(GetUnique, RemovesConsecutiveRepeatedStrings) {
  std::vector<std::string> input = {"line1", "line2", "line2", "line3"};

  std::vector<std::string> result = GetUnique(input);

  EXPECT_THAT(result, testing::ElementsAre("line1", "line2", "line3"));
}

TEST(GetUnique, DoesNotRemoveRepeatedNonAdjacent) {
  std::vector<std::string> input = {"line1", "line2", "line1", "line3"};

  std::vector<std::string> result = GetUnique(input);

  EXPECT_THAT(result, testing::ElementsAre("line1", "line2", "line1", "line3"));
}
