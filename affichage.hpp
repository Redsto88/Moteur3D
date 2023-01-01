#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP

#include <algorithm>
#include "scene.hpp"
#include "matrix4.hpp"

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
        void render(float time, bool isAnimated);
        void render_color_buffer(void);
        void clear_color_buffer(uint32_t color);
        bool isRunning();
        void destroy_window();
        SDL_Renderer* getRenderer();
        void drawTriangle(SDL_Renderer* renderer,SDL_Point v1, SDL_Point v2, SDL_Point v3, SDL_Color color, float illumination);
};


#endif