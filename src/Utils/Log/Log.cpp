#include <Log.h>

using namespace Utils;

std::mutex Log::_mutex;

void Log::Level(Level_t level)
{
    _level = level;
}

void Log::Mode(Mode_t mode)
{
    _mode = mode;
}