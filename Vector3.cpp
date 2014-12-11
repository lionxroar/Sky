#include <math.h>

#include "Vector3.h"

Vector3::Vector3(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

/* This operation adds the parameter vector's coordinates to the current vector
and returns the sum of the two, therefore it modifies the calling vector.
*/
Vector3& Vector3::operator+(const Vector3& v)
{
	Vector3 temp(0, 0, 0);
	temp.x = x + v.x;
	temp.y = y + v.y;
	temp.z = z + v.z;

	return temp;
}

/*	Same as operator+ above, except subtracts their coordinates
*/
Vector3& Vector3::operator-(const Vector3& v)
{
	Vector3 temp(0, 0, 0);
	temp.x = x - v.x;
	temp.y = y - v.y;
	temp.z = z - v.z;

	return temp;
}

Vector3& Vector3::operator*(float t)
{
	Vector3 temp;
	temp.x = x*t;
	temp.y = y*t;
	temp.z = z*t;

	return temp;
}

void Vector3::negate()
{
	x = -x;
	y = -y;
	z = -z;
}

void Vector3::scale(double s)
{
	x = s*x;
	y = s*y;
	z = s*z;
}

double Vector3::dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vector3& Vector3::cross(const Vector3& v1)
{
	double cx = y*v1.z - z*v1.y;
	double cy = z*v1.x - x*v1.z;
	double cz = x*v1.y - y*v1.x;

	Vector3 yoFace(cx, cy, cz);
	return yoFace;
}

double Vector3::length()
{
	double x2 = x*x;
	double y2 = y*y;
	double z2 = z*z;

	return sqrt(x2 + y2 + z2);
}

void Vector3::normalize()
{
	double length = (*this).length();
	x = x / length;
	y = y / length;
	z = z / length;
}

void Vector3::print(string comment)
{
	cout << comment << endl << "x: " << x << endl << "y: " << y << endl << "z: " << z << endl;
}

float Vector3::angle(Vector3 a)
{
	float x = a.dot(a, *this);
	float y = (*this).magnitude();
	return acos(x / (a.magnitude()*y));
}

float Vector3::magnitude()
{

	//cout << "mag: " << x << ',' << y << ',' << z;
	return sqrt(x*x + y*y + z*z);
}