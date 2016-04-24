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

std::vector<Command> parse_cmds(std::string&& s) {
    std::vector<Command> cmds;
    std::size_t prev_pos = 0;
    std::size_t cur_pos = 0;

    while (prev_pos != s.size()) {
        cur_pos = s.find('|', prev_pos);
        
        std::string full_cmd = s.substr(prev_pos, cur_pos - prev_pos);
        cmds.push_back(make_command(full_cmd));
        prev_pos = cur_pos == std::string::npos ? s.size() : cur_pos + 1; 
    }
    
    return cmds;
}

int main() {
  std::array<int, 2> pipe_fd;
  std::string cmds_line;

  std::getline(std::cin, cmds_line);
  auto cmds = parse_cmds(std::move(cmds_line));
  
  for (const auto& c : cmds) {
    std::cout << "cmd: " << c.cmd << std::endl;
    std::cout << "args: " << c.args << std::endl;
  }
/*  try {
    open_pipe(pipe_fd);
  }
  catch (const std::system_error& e) {
    std::cerr << e.code() << ": " << e.what() << std::endl;
    return 1;
  }

  if (fork() == 0) {
    close(STDOUT_FILENO);
    close(pipe_fd.front());
    dup2(pipe_fd.back(), STDOUT_FILENO);
    execlp(cmds.front().c_str(), cmds.front().c_str(), nullptr);
  }
  else {
    close(STDIN_FILENO);
    close(pipe_fd.back());
    dup2(pipe_fd.front(), STDIN_FILENO);
    execlp(cmds.back().c_str(), cmds.back().c_str(), nullptr);
  } */

  return 0;
}
