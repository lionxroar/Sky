#include "Bezier.h"

Bezier::Bezier(float u, float v, float angle)
{
	float q = u / 3; //q is horizontal
	float r = v / 3; //r is vertical

	float s = r - q;
	float a = r + q;

	//p0-p3
	p0.x = 0 * q;
	p1.x = 1 * q;
	p2.x = 2 * q;
	p3.x = 3 * q;

	p0.z = 0 * r;
	p1.z = 0 * r;
	p2.z = 0 * r;
	p3.z = 0 * r;

	p1.y = sin(s*angle);
	p3.y = cos(a*angle);

	//p4-p7
	p4.x = 0 * q;
	p5.x = 1 * q;
	p6.x = 2 * q;
	p7.x = 3 * q;

	p4.z = 1 * r;
	p5.z = 1 * r;
	p6.z = 1 * r;
	p7.z = 1 * r;

	p5.y = sin(a*angle) / 50;
	p7.y = cos(s*angle) / 50;

	//p8-p11
	p8.x = 0 * q;
	p9.x = 1 * q;
	p10.x = 2 * q;
	p11.x = 3 * q;

	p8.z = 2 * r;
	p9.z = 2 * r;
	p10.z = 2 * r;
	p11.z = 2 * r;

	p9.y = sin(s*angle);
	p11.y = cos(a*angle);

	//p12-p15
	p12.x = 0 * q;
	p13.x = 1 * q;
	p14.x = 2 * q;
	p15.x = 3 * q;

	p12.z = 3 * r;
	p13.z = 3 * r;
	p14.z = 3 * r;
	p15.z = 3 * r;

	p13.y = sin(a*angle);
	p15.y = cos(s*angle);
}

long factorial(long n)
{
	long result = 1;

	//If n is 0, by definition 0! is equal to 1
	if (n <= 0)
		return result;

	//Calculate the factorial, n * n-1 * n-2 * ... * 1
	for (long i = n; i > 0; --i)
	{
		result *= i;
	}

	return result;
}

long combo(long n, long i)
{
	//C(n, i) = n! / ((n-1)! * i!)
	return factorial(n) / (factorial(n - i) * factorial(i));
}

double bernstizzlesCoeff(long n, long i, double t)
{
	//long n: is the degree of our curve, in the case of a cubic curve it is 3
	//long i: the index of the Bernstein coefficient and the control point
	//double t: is the time we are evaluating at

	//Calculate the Bernstein coefficient
	return combo(n, i) * pow(1.0 - t, n - i) * pow(t, i);
}

void Bezier::tessellate(float t1, float t2, float delta)
{
	//q0

	//t1 = sin(3.14*t1);
	//t2 = sin(3.14*t2);
	Matrix4 mp0(p0.x, p1.x, p2.x, p3.x,
		p0.y, p1.y, p2.y, p3.y,
		p0.z, p1.z, p2.z, p3.z,
		0.0, 0.0, 0.0, 0.0);

	Vector4 C(bernstizzlesCoeff(3, 0, t1),
		bernstizzlesCoeff(3, 1, t1),
		bernstizzlesCoeff(3, 2, t1),
		bernstizzlesCoeff(3, 3, t1));

	Vector4 q0 = mp0 * C;
	q0.w = 1.0;

	//q1
	Matrix4 mp1(p4.x, p5.x, p6.x, p7.x,
		p4.y, p5.y, p6.y, p7.y,
		p4.z, p5.z, p6.z, p7.z,
		0.0, 0.0, 0.0, 0.0);

	Vector4 q1 = mp1 * C;
	q1.w = 1.0;

	//q2
	Matrix4 mp2(p8.x, p9.x, p10.x, p11.x,
		p8.y, p9.y, p10.y, p11.y,
		p8.z, p9.z, p10.z, p11.z,
		0.0, 0.0, 0.0, 0.0);

	Vector4 q2 = mp2 * C;
	q2.w = 1.0;

	//q3
	Matrix4 mp3(p12.x, p13.x, p14.x, p15.x,
		p12.y, p13.y, p14.y, p15.y,
		p12.z, p13.z, p14.z, p15.z,
		0.0, 0.0, 0.0, 0.0);

	Vector4 q3 = mp3 * C;
	q3.w = 1.0;

	//t2

	Matrix4 mq(q0.x, q1.x, q2.x, q3.x,
		q0.y, q1.y, q2.y, q3.y,
		q0.z, q1.z, q2.z, q3.z,
		0.0, 0.0, 0.0, 0.0);

	Vector4 C2(bernstizzlesCoeff(3, 0, t2),
		bernstizzlesCoeff(3, 1, t2),
		bernstizzlesCoeff(3, 2, t2),
		bernstizzlesCoeff(3, 3, t2));

	Vector4 x = mq * C2;
	x.w = 1.0;

	glBegin(GL_QUADS);
	glVertex3d(x.x, x.y, x.z);
	glVertex3d(x.x + delta, x.y, x.z);
	glVertex3d(x.x + delta, x.y , x.z +delta);
	glVertex3d(x.x, x.y , x.z +delta);
	glEnd();

}