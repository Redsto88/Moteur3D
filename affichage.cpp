#include <iostream>
#include <algorithm>

#include "affichage.hpp"
#include "scene.hpp"
#include "vector3.hpp"
#include "vector2.hpp"
#include "matrix4.hpp"


typedef struct {
    Triangle t; //triangle
    float e; //eclairement
}Tri_Ecl;

Affichage::Affichage(Scene& _scene, const int _window_width, const int _window_height, const float _fov_factor){
    //std::cout << "initialisation affichage scene" << std::endl;
    scene = _scene;
    //std::cout << "initialisation affichage width" << std::endl;
    window_width = _window_width;
    //std::cout << "initialisation affichage height" << std::endl;
    window_height = _window_height;
    //std::cout << "initialisation affichage fov" << std::endl;
    fov_factor = _fov_factor;
    //std::cout << "initialisation affichage color_buffer" << std::endl;
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
    //std::cout << "initialisation affichage color_buffer_texture" << std::endl;
    //std::cout << "c_b_t initialisé";
    running = true;
    
    //std::cout << "initialisation SDL" << std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        running = false;
        return;
    }
    // Create a SDL Window
    //std::cout << "creation fenetre" << std::endl;
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
    //std::cout << "creation renderer" << std::endl;
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        running = false;
        return;
    }
    int SDL_SetRenderDrawBlendMode(SDL_Renderer* renderer,SDL_BlendMode blendMode); //permet d'utiliser la transparence
    int SDL_SetTextureBlendMode(SDL_Texture*  texture, SDL_BlendMode blendMode);

    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
}

void Affichage::Setrunning(bool _running){
    //std::cout << "setRunning" << std::endl;
    running = _running;
}

