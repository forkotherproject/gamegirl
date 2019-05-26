#include <SDL2/SDL.h>
#include <string>

#include "../common.h"

const LCDC


class windows
{
public:
    //create the window and init the private var
    void initWindow(int WINDOW_WIDTH, int WINDOW_HEIGHT, int pos_x, int pos_Y, std::string title_window);
    //destory the surface
    void end();
    //set the certain pixel's color
    void setPixelColor(int pos_x,int pos_y,int color);
    //add gpu clock
    void addTime(int clock);

    //todo: Joypad and communiate about the ram to store the input 
    bool getJoypad();
    //todo
private:
    SDL_Window *win;
    SDL_Surface *surface;
    int window_width;
    int window_height;
};