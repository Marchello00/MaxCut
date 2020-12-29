#pragma once

#include "maxcut.hpp"

#include <random>

namespace graph::maxcut {

// Half-optimal guarantee only with edges of weight 1
class RandomHalfOptimal : public MaxCutSolver {
 public:
  RandomHalfOptimal(const Graph& graph, unsigned seed = 0);

 protected:
  WeightT Solve_() override;

 private:
  unsigned seed_;
};

// Half-optimal guarantee only with edges of weight 1
class DeterminateHalfOptimal : public MaxCutSolver {
 public:
  DeterminateHalfOptimal(const Graph& graph);

 protected:
  WeightT Solve_() override;
};

}  // namespace graph::maxcut