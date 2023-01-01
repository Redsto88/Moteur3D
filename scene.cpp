#include "scene.hpp"
#include <iostream>

Scene::Scene() {
    volumes = std::vector<Volume3D*>();
    upDirection = Vector3(0, 1, 0);
    lookDirection = Vector3(10, 0, 5);
    cameraPosition = Vector3(-10, 0, -5);
    target = cameraPosition + lookDirection;
}

Scene::Scene(std::vector<Volume3D*> _volumes) {
    volumes = _volumes;
    upDirection = Vector3(0, 1, 0);
    lookDirection = Vector3(10, 0, 5);
    cameraPosition = Vector3(-10, 0, -5);
    target = cameraPosition + lookDirection;
}

std::vector<Volume3D*> Scene::getVolumes() const {
    return volumes;
}

void Scene::addVolume(Volume3D* _volume) {
    volumes.push_back(_volume);
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

void Scene::setCameraPosition(const Vector3& _cameraPosition) {
    cameraPosition = _cameraPosition;
    target = cameraPosition + lookDirection;
}

void Scene::setLookDirection(const Vector3& _lookDirection) {
    lookDirection = _lookDirection;
    target = cameraPosition + lookDirection;
}

void Scene::setUpDirection(const Vector3& _upDirection) {
    upDirection = _upDirection;
}

Vector3 Scene::getCameraPosition() const {
    return cameraPosition;
}

Vector3 Scene::getLookDirection() const {
    return lookDirection;
}

Vector3 Scene::getUpDirection() const {
    return upDirection;
}

Vector3 Scene::getTarget() const {
    return target;
}

