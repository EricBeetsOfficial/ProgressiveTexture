#pragma once

#include <functional>
#include <mutex>
#include <utility>
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
    }

    ~ThreadWorker()
    {
    }
 public:
    bool tick()
    {
        unique_lock<std::mutex> lock(_mutex);
        std::unordered_set<T*> taskToRemove;
        for (auto const task: _tasks)
        {
            if (!CALL_METHOD(task, isEmpty))
            {
                bool ended = CALL_METHOD(task, runTasks);
                if (ended)
                {
                    taskToRemove.insert(task);
                }
            }
        }

        for (auto const taskToRemove: taskToRemove)
        {
            delete taskToRemove;
            _tasks.erase(taskToRemove);
        }
        taskToRemove.clear();
        return false;
    }

    void addWorker(T* task)
    {
        unique_lock<std::mutex> lock(_mutex);
        _tasks.insert(std::move(task));
    }

    bool isComplete() const
    {
        return _tasks.empty();
    }

 private:
    T* _currentTask;
    mutex _mutex;
    std::unordered_set<T*> _tasks;

    DEFINE_METHOD(runTasks)
    DEFINE_METHOD(isEmpty)
};