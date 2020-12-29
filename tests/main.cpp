#include <iostream>
#include <maxcut/graph.hpp>
#include <maxcut/maxcut.hpp>
#include <maxcut/bruteforce.hpp>
#include <maxcut/half-optimal.hpp>

using graph::Graph;
using graph::maxcut::BruteForceMaxCut;
using graph::maxcut::DeterminateHalfOptimal;
using graph::maxcut::MaxCutSolver;
using graph::maxcut::RandomHalfOptimal;

int main() {
  size_t n, m;
  std::cin >> n >> m;
  Graph g(n);
  g.ReadGraph(m, true);

  BruteForceMaxCut brute_force(g);
  RandomHalfOptimal random_half_optimal(g);
  DeterminateHalfOptimal determinate_half_optimal(g);

  std::vector<std::pair<std::string, MaxCutSolver*>> solvers = {
      {"BruteForce", &brute_force},
      {"Random", &random_half_optimal},
      {"Greed", &determinate_half_optimal}};

  for (auto [name, solver] : solvers) {
    std::cout << name << "\n";
    std::cout << "Cut weight: " << solver->Solve() << "\n";
    std::cout << "Left:\n";
    for (size_t v = 0; v < g.Size(); ++v) {
      if (!solver->GetCut()[v]) {
        std::cout << v + 1 << " ";
      }
    }
    std::cout << "\n--------------------\n";
  }
  return 0;
}