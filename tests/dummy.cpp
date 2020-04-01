#include <cpputility/containers/storage_vector.hpp>
#include <cpputility/containers/vector_view.hpp>
#include <iostream>
#include <typeinfo>
#include <vector>

int main(int, char **)
{
    cpputility::StorageVector<double> vs;

    std::vector<double> v{1.0, 2.0, 3.0};

    for (auto val : v) {
        vs.emplace_back(std::make_unique<double>(val));
    }
    auto vv = cpputility::VectorView(vs);

    std::cout << typeid(vv).name() << std::endl;
    std::cout << vv[0] << std::endl;
    for (auto &val : vv) {
        val += 3;
    }

    for (auto &val : vs) {
        std::cout << val << std::endl;
    }

    return 1;
}
