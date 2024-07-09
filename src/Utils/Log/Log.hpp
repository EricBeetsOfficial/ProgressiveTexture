#pragma once

#include <Log.h>

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
    void Log::color(const string &color, std::ostream& out)
    {
        cout << "\x1B["<< _colors[color] << "m";
    }

    inline void Log::restore(std::ostream& out)
    {
        out << "\033[0m\t\t";
        endl(cout);
    }
}