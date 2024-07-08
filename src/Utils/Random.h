#pragma once

#include <random>

namespace Utils
{
    static void InitRand()
    {
        srand( (unsigned)time(NULL) );
    }

    static int Random(int min = 0, int max = 10)
    {
        return rand() % (max - min) + min;
    }
}
