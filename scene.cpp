#include "scene.hpp"
#include <iostream>

Scene::Scene() {
    volumes = std::vector<Volume3D*>();
}

Scene::Scene(std::vector<Volume3D*> _volumes, Vector3 _lightSource, int _intensite) {
    volumes = _volumes;
    lightSource = _lightSource;
    intensite = _intensite;
}

std::vector<Volume3D*> Scene::getVolumes() const {
    return volumes;
}

Vector3 Scene::getLightSource(){
    return lightSource;
}

float Scene::getIntensite(){
    return intensite;
 }

void Scene::setIntensite(float _intensite){
    intensite = _intensite;
}

void Scene::addVolume(Volume3D* _volume) {
    volumes.push_back(_volume);
}

void Scene::addLightSource(Vector3 _lightSource){
    lightSource =_lightSource ;
}

std::vector<Vector3> Scene::getPoints() {
    std::vector<Vector3> points;
    for (int i = 0; i < volumes.size(); i++) {
        std::vector<Quad> quads = volumes[i]->getQuads();
        for (int j = 0; j < quads.size(); j++) {
            std::vector<Vector3> quadPoints = quads[j].getPoints();
            for (int k = 0; k < quadPoints.size(); k++) {
                points.push_back(quadPoints[k]);
            }
        }
    }
    return points;
}