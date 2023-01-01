#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "volume3D.hpp"
#include "pave3D.hpp"

class Scene
{
    private:
        std::vector<Volume3D*> volumes;
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
        void addLightSource(Vector3 _lightSource);
        std::vector<Vector3> getPoints();
};


#endif
