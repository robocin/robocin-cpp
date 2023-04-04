########################################################################################################################

cmake_minimum_required(VERSION 3.16)

########################################################################################################################

project(robocin LANGUAGES CXX)

########################################################################################################################

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake) # add our custom cmake modules to the module path

include(cmake/deps.cmake) # load our dependencies
include(cmake/rules.cmake) # load our custom rules

########################################################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROBOCIN_PROJECT_PATH}/bin) # set the output directory for all executables

########################################################################################################################

add_subdirectory(${ROBOCIN_PROJECT_NAME}) # add the source directory to the build

########################################################################################################################
