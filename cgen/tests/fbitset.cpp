#include <catch2/catch_test_macros.hpp>
#define CONFIG_CATCH_MAIN

#include "fbitset.hpp"

TEST_CASE("fbitset Addition")
{
    fbitset one{1, 1};
    fbitset three_initialized{3, 1};

    REQUIRE((one == 1));
    REQUIRE((three_initialized == 1));
    REQUIRE(((one + one) == 2));
    REQUIRE(((one + three_initialized) == 2));
}

TEST_CASE("fbitset shift")
{
    fbitset five{0b101, 3};

    REQUIRE((five << 1 == 2));
    REQUIRE((five >> 1 == 2));
}

TEST_CASE("fbitset complement")
{
    fbitset five{0b101, 3};
    REQUIRE((~five  == 2));
}

TEST_CASE("fbitset concatenation")
{
    fbitset five{0b101, 3};
    REQUIRE(((five,five)  == 0b101101));
}