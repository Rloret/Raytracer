#pragma once
#include "Vector3.h"
#include "Ray.h"
#include <math.h>
#include <iostream>



class Camera
{
public:
	Camera(Vector3 LookFrom, Vector3 Lookat, Vector3 Up,float FOVY, float AspectRatio) {
		Vector3 u, v, w;
		
		float theta = FOVY * M_PI / 180.0;
		float half_height = tan(theta / 2.0);
		float half_width = AspectRatio * half_height;
		
		COP = LookFrom;
		w = (LookFrom-Lookat ).normalized();
		u =  (Up^w).normalized();
		v = (w^u);

		//lowerLCorner = Vector3(-half_width, -half_height, -1);
		lowerLCorner = COP -u*half_width -  v*half_height - w;
		Horizontal =  u*2.0f*half_width;
		Vertical = v* 2.0f * half_height;
		Vector3 uppercorner = lowerLCorner + Horizontal + Vertical;
		
		std::cout << "COP" << COP.ToString() << std::endl;


	}
	Vector3 getPointInPLane(float u, float v) {
		return lowerLCorner + Horizontal * u + Vertical * v;
	}

	Ray getRay(float u, float v) {
		return Ray(COP, getPointInPLane(u, v));
	}

	Vector3 COP;
private:


	Vector3 Horizontal;
	Vector3 Vertical;
	Vector3 lowerLCorner;
	


};

