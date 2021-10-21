#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RGBPixel.h"
#include "Singleton.h"

using namespace std;

RGBPixel::RGBPixel::RGBPixel(){};
RGBPixel::RGBPixel(int x, int y)
{
    this->setpixelrgb(x,y);
}

void RGBPixel::setpixelrgb(int x, int y)
{
    SDL_Surface* &sur=Singleton::getInstance().surface;
    uint32_t pixel = *((uint32_t *) sur->pixels + y * sur->w + x );
    SDL_GetRGB(pixel,sur->format,&this->r,&this->g,&this->b);
    if( this->r== 0){
        val = 0;
    }
    else if (this->r == 255){
        val = 1;
    }
    else{
        cout<<"ERROR: Wrong pixel value."<<endl;
        exit(1);
    }
}

short RGBPixel::getValue()
{
    return val;
}

void RGBPixel::setvalue(int x, int y, short value)
{
    SDL_Surface* &sur = Singleton::getInstance().surface;
    unsigned char *pixels = (unsigned char*)sur->pixels;
    unsigned char newVal;
    if ( value == 0 ){
        newVal = 0;
    }
    else if ( value == 1){
        newVal = 255;
    }
    else{
        cout << "Wrong pixel value x="<<x<<"y="<<y<<endl;
        exit(1);
    }
    for (int c = 0;c<3;c++){
        pixels[4*(y*sur->w+x)+c]=newVal;
    }
}

RGBPixel::~RGBPixel(){;}




