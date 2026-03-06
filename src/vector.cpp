#include "fusionanns/vector.h"

#include <stdexcept>
#include <utility>

namespace fusionanns {

Vector::Vector(std::size_t dim) : data_(dim, 0.0F) {}

Vector::Vector(std::vector<float> data) : data_(std::move(data)) {
    if (data_.empty()) {
        throw std::invalid_argument("Vector must have positive dimension");
    }
}

std::size_t Vector::dim() const noexcept {
    return data_.size();
}

float Vector::operator[](std::size_t i) const {
    return data_.at(i);
}

float& Vector::operator[](std::size_t i) {
    return data_.at(i);
}

}  // namespace fusionanns
