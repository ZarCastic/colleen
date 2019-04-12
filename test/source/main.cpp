#include "colleen.h"
#include <gtest/gtest.h>
#include <stdexcept>

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
    // colleen.addArgument<int>("testArg1", 1, {"--opt1", "--option1", "-o1"});
    colleen.addArgument<std::string>("testArg2", 2, {"--opt2", "--option2", "-o2"});
    // colleen.addArgument<bool>("testArg3", 3, {"--opt3", "--option3", "-o3"});

    EXPECT_EQ(colleen.noArgs(), 1);
    int i = 2;
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
