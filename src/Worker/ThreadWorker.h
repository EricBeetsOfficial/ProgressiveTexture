#pragma once

#include <functional>
#include <mutex>
#include <utility>
#include <queue>
#include <Log.h>
#include <DynamicTemplate.h>

using namespace std;
using namespace Utils;

template <typename T>
class ThreadWorker
{
 public:
    ThreadWorker() : _currentTask {nullptr}
    {
        DEBUG("ThreadWorker Ctr ");
    }

 public:
    bool tick()
    {
        unique_lock<std::mutex> lock(_mutex);
        if (_currentTask == nullptr)
        {
            if (!_queue.empty())
            {
                _currentTask = std::move(_queue.front());
                _queue.pop();
                bool empty = CALL_METHOD(_currentTask, runTasks);
                if (empty)
                    _currentTask = nullptr;
            }
        }
        else
        {
            bool empty = CALL_METHOD(_currentTask, runTasks);
            if (empty)
                _currentTask = nullptr;
        }
        return _queue.empty() && (_currentTask == nullptr);
    }

    void addWorker(T* task)
    {
        unique_lock<std::mutex> lock(_mutex);
        _queue.push(std::move(task));
    }

    bool isComplete()
    {
        return _queue.empty();
    }

 private:
    T* _currentTask;
    mutex _mutex;
    std::queue<T*> _queue;

    DEFINE_METHOD(runTasks)
};