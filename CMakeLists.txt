cmake_minimum_required(VERSION 3.12)
project(AdvancedProg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(AdvancedProg main.cpp command.h openDataServer.h lexer.h lexer.cpp commandGiver.h runCommand.h runCommand.cpp openDataServer.cpp DataReaderServer.h DataReaderServer.cpp connectCommand.cpp connectCommand.h expression.h variable.cpp variable.h symbolTable.cpp symbolTable.h createVarCommand.cpp createVarCommand.h commandGiver.cpp)