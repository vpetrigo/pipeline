#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cstring>
#include <cerrno>
#include <system_error>
#include <unistd.h>

#include "commands.hpp"

void open_pipe(std::array<int, 2>& fd) {
    if (pipe(fd.data()) != 0) {
        throw std::system_error{std::error_code(errno, std::generic_category())};
    }
}

int main() {
  std::array<int, 2> pipe_fd;
  std::string cmds_line;

  std::getline(std::cin, cmds_line);
  auto cmds = parse_commands(cmds_line);
  
  for (const auto& c : cmds) {
    std::cout << "cmd: " << c.cmd << std::endl;
    std::cout << "args: " << c.args << std::endl;
  }

  return 0;
}
