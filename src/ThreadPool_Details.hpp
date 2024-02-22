///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            ThreadPool_Details.hpp
/// @authors         Poturaiev Anton
/// @date            22.02.2024
///
/// @brief           Declaration of @class ThreadPool.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ThreadPool/IThreadPool.hpp>
#include "ThreadStorage.hpp"
#include "ThreadQueue.hpp"

#include <atomic>
#include <condition_variable>

namespace Darkness::Concurrency::Details {
    class ThreadPool : public IThreadPool {
        using tUniqueLock = std::unique_lock<ThreadQueue::tAccess>;
        using tCondition = std::condition_variable_any;
        using tAtomicBool = std::atomic<bool>;

    public:
        explicit ThreadPool(size_t threadCount) noexcept;

        ThreadPool(ThreadPool const&) noexcept = delete;
        ThreadPool& operator=(ThreadPool const&) noexcept = delete;

        ~ThreadPool();

        size_t ThreadCount() const noexcept override;

        bool IsEmpty() const noexcept override;

        void AddTask(tTask&& task) noexcept(false) override;
        void AddTask(tTask const& task) noexcept(false) override;

        void Stop() noexcept override;
        bool IsStoped() const noexcept override;

        void Pause(bool state) noexcept override;
        bool IsPaused() const noexcept override;

    private:
        void _Routine();

        tTask _GetTask() noexcept;

        template<typename TaskT>
        void _AddTask(TaskT&& task) noexcept(false);

    private:
        ThreadStorage m_Storage;
        ThreadQueue m_Queue;
        tCondition m_Condition;
        tAtomicBool m_ShouldStopProcessing = false;
        tAtomicBool m_IsStop = false;
        tAtomicBool m_IsPaused = false;
    };
} /// end namespace Darkness::Concurrency::Details
