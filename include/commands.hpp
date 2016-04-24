#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <cstring>
#include <algorithm>

struct Command {
    Command() {}

    Command(const std::string& cmd, const std::string& args) : cmd{cmd}, args{args} {} 
    
    explicit Command(const char *s) {
        auto input_string_size = std::strlen(s);
        // check whether size > 0
        auto space_pos = std::distance(s, std::find(s, s + input_string_size, ' '));

        cmd = std::string(s, space_pos);
        args = std::string(s + (space_pos + 1));
    }

    std::string cmd;
    std::string args;
};

Command make_command(const std::string& inp);

#endif // COMMANDS_HPP
