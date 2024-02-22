///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            IThreadPoolFwd.hpp
/// @authors         Poturaiev Anton
/// @date            21.02.2024
///
/// @brief           Forward declaration for @interface IThreadPool.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <memory>
#include <functional>

namespace Darkness::Concurrency {
    using tTask = std::function<void()>;

    struct IThreadPool;

    using tThreadPoolUniquePtr = std::unique_ptr<IThreadPool>;
    using tThreadPoolSharedPtr = std::shared_ptr<IThreadPool>;
} /// end namespace Darkness::Concurrency
