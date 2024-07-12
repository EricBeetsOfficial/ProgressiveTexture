#include <string>
#include <ITaskWorker.h>
#include <Image.h>
#include <SplitterImageProcess.h>

class TextureTasksTest
{
 public:
    TextureTasksTest  (const std::string &texturePath = "");
    ~TextureTasksTest ( );
};

class TextureTasks : public ITaskWorker
{
 public:
    TextureTasks  (const std::string &texturePath = "");
    ~TextureTasks ( );

 private:
    std::shared_ptr<Image> _image;
    std::shared_ptr<SplitterImageProcess> _splitter;
};