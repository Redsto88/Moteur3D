#include <iostream>
#include "affichage.hpp"
#include "vector3.hpp"
#include "quad.hpp"
#include "pave3D.hpp"
#include "sphere3D.hpp"

void process_input(Affichage& affichage) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            affichage.Setrunning(false);
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                affichage.Setrunning(false);
            break;
    }
}


int main(int argc, char const *argv[])
{
    //creation de la scene
    std::cout << "creation scene" << std::endl;
    Scene scene;
    
    //creation d'un cube
    std::cout << "creation pave" << std::endl;
    Vector3 v1(-1,-1,-1); //Test avec le constructeur qui prend 8 vector3
    Vector3 v2(-1,1,-1);
    Vector3 v3(1,1,-1);
    Vector3 v4(1,-1,-1);
    Vector3 v5(1,1,1);
    Vector3 v6(1,-1,1);
    Vector3 v7(-1,1,1);
    Vector3 v8(-1,-1,1);
    Pave3D* p1 = new Pave3D(v1,v2,v3,v4,v5,v6,v7,v8, 0x00ffff);

    //creation d'une sphere
    Vector3 v0(0,0,0);
    Sphere3D* s1 = new Sphere3D(v0,1,10, 0xff0000);
    
    //creation de la source lumineuse
    Vector3 lightSource(2,2,-1);
    
    //mise en place des objets dans la scene
    scene.addVolume(s1);
    //scene.addVolume(p1);
    scene.addLightSource(lightSource);
    scene.setIntensite(20.0f);

    std::cout << "creation affichage" << std::endl;
    Affichage affichage(scene,800,600,640.0f);
    std::cout << (affichage.isRunning()? "true" : "false") << std::endl;
    
    SDL_Event windowEvent;
    float t = 0.0f;
    while (affichage.isRunning())
    {
        process_input(affichage);
        affichage.render(t,true);
        // affichage.test();
        t = (float)SDL_GetTicks()/1000.0f;
    }

    //nettoyage
    affichage.destroy_window();

    return 0;
}