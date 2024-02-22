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
/// @brief           Implementation of @class ThreadQueue.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ThreadQueue.hpp"

#include <cassert>

namespace Darkness::Concurrency::Details {
    bool ThreadQueue::IsEmpty() const noexcept {
        tLock lock(m_Access);
        return m_Queue.empty();
    }

    ThreadQueue::tAccess& ThreadQueue::Access() noexcept {
        return m_Access;
    }

    tTask ThreadQueue::PikUpFront() {
        assert(!m_Queue.empty());
        auto task = std::move(m_Queue.front());
        m_Queue.pop();
        return task;
    }
} /// end namespace Darkness::Concurrency::Details
