/*
	
	THIS PROJECT IS HEAVILY BASED ON PETER SHIRLEY´S BOOKS: 
	RAY TRACING IN ONE WEEKEND AND RAY TRACING, THE NEXT WEEK
	I HAVE DONE SOME MODIFICATIONS TO IT TO INCLUDE DIRECT ILUMINATION
	AND SUPPORT FOR TRIANGLES WITH A POSSIBLE EXTENSION TO MODELS

*/

#include "stdafx.h"
#include "Vector3.h"
#include "Ray.h"
#include "Camera.h"
#include "Collidable.h"
#include "Sphere.h"
#include "CollidableList.h"
#include "Triangle.h"

#include "Lambertian.h"
#include "Metal.h"
#include "Phong.h"
#include "Dielectric.h"
#include "Diffuse_Light.h"


#include "Light.h"
#include "Texture.h"
#include "Constant_Texture.h"
#include "Checker_Texture.h"
#include "Image_Texture.h"
#include "Image.h"

#include <iostream>
#include <fstream>
#include <cfloat>
#include <time.h>
#include <random>

#include <math.h>

#define IMAGE_WIDTH 400
#define	IMAGE_HEIGHT 200
#define RAND01 ((double)rand() / (RAND_MAX))
#define MAXRAYDEPTH 8
#define AASAMPLES  400
#define NLIGHTS  1
//Change the number from SCENE1 to SCENE2 to see indirect and direct ilumination
#define SCENE1


Vector3 BackGroundColor(const Ray & r) {
	Vector3 D = r.D.normalized();
	float t = (D.y + 1.0f)*0.5; // range -1/1 to 0/1
	Vector3 BCKGTop = Vector3(1, 1, 1);
	Vector3 BCKGBot = Vector3(0.5, 0.7, 1);
	Vector3 FinalColor = BCKGTop*(1.0 - t) + BCKGBot*t;
	return Vector3(0);
	

}


