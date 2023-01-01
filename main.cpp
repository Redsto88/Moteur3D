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


int main(int argc, char const *argv[])
{
    std::cout << "creation scene" << std::endl;
    Scene scene;
    
    // Vector3 v1(-1,-1,-1); //Test avec le constructeur qui prend une face
    // Vector3 v2(-1,-1,1);
    // Vector3 v3(1,-1,-1);
    // Vector3 v4(1,-1,1);
    // Quad q1(v1,v2,v3,v4);
    // Pave3D* p1 = new Pave3D(q1, 2);
    
    std::cout << "creation pave" << std::endl;
    Vector3 v1(-1,-1,-1); //Test avec le constructeur qui prend 8 vector3
    Vector3 v2(-1,1,-1);
    Vector3 v3(1,1,-1);
    Vector3 v4(1,-1,-1);
    Vector3 v5(1,1,1);
    Vector3 v6(1,-1,1);
    Vector3 v7(-1,1,1);
    Vector3 v8(-1,-1,1);
    Pave3D* p1 = new Pave3D(v1,v2,v3,v4,v5,v6,v7,v8);

    Vector3 v0(0,0,0);
    Sphere3D* s1 = new Sphere3D(v0,0.8,6);
    
    std::cout << "ajout du pave a la scene" << std::endl;
    // scene.addVolume(s1);
    scene.addVolume(p1);
    //std::cout << typeid(p1).name() << std::endl;

    std::cout << "creation affichage" << std::endl;
    Affichage affichage(scene,800,600,640.0f);
    std::cout << (affichage.isRunning()? "true" : "false") << std::endl;
    
    //affichage.render(); //fonctionne pas
    //affichage.drawSDL_Rect(10,10,100,100); //fonctionne
    //affichage.testFillTriangle(affichage.getRenderer()); //fonctionne à moitiée

    SDL_Event windowEvent;
    float t = 0.0f;
    float fYaw = 0.0f;
    while (affichage.isRunning())
    {
        fYaw = process_input(affichage, scene, fYaw);
        affichage.render(t,false,fYaw);
        // affichage.test();
        t = (float)SDL_GetTicks()/1000.0f;
    }

    //nettoyage
    affichage.destroy_window();

    return 0;
}