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
        void drawRect(int x, int y, int width, int height/*, uint32_t color*/);
        void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
        void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);
        void drawTriangle(Triangle tri);
        void render();
        bool isRunning();
        void destroy_window();
        SDL_Renderer* getRenderer();
        void testFillTriangle(SDL_Renderer* renderer);

};


#endif