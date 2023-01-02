#ifndef SCENE_HPP
#define SCENE_HPP

#include "volume3D.hpp"

/**
 * @class Scene scene.hpp
 * @brief La classe Scene contient tous les objets à afficher ainsi que les informations concernant la lumière, le mode de rendu, l'animation et la caméra.
 * Elle est composée de :
 *      - douze attributs privés :
 *              - volumes (std::vector<Volume3D*>)
 *              - cameraPosition (Vector3)
 *              - upDirection (Vector3)
 *              - target (Vector3)
 *              - lookDirection (Vector3)
 *              - lightSource(Vector3)
 *              - intensite (float)
 *              - isLit (bool)
 *              - showEdge (bool)
 *              - lineThickness (int)
 *              - colorLines (SDL_Color)
 *              - anim (bool)
 *      - deux constructeurs :
 *              - un constructeur par défaut
 *              - un constructeur prenant une liste de pointeurs vers des Volume3D, un Vector3, deux int, trois bool et un SDL_Color en entrée
 *      - un getter pour chaque attribut
 *      - un setter pour les attributs :
 *              - cameraPosition
 *              - upDirection
 *              - target 
 *              - lookDirection
 */
class Scene
{
    private:
        /**
         * @brief L'attribut volumes un un vecteur de pointeurs vers tous les Volume3D présents dans la scène.
         * Il est de type std::vector<Volume3D*>.
         */
        std::vector<Volume3D*> volumes;
        /**
         * @brief L'attribut cameraPosition contient la position fixe de la caméra.
         * Il est de type Vector3.
         */
        Vector3 cameraPosition;
        /**
         * @brief L'attribut upDirection représente l'orientation vertocale de la caméra.
         * Il est de type Vector3.
         */
        Vector3 upDirection;
        /**
         * @brief L'attribut target représente l'orientation latérale de la caméra.
         * Il est de type Vector3.
         */
        Vector3 target;
        /**
         * @brief L'attribut lookDirection repréesnte le sens dans lequel la caméra doit regarder, d'après l'orientation de target.
         * Il est de type Vector3.
         */
        Vector3 lookDirection;
        /**
         * @brief L'attribut lightSource contient la position de la source de lumière de la scène
         * Il est de type Vector3.
         */
        Vector3 lightSource;
        /**
         * @brief L'attribut intensite représente la puissance de l'intensité de la source lumineuse.
         * Il est de type float.
         */
        float intensite;
        /**
         * @brief L'attribut isLit sert à savoir si la scène doit être rendu en mode Lit ou Unlit.
         * Il est de type bool.
         */
        bool isLit;
        /**
         * @brief L'attribut showEdge sert à savoir si la scène doit être rendu en Wireframe ou non.
         * Il est de type bool.
         */
        bool showEdge;
        /**
         * @brief L'attribut lineThickness représente l'épaisseur des lignes dans le mode Wireframe.
         * Il est de type int.
         */
        int lineThickness;
        /**
         * @brief L'attribut colorLines contient la couleur des lignes dans le mode Wireframe.
         * Il est de type SDL_Color.
         */
        SDL_Color colorLines;
        /**
         * @brief L'attribut anim sert à savoir si l'animation doit se jouer ou non.
         * Il est de type bool.
         */
        bool anim;

    public:
        /**
         * @brief Constructeur par défaut
         */
        Scene();
        /**
         * @brief Construit une nouvelle scène
         * 
         * @param _volumes (std::vector<Volume3D*>)
         * @param _lightSource (Vector3)
         * @param _intensite (int)
         * @param _isLit (bool)
         * @param _showEdge (bool)
         * @param _lineThickness (int)
         * @param _colorlines (SDL_Color)
         * @param _anim (bool)
         */
        Scene(std::vector<Volume3D*> _volumes, Vector3 _lightSource, int _intensite, bool _isLit, bool _showEdge, int _lineThickness, SDL_Color _colorlines, bool _anim);
        /**
         * @brief Getter de l'attribut volumes.
         * 
         * @return retourne l'attribut volumes de l'instance (std::vector<Volume3D*>)
         */
        std::vector<Volume3D*> getVolumes() const;
        /**
         * @brief Getter de l'attribut lightSource.
         * 
         * @return retourne l'attribut lightSource de l'instance (Vector3)
         */
        Vector3 getLightSource();
        /**
         * @brief Getter de l'attribut intensite.
         * 
         * @return retourne l'attribut intensite de l'instance (int))
         */
        float getIntensite();
        /**
         * @brief Getter de l'attribut isLit.
         * 
         * @return retourne l'attribut isLit de l'instance (bool)
         */
        bool getIsLit();
        /**
         * @brief Getter de l'attribut showEdge.
         * 
         * @return retourne l'attribut showEdge de l'instance (bool)
         */
        bool getShowEdge();
        /**
         * @brief Getter de l'attribut lineThickness.
         * 
         * @return retourne l'attribut lineThickness de l'instance (int)
         */
        int getLineThickness();
        /**
         * @brief Getter de l'attribut colorLines.
         * 
         * @return retourne l'attribut colorLines de l'instance (SDL_Color)
         */
        SDL_Color getColorLines();
        /**
         * @brief Getter de l'attribut anim.
         * 
         * @return retourne l'attribut anim de l'instance (bool)
         */
        bool getAnim();
        /**
         * @brief Ajoute un pointeur vers un volume à la scène
         * 
         * @param _volume (Volume3D*)
         */
        void addVolume(Volume3D* _volume);
        /**
         * @brief Setter de l'attribut cameraPosition.
         * 
         * @param _cameraPosition (const Vector3&)
         */
        void setCameraPosition(const Vector3& _cameraPosition);
        /**
         * @brief Setter de l'attribut lookDirection.
         * 
         * @param _lookDirection (const Vector3&)
         */
        void setLookDirection(const Vector3& _lookDirection);
        /**
         * @brief Setter de l'attribut upDirection.
         * 
         * @param _upDirection (const Vector3&)
         */
        void setUpDirection(const Vector3& _upDirection);
        /**
         * @brief Getter de l'attribut cameraPosition.
         * 
         * @return retourne l'attribut cameraPosition de l'instance (Vector3)
         */
        Vector3 getCameraPosition() const;
        /**
         * @brief Getter de l'attribut lookDirection.
         * 
         * @return retourne l'attribut lookDirection de l'instance (Vector3)
         */
        Vector3 getLookDirection() const;
        /**
         * @brief Getter de l'attribut upDirection.
         * 
         * @return retourne l'attribut upDirection de l'instance (Vector3)
         */
        Vector3 getUpDirection() const;
        /**
         * @brief Getter de l'attribut target.
         * 
         * @return retourne l'attribut target de l'instance (Vector3)
         */
        Vector3 getTarget() const;
};


#endif
