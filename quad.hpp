#ifndef Quad_HPP
#define Quad_HPP

#include <vector>
#include "Triangle.hpp"

/**
 * @class Quad quad.hpp
 * @brief La classe Quad est une classe représantant un quadrilatère à partir de deux triangles.
 * Elle est composée de :
 *      - trois attributs privés :
 *              - t1 (Triangle)
 *              - t2 (Triangle)
 *              - color (SDL_Color)
 *      - Trois constructeurs :
 *              - Un constructeur par défaut
 *              - un constructeur prenant deux cnst Triangle& et une const SDL_Color en entrée
 *              - un constructeur prenant quatres const Vector3& et une const SDL_Color en entrée
 *      - Un getter pour chaque attribut
 */
class Quad
{
private:
    /**
     * @brief L'attribut t1 représente le triangle ABC du quadrilatère, dans le sens trigonométrique.
     * Il est de type Triangle.
     */
    Triangle t1;
    /**
     * @brief L'attribut t2 représente le triangle CDA du quadrilatère, dans le sens trigonométrique.
     * Il est de type Triangle.
     */
    Triangle t2;
    /**
     * @brief L'attribut color contient la couleur du quadrilatère.
     * Il est de type SDL_Color
     */
    SDL_Color color;
    
public:
    /**
     * @brief Constructeur par défaut
     */
    Quad() = default;
    /**
     * @brief Construit un nouveau Quad à partir de deux triangles dont le troisème côté doit être le côté commun aux deux triangles.
     * 
     * @param _t1 (const Triangle&)
     * @param _t2 (const Triangle&)
     * @param _color (SDL_Color)
     */
    Quad(Triangle& _t1,Triangle& _t2, SDL_Color& _color);
    /**
     * @brief Construit un nouveau Quad de points A, B, C et D à donner dans le sens trigonométrique.
     * les vecteurs doivent être donné dans le sens trigonométrique suivant
            haut_droite
            haut_gauche
            bas_gauche
            bas_droite
     * @param _a (const Vector3&)
     * @param _b (const Vector3&)
     * @param _c (const Vector3&)
     * @param _d (const Vector3&)
     * @param _color (SDL_Color)
     */
    Quad(Vector3& _a, Vector3& _b, Vector3& _c, Vector3& _d,SDL_Color& _color); 
    /**
     * @brief Getter de l'attribut t1.
     * 
     * @return L'attibut t1 de l'instance (Triangle)
     */
    Triangle getT1() const;
    /**
     * @brief Getter de l'attribut t2.
     * 
     * @return L'attibut t2 de l'instance (Triangle)
     */
    Triangle getT2() const;
    /**
     * @brief Getter de l'attribut color.
     * 
     * @return L'attibut Color de l'instance (SDL_Color)
     */
    SDL_Color getColor() const;
};





#endif