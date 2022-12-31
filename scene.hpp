#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "volume3D.hpp"
#include "pave3D.hpp"

class Scene
{
    private:
        Vector3 lightSource;
        float intensite;
        std::vector<Volume3D*> volumes;

    public:
        Scene();
        Scene(std::vector<Volume3D*> _volumes, Vector3 _lightSource, int _intensite);
        std::vector<Volume3D*> getVolumes() const;
        Vector3 getLightSource();
        float getIntensite();
        void setIntensite(float _intensite);
        void addVolume(Volume3D* _volume);
        void addLightSource(Vector3 _lightSource);
        std::vector<Vector3> getPoints();
};


#endif
