#ifndef _BEZIER_H_
#define _BEZIER_H_

#include "Vector4.h"
#include "Matrix4.h"
#include <GL/glut.h>

class Bezier
{
public:
	Vector4 p0, p1, p2, p3,
		p4, p5, p6, p7,
		p8, p9, p10, p11,
		p12, p13, p14, p15;

	Bezier(float, float, float);
	void tessellate(float, float, float);
	void draw(Vector4, float);
};
#endif