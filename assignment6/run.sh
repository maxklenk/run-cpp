#!/usr/bin/env bash

echo "build..."
cmake --build .


echo "execute graph..."
./graph_
echo "execute mixin..."
./mixin_
echo "low res..."
cat ./low_res.txt
echo "high res..."
cat ./high_res.txt
echo "transactions..."
./transaction_