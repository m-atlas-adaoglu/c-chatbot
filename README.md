
# Chatbot in C

A simple console chatbot inspired by [ELIZA](https://en.wikipedia.org/wiki/ELIZA).

This is my own final project for the 2020/2021 COMP1921 Programming Project module.
(University of Leeds Computer Science Year 1).

The project scored a **69 / 70**.

This was my first time working on a (relatively) large program using **the C Programming Language**.
(Also, my first year studying/living at University abroad)

Looking at the code now, I can definitely spot some rookie mistakes. Please excuse these.
I hope to revisit and polish this project someday.

## Getting Started

### Prerequisites
* [CMake](https://cmake.org/): Version 3.22 or above.
* A compiler that supports C99. (I used [minGW](https://www.mingw-w64.org/))

---

### Building the Project
Use the provided CMakeLists.txt file.

An example using GCC:
```sh
   mkdir build
   cd build
   cmake ..
   make
```
---

### Running the Project
Two executables will be produced:

1. **unit_tests**
   * This program will run all the unit tests and print results to console.
2. **chatbot**
   * This is the actual program. It will run the chatbot.

-----

## Acknowledgements
This project uses the [Unity](http://www.throwtheswitch.org/unity) testing suite to facilitate unit testing.
(As instructed for the COMP1921 module).
