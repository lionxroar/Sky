#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3.h"

class Camera
{
public:

	Vector3 mPos;
	Vector3 mView;
	Vector3 mUp;

	//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
	int mWindowWidth;
	int mWindowHeight;


	// This function let you control the camera with the mouse
	void Mouse_Move();

	//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

	void Rotate_View(float x, float y, float z);
	void Move_Camera(float cameraspeed);
	void Position_Camera(float pos_x, float pos_y, float pos_z,
		float view_x, float view_y, float view_z,
		float up_x, float up_y, float up_z);
};

#endif