#!/bin/sh

if [ -z "$1" ]
then
	echo "Empty commit message!"
	exit 1
fi

git pull
git add *
git commit -am $1
git push
