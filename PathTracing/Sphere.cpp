#include "Sphere.h"

void Sphere::calcBoudingBox()
{
	aabb.minBound = vec3(center - vec3(radius));
	aabb.maxBound = vec3(center + vec3(radius));
}


bool Sphere::calcObjectIntersection(const Ray & ray, const double & bias, HitPointInfo & hitPointInfo)
{
	double tNear = 0;
	float tmp_val = dot(ray.dir,(ray.ori - center));
	vec3 tmp_vec = ray.ori - center;
	float val = tmp_val*tmp_val - dot(ray.dir, ray.dir)*(dot(tmp_vec, tmp_vec) - radius*radius);

	float inv_dot = 1 / dot(ray.dir, ray.dir);
	if (val<0)
		return false;
	else if (abs(val) < bias)
	{
		tNear = -tmp_val*inv_dot;
		if (tNear < 0)
			return false;
	}
	else
	{
		val = sqrt(val);
		float t1 = (-tmp_val + val)*inv_dot;
		float t2 = (-tmp_val - val)*inv_dot;
		if (t1<0 && t2<0)
			return false;
		else if (t1 < 0)
			tNear = t2;
		else if (t2 < 0)
			tNear = t1;
		else
			tNear = fmin(t1, t2);
	}
	hitPointInfo.tNear = tNear;
	hitPointInfo.hitPoint = ray.ori + vec3(tNear)*ray.dir;
	hitPointInfo.mtl = this->mtl;
	hitPointInfo.hitN = normalize(hitPointInfo.hitPoint - center);
	return true;
}
