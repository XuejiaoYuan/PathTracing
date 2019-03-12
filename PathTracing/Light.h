#pragma once
#include "Object.h"
#include "ObjList.h"
#include "Sphere.h"

class Light
{
public:
	Light() {}
	Light(Object* _obj) :obj(_obj) {};
	virtual void setLightParam(const vec3&_color, const double& _intensity, const int _lightIndex);
	virtual vec3 calcDirectLightIntensity(Ray&ray, const vec3&hitN, const double&bias, const vec2& r1r2, ObjList& objList);
	bool calcLightIntensity(const Ray&ray, const double&bias, ObjList&objList, vec3&lightIntensity);
	~Light() {}
	vec3 color;
	float intensity;

protected:
	Object* obj;
	vec3 center;

};

class SphereLight:public Light
{
public:
	SphereLight(Sphere*_sphere) :sphere(_sphere) { sphere->getRandCenter(radius, center);  }
	void setLightParam(const vec3&_color, const double&_intensity, const int _lightIndex);
	vec3 calcDirectLightIntensity(Ray&ray, const vec3&hitN, const double&bias, const vec2& r1r2, ObjList& objList);
	void setLightObject(Sphere* _sphere) { sphere = _sphere;  }

private:
	Sphere* sphere;
	double radius;
};

