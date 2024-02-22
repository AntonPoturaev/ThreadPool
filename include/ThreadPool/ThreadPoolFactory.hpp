///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            ThreadPoolFactory.hpp
/// @authors         Poturaiev Anton
/// @date            21.02.2024
///
/// @brief           Declaration of @class ThreadPoolFactory.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ThreadPool/IThreadPoolFwd.hpp>

namespace Darkness::Concurrency {
    struct ThreadPoolFactory {
        static uint32_t HardwareConcurrency() noexcept;

        [[nodiscard]]
        static tThreadPoolUniquePtr MakeUnique(uint32_t threadsCount = HardwareConcurrency()) noexcept;

        [[nodiscard]]
        static tThreadPoolSharedPtr MakeShared(uint32_t threadsCount = HardwareConcurrency()) noexcept;
    };
} /// end namespace Darkness::Concurrency
