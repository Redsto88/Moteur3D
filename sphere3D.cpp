#include "sphere3D.hpp"
#include <SDL2/SDL.h>


Sphere3D::Sphere3D(Sphere3D& _sphere)
{
  center = _sphere.getCenter();
  radius = _sphere.getRadius();
  quads = _sphere.getQuads();
}

Sphere3D::Sphere3D(Vector3 _center, float _radius, int numSegments) {
  
  center = _center;
  radius = _radius;

  // Calcul des points de la sphère
  std::vector<Vector3> points;
  for (int i = 0; i <= numSegments; i++) {
    float lat = -M_PI/2 + M_PI * (float)i / numSegments;
    for (int j = 0; j < numSegments; j++) {
      float lng = 2 * M_PI * (float)j / numSegments;
      float x = radius * cos(lat) * cos(lng) + center.getX(); 
      float y = radius * cos(lat) * sin(lng) + center.getY();
      float z = radius * sin(lat) + center.getZ();
      points.push_back({x, y, z});
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
      Quad quad(points[a], points[b], points[c],points[d]);
      quads.push_back(quad);

      /*triangles des faces Permtra de faire des tests pour faire des vérifications
      Triangle tri1(points[a], points[b], points[c]);
      Triangle tri2(points[a], points[c], points[d]);
      triangles.push_back(tri1);
      triangles.push_back(tri2);*/
    }
  }
}

Vector3 Sphere3D::getCenter()
{
  return center;
}

float Sphere3D::getRadius()
{
  return radius;
}

std::vector<Quad> Sphere3D::getQuads()
{
  return quads;
}




/* AUTRE METHODE 
#include <iostream>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>
#include "vector3.hpp"


// Fonction pour créer les points d'une sphère
std::vector<Vector3> createSpherePoints(float radius, int numVerticalSubdivisions, int numHorizontalSubdivisions) {
  std::vector<Vector3> points;

  // Pas de subdivisions
  if (numVerticalSubdivisions == 0 || numHorizontalSubdivisions == 0) {
    return points ;
  }

  // Nombre de degrés de chaque subdivision verticale et horizontale
  float verticalDegrees = 180.0f / numVerticalSubdivisions;
  float horizontalDegrees = 360.0f / numHorizontalSubdivisions;

  // Création des points
  for (float i = -90.0f; i <= 90.0f; i += verticalDegrees) {
    for (float j = 0.0f; j < 360.0f; j += horizontalDegrees) {
      float x = radius * sin(i * M_PI / 180.0f) * cos(j * M_PI / 180.0f);
      float y = radius * sin(i * M_PI / 180.0f) * sin(j * M_PI / 180.0f);
      float z = radius * cos(i * M_PI / 180.0f);
      points.emplace_back(x, y, z);
    }
  }

  return points
}*/