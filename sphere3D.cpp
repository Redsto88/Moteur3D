#include "sphere3D.hpp"


Sphere3D::Sphere3D(Sphere3D& _sphere){
  quads = _sphere.getQuads();
}

Sphere3D::Sphere3D(Vector3& _center, const float _radius, const int numSegments, SDL_Color _color){
  color = _color;
  // Calcul des points de la sphère
  std::vector<Vector3> points;
  int k = 0;
  for (int i = 0; i <= numSegments; i++) {
    float lat = -M_PI/2 + M_PI * ((float)i) / numSegments;
    for (int j = 0; j <= numSegments; j++) {
      float lng = 2 * M_PI * ((float)j) / numSegments;
      float x = _radius * cos(lat) * cos(lng) + _center.getX(); 
      float y = _radius * cos(lat) * sin(lng) + _center.getY();
      float z = _radius * sin(lat) + _center.getZ();
      points.push_back({x, y, z});
      k++;
    }
  }


  // Calcul des faces de la sphère
  for (int i = 0; i < numSegments; i++) {
    for (int j = 0; j < numSegments; j++) {
      int a = i * (numSegments+1) + j;
      int b = (i+1) * (numSegments+1) + j;
      int c = (i+1) * (numSegments+1) + j + 1;
      int d = i * (numSegments+1) + j + 1;
      //face quadrilatère
      Quad quad(points[a], points[b], points[c],points[d],color);
      quads.push_back(quad);

    }
  }
}

SDL_Color Sphere3D::getColor(){
  return color;
}

std::vector<Quad> Sphere3D::getQuads(){
  return quads;
}