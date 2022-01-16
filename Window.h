#ifndef WINDOW_H
#define WINDOW_H

/**
 * Class responsible for displaying pictures in window
 */
class Window
{
public:
    /**
     *Window itself
     */
    SDL_Window* win;
    /**
     *Renderer. It's what is shown in window
     */
    SDL_Renderer* rend;
    /**
     * Constructor of the class. Creates new window
     * 
     * @param w Width of the new window in pixels
     * @param h Heigth of the new window in pixels
     * @param name Name of the new window displayed on the bar
     */
    Window(int w,int h,const char * name);
    /**
     * Playes texture on the renderer to be displayed
     * 
     * @param tex Texture to be displayed
     * @param rect Structure containing informations about position and size of the texture on the renderer
     */
    void putOnRend(SDL_Texture* tex,SDL_Rect rect);
    /**
     *Refreshes displayed renderer with changes made after last display
     */
    void refrRend();
    /**Puts current state of the renderer in the window
     */
    void rendShow();
    /**
     *Deletes current window
     */
    void deletewin();
    /**
     * Creates new window and initializes SDL
     *
     * @param w Width of the new window
     * @param h Heigth of the new window
     * @param name Name of the new window displayed on the bar
     */
    void makenew(int w,int h, const char * name);
    /**
     *Destructor of the class
     * 
     * Deletes window and closes SDL
     */
    ~Window();
};

#endif
