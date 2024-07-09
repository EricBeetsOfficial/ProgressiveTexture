#include <Log.h>

using namespace Utils;

std::mutex Log::_mutex;

void Log::Level(Level_t level)
{
    _level = level;
}