Vector3 TraceRay( Ray& r, ICollidable * geometry,Light** lightlist,int depth) {
	HitInformation hitinfo;
	//We check whether there is an intersection adn capture the surface material and other hit information
	if (geometry->IntersectedBy(r, 0.01, FLT_MAX-1, hitinfo)) {
		Ray scatteredRay;
		Vector3 attenuation;
	
		//Then we check if the path should survive, and if so we check whether the material should scatter a ray
		if (depth < MAXRAYDEPTH ) {
			Vector3 emission = hitinfo.Surface_Mat->emitted(hitinfo.UV.x,hitinfo.UV.y,hitinfo.Point);
			//If there is an scatter Event, we recursively add attenuating by the albedo of each material.

			if ( hitinfo.Surface_Mat->scatterRay(r, hitinfo, attenuation, scatteredRay)) {
				
				if (scatteredRay.O.x == FLT_MAX) {
					return attenuation;
				}
				Vector3 Color = emission +Vector3::componentWiseMult(attenuation, TraceRay(scatteredRay, geometry, lightlist, depth + 1));
				return Color;
			}
			else {
				return emission;
			}

		}
		//If something of the above does not happen the path does not contribute and the tree branch ends here
		else {
			return Vector3(0);
		}
	}
	//If there is no intersection, we compute backgroundcolor.
	else {
		return BackGroundColor(r);
	}
}
int main()
{
	srand(time(NULL));


	Vector3 pixelMatrix[IMAGE_HEIGHT][IMAGE_WIDTH];
	Light* LightsList[1];
	LightsList[0] = new Light(Vector3(0, 2, -2), Vector3(0.5), Vector3(0.10, 0.03, 0));

	HitInformation hitINfo = HitInformation();

	
	
#ifdef SCENE1 //Area Light with Textures
	Image screamImg = Image(std::string("../Textures/scream.jpg").c_str());
	Image_Texture* screamTex = new Image_Texture(screamImg.tex_data, screamImg.width, screamImg.height);
	Checker_Texture* checker = new Checker_Texture(new Constant_Texture(Vector3(0)), new Constant_Texture(Vector3(1)));
	Diffuse_Light* EmissiveMat = new Diffuse_Light(checker);

	ICollidable* geometryList[7];
	ICollidable* geometry = new Collidable_List(geometryList, 7);

	Phong* phongmat = new Phong(checker, new Constant_Texture(Vector3(1)), 5, &LightsList[0], NLIGHTS, geometry);
	Phong* phongmat2 = new Phong(screamTex, new Constant_Texture(Vector3(1)), 5, &LightsList[0], NLIGHTS, geometry);
	//Big sphere representing the floor
	geometryList[0] = new Sphere(Vector3(0, -100.5, -1), 100, new Lambertian(checker));

	//different materials on spheres
	geometryList[1] = new Sphere(Vector3(1, 0, -1), 0.5, new Metal(Vector3(0.8, 0.6, 0.2), 0));
	geometryList[2] = new Sphere(Vector3(-1, 0, -1), 0.5, new Lambertian(new Constant_Texture(Vector3(1, 0, 0))));

	//outer glass ball and inner glass ball to represent thickness in glass
	geometryList[3] = new Sphere(Vector3(0, 0, -1), 0.5, new Dielectric(1.3f)); //glass;
	geometryList[4] = new Sphere(Vector3(0, 0, -1), -0.45, new Dielectric(1.3f)); //glass;



	Vector3 A = Vector3(-1, -0.5, -1.5); Vector3 uvA = Vector3(0);
	Vector3 B = Vector3(-1,1.5, -1.5); Vector3 uvB = Vector3(0, 1, 0);
	Vector3 C = Vector3(1, 1.5, -1.5);  Vector3 uvC = Vector3(1, 1, 0);
	Vector3 D = Vector3(1, -0.5, -1.5);  Vector3 uvD = Vector3(1, 0, 0);


	geometryList[5] = new Triangle(A, B, C, uvA, uvB, uvC, EmissiveMat);
	geometryList[6] = new Triangle(C, D, A, uvC, uvD, uvA, EmissiveMat);
#endif
#ifdef SCENE2
	Image screamImg = Image(std::string("../Textures/scream.jpg").c_str());
	Image_Texture* screamTex = new Image_Texture(screamImg.tex_data, screamImg.width, screamImg.height);
	Image Red_IMG = Image(std::string("../Textures/Simple_Red.jpg").c_str());
	Image_Texture* redText = new Image_Texture(Red_IMG.tex_data, Red_IMG.width, Red_IMG.height);
	
	Checker_Texture* checker = new Checker_Texture(new Constant_Texture(Vector3(0)), new Constant_Texture(Vector3(1)));

	Diffuse_Light* EmissiveMat = new Diffuse_Light(checker);

	ICollidable* geometryList[6];
	ICollidable* geometry = new Collidable_List(geometryList,6);

	Phong* phongmat = new Phong(checker, new Constant_Texture(Vector3(1)), 5, &LightsList[0], NLIGHTS, geometry);
	Phong* phongmat2 = new Phong(screamTex, new Constant_Texture(Vector3(1)), 5, &LightsList[0], NLIGHTS, geometry);
	Phong* phongmat3 = new Phong(new Constant_Texture(Vector3(0,0.3,0.8)), new Constant_Texture(Vector3(1)), 5, &LightsList[0], NLIGHTS, geometry);
	Phong* phongmat4 = new Phong(redText, new Constant_Texture(Vector3(1)), 5, &LightsList[0], NLIGHTS, geometry);

	//Big sphere representing the floor
	geometryList[0] = new Sphere(Vector3(0, -100.5, -1), 100, phongmat3);

	//different materials on spheres
	geometryList[1] = new Sphere(Vector3(1, 0, -1), 0.5, new Metal(Vector3(0.8, 0.6, 0.2), 0));
	geometryList[2] = new Sphere(Vector3(-1, 0, -1), 0.5,phongmat4);
	geometryList[3] = new Sphere(Vector3(0, -0.25, -1), 0.25, new Dielectric(1.3f)); //glass;


	Vector3 A = Vector3(-1, -0.5, -2); Vector3 uvA = Vector3(0);
	Vector3 B = Vector3(-1, 1.5, -2); Vector3 uvB = Vector3(0, 1, 0);
	Vector3 C = Vector3(1, 1.5, -1.5);  Vector3 uvC = Vector3(1, 1, 0);
	Vector3 D = Vector3(1, -0.5, -1.5);  Vector3 uvD = Vector3(1, 0, 0);


	geometryList[4] = new Triangle(A, B, C, uvA, uvB, uvC, new Metal(Vector3(1),0.8));
	geometryList[5] = new Triangle(C, D, A, uvC, uvD, uvA, new Metal(Vector3(1),0));
#endif // SCENE1


	
	
	//Camera with a FOVY of 90 looking at -20z;
	Camera Cam = Camera(Vector3(0, 0, 0), Vector3(0, 0, -20), Vector3(0, 1, 0), 90 , float(IMAGE_WIDTH) / float(IMAGE_HEIGHT));


	for (int row = IMAGE_HEIGHT - 1; row >= 0; row--)
	{
		for (int col = 0; col < IMAGE_WIDTH; col++)
		{

			Vector3 Color = Vector3(0);
			//We compute the MC integration over the pixels to get AA
			//Statistically we have the probability of a single ray to hit the same
			// spot in the surface and thus we are solving the Light equation.
			for (int sample = 0; sample < AASAMPLES; sample++)
			{
				float v = (float)((row + RAND01) / IMAGE_HEIGHT);
				float u = (float)((col + RAND01) / IMAGE_WIDTH);
				Ray r = Cam.getRay(u, v);//  Ray(COP, PP.getPointInPlane(u, v));

				Color += TraceRay(r, geometry,LightsList, 0);
			}
			Color /= AASAMPLES;

			pixelMatrix[row][col] = Color;
			//std::cout << row << " " << col<<std::endl	;
			
		}
		std::cout << 1.0*row / IMAGE_WIDTH << std::endl;
	}


	//Lets create a simple ppm
	std::string file = "../Results/Result";
	std::string num = std::to_string(0);
	std::string format = ".ppm";
	string filename = file + num + format;
	std::ofstream outstream(filename.c_str());
	outstream.clear();
	outstream << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";
	for (int row = IMAGE_HEIGHT - 1; row >= 0; row--)
	{
		for (int col = 0; col < IMAGE_WIDTH; col++)
		{
			//Gamma correction
			Vector3 Color = pixelMatrix[row][col];
			int r = sqrt(Color.x)*255.99;
			int g = sqrt(Color.y)*255.99;
			int b = sqrt(Color.z)*255.99;
			outstream << r << " " << g << " " << b << "\n";
		}
	}
	outstream.close();

	return 0;
}

