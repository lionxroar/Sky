#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include <string>
#include "Vector3.h"
#include "Vector4.h"
#include "GL/glut.h"

#define M_PI 3.14159265358979323846

using namespace std;

class Matrix4
{
public:
	double m[4][4];
	Matrix4();
	Matrix4(double, double, double, double,
		double, double, double, double,
		double, double, double, double,
		double, double, double, double);
	Matrix4& operator=(const Matrix4&);
	Matrix4& operator*(const Matrix4&);
	Vector4& operator*(const Vector4&);
	double* getPointer();
	void identity();
	void transpose();
	void makeRotateX(double);
	void makeRotateY(double);
	void makeRotateZ(double);
	void makeRotate(double angle, const Vector3& axis);
	void makeScale(double sx, double sy, double sz);
	void makeTranslate(double tx, double ty, double tz);
	void print(string comment);

	//what im adding
	void changeValue(int i, int j, double value);
	void allChange(int);
	void printInfo();
	//
	Matrix4 Matrix4::ballRotation(int, int, int, int, int, int);
	void copyRot(Matrix4);
	void invertOrtho();
	Matrix4& rotate(double, float, float, float);
	void rotate(double, Vector3&);
	//end of what I added
};

#endif