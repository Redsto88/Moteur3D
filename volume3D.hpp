#ifndef VOL3D_HPP
#define VOL3D_HPP

#include "Quad.hpp"

/**
 * @class Volume3D volume3D.hpp
 * @brief La classe Volume3D est une classe générique pour tous les objets pouvant être représentés en trois dimensiosn.
 * Elle est composée de :
 *      - deux attributs privés :
 *              - quads (std::vector<Quad>)
 *              - color (STD_Color)
 *      - un constructeur par défaut
 *      - un destructeur par défaut
 *      - deux méthodes virtuelles publiques :
 *              - getColor()
 *              - getQuads()
 */
class Volume3D
{
    private:
        /**
         * @brief L'attribut quads est un vecteur contenant chaque quad appartenant au volume.
         * Il est de type std::vector<Quad>.
         */
        std::vector<Quad> quads;
        /**
         * @brief L'attribut color représente la couleur de l'objet.
         * Il est de type SDL_Color.
         */
        SDL_Color color;

    public:
        /**
         * @brief Constructeur par défaut de la classe Volume3D
         */
        Volume3D() = default;

        /**
         * @brief Destructeur par défaut de la classe Volume3D
         */
        ~Volume3D() = default;

        /**
         * @brief Getter de l'attribut color.
         * 
         * @return l'attribut color de l'instance (SDL_Color)
         */
        virtual SDL_Color getColor()
        {
            std::cout << "WRONG" << std::endl;
            std::cout << "couleur = " << color.a << "; " << color.r << "; " << color.g << "; " << color.b << std::endl;
            return color;
        };

        /**
         * @brief Getter de l'attibut quads.
         * 
         * @return l'attribut quads de l'instance (std::vector<Quad>)
         */
        virtual std::vector<Quad> getQuads()
        {
            std::cout << "WRONG" << std::endl;
            std::cout << "quads.size() = " << quads.size() << std::endl;
            return quads;
        };
};

#endif