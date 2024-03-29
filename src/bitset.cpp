/*
    Copyright (C) 2011 Emmanuel Teisaire, Nicolás Bombau, Carlos Castro, Damián Domé, FuDePAN

    This file is part of the Phyloloc project.

    Phyloloc is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Phyloloc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Phyloloc.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <mili/mili.h>
#include "phylopp/Consensor/bitset.h"

namespace Consensus
{
using namespace std;
/*bit
 */

class BitSetExceptionHierarchy {};

typedef mili::GenericException<BitSetExceptionHierarchy> BitsetException;

DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidSizeException,
                               BitSetExceptionHierarchy,
                               "Bitsets sizes don't match");

DEFINE_SPECIFIC_EXCEPTION_TEXT(IndexOutOfRangeException,
                               BitSetExceptionHierarchy,
                               "Index out of range");

bitset::bit::bit() : value(false) {}
bitset::bit::bit(bool v) : value(v) {}

const bitset::bit bitset::bit::false_bit = bit(false);
const bitset::bit bitset::bit::true_bit = bit(true);

bitset::bit& bitset::bit::operator=(bool v)
{
    value = v;
    return *this;
}

bitset::bit& bitset::bit::operator=(const bitset::bit& b)
{
    value = b.value;
    return *this;
}

bitset::bit& bitset::bit::operator|=(bool v)
{
    value = value || v;
    return *this;
}

bitset::bit& bitset::bit::operator&=(bool v)
{
    value = value && v;
    return *this;
}

bitset::bit& bitset::bit::operator^=(bool v)
{
    if (v) value = !value;
    return *this;
}

bitset::bit& bitset::bit::operator-=(bool v)
{
    if (v) value = false;
    return *this;
}

bool bitset::bit::operator~() const
{
    return !value;
}

bitset::bit::operator bool() const
{
    return value;
}

bitset::bit& bitset::bit::flip()
{
    value = !value;
    return *this;
}


bitset::bitset() { }

bitset::bitset(size_t size)
{
    resize(size);
}

bitset::bitset(const bitset& b)
{
    bits.resize(b.size());

    for (unsigned int i = 0; i < b.size(); i++)
        bits[i] = b[i];
}


bitset& bitset::operator=(const bitset& b)
{
    bits.clear();
    resize(b.size());

    for (unsigned int i = 0; i < bits.size(); i++)
    {
        bits[i] = b[i];
    }
    return *this;

}

void bitset::resize(size_t n, const bit& v)
{
    bits.resize(n, v);
}
void bitset::clear()
{
    bits.clear();
}

bitset& bitset::operator&=(const bitset& b)
{
    if (b.size() != this->size()) throw InvalidSizeException();

    for (unsigned int i = 0; i < b.size(); i++)
        bits[i] &= b[i];
    return *this;
}

bitset& bitset::operator|=(const bitset& b)
{
    if (b.size() != this->size()) throw InvalidSizeException();

    for (unsigned int i = 0; i < b.size(); i++)
        bits[i] |= b[i];
    return *this;
}

bitset& bitset::operator^=(const bitset& b)
{
    if (b.size() != this->size()) throw InvalidSizeException();

    for (unsigned int i = 0; i < b.size(); i++)
        bits[i] ^= b[i];
    return *this;
}

bitset& bitset::operator-=(const bitset& b)
{
    if (b.size() != this->size()) throw InvalidSizeException();

    for (unsigned int i = 0; i < b.size(); i++)
        bits[i] -= b[i];
    return *this;
}

bitset& bitset::operator<<=(size_t n)
{
    if (n >= this->size()) throw IndexOutOfRangeException();

    for (unsigned int i = 0; i < n; i++)
    {
        bitset::bit last;
        bits.erase(bits.begin());
        bits.push_back(last);
    }
    return *this;
}

