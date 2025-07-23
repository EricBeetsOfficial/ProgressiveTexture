#pragma once

#include <Log.h>
#include <sstream>

template <typename T>
std::string toString(T&& value)
{
    std::ostringstream oss;
    oss << std::forward<T>(value);
    return oss.str();
}

#define PRINT(level, c, args)  {\
                            std::unique_lock<std::mutex> lock(_mutex); \
                            colorChange(c); \
                            cout << level; \
                            ((cout << " " << std::forward<Args>(args)), ...); \
                            if (Utils::Log::_mode == Utils::Log::Mode_t::Queued) { \
                                 _queue.push(std::make_pair(std::string(level) + ((std::string(" ") + toString(std::forward<Args>(args))) + ...), c)); \
                            } \
                            colorReset(); \
                        }

namespace Utils
{
    template<typename... Args>
    void Log::Debug(Args&&... args)
    {
        if (_level >= Level_t::Debug)
            PRINT("[DEBUG]  ", "BLUE", args);
    }

    template<typename... Args>
    void Log::Info(Args&&... args)
    {
        if (_level >= Level_t::Info)
            PRINT("[INFO]   ", "GREEN", args);
    }

    template<typename... Args>
    void Log::Warn(Args&&... args)
    {
        if (_level >= Level_t::Warning)
            PRINT("[WARING] ", "YELLOW", args);
    }

    template<typename... Args>
    void Log::Error(Args&&... args)
    {
        if (_level >= Level_t::Error)
            PRINT("[ERROR]  ", "RED", args);
    }

    template<typename... Args>
    void Log::Console(Args&&... args)
    {
        std::unique_lock<std::mutex> lock(_mutex); \
        ((cout << std::forward<Args>(args)), ...);
    }

    template<typename... Args>
    void Log::Assert(bool condition, Args&&... args)
    {
         if (_level >= Level_t::Error && !condition)
            PRINT("[ASSERT]  ", "YELLOW", args);
    }

    template<typename... Args>
    void Log::colorChange(const string &color, std::ostream& out)
    {
        cout << "\x1B["<< _colors[color] << "m";
    }

    inline void Log::colorReset(std::ostream& out)
    {
        out << "\033[0m\t\t";
        endl(cout);
    }
}