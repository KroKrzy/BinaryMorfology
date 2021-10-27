#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "RGBPixel.h"
#include "Picture.h"
#include "PixelArr.h"
#include "Singleton.h"

using namespace std;

int main(){
    cout<<1;
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)!=0){
        cout<<"SDL Init error"<<endl;
        return 1;
    }
    cout<<2;
    Picture* pic = new Picture();
    cout<<3;
    pic->loadPicture("test.png");
    cout<<4;
    SDL_Window* win = SDL_CreateWindow( "test",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        pic->getw(),pic->geth(),0);
    
    if (!win)
    {
        cout<<"Error creating window"<<endl;
        SDL_Quit();
        return 1;
    }
    cout<<5;
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win,-1,render_flags);
    if (!rend)
    {
        cout<<"Error creating renderer"<<endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    SDL_Texture* tex =SDL_CreateTextureFromSurface(rend, Singleton::getInstance().surface);
    if (!tex){
        cout<<"Error creating texture"<<endl;
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Rect rect;
    SDL_QueryTexture(tex,NULL,NULL,&rect.w,&rect.h);
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend,tex,NULL,&rect);
    SDL_RenderPresent(rend);
    SDL_Delay(5000);
    
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}