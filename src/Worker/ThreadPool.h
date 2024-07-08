#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <Log.h>

using namespace std;

// Class that represents a simple thread pool
class ThreadPool
{
 public:
    // // Constructor to creates a thread pool with given
    // number of threads
    ThreadPool(size_t num_threads = thread::hardware_concurrency())
    {
        // cout << thread::hardware_concurrency() << endl;
        // Creating worker threads
        for (size_t i = 0; i < num_threads; ++i)
        {
            _threads.emplace_back([this]
            {
                while (true)
                {
                    Utils::Log::Debug("loop ", _stop);
                    function<void()> task;
                    // The reason for putting the below code
                    // here is to unlock the queue before
                    // executing the task so that other
                    // threads can perform enqueue tasks
                    if (false)
                    {
                        // Locking the queue so that data
                        // can be shared safely
                        unique_lock<mutex> lock(_queue_mutex);

                        // Waiting until there is a task to
                        // execute or the pool is stopped
                        Utils::Log::Debug("1- ", "Waiting ..");
                        _cv.wait(lock, [this]
                        {
                            // cout << _tasks.empty() << endl;
                            // if ((!_tasks.empty() || _stop) == false) cout << "wait.. " << endl;
                            // return !_tasks.empty() || _stop;
                            Utils::Log::Debug("2- ", (!_tasks.empty() || _stop));
                            return !_tasks.empty() || _stop;
                        });
                        Utils::Log::Debug("3- ", "Running ..");
                        // cout << "2- " << _tasks.empty() << endl;

                        // exit the thread in case the pool
                        // is stopped and there are no tasks
                        if (_stop && _tasks.empty())
                        {
                            Utils::Log::Debug("EXIT");
                            return;
                        }
                        // Get the next task from the queue
                        task = move(_tasks.front());
                        // task = _tasks.front();
                        _tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    // Destructor to stop the thread pool
    ~ThreadPool()
    {
        {
            // Lock the queue to update the stop flag safely
            unique_lock<mutex> lock(_queue_mutex);
            Utils::Log::Debug("ThreadPool Dtr");
            _stop = true;
        }

        // Notify all threads
        _cv.notify_all();

        // Joining all worker threads to ensure they have
        // completed their tasks
        Utils::Log::Debug("ThreadPool Dtr - Join");
        for (auto& thread : _threads)
        {
            thread.join();
        }
        Utils::Log::Debug("ThreadPool Dtr - End");
    }

    // Enqueue task for execution by the thread pool
    void enqueue(function<void()> task)
    {
        {
            unique_lock<std::mutex> lock(_queue_mutex);
            _tasks.emplace(move(task));
            // _tasks.emplace(task);
            Utils::Log::Debug("Add task ", _tasks.size());
        }
        _cv.notify_one();
    }

private:
    // Vector to store worker threads
    vector<thread> _threads;

    // Queue of tasks
    queue<function<void()> > _tasks;

    // Mutex to synchronize access to shared data
    mutex _queue_mutex;

    // Condition variable to signal changes in the state of
    // the tasks queue
    condition_variable _cv;

    // Flag to indicate whether the thread pool should stop
    // or not
    bool _stop = false;
};