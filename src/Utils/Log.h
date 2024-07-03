#pragma once

#include <string>
#include <iostream>
#include <format>
#include <map>
#include <mutex>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::map;

#if NDEBUG
# define DEBUG(...)
# define INFO(...)
# define WARN(...)
#else
# define DEBUG(...) Utils::Log::Debug("[", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);
# define INFO(...)  Utils::Log::Info ("[", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);
# define WARN(...)  Utils::Log::Warn ("[", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);
#endif

#define ERROR(...)   Utils::Log::Error  ("[", __FILE__, " ", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);
#define CONSOLE(...) Utils::Log::Console("[", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);

#define PRINT(p, c, args)  {\
                            std::unique_lock<std::mutex> lock(_mutex); \
                            color(c); \
                            cout << p; \
                            ((cout << std::forward<Args>(args)), ...); \
                            restore(); \
                        }
namespace Utils
{
    class Log
    {
     public:
        enum class Level_t {Error, Warning, Info, Debug};
        static void Level(Level_t level)
        {
            _level = level;
        }

     private:
        inline static Level_t _level = Level_t::Debug;

     public:
        template<typename... Args>
        static void Debug(Args&&... args)
        {
            if (_level >= Level_t::Debug)
                PRINT("[DEBUG]  ", "BLUE", args);
        }

        template<typename... Args>
        static void Info(Args&&... args)
        {
            if (_level >= Level_t::Info)
                PRINT("[INFO]   ", "GREEN", args);
        }

        template<typename... Args>
        static void Warn(Args&&... args)
        {
            if (_level >= Level_t::Warning)
                PRINT("[WARING] ", "YELLOW", args);
        }

        template<typename... Args>
        static void Error(Args&&... args)
        {
            if (_level >= Level_t::Error)
                PRINT("[ERROR]  ", "RED", args);
        }

        template<typename... Args>
        static void Console(Args&&... args)
        {
            std::unique_lock<std::mutex> lock(_mutex); \
            ((cout << std::forward<Args>(args)), ...);
        }

     private:
        template<typename... Args>
        static void color(const string &color, std::ostream& out = cout)
        {
            cout << "\x1B["<< _colors[color] << "m";
        }

        static void restore(std::ostream& out = cout)
        {
            out << "\033[0m\t\t";
            endl(cout);
        }

     private:
        static std::mutex _mutex;
        inline static map<string, string> _colors =
        {
            {"RED", "31"},
            {"BLUE", "34"},
            {"YELLOW", "33"},
            {"GREEN", "32"},
        };
    };
}