#pragma once

#include <vector>
#include <iostream>
#include <cmath>

class AddressInfo;

//accurate abitset
class abitset
{

public:
    typedef std::size_t storage_t;
    typedef std::size_t bits_t; //datatype exceeds 8*sizeof(storage_t)
    typedef std::size_t byte_t; //datatype must exceed sizeof(storage_t)
    abitset();
    abitset(std::vector<uint8_t> data, bits_t length);
    abitset(abitset data, bits_t length);
    abitset(std::vector<uint8_t> data);
    abitset(uint8_t* data, bits_t bytes, bits_t length);
    abitset(int data, bits_t length = 0);
    abitset(long data, bits_t length = 0);
    abitset(std::size_t data, bits_t length = 0);
    abitset(std::string data, bits_t length = 0);
    
    void apply_mask();
    const std::size_t size() const { return length; }
    uint8_t operator[](abitset i) const { return data[i.val()]; }
    uint8_t &operator[](abitset i) { return data[i.val()]; }
    uint8_t operator[](std::size_t i) const { return data[i]; }
    uint8_t &operator[](std::size_t i) { return data[i]; }

    void write(uint8_t* addr, const AddressInfo& info) const;

    friend abitset operator+(abitset a, abitset const &b);
    friend abitset operator&(abitset a, abitset const &b);
    friend abitset operator|(abitset a, abitset const &b);
    friend abitset operator~(abitset a);
    friend abitset operator,(abitset a, abitset const &b);
    friend abitset operator^(abitset a, abitset const &b);
    explicit operator bool() const;

    bool operator>(const abitset &other);
    bool operator<(const abitset &other);

    // bool operator>(abitset const&other);
    // bool operator<(abitset const&other);


    bool operator<(const int &other);
    bool operator>(const int &other);


    bool operator>=(const abitset &other);
    bool operator<=(const abitset &other);

    bool operator<=(const int &other);
    bool operator>=(const int &other);

    abitset operator<<(const abitset c);
    abitset operator>>(const abitset c);

    abitset& operator=(const abitset& other);
    bool operator==(const int& other);
    bool operator==(const std::size_t& other);
    bool operator==(const abitset& other);

    bool operator!=(const int& other);
    bool operator!=(const std::size_t& other);
    bool operator!=(const abitset& other);


    const std::size_t bytes() const;
    void bin(char* addr) const;
    void hex(char* addr) const;
    void dec(char* addr) const;
    const std::size_t val() const;

private:
    std::vector<uint8_t> data = {};
    std::size_t length = 0;
};
