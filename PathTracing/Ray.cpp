#include "Ray.h"

void Ray::fresnel(const vec3&hitN, const double & Ni, double & kr, vec3 & refractDir)
{
	vec3 n = hitN;
	double cosi = fmax(-1, fmin(dot(dir, n), 1));
	double etai = 1, etat = Ni;
	if (cosi > 0) {
		swap(etai, etat);
		n = -n;
	}
	else
		cosi = -cosi;
	double eta = etai / etat;
	double sint = eta * sqrt(fmax(1 - cosi*cosi, 0.0f));
	if (sint >= 1)
		kr = 1;
	else {
		double cost = sqrt(fmax(1 - sint*sint, 0.0f));
		cosi = abs(cosi);
		double Rs = ((etat*cosi) - (etai*cost)) / ((etat*cosi) + (etai*cost));
		double Rp = ((etai*cosi) - (etat*cost)) / ((etai*cosi) + (etat*cost));
		kr = (Rs*Rs + Rp*Rp) / 2;
		refractDir = normalize(vec3(eta)*dir + vec3(eta*cosi - cost)*n);
	}

}

void Ray::reflect(const vec3 & hitN, vec3 & reflectDir, bool inverse)
{
	vec3 inverseDir(dir);
	if (inverse)
		inverseDir = -dir;
	double k = 2 * dot(inverseDir, hitN);
	reflectDir = normalize(inverseDir - vec3(k)*hitN);

}
