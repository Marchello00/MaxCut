#include "include/maxcut/maxcut.hpp"

graph::maxcut::MaxCutSolver::MaxCutSolver(const graph::Graph& graph)
    : graph_(graph), answer_(graph_.Size(), false), solved_(false) {
}

const std::vector<bool>& graph::maxcut::MaxCutSolver::GetCut() const {
  if (!solved_) {
    throw std::runtime_error("Call Solve() before getting answer");
  }
  return answer_;
}

graph::WeightT graph::maxcut::MaxCutSolver::GetCutWeight(
    const std::vector<bool>& cut) const {
  WeightT weight = 0;
  for (size_t v = 0; v < graph_.Size(); ++v) {
    if (!cut[v]) {
      for (auto& edge : graph_[v]) {
        if (cut[edge.to]) {
          weight += edge.weight;
        }
      }
    }
  }
  return weight;
}

graph::WeightT graph::maxcut::MaxCutSolver::Solve() {
  solved_ = true;
  return Solve_();
}
