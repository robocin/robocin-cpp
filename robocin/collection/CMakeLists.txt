robocin_cpp_library(
        NAME collection
        HDRS collection.h
        SRCS collection.cpp
        DEPS tbb
)

robocin_cpp_test(
        NAME collection_test
        SRCS collection_test.cpp
        DEPS collection
)
