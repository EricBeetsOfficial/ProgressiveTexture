#pragma once

#include <queue>
#include <thread>
#include <Log.h>

template<typename T>
class ThreadWorker;

class ITasks
{
    template<typename T>
    friend class ThreadWorker;
 public:
    ITasks(const std::string& name = "") :  _name {name},
                                            _currentProcess {nullptr, false},
                                            _isDone{false},
                                            _nonThreadRunning {false},
                                            _threadRunning {false} { }

 public:
    void addTask(std::function<bool()> func, bool threaded)
    {
        _processes.push(std::make_pair(move(func), threaded));
    }

    bool isEmpty() const
    {
        return _processes.empty();
    }

    bool isRunning() const
    {
        return _currentProcess.second ? _threadRunning.load() : _nonThreadRunning;
    }

    bool isDone() const
    {
        return _isDone;
    }

    bool isComplete() const
    {
        return !isRunning() && isDone();
    }

 private:
    bool runTasks()
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

 private:
    std::pair<std::function<bool()>, bool> _currentProcess;
    std::string _name;
    std::queue<std::pair<std::function<bool()>, bool>> _processes;

    std::jthread _thread;
    std::atomic<bool> _threadRunning;
    bool _nonThreadRunning;
    bool _isDone;
};