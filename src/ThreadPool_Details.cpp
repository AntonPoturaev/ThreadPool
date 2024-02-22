///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            ThreadPool_Details.cpp
/// @authors         Poturaiev Anton
/// @date            22.02.2024
///
/// @brief           Implementation of @class ThreadPool.
///
////////////////////////////////////////////////////////////////////////////////

#include "ThreadPool_Details.hpp"

#include <cassert>

namespace Darkness::Concurrency::Details {
    ThreadPool::ThreadPool(size_t threadCount) noexcept
        : m_Storage(threadCount, std::bind(&ThreadPool::_Routine, this))
    {
    }

    ThreadPool::~ThreadPool() noexcept {
        m_ShouldStopProcessing = true;
        m_Condition.notify_all();
    }

    size_t ThreadPool::ThreadCount() const noexcept {
        return m_Storage.Count();
    }

    bool ThreadPool::IsEmpty() const noexcept {
        return m_Queue.IsEmpty();
    }

    void ThreadPool::AddTask(tTask&& task) noexcept(false) {
        _AddTask(task);
    }

    void ThreadPool::AddTask(tTask const& task) noexcept(false) {
        _AddTask(task);
    }

    void ThreadPool::Stop() noexcept {
        if (!m_IsStop)
        {
            m_IsStop = true;
            m_Condition.notify_all();
        }
    }

    bool ThreadPool::IsStoped() const noexcept {
        return m_IsStop;
    }

    void ThreadPool::Pause(bool state) noexcept {
        assert(!m_IsStop && "Bad logic!");

        if (!m_IsStop)
        {
            m_IsPaused = state;
            m_Condition.notify_all();
        }
    }

    bool ThreadPool::IsPaused() const noexcept {
        return m_IsPaused;
    }

    void ThreadPool::_Routine() {
        while (true)
        {
            try
            {
                if (auto task = _GetTask())
                {
                    task();
                }
                else
                    return;
            }
            catch (...)
            {
                throw;
            }
        }

    }

    tTask ThreadPool::_GetTask() noexcept {
        tUniqueLock lock(m_Queue.Access());

        m_Condition.wait(lock, [this]() {
            return (!m_Queue.IsEmpty() && !m_IsPaused) || m_ShouldStopProcessing || m_IsStop;
            });

        if ((m_ShouldStopProcessing && m_Queue.IsEmpty()) || m_IsStop)
            return {};

        return m_Queue.PikUpFront();
    }

    template<typename TaskT>
    void ThreadPool::_AddTask(TaskT&& task) noexcept(false) {
        if (m_ShouldStopProcessing || m_IsStop)
            throw std::runtime_error("ERROR: ThreadPool::AddTask() - attempted to add task to stopped pool!");

        m_Queue.Emplace(std::forward<TaskT>(task));

        m_Condition.notify_one();
    }

} /// end namespace Darkness::Concurrency::Details
