#pragma once
#include "Camera.h"
#include "ObjList.h"
#include "Light.h"
#include "CommonFunc.h"
#include <cmath>
#include <random>
using namespace std;

class RayTracer
{
public:
	RayTracer(int _maxDepth = 10, double _bias = 1e-4, int _mcN = 8) :maxDepth(_maxDepth), bias(_bias), mcN(_mcN) {
	}
	void setCamera(const int _width, const int _height, const vec3&_cameraPos, 
		const vec3&_lookAt, const vec3&_tmp = vec3(0, 1, 0), const double _fov = 90) 
	{
		camera.setCameraParam(_width, _height, _cameraPos, _lookAt, _tmp, _fov);
	}
	void rayTracing(ObjList&objList, const vector<Light*>&lightList);
	vector<vector<vec3>>& getFrameBuffer() { return frameBuffer; }

private:
	int maxDepth;
	double bias;
	int mcN;
	Camera camera;
	vector<vector<vec3>> frameBuffer;
	default_random_engine generator;
	uniform_real_distribution<double> rand;

	vec3 castRay(Ray&ray, ObjList& objList, const vector<Light*>& lightList, int depth = 0);
	void createCoordsSystem(const vec3&N, vec3&Nt, vec3& Nb);
	vec3 uniformSampleHemisphere(const double&r1, const double&r2);
	
};

