#include "commands.hpp"

constexpr char SPACE_DELIM = ' ';

inline std::size_t skip_whitespaces(const std::string& s, std::size_t pos = 0) {
   return s.find_first_not_of(SPACE_DELIM, pos); 
}

Command make_command(const std::string& inp) {
    // skip whitespaces if exsist
    auto non_ws_pos = skip_whitespaces(inp);
    auto cmd_end_pos = inp.find(SPACE_DELIM, non_ws_pos);
    auto cmd_size = cmd_end_pos - non_ws_pos;
    Command new_cmd;

    new_cmd.cmd = inp.substr(non_ws_pos, cmd_size);

    auto args_start_pos = skip_whitespaces(inp, cmd_size); 
    
    new_cmd.args = inp.substr(args_start_pos);

    return new_cmd;
}


