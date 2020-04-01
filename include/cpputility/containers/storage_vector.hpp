/* NetSim Project - Numerical Simulation, Analysis and Optimization of District Heating Networks
 *
 * include/NetSim/Containers/StorageVector.hpp
 *
 * created: 2019-12-13, Dominik Linn <d.linn@gmx.net> <dominik.linn@itwm.fraunhofer.de>
 *
 * (c) 2019 Dominik Linn, Fraunhofer ITWM
 *
 */

#ifndef CPPUTILITY_STORAGE_VECTOR_HPP
#define CPPUTILITY_STORAGE_VECTOR_HPP

#include <memory>
#include <vector>

#include <cpputility/containers/iterator.hpp>
#include <cpputility/containers/vector_base.hpp>

namespace cpputility
{
template<typename BaseT, typename DelT = std::default_delete<BaseT>>
class StorageVector : public VectorBase<StorageVector<BaseT, DelT>, BaseT>
{
public:
    using const_iterator = ConstIterator<BaseT, StorageVector<BaseT, DelT>>;
    using iterator = Iterator<BaseT, StorageVector<BaseT, DelT>>;
    using value_type = BaseT;

private:
    std::vector<std::unique_ptr<BaseT, DelT>> m_objects;

public:
    StorageVector() = default;
    StorageVector(StorageVector &&other) : m_objects{std::move(other.m_objects)} {}
    StorageVector(std::vector<std::unique_ptr<BaseT, DelT>> &&other) : m_objects{std::move(other)}
    {
    }
    StorageVector(StorageVector const &rhs) = delete;

    StorageVector &operator=(StorageVector &&rhs)
    {
        m_objects = std::move(rhs.m_objects);
        return *this;
    }

    StorageVector &operator=(StorageVector const &rhs) = delete;

    virtual ~StorageVector() = default;

    StorageVector clone() const
    {
        StorageVector result;
        for (BaseT const &elem : *this) {
            result.emplace_back(std::make_unique<BaseT>(elem));
        }

        return result;
    }

    BaseT &get(size_t pos) const
    {
        assert(pos < this->size());
        return *m_objects[pos].get();
    }

    BaseT &get_front() const
    {
        assert(!this->empty());
        return *m_objects.front().get();
    }

    BaseT &get_back() const
    {
        assert(!this->empty());
        return *m_objects.back().get();
    }

    inline size_t get_size() const { return m_objects.size(); }

    void clear() { m_objects.clear(); }

    void emplace_back(std::unique_ptr<BaseT, DelT> &&value)
    {
        m_objects.emplace_back(std::move(value));
    }

    void emplace(iterator &position, std::unique_ptr<BaseT, DelT> &&value)
    {
        auto pos = position - this->begin();
        m_objects.emplace(pos, move(value));
    }

    //        template <typename ...Args>
    //        void emplace_back(Args ...args)
    //        {
    //            m_objects.emplace_back(std::make_unique<BaseT>(args...));
    //        }
};
} // namespace cpputility

#endif // CPPUTILITY_STORAGE_VECTOR_HPP
