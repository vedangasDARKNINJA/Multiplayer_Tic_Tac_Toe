#!/bin/bash

./GenerateProject.sh

make clean -C build
bear make -C build

read -n1 -r -p "Press any key to continue..." key
