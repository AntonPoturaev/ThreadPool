#include "ThreadPool.h"

namespace ThreadPool {
    ThreadPool::ThreadPool(size_t threadCount) noexcept
        : mStorage(threadCount)
    {
        for (auto& worker : mStorage)
            worker = std::thread(&ThreadPool::_Routine, this);
    }

    ThreadPool::~ThreadPool() noexcept
    {
        mShouldStopProcessing = true;
        mCondition.notify_all();

        for (auto& worker : mStorage)
            if (worker.joinable())
                worker.join();
    }

    size_t ThreadPool::ThreadCount() const noexcept { return mStorage.size(); }

    void ThreadPool::AddTask(tTask&& task)
    {
        if (mShouldStopProcessing || mIsStop)
            throw std::runtime_error("ERROR: ThreadPool::AddTask() - attempted to add task to stopped pool!");

        {
            tUniqueLock const lock(mAccess);
            mQueue.emplace(std::forward<tTask>(task));
        }

        mCondition.notify_one();
    }

    void ThreadPool::AddTask(tTask const& task)
    {
        if (mShouldStopProcessing || mIsStop)
            throw std::runtime_error("ERROR: ThreadPool::AddTask() - attempted to add task to stopped pool!");

        {
            tUniqueLock const lock(mAccess);
            mQueue.push(task);
        }

        mCondition.notify_one();
    }

    void ThreadPool::Stop() noexcept
    {
        mIsStop = true;
        mCondition.notify_all();
    }

    void ThreadPool::Pause(bool state) noexcept
    {
        mIsPaused = state;
        mCondition.notify_all();
    }

    void ThreadPool::_Routine()
    {
        while (true)
        {
            try
            {
                if (tTask task = _GetTask())
                    task();
                else
                    return;
            }
            catch (...)
            {
                throw;
            }
        }
    }

    ThreadPool::tTask ThreadPool::_GetTask() noexcept
    {
        tUniqueLock lock(mAccess);

        mCondition.wait(lock, [this]() {
            return (!mQueue.empty() && !mIsPaused) || mShouldStopProcessing || mIsStop;
            });

        if ((mShouldStopProcessing && mQueue.empty()) || mIsStop)
            return {};

        auto task = std::move(mQueue.front());
        mQueue.pop();

        return task;
    }
} /// end namespace ThreadPool
