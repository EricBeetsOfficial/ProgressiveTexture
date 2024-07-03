#include <ThreadWorker.h>
#include <TextureWorker.h>
#include <Random.h>
#include <Console.h>
#include <Log.h>

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
#endif
    Utils::Log::Level(Utils::Log::Level_t::Debug);

    ThreadWorker<TextureTasks> workerTest1;
    ThreadWorker<TextureTasks> workerTest2;
    ThreadWorker<TextureTasksTest> workerTest22;


    workerTest1.addWorker(new TextureTasks("../Test/images/granular.jpg"));
    workerTest2.addWorker(new TextureTasks("q"));
    workerTest22.addWorker(new TextureTasksTest("tex2"));

    Utils::loop([&]()
    {
        workerTest1.tick();
        // workerTest2.tick();
        // workerTest22.tick();
        return false;
    });
    endl(cout);
    return 0;
#if 0
    ThreadWorker worker;

    TextureTasks task10("../Test/images/granular.jpg");
    Utils::Log::Debug("Task count: ", task10.countTask());
    TextureTasks task20("../Test/images/wave.jpg");
    TextureTasks task30("../Test/images/_.jpg");

    worker.addWorker(&task10);
    worker.addWorker(&task20);
    worker.addWorker(&task30);

    Utils::loop([&]()
    {
        worker.tick();
        return false;
        // if (worker.tick())
        //     return true;
    });
#endif
    return 0;
}