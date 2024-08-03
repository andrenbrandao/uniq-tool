#include "hello_world.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(HelloWorld, PrintsHelloWorld) {
  std::ostringstream output_stream;

  HelloWorld("World", output_stream);

  EXPECT_EQ(output_stream.str(), "Hello World!\n");
}
