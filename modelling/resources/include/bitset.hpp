#pragma once

#include <vector>
#include <iostream>
#include <cmath>

class bitset
{
public:
    bitset();
    bitset(std::vector<uint8_t> data, std::size_t length);
    bitset(bitset data, std::size_t length);
    bitset(std::vector<uint8_t> data);
    bitset(int data, std::size_t length = 0);
    bitset(long data, std::size_t length = 0);
    bitset(std::size_t data, std::size_t length = 0);
    bitset(std::string data, std::size_t length = 0);
    

    const std::size_t size() const { return length; }
    uint8_t operator[](bitset i) const { return data[i.val()]; }
    uint8_t &operator[](bitset i) { return data[i.val()]; }


    friend bitset operator+(bitset a, bitset const &b);
    friend bitset operator~(bitset a);
    friend bitset operator,(bitset a, bitset const &b);
    friend bitset operator^(bitset a, bitset const &b);


    bool operator>(const bitset &other);
    bool operator<(const bitset &other);

    bool operator<(const int &other);
    bool operator>(const int &other);


    bool operator>=(const bitset &other);
    bool operator<=(const bitset &other);

    bool operator<=(const int &other);
    bool operator>=(const int &other);

    bitset operator<<(const bitset c);
    bitset operator>>(const bitset c);



    bitset& operator=(const bitset& other);
    bool operator==(const int& other);
    bool operator==(const std::size_t& other);
    bool operator==(const bitset& other);

    const std::size_t bytes() const;
    const std::string bin() const;
    const std::string hex() const;
    const std::string dec() const;
    const std::size_t val() const;

private:
    std::vector<uint8_t> data = {};
    std::size_t length = 0;
};