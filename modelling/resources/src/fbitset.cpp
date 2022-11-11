#include "fbitset.hpp"
#include "AddressInfo.hpp"

#define max(a, b) ((a) > (b) ? (a) : (b))

// returns the bitmask by length
//  0 -> 0; 1 -> 1; 2 -> 11; 3 -> 111...
const fbitset::storage_t fbitset::mask() const
{
    return ((1 << bits) - 1);
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

fbitset::fbitset(int data_, fbitset::bits_t bits)
    : bits{!bits ? (bits_t)(8 * sizeof(data_)) : bits} // set length to maximum if it is 0
{
    set((storage_t)data_); // assign value
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

fbitset &fbitset::operator=(const fbitset &other)
{
    this->data = other.data;
    return *this;
}

void fbitset::write(uint8_t *mem, const AddressInfo &info) const
{
    auto m = mask() << info.bit_offset;
    uint8_t m_overflow = data >> ((sizeof(storage_t) - 1) * 8 - info.bit_offset); // we need an extra byte for our overflow

    auto d = data << info.bit_offset;
    uint8_t d_overflow = data >> ((sizeof(storage_t) - 1) * 8 - info.bit_offset); // we need an extra byte for our overflow

    for (auto i = 0u; i < bytes_needed(info); i++)
    {
        if (i > sizeof(storage_t))
        {
            mem[i + info.bit_offset] = 0;
        }
        else if (i == sizeof(storage_t))
        {
            mem[i + info.bit_offset] = (mem[i + info.bit_offset] & ~m_overflow) | (d_overflow & m_overflow);
        }
        else
        {
            mem[i + info.bit_offset] = (mem[i + info.bit_offset] & ~m) | (d & m);
            d >>= 8;
            m >>= 8;
        }
    }
}
// print value as bin
const char *fbitset::bin() const
{
    return NULL;
}
// print value as hex
const char *fbitset::hex() const
{
    return NULL;
}
// print value as dec
const char *fbitset::dec() const
{
    return NULL;
}