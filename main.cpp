#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


#include "RGBPixel.h"
#include "PixelArr.h"


using namespace std;


int main(){
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)!=0){
        cout<<"SDL Init error"<<endl;
        return 1;
    }
    PixelArr pic;
    const string test = "./test.txt";
    pic.loadPicturetxt(test);
    SDL_Window* win = SDL_CreateWindow( "test",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        pic.getW()*10*2+1,pic.getH()*10,0);
    
    if (!win)
    {
        cout<<"Error creating window"<<endl;
        SDL_Quit();
        return 1;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win,-1,render_flags);
    if (!rend)
    {
        cout<<"Error creating renderer"<<endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* tex =SDL_CreateTextureFromSurface(rend, pic.sur);
    if (!tex){
        cout<<"Error creating texture"<<endl;
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    pic.open("teststruc.txt");
    
    SDL_Texture* tex1 =SDL_CreateTextureFromSurface(rend, pic.sur);
    if (!tex1){
        cout<<"Error creating texture"<<endl;
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    bool close_requested=false;
    
    while(!close_requested)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) close_requested = true;
        }
        SDL_Rect rect;
        SDL_QueryTexture(tex,NULL,NULL, &rect.w,&rect.h);
        rect.h*=10;
        rect.w*=10;
        rect.x=0;
        rect.y=0;
        
        
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend,tex,NULL,&rect);
        
        SDL_QueryTexture(tex1,NULL,NULL, &rect.w,&rect.h);
        rect.h*=10;
        rect.w*=10;
        rect.x=pic.getW()*10+1;
        rect.y=0;
        
        SDL_RenderCopy(rend,tex1,NULL,&rect);
        
        SDL_RenderPresent(rend);
        SDL_Delay(1/20);
        
        
    }
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(tex1);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
