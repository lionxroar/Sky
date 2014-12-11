#ifndef _POINT_H_
#define _POINT_H_

class Point
{
private:
	double xval, yval;
public:
	Point();
	Point& GetCursorPos(Point*);
	SetCursorPos(double, double);
};
#endif