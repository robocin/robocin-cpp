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


robocin_cpp_library(
        NAME rect2d
        HDRS rect2d.h
        SRCS rect2d.cpp
)


robocin_cpp_test(
        NAME rect2d_test
        HDRS ../utility/internal/test/epsilon_injector.h
        SRCS rect2d_test.cpp
        DEPS rect2d
)
