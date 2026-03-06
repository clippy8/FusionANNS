#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

#include "fusionanns/distance.h"
#include "fusionanns/index.h"
#include "fusionanns/vector.h"

int main() {
    using fusionanns::Vector;

    const Vector a(std::vector<float>{1.0F, 2.0F, 3.0F});
    const Vector b(std::vector<float>{1.0F, 2.0F, 5.0F});

    const float d = fusionanns::l2_distance(a, b);
    assert(d == 4.0F);

    auto index = fusionanns::make_flat_index();
    index->add(Vector(std::vector<float>{1.0F, 0.0F}));
    index->add(Vector(std::vector<float>{0.0F, 1.0F}));
    index->add(Vector(std::vector<float>{0.9F, 0.1F}));

    std::vector<std::size_t> results;
    const std::size_t found = index->search(Vector(std::vector<float>{1.0F, 0.0F}), 1, results);

    assert(found == 1);
    assert(results.size() == 1);
    assert(results[0] == 0);

    std::cout << "basic_test passed\n";
    return 0;
}
