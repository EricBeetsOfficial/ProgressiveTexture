#include <ThreadWorker.h>

template <typename T>
ThreadWorker<T>::ThreadWorker() : _currentTask {nullptr}
{
}

template <typename T>
ThreadWorker<T>::~ThreadWorker()
{
    auto it = _tasks.begin();
    while(it != _tasks.end())
    {
        delete *it;
        _tasks.erase(it++);
    }
}

template <typename T>
bool ThreadWorker<T>::tick()
{
    std::unique_lock<std::mutex> lock(_mutex);
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

template <typename T>
void ThreadWorker<T>::addWorker(T* task)
{
    std::unique_lock<std::mutex> lock(_mutex);
    _tasks.insert(std::move(task));
}

template <typename T>
bool ThreadWorker<T>::isComplete() const
{
    return _tasks.empty();
}