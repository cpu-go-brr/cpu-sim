#include "bitset.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>

const std::size_t bitset::val() const
{
    std::size_t v = 0;
    for (std::size_t i = sizeof(std::size_t) - 1; (int)i != -1; i--)
        v = (v << 8) | ((i < data.size()) ? data[i] : 0);

    return v;
}
bitset::bitset() : length{8}
{
    data = {0};
}

bitset::bitset(std::vector<uint8_t> data_, std::size_t length_) : length{length_}
{
    for (std::size_t i = 0; i < bytes(); i++)
        data.push_back((data_.size() > i) ? data_[i] : 0);
}

bitset::bitset(bitset data_, std::size_t length_) : length{length_}
{
    for (std::size_t i = 0; i < std::ceil(length / 8.0); i++)
        data.push_back((data_.size() > i) ? data_[bitset(i)] : 0);
}

bitset::bitset(std::size_t data_, std::size_t length_)
{

    if (length_ == 0)
        length = 8 * sizeof(std::size_t);
    else
        length = length_;
    for (std::size_t i = 0; i < bytes(); i++)
    {
        data.push_back(data_);
        data_ >>= 8;
    }
}

bitset::bitset(std::string data_, std::size_t length_)
{
    uint16_t num = 0;

    for (std::size_t i = 0; i < data_.size(); i++)
    {
        num = num * 10 + data_[i] - '0';
        if (num > 0xFF)
        {
            data.push_back(num);
            num >>= 8;
        }
    }
    data.push_back(num);
    if (length_ == 0)
        length = data.size() * 8;
    else
        length = length_;
}

bitset::bitset(int data_, std::size_t length_)
{
    if (length_ == 0)
        length = 8 * sizeof(int);
    else
        length = length_;

    for (std::size_t i = 0; i < bytes(); i++)
    {
        data.push_back(data_);
        data_ >>= 8;
    }
}

bitset::bitset(long data_, std::size_t length_)
{
    if (length_ == 0)
        length = 8 * sizeof(long);
    else
        length = length_;
    for (std::size_t i = 0; i < bytes(); i++)
    {
        data.push_back(data_);
        data_ >>= 8;
    }
}

const std::size_t bitset::bytes() const
{
    return (std::size_t)std::ceil(length / 8.0);
}

const std::string bitset::bin() const
{
    std::string ret = "";
    for (auto i : data)
    {
        for (int index = 0; index < 8; index++)
        {
            ret = ((i % 2) ? "1" : "0") + ret;
            i >>= 1;
        }
    }
    return ret.substr(ret.length() - length, length);
}

const std::string bitset::hex() const
{
    std::string ret = "";
    for (auto i : data)
    {
        std::stringstream ss;
        ss << std::setw(2) << std::hex << std::setfill('0') << (int)i;
        ret = ss.str() + ret;
    }

    if (length % 8 <= 4 && length % 8 > 0)
        ret = ret.substr(1);
    return ret;
}

const std::string bitset::dec() const
{
    return std::to_string(val());
}

bitset &bitset::operator=(const bitset &other)
{
    this->data = other.data;
    this->length = other.length;
    return *this;
}

bool bitset::operator==(const int &other)
{
    return val() == (std::size_t)other;
}

bool bitset::operator==(const std::size_t &other)
{
    return val() == other;
}

bool bitset::operator==(const bitset &other)
{
    return val() == other.val();
}


bool bitset::operator<(const bitset &other)
{
    return val() < other.val();
}

bool bitset::operator<=(const bitset &other)
{
    return val() <= other.val();
}
bool bitset::operator>=(const bitset &other)
{
    return val() >= other.val();
}

bool bitset::operator>(const int &other)
{
    return (int)val() > other;
}

bool bitset::operator>=(const int &other)
{
    return (int)val() >= other;
}

bool bitset::operator<(const int &other)
{
    return (int)val() < other;
}

bool bitset::operator<=(const int &other)
{
    return (int)val() <= other;
}


