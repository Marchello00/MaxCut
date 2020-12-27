#pragma once

#include "iterating.hpp"

#include <iostream>
#include <vector>

namespace graph {

using WeightT = int;

struct Edge {
  // Networks in MaxCut/MinCut problems are usually oriented
  size_t from;
  size_t to;

  WeightT weight;

  size_t index;  // Just for output
};

class Graph {
  friend class iterating::VertexNeighbourhood;

 public:
  explicit Graph(size_t n);

  [[nodiscard]] size_t Size() const;

  [[nodiscard]] const Edge& GetEdgeByIndex(size_t index) const;

  size_t AddEdge(size_t from, size_t to, WeightT weight);

  void ReadGraph(size_t edge_count, std::istream& in = std::cin);

  iterating::VertexNeighbourhood operator[](size_t vertex) const;

 private:
  size_t n_;  // Vertex count

  std::vector<Edge> edges_;
  std::vector<std::vector<size_t>> edges_from_vertex_;
};

}  // namespace graph