void Affichage::render(float time, bool isAnimated, float Yaw){
    Vector3 camera;
    float xMin, xMax, yMin, yMax, zMin;
    
    render_color_buffer();
    clear_color_buffer(0xFF000000);

    //On récupère les différentes volumes
    std::vector<Volume3D*> volumes = scene.getVolumes();

    //On récupère les faces de chaque volume
    std::vector<std::vector<Quad>> faces ;
    for (int i=0; i<volumes.size(); i++){
        faces.push_back(volumes[i]->getQuads());
    }

    //On récupère les triangles de chaque face
    std::vector<Triangle> triangles;
    
    for (int i=0; i<faces.size(); i++)
    {
        for (int j=0; j<faces[i].size(); j++)
        {
            triangles.push_back(faces[i][j].getT1());
            triangles.push_back(faces[i][j].getT2());
        }
    }

    //matrice de projection V2
    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90.0f;
    float fAspectRatio = (float)window_height / (float)window_width;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

    //Défintion de la matrice (est normalisée donc renvoie toujours un résultat entre -1 et 1)
    Matrix4 matProj;

    matProj[{0,0}] = fAspectRatio * fFovRad;
    matProj[{1,1}] = fFovRad;
    matProj[{2,2}] = fFar / (fFar - fNear);
    matProj[{3,2}] = (-fFar * fNear) / (fFar - fNear);
    matProj[{2,3}] = 1.0f;

    //matrices de rotation
    Matrix4 matRotZ, matRotX, matRotY,  matView;
    float fTheta = isAnimated? time : 5.0f; //on laisse 0 si on ne veut pas de l'animation

    matRotZ[{0,0}] = cosf(fTheta);
    matRotZ[{0,1}] = sinf(fTheta);
    matRotZ[{1,0}] = -sinf(fTheta);
    matRotZ[{1,1}] = cosf(fTheta);
    matRotZ[{2,2}] = 1;
    matRotZ[{3,3}] = 1;

    matRotX[{0,0}] = 1;
    matRotX[{1,1}] = cosf(fTheta * 0.5f);
    matRotX[{1,2}] = sinf(fTheta * 0.5f);
    matRotX[{2,1}] = -sinf(fTheta * 0.5f);
    matRotX[{2,2}] = cosf(fTheta * 0.5f);
    matRotX[{3,3}] = 1;

    matRotY[{0,0}] = cosf(fYaw);
    matRotY[{0,2}] = sinf(fYaw);
    matRotY[{1,1}] = 1;
    matRotY[{2,0}] = -sinf(fYaw);
    matRotY[{2,2}] = cosf(fYaw);
    matRotY[{3,3}] = 1;

    Vector3 vCamera = scene.getCameraPosition();
    Vector3 vTarget = scene.getTarget();
    Vector3 vUp = scene.getUpDirection();
    std::cout << "vTarget AVANT= " << vTarget << std::endl;
    std::cout << "look dir = " << scene.getLookDirection() << std::endl;
    Vector3 vLookDir =  scene.getLookDirection().multiplyVector3ByMatrix4(scene.getLookDirection(),matRotY);
    vTarget = vCamera + vLookDir;
    std::cout << "vTarget APRES= " << vTarget << std::endl;
    std::cout << "look dir = " << vLookDir << std::endl;
    std::cout << "vCamera = " << vCamera << std::endl;
    std::cout << "vTarget = " << vTarget << std::endl;
    std::cout << "vUp = " << vUp << std::endl;

    matView = (Matrix_camera(vCamera, vTarget, vUp)).inverse();


    std::cout << "matView = " << matView << std::endl;


   

    //stockage pour les triangles projetés
    std::vector<Tri_Ecl> trianglesToRaster;
    //On dessine les triangles
    for (int i = 0; i < triangles.size(); i++)
    {
        Triangle triProjected;
        triProjected.setColor(triangles[i].getColor());
        Triangle triTranslated = Triangle(triangles[i]); //triangle projeté et translaté pour la perspective

        
        triTranslated.setA(triTranslated.getA().multiplyVector3ByMatrix4(triTranslated.getA(), matRotZ));
        triTranslated.setB(triTranslated.getB().multiplyVector3ByMatrix4(triTranslated.getB(), matRotZ));
        triTranslated.setC(triTranslated.getC().multiplyVector3ByMatrix4(triTranslated.getC(), matRotZ));

        triTranslated.setA(triTranslated.getA().multiplyVector3ByMatrix4(triTranslated.getA(), matRotX));
        triTranslated.setB(triTranslated.getB().multiplyVector3ByMatrix4(triTranslated.getB(), matRotX));
        triTranslated.setC(triTranslated.getC().multiplyVector3ByMatrix4(triTranslated.getC(), matRotX));




        // triTranslated.setA(triTranslated.getA().setZ(triTranslated.getA().getZ() + 5.0f));
        // triTranslated.setB(triTranslated.getB().setZ(triTranslated.getB().getZ() + 5.0f));
        // triTranslated.setC(triTranslated.getC().setZ(triTranslated.getC().getZ() + 5.0f));


        // calcul de la normale du triangle et de son orientation par rapport à la caméra
        Vector3 normal, ligne1, ligne2;
        ligne1 = triTranslated.getB()-triTranslated.getA();
        ligne2 = triTranslated.getC()-triTranslated.getA();
        normal.setX(ligne1.getY()*ligne2.getZ() - ligne1.getZ()*ligne2.getY());
        normal.setY(ligne1.getZ()*ligne2.getX() - ligne1.getX()*ligne2.getZ());
        normal.setZ(ligne1.getX()*ligne2.getY() - ligne1.getY()*ligne2.getX());

        float l_n = sqrt(normal.getX()*normal.getX() + normal.getY()*normal.getY() + normal.getZ()*normal.getZ());
        normal.setX(normal.getX()/l_n);
        normal.setY(normal.getY()/l_n);
        normal.setZ(normal.getZ()/l_n);
        
        Vector3 cameraRay = triTranslated.getA() - camera;
        float dot = normal.getX()*cameraRay.getX() + normal.getY()*cameraRay.getY() + normal.getZ()*cameraRay.getZ();

        if (dot <= 0.0f)
        {

            //on applique la matrice de vue
            triTranslated.setA(triTranslated.getA().multiplyVector3ByMatrix4(triTranslated.getA(), matView));
            triTranslated.setB(triTranslated.getB().multiplyVector3ByMatrix4(triTranslated.getB(), matView));
            triTranslated.setC(triTranslated.getC().multiplyVector3ByMatrix4(triTranslated.getC(), matView));
        

            // //on projette le triangle
            triProjected.setA(triTranslated.getA().multiplyVector3ByMatrix4(triTranslated.getA(), matProj));
            triProjected.setB(triTranslated.getB().multiplyVector3ByMatrix4(triTranslated.getB(), matProj));
            triProjected.setC(triTranslated.getC().multiplyVector3ByMatrix4(triTranslated.getC(), matProj));

            // //on divise par w pour avoir des coordonnées homogènes
            triProjected.setA(triProjected.getA() / triProjected.getA().getW());
            triProjected.setB(triProjected.getB() / triProjected.getB().getW());
            triProjected.setC(triProjected.getC() / triProjected.getC().getW());
            
            triProjected.setA(triProjected.getA().setX(triProjected.getA().getX() * -1.0f));
            triProjected.setB(triProjected.getB().setX(triProjected.getB().getX() * -1.0f));
            triProjected.setC(triProjected.getC().setX(triProjected.getC().getX() * -1.0f));
            triProjected.setA(triProjected.getA().setY(triProjected.getA().getY() * -1.0f));
            triProjected.setB(triProjected.getB().setY(triProjected.getB().getY() * -1.0f));
            triProjected.setC(triProjected.getC().setY(triProjected.getC().getY() * -1.0f));
            
        

            //met à l'échelle de la vue
            triProjected.setA(triProjected.getA().setX(triProjected.getA().getX() + 1.0f));
            triProjected.setA(triProjected.getA().setY(triProjected.getA().getY() + 1.0f));
            triProjected.setB(triProjected.getB().setX(triProjected.getB().getX() + 1.0f));
            triProjected.setB(triProjected.getB().setY(triProjected.getB().getY() + 1.0f));
            triProjected.setC(triProjected.getC().setX(triProjected.getC().getX() + 1.0f));
            triProjected.setC(triProjected.getC().setY(triProjected.getC().getY() + 1.0f));

            triProjected.setA(triProjected.getA().setX(triProjected.getA().getX() * 0.5f * (float) window_width));
            triProjected.setA(triProjected.getA().setY(triProjected.getA().getY() * 0.5f * (float) window_height));
            triProjected.setB(triProjected.getB().setX(triProjected.getB().getX() * 0.5f * (float) window_width));
            triProjected.setB(triProjected.getB().setY(triProjected.getB().getY() * 0.5f * (float) window_height));
            triProjected.setC(triProjected.getC().setX(triProjected.getC().getX() * 0.5f * (float) window_width));
            triProjected.setC(triProjected.getC().setY(triProjected.getC().getY() * 0.5f * (float) window_height));

            // calcul lumière
            Vector3 lightRay = triTranslated.getBarycentre() - scene.getLightSource();
            float lightRayMagnitude = lightRay.magnitude();
            float dot_l = normal.getX()*lightRay.getX() + normal.getY()*lightRay.getY() + normal.getZ()*lightRay.getZ();
            float eclairement;

            float intensite = scene.getIntensite();
            if(/*dot_l>=0 &&*/ i%2 ==0){  
                float teta = std::acos(dot_l / (normal.magnitude() * lightRay.magnitude()));      //E=(I/d^2)*cos(teta) = formule de l'éclairemnt      
                eclairement = intensite / pow(lightRayMagnitude,2) * cos(teta);
                
                if(eclairement<0.1){
                    eclairement=0.1;
                }
                if(eclairement>1){
                    eclairement = 1;
                }
            }
            else if(/*dot_l<=0 &&*/ i%2 ==1){
                float teta = std::acos(- dot_l / (normal.magnitude() * lightRay.magnitude()));      //E=(I/d^2)*cos(teta) = formule de l'éclairemnt      
                eclairement = intensite / pow(lightRayMagnitude,2) * cos(teta);
                
                if(eclairement<0.1){
                    eclairement=0.1;
                }
                if(eclairement>1){
                    eclairement = 1;
                }
            }

            //stockage
            trianglesToRaster.push_back({triProjected,eclairement});
        }
    }
        
    //triage des triangles par profondeur
    std::sort(trianglesToRaster.begin(), trianglesToRaster.end(), [](Tri_Ecl &t1, Tri_Ecl &t2){
        float z1 = (t1.t.getA().getZ() + t1.t.getB().getZ() + t1.t.getC().getZ()) / 3.0f;
        float z2 = (t2.t.getA().getZ() + t2.t.getB().getZ() + t2.t.getC().getZ()) / 3.0f;
        return z1 > z2;
    });


    for (auto &triProjected : trianglesToRaster){
        //drawTriangle(triProjected) si sa normale pointe vers la caméra et qu'il n'est pas caché derrière un autre
        // //std::cout << i << " isVisible : " << triProjected.isVisible() << std::endl << std::endl;

        SDL_Point A = {(int) triProjected.t.getA().getX(),(int) triProjected.t.getA().getY()};
        SDL_Point B = {(int) triProjected.t.getB().getX(),(int) triProjected.t.getB().getY()};
        SDL_Point C = {(int) triProjected.t.getC().getX(),(int) triProjected.t.getC().getY()};
           
        testFillTriangle(renderer, A, B, C, triProjected.t.getColor(), triProjected.e);
        
    }

    SDL_RenderPresent(renderer);

}

