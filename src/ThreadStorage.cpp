///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            ThreadStorage.cpp
/// @authors         Poturaiev Anton
/// @date            22.02.2024
///
/// @brief           Implementation of @class ThreadStorage.
///
////////////////////////////////////////////////////////////////////////////////

#include "ThreadStorage.hpp"

namespace Darkness::Concurrency::Details {
    ThreadStorage::ThreadStorage(size_t threadCount, tTask const& routine) noexcept
        : m_Storage(threadCount)
    {
        for (auto& worker : m_Storage)
            worker = std::thread(routine);
    }

    ThreadStorage::~ThreadStorage() {
        for (auto& worker : m_Storage)
            if (worker.joinable())
                worker.join();
    }

    size_t ThreadStorage::Count() const noexcept {
        return m_Storage.size();
    }
} /// end namespace Darkness::Concurrency::Details

