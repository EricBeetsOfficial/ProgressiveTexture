#include <conio.h>
#include <functional>
#include <Console.h>
#include <Log.h>

namespace Utils
{
    char running[] = { '|', '/', '-', '\\'};

    bool getInput(char *c)
    {
        if (kbhit())
        {
            *c = getch();
            return true; // Key Was Hit
        }
        return false; // No keys were pressed
    }

    void loop(std::function<bool()> func)
    {
        int runningState = 0;
        char key = ' ';
    	Utils::Log::Warn("Press q to quit");
        while (key != 'q')
        {
            while (!getInput(&key))
            {
                Utils::Log::Console(running[runningState], " ", '\r');
                runningState = (runningState + 1) % strlen(running);
                if (func())
                {
                    key = 'q';
                    break;
                }
            }
        }
    }
}