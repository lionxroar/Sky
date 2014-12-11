#include <math.h>
#include "Matrix4.h"

Matrix4::Matrix4()
{
	for (int i = 0; i<4; ++i)
	{
		for (int j = 0; j<4; ++j)
		{
			m[i][j] = 0;
		}
	}
}

Matrix4::Matrix4(double a, double b, double c, double d,
	double e, double f, double g, double h,
	double i, double j, double k, double l,
	double z, double n, double o, double p)
{
	m[0][0] = a;
	m[0][1] = b;
	m[0][2] = c;
	m[0][3] = d;

	m[1][0] = e;
	m[1][1] = f;
	m[1][2] = g;
	m[1][3] = h;

	m[2][0] = i;
	m[2][1] = j;
	m[2][2] = k;
	m[2][3] = l;

	m[3][0] = z;
	m[3][1] = n;
	m[3][2] = o;
	m[3][3] = p;
}

//Method im adding to test other methods
void Matrix4::changeValue(int i, int j, double value)
{
	m[i][j] = value;
}

void Matrix4::allChange(int a)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = a;
}
//End of my method

Matrix4& Matrix4::operator=(const Matrix4& m2)
{
	if (this != &m2)
	{
		for (int i = 0; i<4; ++i)
		{
			for (int j = 0; j<4; ++j)
			{
				m[i][j] = m2.m[i][j];
			}
		}
	}
	return *this;
}

Matrix4& Matrix4::operator*(const Matrix4& m2)
{
	double x = 0;
	double fuckyou[4][4];
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				x = x + (m[k][j])*(m2.m[j][i]);
			}
			fuckyou[k][i] = x;
			x = 0;
		}
	}
	Matrix4 yoFace;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[j][i] = fuckyou[j][i];
		}
	}

	return *this;
}

Vector4& Matrix4::operator*(const Vector4& v)
{
	double x = v.x*m[0][0] + v.y*m[0][1] + v.z*m[0][2] + v.w*m[0][3];
	double y = v.x*m[1][0] + v.y*m[1][1] + v.z*m[1][2] + v.w*m[1][3];
	double z = v.x*m[2][0] + v.y*m[2][1] + v.z*m[2][2] + v.w*m[2][3];
	double w = v.x*m[3][0] + v.y*m[3][1] + v.z*m[3][2] + v.w*m[3][3];

	Vector4 newVector(x, y, z, w);
	return newVector;
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
	return &m[0][0];
}

// set matrix to identity matrix
void Matrix4::identity()
{
	for (int i = 0; i<4; ++i)
	{
		for (int j = 0; j<4; ++j)
		{
			if (i == j)
				m[i][j] = 1.0;
			else
				m[i][j] = 0.0;
		}
	}
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
	Matrix4 temp;
	for (int i = 0; i<4; ++i)
	{
		for (int j = 0; j<4; ++j)
		{
			temp.m[j][i] = m[i][j];
		}
	}
	*this = temp;  // copy temporary values to this matrix
}

void Matrix4::makeRotateX(double angle)
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[1][1] = cos(angle);
	m[2][1] = sin(angle);
	m[1][2] = -sin(angle);
	m[2][2] = cos(angle);
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle)
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
}

void Matrix4::makeRotateZ(double angle)
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[0][0] = cos(angle);
	m[1][0] = sin(angle);
	m[0][1] = -sin(angle);
	m[1][1] = cos(angle);
}

void Matrix4::makeRotate(double angle, const Vector3& axis)
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[0][0] = 1 + (1 - cos(angle))*((axis.x*axis.x) - 1);
	m[1][0] = axis.z*sin(angle) + (1 - cos(angle))*axis.y*axis.x;
	m[2][0] = -axis.y*sin(angle) + (1 - cos(angle))*axis.z*axis.x;
	m[0][1] = -axis.z*sin(angle) + (1 - cos(angle))*axis.x*axis.y;
	m[1][1] = 1 + (1 - cos(angle))*((axis.y*axis.y) - 1);
	m[2][1] = axis.x*sin(angle) + (1 - cos(angle))*axis.z*axis.y;
	m[0][2] = axis.y*sin(angle) + (1 - cos(angle))*axis.x*axis.z;
	m[1][2] = -axis.x*sin(angle) + (1 - cos(angle))*axis.y*axis.z;
	m[2][2] = 1 + (1 - cos(angle))*((axis.z*axis.z) - 1);
}

