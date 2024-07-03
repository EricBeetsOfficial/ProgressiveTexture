#include <random>

namespace Utils
{
    static int Random(int min = 0, int max = 10)
    {
        srand( (unsigned)time(NULL) );

        return rand() % (max - min) + min;
    }
}
