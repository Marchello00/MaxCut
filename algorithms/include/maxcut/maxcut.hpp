#pragma once

#include "include/maxcut/graph.hpp"

namespace graph::maxcut {

class MaxCutSolver {
 public:
  MaxCutSolver(const Graph& graph) : graph_(graph) {
  }

  WeightT Solve();

 private:
  const Graph& graph_;
};

}  // namespace graph::maxcut