#include "RayTracer.h"
#include "ImageSaver.h"
#include "Sphere.h"

int main(int argc, char** argv)
{
	if (argc != 8) {
		cout << "Command Error! Usage: [Path] [objFileName] [savePath] [saveName] [maxDepth] [sampleNumber] [bias]" << endl;
		return -1;
	}

	ObjList objList;
	string path = string(argv[1]);
	string fileName = string(argv[2]);
	objList.ObjectLoader(path, fileName);
	
	int maxDepth = atoi(argv[5]);
	int mcN = atoi(argv[6]);
	double bias = atof(argv[7]);
	RayTracer rayTracer(maxDepth, bias, mcN);


#ifdef SCENE01
	Sphere* sphere1 = new Sphere("pSphere1");
	sphere1->setParameters(vec3(-2.88, 2, -2.5), 2, objList.mtlMap["sphere_mirror"], SpecularType, 1);

	Sphere* sphere2 = new Sphere("pSphere2");
	sphere2->setParameters(vec3(2.88, 2, 2.5), 2, objList.mtlMap["sphere_transparent"], TransparentType, 1);

	objList.eraseObject("pSphere1");
	objList.eraseObject("pSphere2");
	
	objList.objs.push_back(sphere1);
	objList.objs.push_back(sphere2);

	vector<Light*> lightList;
	Light* light1 = new Light(objList.getObject("pCube2"));
	light1->setLightParam(vec3(1, 1, 1), 1, lightList.size());
	lightList.push_back(light1);

	rayTracer.setCamera(800, 700, vec3(0, 5, 11), vec3(0, 5, 0));


#else
	Sphere* sphere1 = new Sphere("pSphere1");
	sphere1->setParameters(vec3(-3.4, 6, 3), 0.08, objList.mtlMap["lambert2SG"], LightType);

	Sphere* sphere2 = new Sphere("pSphere2");
	sphere2->setParameters(vec3(0.1, 6, 3), 0.33, objList.mtlMap["lambert3SG"], LightType);
	
	Sphere* sphere3 = new Sphere("pSphere3");
	sphere3->setParameters(vec3(3.7, 6, 3), 0.50, objList.mtlMap["lambert4SG"], LightType);

	Sphere* sphere4 = new Sphere("pSphere4");
	sphere4->setParameters(vec3(7.3, 6, 3), 1.00, objList.mtlMap["lambert5SG"], LightType);
	
	objList.eraseObject("pSphere1");
	objList.eraseObject("pSphere2");
	objList.eraseObject("pSphere3");
	objList.eraseObject("pSphere4");

	objList.objs.push_back(sphere1);
	objList.objs.push_back(sphere2);
	objList.objs.push_back(sphere3);
	objList.objs.push_back(sphere4);

	vector<Light*> lightList;
	SphereLight* sLight1 = new SphereLight(sphere1);
	sLight1->setLightParam(vec3(1, 1, 1), 1, lightList.size());
	lightList.push_back(sLight1);

	SphereLight* sLight2 = new SphereLight(sphere2);
	sLight2->setLightParam(vec3(1, 1, 1),1,  lightList.size());
	lightList.push_back(sLight2);

	SphereLight* sLight3 = new SphereLight(sphere3);
	sLight3->setLightParam(vec3(1, 1, 1), 1, lightList.size());
	lightList.push_back(sLight3);

	SphereLight* sLight4 = new SphereLight(sphere4);
	sLight4->setLightParam(vec3(1, 1, 1), 1, lightList.size());
	lightList.push_back(sLight4);
	
	rayTracer.setCamera(600, 480, vec3(0, 7, 20), vec3(0, 4, 0));


#endif // SCENE01

	rayTracer.rayTracing(objList, lightList);

	ImageSaver imgSave;
	//string savePath = "../res/";
	imgSave.save(string(argv[3]) + string(argv[4]) + "_maxDepth" + to_string(maxDepth) + "_mcN" + to_string(mcN) + ".bmp",
		rayTracer.getFrameBuffer());

	return 0;
}