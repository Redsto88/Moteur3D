#include <iostream>
#include "affichage.hpp"
#include "vector3.hpp"
#include "quad.hpp"
#include "pave3D.hpp"
#include "sphere3D.hpp"

float process_input(Affichage& affichage, Scene& scene, float fYaw) {
    SDL_Event event;
    SDL_PollEvent(&event);
    float f = fYaw;
    switch (event.type) {
        case SDL_QUIT:
            affichage.Setrunning(false);
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                affichage.Setrunning(false);
            if (event.key.keysym.sym == SDLK_UP){
                std::cout << "up" << std::endl;
                Vector3 v(0,0.1,0);
                affichage.getScene()->setCameraPosition(affichage.getScene()->getCameraPosition() + v);
            }
            if (event.key.keysym.sym == SDLK_DOWN){
                std::cout << "down" << std::endl;
                Vector3 v(0,-0.1,0);
                affichage.getScene()->setCameraPosition(affichage.getScene()->getCameraPosition() + v);
            }
            if (event.key.keysym.sym == SDLK_LEFT){
                std::cout << "left" << std::endl;
                f-=0.1;
            }
            if (event.key.keysym.sym == SDLK_RIGHT){
                std::cout << "right" << std::endl;
                f+=0.1;
            }
            if (event.key.keysym.sym == SDLK_w){
                std::cout << "w" << std::endl;
                Vector3 v(0,0,0.1);
                affichage.getScene()->setCameraPosition(affichage.getScene()->getCameraPosition() + v);
            }
            if (event.key.keysym.sym == SDLK_s){
                std::cout << "s" << std::endl;
                Vector3 v(0,0,-0.1);
                affichage.getScene()->setCameraPosition(affichage.getScene()->getCameraPosition() + v);
            }
            break;
            
    }
    return f;
}


int main(int argv, char** args)  //int argv, char** args //// int argc, char *argv[]
{
    //creation de la scene
    std::vector<Volume3D*> volumes;
    Vector3 lightSource(2,2,-1);
    SDL_Color colorLines; //toujours opaque
    colorLines.r = 100;
    colorLines.g = 100;
    colorLines.b = 100;
    Scene scene(volumes,lightSource, 20.0f, true, true, 2, colorLines, true); 
    
    //creation d'un cube
    SDL_Color colorP;
    colorP.r = 0;
    colorP.g = 100;
    colorP.b = 250;
    colorP.a = 100;
    Vector3 v1(-2,-1,-1); //Test avec le constructeur qui prend 8 vector3
    Vector3 v2(-2,1,-1);
    Vector3 v3(0,1,-1);
    Vector3 v4(0,-1,-1);
    Vector3 v5(0,1,1);
    Vector3 v6(0,-1,1);
    Vector3 v7(-2,1,1);
    Vector3 v8(-2,-1,1);
    Pave3D* p1 = new Pave3D(v1,v2,v3,v4,v5,v6,v7,v8, colorP); //RGBA

    //creation d'une sphere
    SDL_Color colorS;
    colorS.r = 255;
    colorS.g = 100;
    colorS.b = 0; 
    colorS.a = 255;
    Vector3 v0(1,0,0);
    Sphere3D* s1 = new Sphere3D(v0,1,16, colorS); //RGBA
    
    
    
    //mise en place des objets dans la scene
    scene.addVolume(s1);
    scene.addVolume(p1);

    // creation affichage
    Affichage affichage(scene,800,600,640.0f);
    
    SDL_Event windowEvent;
    float t = 0.0f;
    float fYaw = 0.0f;
    while (affichage.isRunning())
    {
        fYaw = process_input(affichage, scene, fYaw);
        affichage.render(t,scene.getAnim(),fYaw);
        // affichage.test();
        t = (float)SDL_GetTicks()/1000.0f;
    }

    //nettoyage
    affichage.destroy_window();

    return 0;
}