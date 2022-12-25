#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP

#include "scene.hpp"
#include <SDL2/SDL.h>

class Affichage{
    private:
        Scene scene;
        SDL_Window* window;
        SDL_Renderer* renderer;
        uint32_t* color_buffer;
        int window_width;
        int window_height;
        bool running;
        
    public:
        Affichage(Scene _scene, int _window_width, int _window_height);
        void Setrunning(bool _running);
        void afficher();
        void drawPixel(int x, int y, uint32_t color);
        void drawRect(int x, int y, int width, int height, uint32_t color);
        void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
        void render();
        bool isRunning();
        void destroy_window();

};


#endif