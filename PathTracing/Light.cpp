#include "Light.h"

void Light::setLightParam(const vec3 & _color, const double & _intensity, const int _lightIndex)
{
	color = _color;
	intensity = _intensity;
	obj->objType = LightType;
	obj->lightIndex = _lightIndex;
	center = (obj->aabb.maxBound + obj->aabb.minBound) / vec3(2);
}

//vec3 Light::calcDirectLightIntensity(Ray & ray, const vec3 & hitN, const double & bias, const vec2 & r1r2, ObjList & objList)
//{
//	double r1 = r1r2.x;
//	double r2 = r1r2.y;
//	float sinTheta = sqrtf(1 - r1 * r1);
//	float phi = 2 * M_PI * r2;
//	float x = sinTheta * cosf(phi);
//	float z = sinTheta * sinf(phi);
//	vec3 a(x, r1, z);
//	double radius;
//	vec3 center;
//	light->getLightParam(radius, center);
//	a *= radius;
//	a += center;
//
//	ray.dir = normalize(a - ray.ori);		//ori to light
//	ray.ori += vec3(bias)*ray.dir;
//	HitPointInfo hitPointInfo;
//	vec3 lightIntensity(0);
//	if (objList.calcObjListIntersection(ray, bias, hitPointInfo)
//		&& hitPointInfo.name == obj->name) {
//		lightIntensity = vec3(intensity)*color;
//	}
//
//	return lightIntensity;
//}


vec3 Light::calcDirectLightIntensity(Ray & ray, const vec3 & hitN, const double & bias, const vec2 & r1r2, ObjList & objList)
{
	ray.dir = normalize(center - ray.ori);		//ori to light
	ray.ori += vec3(bias)*ray.dir;
	HitPointInfo hitPointInfo;
	vec3 lightIntensity(0);
	if (objList.calcObjListIntersection(ray, bias, hitPointInfo)
		&& hitPointInfo.name == obj->name) {
		lightIntensity = vec3(intensity)*color;
	}

	return lightIntensity;
}

bool Light::calcLightIntensity(const Ray & ray, const double & bias, ObjList & objList, vec3 & lightIntensity)
{
	HitPointInfo hitPointInfo;
	if (objList.calcObjListIntersection(ray, bias, hitPointInfo)
		&& hitPointInfo.name == obj->name) {
		lightIntensity = vec3(intensity)*color;
		return true;
	}

	return false;
}

void SphereLight::setLightParam(const vec3 & _color, const double & _intensity, const int _lightIndex)
{
	color = _color;
	intensity = _intensity;
	sphere->objType = LightType;
	sphere->lightIndex = _lightIndex;
}

vec3 SphereLight::calcDirectLightIntensity(Ray & ray, const vec3 & hitN, const double & bias, const vec2 & r1r2, ObjList & objList)
{
	double r1 = r1r2.x;
	double r2 = r1r2.y;
	float sinTheta = sqrtf(1 - r1 * r1);
	float phi = 2 * M_PI * r2;
	float x = sinTheta * cosf(phi);
	float z = sinTheta * sinf(phi);
	vec3 a(x, r1, z);
	a *= radius;
	a += center;

	ray.dir = normalize(a - ray.ori);		//ori to light
	ray.ori += vec3(bias)*ray.dir;
	HitPointInfo hitPointInfo;
	vec3 lightIntensity(0);
	if (objList.calcObjListIntersection(ray, bias, hitPointInfo)
		&& hitPointInfo.name == sphere->name) {
		lightIntensity = vec3(intensity)*color;
	}

	return lightIntensity;
}
