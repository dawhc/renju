PROJECT(renju)

set(CMAKE_CXX_STANDARD 14)

add_executable(renju start.cpp createmoves.h createmoves.cpp define.h define.cpp evaluate.h evaluate.cpp hash.h hash.cpp makemove.h makemove.cpp printchessboard.h printchessboard.cpp searchmove.h searchmove.cpp)