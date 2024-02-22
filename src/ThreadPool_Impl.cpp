///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            ThreadPool_Impl.cpp
/// @authors         Poturaiev Anton
/// @date            20.02.2024
///
/// @brief           Implementation of class ThreadPool.
///
////////////////////////////////////////////////////////////////////////////////

#include "ThreadPool_Impl.hpp"
#include "ThreadPool_Details.hpp"

#include <cassert>

namespace Darkness::Concurrency {
    ThreadPool::ThreadPool(size_t threadCount) noexcept
        : m_Impl(std::make_unique<Details::ThreadPool>(threadCount))
    {
    }

    size_t ThreadPool::ThreadCount() const noexcept {
        return m_Impl->ThreadCount();
    }

    bool ThreadPool::IsEmpty() const noexcept {
        return m_Impl->IsEmpty();
    }

    void ThreadPool::AddTask(tTask&& task) noexcept(false) {
        m_Impl->AddTask(std::forward<tTask>(task));
    }

    void ThreadPool::AddTask(tTask const& task) noexcept(false) {
        m_Impl->AddTask(task);
    }

    void ThreadPool::Stop() noexcept {
        m_Impl->Stop();
    }

    bool ThreadPool::IsStoped() const noexcept {
        return m_Impl->IsStoped();
    }

    void ThreadPool::Pause(bool state) noexcept {
        m_Impl->Pause(state);
    }

    bool ThreadPool::IsPaused() const noexcept {
        return m_Impl->IsPaused();
    }
} /// end namespace Darkness::Concurrency
