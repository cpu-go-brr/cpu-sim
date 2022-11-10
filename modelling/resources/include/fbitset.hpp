#pragma once

#include <cstdint>

class fbitset
{
    typedef std::size_t storage_t;
    typedef uint8_t bits_t; //datatype exceeds 8*sizeof(storage_t)
    typedef uint8_t byte_t; //datatype must exceed sizeof(storage_t)
public:
    fbitset() = default;
    fbitset(int data, bits_t length = 0);
    fbitset(storage_t data, bits_t length = 0);
    fbitset(fbitset data, bits_t length);
    fbitset(byte_t* data, bits_t length);
    

    //get bytes needed to store a value of given bitlength
    const byte_t bytes(const bits_t& bits) const;
    //get bytes needed to store current bitlength
    const byte_t bytes() const;
    //get bitlength
    const bits_t size() const;
    //print value as binary
    const char* bin() const;
    //print value as hex
    const char* hex() const;
    //print value as dec
    const char* dec() const;

    //get value
    const storage_t val() const;
    //get mask for current bitlength
    const storage_t mask() const;
    // set the current value whilst applying the bitmask
    void set(const storage_t& data);

    fbitset operator+(fbitset const &b);
    fbitset operator,(fbitset const &b);
    fbitset operator^(fbitset const &b);
    fbitset operator~();

    bool operator>(const fbitset &other);
    bool operator<(const fbitset &other);

    bool operator<(const int &other);
    bool operator>(const int &other);


    bool operator>=(const fbitset &other);
    bool operator<=(const fbitset &other);

    bool operator<=(const int &other);
    bool operator>=(const int &other);

    fbitset operator<<(const fbitset c);
    fbitset operator>>(const fbitset c);

    fbitset operator<<(const int &other);
    fbitset operator>>(const int &other);

    bool operator==(const int& other);
    bool operator==(const storage_t& other);
    bool operator==(const fbitset& other);

private:
    storage_t data = 0;
    const bits_t bits = 0; // number of bits
};