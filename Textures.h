#ifndef TEXTURES_H
#define TEXTURES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

using namespace std;

class Window;
/**
 *Class storing textures way they can be iterated
 */
class Textures
{
public:
    /**
     *Constructor of the class
     */
    Textures();
    /**
     * Sets window textures are going to be used on
     * 
     * @param wind Object of class window that will be using textures saved in object of this class
     */
    void setWindow(Window* wind);
    /**
     * Adds new texture to the container
     * 
     * @param name Identificator of the texture. Allows to access the texture
     * @param sur Surface with the picture to be turned into texture and to be stored in the container
     */
    void include(string name,SDL_Surface* sur);
    /**
     * Allows to get access to the stored texture
     * 
     * @param name Identificator of the texture
     * @returns Texture with chosen identificator
     */
    SDL_Texture* getTexture(string name);
    /**
     * Replaces texture with given identificator with different one
     * 
     * @param name Identificator of the texture to be updated
     * @param sur Surface to be turned into texture and replace old one
     */
    void update(string name,SDL_Surface* sur);
    /**
     *Container with textures and their identificators. Can be iterated
     */
    map<string,SDL_Texture*> tex;
    /**
     * Destrucor of the class
     * 
     * Destroys all textures inside
     */
    ~Textures();
private:
    /**
     *Window textures will work on
     */
    Window* window;
    /**
     * Puts texture in the container
     * 
     * @param name Identificator of the texture
     * @param texture Texture to be put in the container
     */
    void mapTexture(string name, SDL_Texture* texture);
    /**
     * Turn Surface into texture
     * 
     * @param sur Surface to be turned into texture
     * @returns Texture made out of the surface
     */
    SDL_Texture* makeTexture(SDL_Surface* sur);
};

#endif
