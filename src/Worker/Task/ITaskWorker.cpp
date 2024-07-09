#include <ITaskWorker.h>

ITaskWorker::ITaskWorker(const std::string& name) :_name             {name},
                                         _currentProcess   {nullptr, false},
                                         _isDone           {false},
                                         _nonThreadRunning {false},
                                         _threadRunning    {false}
{
}

void ITaskWorker::addTask(std::function<bool()> func, bool threaded)
{
    _processes.push(std::make_pair(move(func), threaded));
}

bool ITaskWorker::isEmpty() const
{
    return _processes.empty();
}

bool ITaskWorker::isRunning() const
{
    return _currentProcess.second ? _threadRunning.load() : _nonThreadRunning;
}

bool ITaskWorker::isDone() const
{
    return _isDone;
}

bool ITaskWorker::isComplete() const
{
    return !isRunning() && isDone();
}

bool ITaskWorker::runTasks()
{
    if (_currentProcess.first == nullptr)
    {
        if (!_processes.empty())
        {
            _currentProcess = move(_processes.front());
            _isDone = false;
            // Threaded task
            if (_currentProcess.second)
            {
                _threadRunning = true;
                _thread = std::jthread([&]()
                {
                    _currentProcess.first();
                    _threadRunning = false;
                });
            }
            // Non-threaded task
            else
            {
                _nonThreadRunning = !_currentProcess.first();
            }
        }
    }
    else
    {
        if (isRunning() && (_currentProcess.second == false))
        {
            _nonThreadRunning = !_currentProcess.first();
        }
        else if (!isRunning())
        {
            _isDone = true;
            _currentProcess.first = nullptr;
            _processes.pop();
        }
    }
    return _processes.empty() && (_currentProcess.first == nullptr);
}