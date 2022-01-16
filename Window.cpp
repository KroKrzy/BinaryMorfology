#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "Window.h"

using namespace std;

Window::Window(int w, int h,const char* name)
{
    makenew(w,h,name);
}
void Window::makenew(int w, int h, const char* name)
{
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)!=0)
    {
        cout<<"error initialising SDL: \n"<<SDL_GetError()<<endl;
        exit(1);
    }
    win = SDL_CreateWindow(name,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,0);
    if(!win)
    {
        cout<<"error creating window: \n"<<SDL_GetError()<<endl;
        exit(1);
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    rend = SDL_CreateRenderer(win,-1,render_flags);
    if(!rend)
    {
        cout<<"error creating renderer: \n"<<SDL_GetError()<<endl;
        exit(1);
    }
}

void Window::putOnRend(SDL_Texture* tex, SDL_Rect rect)
{
    SDL_RenderCopy(rend,tex,NULL,&rect);
}
void Window::refrRend()
{
    rendShow();
    SDL_Delay(1000/60);
    SDL_RenderClear(rend);
}
void Window::rendShow()
{
    SDL_RenderPresent(rend);
}
void Window::deletewin()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
}
Window::~Window()
{
    deletewin();
    SDL_Quit();
}




