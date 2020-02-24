# Report

## Authors
 **Emilio Cecchini** &ensp; &ensp;**Lorenzo Palloni**

## Table of Contents
1. [What we have implemented](#what-we-have-implemented)
2. [Applied techniques and frameworks](#applied-techniques-and-frameworks)
3. [Design and implementation choices](#design-and-implementations-choices)
4. [Some of the problems encountered and how we have solved them](#possible-problems-encountered-and-how-you-solve-them)
5. [Descriptions of the development (and testing) of the most interesting parts](#descriptions-of-the-development-(and testing)-of-the-most-interesting-parts)
6. [Explanation of some of the tools used](#explanation-of-some-of-the-tools-used)

## What we have implemented
We implemented **[yasa](https://github.com/ceccoemi/yasa) ** (Yet Another Sentiment Analyser), a containerized command line tool that make easy the application of Sentiment Analysis.
It allows to train an underneath model of sentiment analysis with text files labeled as positives or negatives. After the training phase the model is able to predict the label of an unseen text file into positive/negative.

The management of this model is done trough a command line interface (CLI).
The model can be trained giving folder containing positives or negatives text using the command

`$ yasa train --positives <positives-folder> --negatives <negatives-folder>`

After trained, the model is able to classify a text file using the command

`$ yasa classify --file <file-to-classify>`

## Applied techniques and frameworks
The software is implemented in C++ and in order to make it reproducible and portable we use docker. To store all the information that the underneath model needs, we use SQLite that is a database management system (DBMS) based on a relational model.

- **Test ->** Google Test
- **Mock ->** Google Mock
- **Code Covarage ->** Gcov
- **Code Quality ->** LGTM
- **Linter + Formatter ->** Clang-tidy
- **Build Automation ->** CMake + Docker
- **CI Server->** Travis CI
- **VCS ->** GitHub
- **IDE ->** Eclipse
- **DBMS ->** SQLite

## Design and implementation choices
The main function calls the ArgumentParser class that parses the input arguments given through the CLI.
Then there are three possibilities:

* train;
* classify;
* display usage message.

The training is handled by the Trainer class that:

1. reads all the text files in the given directories with TextFileReader class;
2. tokenizes the words previously found with the extractWords function (in preprocessing source code file);
3. updates the underneath SQLite database using the SqliteDictionary class.

We wrapped the C-written API of SQLite in the class SqliteHandler to make easier the usage.
The classifying is handled by a Classifier class that:

1. reads the given text file with TextFileReader;
2. tokenizes the words previously found with the extractWords function (in preprocessing source code file);
3. classifies the text querying the database using SqliteDictionary class.

Usage messages to displayed are managed by the ArgumentParser class.

## Some of the problems encountered and how we have solved them
The management of SQLite database was one of the biggest challenges because its implementation in C language did not fit well with our other C++ classes. We have solved this problem encapsulating the necessary functionality of the API wrapping it in our SqliteHandler C++ class.

We initially missed the concept of isolation for unit-tests: when a bug in a component caused tests of other components to fail. Then Google Mock came into rescue!

* Google Mock requires a virtual implementation of the class to mock. Both original and mocked classes will inherit from their virtual base class. For example, in our case the mocked class MockDictionary and the original class SqliteDictionary both inherit from the interface Dictionary.

## Descriptions of the development (and testing) of the most interesting parts
Initially the subject of our project was a preprocessing tool for natural language processing. We changed almost completely the project due to give more sense to the application of a database and in order to have a more concrete goal.

One of the most difficult parts to test was the main because it has a lot of logic branches. We delegates much of the responsabilities of the main to the ArgumentParser class.

[//]: # (At some point during the development of this project, there was a folder `./tests/resources` that contained examples of text files. They allowed us to test Trainer and Classifier classes, but we understood that with a mock object on the text files we would achieve a more isolated unit-tests for both Trainer and Classifier classes.)

## Explanation of some of the tools used
