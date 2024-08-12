#pragma once

#include <string>
#include <iostream>
#include <format>
#include <map>
#include <queue>
#include <mutex>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::map;

#if NDEBUG
# define DEBUG(...)
# define INFO(...)
#else
# define DEBUG(...) Utils::Log::Debug("[", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);
# define INFO(...)  Utils::Log::Info ("[", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);
#endif

#define WARN(...)  Utils::Log::Warn ("[", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);
#define ERROR(...)   Utils::Log::Error  ("[", __FILE__, " ", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);
#define CONSOLE(...) Utils::Log::Console("[", __FUNCTION__, ":", __LINE__, "] ", __VA_ARGS__);

namespace Utils
{
    class Log
    {
#pragma region Level
     public:
        enum class Level_t {Error, Warning, Info, Debug};

        static void Level(Level_t level);

     private:
        inline static Level_t _level = Level_t::Debug;
#pragma endregion

#pragma region Mode
     public:
        enum class Mode_t {Classic, Queued};

        static void Mode(Mode_t mode);

        inline static std::pair<std::string, std::string> GetLast()
        {
            std::pair<std::string, std::string> message ("", "");
            if (!_queue.empty())
            {
                message = _queue.front();
                _queue.pop();
            }
            return message;
        }
     private:
        inline static Mode_t _mode = Mode_t::Classic;
        inline static std::queue<std::pair<std::string, std::string>> _queue;
#pragma endregion

#pragma region Ouputs
     public:
        template<typename... Args>
        static void Debug(Args&&... args);

        template<typename... Args>
        static void Info(Args&&... args);

        template<typename... Args>
        static void Warn(Args&&... args);

        template<typename... Args>
        static void Error(Args&&... args);

        template<typename... Args>
        static void Console(Args&&... args);
#pragma endregion

#pragma region Color
     private:
        template<typename... Args>
        static void color(const string &color, std::ostream& out = cout);

        static void restore(std::ostream& out = cout);
#pragma endregion

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

#include <Log.hpp>