void Matrix4::makeScale(double sx, double sy, double sz)
{
	identity();
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
}

void Matrix4::makeTranslate(double tx, double ty, double tz)
{
	identity();
	m[0][3] = tx;
	m[1][3] = ty;
	m[2][3] = tz;
}

void Matrix4::print(string comment)
{
	cout << comment << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

void Matrix4::printInfo()
{
	double normX = m[0][3];
	double normY = m[1][3];
	double normZ = m[2][3];
	Vector3 norm(normX, normY, normZ);
	norm.print("");
}

Matrix4 Matrix4::ballRotation(int width, int height, int oX, int oY, int tX, int tY)
{
	const float TRACKBALL_SIZE = 1.3f;              // virtual trackball size (empirical value)
	Matrix4 mInv;                                   // inverse of ObjectView matrix
	Vector3 v1, v2;                                 // mouse drag positions in normalized 3D space
	float smallSize;                                // smaller window size between width and height
	float halfWidth, halfHeight;                    // half window sizes
	float angle;                                    // rotational angle
	float d;                                        // distance

	// Compute mouse coordinates in window and normalized to -1..1
	// ((0,0)=window center, (-1,-1) = bottom left, (1,1) = top right)
	halfWidth = (float)width / 2.0f;
	halfHeight = (float)height / 2.0f;
	smallSize = (halfWidth < halfHeight) ? halfWidth : halfHeight;
	v1.x = (((float)oX - halfWidth) / smallSize);
	v1.y = (((float)(height - oY) - halfHeight) / smallSize);
	v2.x = (((float)tX - halfWidth) / smallSize);
	v2.y = (((float)(height - tY) - halfHeight) / smallSize);

	// Compute z-coordinates on Gaussian trackball:
	d = sqrtf(v1.x * v1.x + v1.y * v1.y);
	v1.z = (expf(-TRACKBALL_SIZE * d * d));
	d = sqrtf(v2.x * v2.x + v2.y * v2.y);
	v2.z = (expf(-TRACKBALL_SIZE * d * d));

	// Compute rotational angle:
	angle = v1.angle(v2);                          // angle = angle between v1 and v2

	// Compute rotational axis:
	v2 = v2.cross(v1);                                  // v2 = v2 x v1 (cross product)

	// Convert axis coordinates (v2) from WCS to OCS:
	mInv.identity();
	mInv.copyRot(*this);                             // copy rotational part of mv to mInv
	mInv.invertOrtho();                             // invert orthogonal matrix mInv
	// MIGHT BE 1 BELOW
	Vector4 tmp = Vector4(v2.x, v2.y, v2.z, 1);
	Vector4 tmp2 = mInv*tmp;
	v2 = Vector3(tmp2.x, tmp2.y, tmp2.z);
	//v2.multiply(&mInv);                             // v2 = v2 x mInv (matrix multiplication)
	v2.normalize();                                 // normalize v2 before rotation

	// Perform acutal model view matrix modification:
	return rotate(-angle * 100, v2.x, v2.y, v2.z);      // rotate model view matrix
}

void Matrix4::copyRot(Matrix4 a)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//this->set(i, j, a->get(i, j));
			(*this).m[i][j] = a.m[i][j];
		}
	}
}

void Matrix4::invertOrtho()
{
	(*this).transpose();
}

Matrix4& Matrix4::rotate(double angle, float a, float b, float c)
{
	Vector3 tmp = Vector3(a, b, c);
	this->rotate(angle, tmp);
	return *this;
}

void Matrix4::rotate(double angle, Vector3 &a)
{
	// Transformations slide 44
	Vector3 b = Vector3(a.x, a.y, a.z);
	b.normalize();

	Matrix4 rot;
	rot.makeRotate(angle, b);
	rot.transpose(); // make row major

	Matrix4 result = (*this)*rot;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = result.m[i][j];
		}
	}
}