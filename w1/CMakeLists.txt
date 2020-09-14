cmake_minimum_required(VERSION 3.17)
project(w1)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(w1
#        hash_set.cpp
        profile.h
        profile_extendet.h
        test_runner.h
        head.h
#        set_iterator_next.cpp
#        hash_point.cpp
#        hash_person.cpp
        secondary_index.cpp
        )
