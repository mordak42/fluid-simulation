#!/usr/bin/env bash

dirlist=$(find srcs -type d)

for dir in $dirlist
do
	filelist=$(ls $dir)
	for file in $filelist
	do
		echo $dir/$file
	done
done
