/* NetSim Project - Numerical Simulation, Analysis and Optimization of District Heating Networks
 *
 * include/NetSim/Containers/VectorView.hpp
 *
 * created: 2019-12-13, Dominik Linn <d.linn@gmx.net> <dominik.linn@itwm.fraunhofer.de>
 *
 * (c) 2019 Dominik Linn, Fraunhofer ITWM
 *
 */

#ifndef CPPUTILITY_VECTOR_VIEW_HPP
#define CPPUTILITY_VECTOR_VIEW_HPP

#include <cstddef>
#include <memory>

#include <cpputility/containers/iterator.hpp>
#include <cpputility/containers/vector_base.hpp>

namespace cpputility
{
template<class VectorT>
class VectorView : public VectorBase<VectorView<VectorT>>
{
private:
    VectorT *m_base;

public:
    using value_type = typename VectorT::value_type;

    VectorView() = delete;

    VectorView(VectorT &array) : m_base{array} {}

    VectorView(VectorView const &other) : m_base{other.m_base} {}

    VectorView(VectorView &&other) : m_base{std::move(other.m_base)} {}

    VectorView &operator=(const VectorView &other)
    {
        m_base = other.m_base;
        return *this;
    }

    VectorView &operator=(VectorView &&other)
    {
        if (this != &other) {
            m_base = std::move(other.m_base);
        }
        return *this;
    }

    inline value_type &get(ptrdiff_t pos) { return std::ref(m_base[pos]); }

    inline value_type const &get(ptrdiff_t pos) const { return std::ref(m_base[pos]); }

    inline value_type &get_front() { return std::ref(m_base->front()); }

    inline value_type const &get_front() const { return std::ref(m_base->front()); }

    inline value_type &get_back() { return std::ref(m_base->back()); }

    inline value_type const &get_back() const { return std::ref(m_base->back()); }

    inline ptrdiff_t get_size() const { return m_base->size(); }

    virtual ~VectorView() = default;
};

template<class VectorT>
class ConstVectorView : public ConstVectorBase<VectorView<VectorT>>
{
private:
    VectorT *m_base;

public:
    using value_type = typename VectorT::value_type;

    ConstVectorView() = delete;

    ConstVectorView(VectorT &array) : m_base{array} {}

    ConstVectorView(ConstVectorView const &other) : m_base{other.m_base} {}

    ConstVectorView(ConstVectorView &&other) : m_base{std::move(other.m_base)} {}

    ConstVectorView &operator=(const ConstVectorView &other)
    {
        m_base = other.m_base;
        return *this;
    }

    ConstVectorView &operator=(ConstVectorView &&other)
    {
        if (this != &other) {
            m_base = std::move(other.m_base);
        }
        return *this;
    }

    inline value_type const &get(ptrdiff_t pos) const { return std::ref(m_base[pos]); }

    inline value_type const &get_front() const { return std::ref(m_base->front()); }

    inline value_type const &get_back() const { return std::ref(m_base->back()); }

    inline ptrdiff_t get_size() const { return m_base->size(); }

    virtual ~ConstVectorView() = default;
};
} // namespace cpputility
#endif // CPPUTILITY_CONTAINERS_VECTOR_VIEW_HPP
