#include <string>
#include <ITaskWorker.h>
#include <Image.h>
#include <SplitterImageProcess.h>
#include <GraphicAPI.h>
#include <Callback.h>

class TextureTasksTest
{
 public:
    TextureTasksTest  (const GraphicsAPI api, const std::string &texturePath = "") {}
    ~TextureTasksTest ( ) {}
};

class Texture;

class TextureTasks : public ITaskWorker
{
 public:
    TextureTasks  (const GraphicsAPI api, const std::string &texturePath, const Utils::Delegate::TextureParameter* _textureParameter);
    ~TextureTasks ( );

 private:
    std::shared_ptr<Image> _image;
    std::shared_ptr<SplitterImageProcess> _splitter;
    std::shared_ptr<Texture> _texture;
    Utils::Delegate::TextureParameter *_textureParameter;
};