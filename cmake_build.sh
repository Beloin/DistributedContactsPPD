#!/bin/bash

cmake -S . -B build;
pushd build;
echo "Copying compile_commands.json"
cp compile_commands.json ../;
popd;
