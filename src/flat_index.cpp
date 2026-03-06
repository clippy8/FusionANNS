#include "fusionanns/index.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "fusionanns/distance.h"

namespace fusionanns {

class FlatIndex final : public Index {
public:
    void add(const Vector& v) override {
        if (!vectors_.empty() && vectors_.front().dim() != v.dim()) {
            throw std::invalid_argument("All vectors in index must share the same dimension");
        }
        vectors_.push_back(v);
    }

    std::size_t search(
        const Vector& query,
        std::size_t k,
        std::vector<std::size_t>& results
    ) const override {
        results.clear();
        if (vectors_.empty() || k == 0) {
            return 0;
        }
        if (query.dim() != vectors_.front().dim()) {
            throw std::invalid_argument("Query dimension does not match index dimension");
        }

        const std::size_t result_count = std::min(k, vectors_.size());
        std::vector<std::pair<float, std::size_t>> distances;
        distances.reserve(vectors_.size());

        for (std::size_t i = 0; i < vectors_.size(); ++i) {
            distances.emplace_back(l2_distance(query, vectors_[i]), i);
        }

        std::partial_sort(
            distances.begin(),
            distances.begin() + static_cast<std::ptrdiff_t>(result_count),
            distances.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; }
        );

        results.reserve(result_count);
        for (std::size_t i = 0; i < result_count; ++i) {
            results.push_back(distances[i].second);
        }
        return results.size();
    }

private:
    std::vector<Vector> vectors_;
};

std::unique_ptr<Index> make_flat_index() {
    return std::make_unique<FlatIndex>();
}

}  // namespace fusionanns
