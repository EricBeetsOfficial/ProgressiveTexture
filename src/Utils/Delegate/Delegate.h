namespace Utils
{
    #pragma pack(push, 1)
    namespace Delegate
    {
        struct TextureParameter
        {
            void* texturePtr;
            void* texId;
            char guid[64];
            bool yFlip;
        };
    }
    #pragma pack(pop)
}