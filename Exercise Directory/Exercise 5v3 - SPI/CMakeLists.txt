cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
# Only build the components this project actually uses (faster builds)
idf_build_set_property(MINIMAL_BUILD ON)
project(SPI)
