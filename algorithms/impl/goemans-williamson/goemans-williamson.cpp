#include "include/maxcut/goemans-williamson.hpp"

#include "fusion.h"

#include <random>

using namespace mosek::fusion;
using namespace monty;

Variable::t SolveSDP(const graph::Graph& graph) {
  Model::t M = new Model("GoemansWilliamson");
  auto _M = finally([&]() { M->dispose(); });

  // Setting up the variables
  Variable::t X = M->variable("X", Domain::inPSDCone(graph.Size()));

  // Setting up the constant coefficient matrices
  std::vector<std::vector<double>> weights(graph.Size());
  graph::WeightT total_weight = 0;
  for (size_t from = 0; from < graph.Size(); ++from) {
    weights[from].resize(graph.Size());
    for (size_t to = 0; to < graph.Size(); ++to) {
      weights[from][to] = graph.GetEdgeBetweenVertexes(from, to).weight;
      total_weight += weights[from][to];
    }
  }
  Matrix::t C = Matrix::dense(new_array_ptr(weights));

  // Objective
  M->objective(ObjectiveSense::Maximize,
               Expr::mul(0.25, Expr::sub(Expr::constTerm(total_weight),
                                         Expr::dot(C, X))));

  // Constraints
  for (size_t v = 0; v < graph.Size(); ++v) {
    M->constraint("X(" + std::to_string(v) + ")",
                  X->pick(new_array_ptr<int, 1>({(int)v}),
                          new_array_ptr<int, 1>({(int)v})),
                  Domain::equalsTo(1.0));
  }

  M->solve();

  //  std::cout << "Solution : " << std::endl;
  //  std::cout << "  X = " << *(X->level()) << std::endl;

  return X;
}

std::vector<double> CholeskyDecomposition(Variable::t X) {
  auto n = *(X->getShape()->begin());

  auto X_level = X->level();
  auto tmp = new_vector_from_array_ptr(X_level);
  auto L = new_array_ptr(tmp);

  mosek::LinAlg::potrf(MSKuploe::MSK_UPLO_LO, n, L);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      *(L->begin() + j * n + i) = 0;
    }
  }

  //  std::cout << "  L = " << *L << "\n";
  return new_vector_from_array_ptr(L);
}

graph::maxcut::GoemansWilliamson::GoemansWilliamson(const Graph& graph,
                                                    unsigned seed)
    : MaxCutSolver(graph), seed_(seed) {
}

graph::WeightT graph::maxcut::GoemansWilliamson::Solve_() {
  auto A = SolveSDP(graph_);
  auto L = CholeskyDecomposition(A);
  RandomSplit(L);
  return GetCutWeight(GetCut());
}

void graph::maxcut::GoemansWilliamson::RandomSplit(
    const std::vector<double>& coordinates) {
  std::mt19937 rng(seed_);
  size_t n = graph_.Size();
  WeightT max_found_cut_weight = kMinWeight;
  for (int repeat = 0; repeat < 15; ++repeat) {
    std::vector<double> plane(n);
    for (auto& coord : plane) {
      coord = rng();
    }
    std::vector<bool> current_answer(graph_.Size());
    for (int v = 0; v < graph_.Size(); ++v) {
      double dot = 0;
      for (int i = 0; i < n; ++i) {
        dot += coordinates[n * v + i] * plane[i];
      }
      current_answer[v] = dot >= 0;
    }
    auto current_cut_weight = GetCutWeight(current_answer);
    if (current_cut_weight >= max_found_cut_weight) {
      max_found_cut_weight = current_cut_weight;
      answer_ = current_answer;
    }
  }
}
