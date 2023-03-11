#include <string.h>
#include "abitset.hpp"
#include "AddressInfo.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>


void abitset::apply_mask()
{
    if(length % 8 == 0) return;

    data[data.size()-1] &= ((1 << (length % 8))-1);
}

const std::size_t abitset::val() const
{
    std::size_t v = 0;
    for (std::size_t i = sizeof(std::size_t) - 1; (int)i != -1; i--)
    {
        auto val = ((i < data.size()) ? data[i] : 0);

        if (length % 8 != 0 && i == data.size() - 1)
            val &= (1 << (length % 8)) - 1;

        v = (v << 8) | val;
    }

    return v;
}

abitset::abitset() : length{8}
{
    data = {0};
}

abitset::abitset(std::vector<uint8_t> data_, std::size_t length_) : length{length_}
{
    for (std::size_t i = 0; i < bytes(); i++)
        data.push_back((data_.size() > i) ? data_[i] : 0);

    apply_mask();
}

abitset::abitset(uint8_t* data_, bits_t bytes_, bits_t length_) : length{length_}
{
    for (std::size_t i = 0; i < bytes(); i++)
        data.push_back((bytes_ > i) ? data_[i] : 0);

    apply_mask();
}

abitset::abitset(abitset data_, std::size_t length_) : length{length_}
{
    for (std::size_t i = 0; i < std::ceil(length / 8.0); i++)
        data.push_back((data_.size() > i) ? data_[abitset(i)] : 0);
    
    apply_mask();
}

abitset::abitset(std::size_t data_, std::size_t length_)
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

    apply_mask();
}

abitset::abitset(std::string data_, std::size_t length_)
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

    apply_mask();
}

abitset::abitset(int data_, std::size_t length_)
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

    apply_mask();
}

abitset::abitset(long data_, std::size_t length_)
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

    apply_mask();
}

const std::size_t abitset::bytes() const
{
    return (std::size_t)std::ceil(length / 8.0);
}

void abitset::bin(char* str) const
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
    ret = ret.substr(ret.length() - length, length);

    strncpy(str, ret.c_str(), ret.size());
}

void abitset::hex(char* str) const
{
    std::string ret = "";
    for (auto i : data)
    {
        std::stringstream ss;
        ss << std::setw(2) << std::uppercase << std::hex << std::setfill('0') << (int)i;
        ret = ss.str() + ret;
    }

    if (length % 8 <= 4 && length % 8 > 0)
        ret = ret.substr(1);
    
    strncpy(str, ret.c_str(), ret.size());
}

void abitset::dec(char* str) const
{
    std::size_t size = (std::size_t)std::ceil(std::log10(std::pow(2,length)));
    std::string ret = "";
    ret += std::to_string(val());

    while(ret.size() < size) ret = " " + ret;
    strncpy(str, ret.c_str(), ret.size());
}

abitset &abitset::operator=(const abitset &other)
{
    this->data = other.data;
    this->length = other.length;
    return *this;
}

bool abitset::operator==(const int &other)
{
    return val() == (std::size_t)other;
}

bool abitset::operator==(const std::size_t &other)
{
    return val() == other;
}

bool abitset::operator==(const abitset &other)
{
    return val() == other.val();
}

bool abitset::operator!=(const int &other)
{
    return val() != (std::size_t)other;
}

bool abitset::operator!=(const std::size_t &other)
{
    return val() != other;
}

bool abitset::operator!=(const abitset &other)
{
    return val() != other.val();
}

bool abitset::operator<(const abitset &other)
{
    return val() < other.val();
}

bool abitset::operator>(const abitset &other)
{
    return val() > other.val();
}
// bool abitset::operator>(abitset& other)
// {
//     return val() > other.val();
// }
// bool abitset::operator<(abitset& other)
// {
//     return val() < other.val();
// }

// bool abitset::operator>(abitset const&other)
// {
//     return val() > other.val();
// }
// bool abitset::operator<(abitset const&other)
// {
//     return val() < other.val();
// }


bool abitset::operator<=(const abitset &other)
{
    return val() <= other.val();
}
bool abitset::operator>=(const abitset &other)
{
    return val() >= other.val();
}

bool abitset::operator>(const int &other)
{
    return (int)val() > other;
}

bool abitset::operator>=(const int &other)
{
    return (int)val() >= other;
}

bool abitset::operator<(const int &other)
{
    return (int)val() < other;
}

bool abitset::operator<=(const int &other)
{
    return (int)val() <= other;
}

abitset abitset::operator>>(const abitset c_)
{

    const std::size_t c = c_.val();
    if(c == 0) return *this;
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

    return abitset(ret, length);
}

abitset abitset::operator<<(const abitset c_)
{
    const std::size_t c = c_.val();
    if(c == 0) return *this;
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

    return abitset(ret, length);
}

