#pragma once

#include <Log.h>
#include <Context.h>

// template <GraphicsAPI API>
class Texture
{
   friend class Factory;
 private:
    Texture  ()
    {
        // _context = FactoryContext<API>::createContext();
        DEBUG(typeid(this).name());
// #if defined(USE_OPENGL)
//         DEBUG("OPENGL")
// #endif
// #ifdef USE_VULKAN
//         DEBUG("VULKAN")
// #endif
// #ifdef USE_D3D
//         DEBUG("D3D")
// #endif
        if constexpr (USE_OPENGL)
        {
            DEBUG("USE_OPENGL")
        }
        if constexpr (USE_VULKAN)
        {
            DEBUG("USE_VULKAN")
        }
        if constexpr (USE_D3D)
        {
            DEBUG("USE_D3D")
        }
    }
    ~Texture ( ){}

//  private:
//     Context* _context;
};