#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <iostream>
#include <string>

using namespace std;

class Vector4
{
public:
	double x;
	double y;
	double z;
	double w;

	Vector4();
	Vector4(double a, double b, double c, double d);
	Vector4& operator+(const Vector4&);
	Vector4& operator-(const Vector4&);
	void dehomogenize();
	void print(string comment);
};
#endif _VECTOR4_H_