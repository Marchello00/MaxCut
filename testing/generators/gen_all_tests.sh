#!/bin/bash

# Edge probability 50%
echo "Generating graphs with 50% edges..."
for n in 8 15 20 35 50 75 100 250 500; do
  mkdir -p ../tests/random_graph_50/size-${n}
  for seed in {1..100}; do
    ../../bin/RandomGraphGenerator ${n} ${seed} >../tests/random_graph_50/size-${n}/rand-${seed}
  done
done

# Edge probability 10/n
echo "Generating graphs with 1000/n% edges..."
for n in 10 35 50 75 100 250; do
  mkdir -p ../tests/random_graph_10n/size-${n}
  for seed in {1..100}; do
    ../../bin/RandomGraphGenerator ${n} ${seed} 1 $((1000 / n)) >../tests/random_graph_10n/size-${n}/rand-${seed}
  done
done

# random graph of size 100 with different probabilities
echo "Generating graphs of size 100 with p% edges..."
for p in 10 20 30 40 50 60 70 80 90; do
  mkdir -p ../tests/random_graph_prob/prob-${p}
  for seed in {1..100}; do
    ../../bin/RandomGraphGenerator 100 ${seed} 1 ${p} >../tests/random_graph_prob/prob-${p}/rand-${seed}
  done
done

# random graph of size 100 with different weights
echo "Generating graphs of size 100 with p% edges..."
for p in 10 20 30 40 50 60 70 80 90; do
  mkdir -p ../tests/random_graph_prob/prob-${p}
  for seed in {1..100}; do
    ../../bin/RandomGraphGenerator 100 ${seed} 1 ${p} >../tests/random_graph_prob/prob-${p}/rand-${seed}
  done
done

# random graph with large cut
echo "Generating graphs with large cut..."
for n in 8 15 20 35 50 75 100 250 500; do
  mkdir -p ../tests/large_cut/size-${n}
  for seed in {1..100}; do
    ../../bin/LargeCutGenerator ${n} ${seed} >../tests/large_cut/size-${n}/rand-${seed}
  done
done