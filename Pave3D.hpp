#ifndef PAVE3D_HPP
#define PAVE3D_HPP

#include "volume3D.hpp"

/**
 * @class Pave3D pave3D.hpp
 * @brief La classe Pave3D est une classe héritant de Volume3D et représente un pavé en trois dimensions
 * Elle est composée de :
 *      - deux attributs privés :
 *              - quads (std::vector<Quad>)
 *              - color (STD_Color)
 *      - deux constructeurs :
 *              - un constructeur par copie
 *              - un constructeur prenant huit Vector3& une SDL_COlor en entrée
 *      - deux méthodes override publiques :
 *              - getColor()
 *              - getQuads()
 */
class Pave3D : public Volume3D
{
    private:
    /**
         * @brief L'attribut quads est un vecteur contenant chaque quad appartenant au pavé.
         * Il est de type std::vector<Quad>.
         */
        std::vector<Quad> quads;
        /**
         * @brief L'attribut color représente la couleur du pavé.
         * Il est de type SDL_Color.
         */
        SDL_Color color;

    public:
        /**
         * @brief Constructeur par copie
         *  
         * @param _pave (Pave3D&)
         */
        Pave3D(Pave3D& _pave);
        /**
         * @brief Construit un nouveau Pave3D en donnant les points du pavé.
         * Les Vectors3 en entrée sont les points du pavé. Ils doivent être rentré dans le bon ordre.
         * 
         * @param leftBotomForward (Vector3&)
         * @param leftTopForward (Vector3&)
         * @param rightTopForward (Vector3&)
         * @param rightBotomForward (Vector3&)
         * @param rightTopBackward (Vector3&)
         * @param rightBotomBackward (Vector3&)
         * @param leftTopBackward (Vector3&)
         * @param leftBotomBackward (Vector3&)
         * @param _color (SDL_Color)
         */
        Pave3D(const Vector3& leftBotomForward,
                const Vector3& leftTopForward,
                const Vector3& rightTopForward,
                const Vector3& rightBotomForward,
                const Vector3& rightTopBackward,
                const Vector3& rightBotomBackward,
                const Vector3& leftTopBackward,
                const Vector3& leftBotomBackward,
                const SDL_Color& _color);
        /**
         * @brief Getter de l'attribut quads.
         * 
         * @return L'attribut quad de l'instance (std::vector<Quad>) 
         */
        std::vector<Quad> getQuads() override;
        /**
         * @brief Getter de l'attribut color.
         * 
         * @return L'attribut color de l'instance (SDL_Color) 
         */
        SDL_Color getColor() override;
};





#endif