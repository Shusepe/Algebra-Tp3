#pragma once
#include <GL/glut.h>
#include "glm/glm.hpp"

using namespace glm;

class Plane
{
public:
    vec3 normal = { 0.f, 1.f, 0.f };
    float distance = 0.f;   

    //Constructors
    Plane(){
        normal = { 0.f, 1.f, 0.f };
        distance = 0.f;   
    }

    Plane(const vec3& p1, const vec3& norm) : normal(normalize(norm)), distance(dot(normal, p1)) {} 

    Plane(const vec3& norm, const float dist) 
    {
        normal = normalize(norm);
        distance = dist;
    }

    float getSignedDistanceToPlan(const glm::vec3& point) const
	{
		return glm::dot(normal, point) - distance;
	}
};