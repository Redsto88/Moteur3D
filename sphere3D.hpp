#ifndef SPHERE3D_HPP
#define SPHERE3D_HPP

#include "volume3D.hpp"

/**
 * @class Sphere3D sphere3D.hpp
 * @brief La classe Sphere3D est une classe héritant de Volume3D et représente une sphèree en trois dimensions.
 * Elle est composée de :
 *      - deux attributs privés :
 *              - quads (std::vector<Quad>)
 *              - color (STD_Color)
 *      - un constructeur prenant un Vector3&, un const float, un const int et une SDL_COlor en entrée
 *      - deux méthodes override publiques :
 *              - getColor()
 *              - getQuads()
 */
class Sphere3D : public Volume3D
{
    private:
        /**
         * @brief L'attribut quads est un vecteur contenant chaque quad appartenant à la sphère.
         * Il est de type std::vector<Quad>.
         */
        std::vector<Quad> quads;
        /**
         * @brief L'attribut color représente la couleur de la sphère.
         * Il est de type SDL_Color.
         */
        SDL_Color color;
    
    public:
        /**
         * @brief Constructeur par copie.
         * 
         * @param _sphere (Sphere3D&)
         */
        Sphere3D(Sphere3D& _sphere);
        /**
         * @brief Construit une nouvelle Sphere3D de centre _center, de rayon _radius, de couleur _color avec _numSegment subdivisions transversales et longitudinales.
         * 
         * @param _center (Vector3&)
         * @param _radius (const float)
         * @param _numSegments (const int)
         * @param _color (SDL_Color)
         */
        Sphere3D(Vector3& _center, const float _radius, const int _numSegments, SDL_Color _color);
        /**
         * @brief Getter de l'attribut color.
         * 
         * @return l'attribut color de l'instance (SDL_Color)
         */
        SDL_Color getColor() override;
        /**
         * @brief Getter de l'attibut quads.
         * 
         * @return l'attribut quads de l'instance (std::vector<Quad>)
         */
        std::vector<Quad> getQuads() override;

};



#endif