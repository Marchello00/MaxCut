#include <iostream>
#include <random>

struct Edge {
  size_t from;
  size_t to;
  int weight;
};

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\n\t" << argv[0]
              << " <N> <seed> [max_weight (default = 1)] [probability_of_edge "
                 "(in %, default 50)]\n";
    return 0;
  }
  size_t n = std::atoi(argv[1]);
  unsigned seed = std::atoi(argv[2]);
  int max_weight = 1;
  if (argc > 3) {
    max_weight = std::atoi(argv[3]);
  }
  int edge_probability = 50;
  if (argc > 4) {
    edge_probability = std::atoi(argv[4]);
  }

  std::mt19937 rng(seed);

  std::vector<Edge> edges;

  for (size_t from = 0; from < n; ++from) {
    for (size_t to = from + 1; to < n; ++to) {
      if (rng() % 100 < edge_probability) {
        Edge new_edge{from, to, 1};
        if (max_weight > 1) {
          new_edge.weight = rng() % max_weight + 1;
        }
        edges.push_back(new_edge);
      }
    }
  }

  std::cout << n << " " << edges.size() << "\n";
  for (auto& e : edges) {
    std::cout << e.from + 1 << " " << e.to + 1 << " " << e.weight << "\n";
  }
  return 0;
}