#include <catch2/catch_test_macros.hpp>
#define CONFIG_CATCH_MAIN

#include "expression.hpp"
#include <iostream>


//Testbenamung dreiteilig Methode, Fall, Erwartung


TEST_CASE("wrapAddressInsideParenthesisInGetFunction- multiple function values")
{
    std::string s{"mem((PC+1), (PC+2))"};
    CPUDescription::Expression::wrapAddressInsideParenthesisInGetFunction(s);

    std::cout << s << "\n";

    REQUIRE((s == "set((get(AC)), mem(((mem(get(PC)+1)), mem(get(PC)+2)))"));
}

TEST_CASE("wrapAddressInsideParenthesisInGetFunction- - function value")
{
    std::string s{"ram_status((CM, X2, 0b00))"};
    CPUDescription::Expression::wrapAddressInsideParenthesisInGetFunction(s);
    REQUIRE((s == "ram_status((get(CM), get(X2), 0b00))"));
}

TEST_CASE("wrapAddressInsideParenthesisInGetFunction single value")
{
    std::string s{"CM"};
    CPUDescription::Expression::wrapAddressInsideParenthesisInGetFunction(s);
    REQUIRE((s == "CM"));
}

TEST_CASE("wrapAddressInGetFunction")
{
    std::string s{"ram_status((CM, X2, 0b00))"};
    CPUDescription::Expression::wrapAddressInGetFunction(s);
    REQUIRE((s == "ram_status((get(CM), get(X2), 0b00))"));
}

TEST_CASE("expression conversion")
{
//     CPUDescription::Expression e{"ACC --> ram_status((CM, X2, 0b00))"};
//     std::string out = e.getCode({});
//     std::cout << out << "\n";
//     REQUIRE((out == "/* ACC --> ram_status((CM, X2, 0b00))*/\nset((get(ACC)), ram_status((get(CM),get(X2),bitset(0,2))));\n"));
}