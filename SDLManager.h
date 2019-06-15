//
// Created by dell on 2019/6/6.
//

#ifndef GAMEGIRL_SDLMANAGER_H
#define GAMEGIRL_SDLMANAGER_H

#include <string>
#include "Exceptions.h"
extern "C" {
    #include "SDL.h"
}

struct Color{
    Byte r, g, b, a;
};
extern const Color realColorMap[4];

class SDLManager {
    SDL_Window *win{nullptr};
    SDL_Surface *surface{nullptr};
    SDL_PixelFormat* fmt{nullptr};
    SDL_Event e;
    int zoomTime = 1;
    const static int WINDOW_HEIGHT = 144;
    const static int WINDOW_WIDTH = 160;
    const static int BUFFER_HEIGHT = 256;
    const static int BUFFER_WIDTH = 256;
    const static int WINDOW_POSITION_X = SDL_WINDOWPOS_UNDEFINED;
    const static int WINDOW_POSITION_Y = SDL_WINDOWPOS_UNDEFINED;
    Byte joypadC1 = 0x0F;
    Byte joypadC0 = 0x0F;
    bool isQuit = false;
    uint32_t tmp[160 * 144];
    uint32_t fpsTimer = 0;
    const static int FPS = 60;
public:
    ~SDLManager();
    void init(std::string title_window,int zoomTime = 1);
    void refreshWindow();
    Uint32 mapColor(Byte);;
    void setLine(Byte lineNum, Uint32 * line);
    Byte getJoypad(Byte in);
    bool handleInput ();

};
extern SDLManager sdlManager;

#endif //GAMEGIRL_SDLMANAGER_H
