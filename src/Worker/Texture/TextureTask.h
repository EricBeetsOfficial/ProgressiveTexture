#include <string>
#include <Image.h>
#include <ITaskWorker.h>

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
};