#include <math.h>

#include "Vector4.h"

Vector4::Vector4(double a, double b, double c, double d)
{
	x = a;
	y = b;
	z = c;
	w = d;
}

Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

Vector4& Vector4::operator+(const Vector4& v1)
{
	Vector4 temp(0, 0, 0, 0);
	temp.x = x + v1.x;
	temp.y = y + v1.y;
	temp.z = z + v1.z;
	temp.w = w + v1.w;

	return temp;
}

Vector4& Vector4::operator-(const Vector4& v1)
{
	Vector4 temp(0, 0, 0, 0);
	temp.x = x - v1.x;
	temp.y = y - v1.y;
	temp.z = z - v1.z;
	temp.w = w - v1.w;

	return temp;
}

void Vector4::dehomogenize()
{
	x = x / w;
	y = y / w;
	z = z / w;
	w = w / w;
}

void Vector4::print(string comment)
{
	cout << comment << endl << "x: " << x << endl << "y: " << y << endl << "z: " << z << endl << "w: " << w << endl;
}