#!/bin/bash

# git add
# for file in "$@"
# do
#     echo "git add $file"
#     git add $file
# done
while [ $# -gt 1 ]
do
    echo "git add $1"
    git add $1
    shift
done

# git commit
git commit -m "$(eval echo \$$#)"

# git push
git push github master