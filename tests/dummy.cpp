#include <cpputility/containers/storage_vector.hpp>
#include <cpputility/containers/vector_slice.hpp>
#include <cpputility/containers/vector_view.hpp>
#include <iostream>
#include <typeinfo>
#include <vector>

int main(int, char **)
{
    cpputility::StorageVector<double> vs;

    std::vector<double> v{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    for (auto val : v) {
        vs.emplace_back(std::make_unique<double>(val));
    }
    auto vsl = cpputility::slice(vs, 1, vs.size(), 2);

    auto vcsl = cpputility::slice(vs, 0, vs.size(), 2);

    for (auto &val : vsl) {
        val = 0;
    }

    for (auto &val : vs) {
        std::cout << val << std::endl;
    }

    for (auto &val : vcsl) {
        std::cout << val << std::endl;
    }

    return 1;
}
