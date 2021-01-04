#include "include/maxcut/half-optimal.hpp"

graph::maxcut::RandomHalfOptimal::RandomHalfOptimal(const graph::Graph& graph,
                                                    unsigned seed)
    : MaxCutSolver(graph), seed_(seed) {
}

graph::WeightT graph::maxcut::RandomHalfOptimal::Solve_() {
  std::mt19937 rng(seed_);
  auto max_found_weight = kMinWeight;
  for (int repeat = 0; repeat < 15; ++repeat) {
    std::vector<bool> current_answer(graph_.Size());
    for (unsigned v = 0; v < graph_.Size(); ++v) {
      current_answer[v] = rng() & 1;
    }
    auto current_weight = GetCutWeight(current_answer);
    if (current_weight >= max_found_weight) {
      max_found_weight = current_weight;
      answer_ = current_answer;
    }
  }
  return GetCutWeight(GetCut());
}

graph::maxcut::DeterminateHalfOptimal::DeterminateHalfOptimal(
    const graph::Graph& graph)
    : MaxCutSolver(graph) {
}

graph::WeightT graph::maxcut::DeterminateHalfOptimal::Solve_() {
  for (size_t v = 0; v < graph_.Size(); ++v) {
    size_t left_neighbours = 0;
    size_t right_neighbours = 0;
    for (auto& edge : graph_[v]) {
      if (edge.to > v) {
        continue;
      }
      left_neighbours += !answer_[edge.to];
      right_neighbours += answer_[edge.to];
    }
    answer_[v] = left_neighbours > right_neighbours;
  }
  return GetCutWeight(GetCut());
}
