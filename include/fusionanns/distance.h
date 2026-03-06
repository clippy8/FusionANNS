#pragma once

#include "fusionanns/vector.h"

namespace fusionanns {

float l2_distance(const Vector& a, const Vector& b);
float inner_product(const Vector& a, const Vector& b);

}  // namespace fusionanns
