#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <bitset>

class bitset
{
public:
    bitset(std::vector<uint8_t> data, std::size_t length);
    bitset(bitset data, std::size_t length);
    bitset(std::vector<uint8_t> data);
    bitset(int data);
    bitset(long data);
    bitset(std::size_t data);
    bitset(std::string data);
    

    const std::size_t size() const { return length; }
    uint8_t operator[](bitset i) const { return data[i.val()]; }
    uint8_t &operator[](bitset i) { return data[i.val()]; }

    friend bitset operator+(bitset a, bitset const &b);
    friend bitset operator~(bitset a);

    bitset operator<<(const bitset c);
    bitset operator>>(const bitset c);

    bitset& operator=(const bitset& other);

    const std::size_t bytes() const;
    const std::string show() const;
    const std::size_t val() const;

private:
    std::vector<uint8_t> data = {};
    std::size_t length = 0;
};