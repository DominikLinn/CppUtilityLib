#ifndef CPPUTILITY_CONTAINERS_VECTOR_BASE_HPP
#define CPPUTILITY_CONTAINERS_VECTOR_BASE_HPP

#include <cpputility/containers/iterator.hpp>
#include <cstddef>

namespace cpputility
{
template<typename Derived, typename ValueT>
class VectorBase
{
public:
    using value_type = ValueT;
    using const_iterator = ConstIterator<value_type, VectorBase<Derived, ValueT>>;
    using iterator = Iterator<value_type, VectorBase<Derived, ValueT>>;

public:
    value_type &operator[](ptrdiff_t pos)
    {
        Derived &derivedObject = static_cast<Derived &>(*this);
        return derivedObject.get(pos);
    }

    value_type const &operator[](ptrdiff_t pos) const
    {
        Derived const &derivedObject = static_cast<Derived const &>(*this);
        return derivedObject.get(pos);
    }

    value_type &front()
    {
        Derived &derivedObject = static_cast<Derived &>(*this);
        return derivedObject.get_front();
    }

    value_type const &front() const
    {
        Derived const &derivedObject = static_cast<Derived const &>(*this);
        return derivedObject.get_front();
    }

    value_type &back()
    {
        Derived &derivedObject = static_cast<Derived &>(*this);
        return derivedObject.get_back();
    }

    value_type const &back() const
    {
        Derived const &derivedObject = static_cast<Derived const &>(*this);
        return derivedObject.get_back();
    }

    inline ptrdiff_t size() const
    {
        Derived const &derivedObject = static_cast<Derived const &>(*this);
        return derivedObject.get_size();
    }

    inline bool empty() const { return size() == 0; }

    auto begin() { return iterator(*this); }
    auto begin() const { return const_iterator(*this); }
    auto cbegin() const { return const_iterator(*this); }

    auto end() { return iterator(*this, size()); }
    auto end() const { return const_iterator(*this, size()); }
    auto cend() const { return const_iterator(*this, size()); }
};

template<typename Derived, typename ValueT>
class ConstVectorBase
{
public:
    using value_type = ValueT;
    using const_iterator = ConstIterator<value_type, ConstVectorBase<Derived, ValueT>>;
    using iterator = Iterator<value_type, ConstVectorBase<Derived, ValueT>>;

public:
    value_type const &operator[](ptrdiff_t pos) const
    {
        auto const &derivedObject = static_cast<Derived const &>(*this);
        return derivedObject.get(pos);
    }

    value_type const &front() const
    {
        Derived const &derivedObject = static_cast<Derived const &>(*this);
        return derivedObject.get_front();
    }

    value_type const &back() const
    {
        Derived const &derivedObject = static_cast<Derived const &>(*this);
        return derivedObject.get_back();
    }

    inline ptrdiff_t size() const
    {
        auto const &derivedObject = static_cast<Derived const &>(*this);
        return derivedObject.get_size();
    }

    inline bool empty() const { return size() == 0; }

    auto begin() const { return const_iterator(*this); }
    auto cbegin() const { return const_iterator(*this); }

    auto end() const { return const_iterator(*this, size()); }
    auto cend() const { return const_iterator(*this, size()); }
};
} // namespace cpputility

namespace std
{
template<typename Derived, typename ValueT>
auto begin(cpputility::VectorBase<Derived, ValueT> &vec)
{
    return vec.begin();
}

template<typename Derived, typename ValueT>
auto begin(cpputility::VectorBase<Derived, ValueT> const &vec)
{
    return vec.begin();
}

template<typename Derived, typename ValueT>
auto end(cpputility::VectorBase<Derived, ValueT> &vec)
{
    return vec.end();
}

template<typename Derived, typename ValueT>
auto end(cpputility::VectorBase<Derived, ValueT> const &vec)
{
    return vec.end();
}

template<typename Derived, typename ValueT>
auto begin(cpputility::ConstVectorBase<Derived, ValueT> &vec)
{
    return vec.begin();
}

template<typename Derived, typename ValueT>
auto end(cpputility::ConstVectorBase<Derived, ValueT> &vec)
{
    return vec.end();
}

template<typename Derived, typename ValueT>
auto begin(cpputility::ConstVectorBase<Derived, ValueT> const &vec)
{
    return vec.begin();
}

template<typename Derived, typename ValueT>
auto end(cpputility::ConstVectorBase<Derived, ValueT> const &vec)
{
    return vec.end();
}
} // namespace std
#endif // CPPUTILITY_CONTAINERS_VECTOR_BASE_HPP
