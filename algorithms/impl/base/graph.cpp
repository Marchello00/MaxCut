#include "include/maxcut/graph.hpp"
#include "include/maxcut/iterating.hpp"

#include <iostream>

graph::Graph::Graph(size_t n) : n_(n), edges_from_vertex_(n_) {
}

size_t graph::Graph::Size() const {
  return n_;
}

const graph::Edge& graph::Graph::GetEdgeByIndex(size_t index) const {
  return edges_[index];
}

size_t graph::Graph::AddEdge(size_t from, size_t to, graph::WeightT weight) {
  Edge new_edge{from, to, weight, edges_.size()};
  edges_.push_back(new_edge);
  edges_from_vertex_[from].push_back(new_edge.index);
  return new_edge.index;
}

void graph::Graph::ReadGraph(size_t edge_count, bool undirected,
                             std::istream& in) {
  for (size_t i = 0; i < edge_count; ++i) {
    size_t from, to;
    WeightT weight;
    in >> from >> to >> weight;
    --from, --to;
    AddEdge(from, to, weight);
    if (undirected) {
      AddEdge(to, from, weight);
    }
  }
}

graph::iterating::VertexNeighbourhood graph::Graph::operator[](
    size_t vertex) const {
  return graph::iterating::VertexNeighbourhood(*this, vertex);
}
