#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <string>
#include <iostream>

using namespace std;

class Vector3
{
public:
	double x;
	double y;
	double z;

	Vector3(double a, double b, double c);
	Vector3();

	Vector3& operator+(const Vector3&);
	Vector3& operator-(const Vector3&);
	Vector3& operator*(float t);
	void negate();
	void scale(double s);
	static double dot(const Vector3&, const Vector3&);
	Vector3& cross(const Vector3&);
	double length();
	void normalize();
	void print(string comment);
	float angle(Vector3);
	float magnitude();
};
#endif