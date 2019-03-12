#pragma once
#include "Ray.h"


class AABB
{
public:
	AABB();
	void calcBounds(const vector<vec3>& v, AABB& aabb);
	bool calcIntersection(const Ray&ray);

	vec3 minBound;	//minX, minY, minZ
	vec3 maxBound;	//maxX, maxY, maxZ

private:

};

