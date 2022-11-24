#pragma once
#include "glm/glm.hpp"
#include "frustum.h"

using namespace glm;

class Sphere 
{
public:
	vec3 center;
	float radius;

	Sphere();
	
	Sphere(vec3 cen, float rad)
	{
		center = cen;
		radius = rad;
	}

	bool isOnOrForwardPlan(const Plane& plane) const
	{
		return plane.getSignedDistanceToPlan(center) > -radius;
	}

	bool isOnFrustum(const Frustum& camFrustum)
	{
		return (
			isOnOrForwardPlan(camFrustum.leftFace) &&
			isOnOrForwardPlan(camFrustum.rightFace) &&
			isOnOrForwardPlan(camFrustum.farFace) &&
			isOnOrForwardPlan(camFrustum.nearFace) &&
			isOnOrForwardPlan(camFrustum.topFace) &&
			isOnOrForwardPlan(camFrustum.bottomFace)
		);
	};


	void draw()
	{
		glColor3f(1, 0, 0);
		glutSolidSphere(radius, 10, 10);
		glTranslatef(center.x, center.y, center.z);
	}
	
	void draw(bool isVisible)
	{
		if (isVisible)
		{
			glColor3f(1, 0, 0);
		} else 
		{
			glColor4f(0, 1, 0, 0.1);
		}
	
		glutSolidSphere(radius, 10, 10);
		glTranslatef(center.x, center.y, center.z);
	}
};

Sphere::Sphere()
{
	center = {0.0f, 0.0f , 0.0f};
	radius = 0.f;
}

