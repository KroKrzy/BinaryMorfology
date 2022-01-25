#ifndef PIXELARR_H
#define PIXELARR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <sstream>


using namespace std;
/**
 *Class that stores data on picture and methods to modify it
 */
class PixelArr{
public:
    /**
     *Surface storing picture
     */
    SDL_Surface * sur;
    /**
     * Constructor of the class
     * 
     * Sets RGBA masks and creates temporal empty surface to avoid errors
     */
    PixelArr();
    /**
     * Get size of the picture in pixels
     * 
     * @returns number of pixels in the picture
     */
    int getsize();
    /**
     * Set value of given pixel
     * 
     * @param x x coordinate of the pixel
     * @param y y coordinate of the pixel
     * @param value new value of the pixel from set{0,1}
     */
    void setValue(int x, int y, short value);
    /**
     * Get RGB values of given pixel to temporal r,g,b variables
     * 
     * @param x x coordinate of the pixel
     * @param y y coordinate of the pixel
     */
    void getrgb(int x, int y);
    /**
     * Get the width of the picture
     * 
     * @returns width of the picture in pixels
     */
    int getW();
    /**
     * Get the height of the picture
     * 
     * @returns height of the picture in pixels
     */
    int getH();
    /**
     * Get value of the given pixel
     * 
     * @param x x coordinate of the pixel
     * @param y y coordinate of the pixel
     * 
     * @returns value of the pixel from set {0,1}
     */
    short getValue(int x, int y);
    /**
     * Set rgb value to given pixel
     * 
     * @param nr new red value
     * @param ng new green value
     * @param nb new blue value
     * @param x x coordinate of the pixel
     * @param y y coordinate of the pixel
     */
    void setrgb(uint8_t nr, uint8_t ng, uint8_t nb, int x, int y);
    /**
     * Load Picture from .txt file
     * 
     * Text file needs to follow the format:
     * 
     * 1st line: (number of colums) (number of rows) without ()
     * 
     * rest of the file: (1st value in the row)    (2nd value in the row)    ...    (last value in the row) without ()
     * 
     * Values need to belong in set {0,1}
     * 
     * @param path Path to the text file
     */
    void loadPicturetxt(string path);
    /**
     * Load picture from graphic file like .png .jpg or other
     * 
     * Picture needs to be reloaded by saving in text form and then loaded using loadPicturetxt
     * 
     * @param path Path to the file
     */
    void loadPictureGrp(string path);
    /**
     * Operation of dilation on the picture using given structured object
     * 
     * Structured Object is saved in .txt file and needs to follow the format:
     * 
     * 1st line: (number of colums) (number of rows) without ()
     * 
     * rest of the file: (1st value in the row)    (2nd value in the row)    ...    (last value in the row) without ()
     * 
     * @param path Path to file with structured object
     */
    void dilation(string path);
    /**
     * Operation of erosion on the picture using given structuring element
     * 
     * Structuring element is saved in .txt file and needs to follow the format:
     * 
     * 1st line: (number of colums) (number of rows) without ()
     * 
     * rest of the file: (1st value in the row)    (2nd value in the row)    ...    (last value in the row) without ()
     * 
     * @param path Path to file with structuring element
     */
    void erosion(string path);
    /**
     * Operation of opening on the picture using given structuring element
     * 
     * Structuring element is saved in .txt file and needs to follow the format:
     * 
     * 1st line: (number of colums) (number of rows) without ()
     * 
     * rest of the file: (1st value in the row)    (2nd value in the row)    ...    (last value in the row) without ()
     * 
     * @param path Path to file with structuring element
     */
    void open(string path);
    /**
     * Operation of closing on the picture using given structuring element
     * 
     * Structuring element is saved in .txt file and needs to follow the format:
     * 
     * 1st line: (number of colums) (number of rows) without ()
     * 
     * rest of the file: (1st value in the row)    (2nd value in the row)    ...    (last value in the row) without ()
     * 
     * @param path Path to file with structuring element
     */
    void close(string path);
    /**
     * Saving current state of the picture as output.bmp and output.txt files
     * 
     * Files are being saved in main folder of the app
     */
    void save();
    /**
     * Saving current state as .txt in chosen location
     * 
     * @param path Path to place to save the file
     */
    void savetxt(string path);
    /**
     * Turn objects on the picture into conture using structuring element
     * 
     * Thickness of the contur is equal radius of the element minus of on given axis
     * 
     * Structuring element is saved in .txt file and needs to follow the format:
     * 1st line: (number of colums) (number of rows) without ()
     * rest of the file: (1st value in the row)    (2nd value in the row)    ...    (last value in the row) without ()
     * 
     * @param path Path to file with structuring element
     */
    void conture(string path);
    /**
     *Vertical flip of the picture
     */
    void vflip();
    /**
     *Horizontal flip of the picture
     */
    void hflip();
    /**
     *Destructor of the class
     * 
     * Frees surface
     */
    ~PixelArr();
private:
    /**
     * Get the data of chosen pixel
     * 
     * @param x x coordinate of the pixel
     * @param y y coordinate of the pixel
     * 
     * @returns red, greeb, blue, alpha values as a single 32bit number
     */
    Uint32 getpixel(int x, int y);
    /*Temporal red, green, blue values used by methods*/
    Uint8 r,g,b;
};


#endif
