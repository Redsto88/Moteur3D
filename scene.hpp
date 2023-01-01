#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "volume3D.hpp"
#include "pave3D.hpp"
#include "vector3.hpp"

class Scene
{
    private:
        std::vector<Volume3D*> volumes;
        Vector3 cameraPosition;
        Vector3 lookDirection;
        Vector3 upDirection;
        Vector3 target;

    public:
        Scene();
        Scene(std::vector<Volume3D*> _volumes);
        std::vector<Volume3D*> getVolumes() const;
        void addVolume(Volume3D* _volume);
        std::vector<Vector3> getPoints();
        void setCameraPosition(const Vector3& _cameraPosition);
        void setLookDirection(const Vector3& _lookDirection);
        void setUpDirection(const Vector3& _upDirection);
        Vector3 getCameraPosition() const;
        Vector3 getLookDirection() const;
        Vector3 getUpDirection() const;
        Vector3 getTarget() const;
};


#endif
