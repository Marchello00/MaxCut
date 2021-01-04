mkdir ../tests/random_graph

for n in 8 15 50 100; do
  mkdir ../tests/random_graph/size-${n}
  for seed in {1..100}; do
    ../../bin/RandomGraphGenerator ${n} ${seed} >../tests/random_graph/size-${n}/rand-${seed}
  done
done
