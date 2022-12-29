#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP

#include "scene.hpp"
#include "vector2.hpp"
#include <SDL2/SDL.h>

class Affichage{
    private:
        Scene scene;
        SDL_Window* window;
        SDL_Renderer* renderer;
        uint32_t* color_buffer;
        SDL_Texture* color_buffer_texture;
        int window_width;
        int window_height;
        float fov_factor;
        bool running;
        
    public:
        Affichage(Scene& _scene, const int _window_width, const int _window_height, const float _fov_factor);
        void Setrunning(bool _running);
        void render(float time);
        void render_color_buffer(void);
        void clear_color_buffer(uint32_t color);
        void drawPixel(int x, int y, uint32_t color);
        void drawRect(int x, int y, int width, int height, uint32_t color);
        void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
        void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);
        void drawTriangle(Triangle tri);
        Vector2 project(Vector3 point);
        //void render();
        bool isRunning();
        void destroy_window();
        SDL_Renderer* getRenderer();
        void testFillTriangle(SDL_Renderer* renderer,SDL_Point v1, SDL_Point v2, SDL_Point v3);
        void drawSDL_Rect(int x, int y, int width, int height);
        void test();
};


#endif