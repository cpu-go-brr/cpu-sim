#include <catch2/catch_test_macros.hpp>
#define CONFIG_CATCH_MAIN

#include "abitset/include/abitset.hpp"

TEST_CASE("abitset Addition")
{
    abitset one{1, 1};
    abitset three_initialized{3, 1};

    REQUIRE((one == 1));
    REQUIRE((three_initialized == 1));
    REQUIRE(((one + one) == 2));
    REQUIRE(((one + three_initialized) == 2));
}

TEST_CASE("abitset shift")
{
    abitset five{0b101, 3};

    REQUIRE((five << 1 == 2));
    REQUIRE((five >> 1 == 2));
}

TEST_CASE("abitset complement")
{
    abitset five{0b101, 3};
    REQUIRE((~five  == 2));
}

TEST_CASE("abitset concatenation")
{
    abitset five{0b101, 3};
    REQUIRE(((five,five)  == 0b101101));
}