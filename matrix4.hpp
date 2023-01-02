#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <iostream>

/**
 * @class Matrix4 matrix4.hpp
 * @brief La classe Matrix4 représente une matrice carrée de dimension 4.
 * Elle est composée de : 
 *      - un attribut privé :
 *              - m (float[4][4])
 *      - deux constructeurs :
 *              - un constructeur par défaut
 *              - un constructeur prenant seize float en entrée
 *      - une méthode publique :
 *              - inverse()
 *      - des operators pour effectuer des calculs avec des instances de la classe
 */
class Matrix4
{
    private :
        /**
         * @brief L'attribut m est une matrice contenant les flottants de l'instance de Matrix4.
         * Il est de type float[4][4].
         */
        float m[4][4];
    
    public:
        /**
         * @brief Constructeur par défaut
         */
        Matrix4();
        /**
         * @brief Construit une nouvelle Matrix4 avec seize floats.
         * 
         * @param m00 (float)
         * @param m01 (float)
         * @param m02 (float)
         * @param m03 (float)
         * @param m10 (float)
         * @param m11 (float)
         * @param m12 (float)
         * @param m13 (float)
         * @param m20 (float)
         * @param m21 (float)
         * @param m22 (float)
         * @param m23 (float)
         * @param m30 (float)
         * @param m31 (float)
         * @param m32 (float)
         * @param m33 (float)
         */
        Matrix4(float m00, float m01, float m02, float m03,
                float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23,
                float m30, float m31, float m32, float m33);
        /**
         * @brief Calcule la matrice inverse de l'instance
         * 
         * @return L'inverse de l'instance (Matrix4) 
         */
        Matrix4 inverse();
        
        float& operator[](std::pair<int, int> index);
        const float& operator[](std::pair<int, int> index) const;
        Matrix4 operator *= (const Matrix4& m);
        friend Matrix4 operator*(const Matrix4& m, const Matrix4& m2);
};


std::ostream& operator<<(std::ostream& st, Matrix4& m);
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);


#endif