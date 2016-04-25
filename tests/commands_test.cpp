#include <gtest/gtest.h>
#include "commands.hpp"

TEST(Command_with_C_string, ideal_input) {
    const char *s = "ls -al";
    Command test{s};

    EXPECT_EQ(test.cmd, "ls");
    EXPECT_EQ(test.args, "-al");
}

TEST(Command_with_C_string, plain_command) {
    const char *s = "ls";
    Command test{s};

    EXPECT_EQ(test.cmd, "ls");
    EXPECT_EQ(test.args, "");
}

TEST(Command_with_C_string, plain_command_with_spaces_at_the_beginning) {
    const char *s = "   ls";
    Command test{s};

    EXPECT_EQ(test.cmd, "ls");
    EXPECT_EQ(test.args, "");
}

TEST(Command_with_C_string, plain_command_with_spaces_at_the_end) {
    const char *s = "ls      ";
    Command test{s};

    EXPECT_EQ(test.cmd, "ls");
    EXPECT_EQ(test.args, "");
}

TEST(Command_with_C_string, empty_string) {
    const char *s = "";
    Command test{s};

    EXPECT_EQ(test.cmd, "");
    EXPECT_EQ(test.args, "");
}

TEST(Command_with_C_string, several_args1) {
    const char *s = "ls -a -l";
    Command test{s};

    EXPECT_EQ(test.cmd, "ls");
    EXPECT_EQ(test.args, "-a -l");
}

TEST(Command_with_C_string, several_args2) {
    const char *s = "        ls        -a       -l         ";
    Command test{s};

    EXPECT_EQ(test.cmd, "ls");
    EXPECT_EQ(test.args, "-a -l");
}

TEST(Command_parser, ideal_input) {
    const char *s = "ls -al | grep test | wc";
    auto parsed_cmds = parse_commands(s);
    const std::vector<Command> ans{Command{"ls -al"}, Command{"grep test"}, Command{"wc"}};

    ASSERT_EQ(parsed_cmds.size(), ans.size());

    for (std::size_t i = 0; i < ans.size(); ++i) {
        EXPECT_EQ(ans[i].cmd, parsed_cmds[i].cmd);
        EXPECT_EQ(ans[i].args, parsed_cmds[i].args);
    }
}

TEST(Command_parser, no_space_input) {
    const char *s = "ls -al|grep test|wc";
    auto parsed_cmds = parse_commands(s);
    const std::vector<Command> ans{Command{"ls -al"}, Command{"grep test"}, Command{"wc"}};

    ASSERT_EQ(parsed_cmds.size(), ans.size());

    for (std::size_t i = 0; i < ans.size(); ++i) {
        EXPECT_EQ(ans[i].cmd, parsed_cmds[i].cmd);
        EXPECT_EQ(ans[i].args, parsed_cmds[i].args);
    }
}

TEST(Command_parser, one_command) {
    const char *s = "ls";
    auto parsed_cmds = parse_commands(s);
    const std::vector<Command> ans{Command{"ls"}};

    ASSERT_EQ(parsed_cmds.size(), ans.size());

    for (std::size_t i = 0; i < ans.size(); ++i) {
        EXPECT_EQ(ans[i].cmd, parsed_cmds[i].cmd);
        EXPECT_EQ(ans[i].args, parsed_cmds[i].args);
    }
}

TEST(Command_parser, zero_length_input) {
    const char *s = "";
    auto parsed_cmds = parse_commands(s);
    const std::vector<Command> ans;

    ASSERT_EQ(parsed_cmds.size(), ans.size());
}

TEST(Command_parser, input_with_lots_of_spaces) {
    const char *s = "ls           | echo |  wc            ";
    auto parsed_cmds = parse_commands(s);
    const std::vector<Command> ans{Command{"ls"}, Command{"echo"}, Command{"wc"}};

    ASSERT_EQ(parsed_cmds.size(), ans.size());

    for (std::size_t i = 0; i < ans.size(); ++i) {
        EXPECT_EQ(ans[i].cmd, parsed_cmds[i].cmd);
        EXPECT_EQ(ans[i].args, parsed_cmds[i].args);
    }
}

TEST(Command_parser, only_spaces_input) {
    const char *s = "          ";
    auto parsed_cmds = parse_commands(s);
    const std::vector<Command> ans;

    ASSERT_EQ(parsed_cmds.size(), ans.size());
}
