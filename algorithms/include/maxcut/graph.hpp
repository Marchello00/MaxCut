#pragma once

#include "iterating.hpp"
#include "weight.hpp"

#include <iostream>
#include <vector>

namespace graph {

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

  const Edge& GetEdgeBetweenVertexes(size_t from, size_t to) const;

  size_t AddEdge(size_t from, size_t to, WeightT weight);

  void ReadGraph(size_t edge_count, bool undirected = false,
                 std::istream& in = std::cin);

  iterating::VertexNeighbourhood operator[](size_t vertex) const;

 private:
  size_t n_;  // Vertex count

  std::vector<Edge> edges_;
  std::vector<std::vector<size_t>> edges_from_vertex_;

  std::vector<std::vector<size_t>> edge_between_vertexes_;
};

}  // namespace graph