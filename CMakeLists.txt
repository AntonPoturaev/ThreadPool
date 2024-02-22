cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ThreadPool")

include_directories("include")

set(SRC
    "src/IThreadPool.cpp"
    "src/ThreadPoolFactory.cpp"
    "src/ThreadPool_Impl.hpp"
    "src/ThreadPool_Impl.cpp"
    "src/ThreadPool_Details.hpp"
    "src/ThreadPool_Details.cpp"
    "src/ThreadStorage.hpp"
    "src/ThreadStorage.cpp"
    "src/ThreadQueue.hpp"
    "src/ThreadQueue.cpp"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message("Build ${PROJECT_NAME} for LINUX")
    add_library(${PROJECT_NAME} ${SRC})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message("Build ${PROJECT_NAME} for WINDOWS")
    add_library(${PROJECT_NAME} ${SRC})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(WARNING "Currently unimplemented!")
    message(FATAL_ERROR "Build ${PROJECT_NAME} for APPLE")
    add_library(${PROJECT_NAME} MACOSX_BUNDLE ${SRC})
else()
    message(WARNING "Build ${PROJECT_NAME} for unknown OS")
    add_library(${PROJECT_NAME} ${SRC})
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "src"
    INTERFACE
        "include"
)
