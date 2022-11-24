#pragma once
#include "plane.h"
#include "camera.h"
#include "glm/glm.hpp"

using namespace glm;

struct Frustum
{
    Plane bottomFace;
    Plane topFace; 
    Plane leftFace;
    Plane rightFace;
    Plane farFace;
    Plane nearFace;
};

Frustum getFrustumFromCamera(Camera& cam, float aspect, float fov, float zNear, float zFar)
{
    Frustum frustum;
    const float halfVSide = zFar * tanf(fov * .5f);
    const float halfHSide = halfVSide * aspect;
    const vec3 frontMultFar = zFar * cam.Front;

    frustum.bottomFace = Plane(cam.Position, cross(frontMultFar + cam.Up * halfVSide, cam.Right));
    frustum.topFace = Plane(cam.Position, cross(cam.Right, frontMultFar - cam.Up * halfVSide));
    frustum.leftFace = Plane(cam.Position, cross(frontMultFar - cam.Right * halfHSide, cam.Up));
    frustum.rightFace = Plane(cam.Position, cross(cam.Up, frontMultFar + cam.Right * halfHSide));
    frustum.farFace = Plane(cam.Position + frontMultFar, -cam.Front);
    frustum.nearFace = Plane(cam.Position + zNear * cam.Front, cam.Front);

    return frustum;
};