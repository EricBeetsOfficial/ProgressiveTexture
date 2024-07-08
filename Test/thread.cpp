#include <ThreadWorker.h>
#include <TextureTask.h>
#include <Random.h>
#include <Console.h>
#include <Log.h>

#include <ThreadPool.h>

int main()
{
#if 0
    // Create a thread pool with 4 threads
    ThreadPool pool(1);

    // Enqueue tasks for execution
    for (int i = 0; i < 20; ++i)
    {
        pool.enqueue([i]
        {
            int timeout = Utils::Random(1000, 2000);
            cout << "Task " << i << " is running on thread " << this_thread::get_id() << " (" << timeout << ")" << endl;
            // Simulate some work
            this_thread::sleep_for(chrono::milliseconds(timeout));
        });
        // this_thread::sleep_for(chrono::milliseconds(100));
        std::this_thread::yield();
    }
    cout << "END" << endl;
#else
    Utils::Log::Level(Utils::Log::Level_t::Debug);
    Utils::InitRand();

    ThreadWorker<TextureTasks> workerTest1;
    ThreadWorker<TextureTasks> workerTest2;
    ThreadWorker<TextureTasks> workerTest3;
    ThreadWorker<TextureTasksTest> workerTest22;


    workerTest1.addWorker(new TextureTasks("../Test/images/granular.jpg"));
    workerTest1.addWorker(new TextureTasks("../Test/images/wave.jpg"));
    workerTest2.addWorker(new TextureTasks("q"));
    workerTest3.addWorker(new TextureTasks("a"));
    workerTest22.addWorker(new TextureTasksTest("tex2"));

    Utils::loop([&]()
    {
        workerTest1.tick();
        workerTest2.tick();
        // workerTest3.tick();
        // workerTest22.tick();
        if (workerTest1.isComplete() && workerTest2.isComplete())
        {
            INFO("Worker is completed: EXIT");
            return true;
        }
        return false;
    });
    endl(cout);
#endif
    return 0;
}