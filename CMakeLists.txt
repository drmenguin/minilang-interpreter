cmake_minimum_required(VERSION 3.10)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_executable(project main.cpp lexer/lexer.cpp lexer/lexer.h lexer/token.cpp lexer/token.h parser/parser.cpp parser/parser.h parser/ast.cpp parser/ast.h)