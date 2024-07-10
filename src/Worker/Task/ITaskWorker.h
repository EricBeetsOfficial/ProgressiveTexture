#pragma once

#include <queue>
#include <thread>
#include <functional>

class ITaskWorker
{
    template<typename T>
    friend class ThreadWorker;
 public:
    ITaskWorker(const std::string& name = "");

 public:
    void addTask    (std::function<bool()> func, bool threaded);
    bool isEmpty    ( ) const;
    bool isRunning  ( ) const;
    bool isDone     ( ) const;
    bool isComplete ( ) const;

 private:
    bool runTasks ( );

 private:
    std::pair<std::function<bool()>, bool> _currentProcess;
    std::string _name;
    std::queue<std::pair<std::function<bool()>, bool>> _processes;

    std::jthread _thread;
    std::atomic<bool> _threadRunning;
    bool _nonThreadRunning;
    bool _isDone;
};