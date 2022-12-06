#include "fbitset.hpp"
#include "AddressInfo.hpp"
#include <stddef.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

// returns the bitmask by length
//  0 -> 0; 1 -> 1; 2 -> 11; 3 -> 111...
const fbitset::storage_t fbitset::mask() const
{
    return ((1ul << bits) - 1);
}

const fbitset::storage_t fbitset::mask(bits_t b) const
{
    return ((1ul << b) - 1);
}

const fbitset::storage_t fbitset::val() const
{
    return data;
}

void fbitset::apply_mask()
{
    data = data & mask(); // assign value
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

fbitset::fbitset(int data_, fbitset::bits_t bits_)
    : bits{!bits_ ? (bits_t)(8 * sizeof(data_)) : bits_} // set length to maximum if it is 0
{
    set((storage_t)data_); // assign value
}

fbitset::fbitset(storage_t data_, fbitset::bits_t bits_)
    : bits{!bits_ ? (bits_t)(8 * sizeof(data_)) : bits_} // set length to maximum if it is 0
{
    set(data_); // assign value
}

fbitset::fbitset(fbitset data_, fbitset::bits_t bits_)
    : bits{bits_}
{
    set(data_.data); // assign value
}

fbitset::fbitset(uint8_t *data_,fbitset::bits_t len, fbitset::bits_t bits)
    : bits{bits}
{
    storage_t buffer = 0;
    for (uint8_t byte = 0; byte <  len; byte++)
        buffer = buffer << 8 | data_[len - byte -1];
    
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

fbitset fbitset::operator<<(const int &c)
{
    return fbitset(data << c, bits);
}
fbitset fbitset::operator>>(const int &c)
{
    return fbitset(data >> c, bits);
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

bool fbitset::operator!=(const int &other)
{
    return data != (storage_t)other;
}

bool fbitset::operator!=(const storage_t &other)
{
    return data != other;
}

bool fbitset::operator!=(const fbitset &other)
{
    return data != other.data;
}

fbitset &fbitset::operator=(const fbitset &other)
{
    this->data = other.data;
    this->bits = other.bits;
    return *this;
}

void fbitset::write(uint8_t *mem, const AddressInfo &info) const
{
    auto m = mask(info.length) << info.bit_offset;
    uint8_t m_overflow = data >> ((sizeof(storage_t) - 1) * 8 - info.bit_offset); // we need an extra byte for our overflow


    auto d = data << info.bit_offset;
    uint8_t d_overflow = data >> ((sizeof(storage_t) - 1) * 8 - info.bit_offset); // we need an extra byte for our overflow

    auto needed_bytes = bytes_needed(info); 
    for (auto i = 0u; i < needed_bytes; i++)
    {
        size_t index = info.byte_start  + i;
        if (i > sizeof(storage_t))
        {
            mem[index] = (mem[index] & ~m);
        }
        else if (i == sizeof(storage_t))
        {
            mem[index] = (mem[index] & ~m_overflow) | (d_overflow & m_overflow);
        }
        else
        {
            mem[index] = (mem[index] & ~m) | (d & m);
            d >>= 8;
            m >>= 8;
        }
    }
}
// print value as bin
void fbitset::bin(char * str) const
{
    storage_t cpy = data;
    for(size_t i = 0; i < bits; i++)
    {
        str[bits-1-i] = (cpy&1)?'1':'0';
        cpy >>= 1;
    }
}
// print value as hex
void fbitset::hex(char * str) const
{
    storage_t cpy = data;
    size_t chars = (bits / 4) + ((bits%4)?1:0);
    for(size_t i = 0; i < chars; i++)
    {
        char val = cpy&0b1111;
        str[chars-i-1] = val + ((val <= 9)? '0': ('A'-10));
        cpy >>=4;
    }
}
// print value as dec
void fbitset::dec(char* str) const 
{
    storage_t cpy = data;
    size_t i = 0;
    for(storage_t m = mask(); m > 0; m /= 10) i++;

    for(; i-->0;)
    {
        str[i] =cpy % 10 + '0';
        cpy /= 10;
    }
}

fbitset::operator bool() const
{
    return data > 0;
}
