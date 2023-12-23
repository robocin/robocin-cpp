robocin_cpp_library(
        NAME angle
        HDRS angle.h internal/angle_internal.h
        SRCS angle.cpp
        DEPS angular fuzzy_compare
)
