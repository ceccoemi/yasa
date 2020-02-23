#!/bin/sh


set -o nounset  # display error and exit when referencing undefined variables
set -o errexit  # abort script when a command exists with a non-zero status


if [ ! -e yasa.db ]; then
    touch yasa.db
fi

docker run \
    --mount type=bind,source="$PWD"/yasa.db,target=/yasa.db \
    --mount type=bind,source="$PWD"/example,target=/example,readonly \
    --rm --tty yasa train -n example/neg -p example/pos

docker run \
    --mount type=bind,source="$PWD"/yasa.db,target=/yasa.db \
    --mount type=bind,source="$PWD"/example,target=/example,readonly \
    --rm --tty yasa classify -f example/neg.txt

docker run \
    --mount type=bind,source="$PWD"/yasa.db,target=/yasa.db \
    --mount type=bind,source="$PWD"/example,target=/example,readonly \
    --rm --tty yasa classify -f example/pos.txt
