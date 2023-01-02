#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vector3.hpp"

/**
 * @class Triangle triangle.hpp
 * @brief La classe Triangle représente les faces triangulaires des volumes avec ses points A, B et C donné dans le sens trigonométrique.
 * Elle est composée de :
 *      - quatres attributs privés :
 *              - a (Vector3)
 *              - b (Vector3)
 *              - c (Vector3)
 *              - color (SDL_Color)
 *      - deux constructeurs :
 *              - un constructeur par défaut
 *              - un constructeur prenant trois Vector3 et une SDL_Color en entrée
 *      - un getter et un setter pour chaque attribut
 *      - la méthode publique :
 *              - getCenterThirdSide()
 */
class Triangle{
    private:
        /**
         * @brief L'attribut a correspond au premier point du triangle.
         * Il est de type Vector3.
         */
        Vector3 a;
        /**
         * @brief L'attribut b correspond au deuxième point du triangle.
         * Il est de type Vector3.
         */
        Vector3 b;
        /**
         * @brief L'attribut c correspond au troisième point du triangle.
         * Il est de type Vector3.
         */
        Vector3 c;
        /**
         * @brief L'attribut color correspond à la couleur du triangle.
         * Il est de type SDL_Color.
         */
        SDL_Color color;

    public:
        /**
         * @brief Constructeur par défaut de la classe.
         */
        Triangle();
        /**
         * @brief Construit un nouveau Triangle avec ses trois points A, B et C à donner dans le sens trigonométrique.
         * 
         * @param a (Vector3)
         * @param b (Vector3)
         * @param c (Vector3)
         * @param _color (SDL_Color)
         */
        Triangle(Vector3& a, Vector3& b, Vector3& c, const SDL_Color& _color);
        /**
         * @brief Getter de l'attribut a. 
         * 
         * @return L'attribut a (Vector3)
         */
        Vector3& getA() const;
        /**
         * @brief Getter de l'attribut b. 
         * 
         * @return L'attribut b (Vector3)
         */
        Vector3& getB() const;
        /**
         * @brief Getter de l'attribut c. 
         * 
         * @return L'attribut c (Vector3)
         */
        Vector3& getC() const;
        /**
         * @brief Getter de l'attribut color. 
         * 
         * @return L'attribut color (SDL_Color)
         */
        SDL_Color& getColor() const;
        /**
         * @brief Setter de l'attribut a.
         * 
         * @param _a (Vector3)
         */
        void setA(const Vector3& _a);
        /**
         * @brief Setter de l'attribut b.
         * 
         * @param _b (Vector3)
         */
        void setB(const Vector3& _b);
        /**
         * @brief Setter de l'attribut c.
         * 
         * @param _c (Vector3)
         */
        void setC(const Vector3& _c);
        /**
         * @brief Setter de l'attribut color.
         * 
         * @param _color (SDL_Color)
         */
        void setColor(const SDL_Color& _color);
        /**
         * @brief Calcule la troisième côté du triangle, celui qui peut fomer la diagonale d'un quadrilatère.
         * 
         * @return Le miliei du troisième côté (Vector3)
         */
        Vector3 getCenterThirdSide();
        
        Triangle multiplyByMatrix(const Matrix4& mat);
        void operator+= (const Vector3& vec);
        void operator*= (float scalar);
        void inverseXY();
        void scaleToViewAndWindow(int window_width,int window_height);
};

std::ostream& operator<<(std::ostream& st, Triangle& tri);


#endif