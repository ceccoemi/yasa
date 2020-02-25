#!/bin/sh


set -o nounset  # display error and exit when referencing undefined variables
set -o errexit  # abort script when a command exists with a non-zero status


if [ ! -e yasa.db ]; then
    touch yasa.db
fi

docker run \
    --mount type=bind,source="$PWD"/yasa.db,target=/yasa.db \
    --mount type=bind,source="$PWD"/example/neg,target=/neg,readonly \
    --mount type=bind,source="$PWD"/example/pos,target=/pos,readonly \
    --rm --tty yasa train -n neg

docker run \
    --mount type=bind,source="$PWD"/yasa.db,target=/yasa.db \
    --mount type=bind,source="$PWD"/example/neg.txt,target=/neg.txt,readonly \
    --rm --tty yasa classify -f neg.txt

docker run \
    --mount type=bind,source="$PWD"/yasa.db,target=/yasa.db \
    --mount type=bind,source="$PWD"/example/pos.txt,target=/pos.txt,readonly \
    --rm --tty yasa classify -f pos.txt

