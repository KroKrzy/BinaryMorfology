#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <sstream>


#include "PixelArr.h"


using namespace std;

PixelArr::PixelArr()
{
    Uint32 rmask,gmask,bmask,amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xFF000000;
        gmask = 0x00FF0000;
        bmask = 0x0000FF00;
        amask = 0x000000FF;
    #else
        rmask = 0x000000FF;
        gmask = 0x0000FF00;
        bmask = 0x00FF0000;
        amask = 0xFF000000;
    #endif
    sur = SDL_CreateRGBSurface(0,10,10,32,rmask, gmask,bmask,amask);
}

int PixelArr::getsize()
{
    return getW()*getH();
}
void PixelArr::getrgb(int x, int y)
{
     SDL_LockSurface(sur);
     Uint32 pixel = getpixel(x,y);
     SDL_GetRGB(pixel,sur->format,&r,&g,&b);
     SDL_UnlockSurface(sur);
}

int PixelArr::getW()
{
    return sur->w;
}

int PixelArr::getH()
{
    return sur->h;
}

Uint32 PixelArr::getpixel(int x, int y)
{
    SDL_LockSurface(sur);
    int bpp = sur->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)sur->pixels + y * sur->pitch + x * bpp;
    SDL_UnlockSurface(sur);
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


short PixelArr::getValue(int x, int y)
{
    getrgb(x,y);
    if (r==255){return 0;}
    else{return 1;}
}

void PixelArr::setValue(int x, int y, short value)
{
    Uint8 newVal;
    if ( value == 0 ){
        newVal = 255;
    }
    else if ( value == 1){
        newVal = 0;
    }
    else{
        cout << "Wrong pixel value x="<<x<<"y="<<y<<" "<<value<<endl;
        exit(1);
    }
    setrgb(newVal,newVal,newVal,x,y);
}
void PixelArr::setrgb(Uint8 nr, Uint8 ng, Uint8 nb, int x, int y)
{
    SDL_LockSurface(sur);
    Uint32 newpixel = SDL_MapRGB(sur->format,nr,ng,nb);
    Uint32 * const target = (Uint32*)((Uint8*)sur->pixels+y*sur->pitch+x*sur->format->BytesPerPixel);
    *target=newpixel;
    SDL_UnlockSurface(sur);
}
void PixelArr::loadPicturetxt(string path)
{
    string line;
    ifstream infile (path);
    int dim[2];
    if(infile.good())
    {
        infile>>dim[0]>>dim[1];
    }
    cout<<dim[0]<<" "<<dim[1]<<endl;
    short tab[dim[0]][dim[1]];
    int x=0,y=-1;
    while(getline(infile,line))
    {
        
        stringstream ss(line);
        if(y>=0)
        {
            for (int i=0;i<dim[0];i++)
            {
                ss>>tab[x++][y];
            }
        }
        x=0;
        y++;
    }
    SDL_FreeSurface(sur);
    Uint32 rmask,gmask,bmask,amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xFF000000;
        gmask = 0x00FF0000;
        bmask = 0x0000FF00;
        amask = 0x000000FF;
    #else
        rmask = 0x000000FF;
        gmask = 0x0000FF00;
        bmask = 0x00FF0000;
        amask = 0xFF000000;
    #endif
    sur = SDL_CreateRGBSurface(0,dim[0],dim[1],32,rmask, gmask,bmask,amask);
    for(int ny=0;ny<dim[1];ny++)
    {
        for(int nx=0;nx<dim[0];nx++)
        {
            setValue(nx,ny,tab[nx][ny]);        }
    }
}

