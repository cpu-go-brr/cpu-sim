#include "bitset.hpp"

#include <cmath>

const std::size_t bitset::val() const
{
    std::size_t v;
    for (std::size_t i = sizeof(std::size_t); i >= 0; i--)
        v = (v << 8) | (i < data.size()) ? data[i] : 0;

    return v;
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

bitset::bitset(std::vector<uint8_t> data_)
{
    length = data_.size() * 8;

    for (std::size_t i = 0; i < std::ceil(length / 8.0); i++)
        data.push_back((data_.size() > i) ? data_[i] : 0);
}

bitset::bitset(std::size_t data_)
{
    length = sizeof(std::size_t);

    for (std::size_t i = 0; i < length; i++)
    {
        data.push_back(data_);
        data_ >>= 8;
    }
}

bitset::bitset(std::string data_)
{
    uint16_t num = 0;

    for(std::size_t i = 0; i < data_.size(); i++)
    {
        num = num * 10 + data_[i] - '0';
        if(num > 0xFF)
        {
            data.push_back(num);
            num >>= 8;
        }
    }
    data.push_back(num);
    length = data.size() * 8;
}


bitset::bitset(int data_)
{
    length = sizeof(int);

    for (std::size_t i = 0; i < length; i++)
    {
        data.push_back(data_);
        data_ >>= 8;
    }
}

bitset::bitset(long data_)
{
    length = sizeof(long);

    for (std::size_t i = 0; i < length; i++)
    {
        data.push_back(data_);
        data_ >>= 8;
    }
}

const std::size_t bitset::bytes() const
{
    return (std::size_t)std::ceil(length / 8.0);
}

const std::string bitset::show() const
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

bitset &bitset::operator=(const bitset &other)
{
    this->data = other.data;
    this->length = other.length;
    return *this;
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
        ret.push_back(0);

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
    return bitset(bytes, a.length);
}