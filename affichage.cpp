#include "affichage.hpp"


typedef struct{
    Triangle t; //triangle
    float e; //eclairement
}Tri_Ecl;

Affichage::Affichage(Scene& _scene, const int _window_width, const int _window_height, const float _fov_factor){
    scene = _scene;
    window_width = _window_width;
    window_height = _window_height;
    fov_factor = _fov_factor;
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
    running = true;
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        running = false;
        return;
    }

    // Create a SDL Window
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
    running = _running;
}

void Affichage::render(float time, bool isAnimated){
    render_color_buffer();
    clear_color_buffer(0xFF000000);

    //On récupère les différentes volumes
    std::vector<Volume3D*> volumes = scene.getVolumes();

    //On récupère les faces de chaque volume
    std::vector<std::vector<Quad>> faces ;
    for (int i=0; i< (int) volumes.size(); i++){
        faces.push_back(volumes[i]->getQuads());
    }

    //On récupère les triangles de chaque face
    std::vector<Triangle> triangles;
    
    for (int i=0; i< (int) faces.size(); i++)
    {
        for (int j=0; j< (int) faces[i].size(); j++)
        {
            triangles.push_back(faces[i][j].getT1());
            triangles.push_back(faces[i][j].getT2());
        }
    }

    //Défintion de la matrice (est normalisée donc renvoie toujours un résultat entre -1 et 1)
    Matrix4 matProj;
    matProj.initializeProj(window_width, window_height);
    //matrices de rotation
    Matrix4 matRotZ, matRotX, matRotY,  matView;
    float fTheta = isAnimated? time : 180.0f; //valeur de rotation par défaut (0 pour une vue orthogonale du haut)

    matRotZ.initializeZRot(fTheta);
    matRotX.initializeXRot(fTheta);
    matRotY.initializeYRot(fTheta);

    Vector3 vCamera = scene.getCameraPosition();
    Vector3 vTarget = scene.getTarget();
    Vector3 vUp = scene.getUpDirection();
    matView = (Matrix_camera(vCamera, vTarget, vUp)).inverse();
    
    //stockage pour les triangles projetés et leur éclairement
    std::vector<Tri_Ecl> trianglesToRaster;

    //On dessine les triangles
    for (int i = 0; i < (int) triangles.size(); i++)
    {
        Triangle triProjected;
        Triangle triTranslated = Triangle(triangles[i]); //triangle copié pour ne pas modifier le triangle de la scène
        triTranslated.setColor(triangles[i].getColor());
        
        triTranslated.multiplyByMatrix(matRotZ);
        triTranslated.multiplyByMatrix(matRotX);

        // calcul de la normale du triangle et de son orientation par rapport à la caméra
        Vector3 normal, ligne1, ligne2;
        ligne1 = triTranslated.getB()-triTranslated.getA();
        ligne2 = triTranslated.getC()-triTranslated.getA();
        normal.setX(ligne1.getY()*ligne2.getZ() - ligne1.getZ()*ligne2.getY());
        normal.setY(ligne1.getZ()*ligne2.getX() - ligne1.getX()*ligne2.getZ());
        normal.setZ(ligne1.getX()*ligne2.getY() - ligne1.getY()*ligne2.getX());
        normal.normalize();
        
        Vector3 cameraRay = triTranslated.getA() - vCamera; // vecteur allant du centre de la caméra au triangle
        float dot = normal.getX()*cameraRay.getX() + normal.getY()*cameraRay.getY() + normal.getZ()*cameraRay.getZ();

        if (dot >= 0.0f)//si le triangle est orienté vers la caméra
        {
            //on applique la matrice de vue
            triTranslated.multiplyByMatrix(matView);
            //on projette le triangle
            triProjected = Triangle(triTranslated);
            triProjected.multiplyByMatrix(matProj);

            //on divise par w pour avoir des coordonnées homogènes
            (triProjected.getA() /= triProjected.getA().getW());
            (triProjected.getB() /= triProjected.getB().getW());
            (triProjected.getC() /= triProjected.getC().getW());
            triProjected.inverseXY(); //multiplie X par -1 et Y par -1 
            triProjected.scaleToViewAndWindow(window_width, window_height); //met à l'échelle de la vue
            
            // calcul lumière
            Vector3 lightRay = triTranslated.getCenterThirdSide() - scene.getLightSource();
            float lightRayMagnitude = lightRay.magnitude();
            float dot_l = normal.dotProduct(lightRay);
            float theta = std::acos(dot_l / (normal.magnitude() * lightRay.magnitude()));      //E=(I/d^2)*cos(theta) = formule de l'éclairemnt      
            float eclairement = scene.getIntensite() / pow(lightRayMagnitude,2) * cos(theta);
            if(eclairement<0.1) eclairement= 0.1;
            if(eclairement>1) eclairement= 1;
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
        SDL_Point A = {(int) triProjected.t.getA().getX(),(int) triProjected.t.getA().getY()};
        SDL_Point B = {(int) triProjected.t.getB().getX(),(int) triProjected.t.getB().getY()};
        SDL_Point C = {(int) triProjected.t.getC().getX(),(int) triProjected.t.getC().getY()};
           
        drawTriangle(A, B, C, triProjected.t.getColor(), triProjected.e);
    }

    SDL_RenderPresent(renderer);
}

void Affichage::render_color_buffer(void){
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(window_width * sizeof(SDL_Color))
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void Affichage::clear_color_buffer(uint32_t color){
   int x = 0;
   while(x<window_width*window_height){
       color_buffer[x] = color;
       x++;
   }
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

// Fonction qui rasterise un triangle avec l'algorithme de Scanline
void Affichage::fillTriangle(SDL_Point v1, SDL_Point v2, SDL_Point v3){
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
        SDL_Point B = {second_half ? v2.x + (int)(beta * (v3.x - v2.x)) : v1.x + (int)(beta * (v2.x - v1.x)), v1.y+i};
        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++)
        {
            SDL_RenderDrawPoint(renderer, j, A.y);
        }
    }
}

void Affichage::drawTriangle(SDL_Point v1, SDL_Point v2, SDL_Point v3, SDL_Color color, float eclairement){   
    //Couleur de remplissage
    if(scene.getIsLit()){
        SDL_SetRenderDrawColor(renderer,color.r * eclairement, color.g * eclairement, color.b * eclairement, color.a); //ombre
    }
    else{
        SDL_SetRenderDrawColor(renderer,color.r, color.g, color.b, color.a); //pas d'ombre
    }
        
    fillTriangle(v1,v2,v3);

    //Lignes 

    //Couleur des lignes
    if(scene.getShowEdge()){
        SDL_SetRenderDrawColor(renderer,scene.getColorLines().r,scene.getColorLines().g,scene.getColorLines().b,SDL_ALPHA_OPAQUE);
    

        // Dessiner plusieurs lignes côte à côte pour simuler une ligne plus épaisse
        int line_thickness = scene.getLineThickness();
        for (int i = 0; i < line_thickness; i++)
        {   
            SDL_RenderDrawLine(renderer, v1.x + i, v1.y, v2.x + i, v2.y);
            SDL_RenderDrawLine(renderer, v2.x + i, v2.y, v3.x + i, v3.y);
        }
    }
}