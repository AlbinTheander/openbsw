# *******************************************************************************
# Copyright (c) 2026 RemotiveLabs AB
#
# This program and the accompanying materials are made available under the
# terms of the Apache License Version 2.0 which is available at
# https://www.apache.org/licenses/LICENSE-2.0
#
# SPDX-License-Identifier: Apache-2.0
# *******************************************************************************

add_executable(freeRtosPlatformConfigTest src/os/FreeRtosPlatformConfigTest.cpp)

# The unit test build resolves os/FreeRtosPlatformConfig.h to the mock in
# libs/bsw/asyncFreeRtos. This test is about the referenceApp's POSIX
# configuration, so include that header explicitly.
target_include_directories(freeRtosPlatformConfigTest BEFORE PRIVATE ../include)

target_link_libraries(freeRtosPlatformConfigTest PRIVATE gtest_main)

gtest_discover_tests(freeRtosPlatformConfigTest
                     PROPERTIES LABELS "freeRtosPlatformConfigTest")
