#include <iostream>

#include "affichage.hpp"
#include "scene.hpp"
#include "vector3.hpp"
#include "vector2.hpp"

Affichage::Affichage(Scene _scene, int _window_width, int _window_height){
    scene = _scene;
    window_width = _window_width;
    window_height = _window_height;
    color_buffer = new uint32_t[window_width * window_height];
    running = true;
     if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        running = false;
        return;
    }
    // Create a SDL Window
    window = SDL_CreateWindow(
        "Projet",
        SDL_WINDOWPOS_CENTERED,
        500,
        window_width,
        window_height,
        0
    );

    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        running = false;
        return;
    }
    
    // Create a SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        running = false;
        return;
    }
}

void Affichage::Setrunning(bool _running){
    running = _running;
}


void Affichage::afficher(){
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto Width = DM.w/5;
    auto Height = DM.h/5;
    std::vector<Vector3> points = scene.getPoints();
    std::cout << "affichage" << std::endl;
    std::cout << points.size() << std::endl;
    std::vector<Vector2> points2D;
    for(int i = 0; i < points.size(); i++){
        points2D.push_back(Vector2(points[i].getX(), points[i].getY()));
    }
    for(int i = 0; i < points2D.size(); i++){
        drawPixel(points2D[i].getX()*Width,points2D[i].getY()*Height,0x00FF00FF);
    }
}

void Affichage::drawPixel(int x, int y, uint32_t color){
    if(x >= 0 && x < window_width && y >= 0 && y < window_height){
        color_buffer[(window_width * y) + x] = color;
    }
}

void Affichage::drawRect(int x, int y, int width, int height, uint32_t color){
    //color_buffer[window_width*y + x] = color;
    int rectX = x;
    int rectY = y;
    while(rectY<=y+height){
        rectX = x;
        while(rectX<=x+width){
            //color_buffer[(window_width * rectY) + rectX] = color;
            drawPixel(rectX,rectY,color);
            rectX++;
        }
        rectY++;
    }
}

void Affichage::drawLine(int x0, int y0, int x1, int y1, uint32_t color){
    int delta_x = x1 - x0;
    int delta_y = y1 - y0;
    int longest_side;

    if(delta_x > delta_y){
        longest_side = delta_x;
    }
    else{
        longest_side = delta_y;
    }

    float x_increment = delta_x / (float)longest_side;
    float y_increment = delta_y / (float)longest_side;

    float currentX = (float)x0;
    float currentY = (float)y0;

    for(int i = 0; i<longest_side; i++){
        drawPixel(round(currentX),round(currentY),color);
        currentX += x_increment;
        currentY += y_increment;
    }
}

void Affichage::render(){
    SDL_UpdateTexture(
        SDL_CreateTextureFromSurface(renderer, SDL_CreateRGBSurfaceWithFormatFrom(color_buffer, window_width, window_height, 32, window_width * sizeof(uint32_t), SDL_PIXELFORMAT_RGBA32)),
        NULL,
        color_buffer,
        (int)(window_width * sizeof(uint32_t))
    );
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, SDL_CreateRGBSurfaceWithFormatFrom(color_buffer, window_width, window_height, 32, window_width * sizeof(uint32_t), SDL_PIXELFORMAT_RGBA32)), NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool Affichage::isRunning(){
    return running;
}

void Affichage::destroy_window(){
    delete[] color_buffer;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}