bitset bitset::operator>>(const bitset c_)
{

    const std::size_t c = c_.val();

    std::vector<uint8_t> ret;

    std::size_t byte_diff = c / 8;
    std::size_t bit_diff = c % 8;

    for (std::size_t i = 0; i < bytes(); i++)
    {

        std::size_t transfer_index = byte_diff + i;
        uint16_t mydata = 0;
        if (transfer_index < bytes())
            mydata |= data[transfer_index];

        transfer_index++;

        if (transfer_index < bytes())
            mydata |= data[transfer_index] << 8;

        uint16_t shift = mydata >> bit_diff;

        ret.push_back(shift);
    }

    std::size_t new_length = length - c;

    uint8_t allowed_bits = new_length % 8;
    uint8_t new_bytes = new_length / 8;

    for (int i = ret.size() - 1; i > new_bytes; i--)
        ret[i] = 0;

    uint8_t mask = (1 << allowed_bits) - 1;
    ret[new_bytes] &= mask;

    return bitset(ret, length);
}

bitset bitset::operator<<(const bitset c_)
{
    const std::size_t c = c_.val();
    std::vector<uint8_t> ret;

    for (std::size_t i = 0; i < bytes(); i++)
    {

        ret.push_back(0);
    }
    std::size_t byte_diff = c / 8;
    std::size_t bit_diff = c % 8;

    for (std::size_t i = 0; i < bytes(); i++)
    {
        uint16_t shift = data[i] << bit_diff;

        std::size_t transfer_index = byte_diff + i;
        if (transfer_index >= bytes())
            break; // we are overflowing
        // let's start with the low byte first
        ret[transfer_index] |= shift & 0xFF;

        // let's do the high byte now
        transfer_index++;
        if (transfer_index >= bytes())
            break; // we are overflowing
        ret[transfer_index] |= (shift >> 8) & 0xFF;
    }

    return bitset(ret, length);
}

bitset operator,(bitset a, bitset const &b)
{
    auto s = a.length + b.length;
    bitset ret(std::vector<uint8_t>((int)std::ceil(s / 8), 0), s);

    return ((ret + a) << b.length) + b;
}

bitset operator^(bitset a, bitset const &b)
{
    for (std::size_t i = 0; i < std::min(a.bytes(), b.bytes()); i++)
        a[i] ^= b[i];

    return a;
}

bitset operator+(bitset a, bitset const &b)
{
    bool overflow = 0;
    std::size_t res_bits = std::max(a.size(), b.size()) + 1;
    std::size_t res_bytes = (std::size_t)std::ceil(res_bits / 8.0);
    std::vector<uint8_t> bytes{};
    bytes.reserve(res_bytes);

    for (std::size_t i = 0; i < res_bytes; i++)
    {
        uint8_t byte_a = (a.bytes() > i) ? a[i] : 0;
        uint8_t byte_b = (b.bytes() > i) ? b[i] : 0;

        if (a.bytes() - 1 == i)
            byte_a &= (1 << (a.length % 8)) - 1;
        if (b.bytes() - 1 == i)
            byte_b &= (1 << (b.length % 8)) - 1;

        uint16_t addition = byte_a + byte_b + overflow;
        overflow = 0x100 & addition;
        bytes.push_back(addition & 0xFF);
    }
    return bitset(bytes, res_bits);
}

bitset operator~(bitset a)
{
    std::vector<uint8_t> bytes{a.data};

    for (auto &d : bytes)
        d = ~d;

    bytes[bytes.size() - 1] &= (1 << (a.length % 8)) - 1;

    return bitset(bytes, a.length);
}

bool operator>(bitset const &a, bitset const &b)
{
    return a.val() > b.val();
}
bool operator<(bitset const &a, bitset const &b)
{
    return a.val() < b.val();
}
bool operator==(bitset const &a, bitset const &b)
{
    return a.val() == b.val();
}
bool operator>(bitset const &a, int const &b)
{
    return (int)a.val() > b;
}
bool operator<(bitset const &a, int const &b)
{
    return (int)a.val() < b;
}
bool operator==(bitset const &a, int const &b)
{
    return (int)a.val() == b;
}
