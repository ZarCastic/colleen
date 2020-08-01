//
// Created by Tobias Fuchs on 01.08.20.
//

#include "arguments.h"
#include "colleen.h"
#include "gtest/gtest.h"

TEST(ColleenTest, EmptyColleen) {
Colleen colleen;
ASSERT_EQ(colleen.noArgs(), 0);
}

TEST(ColleenTest, OneArgument) {
Colleen colleen;
colleen.addArgument<std::string>("testArg", 1);
ASSERT_EQ(colleen.noArgs(), 1);

auto argument = colleen[0];
ASSERT_EQ(argument->argName(), "testArg");
ASSERT_EQ(argument->argumentType().first, 1);
ASSERT_EQ(argument->argumentType().second, true);

auto option = argument->option(0);
EXPECT_EQ(option, "--testArg");
}

TEST(ColleenTest, MultipleArguments) {
Colleen colleen;
colleen.addArgument<int>("testArg1", 1, {"--opt1", "--option1", "-o1"});
colleen.addArgument<std::string>("testArg2", 2, {"--opt2", "--option2", "-o2"});

EXPECT_EQ(colleen.noArgs(), 2);
int i = 1;
for(const auto &arg : colleen) {
auto arg_name = std::string("testArg") + std::to_string(i);
EXPECT_EQ(arg.argName(), arg_name);

auto arg_type = arg.argumentType();
EXPECT_EQ(arg_type.first, i);
EXPECT_EQ(arg_type.second, true);

auto option    = arg.option(0);
auto optString = std::string("--opt") + std::to_string(i);
EXPECT_EQ(option, optString);

option    = arg.option(1);
optString = std::string("--option") + std::to_string(i);
EXPECT_EQ(option, optString);

option    = arg.option(2);
optString = std::string("-o") + std::to_string(i);
EXPECT_EQ(option, optString);

++i;
}
}

TEST(ColleenTest, ParseSingle) {
Colleen colleen;
colleen.addArgument<std::string>("testArg", 1);

int   argc    = 2;
char *argv2[] = {"Colleen", "noFullfill"};
EXPECT_THROW(colleen.parse(argc, argv2), std::invalid_argument);

int   argc1   = 4;
char *argv1[] = {"Colleen", "--testArg", "test", "me"};
EXPECT_NO_THROW(colleen.parse(argc1, argv1));

auto colleen_arg = colleen.argument<std::string>(0);

EXPECT_EQ(colleen_arg[0], "test");
EXPECT_EQ(colleen_arg[1], "me");

testing::internal::CaptureStdout();
for(auto &x : colleen_arg.args()) {
std::cout << x << std::endl;
}
std::string output = testing::internal::GetCapturedStdout();
EXPECT_EQ(output, "test\nme\n");
}

TEST(ColleenTest, ParseMulti) {
Colleen colleen;
colleen.addArgument<std::string>("testArg1", 1);
colleen.addArgument<int>("testArg2", 2);
colleen.addArgument<std::string>("testArg3", 2);

int   argc    = 2;
char *argv2[] = {"Colleen", "noFullfill"};
EXPECT_THROW(colleen.parse(argc, argv2), std::invalid_argument);

int   argc1   = 9;
char *argv1[] = {"Colleen", "--testArg1", "test", "--testArg2", "1", "2",
                 "--testArg3", "Hello", "World"};
EXPECT_NO_THROW(colleen.parse(argc1, argv1));

auto colleen_arg1 = colleen.argument<std::string>(0);
testing::internal::CaptureStdout();
for(auto &x : colleen_arg1.args()) {
std::cout << x << std::endl;
}
std::string output = testing::internal::GetCapturedStdout();
EXPECT_EQ(output, "test\n");

auto colleen_arg2 = colleen.argument<int>(1);
testing::internal::CaptureStdout();
for(auto &x : colleen_arg2.args()) {
std::cout << x << std::endl;
}
output = testing::internal::GetCapturedStdout();
EXPECT_EQ(output, "1\n2\n");

auto colleen_arg3 = colleen.argument<std::string>(2);
testing::internal::CaptureStdout();
for(auto &x : colleen_arg3.args()) {
std::cout << x << std::endl;
}
output = testing::internal::GetCapturedStdout();
EXPECT_EQ(output, "Hello\nWorld\n");
}