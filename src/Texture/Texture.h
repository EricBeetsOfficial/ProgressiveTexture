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
        // DEBUG(typeid(API).name());
    }
    ~Texture ( ){}

//  private:
//     Context* _context;
};