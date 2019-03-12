#pragma once
#include "CommonFunc.h"

class Camera
{
public:
	Camera() {}
	void setCameraParam(const int _width, const int _height, const vec3&_cameraPos,
		const vec3&_lookAt, const vec3&_tmp = vec3(0, 1, 0), const double _fov = 90)
	{
		width = _width;
		height = _height;
		cameraPos = _cameraPos;
		lookAt = _lookAt;
		fov = _fov;
		tmp = _tmp;
		calcCameraToWorld();
	}
	void multMatrix(const vec4& src, vec3& res);

	int width;
	int height;
	vec3 cameraPos;
	vec3 lookAt;
	vec3 tmp;
	double fov;
	mat4x4 cameraToWorld;

private:
	void calcCameraToWorld();
};

