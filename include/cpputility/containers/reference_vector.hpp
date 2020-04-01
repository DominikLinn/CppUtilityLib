/* NetSim Project - Numerical Simulation, Analysis and Optimization of District Heating Networks
 *
 * include/NetSim/Containers/Algorithms.hpp
 *
 * created: 2019-12-13, Dominik Linn <d.linn@gmx.net> <dominik.linn@itwm.fraunhofer.de>
 *
 * (c) 2019 Dominik Linn, Fraunhofer ITWM
 *
 */

#ifndef CPPUTILITY_CONTAINERS_REFERENCE_VECTOR_HPP
#define CPPUTILITY_CONTAINERS_REFERENCE_VECTOR_HPP

#include <algorithm>
#include <functional>
#include <vector>

#include <cpputility/algorithms.hpp>
#include <cpputility/containers/vector_base.hpp>

namespace cpputility
{
template<typename BaseT>
class ReferenceVector : public VectorBase<ReferenceVector<BaseT>, BaseT>
{
private:
    std::vector<std::reference_wrapper<BaseT>> m_refs;

public:
    using value_type = BaseT;
    using reference_type = BaseT &;

    inline size_t get_size() const { return m_refs.size(); }

    inline value_type &get(ptrdiff_t pos) { return std::ref(m_refs[pos]); }

    inline value_type const &get(ptrdiff_t pos) const { return std::ref(m_refs[pos]); }

    inline value_type &get_front() { return get(0); }

    inline value_type const &get_front() const { return get(0); }

    inline value_type &get_back() { return get(this->size()); }

    inline value_type const &get_back() const { return get(this->size()); }

    ReferenceVector() = default;

    ReferenceVector(ReferenceVector const &other) : m_refs{other.m_refs} {}

    ReferenceVector(ReferenceVector &&other) : m_refs{std::move(other.m_refs)} {}

    ReferenceVector &operator=(ReferenceVector const &rhs)
    {
        std::copy(rhs.m_refs.begin(), rhs.m_refs.end(), m_refs.begin());
        return *this;
    }

    ReferenceVector &operator=(ReferenceVector &&rhs)
    {
        if (*this != &rhs) {
            m_refs = std::move(rhs.m_refs);
        }
        return *this;
    }

    virtual ~ReferenceVector() = default;

    void clear() { m_refs.clear(); }

    void remove(BaseT const &value)
    {
        auto valueIter = find_element_if(m_refs, [&value](BaseT const &obj) -> bool {
            return &obj == &value;
        });

        if (valueIter != m_refs.end()) {
            m_refs.erase(valueIter);
        }
    }

    void emplace_back(BaseT &value) { m_refs.emplace_back(std::ref(value)); }
};

} // namespace cpputility
#endif // CPPUTILITY_CONTAINERS_REFERENCE_VECTOR_HPP
