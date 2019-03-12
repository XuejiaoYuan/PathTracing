#include "ObjList.h"

bool ObjList::ObjectLoader(const string& _path, const string & _fileName)
{
	fstream inFile(_path + _fileName);
	if (inFile.fail()) {
		cout << "Can't open the file! Please check the file name!" << endl;
		return false;
	}

	string s, type, mtlName, useMtl;
	string indexStr;
	stringstream ss;

	vector<vec3> v, vn;
	vector<vec2> vt;
	vec3 tmpV;
	vec2 tmpVt;

	while (getline(inFile, s)) {
		ss.clear();
		ss.str(s);
		ss >> type;

		if (type == "mtllib") {
			ss >> mtlName;
			MtlLoader(_path + mtlName);
		}
		else if (type == "g") {
			ss >> type;
			if (type != "default") {
				objs.push_back(new Object(type));
			}
		}
		else if (type == "v") {
			ss >> tmpV.x >> tmpV.y >> tmpV.z;
			v.push_back(tmpV);
		}
		else if (type == "vt") {
			ss >> tmpVt.x >> tmpVt.y;
			vt.push_back(tmpV);
		}
		else if (type == "vn") {
			ss >> tmpV.x >> tmpV.y >> tmpV.z;
			vn.push_back(tmpV);
		}
		else if (type == "usemtl") {
			ss >> useMtl;
		}
		else if (type == "f") {
			Mesh tmpMesh;
			while (ss >> indexStr) {
				tmpMesh.setMtl(mtlMap[useMtl]);
				int pos = indexStr.find('/');
				tmpMesh.addV(v[stoi(indexStr.substr(0, pos)) - 1]);
				indexStr = indexStr.substr(pos + 1);
				pos = indexStr.find('/');
				tmpMesh.addVt(vt[stoi(indexStr.substr(0, pos)) - 1]);
				indexStr = indexStr.substr(pos + 1);
				tmpMesh.addVn(vn[stoi(indexStr) - 1]);
			}
			tmpMesh.calcMeshN();
			tmpMesh.calcBoudingBox();
			objs[objs.size() - 1]->addMesh(tmpMesh);
		}
	}

	for (int i = 0; i < objs.size(); i++) {
		objs[i]->calcBoudingBox();
		objs[i]->setObjectType();
	}

	inFile.close();
	return true;
}


Object* ObjList::getObject(const string & name)
{
	int i;
	for (i = 0; i < objs.size(); i++) {
		if (objs[i]->name == name)
			break;
	}
	return objs[i];
}


bool ObjList::calcObjListIntersection(const Ray & ray, const double & bias, HitPointInfo & hitPointInfo)
{
	double tNear = INT_MAX;
	HitPointInfo tmpHitPointInfo;
	
	int index;
	for (int i = 0; i < objs.size(); i++) {
		if (objs[i]->calcObjectIntersection(ray, bias,tmpHitPointInfo)) {
			if (tNear > tmpHitPointInfo.tNear) {
				tNear = tmpHitPointInfo.tNear;
				index = i;
				hitPointInfo = tmpHitPointInfo;
			}
		}
	}
	if (tNear == INT_MAX)
		return false;
	else {
		hitPointInfo.objType = objs[index]->objType;
		hitPointInfo.lightIndex = objs[index]->lightIndex;
		hitPointInfo.name = objs[index]->name;
		return true;
	}
}

void ObjList::eraseObject(const string & name)
{
	Object* tmp = NULL;
	for (int i = 0; i < objs.size(); i++) {
		if (objs[i]->name == name) {
			tmp = objs[i];
			objs.erase(objs.begin() + i);
			break;
		}
	}
	delete tmp;
	tmp = NULL;
	
}

bool ObjList::MtlLoader(const string & _mtlName)
{
	fstream inFile(_mtlName);
	
	if (inFile.fail()) {
		cout << "Can't opent the material file!" << endl;
		return false;
	}

	string s, type, newmtl;
	stringstream ss;

	while (getline(inFile, s)) {
		ss.clear();
		ss.str(s);
		ss >> type;
		if (type == "newmtl") {
			ss >> newmtl;
			mtlMap[newmtl] = Material(newmtl);
		}
		else if (type == "illum") {
			ss >> mtlMap[newmtl].illum;
		}
		else if (type == "Kd") {
			ss >> mtlMap[newmtl].Kd.x >> mtlMap[newmtl].Kd.y >> mtlMap[newmtl].Kd.z;
		}
		else if (type == "Ka") {
			ss >> mtlMap[newmtl].Ka.x >> mtlMap[newmtl].Ka.y >> mtlMap[newmtl].Ka.z;
		}
		else if (type == "Tf") {
			ss >> mtlMap[newmtl].Tf.x >> mtlMap[newmtl].Tf.y >> mtlMap[newmtl].Tf.z;
		}
		else if (type == "Ni") {
			ss >> mtlMap[newmtl].Ni;
		}
		else if (type == "Ks") {
			ss >> mtlMap[newmtl].Ks.x >> mtlMap[newmtl].Ks.y >> mtlMap[newmtl].Ks.z;
		}
		else if (type == "Ns") {
			ss >> mtlMap[newmtl].Ns;
		}
	}

	inFile.close();
	return true;
}
