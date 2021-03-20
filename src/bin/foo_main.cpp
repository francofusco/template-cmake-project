/** @file foo_main.cpp
  * @brief Executable using the foo::bar(int) function.
  */
#include <foo/foo.hpp>
#include <iostream>

/** Entrypoint for the `foo_main` executable */
int main(int argc, char** argv) {
  if(argc != 2) {
    std::cout << "Usage: " << argv[0] << " NUMBER" << std::endl;
    return 0;
  }
  int value = std::stoi(argv[1]);
  std::cout << "foo::bar(" << value << ") = " << foo::bar(value) << std::endl;
  return 0;
}
