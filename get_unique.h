#ifndef GET_UNIQUE_H
#define GET_UNIQUE_H

#include <iostream>

struct Config {
  bool count = false;
};

void GetUnique(std::istream &input_stream, std::ostream &output_stream,
               Config config = {});

#endif // !GET_UNIQUE_H
