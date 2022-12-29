#include <iostream>
#include "affichage.hpp"
#include "vector3.hpp"
#include "quad.hpp"
#include "pave3D.hpp"

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
    Scene scene;
    
    /*Vector3 v1(300,200,50); //Test avec le constructeur qui prend une face
    Vector3 v2(300,200,75);
    Vector3 v3(350,200,75);
    Vector3 v4(350,200,50);
    Quad q1(v1,v2,v3,v4);
    Pave3D* p1 = new Pave3D(q1, 2);*/
    
    Vector3 v1(-1,-1,-1); //Test avec le constructeur qui prend 8 vector3
    Vector3 v2(-1,1,-1);
    Vector3 v3(1,1,-1);
    Vector3 v4(1,-1,-1);
    Vector3 v5(1,1,1);
    Vector3 v6(1,-1,1);
    Vector3 v7(-1,1,1);
    Vector3 v8(-1,-1,1);
    Pave3D* p1 = new Pave3D(v1,v2,v3,v4,v5,v6,v7,v8);
    
    //std::cout << typeid(p1).name() << std::endl;
    scene.addVolume(p1);
    Affichage affichage(scene, 800, 600);
    //std::cout << (affichage.isRunning()? "true" : "false") << std::endl;
    
    affichage.afficher(); //fonctionne pas
    //affichage.drawRect(10,10,100,100); //fonctionne
    //affichage.testFillTriangle(affichage.getRenderer()); //fonctionne à moitiée
    affichage.render();

    SDL_Event windowEvent;

    while (affichage.isRunning())
    {
        process_input(affichage);
    }

    //nettoyage
    affichage.destroy_window();

    return 0;
}