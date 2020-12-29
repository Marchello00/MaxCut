#pragma once

#include "graph.hpp"

namespace graph::maxcut {

class MaxCutSolver {
 public:
  MaxCutSolver(const Graph& graph);

  WeightT Solve();

  const std::vector<bool>& GetCut() const;

  WeightT GetCutWeight(const std::vector<bool>& cut) const;

 protected:
  virtual WeightT Solve_() = 0;

 protected:
  const Graph& graph_;

  std::vector<bool> answer_;  // 0 if in left part of cut, else 1

 private:
  bool solved_;
};

}  // namespace graph::maxcut