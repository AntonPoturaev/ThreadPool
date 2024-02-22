///////////////////////////////////////////////////////////////////////////////
///
/// Project           ThreadPool library
/// Copyright (c)     Poturaiev Anton, 2024
///
////////////////////////////////////////////////////////////////////////////////
/// @file            ThreadStorage.hpp
/// @authors         Poturaiev Anton
/// @date            22.02.2024
///
/// @brief           Declaration of @class ThreadStorage.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ThreadPool/IThreadPoolFwd.hpp>

#include <thread>
#include <vector>

namespace Darkness::Concurrency::Details {
    class ThreadStorage final {
        using tStorage = std::vector<std::thread>;

    public:
        explicit ThreadStorage(size_t threadCount, tTask const& routine) noexcept;
        ~ThreadStorage();

        ThreadStorage(ThreadStorage&) noexcept = delete;
        ThreadStorage& operator=(ThreadStorage const&) noexcept = delete;

        size_t Count() const noexcept;

    private:
        tStorage m_Storage;
    };
} /// end namespace Darkness::Concurrency::Details
