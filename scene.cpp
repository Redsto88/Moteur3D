#include "scene.hpp"

Scene::Scene() {
    volumes = std::vector<Volume3D>();
}

Scene::Scene(std::vector<Volume3D> _volumes) {
    volumes = _volumes;
}

std::vector<Volume3D> Scene::getVolumes() const {
    return volumes;
}

void Scene::addVolume(Volume3D _volume) {
    volumes.push_back(_volume);
}