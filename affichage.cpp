#include <iostream>

#include "affichage.hpp"
#include "scene.hpp"
#include "vector3.hpp"
#include "vector2.hpp"
#include "matrix4.hpp"

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
    std::cout << "setRunning" << std::endl;
    running = _running;
}

// Fonction qui rasterise un triangle avec l'algorithme de Bresenham
void fillTriangle(SDL_Renderer* renderer, SDL_Point v1, SDL_Point v2, SDL_Point v3)
{
    // Trier les sommets du triangle par ordre croissant de y
    if (v1.y > v2.y) std::swap(v1, v2);
    if (v1.y > v3.y) std::swap(v1, v3);
    if (v2.y > v3.y) std::swap(v2, v3);

    // Déterminer la zone de remplissage du triangle
    int total_height = v3.y - v1.y;
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > v2.y - v1.y || v2.y == v1.y;
        int segment_height = second_half ? v3.y - v2.y : v2.y - v1.y;
        float alpha = (float) i / total_height;
        float beta  = (float)(i - (second_half ? v2.y - v1.y : 0)) / segment_height;
        SDL_Point A = {v1.x + (int)(alpha * (v3.x - v1.x)), v1.y + i};
        SDL_Point B = {second_half ? v2.x + (int)(beta * (v3.x - v2.x)) : v1.x + (int)(beta * (v2.x - v1.x)), second_half ? v2.y + i : v1.y + i};
        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++)
        {
            SDL_RenderDrawPoint(renderer, j, A.y);
        }
    }
}

SDL_Point Vector3ToSDL_Point(Vector3 v, Matrix4 m)
{
    // Appliquer la matrice de projection au Vector3
    Vector3 projectedVector = m * v;

    // Créer un SDL_Point avec les valeurs du Vector3 résultant
    SDL_Point point;
    point.x = projectedVector.getX();
    point.y = projectedVector.getY();
    
    return point;
}

void Affichage::afficher(){
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    
    //On récupère les différentes volumes
    std::cout << "volumes" << std::endl;
    
    std::vector<Volume3D*> volumes = scene.getVolumes();
    std::cout << "volumes.size() = " << volumes.size() << std::endl;

    //On récupère les faces de chaque volume
    std::cout << "faces" << std::endl;
    std::vector<std::vector<Quad3D>> faces ;
    for (int i=0; i<volumes.size(); i++){
        faces.push_back(volumes[i]->getQuads());
        std::cout << "faces.size() du volume " << i << " = " << faces[i].size() << std::endl;
    }
    std::cout << "faces.size() = " << faces.size() << std::endl;

    //On récupère les triangles de chaque face
    std::cout << "triangles" << std::endl;
    std::vector<Triangle3D> triangles;
    
    for (int i=0; i<faces.size(); i++)
    {
        std::cout << i << std::endl;
        for (int j=0; j<faces[i].size(); j++)
        {
            //std::cout << j << std::endl;
            triangles.push_back(faces[i][j].getT1());
            triangles.push_back(faces[i][j].getT2());
        }
    }
    std::cout << "triangles.size() = " << triangles.size() << std::endl;

    // On définit les limites du plan de projection ainsi que la distance Z minimale et maximale d'affichage
    float right = 100;
    float left = -100;
    float top = 100;
    float bottom = -100;
    float far = 100;
    float near = 0.01;

    // On définit la matrice de projection
    std::cout << "matrices" << std::endl;
    Matrix4 projectionMatrix;
    projectionMatrix[0][0] = 2.0f / (right - left);
    projectionMatrix[1][1] = 2.0f / (top - bottom);
    projectionMatrix[2][2] = -2.0f / (far - near);
    projectionMatrix[3][3] = 1.0f;
    projectionMatrix[3][0] = -(right + left) / (right - left);
    projectionMatrix[3][1] = -(top + bottom) / (top - bottom);
    projectionMatrix[3][2] = -(far + near) / (far - near);


    //on affiche les triangles
    std::cout << "afficher triangles" << std::endl;
    for(int i=0; i<triangles.size(); i++)
    {
        fillTriangle(renderer, 
                    Vector3ToSDL_Point(triangles[i].getA(), projectionMatrix),
                    Vector3ToSDL_Point(triangles[i].getB(), projectionMatrix),
                    Vector3ToSDL_Point(triangles[i].getC(), projectionMatrix));
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
    std::cout << "Destroy window" << std::endl;
    delete[] color_buffer;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


