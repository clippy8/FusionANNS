#include "fusionanns/distance.h"

#include <stdexcept>

namespace fusionanns {

namespace {

void ensure_same_dim(const Vector& a, const Vector& b) {
    if (a.dim() != b.dim()) {
        throw std::invalid_argument("Vectors must have the same dimension");
    }
}

}  // namespace

float l2_distance(const Vector& a, const Vector& b) {
    ensure_same_dim(a, b);

    float sum = 0.0F;
    for (std::size_t i = 0; i < a.dim(); ++i) {
        const float diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sum;
}

float inner_product(const Vector& a, const Vector& b) {
    ensure_same_dim(a, b);

    float sum = 0.0F;
    for (std::size_t i = 0; i < a.dim(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

}  // namespace fusionanns
