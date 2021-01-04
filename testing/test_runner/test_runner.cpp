#include <iostream>
#include <maxcut/graph.hpp>
#include <maxcut/maxcut.hpp>
#include <maxcut/bruteforce.hpp>
#include <maxcut/half-optimal.hpp>
#include <maxcut/goemans-williamson.hpp>
#include <fstream>

using graph::Graph;
using graph::maxcut::BruteForceMaxCut;
using graph::maxcut::DeterminateHalfOptimal;
using graph::maxcut::GoemansWilliamson;
using graph::maxcut::MaxCutSolver;
using graph::maxcut::RandomHalfOptimal;

void Solve(std::istream& in = std::cin, bool bruteforce = false,
           bool random = false, bool greed = false,
           bool goemans_williamson = false) {
  size_t n, m;
  in >> n >> m;
  Graph g(n);
  g.ReadGraph(m, true, in);

  // Only for analyse
  graph::WeightT max_cut_hint;
  if (in >> max_cut_hint) {
    std::cout << "Known lower bound: " << max_cut_hint << "\n";
  }
  graph::WeightT upper_bound = 0;
  graph::WeightT negative_weight = 0;
  for (size_t v = 0; v < g.Size(); ++v) {
    for (auto& e : g[v]) {
      if (e.weight > 0) {
        upper_bound += e.weight;
      } else {
        negative_weight += e.weight;
      }
    }
  }
  std::cout << "Known upper bound: " << upper_bound << "\n";
  std::cout << "Negative weight: " << negative_weight << "\n";

  BruteForceMaxCut brute_force(g);
  RandomHalfOptimal random_half_optimal(g);
  DeterminateHalfOptimal determinate_half_optimal(g);
  GoemansWilliamson goemans_williamson_solver(g, 0);

  std::vector<std::pair<std::string, MaxCutSolver*>> solvers;

  if (bruteforce) {
    solvers.emplace_back("BruteForce", &brute_force);
  }
  if (random) {
    solvers.emplace_back("Random", &random_half_optimal);
  }
  if (greed) {
    solvers.emplace_back("Greed", &determinate_half_optimal);
  }
  if (goemans_williamson) {
    solvers.emplace_back("Goemans-Williamson", &goemans_williamson_solver);
  }

  for (auto [name, solver] : solvers) {
    auto start_time = clock();
    auto cut_weight = solver->Solve();
    auto finish_time = clock();
    auto required_time = double(finish_time - start_time) / CLOCKS_PER_SEC;
    std::cout << name << " (answer): " << cut_weight << "\n";
    std::cout << name << " (time, sec): " << std::fixed << std::setprecision(5)
              << required_time << "\n";
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\n\t" << argv[0]
              << " <input file> [--bruteforce] [--random] [--greed] "
                 "[--goemans-williamson]\n";
  }
  std::string input_file(argv[1]);
  bool bruteforce = false;
  bool random = false;
  bool greed = false;
  bool goemans_williamson = false;
  for (int i = 2; i < argc; ++i) {
    std::string arg(argv[i]);
    if (arg == "--bruteforce") {
      bruteforce = true;
    }
    if (arg == "--random") {
      random = true;
    }
    if (arg == "--greed") {
      greed = true;
    }
    if (arg == "--goemans-williamson") {
      goemans_williamson = true;
    }
  }
  std::fstream in(input_file, std::fstream::in);
  Solve(in, bruteforce, random, greed, goemans_williamson);
  return 0;
}