void Affichage::render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(window_width * sizeof(SDL_Color))
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void Affichage::clear_color_buffer(uint32_t color) {
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

    if(abs(delta_x) > abs(delta_y)){
        longest_side = abs(delta_x);
    }
    else{
        longest_side = abs(delta_y);
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
    //SDL_RenderDrawLine(renderer, tri.getC().getX(), tri.getC().getY(), tri.getB().getX(), tri.getB().getY());
}

Vector2 Affichage::project(Vector3 point){
    Vector2 projected_point = {
       (int) (fov_factor * point.getX() / point.getZ()),
       (int) (fov_factor * point.getY() / point.getZ())
    };

    return projected_point;
}

bool Affichage::isRunning(){
    return running;
}

void Affichage::destroy_window(){
    //std::cout << "Destroy window" << std::endl;
    delete[] color_buffer;
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}




////// FONCTIONS DE TESTS /////


// Fonction qui rasterise un triangle avec l'algorithme de Bresenham
void fillTriangle(SDL_Renderer* renderer, SDL_Point v1, SDL_Point v2, SDL_Point v3)
{
    // Trier les sommets du triangle par ordre croissant de y
    if (v1.y > v2.y) std::swap(v1, v2);
    if (v1.y > v3.y) std::swap(v1, v3);
    if (v2.y > v3.y) std::swap(v2, v3);

    // Déterminer la zone de remplissage du triangle
    int total_height = v3.y - v1.y;
    // std::cout << "total_height = " << total_height << std::endl;
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > v2.y - v1.y || v2.y == v1.y;
        int segment_height = second_half ? v3.y - v2.y : v2.y - v1.y;
        float alpha = (float) i / total_height;
        float beta  = (float)(i - (second_half ? v2.y - v1.y : 0)) / segment_height;
        SDL_Point A = {v1.x + (int)(alpha * (v3.x - v1.x)), v1.y + i};
        SDL_Point B = {second_half ? v2.x + (int)(beta * (v3.x - v2.x)) : v1.x + (int)(beta * (v2.x - v1.x)), v1.y+i};
        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++)
        {
            // std::cout << "j = " << j << std::endl;
            SDL_RenderDrawPoint(renderer, j, A.y);
        }
    }
}

