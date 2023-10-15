robocin_cpp_library(
        NAME point2d
        HDRS point2d.h
        SRCS point2d.cpp
)

robocin_cpp_test(
        NAME point2d_test
        HDRS ../utility/internal/test/epsilon_injector.h
        SRCS point2d_test.cpp
        DEPS point2d
)
