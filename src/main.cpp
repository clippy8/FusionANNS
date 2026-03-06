#include <cstddef>
#include <iostream>
#include <vector>

#include "fusionanns/index.h"
#include "fusionanns/vector.h"

int main() {
    using fusionanns::Vector;

    auto index = fusionanns::make_flat_index();
    index->add(Vector(std::vector<float>{1.0F, 0.0F, 0.0F}));
    index->add(Vector(std::vector<float>{0.0F, 1.0F, 0.0F}));
    index->add(Vector(std::vector<float>{0.0F, 0.0F, 1.0F}));
    index->add(Vector(std::vector<float>{0.8F, 0.1F, 0.0F}));

    const Vector query(std::vector<float>{0.9F, 0.0F, 0.0F});

    std::vector<std::size_t> results;
    const std::size_t found = index->search(query, 2, results);

    std::cout << "Query nearest neighbors (k=2):\n";
    for (std::size_t i = 0; i < found; ++i) {
        std::cout << "  rank " << (i + 1) << ": index #" << results[i] << '\n';
    }

    return 0;
}
