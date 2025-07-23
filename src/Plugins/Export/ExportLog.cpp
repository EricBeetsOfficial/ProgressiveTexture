#include <ExportInterface.h>
#include <Callback.h>

extern "C"
{
    void INTERFACE_EXPORT INTERFACE_API LogTest()
    {
        LOG_DEBUG("Debug");
        LOG_INFO("Info");
        LOG_WARN("Warn");
        LOG_ERROR("Error");
    }

    void INTERFACE_EXPORT INTERFACE_API LogLevel(int logLevel)
    {
        // Error = 0, Warning = 1, Info = 2, Debug = 3
        Utils::Log::Level((Utils::Log::Level_t)logLevel);

    }

    void INTERFACE_EXPORT INTERFACE_API LogRegisterCallback(Utils::Delegate::LogCallback callback)
    {
        // Force the queued log mode
        Utils::Log::Mode(Utils::Log::Mode_t::Queued);
        Utils::Delegate::ExportLog::logCallback = callback;
    }

    void INTERFACE_EXPORT INTERFACE_API LogUnregisterCallback()
    {
        Utils::Delegate::ExportLog::logCallback = nullptr;
    }
}