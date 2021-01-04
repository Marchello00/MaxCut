#pragma once

#include "maxcut.hpp"

#include <random>

namespace graph::maxcut {

class GoemansWilliamson : public MaxCutSolver {
 public:
  GoemansWilliamson(const Graph& graph, unsigned seed = 0);

 protected:
  WeightT Solve_() override;

 private:
  void RandomSplit(const std::vector<double>& coordinates);

 private:
  unsigned seed_;
};

}  // namespace graph::maxcut