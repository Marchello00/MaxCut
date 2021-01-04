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

void Test(std::istream& in = std::cin, bool bruteforce = false,
          bool random = false, bool greed = false,
          bool goemans_williamson = false) {
  size_t n, m;
  in >> n >> m;
  Graph g(n);
  g.ReadGraph(m, true, in);

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
    auto cut_weight = solver->Solve();
    std::cout << name << ": " << cut_weight << "\n";
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
  Test(in, bruteforce, random, greed, goemans_williamson);
  return 0;
}