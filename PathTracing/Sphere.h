#pragma once
#include "Object.h"

class Sphere:public Object
{
public:
	Sphere(const string&_name):Object(_name) { }
	void setParameters(const vec3&_center, const double&_radius, const Material& _mtl, const ObjectType&type, const double&albedo = 0.5) {
		center = _center;
		radius = _radius;
		mtl = _mtl;
		objType = type;
		mtl.albedo = albedo;
		calcBoudingBox();
	}
	bool calcObjectIntersection(const Ray&ray, const double& bias, HitPointInfo&hitPointInfo);
	void getRandCenter(double&radius, vec3&center) { radius = this->radius; center = this->center; }

private:
	vec3 center;
	double radius;
	Material mtl;
	void calcBoudingBox();			//calculate object's bouding box

};

