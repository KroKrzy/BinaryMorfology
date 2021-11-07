#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

#include "RGBPixel.h"



using namespace std;

RGBPixel::RGBPixel::RGBPixel(){};
RGBPixel::RGBPixel(int x, int y,SDL_Surface* sur)
{
    setpixelrgb(x,y,sur);
}

void RGBPixel::setpixelrgb(int x, int y,SDL_Surface* sur)
{
    Uint32 pixel = getpixel(x,y,sur);
    SDL_GetRGBA(pixel,sur->format,&r,&g,&b,&a);
}

Uint32 RGBPixel::getpixel(int x, int y, SDL_Surface* sur)
{
    int bpp = sur->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)sur->pixels + y * sur->pitch + x * bpp;
    
    switch (bpp)
    {
        case 1:
            return *p;
            break;
        case 2:
            return *(Uint16 *)p;
            break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;
        case 4:
            return *(Uint32 *)p;
            break;
        default:
            return 0;
    }
}


short RGBPixel::getValue()
{
    return val;
}

void RGBPixel::setvalue(int x, int y, short value, SDL_Surface* sur)
{
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
    Uint32 amask = sur->format->Amask;
    short ignore;
    switch(amask){
        case 0xFF000000:
            ignore=0;
            break;
        case 0x00FF0000:
            ignore=1;
            break;
        case 0x0000FF00:
            ignore=2;
            break;
        case 0x000000FF:
            ignore=3;
            break;
        default:
            cout<<"Error: Wrong format"<<endl;
            exit(1);
    }
    for (short c = 0;c<4;c++){
        if (c!=ignore){
            pixels[4*(y*sur->w+x)+c]=newVal;
        }
    }
}
Uint8 RGBPixel::getr()
{
    return r;
    
}
Uint8 RGBPixel::getg()
{
    return g;
}
Uint8 RGBPixel::getb()
{
    return b;
}

void RGBPixel::setr(Uint8 nr,int x, int y, SDL_Surface* sur)
{
    r=nr;
    Uint32 rmask = sur->format->Rmask;
    Uint8* pixels = (uint8_t*) sur->pixels;
    switch (rmask){
        case 0xFF000000:
            pixels[4*(y*sur->w+x)]=nr;
            break;
        case 0x00FF0000:
            pixels[4*(y*sur->w+x)+1]=nr;
            break;
        case 0x0000FF00:
            pixels[4*(y*sur->w+x)+2]=nr;
            break;
        case 0x000000FF:
            pixels[4*(y*sur->w+x)+3]=nr;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setr(Uint8 nr,int i, SDL_Surface* sur)
{
    cout<<"nr"<<unsigned(nr)<<"i"<<i<<endl;
    r=nr;
    Uint32 rmask = sur->format->Rmask;
    Uint8* pixels = (uint8_t*) sur->pixels;
    switch (rmask){
        case 0xFF000000:
            pixels[4*(i)]=nr;
            break;
        case 0x00FF0000:
            pixels[4*(i)+1]=nr;
            break;
        case 0x0000FF00:
            pixels[4*(i)+2]=nr;
            break;
        case 0x000000FF:
            pixels[4*(i)+3]=nr;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setg(Uint8 ng, int x, int y, SDL_Surface* sur)
{
    g=ng;
    uint32_t gmask = sur->format->Gmask;
    uint8_t* pixels = (uint8_t*) sur->pixels;
    switch (gmask){
        case 0xFF000000:
            pixels[4*(y*sur->w+x)]=ng;
            break;
        case 0x00FF0000:
            pixels[4*(y*sur->w+x)+1]=ng;
            break;
        case 0x0000FF00:
            pixels[4*(y*sur->w+x)+2]=ng;
            break;
        case 0x000000FF:
            pixels[r*(y*sur->w+x)+3]=ng;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setg(Uint8 ng, int i, SDL_Surface* sur)
{
    g=ng;
    Uint32 gmask = sur->format->Gmask;
    Uint8* pixels = (Uint8*) sur->pixels;
    switch (gmask){
        case 0xFF000000:
            pixels[4*(i)]=ng;
            break;
        case 0x00FF0000:
            pixels[4*(i)+1]=ng;
            break;
        case 0x0000FF00:
            pixels[4*(i)+2]=ng;
            break;
        case 0x000000FF:
            pixels[4*(i)+3]=ng;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setb(uint8_t nb, int x, int y, SDL_Surface* sur)
{
    b=nb;
    Uint32 bmask = sur->format->Bmask;
    Uint8* pixels = (Uint8*) sur->pixels;
    switch (bmask){
        case 0xFF000000:
            pixels[4*(y*sur->w+x)]=nb;
            break;
        case 0x00FF0000:
            pixels[4*(y*sur->w+x)+1]=nb;
            break;
        case 0x0000FF00:
            pixels[4*(y*sur->w+x)+2]=nb;
            break;
        case 0x000000FF:
            pixels[4*(y*sur->w+x)+3]=nb;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::setb(Uint8 nb, int i, SDL_Surface* sur)
{
    this->b=nb;
    Uint32 bmask = sur->format->Bmask;
    Uint8* pixels = (Uint8*) sur->pixels;
    switch (bmask){
        case 0xFF000000:
            pixels[4*(i)]=nb;
            break;
        case 0x00FF0000:
            pixels[4*(i)+1]=nb;
            break;
        case 0x0000FF00:
            pixels[4*(i)+2]=nb;
            break;
        case 0x000000FF:
            pixels[4*(i)+3]=nb;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::seta(uint8_t na, int x, int y, SDL_Surface* sur)
{
    a=na;
    Uint32 amask = sur->format->Amask;
    Uint8* pixels = (Uint8*) sur->pixels;
    switch (amask){
        case 0xFF000000:
            pixels[4*(y*sur->w+x)]=na;
            break;
        case 0x00FF0000:
            pixels[4*(y*sur->w+x)+1]=na;
            break;
        case 0x0000FF00:
            pixels[4*(y*sur->w+x)+2]=na;
            break;
        case 0x000000FF:
            pixels[4*(y*sur->w+x)+3]=na;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}
void RGBPixel::seta(Uint8 na, int i, SDL_Surface* sur)
{
    a=na;
    Uint32 amask = sur->format->Amask;
    Uint8* pixels = (Uint8*) sur->pixels;
    switch (amask){
        case 0xFF000000:
            pixels[4*(i)]=na;
            break;
        case 0x00FF0000:
            pixels[4*(i)+1]=na;
            break;
        case 0x0000FF00:
            pixels[4*(i)+2]=na;
            break;
        case 0x000000FF:
            pixels[r*(i)+3]=na;
            break;
        default:
            cout<<"Error:Wrong format"<<endl;
    }
}

void RGBPixel::setrgb(Uint8 nr, Uint8 ng, Uint8 nb, int x, int y, SDL_Surface* sur)
{
    setr(nr,x,y,sur);
    setg(ng,x,y,sur);
    setb(nb,x,y,sur);
    getpixel(x,y,sur);
}
void RGBPixel::setrgb(uint8_t nr, uint8_t ng, uint8_t nb, int i, SDL_Surface* sur)
{
    cout<<"nr"<<unsigned(nr)<<"ng"<<unsigned(ng)<<"nb"<<unsigned(nb)<<"i"<<i<<endl;
    setr(nr,i,sur);
    setg(ng,i,sur);
    setb(nb,i,sur);
}
RGBPixel::~RGBPixel(){;}
