#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>

#include "Singleton.h"
#include "PixelArr.h"

using namespace std;
Singleton::Singleton(){}

Singleton* Singleton::instance_=nullptr;

Singleton * Singleton::getInstance()
{
    if (!instance_)
    {
        instance_ = new Singleton;
    }
    return instance_;
}
Singleton:: Singleton::~Singleton()
{
    delete [] this->array;
}














