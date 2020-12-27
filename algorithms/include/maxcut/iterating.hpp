#pragma once

#include <iterator>
#include <vector>

namespace graph {

struct Edge;
class Graph;

namespace iterating {

class EdgeIterator;

class VertexNeighbourhood {
  friend class graph::Graph;

 public:
  [[nodiscard]] EdgeIterator begin() const;
  [[nodiscard]] EdgeIterator end() const;

 private:
  VertexNeighbourhood(const Graph& father, size_t vertex);

 private:
  const Graph& father_;
  size_t vertex_;
};

class EdgeIterator
    : std::iterator<std::random_access_iterator_tag, const Edge> {
  friend class VertexNeighbourhood;

 public:
  bool operator!=(EdgeIterator& other) const;

  reference operator*() const;
  Edge operator->() const;

  EdgeIterator operator++();
  const EdgeIterator operator++(int);

  EdgeIterator& operator--();
  const EdgeIterator operator--(int);

  EdgeIterator& operator+=(difference_type n);
  EdgeIterator operator+(difference_type n) const;
  EdgeIterator& operator-=(difference_type n);
  EdgeIterator operator-(difference_type n) const;
  difference_type operator-(EdgeIterator& other) const;
  reference operator[](difference_type n) const;
  bool operator<(const EdgeIterator& other) const;
  bool operator>(const EdgeIterator& other) const;
  bool operator<=(const EdgeIterator& other) const;
  bool operator>=(const EdgeIterator& other) const;

 private:
  EdgeIterator(const Graph& father, size_t vertex,
               const std::vector<size_t>::const_iterator& start_position);

 private:
  const Graph& father_;
  const size_t vertex_;
  std::vector<size_t>::const_iterator neighbour_;
};

}  // namespace iterating

}  // namespace graph