#include "Camera.h"

void Camera::multMatrix(const vec4 & src, vec3 & res)
{
	vec4 tmp(0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			tmp[i] += src[j] * cameraToWorld[j][i];
	}

	if (tmp[3] != 0)
		for (int i = 0; i < 4; i++)
			tmp[i] /= tmp[3];
	res = vec3(tmp[0], tmp[1], tmp[2]);
}

void Camera::calcCameraToWorld()
{
	vec3 forward = normalize(cameraPos - lookAt);
	vec3 right = normalize(cross(normalize(tmp), forward));
	vec3 up = normalize(cross(forward, right));

	vector<vec3> coords(4);
	coords[0] = right;
	coords[1] = up;
	coords[2] = forward;
	coords[3] = cameraPos;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++)
			cameraToWorld[i][j] = coords[i][j];
	}
	cameraToWorld[3][3] = 1;
}
