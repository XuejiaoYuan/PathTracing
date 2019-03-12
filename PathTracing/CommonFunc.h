#pragma once
#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"
#include "../glm/vec4.hpp"
#include "../glm/mat4x4.hpp"
using namespace glm;

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#define M_PI acos(double(-1))
#define SCENE01

typedef enum {
	TransparentType, DiffuseType, LightType, SpecularType
}ObjectType;
