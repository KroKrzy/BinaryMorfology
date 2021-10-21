#ifndef SINGLETON_H
#define SINGLETON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Singleton{
public:
    static Singleton& getInstance();
    SDL_Surface* surface;
private:
    Singleton();
    Singleton(const Singleton&);
    ~Singleton();
};
#endif
