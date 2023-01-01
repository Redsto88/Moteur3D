#ifndef SCENE_HPP
#define SCENE_HPP

#include "volume3D.hpp"


class Scene
{
    private:
        std::vector<Volume3D*> volumes;
        Vector3 cameraPosition;
        Vector3 lookDirection;
        Vector3 upDirection;
        Vector3 target;
        Vector3 lightSource;
        float intensite;
        bool isLit;
        bool showEdge;
        int lineThickness;
        bool anim;
        SDL_Color colorLines;

    public:
        Scene();
        Scene(std::vector<Volume3D*> _volumes, Vector3 _lightSource, int _intensite, bool _isLit, bool _showEdge, int _lineThickness, SDL_Color _colorlines, bool _anim);
        std::vector<Volume3D*> getVolumes() const;
        Vector3 getLightSource();
        float getIntensite();
        bool getIsLit();
        bool getShowEdge();
        int getLineThickness();
        SDL_Color getColorLines();
        bool getAnim();
        void addVolume(Volume3D* _volume);
        void setCameraPosition(const Vector3& _cameraPosition);
        void setLookDirection(const Vector3& _lookDirection);
        void setUpDirection(const Vector3& _upDirection);
        Vector3 getCameraPosition() const;
        Vector3 getLookDirection() const;
        Vector3 getUpDirection() const;
        Vector3 getTarget() const;
};


#endif
