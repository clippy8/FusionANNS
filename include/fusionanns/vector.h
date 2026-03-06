#pragma once

#include <cstddef>
#include <vector>

namespace fusionanns {

class Vector {
public:
    explicit Vector(std::size_t dim);
    explicit Vector(std::vector<float> data);

    std::size_t dim() const noexcept;
    float operator[](std::size_t i) const;
    float& operator[](std::size_t i);

private:
    std::vector<float> data_;
};

}  // namespace fusionanns
