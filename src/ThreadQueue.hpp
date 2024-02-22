///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            ThreadQueue.hpp
/// @authors         Poturaiev Anton
/// @date            22.02.2024
///
/// @brief           Declaration of @class ThreadQueue.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ThreadPool/IThreadPool.hpp>

#include <mutex>
#include <queue>

namespace Darkness::Concurrency::Details {
    class ThreadQueue final {
    public:
        using tAccess = std::recursive_mutex;

    private:
        using tLock = std::lock_guard<tAccess> const;
        using tQueue = std::queue<tTask>;

    public:
        bool IsEmpty() const noexcept;

        template<typename TaskT>
        void Emplace(TaskT&& task) {
            tLock lock(m_Access);
            m_Queue.emplace(std::forward<TaskT>(task));
        }

        tAccess& Access() noexcept;

        tTask PikUpFront();

    private:
        tQueue m_Queue;
        tAccess mutable m_Access;
    };
} /// end namespace Darkness::Concurrency::Details
