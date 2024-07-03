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
    ITasks(const std::string& name = "") : _name {name}, _currentTask{nullptr, false} { }

 public:
    void addTask(std::function<bool()> func, bool threaded)
    {
        _tasks.push(std::make_pair(move(func), threaded));
    }

    // unsigned int countTask() const
    // {
    //     return _tasks.size();
    // }

    // bool isEmpty() const
    // {
    //     return _tasks.empty();
    // }

    bool isRunning() const
    {
        return _currentTask.second ? _threadRunning.load() : _nonThreadRunning;
    }

 private:
    bool runTasks()
    {
        if (_currentTask.first == nullptr)
        {
            if (!_tasks.empty())
            {
                _currentTask = move(_tasks.front());
                _tasks.pop();
                // Threaded task
                if (_currentTask.second)
                {
                    _threadRunning = true;
                    _thread = std::jthread([&]()
                    {
                        _currentTask.first();
                        _threadRunning = false;
                    });
                }
                // Non-threaded task
                else
                {
                    _nonThreadRunning = !_currentTask.first();
                }
            }
        }
        else
        {
            if (isRunning() && (_currentTask.second == false))
            {
                _nonThreadRunning = !_currentTask.first();
            }
            else if (!isRunning())
            {
                DEBUG("Task is Done");
                _currentTask.first = nullptr;
            }
        }
        return _tasks.empty() && (_currentTask.first == nullptr);
    }

 private:
    std::pair<std::function<bool()>, bool> _currentTask;
    std::string _name;
    std::queue<std::pair<std::function<bool()>, bool>> _tasks;

    std::jthread _thread;
    std::atomic<bool> _threadRunning;
    bool _nonThreadRunning;
};