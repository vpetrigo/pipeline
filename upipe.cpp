#include <iostream>
#include <iterator>
#include <array>
#include <algorithm>
#include <cstring>
#include <cerrno>
#include <system_error>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "commands.hpp"

std::array<int, 2> open_pipe() {
  constexpr int PIPE_FD = 2;
  std::array<int, 2> pipe_fd;

  if (pipe(pipe_fd.data()) != 0) {
    throw std::system_error{std::error_code(errno, std::generic_category())};
  }

  return pipe_fd;
}

int call_command(const Command& cmd) {
  return (cmd.args.empty()) ? execlp(cmd.cmd.c_str(), cmd.cmd.c_str(), nullptr)
                            : execlp(cmd.cmd.c_str(), cmd.cmd.c_str(),
                                     cmd.args.c_str(), nullptr);
}

void spawn_proc(const Command& cmd, int& in_fd) {
  constexpr unsigned PIPE_READ = 0;
  constexpr unsigned PIPE_WRITE = 1;
  try {
    const auto pipe = open_pipe();
    pid_t ch_pid = fork();

    if (ch_pid == -1) {
      // handle fork error
    } 
    else if (ch_pid == 0) {
      // child code
      close(pipe[PIPE_READ]);
      dup2(in_fd, STDIN_FILENO);
      dup2(pipe[PIPE_WRITE], STDOUT_FILENO);

      int retval = call_command(cmd);

      if (retval) {
        throw std::system_error{
            std::error_code(errno, std::generic_category())};
      }
    } 
    else {
      in_fd = pipe[PIPE_READ];
      close(pipe[PIPE_WRITE]);
      wait(nullptr);
    }
  } 
  catch (const std::system_error& se) {
    std::cerr << "ERROR " << se.code() << ": " << se.what() << std::endl;
    throw;
  }
}

void process_commands(const std::vector<Command>& cmds) {
  int in_fd;
  auto last_command = cmds.back();

  for (auto it = cmds.cbegin(); it != cmds.cend() - 1; ++it) {
    spawn_proc(*it, in_fd);
  }
  // get data from the last pipe's out
  dup2(in_fd, STDIN_FILENO);

  int retval = call_command(last_command);

  if (retval) {
    throw std::system_error{std::error_code(errno, std::generic_category())};
  }
}

int main() {
  std::string cmds_line;

  std::getline(std::cin, cmds_line);

  auto cmds = parse_commands(cmds_line);
  
  try {
      process_commands(cmds);
  }
  catch (const std::system_error& se) {
    std::cerr << "ERROR: " << se.code() << ": " << se.what() << std::endl;
    return 1;
  }

  return 0;
}
