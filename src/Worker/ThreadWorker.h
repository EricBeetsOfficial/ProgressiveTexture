#pragma once

#include <functional>
#include <mutex>
#include <utility>
// #include <queue>
#include <unordered_set>
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
        // DEBUG("Ctr ");
    }

    ~ThreadWorker()
    {
        // DEBUG("Dtr ");
    }
 public:
    bool tick()
    {
        unique_lock<std::mutex> lock(_mutex);
#if 0
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
#endif
        std::unordered_set<T*> toRemove;
        for (auto const task: _tasks)
        {
            if (!CALL_METHOD(task, isEmpty))
            {
                bool empty = CALL_METHOD(task, runTasks);
                if (empty)
                    toRemove.insert(task);
            }
            else
            {
                DEBUG("Task is empty");
                toRemove.insert(task);
            }
        }

        for (auto const taskToRemove: toRemove)
        {
            _tasks.erase(taskToRemove);
        }
        toRemove.clear();
        return false;
    }

    void addWorker(T* task)
    {
        unique_lock<std::mutex> lock(_mutex);
        // _queue.push(std::move(task));
        _tasks.insert(std::move(task));
    }

    bool isComplete()
    {
        // return _queue.empty();
        return _tasks.empty();
    }

 private:
    T* _currentTask;
    mutex _mutex;
    // std::queue<T*> _queue;
    std::unordered_set<T*> _tasks;

    DEFINE_METHOD(runTasks)
    DEFINE_METHOD(isEmpty)
};