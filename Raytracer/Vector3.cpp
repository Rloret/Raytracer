#include "stdafx.h"
#include "Vector3.h"

#define RAND01 ((double)rand() / (RAND_MAX))
Vector3::Vector3() {}
Vector3::Vector3(float X, float Y, float Z) {
	x = X;
	y = Y;
	z = Z;
}

Vector3::Vector3(float V)
{
	x = y = z = V;
}

Vector3::Vector3(int V)
{
	x = y = z = V;
}

Vector3::Vector3(double V)
{
	x = y = z = V;
}

Vector3::~Vector3() {

}
double Vector3::operator* (const Vector3 &p) const
{
	return (x*p.x + y*p.y + z*p.z);
}
void Vector3::operator*=(const Vector3 & p)
{
	x *= p.x;
	y *= p.y;
	z *= p.z;
}

void Vector3::operator*=(const float p)
{
	x *= p; y *= p; z *= p;
}

Vector3 Vector3::operator*(const float p) const
{
	return Vector3(x * p, y * p, z * p);
}


Vector3 Vector3::operator/(const float p) const
{
	return Vector3(x / p, y / p, z / p);
}

void Vector3::operator/=(const float p)
{
	x /= p; y /= p; z /= p;
}

void Vector3::operator^=(const Vector3 & p)
{
	//compute cross product
	double a = (this->y*p.z - this->z*p.y);
	double b = (this->z*p.x - this->x*p.z);
	double c = (this->z*p.y - this->y*p.x);
	//set new values to this vector;
	x = a; y = b; z = c;
}

Vector3 Vector3::operator^(const Vector3 & p) const
{

	return Vector3((y*p.z - z*p.y), (z*p.x - x*p.z), (x*p.y - y*p.x));

}

void Vector3::operator+=(const Vector3 & p)
{
	x += p.x;
	y += p.y;
	z += p.z;
}

void Vector3::operator-=(const Vector3 & p)
{
	x -= p.x;
	y -= p.y;
	z -= p.z;
}

bool Vector3::operator==(const Vector3 & p)const
{
	return ((x == p.x) && (y == p.y) && (z == p.z));
}

bool Vector3::operator!=(const Vector3 & p)const
{
	return ((x != p.x) && (y != p.y) && (z != p.z));
}

void Vector3::operator-()
{
	x = -x;
	y = -y;
	z = -z;
}

Vector3 Vector3::operator-(const Vector3 & p) const
{
	return Vector3(x - p.x, y - p.y, z - p.z);

}

Vector3 Vector3::operator+(const Vector3 & p) const
{
	return Vector3(x + p.x, y + p.y, z + p.z);
}

void Vector3::normalize()
{
	float module = this->module();

	if (module == 0) return;

	x /= module;
	y /= module;
	z /= module;

}

Vector3 Vector3::normalized() const
{
	Vector3 copy = Vector3(this->x,this->y,this->z);
	float module = copy.module();

	if (module == 0) return Vector3();
	return (Vector3(x, y, z) / module);

}

Vector3 Vector3::Clamp(float min, float max) const
{
	Vector3 clamped = Vector3(x > max ? max : x < min ? min : x,
								y > max ? max : y < min ? min : y,
								z > max ? max : z < min ? min : z);
	return clamped;
}



double Vector3::module()
{
	return sqrt(x*x + y*y + z*z);
}

double Vector3::distance(const Vector3 & p)
{
	return sqrt((p.x - x)*(p.x - x) + (p.y - y)*(p.y - y) + (p.z - z)*(p.z - z));
}

double Vector3::distance2(const Vector3 & p)
{
	return (p.x - x)*(p.x - x) + (p.y - y)*(p.y - y) + (p.z - z)*(p.z - z);
}

Vector3 Vector3::Random_In_Sphere_Volume()
{
	{
		Vector3 p;
		do {
			p = (Vector3(RAND01, RAND01, RAND01)*2.0F) - Vector3(1);
		} while (p.module() >= 1.0);
		return p;

	}
}

bool Vector3::Refract(Vector3 & v, Vector3 & n, float refractive_index, Vector3 & refracted)
{
	Vector3 nv = v.normalized();
	float theta = nv*n.normalized();
	float discriminant = 1.0 - refractive_index*refractive_index * (1 - theta*theta);

	if (discriminant > 0) {
		refracted =  ((nv - n*theta)*refractive_index) - (n*sqrt(discriminant));
		return true;
	}
	else return false;
}

Vector3 Vector3::Reflect(Vector3& v, Vector3& n)
{
	Vector3 N = n.normalized();
	return v - N*(v*N * 2);
}

Vector3 Vector3::componentWiseMult(Vector3& a, Vector3& b)
{
	return Vector3(a.x*b.x, a.y*b.y, a.z*b.z);
}



string Vector3::ToString()
{
	to_string(this->x);
	return string(to_string(this->x) + ',' + to_string(this->y) + ',' + to_string(this->z));
}





