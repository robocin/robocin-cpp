robocin_cpp_library(
        NAME angle
        HDRS angle.h internal/angle_internal.h
        SRCS angle.cpp
        DEPS angular fuzzy_compare
)

robocin_cpp_test(
        NAME angle_test
        HDRS ../utility/internal/test/epsilon_injector.h
        SRCS angle_test.cpp
        DEPS angle
)