SDL_Renderer* Affichage::getRenderer(){
    return renderer;
}


SDL_Color UintTocolor(uint32_t color)
{
	SDL_Color tempcol;
	tempcol.a = (color >> 24) & 0xFF;
	tempcol.r = (color >> 16) & 0xFF;
	tempcol.g = (color >> 8) & 0xFF;
	tempcol.b = color & 0xFF;
	return tempcol;
}


void Affichage::testFillTriangle(SDL_Renderer* renderer,SDL_Point v1, SDL_Point v2, SDL_Point v3, SDL_Color color, float eclairement)
{   
    //Couleur de remplissage
    if(scene.getIsLit()){
        SDL_SetRenderDrawColor(renderer,color.r * eclairement, color.g * eclairement, color.b * eclairement, color.a); //ombre
    }
    else{
        SDL_SetRenderDrawColor(renderer,color.r, color.g, color.b, color.a); //pas d'ombre
    }
        
    fillTriangle(renderer,v1,v2,v3);

    //Lignes 

    //Couleur des lignes
    if(scene.getShowEdge()){
        SDL_SetRenderDrawColor(renderer,scene.getColorLines().r,scene.getColorLines().g,scene.getColorLines().b,SDL_ALPHA_OPAQUE);
    }

    // Dessiner plusieurs lignes côte à côte pour simuler une ligne plus épaisse
    int line_thickness = scene.getLineThickness();
    for (int i = 0; i < line_thickness; i++)
    {   
        SDL_RenderDrawLine(renderer, v1.x + i, v1.y, v2.x + i, v2.y);
        SDL_RenderDrawLine(renderer, v2.x + i, v2.y, v3.x + i, v3.y);
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

Scene* Affichage::getScene(){
    return &scene;
}


