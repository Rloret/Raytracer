#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
using namespace std;
class Vector3 {



public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float X, float Y, float Z);
	Vector3(float V);
	Vector3(int V);
	Vector3(double V);
	~Vector3();

#pragma region Operators

	/* brief: Vector3 multiplication componentwise and modification of *this to hold the result
	* p: second Vector3 operator. First operator is *this
	*/
	void operator*=(const Vector3 &p);

	/* brief: Dot product of two Vector3
	* p: second Vector3 operator. First operator is *this
	* returns the scalar result of the dot product
	*/
	double operator* (const Vector3 &p) const;
	/* brief: product of *this by a scalar
	* p: scalar. First operator is *this
	*/
	void operator*=(const float p);


	/* brief: Product of *this by a scalar
	* p: scalar. First operator is *this
	*/
	Vector3 operator* (const float p) const;


	/* brief: divides *this by a scalar
	params: the second operator is p which is the scalar by which *this, the first operator is divided
	returns: Vector3 result of the division
	*/

	Vector3 operator/ (const float p) const;
	void operator/=(const float p);


	/* brief: Cross product of two Vector3 that modifies *this to hold the result
	* p: second Vector3 operator. First operator is *this
	*/
	void operator^=(const Vector3 &p);


	/* brief: Cross product of two Vector3
	* p: second Vector3 operator. First operator is *this
	* returns the Vector3 result of the cross product
	*/
	Vector3 operator^ (const Vector3 &p) const;


	/* brief: Sum two Vector3 and accumulation into *this
	* p: second Vector3 operator. First operator is *this
	*/
	void operator+=(const Vector3 &p);


	/* brief: Substraction of two Vector3 and accumulation into *this
	* p: second Vector3 operator. First operator is *this
	*/
	void operator-=(const Vector3 &p);
	bool operator==(const Vector3 &p)const;
	bool operator!=(const Vector3 &p)const;


	/* brief: Negates Vector3 *this
	*/
	void operator-();

	Vector3 operator- (const Vector3 &p) const;
	Vector3 operator+ (const Vector3 &p) const;

#pragma endregion Operators

	void normalize();
	Vector3 normalized() const;
	Vector3 Clamp(float min, float max)const;
	double module();
	double distance(const Vector3 &p);
	double distance2(const Vector3 &p);
	static Vector3 Random_In_Sphere_Volume();
	static Vector3 Reflect(Vector3& v, Vector3& n);
	static bool Refract(Vector3& v, Vector3& n,float refractive_index,Vector3 &refracted);

	static Vector3 componentWiseMult(Vector3& a, Vector3& b);
	string ToString();



};
