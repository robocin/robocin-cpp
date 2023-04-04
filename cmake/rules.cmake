########################################################################################################################

include(deps)

########################################################################################################################

# define the project name to be used in the code
set(ROBOCIN_PROJECT_NAME ${CMAKE_PROJECT_NAME})

########################################################################################################################

# define the project path to be used in the code
get_filename_component(ROBOCIN_PROJECT_PATH "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

########################################################################################################################

# add cpp library
# named parameters:
#  NAME: name of the library
#  HDRS: header files
#  SRCS: source files
#  RSRCS: resource files
#  DEPS: dependencies
#  MACROS: macros
#  CONFIGS: CMake configurable files
function(robocin_cpp_library)
  cmake_parse_arguments(
          ARG                                    # prefix of output variables
          ""                                     # list of names of the boolean arguments
          "NAME"                                 # list of names of mono-valued arguments
          "HDRS;SRCS;RSRCS;DEPS;MACROS;CONFIGS"  # list of names of multi-valued arguments
          ${ARGN}                                # arguments of the function to parse (ARGN contains all the arguments after the function name)
  )

  # if there isn't at least one header file, then the library is not created
  if (NOT ARG_HDRS)
    message(FATAL_ERROR "robocin_cpp_library: no header files given")
  endif ()

  # if there isn't at least one source file, then the library is not created
  if (NOT ARG_SRCS)
    message(FATAL_ERROR "robocin_cpp_library: no source files given")
  endif ()

  # if there are CMake configurable files, then they are configured and added to the library
  if (ARG_CONFIGS)
    foreach (CONFIG_FILE ${ARG_CONFIGS})
      get_filename_component(config_last_extension ${CONFIG_FILE} LAST_EXT)

      if (NOT ${config_last_extension} STREQUAL ".in")
        message(FATAL_ERROR "robocin_cpp_library: invalid extension '${config_last_extension}' for configurable file '${CONFIG_FILE}'")
      endif ()

      get_filename_component(config_filename ${CONFIG_FILE} NAME_WLE)
      configure_file(${CONFIG_FILE} ${config_filename})
      list(APPEND CONFIG_HDRS ${CMAKE_CURRENT_BINARY_DIR}/${config_filename})
    endforeach ()
  endif ()

  add_library(${ARG_NAME} ${ARG_HDRS} ${ARG_SRCS} ${ARG_RSRCS} ${CONFIG_HDRS}) # add library with given name, headers, sources and resources
  target_link_libraries(${ARG_NAME} PUBLIC ${ARG_DEPS}) # link library with given dependencies

  target_include_directories(${ARG_NAME} PRIVATE ${ROBOCIN_PROJECT_PATH})
  target_include_directories(${ARG_NAME} PRIVATE ${CMAKE_BINARY_DIR})

  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_NAME="${ROBOCIN_PROJECT_NAME}")
  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_PATH="${ROBOCIN_PROJECT_PATH}")

  if (ARG_MACROS)
    target_compile_definitions(${ARG_NAME} ${ARG_MACROS})
  endif ()

endfunction(robocin_cpp_library)

########################################################################################################################

# Add cpp unit test
# Named parameters:
#  NAME: name of the test
#  HDRS: header files
#  SRCS: source files
#  RSRCS: resource files
#  DEPS: dependencies
function(robocin_cpp_test)
  cmake_parse_arguments(
          ARG                            # prefix of output variables
          ""                             # list of names of the boolean arguments
          "NAME"                         # list of names of mono-valued arguments
          "HDRS;SRCS;RSRCS;DEPS;MACROS"  # list of names of multi-valued arguments
          ${ARGN}                        # arguments of the function to parse (ARGN contains all the arguments after the function name)
  )

  # check if at least one source file is given with suffix '_test.cpp'
  if (NOT ARG_SRCS)
    message(FATAL_ERROR "robocin_cpp_test: no source files given")
  else ()
    set(FILTERED_SRCS ${ARG_SRCS})
    list(FILTER FILTERED_SRCS INCLUDE REGEX "_test\.cpp$")

    if (NOT FILTERED_SRCS)
      message(FATAL_ERROR "robocin_cpp_test: no source files given with suffix '_test.cpp'")
    endif ()
  endif ()

  add_executable(${ARG_NAME} ${ARG_HDRS} ${ARG_SRCS} ${ARG_RSRCS}) # add test with given name, headers, sources and resources
  target_link_libraries(${ARG_NAME} PRIVATE GTest::gtest GTest::gtest_main ${ARG_DEPS}) # link library with given dependencies

  target_include_directories(${ARG_NAME} PRIVATE ${ROBOCIN_PROJECT_PATH})
  target_include_directories(${ARG_NAME} PRIVATE ${CMAKE_BINARY_DIR})

  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_NAME="${ROBOCIN_PROJECT_NAME}")
  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_PATH="${ROBOCIN_PROJECT_PATH}")

  if (ARG_MACROS)
    target_compile_definitions(${ARG_NAME} ${ARG_MACROS})
  endif ()

  gtest_discover_tests(${ARG_NAME})

