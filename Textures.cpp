#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#include "Textures.h"
#include "Window.h"

using namespace std;

Textures::Textures(){};
SDL_Texture * Textures::makeTexture(SDL_Surface* sur)
{
    SDL_Texture* text = SDL_CreateTextureFromSurface(window->rend,sur);
    if(!text)
    {
        cout<<"error creating texture \n"<<SDL_GetError()<<endl;
        exit(1);
    }
    return text;
}
void Textures::mapTexture(std::string name, SDL_Texture* texture)
{
    tex.insert({name,texture});
}
void Textures::setWindow(Window* wind)
{
    window=wind;
}
void Textures::include(std::string name, SDL_Surface* sur)
{
    if(getTexture(name)==NULL){
        mapTexture(name,makeTexture(sur));
    }
    else{cout<<"Texture exists"<<endl;}
}
SDL_Texture * Textures::getTexture(std::string name)
{
    typename map<string,SDL_Texture*>::iterator it;
    for(it=tex.begin();it!=tex.end();it++)
    {
        if(it->first==name){return it->second;}
    }
    return NULL;
}
void Textures::update(std::string name, SDL_Surface* sur)
{
    SDL_Surface* temp=SDL_CreateRGBSurface(0,sur->w,sur->h,32,0,0,0,0);
    SDL_BlitSurface(sur,NULL,temp,NULL);
    typename map<string,SDL_Texture*>::iterator it;
    for(it=tex.begin();it!=tex.end();it++)
    {
        if(it->first==name){it->second=makeTexture(temp);}
    }
}

Textures::~Textures()
{
    typename map<string,SDL_Texture*>::iterator it;
    for(it = tex.begin();it!=tex.end();it++){
        SDL_DestroyTexture(it->second);
    }
}





