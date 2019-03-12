#include "Mesh.h"

void Mesh::calcMeshN()
{
	int i;
	for (i = 0; i < vn.size() - 1; i++)
		if (vn[i] != vn[i + 1])
			break;
	if (i == vn.size() - 1)
		sN = vn[0];
	else
		sN = normalize(cross(v[1] - v[0], v[2] - v[1]));
}

bool Mesh::calcMeshIntersection(const Ray & ray, const double & bias, HitPointInfo & hitPointInfo)
{
	vec3 ori = ray.ori;
	vec3 dir = ray.dir;
	if (aabb.calcIntersection(ray)) {
		vec3 v0v1 = v[1] - v[0];
		vec3 v0v2 = v[2] - v[0];
		vec3 pvec = cross(dir, v0v2);
		float det = dot(v0v1, pvec);

		// ray and triangle are parallel if det is close to 0
		if (fabs(det) < bias) return false;

		float invDet = 1 / det;

		vec3 tvec = ori - v[0];
		double ut = dot(tvec, pvec)*invDet;
		//if (ut < 0 || ut > 1) return false;

		vec3 qvec = cross(tvec, v0v1);
		double vt = dot(dir, qvec)*invDet;
		//if (vt < 0 || ut + vt > 1) return false;
		
		hitPointInfo.tNear = dot(v0v2, qvec) * invDet;
		hitPointInfo.hitPoint = ori + vec3(hitPointInfo.tNear)*dir;
		hitPointInfo.mtl = this->mtl;
		hitPointInfo.hitN = this->sN;

		return (hitPointInfo.tNear > 0) ? true : false;

	}
	else
		return false;
}
