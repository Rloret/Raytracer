#pragma once
#pragma once


#include "Collidable.h"
#include "Material.h"
#include <iostream>
class Triangle : public ICollidable
{
public:
	Triangle(Vector3 A, Vector3 B, Vector3 C) {
		this->A = A;
		this->B = B;
		this->C = C;
	}
	Triangle(Vector3 A, Vector3 B, Vector3 C,Vector3 UVA, Vector3 UVB, Vector3 UVC, Material* surfaceMaterial) {
		this->A = A;
		this->B = B;
		this->C = C;

		this->uvA = UVA;
		this->uvB = UVB;
		this->uvC = UVC;

		Vector3 BA = A - B;
		Vector3 BC = C - B;
		Vector3 BCxBA = BA^BC;


		N = BCxBA.normalized();

		this->triangleMaterial = surfaceMaterial;

	}
	bool IntersectedBy(const Ray& r, float min, float max, HitInformation& hitInfo) override;
	void GetBarycentric(Vector3 & p, Vector3 & A, Vector3 & B, Vector3 & C, float & u, float & v, float & w);
	float GetTriangleArea();
private:
	Vector3 A;
	Vector3 B;
	Vector3 C;
	Vector3 uvA;
	Vector3 uvB;
	Vector3 uvC;
	Vector3 N;
	float triangleArea;
	Material* triangleMaterial;
};



inline bool Triangle::IntersectedBy(const Ray & r, float min, float max, HitInformation& hitInfo)
{
	


	//check Ray interesects with plane
	//First we check whether the point lies in the plane defined by the points
	// We know that a plane can be defined as a set of points P, that create a segment which any known point in the plane
	// and that the dot product of that segment and the normal vector gives 0(they are perpendicular)
	// (P-p)·N =0
	// We also know that a ray can be expresed as the set of points that are defined in segment that starts at an origin
	// and extends to infinity in a direction
	// P = O+a*D
	// In order to find the point that lies in the plane first we need to know whether the ray crosses the plane(its not parallel to it)
	// If we substitute we arrive at the following equation
	// a = ((p-O)·N)/(D·N);

	
	float denominator = r.D*N;
	float enumerator = (A - r.O)*N;
	float a = 0;
	if (denominator == 0) {
		return false;

	}

	a = enumerator / denominator;

	if (a >= 0) {
		//std::cout << enumerator << " " << denominator << std::endl;
		Vector3 P = r.O + r.D*a; // find the point in the plane.


							 //Now we need to calculate whether the point lies within the triangle.
							 //For that means we can compute the area of each of the 3 sub-triangles
							 //each new triangle is created by connecting 2 vertices of the main triangle with the new point.

		Triangle t1 = Triangle(A, B, P);
		Triangle t2 = Triangle(A, C, P);
		Triangle t3 = Triangle(B, C, P);

		float TriangleArea = GetTriangleArea();

		float u = t1.GetTriangleArea();
		float v = t2.GetTriangleArea();
		float w = t3.GetTriangleArea();

		//std::cout << (u + v + w) << std::endl;
		// If the sum of each of the areas is equal to One then inside if not, outside
		if (u + v + w == triangleArea) {
			hitInfo.t = a;
			hitInfo.Point =P;
			hitInfo.Normal = N;
			hitInfo.Surface_Mat = this->triangleMaterial;
			float w;
			GetBarycentric(hitInfo.Point, A, B, C, u, v, w);
			Vector3 UV = uvA * u + uvB * v + uvC * w;
			hitInfo.UV = UV;
			return true;
		}
	}
	return false;




}


void Triangle::GetBarycentric(Vector3 & p, Vector3 & A, Vector3 & B, Vector3 & C, float & u, float & v, float & w)
{
	Vector3 v0 = B - A, v1 = C - A, v2 = p - A;
	float d00 = v0*(v0);
	float d01 = v0*(v1);
	float d11 = v1*(v1);
	float d20 = v2*(v0);
	float d21 = v2*(v1);
	float denom = d00 * d11 - d01 * d01;
	v = (d11 * d20 - d01 * d21) / denom;
	w = (d00 * d21 - d01 * d20) / denom;
	u = 1.0f - v - w;
}


float Triangle::GetTriangleArea()
{

	Vector3 AB = B - A;
	Vector3 AC = C - A;

	Vector3 ABxAC = AB ^AC;
	float module = ABxAC.module();
	triangleArea = module == 0 ? 0 : module *0.5f;
	return triangleArea;

}