#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include "Object.h"
using namespace std;

class ObjList
{
public:
	ObjList() {}
	bool ObjectLoader(const string& _path, const string& _fileName);		//read the .obj file
	Object* getObject(const string& name);
	bool calcObjListIntersection(const Ray&ray, const double&bias, HitPointInfo&hitPointInfo);
	void eraseObject(const string&name);
	vector<Object*> objs;		//save all the objects in the scene
	map<string, Material> mtlMap;

private:

	bool MtlLoader(const string& _mtlName);	//read the .mtl file

};

