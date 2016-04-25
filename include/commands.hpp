#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <vector>

struct Command {
  Command(const std::string& cmd, const std::string& args);

  explicit Command(const std::string& s);

  std::string cmd;
  std::string args;
};

// parse input string for commands
// input must be a string with '|' delimiter
std::vector<Command> parse_commands(const std::string& s);

#endif  // COMMANDS_HPP
