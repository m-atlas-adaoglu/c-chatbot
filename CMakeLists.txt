cmake_minimum_required(VERSION 3.22)
project(c-chatbot C)

set(CMAKE_C_STANDARD 99)

include_directories(unity/include)
add_executable(UnitTests UnitTests.c unity/src/unity.c)
add_executable(Chatbot main.c Application.c UserInput.c Chatbot.c)
