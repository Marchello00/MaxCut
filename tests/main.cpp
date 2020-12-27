#include <iostream>
#include <maxcut/graph.hpp>

using graph::Graph;

int main() {
  size_t n, m;
  std::cin >> n >> m;
  Graph g(n);
  g.ReadGraph(m);
  for (size_t v = 0; v < g.Size(); ++v) {
    std::cout << v << ":\n";
    for (auto& edge : g[v]) {
      std::cout << edge.from << " " << edge.to << " " << edge.weight << " "
                << edge.index << "\n";
    }
  }
  return 0;
}