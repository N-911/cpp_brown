cmake_minimum_required(VERSION 3.17)
project(uniqe_prt)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(uniqe_prt
       unique_ptr.cpp
        profile.h
#        profile_extendet.h
        test_runner.h
        )
