#include "RayTracer.h"
#include <omp.h>
using namespace std;

void RayTracer::rayTracing(ObjList& objList, const vector<Light*>&lightList)
{
	frameBuffer.clear();
	frameBuffer.resize(camera.height, vector<vec3>(camera.width));
	vector<vector<vec3>>::iterator iter = frameBuffer.begin();
	int h = 0;
	double scale = tan(camera.fov / 2 * M_PI / 180);
	double imageAspectRatio = camera.width / (double)camera.height;
	
	vec3 ori;
	camera.multMatrix(vec4(0, 0, 0, 1), ori);


#pragma omp parallel for
	for (int j = camera.height - 1; j >= 0; j--) {
		for (int i = 0; i < camera.width; i++) {
			vec3 color(0);
			for (int w = 0; w < mcN; w++) {
				double r1 = rand(generator);
				double r2 = rand(generator);
				double x = (2 * (i + r1) / (double)camera.width - 1)*imageAspectRatio*scale;
				double y = (1 - 2 * (j + r2) / (double)camera.height)*scale;
				vec3 dir;
				camera.multMatrix(vec4(x, y, -1, 0), dir);
				dir = normalize(dir);
				vec3 newColor = castRay(Ray(ori, dir), objList, lightList, 0);
				color += newColor;

			}
			frameBuffer[camera.height - 1 - j][i] = color / vec3(mcN);
		}
		cout << j << endl;
	}

}

