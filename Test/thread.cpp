#include <ThreadWorker.h>
#include <TextureTask.h>
#include <Console.h>
#include <Utils.h>
#include <Log.h>

int main()
{
    Utils::Log::Level(Utils::Log::Level_t::Debug);
    Utils::InitRand();

    ThreadWorker<TextureTasks> workerTest1;
    ThreadWorker<TextureTasks> workerTest2;
    ThreadWorker<TextureTasks> workerTest3;
    ThreadWorker<TextureTasksTest> workerTest22;

    // workerTest1.addWorker(new TextureTasks("../Test/images/granular.jpg"));
    // workerTest1.addWorker(new TextureTasks("../Test/images/wave.jpg"));
    workerTest1.addWorker(new TextureTasks("../Test/images/cat.jpg"));
    // workerTest2.addWorker(new TextureTasks("q"));
    // workerTest3.addWorker(new TextureTasks("a"));
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
    INFO("END");
    return 0;
}