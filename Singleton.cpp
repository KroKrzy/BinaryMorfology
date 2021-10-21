#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Singleton.h"

using namespace std;

Singleton::Singleton(){};
Singleton::Singleton(const Singleton&){};
Singleton::~Singleton(){
    SDL_FreeSurface(this->surface);
}
Singleton & Singleton::getInstance()
{
    static Singleton instance_;
    return instance_;
}




