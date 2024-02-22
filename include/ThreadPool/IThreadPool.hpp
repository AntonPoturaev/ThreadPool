///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            IThreadPool.hpp
/// @authors         Poturaiev Anton
/// @date            21.02.2024
///
/// @brief           Declaration of @interface IThreadPool.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ThreadPool/IThreadPoolFwd.hpp>

namespace Darkness::Concurrency {
    struct IThreadPool {
        virtual ~IThreadPool() = 0;

        virtual size_t ThreadCount() const noexcept = 0;

        virtual bool IsEmpty() const noexcept = 0;

        virtual void AddTask(tTask&& task) noexcept(false) = 0;
        virtual void AddTask(tTask const& task) noexcept(false) = 0;

        virtual void Stop() noexcept = 0;
        virtual bool IsStoped() const noexcept = 0;

        virtual void Pause(bool state) noexcept = 0;
        virtual bool IsPaused() const noexcept = 0;
    };
} /// end namespace Darkness::Concurrency
