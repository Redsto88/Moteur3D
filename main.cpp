#include <iostream>
#include "affichage.hpp"
#include "vector3.hpp"
#include "quad3D.hpp"
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
    Vector3 v1(0,0,0);
    Vector3 v2(0,0,1);
    Vector3 v3(0,1,0);
    Vector3 v4(0,1,1);
    Quad3D q1(v1,v2,v3,v4);
    Pave3D* p1 = new Pave3D(q1, 2);
    std::cout << typeid(p1).name() << std::endl;
    scene.addVolume(p1);
    Affichage affichage(scene, 800, 600);
    while(affichage.isRunning()){
        /**print isRunning*/
        affichage.afficher();
        // affichage.drawRect(0,0,100,100,0xFF0000FF);
        affichage.render();
        process_input(affichage);
    }
    affichage.destroy_window();
    return 0;
}
