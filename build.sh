#!/bin/bash

rm -r build/*;
cd build;
cmake ..;
make;
cp process_image ..;
cd ..;
