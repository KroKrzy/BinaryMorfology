#ifndef RGBPIXEL_H
#define RGBPIXEL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



using namespace std;

class Singleton;
class PixelArr;
class RGBPixel
{
public:
    RGBPixel();
    RGBPixel(int x, int y, SDL_Surface* sur);
    void setpixelrgb(int x,int y,SDL_Surface* sur);
    void setvalue(int x, int y, short value, SDL_Surface* sur);
    short getValue();
    uint8_t getr();
    uint8_t getg();
    uint8_t getb();
    uint8_t geta();
    void setr(uint8_t nr, int x, int y, SDL_Surface* sur);
    void setr(uint8_t nr, int i, SDL_Surface* sur);
    void setg(uint8_t ng, int x, int y, SDL_Surface* sur);
    void setg(uint8_t ng, int i, SDL_Surface* sur);
    void setb(uint8_t nb, int x, int y, SDL_Surface* sur);
    void setb(uint8_t nb, int i, SDL_Surface* sur);
    void seta(uint8_t na, int x, int y, SDL_Surface* sur);
    void seta(uint8_t na, int i, SDL_Surface* sur);
    void setrgb(uint8_t nr, uint8_t ng, uint8_t nb, int x, int y, SDL_Surface* sur);
    void setrgb(uint8_t nr, uint8_t ng, uint8_t nb, int i, SDL_Surface* sur);
    ~RGBPixel();
    
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    short val;
    Uint32 getpixel(int x, int y, SDL_Surface* sur);
};

#endif
