include_directories(algorithms)

add_executable(Tests tests.cpp algorithms/fa.cpp algorithms/kmp.cpp)
add_executable(FA faRunner.cpp algorithms/fa.cpp)
add_executable(KMP kmpRunner.cpp algorithms/kmp.cpp)
