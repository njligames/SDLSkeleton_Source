#!/bin/bash

# set -x

# use imagemagick to give a ratio of how different two images are.
# 0 is not differnt all.
# 1 is completely different.

IMG1=$1
IMG2=$2
OUT=`date +"%m-%d-%Y-%H-%M-%S"`

precentage=`compare -metric NCC ${IMG1} ${IMG2} ${OUT}`

echo $percentage

