cmake_minimum_required(VERSION 3.13)
project(DFA)

set(CMAKE_CXX_STANDARD 14)

add_executable(DFA main.cpp hash.cpp hash.h lnfa.cpp lnfa.h dfa.cpp dfa.h automata.cpp automata.h regex.cpp regex.h)