# Redundant test case identification

## :page_facing_up: Description
This is a Software Verification course project. The program can be used to find redundant test cases from a test suite. It works on Qt unit testing framework. Detailed system description can be found [here](https://github.com/kredenac/redundant-test-cases/blob/ecd97585c9b7844dbe03e275c69878c175f152a7/SystemDescription.txt).

## :computer: Installation

### Getting the code
```
    $ git clone https://github.com/kredenac/redundant-test-cases.git
    $ cd redundant-test-cases
```
### Installing prerequisites

#### Supported operating systems

We support linux-based systems only.

#### Python programming language
Install Python 3. If you don't have python you can download version 3.7 from [here](https://www.python.org/downloads/release/python-372/)

If you already have Python installed, you can verify its version by running 
```
    $ python --version
```
The minimum required version is 3.0.

#### C++ programming language

You will need a c++11 compiler, which should come preinstalled in most linux based systems. 

Install qt 5.12 library, you can follow [this](https://wiki.qt.io/Install_Qt_5_on_Ubuntu) guide for Ubuntu. The minimum requered version is 5.7.

## :wrench: Example of use

Navigate to the project root folder and compile the code by calling:
```
    $ make all
```

Now you can run the program by calling:
```
    $ make run
```

There is a sample project on which the project can be tested that is located in ./src/what_we_test/. In the current version you have to delete the sample project, and put your project and test project in .//src/what_we_test/Root. Future feature will be to input the location of the testing project in runtime. 

The test project should be written in Qt unit framework. We automatically find all test cases and find all redundant ones.


## :baby: Team

| ![](https://avatars0.githubusercontent.com/u/22803285?s=300) | ![](https://upload.wikimedia.org/wikipedia/commons/thumb/9/91/Octicons-mark-github.svg/200px-Octicons-mark-github.svg.png) | 
| :---: | :---: |
| <a href="https://github.com/kredenac" target="_blank">`https://github.com/kredenac`</a> | <a href="https://github.com/mm11021" target="_blank">`https://github.com/mm11021`</a> | 
| ![](https://avatars0.githubusercontent.com/u/23039830?s=300) | ![](https://avatars2.githubusercontent.com/u/23014769?s=300) |
| <a href="https://github.com/Nacili" target="_blank">`https://github.com/Nacili`</a> | <a href="https://github.com/leonardovlibido" target="_blank">`https://github.com/leonardovlibido`</a> |

