# GetIt

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Build Status](https://travis-ci.org/bartkessels/getit.svg?branch=development)](https://travis-ci.org/bartkessels/getit)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f9919567041d4715889d643b784e661f)](https://www.codacy.com/manual/bartkessels/getit?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=bartkessels/getit&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/bartkessels/getit/branch/development/graph/badge.svg)](https://codecov.io/gh/bartkessels/getit)

Application to send HTTP requests to test your API endpoints.

## Table of contents

- [1. Screenshots](#1-screenshots)
- [2. Features](#2-features)
- [3. Roadmap](#3-roadmap)
- [4. Required packages](#4-required-packages)
- [5. Build](#5-build)
    - [5.1 Tests](#51-tests)
        - [5.1.1 Test coverage](#511-test-coverage)
    - [5.2 Application](#52-application)
    
## 1. Screenshots

![Main window of GetIt](data/screenshot_1.png)

## 2. Features

You can send numerous requests to a webserver. You can send RAW post data,
form post data, add cookies to your request and add headers to your request.

The goal of GetIt is making testing API's easier using open sources tools. If you're
missing a feature please do not hesitate to open a pull-request or create an issue.

## 3. Roadmap

Unfortunately there are only so many things we can implement in a specific time period, so there will be some
features that aren't included in GetIt but that we will add in the future.

- Add API for adding settings to the request API
- Syntax highlighting for the response
- Authentication
    - Basic auth
    - Oauth 1/2
- Custom time-out
- Saving / opening a request
    - The response will be saved as well for offline usage

There are some things we want get up and running to make life easier for the developers of GetIt, mostly for
distributing the application.

- Setup CI for Windows machine
- Setup GUI test framework

## 4. Required packages

GetIt relies on a couple of external packages, some are being fetched using Cmake's `FetchContent` while others
are expected to be installed on your system.

The packages that are fetched by Cmake are [CppRestRequest](https://github.com/microsoft/cpprestsdk), a library from
[Microsoft](https://microsoft.com) to send HTTP requests using an easy C++ interface. This package is both used for
building the `getit` executable as well as the `getit_tests` executable. For the `getit_tests` executable the
[Catch2](https://github.com/catchorg/catch2) library is fetched as the unit-tests framework used by GetIt.

The packages you need to install

- `Qt5`, this is used for the GUI of Getit
- `Boost`, these libraries are used within [CppRestSdk](https://github.com/microsoft/cpprestsdk) library
- `CMake`, this is the build system used by GetIt

## 5. Build

Once you've installed the required packages you're ready to compile GetIt or the GetIt tests.

### 5.1 Tests

```bash
$ cd build
$ cmake ..
$ make getit_tests
$ ./bin/getit_tests
```

#### 5.1.1 Test coverage

If you want to generate the test coverage report add the `--coverage` to the `cmake` command, i.e. `cmake --coverage ..`. This will generate a coverage report for each individual sources file. The coverage reports can be bundled using `lcov` which will generate a `.info` file. To open this file convert it to a `.html` file with the `genhtml` command.

```bash
$ lcov --directory tests/CMakeFiles/getit_tests.dir --capture --output-file getit_coverage.info
$ genhtml -o coverage/ getit_coverage.info
$ open coverage/index.html
```

### 5.2 Application

```bash
$ cd build
$ cmake ..
$ make getit
$ ./bin/getit
```