endfunction(robocin_cpp_test)

########################################################################################################################

# Add cpp benchmark test
# Named parameters:
#  NAME: name of the test
#  HDRS: header files
#  SRCS: source files
#  RSRCS: resource files
#  DEPS: dependencies
function(robocin_cpp_benchmark_test)
  cmake_parse_arguments(
          ARG                            # prefix of output variables
          ""                             # list of names of the boolean arguments
          "NAME"                         # list of names of mono-valued arguments
          "HDRS;SRCS;RSRCS;DEPS;MACROS"  # list of names of multi-valued arguments
          ${ARGN}                        # arguments of the function to parse (ARGN contains all the arguments after the function name)
  )

  # check if at least one source file is given with suffix '_benchmark.cpp'
  if (NOT ARG_SRCS)
    message(FATAL_ERROR "robocin_cpp_benchmark_test: no source files given")
  else ()
    set(FILTERED_SRCS ${ARG_SRCS})
    list(FILTER FILTERED_SRCS INCLUDE REGEX "_benchmark\.cpp$")

    if (NOT FILTERED_SRCS)
      message(FATAL_ERROR "robocin_cpp_benchmark_test: no source files given with suffix '_benchmark.cpp'")
    endif ()
  endif ()

  add_executable(${ARG_NAME} ${ARG_HDRS} ${ARG_SRCS} ${ARG_RSRCS}) # add test with given name, headers, sources and resources
  target_link_libraries(${ARG_NAME} PRIVATE benchmark::benchmark benchmark::benchmark_main ${ARG_DEPS}) # link library with given dependencies

  target_include_directories(${ARG_NAME} PRIVATE ${ROBOCIN_PROJECT_PATH})
  target_include_directories(${ARG_NAME} PRIVATE ${CMAKE_BINARY_DIR})

  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_NAME="${ROBOCIN_PROJECT_NAME}")
  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_PATH="${ROBOCIN_PROJECT_PATH}")

  if (ARG_MACROS)
    target_compile_definitions(${ARG_NAME} ${ARG_MACROS})
  endif ()

endfunction(robocin_cpp_benchmark_test)

########################################################################################################################

# Add cpp executable
# Named parameters:
#  NAME: name of the executable
#  HDRS: header files
#  SRCS: source files
#  RSRCS: resource files
#  DEPS: dependencies
function(robocin_cpp_executable)
  cmake_parse_arguments(
          ARG                            # prefix of output variables
          ""                             # list of names of the boolean arguments
          "NAME"                         # list of names of mono-valued arguments
          "HDRS;SRCS;RSRCS;DEPS;MACROS"  # list of names of multi-valued arguments
          ${ARGN}                        # arguments of the function to parse (ARGN contains all the arguments after the function name)
  )

  # check if at least one source file is given with suffix '_main.cpp'
  if (NOT ARG_SRCS)
    message(FATAL_ERROR "robocin_cpp_executable: no source files given")
  else ()
    set(FILTERED_SRCS ${ARG_SRCS})
    list(FILTER FILTERED_SRCS INCLUDE REGEX "_main\.cpp$")

    if (NOT FILTERED_SRCS)
      message(FATAL_ERROR "robocin_cpp_executable: no source files given with suffix '_main.cpp'")
    endif ()
  endif ()

  add_executable(${ARG_NAME} ${ARG_HDRS} ${ARG_SRCS} ${ARG_RSRCS}) # add executable with given name, headers, sources and resources
  target_link_libraries(${ARG_NAME} PRIVATE ${ARG_DEPS}) # link library with given dependencies

  target_include_directories(${ARG_NAME} PRIVATE ${ROBOCIN_PROJECT_PATH})
  target_include_directories(${ARG_NAME} PRIVATE ${CMAKE_BINARY_DIR})

  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_NAME="${ROBOCIN_PROJECT_NAME}")
  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_PATH="${ROBOCIN_PROJECT_PATH}")

  if (ARG_MACROS)
    target_compile_definitions(${ARG_NAME} ${ARG_MACROS})
  endif ()

endfunction(robocin_cpp_executable)

########################################################################################################################
