#pragma once
#include "CommonFunc.h"
#include "Material.h"

class HitPointInfo
{
public:
	HitPointInfo() { tNear = INT_MAX; lightIndex = -1; };
	HitPointInfo(const vec3&hitN, const vec3&hitPoint, const Material&mtl, const double&tNear) :
		hitN(hitN), hitPoint(hitPoint), mtl(mtl), tNear(tNear) {}

	vec3 hitN;
	vec3 hitPoint;
	Material mtl;
	double tNear;
	ObjectType objType;
	string name;
	int lightIndex;

private:

};

