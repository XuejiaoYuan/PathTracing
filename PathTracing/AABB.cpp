#include "AABB.h"

AABB::AABB()
{
	
}

void AABB::calcBounds(const vector<vec3>& v, AABB & aabb)
{
	for (int i = 0; i < 3; i++) {
		double minB = INT_MAX;
		double maxB = INT_MIN;
		for (int j = 0; j < v.size(); j++) {
			if (minB > v[j][i])
				minB = v[j][i];
			if (maxB < v[j][i])
				maxB = v[j][i];
		}
		minBound[i] = minB;
		maxBound[i] = maxB;
	}
}

bool AABB::calcIntersection(const Ray & ray)
{
	vec3 ori = ray.ori;
	vec3 dir = ray.dir;
	vec3 tMin, tMax;
	for (int i = 0; i < 3; i++) {
		if (abs(dir[i])<1e-4) {				//parallel
			if (ori[i]<minBound[i] || ori[i]>maxBound[i])
				return false;
		}
		else {
			if (dir[i] >= 0) {
				tMin[i] = (minBound[i] - ori[i]) / dir[i];
				tMax[i] = (maxBound[i] - ori[i]) / dir[i];
			}
			else {
				tMin[i] = (maxBound[i] - ori[i]) / dir[i];
				tMax[i] = (minBound[i] - ori[i]) / dir[i];
			}
		}
	}

	double tNear = fmax(tMin[2], fmax(tMin[0], tMin[1]));
	double tFar = fmin(tMax[2], fmin(tMax[0], tMax[1]));

	return tNear <= tFar;

}
