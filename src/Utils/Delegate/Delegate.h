namespace Utils
{
    #pragma pack(push, 1)
    namespace Delegate
    {
        struct TextureParameter
        {
            void* texturePtr;
            void* texId;
// #if (SUPPORT_D3D11)
            void* dxPtr;
// #endif
            char guid[64];
            bool yFlip;
        };
    }
    #pragma pack(pop)
}