#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RGBPixel.h"
#include "PixelArr.h"
#include "Picture.h"

using namespace std;
Picture::Picture(){}
void Picture::loadPicture(char* path)
{
    this->surf=IMG_Load(path);
    if (!surf){
        cout<<"Error creating surface"<<endl;
        SDL_Quit();
        exit(1);
    }
}
void Picture::monochrome()
{
        for(int i = 0;i<this->array.getsize();i++){
            uint8_t newval=0.299*this->array.getr(i)+0.587*this->array.getg(i)+0.114*this->array.getb(i);
            this->array.setrgb(i,newval,newval,newval);
        }
}
int Picture::getw()
{
    return this->surf->w;
}
int Picture::geth()
{
    return this->surf->h;
}

Picture::~Picture(){}

