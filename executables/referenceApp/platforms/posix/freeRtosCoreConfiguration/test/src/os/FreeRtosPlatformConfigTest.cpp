/********************************************************************************
 * Copyright (c) 2026 RemotiveLabs AB
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "os/FreeRtosPlatformConfig.h"

#include <gtest/gtest.h>

#include <pthread.h>
#include <unistd.h>

#include <cstdint>
#include <vector>

namespace
{
/**
 * \desc: MINIMUM_STACK_SIZE is a hard-coded guess of the C library's PTHREAD_STACK_MIN, which is
 *        not a compile time constant with _GNU_SOURCE. If it is too small for the C library the
 *        POSIX port falls back to the default pthread stack for every task and prints a warning,
 *        so pin the guess to the C library this test is built against.
 */
TEST(FreeRtosPlatformConfigTest, minimumStackSizeCoversPthreadStackMin)
{
    long const pthreadStackMin = sysconf(_SC_THREAD_STACK_MIN);
    ASSERT_GT(pthreadStackMin, 0L);
    EXPECT_GE(static_cast<long>(MINIMUM_STACK_SIZE), pthreadStackMin);
}

/**
 * \desc: The POSIX port hands the task stack to pthread_attr_setstack(), which rejects stacks
 *        smaller than PTHREAD_STACK_MIN with EINVAL. A stack of MINIMUM_STACK_SIZE bytes must be
 *        accepted.
 */
TEST(FreeRtosPlatformConfigTest, pthreadAcceptsStackOfMinimumStackSize)
{
    std::vector<uint8_t> stack(MINIMUM_STACK_SIZE);
    pthread_attr_t attributes;
    ASSERT_EQ(0, pthread_attr_init(&attributes));
    EXPECT_EQ(0, pthread_attr_setstack(&attributes, stack.data(), stack.size()));
    EXPECT_EQ(0, pthread_attr_destroy(&attributes));
}

} // namespace
