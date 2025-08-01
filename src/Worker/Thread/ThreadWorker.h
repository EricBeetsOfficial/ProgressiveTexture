#pragma once

#include <functional>
#include <mutex>
#include <utility>
#include <unordered_set>
#include <Log.h>
#include <DynamicTemplate.h>

template <typename T>
class ThreadWorker
{
 public:
    ThreadWorker  ( );
    ~ThreadWorker ( );

 public:
    bool tick       ( );
    void addWorker  (T* task);
    bool isComplete ( ) const;

 private:
    T* _currentTask;
    std::mutex _mutex;
    std::unordered_set<T*> _tasks;

    DEFINE_METHOD(runTasks)
    DEFINE_METHOD(isEmpty)
};

#include <ThreadWorker.hpp>