#
# Copyright (c) 2024 Michael Caisse
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 3.25)

project(
    stm32-groov
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION
        "groov definitions for accessing STM32 special function registers")

include(cmake/get_cpm.cmake)
cpmaddpackage("gh:intel/cicd-repo-infrastructure#main")

add_versioned_package("gh:intel/cpp-std-extensions#c0b4c44")
add_versioned_package("gh:intel/generic-register-operation-optimizer#e7a64d4")

add_library(stm32-groov INTERFACE)
target_include_directories(stm32-groov INTERFACE include)
target_link_libraries_system(stm32-groov INTERFACE groov stdx)

