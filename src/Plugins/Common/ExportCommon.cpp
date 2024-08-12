#include <IUnityInterface.h>
#include <Log.h>

#include <cstdlib>

extern "C"
{
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ReleaseChar(char* ptr)
    {
        free(ptr);
    }
}