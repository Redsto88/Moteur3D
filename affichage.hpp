#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP

#include <algorithm>
#include "scene.hpp"
#include "matrix4.hpp"

/**
 * @class Affichage affichage.hpp
 * @brief La classe affichage sert à initialiser la fenêtre SDL, calculer les positions des triangles à rendre te les affiche dans la fenêtre.
 * Elle est composée de :
 *      - neufs aattributs privés :
 *              - scene (Scene)
 *              - window (SDL_Window*)
 *              - rendere (SDL_Renderer*)
 *              - color_buffer (uint32_t*)
 *              - color_buffer_texture (SDL_texture)
 *              - window_width (int)
 *              - window-height (int)
 *              - fov_factor (float)
 *              - running (bool)
 */
class Affichage{
    private:
        /**
         * @brief L'attribut scene correspond à la scène à afficher.
         * Il est du type Scene.
         */
        Scene scene;
        /**
         * @brief L'attribut window est un pointeur vers une SDL_Window qui est la fenêtre de l'executable.
         * Il est du type SDL_Window*.
         */
        SDL_Window* window;
        /**
         * @brief L'attribut renderer est un pointeru vers un SDL_Renderer qui sert à afficher ce qui a été dessine avec la bibliothèque SDL2.
         * Il est de type SDL_Renderer*
         */
        SDL_Renderer* renderer;
        /**
         * @brief L'attribut color_buffer est un pointeur vers un unsigned 32 bit integer qui permet de stocker les pixels qui ont été coloré.
         * Il est de type uint32_t*
         */
        uint32_t* color_buffer;
        /**
         * @brief L'attribut color_buffer_texture ______________________________________________________.
         * Il est de type SDL_Texture*.
         */
        SDL_Texture* color_buffer_texture;
        /**
         * @brief L'attribut window_width correspond à la longueur de la fenêtre en nombre de pixels.
         * Il est de type int.
         */
        int window_width;
        /**
         * @brief L'attribut window_height correspond à la hauteur de la fenêtre en nombre de pixels.
         * Il est de type int.
         */
        int window_height;
        /**
         * @brief L'attribut fov_factor représente la mise au point de la caméra.
         * Il est de type float.
         */
        float fov_factor;
        /**
         * @brief L'attribut running sert à savoir si la fenêtre est ouverte ou non.
         * Il est de type bool.
         */
        bool running;
        
    public:
        /**
         * @brief Construit un nouvel Affichage avec sa scene et la taille de sa fenêtre.
         * 
         * @param _scene (Scene&)
         * @param _window_width (const int)
         * @param _window_height (const int)
         * @param _fov_factor 
         */
        Affichage(Scene& _scene, const int _window_width, const int _window_height, const float _fov_factor);
        /**
         * @brief Setter de l'attribut running.
         * 
         * @param _running (bool)
         */
        void Setrunning(bool _running);
        /**
         * @brief Fait le rendu de l'image à afficher à chaque frame par rapport au dernier rendu fait time secondes avant.
         * 
         * @param time (float)
         * @param isAnimated (bool)
         */
        void render(float time, bool isAnimated);
        /**
         * @brief met à jours le buffer de SDL_Texture et de pixels colorés.
         * 
         */
        void render_color_buffer(void);
        /**
         * @brief Nettoie l'attribut color_buffer. C'est à dire que si un pixel était coloré et ne doit plus l'être la frame d'après, il ne le sera pas.
         * 
         * @param color (uint32_t)
         */
        void clear_color_buffer(uint32_t color);
        /**
         * @brief Vérifie si la fenêtre est en cours d'utilisation. C'est un Getter de l'attribut running.
         * 
         * @return L'attribut running de l'instance (bool)
         */
        bool isRunning();
        /**
         * @brief Détruit la fenêtre et vide toute la mémoire utilisée.
         * 
         */
        void destroy_window();
        /**
         * @brief dessine un triangle projeté sur un plan dont les points sont des SDL_Points et plus des Vector3 selon le mode de rendu de la scene choisi.
         * 
         * @param renderer (SDL_Render*)
         * @param v1 (SDL_Point)
         * @param v2 (SDL_Point)
         * @param v3 (SDL_Point)
         * @param color (SDL_Color)
         * @param illumination (float)
         */
        void drawTriangle(SDL_Renderer* renderer,SDL_Point v1, SDL_Point v2, SDL_Point v3, SDL_Color color, float illumination);
};


#endif