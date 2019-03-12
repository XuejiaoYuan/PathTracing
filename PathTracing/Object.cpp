#include "Object.h"
#include <iostream>

Object::~Object()
{
	meshList.clear();
}

void Object::calcBoudingBox()
{
	for (int i = 0; i < 3; i++) {
		double minB = INT_MAX;
		double maxB = INT_MIN;
		for (auto&mesh : meshList) {
			if (minB > mesh.aabb.minBound[i])
				minB = mesh.aabb.minBound[i];
			if (maxB < mesh.aabb.maxBound[i])
				maxB = mesh.aabb.maxBound[i];
		}
		aabb.minBound[i] = minB;
		aabb.maxBound[i] = maxB;
	}

}

bool Object::calcObjectIntersection(const Ray & ray, const double & bias, HitPointInfo & hitPointInfo)
{
	vec3 ori = ray.ori;
	vec3 dir = ray.dir;
	double tNear = INT_MAX;
	HitPointInfo tmpHitPointInfo;
	bool intersect;
	if (aabb.calcIntersection(ray)) {
		for (auto& mesh : meshList) {
			if (ray.rayType==OUTSIDERAY&&dot(mesh.getMeshNormal(), dir) > 0)
				continue;
			else if (ray.rayType==INSIDERAY&&dot(mesh.getMeshNormal(), dir) < 0)
				continue;
			intersect = mesh.calcMeshIntersection(ray, bias, tmpHitPointInfo);
			if (intersect&&tNear > tmpHitPointInfo.tNear) {
				tNear = tmpHitPointInfo.tNear;
				hitPointInfo = tmpHitPointInfo;
			}
		}
		if (tNear != INT_MAX)
			return true;
		else
			return false;
	}
	else
		return false;
}

void Object::setObjectType()
{
	if (meshList[0].mtl.Ni > 1)
		objType = TransparentType;
	else if (meshList[0].mtl.Ns > 1)
		objType = SpecularType;
	else
		objType = DiffuseType;
}
