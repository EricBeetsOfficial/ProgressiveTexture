#pragma once

#include <random>
#include <string>
#include <filesystem>

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

    static bool IsPowerOf2(unsigned int value)
    {
        return (value & (value - 1)) == 0;
    }

    static unsigned int HighestPowerOf2(unsigned int value)
    {
        // https://graphics.stanford.edu/%7Eseander/bithacks.html#RoundUpPowerOf2
        value--;
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;
        return ++value;
    }

    static unsigned int SmallestPowerOf2(unsigned int value)
    {
        unsigned int v = log2(value);
        return pow(2, v);
    }

    static unsigned int ClosestPowerOf2(unsigned int value)
    {
        unsigned int highest = HighestPowerOf2(value);
        unsigned int smallest = SmallestPowerOf2(value);
        if ((value - smallest) < (highest - value))
            return smallest;
        return highest;
    }

    static std::string FileName(const std::string& filePath)
    {
        std::filesystem::path path(filePath);
        return path.stem().generic_string();
    }

    static std::string FileNameExtension(const std::string& filePath)
    {
        std::filesystem::path path(filePath);
        return path.extension().generic_string();
    }
}
