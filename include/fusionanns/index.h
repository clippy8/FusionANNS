#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "fusionanns/vector.h"

namespace fusionanns {

class Index {
public:
    virtual ~Index() = default;

    virtual void add(const Vector& v) = 0;
    virtual std::size_t search(
        const Vector& query,
        std::size_t k,
        std::vector<std::size_t>& results
    ) const = 0;
};

std::unique_ptr<Index> make_flat_index();

}  // namespace fusionanns
