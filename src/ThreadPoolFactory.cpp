///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            ThreadPoolFactory.cpp
/// @authors         Poturaiev Anton
/// @date            22.02.2024
///
/// @brief           Implementation of @class ThreadPoolFactory.
///
////////////////////////////////////////////////////////////////////////////////

#include <ThreadPool/ThreadPoolFactory.hpp>

#include "ThreadPool_Impl.hpp"

#include <thread>

namespace Darkness::Concurrency {
    uint32_t ThreadPoolFactory::HardwareConcurrency() noexcept {
        return std::thread::hardware_concurrency();
    }

    [[nodiscard]]
    tThreadPoolUniquePtr ThreadPoolFactory::MakeUnique(uint32_t threadsCount) noexcept {
        return std::make_unique<ThreadPool>(threadsCount);
    }

    [[nodiscard]]
    tThreadPoolSharedPtr ThreadPoolFactory::MakeShared(uint32_t threadsCount) noexcept {
        return std::make_shared<ThreadPool>(threadsCount);
    }
} /// end namespace Darkness::Concurrency
