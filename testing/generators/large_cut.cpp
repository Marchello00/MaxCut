#include <iostream>
#include <random>
#include "../../algorithms/include/maxcut/weight.hpp"

struct Edge {
  size_t from;
  size_t to;
  int weight;
};

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\n\t" << argv[0]
              << " <N> <seed> [max_weight_in_cut (default = 100)] [max_weight_outside_cut (default = 10)]\n";
    return 0;
  }
  size_t n = std::atoi(argv[1]);
  unsigned seed = std::atoi(argv[2]);
  int max_weight_in_cut = 100;
  if (argc > 3) {
    max_weight_in_cut = std::atoi(argv[3]);
  }
  int max_weight_out_cut = 10;
  if (argc > 4) {
    max_weight_out_cut = std::atoi(argv[4]);
  }

  std::mt19937 rng(seed);

  std::vector<Edge> edges;

  graph::WeightT max_cut_hint = 0;

  for (size_t from = 0; from < n / 2; ++from) {
    for (size_t to = n / 2; to < n; ++to) {
      if (rng() % 100 < 90) {
        Edge new_edge{from, to, 1};
        if (max_weight_in_cut > 1) {
          new_edge.weight = rng() % max_weight_in_cut + 1;
        }
        edges.push_back(new_edge);
        max_cut_hint += new_edge.weight;
      }
    }
  }

  for (size_t from = 0; from < n / 2; ++from) {
    for (size_t to = from + 1; to < n / 2; ++to) {
      if (rng() % 100 < 40) {
        Edge new_edge{from, to, 1};
        if (max_weight_out_cut > 1) {
          new_edge.weight = rng() % max_weight_out_cut + 1;
        }
        edges.push_back(new_edge);
      }
    }
  }

  for (size_t from = n / 2; from < n; ++from) {
    for (size_t to = from + 1; to < n; ++to) {
      if (rng() % 100 < 40) {
        Edge new_edge{from, to, 1};
        if (max_weight_out_cut > 1) {
          new_edge.weight = rng() % max_weight_out_cut + 1;
        }
        edges.push_back(new_edge);
      }
    }
  }

  std::cout << n << " " << edges.size() << "\n";
  for (auto& e : edges) {
    std::cout << e.from + 1 << " " << e.to + 1 << " " << e.weight << "\n";
  }

  // Hint
  std::cout << max_cut_hint << "\n";
  return 0;
}