void PixelArr::dilation(string path)
{
    string line;
    ifstream infile (path);
    int dim[2];
    if(infile.good())
    {
        infile>>dim[0]>>dim[1];
    }
    short tab[dim[0]][dim[1]];
    int x=0,y=-1;
    while(getline(infile,line))
    {
        stringstream ss(line);
        if(y>=0)
        {
            for (int i=0;i<dim[0];i++)
            {
                ss>>tab[x++][y];
            }
        }
        x=0;
        y++;
    }
    
    int mid[2];
    mid[0]=dim[0]/2+1;
    mid[1]=dim[1]/2+1;
    short temp[getW()][getH()];
    for (int x = 0 ; x < getW() ; x++)
    {
        for (int y = 0 ; y < getH() ; y++)
        {
            temp[x][y]=0;
            bool done = false;
            for (int i = 0 ; i < dim[0] ; i++)
            {
                int nx = x - (mid[0]-i)+1;
                if ( nx>=0 && nx<getW() && !done)
                {
                    for (int j = 0 ; j < dim[1] ; j++)
                    {
                        int ny = y - (mid[1]-j)+1;
                        if (ny>=0 && ny<getH())
                        {
                            if (tab[i][j]==1 && getValue(nx,ny)==1)
                            {
                                temp[x][y]=1;
                                done = true;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int x = 0 ; x < getW() ; x++)
    {
        for(int y = 0 ; y < getH() ; y++)
        {
            setValue(x,y,temp[x][y]);
        }
    }
}
void PixelArr::erosion(string path)
{
    string line;
    ifstream infile (path);
    int dim[2];
    if(infile.good())
    {
        infile>>dim[0]>>dim[1];
    }
    short tab[dim[0]][dim[1]];
    int x=0,y=-1;
    while(getline(infile,line))
    {
        stringstream ss(line);
        if(y>=0)
        {
            for (int i=0;i<dim[0];i++)
            {
                ss>>tab[x++][y];
            }
        }
        x=0;
        y++;
    }
    
    int mid[2];
    mid[0]=dim[0]/2+1;
    mid[1]=dim[1]/2+1;
    short temp[getW()][getH()];
    for (int x = 0 ; x < getW() ; x++)
    {
        for (int y = 0 ; y < getH() ; y++)
        {
            temp[x][y]=1;
            bool done = false;
            for (int i = 0 ; i < dim[0] ; i++)
            {
                int nx = x - (mid[0]-i)+1;
                if ( nx<0 || nx>=getW())
                {
                    temp[x][y]=0;
                    done = true;
                }
                if (!done)
                {
                    for (int j = 0 ; j < dim[1] ; j++)
                    {
                        int ny = y - (mid[1]-j)+1;
                        if ((ny<0 || ny>=getH())||(tab[i][j]==1 && getValue(nx,ny)==0))
                        {
                            temp[x][y]=0;
                            done = true;
                        }
                    }
                }
            }
        }
    }
    for(int x = 0 ; x < getW() ; x++)
    {
        for(int y = 0 ; y < getH() ; y++)
        {
            setValue(x,y,temp[x][y]);
        }
    }
}

void PixelArr::open(std::string path)
{
    erosion(path);
    dilation(path);
}

void PixelArr::close(std::string path)
{
    dilation(path);
    erosion(path);
}

void PixelArr::save()
{
    if(SDL_SaveBMP(sur,"output.bmp")!=0)
    {
        cout<<"SDL_SaveBMP failed "<<SDL_GetError()<<endl;
    }
    ofstream outfile;
    outfile.open("output.txt",ios::out);
    outfile<<sur->w<<"    "<<sur->h<<endl;
    for(int y=0;y<sur->h;y++){
        for(int x=0;x<sur->w;x++){
            outfile<<getValue(x,y)<<"    ";
        }
        outfile<<endl;
    }
    outfile.close();
}

void PixelArr::conture(string path)
{
    int temp[getW()][getH()];
    for (int x=0;x<getW();x++){
        for(int y=0;y<getH();y++){
            temp[x][y]=getValue(x,y);
        }
    }
    dilation(path);
    for (int x=0;x<getW();x++){
        for(int y=0;y<getH();y++){
            if(temp[x][y]==1){
                setValue(x,y,0);
            }
        }
    }
}
void PixelArr::vflip()
{
    for(int ny=0;ny<getH()/2;ny++)
    {
        for(int nx=0;nx<getW();nx++)
        {
            short temp = getValue(nx,ny);
            setValue(nx,ny,getValue(nx,getH()-ny-1));
            setValue(nx,getH()-ny-1,temp);
        }
    }
}
void PixelArr::hflip()
{
    for(int nx=0;nx<getW()/2;nx++)
    {
        for(int ny=0;ny<getH();ny++)
        {
            short temp = getValue(nx,ny);
            setValue(nx,ny,getValue(getW()-nx-1,ny));
            setValue(getW()-nx-1,ny,temp);
        }
    }
}


PixelArr::~PixelArr()
{
    SDL_FreeSurface(sur);
}








