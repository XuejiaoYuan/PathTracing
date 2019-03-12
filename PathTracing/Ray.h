#pragma once
#include "CommonFunc.h"

typedef enum {
	INSIDERAY,OUTSIDERAY
}RayType;

class Ray
{
public:
	Ray(const vec3&_ori = vec3(0), const vec3&_dir = vec3(0),const RayType&_rayType=OUTSIDERAY) :
		ori(_ori), dir(_dir), rayType(_rayType) {}
	void fresnel(const vec3&hitN, const double& Ni, double&kr, vec3&refractDir);
	void reflect(const vec3&hitN, vec3& reflectDir, bool inverse = false);

	vec3 ori;
	vec3 dir;
	RayType rayType;

private:

};
