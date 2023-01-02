#include "scene.hpp"


Scene::Scene() {
    volumes = std::vector<Volume3D*>();
    upDirection = Vector3(0, 1, 0);
    lookDirection = Vector3(0, 0, 4);
    cameraPosition = Vector3(0, 0, -4);
    target = cameraPosition + lookDirection;
    lightSource = Vector3(0, 0, 0);
    intensite = 20;
    isLit = true;
    showEdge = false;
    lineThickness = 1;
    colorLines = {255, 255, 255, 255};
    anim = false;
}

Scene::Scene(std::vector<Volume3D*> _volumes, Vector3 _lightSource, int _intensite, bool _isLit, bool _showEdge, int _lineThickness, SDL_Color _colorlines, bool _anim) {
    volumes = _volumes;
    upDirection = Vector3(0, 1, 0);
    lookDirection = Vector3(0, 0, 4);
    cameraPosition = Vector3(0, 0, -4);
    target = cameraPosition + lookDirection;
    lightSource = _lightSource;
    intensite = _intensite;
    isLit = _isLit;
    showEdge = _showEdge;
    lineThickness = _lineThickness;
    colorLines = _colorlines;
    anim = _anim;
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

bool Scene::getIsLit(){
    return isLit;
}

bool Scene::getShowEdge(){
    return showEdge;
}

int Scene::getLineThickness(){
    return lineThickness;
}

SDL_Color Scene::getColorLines(){
    return colorLines;
}

bool Scene::getAnim(){
    return anim;
}

void Scene::addVolume(Volume3D* _volume) {
    volumes.push_back(_volume);
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

