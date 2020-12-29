#pragma once

#include "maxcut.hpp"

namespace graph::maxcut {

class BruteForceMaxCut : public MaxCutSolver {
 public:
  BruteForceMaxCut(const Graph& graph);

 protected:
  WeightT Solve_() override;

 private:
  std::vector<bool> MaskToVector(unsigned mask);
};

}  // namespace graph::maxcut