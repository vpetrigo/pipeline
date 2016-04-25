#include "commands.hpp"
#include <sstream>

Command::Command(const std::string& cmd, const std::string& args)
    : cmd{cmd}, args{args} {}

Command::Command(const std::string& s) : cmd{s}, args{""} {
  if (cmd.empty()) {
    return;
  }

  std::istringstream iss{cmd};

  iss >> cmd;

  std::string arg;

  while (iss >> arg) {
    args += arg;
    iss >> std::ws;

    if (!iss.eof()) {
      args += " ";
    }
  }
}

std::vector<Command> parse_commands(const std::string& s) {
  std::vector<Command> cmds;
  // skip leading spaces
  std::size_t prev_pos = s.find_first_not_of(' ');
  std::size_t cur_pos = prev_pos;

  while (prev_pos != std::string::npos) {
    cur_pos = s.find('|', prev_pos);

    std::string full_cmd = s.substr(prev_pos, cur_pos - prev_pos);
    cmds.push_back(Command{full_cmd});
    prev_pos = (cur_pos != std::string::npos) ? cur_pos + 1 : std::string::npos;
  }

  return cmds;
}