bitset& bitset::operator>>=(size_t n)
{
    if (n >= this->size()) throw IndexOutOfRangeException();

    for (unsigned int i = 0; i < n; i++)
    {
        bitset::bit first;
        bits.erase(bits.end());
        bits.insert(bits.begin(), first);
    }

    return *this;
}

bitset bitset::operator<<(size_t n) const
{
    bitset b(*this);
    b <<= n;
    return b;
}

bitset bitset::operator>>(size_t n) const
{
    bitset b(*this);
    b >>= n;
    return b;
}

bitset bitset::operator&(const bitset& b)
{
    if (b.size() != this->size()) throw InvalidSizeException();

    bitset bs(b.size());
    for (unsigned int i = 0; i < b.size(); ++i)
        if (b[i] == bit::true_bit && bits[i] == bit::true_bit)
            bs.set(i);

    return bs;
}

bitset& bitset::set()
{
    for (unsigned int i = 0; i < this->size(); i++)
        bits[i] = true;
    return *this;
}

bitset& bitset::set(size_t index, const bit& value)
{
    if (index >= this->size()) throw IndexOutOfRangeException();

    bits[index] = value;
    return *this;
}

bitset& bitset::set(size_t from, size_t to, const bit& value)
{
    if (from >= this->size() || to >= this->size() || from > to)
        throw IndexOutOfRangeException();

    for (unsigned int i = from; i <= to; i++)
    {
        bits[i] = value;
    }

    return *this;
}

bitset& bitset::reset()
{
    for (unsigned int i = 0; i < this->size(); i++)
        bits[i] = false;
    return *this;
}

bitset& bitset::reset(size_t n)
{
    if (n >= this->size()) throw IndexOutOfRangeException();

    bits[n] = false;
    return *this;
}

bitset& bitset::reset(size_t from, size_t to)
{
    return set(from, to, bitset::bit::false_bit);
}

bitset& bitset::flip()
{
    for (unsigned int i = 0; i < this->size(); i++)
        bits[i] = bits[i].flip();
    return *this;
}

bitset& bitset::flip(size_t index)
{
    if (index >= this->size()) throw IndexOutOfRangeException();

    bits[index] = bits[index].flip();
    return *this;
}

bitset& bitset::flip(size_t from, size_t to)
{
    if (from >= this->size() || to >= this->size() || from > to)
        throw IndexOutOfRangeException();

    for (unsigned int i = from; i <= to; i++)
    {
        bits[i] = bits[i].flip();
    }

    return *this;
}

bitset bitset::operator~() const
{
    bitset b(*this);
    for (unsigned int i = 0; i < b.size(); i++)
        b.bits[i] = ~b.bits[i];
    return b;
}

const bitset::bit bitset::operator[](size_t pos)
{
    if (pos >= this->size()) throw IndexOutOfRangeException();

    return bits[pos];
}

bitset::bit bitset::operator[](size_t pos) const
{
    if (pos >= this->size()) throw IndexOutOfRangeException();

    return bits[pos];
}

size_t bitset::size() const
{
    return bits.size();
}

bool bitset::empty() const
{
    return bits.empty();
}

void bitset::print()
{
    for (unsigned int i = 0; i < size(); ++i)
        std::cout << bits[i];
    std::cout << "\n\n";
}

bool operator==(const bitset& a, const bitset& b)
{
    if (a.size() != b.size()) throw InvalidSizeException();

    bool eq = true;
    unsigned int i = 0;

    while (i < a.size() && eq == true)
    {
        eq = (a[i] == b[i]);
        i++;
    }


    return eq;
}

bool operator!=(const bitset& a, const bitset& b)
{
    return !(a == b);
}

bool operator<(const bitset& a, const bitset& b)
{
    if (a.size() != b.size()) throw InvalidSizeException();

    bool lt = false;
    unsigned int i = 0;

    while (i < a.size() && lt == false)
    {
        if (a[i] != b[i])
            return a[i] == bitset::bit::false_bit;
        i++;
    }

    return lt;
}

}

