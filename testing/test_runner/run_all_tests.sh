#!/bin/sh

# random graph 50%
echo "Running on graphs with 50% edges..."
for n in 8 15 20; do
  echo "Size ${n}..."
  ./run_test_dir.sh random_graph_50/size-${n} --bruteforce --random --greed --goemans-williamson
done
for n in 35 50 75 100 250 500; do
  echo "Size ${n}..."
  ./run_test_dir.sh random_graph_50/size-${n} --random --greed --goemans-williamson
done

# random graph (1000/n)%
echo "Running on graphs with 1000/n% edges..."
for n in 10 35 50 75 100 250; do
  echo "Size ${n}..."
  ./run_test_dir.sh random_graph_10n/size-${n} --random --greed --goemans-williamson
done

# random graph of size 100 with different probabilities
echo "Running on graphs of size 100 with p% edges..."
for p in 10 20 30 40 50 60 70 80 90; do
  echo "Edge probability - ${p}%..."
  ./run_test_dir.sh random_graph_prob/prob-${p} --random --greed --goemans-williamson
done

# random graph of size 100 with different weights
echo "Running on graphs of size 100 with different weights..."
for max_weight in 5 10 50 100 1000 10000 100000; do
  echo "Max weight - ${max_weight}..."
  ./run_test_dir.sh random_graph_weights/weight-${max_weight} --greed --goemans-williamson
done

# graph with large cut
echo "Running on graphs with large cut..."
for n in 8 15 20 35 50 75 100 250 500; do
  echo "Size ${n}..."
  ./run_test_dir.sh large_cut/size-${n} --greed --goemans-williamson
done

# BiqMac tests
echo "Running biqmac/ising tests..."
./run_test_dir.sh biqmac/ising --greed --goemans-williamson
echo "Running biqmac/rudy tests..."
./run_test_dir.sh biqmac/rudy --greed --goemans-williamson