vec3 RayTracer::castRay(Ray & ray, ObjList & objList, const vector<Light*>& lightList, int depth)
{
	if (depth > maxDepth)
		return vec3(0, 0, 0);

	//Object* hitObjPtr = NULL;
	//Mesh* hitMeshPtr = NULL;
	//double tNear = INT_MAX;
	HitPointInfo hitPointInfo;
	int Index;
	vec3 hitColor(0);
	vec3 ambient(0.05);

	if (objList.calcObjListIntersection(ray, bias, hitPointInfo)) {
		vec3 hitPoint = hitPointInfo.hitPoint;
		vec3 hitN = hitPointInfo.hitN;

		switch (hitPointInfo.objType)
		{
		case LightType: {
			Index = hitPointInfo.lightIndex;
			hitColor = vec3(lightList[Index]->intensity)*lightList[Index]->color;

			break;
		}
		case SpecularType: {
			vec3 specularColor(0), diffuseColor(0);

#ifdef SCENE01
			Ray reflectRay(hitPoint);
			ray.reflect(hitN, reflectRay.dir);
			reflectRay.ori += reflectRay.dir + vec3(bias);
			specularColor = castRay(reflectRay, objList, lightList, depth + 1);

#endif // SCENE01

			vec3 directLight(0);
			for (auto&light : lightList) {

				for (int i = 0; i < mcN; i++) {
					float r1 = 2 * rand(generator) - 1;
					float r2 = rand(generator);
					Ray shadowRay(hitPoint);
					vec3 lightIntensity = light->calcDirectLightIntensity(shadowRay, hitN, bias, vec2(r1, r2), objList);

					//diffuseColor += lightIntensity*vec3(hitPointInfo.mtl.albedo*fmax(0.0f, dot(shadowRay.dir, hitN)));
					diffuseColor += lightIntensity*vec3(fmax(0.0f, dot(shadowRay.dir, hitN)));

					if (dot(hitN, shadowRay.dir) > bias) {
						//compute specular
						vec3 h = normalize(shadowRay.dir - ray.dir);
						double res = dot(hitN, h);
						if (res < bias)
							continue;
						directLight += lightIntensity*vec3(pow(res, hitPointInfo.mtl.Ns));
					}
				}
				diffuseColor /= vec3(mcN);
				directLight /= vec3(mcN);
			

				//compute diffuse
				//Ray shadowRay(hitPoint);
				
				//vec3 lightIntensity = light->calcDirectLightIntensity(shadowRay, hitN, bias, objList);
				//diffuseColor += lightIntensity*vec3(hitPointInfo.mtl.albedo*fmax(0.0f, dot(shadowRay.dir, hitN)));

				//if (dot(hitN, shadowRay.dir) > bias) {
				//	//compute specular
				//	vec3 h = normalize(shadowRay.dir - ray.dir);
				//	double res = dot(hitN, h);
				//	if (res < bias)
				//		continue;
				//	specularColor += lightIntensity*vec3(pow(res, hitPointInfo.mtl.Ns));
				//}
			}
			hitColor += hitPointInfo.mtl.Kd*diffuseColor + hitPointInfo.mtl.Ks*(specularColor + directLight) + ambient*hitPointInfo.mtl.Kd;
			break;
		}
		case DiffuseType: {
			//compute direct diffuse
			vec3 directLightContrib(0);
			for (auto&light : lightList) {
				//vec3 shadowRayOri = hitPoint + vec3(bias)*hitN;
				vec3 hitLightDir;
				Ray shadowRay(hitPoint);
				float r1 = 2 * rand(generator) - 1;
				float r2 = rand(generator);
				vec3 lightIntensity = light->calcDirectLightIntensity(shadowRay, hitN, bias, vec2(r1, r2), objList);

				//vec3 lightIntensity = light->calcDirectLightIntensity(shadowRay, hitN, bias, objList);
				directLightContrib += lightIntensity*vec3(fmax(0.0f, dot(shadowRay.dir, hitN))); 
			}

			//compute indirect diffuse
			vec3 indirectLightContrib(0);
			vec3 pdf(1 / (2 * M_PI));
			vec3 Nt, Nb;
			createCoordsSystem(hitN, Nt, Nb);
			for (int i = 0; i < mcN; i++) {
				double r1 = rand(generator);
				double r2 = rand(generator);
				vec3 localSample = uniformSampleHemisphere(r1, r2);
				vec3 worldSample;
				for (int i = 0; i < 3; i++)
					worldSample[i] = localSample[0] * Nb[i] + localSample[1] * hitN[i] + localSample[2] * Nt[i];
				indirectLightContrib += vec3(r1)/pdf*castRay(Ray(hitPoint + worldSample*vec3(bias),worldSample),
					objList, lightList, depth + 1);
			}
			indirectLightContrib /= vec3(mcN);

			hitColor = (vec3(2)*indirectLightContrib + directLightContrib / vec3(M_PI))*hitPointInfo.mtl.Kd*vec3(hitPointInfo.mtl.albedo)
				+ ambient*hitPointInfo.mtl.Kd;
			break;
		}
		case TransparentType: {
			double kr;
			vec3 refractDir(0), reflectDir(0);
			vec3 refractColor(0), reflectColor(0);
			ray.fresnel(hitN, hitPointInfo.mtl.Ni, kr, refractDir);
			//inside means ori is in the object
			bool inside = dot(hitN, ray.dir) > 0;
			vec3 move = vec3(bias)*hitN;
			double res = dot(ray.dir, refractDir);
			double ndotr = dot(hitN, refractDir);

			//compute refraction
			if (kr < 1) {
				Ray refractRay(inside ? hitPoint + move : hitPoint - move, refractDir, inside ? OUTSIDERAY : INSIDERAY);
				refractColor = castRay(refractRay, objList, lightList, depth + 1);
			}

			//compute reflection
			ray.reflect(hitN, reflectDir);
			Ray reflectRay(inside ? hitPoint - move : hitPoint + move, reflectDir, inside ? INSIDERAY : OUTSIDERAY);
			reflectColor = castRay(reflectRay, objList, lightList, depth + 1);

			//add refraction color and reflection color up
			hitColor = refractColor*vec3(1 - kr) + reflectColor*vec3(kr) + hitPointInfo.mtl.Kd*ambient;

			break;
		}
		default:
			break;
		}
	}

	return hitColor;
}

void RayTracer::createCoordsSystem(const vec3 & N, vec3 & Nt, vec3 & Nb)
{
	if (abs(N.x) > abs(N.y))
		Nt = vec3(N.z, 0, -N.x) / vec3(sqrt(N.x*N.x + N.z*N.z));
	else
		Nt = vec3(0, -N.z, N.y) / vec3(sqrt(N.y*N.y + N.z*N.z));
	Nb = cross(N, Nt);
}

vec3 RayTracer::uniformSampleHemisphere(const double & r1, const double & r2)
{
	double sinTheta = sqrt(1 - r1*r1);
	double phi = 2 * M_PI*r2;
	double x = sinTheta*cos(phi);
	double z = sinTheta*sin(phi);

	return vec3(x, r1, z);
}

