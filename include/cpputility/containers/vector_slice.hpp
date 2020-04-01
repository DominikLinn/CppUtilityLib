/* NetSim Project - Numerical Simulation, Analysis and Optimization of District Heating Networks
 *
 * include/NetSim/Containers/VectorSlice.hpp
 *
 * created: 2019-12-13, Dominik Linn <d.linn@gmx.net> <dominik.linn@itwm.fraunhofer.de>
 *
 * (c) 2019 Dominik Linn, Fraunhofer ITWM
 *
 */

#ifndef CPPUTILITY_CONTAINERS_VECTORSLICE_HPP
#define CPPUTILITY_CONTAINERS_VECTORSLICE_HPP

#include <cstddef>
#include <memory>

#include <cpputility/containers/iterator.hpp>
#include <cpputility/containers/vector_base.hpp>

namespace cpputility
{
template<typename VectorT>
class VectorSlice : public VectorBase<VectorSlice<VectorT>, typename VectorT::value_type>
{
private:
    VectorT *m_base;
    ptrdiff_t m_start;
    ptrdiff_t m_stride;
    ptrdiff_t m_end;

public:
    using value_type = typename VectorT::value_type;

    VectorSlice() = delete;

    VectorSlice(VectorT &array, ptrdiff_t start, ptrdiff_t end, ptrdiff_t stride = 1)
        : m_base{array}, m_start{start}, m_stride{stride}, m_end{end}
    {
        // REQUIRE(start, ErrorHandling::isLessOrEqualTo, end);
        // REQUIRE(start, ErrorHandling::isGreaterOrEqualTo, size_t{0});
        // REQUIRE(end, isLessThan, array.size());
    }

    VectorSlice(const VectorSlice &other)
        : m_base{other.m_base}, m_start{other.m_start}, m_stride{other.m_stride}, m_end{other.m_end}
    {
    }

    VectorSlice(VectorSlice &&other)
        : m_base{std::move(other.m_base)}, m_start{std::move(other.m_start)},
          m_stride{other.m_stride}, m_end{std::move(other.m_end)}
    {
    }

    VectorSlice &operator=(const VectorSlice &other)
    {
        m_base = other.m_base;
        m_start = other.m_start;
        m_stride = other.m_stride;
        m_end = other.m_end;
        return *this;
    }

    VectorSlice &operator=(VectorSlice &&other)
    {
        if (this != &other) {
            m_base = std::move(other.m_base);
        }
        return *this;
    }

    inline size_t get_size() const { return (m_end - m_start) / m_stride; }

    inline value_type &get(ptrdiff_t pos) { return std::ref(m_base[m_start + m_stride * pos]); }

    inline value_type const &get(ptrdiff_t pos) const
    {
        return std::ref(m_base[m_start + m_stride * pos]);
    }

    inline value_type &get_front() { return get(0); }

    inline value_type const &get_front() const { return get(0); }

    inline value_type &get_back() { return get(this->size()); }

    inline value_type const &get_back() const { return get(this->size()); }

    virtual ~VectorSlice() = default;
};

{
private:
    VectorT *m_base;
    const ptrdiff_t m_start;
    const ptrdiff_t m_stride;
    const ptrdiff_t m_end;

public:
    using value_type = typename VectorT::value_type;

    ConstVectorSlice() = delete;

    ConstVectorSlice(VectorT &vec, ptrdiff_t start, ptrdiff_t end, ptrdiff_t stride = 1)
        : m_base{vec}, m_start{start}, m_stride{stride}, m_end{end}
    {
        // REQUIRE(start, ErrorHandling::isLessOrEqualTo, end);
        // REQUIRE(start, ErrorHandling::isGreaterOrEqualTo, size_t{0});
        // REQUIRE(end, isLessThan, array.size());
    }

    ConstVectorSlice(const ConstVectorSlice &other)
        : m_base{other.m_base}, m_start{other.m_start}, m_stride{other.m_stride}, m_end{other.m_end}
    {
    }

    ConstVectorSlice(ConstVectorSlice &&other)
        : m_base{std::move(other.m_base)}, m_start{std::move(other.m_start)},
          m_stride{other.m_stride}, m_end{std::move(other.m_end)}
    {
    }

    ConstVectorSlice &operator=(const ConstVectorSlice &other)
    {
        m_base = other.m_base;
        m_start = other.m_start;
        m_stride = other.m_stride;
        m_end = other.m_end;
        return *this;
    }

    ConstVectorSlice &operator=(ConstVectorSlice &&other)
    {
        if (this != &other) {
            m_base = std::move(other.m_base);
        }
        return *this;
    }

    inline size_t get_size() const { return (m_end - m_start) / m_stride; }

    inline value_type const &get(ptrdiff_t pos) const
    {
        return std::ref(m_base[m_start + m_stride * pos]);
    }

    inline value_type const &get_front() const { return get(0); }

    inline value_type const &get_back() const { return get(this->size()); }

    virtual ~ConstVectorSlice() = default;
};

template<typename VectorT>
auto slice(VectorT &vec, ptrdiff_t start, ptrdiff_t end, ptrdiff_t stride)

{
    static_assert(std::is_base_of_v<VectorBase<VectorT>, VectorT>);
    using Slice = VectorSlice<VectorT>;
    return Slice(vec, start, end, stride);
}

template<typename VectorT>
auto slice(VectorT const &vec, ptrdiff_t start, ptrdiff_t end, ptrdiff_t stride)
{
    static_assert(std::is_base_of_v<VectorBase<VectorT>, VectorT>);
    using Slice = ConstVectorSlice<VectorT>;
    return Slice(const_cast<VectorT &>(vec), start, end, stride);
}

template<typename VectorT>
auto const_slice(VectorT const &vec, ptrdiff_t start, ptrdiff_t end, ptrdiff_t stride)
{
    static_assert(std::is_base_of_v<VectorBase<VectorT>, VectorT>);
    using Slice = ConstVectorSlice<VectorT>;
    return Slice(const_cast<VectorT &>(vec), start, end, stride);
}

template<typename VectorT>
auto const_slice(VectorT &vec, ptrdiff_t start, ptrdiff_t end, ptrdiff_t stride)
{
    static_assert(std::is_base_of_v<VectorBase<VectorT>, VectorT>);
    using Slice = ConstVectorSlice<VectorT>;
    return Slice(vec, start, end, stride);
}
} // namespace cpputility

#endif // CPPUTILITY_CONTAINERS_VECTORSLICE_HPP
