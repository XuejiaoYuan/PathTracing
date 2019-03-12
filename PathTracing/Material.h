#pragma once
#include "CommonFunc.h"

class Material
{
public:
	Material() :useMtl(""), Ka(vec3(0)), Kd(vec3(0)),
		Ks(vec3(0)), Tf(vec3(0)), Ni(0), Ns(0), illum(-1), albedo(0.4) {}

	Material(const string& _useMtl):useMtl(_useMtl),Ka(vec3(0)),Kd(vec3(0)),
		Ks(vec3(0)),Tf(vec3(0)),Ni(0),Ns(0),illum(-1),albedo(0.4) {}

	string useMtl;
	vec3 Ka;		//ambient color
	vec3 Kd;		//diffuse color
	vec3 Ks;		//specular color
	vec3 Tf;		//filter transmittance
	double Ni;		//index of refraction
	double Ns;		//weight for Ks
	int illum;		//illumination models
	double albedo;

private:

};