abitset operator,(abitset a, abitset const &b)
{
    auto s = a.length + b.length;
    abitset ret(std::vector<uint8_t>((int)std::ceil(s / 8), 0), s);

    return ((ret + a) << b.length) + b;
}

abitset operator^(abitset a, abitset const &b)
{
    for (std::size_t i = 0; i < std::min(a.bytes(), b.bytes()); i++)
        a[i] ^= b[i];

    return a;
}

abitset operator&(abitset a, abitset const &b)
{
    std::size_t res_bits = std::max(a.size(), b.size());
    std::size_t res_bytes = (std::size_t)std::ceil(res_bits / 8.0);
    std::vector<uint8_t> bytes{};
    bytes.reserve(res_bytes);

    for (std::size_t i = 0; i < res_bytes; i++)
    {
        uint8_t byte_a = (a.bytes() > i) ? a[i] : 0;
        uint8_t byte_b = (b.bytes() > i) ? b[i] : 0;

        if (a.bytes() - 1 == i && (a.length % 8) != 0)
            byte_a &= (1 << (a.length % 8)) - 1;
        if (b.bytes() - 1 == i && (b.length % 8) != 0)
            byte_b &= (1 << (b.length % 8)) - 1;

        bytes.push_back(byte_a & byte_b);
    }
    return abitset(bytes, res_bits);
}

abitset operator|(abitset a, abitset const &b)
{
    std::size_t res_bits = std::max(a.size(), b.size());
    std::size_t res_bytes = (std::size_t)std::ceil(res_bits / 8.0);
    std::vector<uint8_t> bytes{};
    bytes.reserve(res_bytes);

    for (std::size_t i = 0; i < res_bytes; i++)
    {
        uint8_t byte_a = (a.bytes() > i) ? a[i] : 0;
        uint8_t byte_b = (b.bytes() > i) ? b[i] : 0;

        if (a.bytes() - 1 == i && (a.length % 8) != 0)
            byte_a &= (1 << (a.length % 8)) - 1;
        if (b.bytes() - 1 == i && (b.length % 8) != 0)
            byte_b &= (1 << (b.length % 8)) - 1;

        bytes.push_back(byte_a | byte_b);
    }
    return abitset(bytes, res_bits);
}

abitset operator+(abitset a, abitset const &b)
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

        if (a.bytes() - 1 == i && (a.length % 8) != 0)
            byte_a &= (1 << (a.length % 8)) - 1;
        if (b.bytes() - 1 == i && (b.length % 8) != 0)
            byte_b &= (1 << (b.length % 8)) - 1;

        uint16_t addition = byte_a + byte_b + overflow;
        overflow = 0x100 & addition;
        bytes.push_back(addition & 0xFF);
    }
    return abitset(bytes, res_bits);
}

abitset operator~(abitset a)
{
    std::vector<uint8_t> bytes{a.data};

    for (auto &d : bytes)
        d = ~d;

    if (a.length % 8 != 0)
        bytes[bytes.size() - 1] &= (1 << (a.length % 8)) - 1;

    return abitset(bytes, a.length);
}

bool operator>(abitset const &a, abitset const &b)
{
    return a.val() > b.val();
}
bool operator<(abitset const &a, abitset const &b)
{
    return a.val() < b.val();
}
bool operator==(abitset const &a, abitset const &b)
{
    return a.val() == b.val();
}

bool operator!=(abitset const &a, abitset const &b)
{
    return a.val() != b.val();
}
bool operator>(abitset const &a, int const &b)
{
    return (int)a.val() > b;
}
bool operator<(abitset const &a, int const &b)
{
    return (int)a.val() < b;
}
bool operator==(abitset const &a, int const &b)
{
    return (int)a.val() == b;
}

bool operator!=(abitset const &a, int const &b)
{
    return (int)a.val() != b;
}
void abitset::write(uint8_t *mem, const AddressInfo &info) const
{
    abitset shifted{*this, (bitset::bits_t)(info.length + info.bit_offset)};
    shifted = shifted << info.bit_offset;

    auto mask_vector = std::vector<uint8_t>(bytes_needed(info), 0xFF);
    abitset mask{mask_vector, (abitset::bits_t)(info.bit_offset + info.length)};
    mask = mask << info.bit_offset;

    if ((info.length + info.bit_offset) % 8 != 0) // alignment needs masking
        mask[bytes_needed(info) - 1] &= ((1 << ((info.length + info.bit_offset) % 8)) - 1);

    for (std::size_t i = 0; i < bytes_needed(info); i++)
    {
        uint8_t original_data = mem[info.byte_start + i];

        mem[info.byte_start + i] = (original_data & ~mask[i]) | (shifted[i] & mask[i]);
    }
}

abitset::operator bool() const
{
    return val() > 0;
}

