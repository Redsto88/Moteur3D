#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>
#include<SDL2/SDL.h>
#include "matrix4.hpp"


/**
 * @class Vector3 vector3.hpp
 * @brief La classe Vector3 représente les vecteurs de dimension 3. Ceux-ci servent à calculer des positions dans un monde en trois dimensions
 * Elle est composée de :
 *      - quatres attributs privés :
 *              - x (float)
 *              - y (float)
 *              - z (float)
 *              - w (float)
 *      - un constructeur prenant 3 floats en entrée
 *      - un getter et un setter pour chaque attribut
 *      - les méthodes publiques :
 *              - normalize()
 *              - magnitude()
 *              - dotProduct()
 *              - crossProduct() 
 *      - des operators afin d'effectuer des calculs avec les instances de la classe
 */
class Vector3 {

    private : 
        /**
         * @brief L'attribut x correspond au premier élément du vecteur.
         * Il est de type float.
         */
        float x;
        /**
         * @brief L'attribut y correspond au deuxième élément du vecteur
         * Il est de type float.
         */
        float y;
        /**
         * @brief L'attribut z correspond au troisième élément du vecteur.
         * Il est de type float.
         */
        float z;
        /**
         * @brief L'attribut w sert à homogénéiser les attributs x, y et z lors des projections surt un plan en deux dimensions.
         * Il est de type float.
         */
        float w;
    
    public :
        /**
         * @brief Construit un nouveau Vector3 de valeur (x,y,z) t w=1.
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        Vector3(float x = 0, float y = 0, float z = 0);
        /**
         * @brief Getter de l'attribut x.
         * 
         * @return L'attribut x (float) 
         */
        float getX() const;
        /**
         * @brief Getter de l'attribut y.
         * 
         * @return L'attribut y (float) 
         */
        float getY() const;
        /**
         * @brief Getter de l'attribut z.
         * 
         * @return L'attribut z (float) 
         */
        float getZ() const;
        /**
         * @brief Getter de l'attribut w.
         * 
         * @return L'attribut w (float) 
         */
        float getW() const;

        /**
         * @brief Setter de l'attribut x.
         * 
         * @param x (float)
         * @return L'instance avec sa valeur x mise à jour (Vector3) 
         */
        Vector3 setX(const float x);
        /**
         * @brief Setter de l'attribut y.
         * 
         * @param y (float)
         * @return L'instance avec sa valeur y mise à jour (Vector3) 
         */
        Vector3 setY(const float y);
        /**
         * @brief Setter de l'attribut z.
         * 
         * @param z (float)
         * @return L'instance avec sa valeur z mise à jour (Vector3) 
         */
        Vector3 setZ(const float z);
        /**
         * @brief Setter de l'attribut w.
         * 
         * @param w (float)
         * @return L'instance avec sa valeur w mise à jour (Vector3) 
         */
        Vector3 setW(const float w);

        /**
         * @brief Normalise le vecteur.
         */
        void normalize();
        /**
         * @brief Calcule la norme du vecteur et la retourne
         * 
         * @return norme de l'instance (float) 
         */
        float magnitude();
        /**
         * @brief Effectue le produit scalaire entre l'instance et un autre Vector3 et retourne le résultat.
         * 
         * @param other (Vector3)
         * @return Résultat du produit scalaire (float) 
         */
        float dotProduct(const Vector3& other) const;
        /**
         * @brief Effectue le produit vectoriel entre l'instance et un autre Vector3 et retourne le résultat.
         * 
         * @param other (Vector3)
         * @return Résultat du produit vectoriel (Vector3) 
         */
        Vector3 crossProduct(const Vector3& other) const;
        /**
         * @brief Effectue le produit matriciel entre l'instance et une Matrix4 et retourne le résultat.
         * 
         * @param vOutput (Vector3)
         * @param m (Matrix4)
         * @return vOutput qui prend le résultat du produit matriciel (Vector3) 
         */
        Vector3 multiplyVector3ByMatrix4(Vector3 vOutput, const Matrix4& m);

        void operator+=(const Vector3& v);
        void operator-=(const Vector3& v);
        void operator*=(const float& f);
        void operator/=(const float& f);

        friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
        friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
        friend Vector3 operator*(const Vector3& v1, const float& f);
        friend Vector3 operator*(const float& f, const Vector3& v1);
        friend Vector3 operator*(const Vector3& v1, const Vector3& v2);

        Vector3 multiplyVector3ByMatrix4(const Matrix4& m);
        Vector3 multiplyVector3ByMatrix4(Vector3 vOutput, const Matrix4& m);
        
        void inverseXY();

        float magnitude();
};

std::ostream& operator<<(std::ostream& st, Vector3 v);


Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v1, const float& f);
Vector3 operator*(const float& f, const Vector3& v1);
Vector3 operator*(const Vector3& v1, const Vector3& v2);
Vector3 operator/(const Vector3& v1, const float& f);
Vector3 operator/(const float& f, const Vector3& v1);

Vector3 planeNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);


Matrix4 Matrix_camera(Vector3& pos, Vector3& cible, Vector3& up);
Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);


#endif