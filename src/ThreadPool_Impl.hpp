///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            ThreadPool_Impl.hpp
/// @authors         Poturaiev Anton
/// @date            22.02.2024
///
/// @brief           Declaration of @class ThreadPool.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ThreadPool/IThreadPool.hpp>

namespace Darkness::Concurrency {
    class ThreadPool : public IThreadPool {
    public:
        explicit ThreadPool(size_t threadCount) noexcept;

        size_t ThreadCount() const noexcept override;

        bool IsEmpty() const noexcept override;

        void AddTask(tTask&& task) noexcept(false) override;
        void AddTask(tTask const& task) noexcept(false) override;

        void Stop() noexcept override;
        bool IsStoped() const noexcept override;

        void Pause(bool state) noexcept override;
        bool IsPaused() const noexcept override;

    private:
        tThreadPoolUniquePtr m_Impl;
    };
} /// end namespace Darkness::Concurrency
