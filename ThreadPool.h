#pragma once

#include <mutex>
#include <thread>
#include <queue>
#include <atomic>
#include <functional>
#include <condition_variable>

namespace ThreadPool {
    class ThreadPool {
        using tAccess = std::recursive_mutex;
        using tUniqueLock = std::unique_lock<tAccess>;
        using tCondition = std::condition_variable_any;
        using tThreads = std::vector<std::thread>;
        using tTask = std::function<void()>;
        using tTaskQueue = std::queue<tTask>;
        using tAtomicBool = std::atomic<bool>; 

    public:
        explicit ThreadPool(size_t threadCount = std::thread::hardware_concurrency()) noexcept;

        ThreadPool(const ThreadPool&) noexcept = delete;
        ThreadPool& operator=(const ThreadPool&) noexcept = delete;

        ~ThreadPool() noexcept;

        size_t ThreadCount() const noexcept;

        void AddTask(tTask&& task);
        void AddTask(tTask const& task);

        void Stop() noexcept;
        void Pause(bool state) noexcept;

    private:
        void _Routine();
        tTask _GetTask() noexcept;

    private:
        tThreads mStorage;
        tTaskQueue mQueue;
        tAccess mAccess;
        tCondition mCondition;
        tAtomicBool mShouldStopProcessing = false;
        tAtomicBool mIsStop = false;
        tAtomicBool mIsPaused = false;
    };
} /// end namespace ThreadPool
