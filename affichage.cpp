#include <iostream>

#include "affichage.hpp"
#include "scene.hpp"
#include "vector3.hpp"
#include "vector2.hpp"
#include "matrix4.hpp"

Affichage::Affichage(Scene _scene, const int _window_width, const int _window_height, const float _fov_factor){
    std::cout << "initialisation affichage scene" << std::endl;
    scene = _scene;
    std::cout << "initialisation affichage width" << std::endl;
    window_width = _window_width;
    std::cout << "initialisation affichage height" << std::endl;
    window_height = _window_height;
    std::cout << "initialisation affichage fov" << std::endl;
    fov_factor = _fov_factor;
    std::cout << "initialisation affichage color_buffer" << std::endl;
    color_buffer = new uint32_t[window_width * window_height];
    std::cout << "initialisation affichage color_buffer_texture" << std::endl;
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
    std::cout << "c_b_t initialisé";
    running = true;
    
    std::cout << "initialisation SDL" << std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        running = false;
        return;
    }
    // Create a SDL Window
    std::cout << "creation fenetre" << std::endl;
    window = SDL_CreateWindow(
        "Projet",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
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
    std::cout << "creation renderer" << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

void Affichage::render(){
    //SDL_DisplayMode DM;
    //SDL_GetCurrentDisplayMode(0, &DM);
    
    render_color_buffer();
    clear_color_buffer(0xFF000000);

    drawRect(0,0,50,50,0xFFFFFF00);

    //On récupère les différentes volumes
    std::cout << "volumes" << std::endl;
    
    std::vector<Volume3D*> volumes = scene.getVolumes();
    std::cout << "volumes.size() = " << volumes.size() << std::endl << std::endl;

    //On récupère les faces de chaque volume
    std::cout << "faces" << std::endl;
    std::vector<std::vector<Quad>> faces ;
    for (int i=0; i<volumes.size(); i++){
        faces.push_back(volumes[i]->getQuads());
        std::cout << "faces.size() du volume " << i << " = " << faces[i].size() << std::endl;
    }
    std::cout << "faces.size() = " << faces.size() << std::endl << std::endl;

    //On récupère les triangles de chaque face
    std::cout << "triangles" << std::endl;
    std::vector<Triangle> triangles;
    
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
    std::cout << "triangles.size() = " << triangles.size() << std::endl << std::endl;

/*    // On définit les limites du plan de projection ainsi que la distance Z minimale et maximale d'affichage
    float right = window_width;
    float left = 0;
    float top = window_height;
    float bottom = 0;
    float far = 100;
    float near = 0.01;

    // On définit la matrice de projection en perspective
    std::cout << "matrices" << std::endl << std::endl;
    Matrix4 projectionMatrix((2.0f * near) / (right - left), 0.0f, (right + left) / (right - left), 0.0f,
                            0.0f, (2.0f * near) / (top - bottom), (top + bottom) / (top - bottom), 0.0f,
                            0.0f, 0.0f, -(far + near) / (far - near), -(2.0f * far * near) / (far - near),
                            0.0f, 0.0f, -1.0f, 0.0f);

    std::cout << projectionMatrix[0][0] << "; " << projectionMatrix[0][1] << "; " << projectionMatrix[0][2] << "; " << projectionMatrix[0][3] << std::endl;
    std::cout << projectionMatrix[1][0] << "; " << projectionMatrix[1][1] << "; " << projectionMatrix[1][2] << "; " << projectionMatrix[1][3] << std::endl;
    std::cout << projectionMatrix[2][0] << "; " << projectionMatrix[2][1] << "; " << projectionMatrix[2][2] << "; " << projectionMatrix[2][3] << std::endl;
    std::cout << projectionMatrix[3][0] << "; " << projectionMatrix[3][1] << "; " << projectionMatrix[3][2] << "; " << projectionMatrix[3][3] << std::endl << std::endl;

    //on affiche les triangles
    std::cout << "afficher triangles" << std::endl;
    for(int i=0; i<triangles.size(); i++)
    {
        SDL_Point p1 = Vector3ToSDL_Point(triangles[i].getA(), projectionMatrix);
        SDL_Point p2 = Vector3ToSDL_Point(triangles[i].getB(), projectionMatrix);
        SDL_Point p3 = Vector3ToSDL_Point(triangles[i].getC(), projectionMatrix);

        std::cout << "triangle " << i << "= " << p1.x << "; " << p1.y << "///";
        std::cout << p2.x << "; " << p2.y << "///";
        std::cout << p3.x << "; " << p3.y << std::endl;
        
        /*fillTriangle(renderer, 
                    p1,
                    p2,
                    p3);

        std::cout << "tentative de dessin du triangle " << i << std::endl;
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
        SDL_RenderDrawLine(renderer, p2.x, p2.y, p3.x, p3.y);
        SDL_RenderDrawLine(renderer, p3.x, p3.y, p1.x, p1.y);
    }*/






    //matrice de projection V2
    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90;
    float fAspectRatio = (float)window_height / (float)window_width;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * M_PI);

    //Défintion de la matrice (est normalisée donc renvoie toujours un résultat entre -1 et 1)
    Matrix4 matProj;
    std::cout << "matrice avant initialisation (nulle)" << std::endl << matProj << std::endl << std::endl;
    
    matProj[{0,0}] = fAspectRatio * fFovRad;
    matProj[{1,1}] = fFovRad;
    matProj[{2,2}] = fFar / (fFar - fNear);
    matProj[{3,3}] = (-fFar * fNear) / (fFar - fNear);
    matProj[{2,3}] = 1.0f;
    
    std::cout << "matrice initialisée" << std::endl << matProj << std::endl << std::endl;

    //On dessine les triangles
    for (int i = 0; i < triangles.size(); i++)
    {
        Triangle triProjected;
        Triangle triTranslated = Triangle(triangles[i]); //triangle projeté et translaté pour la perspective

        triTranslated.getA().setZ(triangles[i].getA().getZ() + 3.0f);
        triTranslated.getB().setZ(triangles[i].getB().getZ() + 3.0f);
        triTranslated.getC().setZ(triangles[i].getC().getZ() + 3.0f);

        triProjected.setA(triTranslated.getA().multiplyVector3ByMatrix4(triProjected.getA(), matProj));
        triProjected.setB(triTranslated.getB().multiplyVector3ByMatrix4(triProjected.getB(), matProj));
        triProjected.setC(triTranslated.getC().multiplyVector3ByMatrix4(triProjected.getC(), matProj));
        
        //met à l'échelle de la vue
        triProjected.getA().setX(triProjected.getA().getX() + 1.0f);
        triProjected.getA().setY(triProjected.getA().getY() + 1.0f);
        triProjected.getB().setX(triProjected.getB().getX() + 1.0f);
        triProjected.getB().setY(triProjected.getB().getY() + 1.0f);
        triProjected.getC().setX(triProjected.getC().getX() + 1.0f);
        triProjected.getC().setY(triProjected.getC().getY() + 1.0f);

        triProjected.getA().setX(triProjected.getA().getX() * 0.5f * (float) window_width);
        triProjected.getA().setY(triProjected.getA().getY() * 0.5f * (float) window_height);
        triProjected.getB().setX(triProjected.getB().getX() * 0.5f * (float) window_width);
        triProjected.getB().setY(triProjected.getB().getY() * 0.5f * (float) window_height);
        triProjected.getC().setX(triProjected.getC().getX() * 0.5f * (float) window_width);
        triProjected.getC().setY(triProjected.getC().getY() * 0.5f * (float) window_height);

        std::cout << i << " : triangle3D = " << triangles[i] << "   | triangle projeté = " << triProjected << std::endl << std::endl; 


        //drawTriangle(triProjected);
        drawTriangle(triProjected.getA().getX(), triProjected.getA().getY(),
                    triProjected.getB().getX(), triProjected.getB().getY(),
                    triProjected.getC().getX(), triProjected.getC().getY(),
                    0xFFF542C2);
    }

    SDL_RenderPresent(renderer);
}

