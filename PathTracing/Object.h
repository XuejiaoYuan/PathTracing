#pragma once
#include "Mesh.h"
#include "Material.h"
#include "HitPointInfo.h"


class Object
{
public:
	Object() {}
	Object(const string& _name) :name(_name),lightIndex(-1) {}
	~Object();
	void addMesh(const Mesh& mesh) { meshList.push_back(mesh); }
	virtual void calcBoudingBox();			//calculate object's bouding box
	virtual bool calcObjectIntersection(const Ray&ray, const double& bias, HitPointInfo&hitPointInfo);
	void setObjectType();

	ObjectType objType;
	int lightIndex;
	string name;
	AABB aabb;

private:
	vector<Mesh> meshList;
	
};

