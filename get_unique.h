#ifndef GET_UNIQUE_H
#define GET_UNIQUE_H

#include <iostream>

struct Config {
  bool count = false;
  bool repeated = false;
  bool unique = false;
};

void GetUnique(std::istream &input_stream, std::ostream &output_stream,
               const Config &config = {});

#endif // !GET_UNIQUE_H
