#include <ostream>

void HelloWorld(const std::string &name, std::ostream &ostream) {
  ostream << "Hello " << name << "!" << std::endl;
}
