#!/bin/bash

if [[ ! -d "./build" ]]
then

	echo "Build directory not found!"
	read -n1 -r -p "Press any key to continue..." key
	exit
fi

cd build
make clean
make

read -n1 -r -p "Press any key to continue..." key
