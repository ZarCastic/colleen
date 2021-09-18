//
// Created by Tobias Fuchs on 10.09.21.
//

#include <gtest/gtest.h>
#include "colleen/colleen.h"
#include "colleen/test/unit_colleen.h"
#include "config/float_option.h"
#include "config/nested_option/nest_level_1_nested_option/nest_level_2_option.h"
#include "config/nested_option/nest_level_1_option.h"
#include "config/signed_int_option.h"
#include "config/string_option.h"
#include "config/unsigned_int_option.h"

TEST_F(Unit_Colleen, DirectAccess) {
    const char* argv[] = {
        "colleen-test",
        "--string_option=StringOption",
        "--unsigned_int_option=1337",
        "--signed_int_option=-12",
        "--float_option=4.20",
        "--nested_option.nest_level_1_option=Nest1",
        "--nested_option.nest_level_1_nested_option.nest_level_2_option=Nest2",
        "--nested_option.nest_level_1_nested_option.nest_level_2_option=Nest2"};
    const auto argc = sizeof(argv) / sizeof(argv[0]);

    colleen::_impl::registry::instance().parse(
        argc, argv, colleen::_impl::registry::parse_options::throw_on_error);

    EXPECT_DOUBLE_EQ(config::float_option.get(), 4.20);
    EXPECT_EQ(config::signed_int_option.get(), -12);
    EXPECT_EQ(config::unsigned_int_option.get(), 1337ull);
    EXPECT_EQ(config::string_option.get(), "StringOption");
    EXPECT_EQ(config::nested_option::nest_level_1_option.get(), "Nest1");
    EXPECT_EQ(
        config::nested_option::nest_level_1_nested_option::nest_level_2_option
            .get(),
        "Nest2");
}

TEST_F(Unit_Colleen, InvalidOptions) {
    const char* argv[] = {"colleen-test", "--invalid_option=True"};
    EXPECT_NO_THROW(colleen::_impl::registry::instance().parse(
        2, argv, colleen::_impl::registry::parse_options::none));
    EXPECT_ANY_THROW(colleen::_impl::registry::instance().parse(
        2, argv, colleen::_impl::registry::parse_options::throw_on_error));
}