void Affichage::render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(window_width * sizeof(uint64_t))
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void Affichage::clear_color_buffer(uint64_t color) {
    //for (int y = 0; y < window_height; y++) {
      //  for (int x = 0; x < window_width; x++) {
        //    color_buffer[(window_width * y) + x] = color;
       // }
   // }

   int x = 0;
   while(x<window_width*window_height){
       color_buffer[x] = color;
       x++;
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

void Affichage::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color){
    drawLine(x1, y1, x2, y2, color);
    drawLine(x1, y1, x3, y3, color);
    drawLine(x3, y3, x2, y2, color);
}

void Affichage::drawTriangle(Triangle tri){
    SDL_RenderDrawLine(renderer, tri.getA().getX(), tri.getA().getY(), tri.getB().getX(), tri.getB().getY());
    SDL_RenderDrawLine(renderer, tri.getA().getX(), tri.getA().getY(), tri.getC().getX(), tri.getC().getY());
    SDL_RenderDrawLine(renderer, tri.getC().getX(), tri.getC().getY(), tri.getB().getX(), tri.getB().getY());
}

Vector2 Affichage::project(Vector3 point){
    Vector2 projected_point = {
       (int) (fov_factor * point.getX() / point.getZ()),
       (int) (fov_factor * point.getY() / point.getZ())
    };

    return projected_point;
}

/*
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
}*/ 

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




////// FONCTIONS DE TESTS /////


// Fonction qui rasterise un triangle avec l'algorithme de Bresenham
void fillTriangle(SDL_Renderer* renderer, SDL_Point v1, SDL_Point v2, SDL_Point v3)
{
    //Couleur de remplissage
    SDL_SetRenderDrawColor(renderer,255,0,0,SDL_ALPHA_OPAQUE); //Rouge

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

SDL_Renderer* Affichage::getRenderer(){
    return renderer;
}
void Affichage::testFillTriangle(SDL_Renderer* renderer)
{
    SDL_Point v1 = {100,100};
    SDL_Point v2 = {500,350};
    SDL_Point v3 = {230,300};

    fillTriangle(renderer,v1,v2,v3);

    //Lignes 

    //Couleur des lignes
    SDL_SetRenderDrawColor(renderer,0,255,0,SDL_ALPHA_OPAQUE); //Vert

    // Dessiner plusieurs lignes côte à côte pour simuler une ligne plus épaisse
    int line_thickness = 5;
    for (int i = 0; i < line_thickness; i++)
    {
        SDL_RenderDrawLine(renderer, v1.x + i, v1.y, v2.x + i, v2.y);
        SDL_RenderDrawLine(renderer, v2.x + i, v2.y, v3.x + i, v3.y);
        SDL_RenderDrawLine(renderer, v3.x + i, v3.y, v1.x + i, v1.y);
    }
}

void Affichage::drawSDL_Rect(int x, int y, int width, int height){
    //Couleur de remplissage
    int rectX = x;
    int rectY = y;

    SDL_SetRenderDrawColor(renderer,255,0,0,SDL_ALPHA_OPAQUE); //Rouge
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = height;
    rect.w = width;

    SDL_RenderDrawRect(renderer, &rect);
}



