cmake_minimum_required(VERSION 3.10)
project(cpp_practice)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 递推和递归
add_executable(recursion algorithm/recursion_and_find_law/recursion.cpp)
add_executable(find_law algorithm/recursion_and_find_law/find_law.cpp)
add_executable(pawn_crossing_river algorithm/recursion_and_find_law/a_pawn_crossing_the_river.cpp)

# binary tree search
add_executable(depth_first_search algorithm/binary_tree/depth_first_search.cpp)
add_executable(breadth_first_search algorithm/binary_tree/breadth_first_search.cpp)

# heap
add_executable(heapify algorithm/heap/heapify.cpp)
add_executable(heapsort algorithm/heap/heapsort.cpp)

# list
add_executable(list_intro STL/containor/list/list_intro.cpp)
add_executable(list_assignment STL/containor/list/list_assignment.cpp)
add_executable(list_insert_remove STL/containor/list/list_insert_remove.cpp)