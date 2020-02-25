# yasa - Yet Another Sentiment Analyzer

[![TravisCI](https://travis-ci.org/ceccoemi/yasa.svg?branch=master)](https://travis-ci.org/ceccoemi/yasa)
[![codecov](https://codecov.io/gh/ceccoemi/yasa/branch/master/graph/badge.svg)](https://codecov.io/gh/ceccoemi/yasa)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/ceccoemi/yasa.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/ceccoemi/yasa/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/ceccoemi/yasa.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/ceccoemi/yasa/context:cpp)

Command line tool to perform sentiment analysis written in C++ with Docker.

## Build with Docker

yasa can be built as a Docker image. The `Dockerfile` located in the project root directory takes care of all the steps to build the image. You only have to cd to the root directory and run:

    $ docker build -t yasa .

This command will download all the needed dependencies, it will execute all the tests and finally Docker image called `yasa` will be built.

The Docker image can be directly executed with the `Docker run` command.

The following command is an example of usage:

    docker run \
        --mount type=bind,source=<path-to-yasa.db>,target=/yasa.db \
        --mount type=bind,source=<path-to-pos-dir>,target=/<pos-dir>,readonly \
        --mount type=bind,source=<path-to-neg-dir>,target=/<neg-dir>,readonly \
        --rm --tty yasa train -p <pos-dir> -n <neg-dir>

After trained, the model is able to classify a text file using the following command:

    docker run \
        --mount type=bind,source=<path-to-yasa.db>,target=/yasa.db \
        --mount type=bind,source=<path-to-file-to-classify>,target=/<file-to-classify>,readonly \
        --rm --tty yasa classify -f <file-to-classify>

The `yasa.db` file must exists (you can create it with `$ touch yasa.db`), moreover files and directories used must be bound to the container, which can be achieved with Docker volumes or Docker bind mounts. The training phase will update this file `yasa.db`, which can be stored and used later for the classification phase or for another training.

For example in order to train the underneath model with all the text files in the directories `example/pos` and `example/neg`, you can use the following command (it can take about minutes 5 minutes):

    docker run \
        --mount type=bind,source="$PWD"/yasa.db,target=/yasa.db \
        --mount type=bind,source="$PWD"/example/pos,target=/pos,readonly \
        --mount type=bind,source="$PWD"/example/neg,target=/neg,readonly \
        --rm --tty yasa train -p pos -n neg

If you want to classify e.g. the `example/neg.txt` file with the model trained just before, you can use the following command:

    docker run \
        --mount type=bind,source="$PWD"/yasa.db,target=/yasa.db \
        --mount type=bind,source="$PWD"/example/neg.txt,target=/neg.txt,readonly \
        --rm --tty yasa classify -f neg.txt

These last three command can be executed simply launching the shell script `run_example.sh`.

## Build on local system (tested only in Ubuntu 18.04)
