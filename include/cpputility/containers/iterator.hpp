/* NetSim Project - Numerical Simulation, Analysis and Optimization of District Heating Networks
 *
 * netsim::utility
 * include/utilitylib/containers/iterator.hpp
 *
 * created: 2019-12-13, Dominik Linn <d.linn@gmx.net> <dominik.linn@itwm.fraunhofer.de>
 *
 * (c) 2019 Dominik Linn, Fraunhofer ITWM
 *
 */

#ifndef CPPUTILITY_CONTAINERS_ITERATOR_HPP
#define CPPUTILITY_CONTAINERS_ITERATOR_HPP

#include <cassert>
#include <cstddef>
#include <iterator>

namespace cpputility
{
using std::ptrdiff_t;
using std::size_t;

template<typename BaseT, typename RangeT>
class Iterator : public std::iterator<std::random_access_iterator_tag, BaseT>
{
private:
    RangeT &m_range;
    size_t m_pos;

public:
    Iterator() = delete;
    explicit Iterator(RangeT &range, size_t start = 0) : m_range{range}
    {
        assert(start <= m_range.size());
        m_pos = start;
    }

    Iterator &operator++()
    {
        if (m_pos < m_range.size()) {
            ++m_pos;
        }
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator copy = *this;
        if (m_pos < m_range.size()) {
            ++m_pos;
        }
        return copy;
    }

    Iterator &operator+=(ptrdiff_t difference)
    {
        m_pos += difference;
        return *this;
    }

    Iterator operator+(int movement)
    {
        auto oldPos = m_pos;
        m_pos += movement;
        auto temp = *this;
        m_pos = oldPos;
        return temp;
    }

    Iterator &operator--()
    {
        if (m_pos > 0) {
            --m_pos;
        }
        return *this;
    }

    Iterator operator--(int)
    {
        Iterator copy = *this;
        if (m_pos > 0) {
            --m_pos;
        }
        return copy;
    }

    Iterator &operator-=(ptrdiff_t difference)
    {
        m_pos -= difference;
        return *this;
    }

    Iterator operator-(int movement)
    {
        auto oldPos = m_pos;
        m_pos -= movement;
        auto temp = *this;
        m_pos = oldPos;
        return temp;
    }

    ptrdiff_t operator-(const Iterator &iter)
    {
        return static_cast<ptrdiff_t>(this->getPos() - iter.getPos());
    }

    inline bool is_comparable(const Iterator &rhs) const
    {
        return (&m_range == &rhs.m_range) && (m_range.size() == rhs.m_range.size());
    }

    bool operator==(const Iterator &rhs) const
    {
        return is_comparable(rhs) && (m_pos == rhs.m_pos);
    }

    bool operator!=(const Iterator &rhs) const
    {
        return !is_comparable(rhs) || (m_pos != rhs.m_pos);
    }

    bool operator<(const Iterator &rhs) const { return is_comparable(rhs) && (m_pos < rhs.m_pos); }

    bool operator<=(const Iterator &rhs) const
    {
        return is_comparable(rhs) && (m_pos <= rhs.m_pos);
    }

    bool operator>(const Iterator &rhs) const { return is_comparable(rhs) && (m_pos > rhs.m_pos); }

    bool operator>=(const Iterator &rhs) const
    {
        return is_comparable(rhs) && (m_pos >= rhs.m_pos);
    }

    BaseT &operator*() { return m_range[m_pos]; }

    const BaseT &operator*() const { return m_range[m_pos]; }

    BaseT *operator->() { return &m_range[m_pos]; }

    BaseT *getPtr() const { return &m_range[m_pos]; }

    size_t getPos() const { return m_pos; }

    const BaseT *getConstPtr() const { return &m_range[m_pos]; }
};

template<typename BaseT, typename RangeT>
class ConstIterator : public std::iterator<std::random_access_iterator_tag, BaseT>
{
private:
    const RangeT &m_range;
    size_t m_pos;

public:
    ConstIterator() = delete;
    ConstIterator(const RangeT &range, size_t start = 0) : m_range{range}
    {
        assert(start <= m_range.size());
        m_pos = start;
    }

    ConstIterator &operator++()
    {
        if (m_pos < m_range.size()) {
            ++m_pos;
        }
        return *this;
    }

    ConstIterator operator++(int)
    {
        ConstIterator copy = *this;
        if (m_pos < m_range.size()) {
            ++m_pos;
        }
        return copy;
    }

    ConstIterator &operator+=(ptrdiff_t difference)
    {
        m_pos += difference;
        return *this;
    }

    ConstIterator operator+(int movement)
    {
        auto oldPos = m_pos;
        m_pos += movement;
        auto temp = *this;
        m_pos = oldPos;
        return temp;
    }

    ConstIterator &operator--()
    {
        if (m_pos > 0) {
            --m_pos;
        }
        return *this;
    }

    ConstIterator operator--(int)
    {
        ConstIterator copy = *this;
        if (m_pos > 0) {
            --m_pos;
        }
        return copy;
    }

    ConstIterator &operator-=(ptrdiff_t difference)
    {
        m_pos -= difference;
        return *this;
    }

    ConstIterator operator-(int movement)
    {
        auto oldPos = m_pos;
        m_pos -= movement;
        auto temp = *this;
        m_pos = oldPos;
        return temp;
    }

    ptrdiff_t operator-(const ConstIterator &iter)
    {
        return static_cast<ptrdiff_t>(this->getPos() - iter.getPos());
    }

    inline bool is_comparable(const ConstIterator &rhs) const
    {
        return (&m_range == &rhs.m_range) && (m_range.size() == rhs.m_range.size());
    }

    bool operator==(const ConstIterator &rhs) const
    {
        return is_comparable(rhs) && (m_pos == rhs.m_pos);
    }

    bool operator!=(const ConstIterator &rhs) const
    {
        return !is_comparable(rhs) || (m_pos != rhs.m_pos);
    }

    bool operator<(const ConstIterator &rhs) const
    {
        return is_comparable(rhs) && (m_pos < rhs.m_pos);
    }

    bool operator<=(const ConstIterator &rhs) const
    {
        return is_comparable(rhs) && (m_pos <= rhs.m_pos);
    }

    bool operator>(const ConstIterator &rhs) const
    {
        return is_comparable(rhs) && (m_pos > rhs.m_pos);
    }

    bool operator>=(const ConstIterator &rhs) const
    {
        return is_comparable(rhs) && (m_pos >= rhs.m_pos);
    }

    const BaseT &operator*() { return m_range[m_pos]; }

    const BaseT &operator*() const { return m_range[m_pos]; }

    const BaseT *operator->() { return &m_range[m_pos]; }

    size_t getPos() const { return m_pos; }

    const BaseT *getPtr() const { return &m_range[m_pos]; }

    const BaseT *getConstPtr() const { return &m_range[m_pos]; }
};
} // namespace cpputility
#endif // CPPUTILITY_CONTAINERS_ITERATOR_HPP
