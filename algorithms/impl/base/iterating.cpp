#include "include/maxcut/iterating.hpp"
#include "include/maxcut/graph.hpp"

namespace graph::iterating {

VertexNeighbourhood::VertexNeighbourhood(const Graph& father, size_t vertex)
    : father_(father), vertex_(vertex) {
}

EdgeIterator VertexNeighbourhood::begin() const {
  return EdgeIterator(father_, vertex_,
                      father_.edges_from_vertex_[vertex_].cbegin());
}
EdgeIterator VertexNeighbourhood::end() const {
  return EdgeIterator(father_, vertex_,
                      father_.edges_from_vertex_[vertex_].cend());
}

EdgeIterator::EdgeIterator(
    const Graph& father, size_t vertex,
    const std::vector<size_t>::const_iterator& start_position)
    : father_(father), vertex_(vertex), neighbour_(start_position) {
}

bool EdgeIterator::operator!=(EdgeIterator& other) const {
  return neighbour_ != other.neighbour_;
}

EdgeIterator::reference EdgeIterator::operator*() const {
  return father_.GetEdgeByIndex(*neighbour_);
}

Edge EdgeIterator::operator->() const {
  return this->operator*();
}

EdgeIterator EdgeIterator::operator++() {
  ++neighbour_;
  return *this;
}

const EdgeIterator EdgeIterator::operator++(int) {
  auto tmp = *this;
  ++*this;
  return tmp;
}

EdgeIterator& EdgeIterator::operator--() {
  neighbour_--;
  return *this;
}

const EdgeIterator EdgeIterator::operator--(int) {
  auto tmp = *this;
  --*this;
  return tmp;
}

EdgeIterator& EdgeIterator::operator+=(long n) {
  neighbour_ += n;
  return *this;
}

EdgeIterator EdgeIterator::operator+(long n) const {
  auto tmp = *this;
  tmp += n;
  return tmp;
}

EdgeIterator& EdgeIterator::operator-=(long n) {
  neighbour_ -= n;
  return *this;
}

EdgeIterator EdgeIterator::operator-(long n) const {
  auto tmp = *this;
  tmp -= n;
  return tmp;
}

long EdgeIterator::operator-(EdgeIterator& other) const {
  return neighbour_ - other.neighbour_;
}

const Edge& EdgeIterator::operator[](long n) const {
  return *(*this + n);
}

bool EdgeIterator::operator<(const EdgeIterator& other) const {
  return neighbour_ < other.neighbour_;
}

bool EdgeIterator::operator>(const EdgeIterator& other) const {
  return neighbour_ > other.neighbour_;
}

bool EdgeIterator::operator<=(const EdgeIterator& other) const {
  return neighbour_ <= other.neighbour_;
}

bool EdgeIterator::operator>=(const EdgeIterator& other) const {
  return neighbour_ >= other.neighbour_;
}

}  // namespace graph::iterating