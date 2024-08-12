#include <IUnityInterface.h>
#include <ExportLog.h>

extern "C"
{
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API LogTest()
    {
        DEBUG("Debug");
        INFO("Info");
        WARN("Warn");
        ERROR("Error");
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API LogLevel(int logLevel)
    {
        // Error = 0, Warning = 1, Info = 2, Debug = 3
        Utils::Log::Level((Utils::Log::Level_t)logLevel);

    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API LogRegisterCallback(Utils::ExportLog::LogCallback callback)
    {
        // Force the queued log mode
        Utils::Log::Mode(Utils::Log::Mode_t::Queued);
        Utils::ExportLog::logCallback = callback;
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API LogUnregisterCallback()
    {
        Utils::ExportLog::logCallback = nullptr;
    }
}