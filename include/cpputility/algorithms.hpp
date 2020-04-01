/* NetSim Project - Numerical Simulation, Analysis and Optimization of District Heating Networks
 *
 * include/NetSim/Containers/Algorithms.hpp
 *
 * created: 2019-12-13, Dominik Linn <d.linn@gmx.net> <dominik.linn@itwm.fraunhofer.de>
 *
 * (c) 2019 Dominik Linn, Fraunhofer ITWM
 *
 */

#ifndef CPPUTILITY_ALGORITHMS_HPP
#define CPPUTILITY_ALGORITHMS_HPP

#include <algorithm>

namespace cpputility
{
template<typename Container, typename T>
auto find_element(const Container &c, const T &t)
{
    return std::find(c.begin(), c.end(), t);
}

template<typename Container, typename Predicate>
auto find_element_if(const Container &c, const Predicate &pred)
{
    return std::find_if(c.begin(), c.end(), pred);
}

template<typename Container, typename T>
bool has_element(const Container &c, const T &t)
{
    return (find_element(c, t) != c.end());
}

template<typename Container, typename Predicate>
bool has_element_if(const Container &c, const Predicate &pred)
{
    return (find_element_if(c, pred) != c.end());
}

template<typename Container, typename Operation>
void for_each(Container &container, Operation operation)
{
    for (auto &elem : container) {
        operation(elem);
    }
}

template<typename Container, typename Operation>
void for_each(const Container &container, Operation operation)
{
    for (const auto &elem : container) {
        operation(elem);
    }
}

template<typename Container, typename Operation>
void for_each(Container &&container, Operation operation)
{
    for (auto &&elem : container) {
        operation(elem);
    }
}

template<typename Iterator, typename Predicate, typename Operation>
void for_each_if(Iterator begin, Iterator end, Predicate pred, Operation op)
{
    for (; begin != end; ++begin) {
        if (pred(*begin)) {
            op(begin);
        }
    }
}

template<typename Container, typename Predicate, typename Operation>
void for_each_if(Container &container, Predicate pred, Operation op)
{
    for (auto &elem : container) {
        if (pred(elem)) {
            op(elem);
        }
    }
}

template<typename Container, typename Predicate, typename Operation>
void for_each_if(const Container &container, Predicate pred, Operation op)
{
    for (const auto &elem : container) {
        if (pred(elem)) {
            op(elem);
        }
    }
}

template<typename Container, typename Predicate, typename Operation>
void for_each_if(Container &&container, Predicate pred, Operation op)
{
    for (auto &&elem : container) {
        if (pred(elem)) {
            op(elem);
        }
    }
}

} // namespace cpputility

#endif // CPPUTILITY_ALGORITHMS_HPP
