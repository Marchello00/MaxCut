#include "include/maxcut/bruteforce.hpp"
#include "include/maxcut/weight.hpp"

graph::maxcut::BruteForceMaxCut::BruteForceMaxCut(const graph::Graph& graph)
    : MaxCutSolver(graph) {
}

graph::WeightT graph::maxcut::BruteForceMaxCut::Solve_() {
  WeightT best_weight = kMinWeight;
  for (unsigned mask = 0; mask < (1ULL << graph_.Size()); ++mask) {
    auto cut = MaskToVector(mask);
    auto cut_weight = GetCutWeight(cut);
    if (cut_weight > best_weight) {
      best_weight = cut_weight;
      answer_ = cut;
    }
  }
  return best_weight;
}
std::vector<bool> graph::maxcut::BruteForceMaxCut::MaskToVector(
    unsigned int mask) {
  std::vector<bool> vec(graph_.Size(), false);
  for (size_t i = 0; i < graph_.Size(); ++i) {
    vec[i] = (mask >> i) & 1;
  }
  return vec;
}
