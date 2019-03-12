#pragma once
#include "AABB.h"
#include "Material.h"
//#include <vector>
//#include <GL\glm\vec2.hpp>
//#include <GL\glm\mat4x4.hpp>
//#include <GL\glm\glm.hpp>
//using namespace std;
//using namespace glm;
#include "HitPointInfo.h"

class Mesh 
{
public:
	Mesh() {}
	void addV(const vec3& _v) { v.push_back(_v); }
	void addVt(const vec2& _vt) { vt.push_back(_vt); }
	void addVn(const vec3& _vn) { vn.push_back(_vn); }
	void calcMeshN();
	void setMtl(const Material&_mtl) { mtl = _mtl;}
	void calcBoudingBox() { aabb.calcBounds(v, aabb); }		//calculate mesh's bouding box
	bool calcMeshIntersection(const Ray&ray, const double&bias, HitPointInfo&hitPointInfo);
	vec3 getMeshNormal() { return sN; }
	AABB aabb;
	Material mtl;		//surface material

private:

	vector<vec3> v;		//vertex
	vector<vec2> vt;	//texture vertex
	vector<vec3> vn;	//vertex normal
	vec3 sN;			//surface normal

};
