#include "fbitset.hpp"

#define max(a, b) ((a) > (b) ? (a) : (b))

// returns the bitmask by length
//  0 -> 0; 1 -> 1; 2 -> 11; 3 -> 111...
const fbitset::storage_t fbitset::mask() const
{
    return ((1 << bits) - 1);
}

const uint8_t fbitset::bytes() const
{
    return (bits >> 3) + ((bits & 0b111) > 0);
}

const uint8_t fbitset::bytes(const fbitset::bits_t &bits_) const
{
    return (bits_ >> 3) + ((bits_ & 0b111) > 0);
}

const uint8_t fbitset::size() const
{
    return bits;
}

// sets the value and applies mask
void fbitset::set(const storage_t &val)
{
    data = (storage_t)val & mask(); // assign value
}

fbitset::fbitset(int data_, fbitset::bits_t bits)
    : bits{!bits ? (bits_t)(8 * sizeof(data_)) : bits} // set length to maximum if it is 0
{
    set((storage_t)data); // assign value
}

fbitset::fbitset(storage_t data_, fbitset::bits_t bits)
    : bits{!bits ? (bits_t)(8 * sizeof(data_)) : bits} // set length to maximum if it is 0
{
    set(data_); // assign value
}

fbitset::fbitset(fbitset data_, fbitset::bits_t bits)
    : bits{bits}
{
    set(data_.data); // assign value
}

fbitset::fbitset(uint8_t *data_, fbitset::bits_t bits)
    : bits{bits}
{
    storage_t buffer = 0;
    for (uint8_t byte = bytes(bits) - 1; byte-- > 0;)
        buffer = buffer << 8 | data_[byte];
    set(buffer);
}

fbitset fbitset::operator+(fbitset const &b)
{
    return fbitset(data + b.data, max(bits, b.bits) + 1);
}

fbitset fbitset::operator,(fbitset const &b)
{
    return fbitset((data << b.bits) + b.data, bits + b.bits);
}

fbitset fbitset::operator^(fbitset const &b)
{
    return fbitset(data ^ b.data, bits);
}

fbitset fbitset::operator~()
{
    return fbitset(~data, bits);
}

bool fbitset::operator>(const fbitset &other)
{
    return data > other.data;
}
bool fbitset::operator<(const fbitset &other)
{
    return data < other.data;
}

bool fbitset::operator<(const int &other)
{
    return data < (storage_t)other;
}
bool fbitset::operator>(const int &other)
{
    return data > (storage_t)other;
}

bool fbitset::operator>=(const fbitset &other)
{
    return data >= other.data;
}
bool fbitset::operator<=(const fbitset &other)
{
    return data <= other.data;
}

bool fbitset::operator<=(const int &other)
{
    return data <= (storage_t)other;
}
bool fbitset::operator>=(const int &other)
{
    return data >= (storage_t)other;
}

fbitset fbitset::operator<<(const fbitset c)
{
    return fbitset(data << c.data, bits);
}
fbitset fbitset::operator>>(const fbitset c)
{
    return fbitset(data >> c.data, bits);
}

bool fbitset::operator==(const int &other)
{
    return data == (storage_t)other;
}

bool fbitset::operator==(const storage_t &other)
{
    return data == other;
}

bool fbitset::operator==(const fbitset &other)
{
    return data == other.data;
}