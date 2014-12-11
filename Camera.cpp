#include "Camera.h"

void Camera::Position_Camera(float pos_x, float pos_y, float pos_z,
	float view_x, float view_y, float view_z,
	float up_x, float up_y, float up_z)
{
	Vector3 vPos = Vector3(pos_x, pos_y, pos_z);
	Vector3 vView = Vector3(view_x, view_y, view_z);
	Vector3 vUp = Vector3(up_x, up_y, up_z);

	mPos = vPos;							// set the position
	mView = vView;							// set the view
	mUp = vUp;							// set the up vector
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA MOVE CAMERA
/////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Move_Camera(float cameraspeed)
{
	Vector3 vVector = Vector3(0, 0, 0);		// init a new view vector
	vVector = mView - mPos;					// Get the view vector

	// forward positive cameraspeed and backward negative -cameraspeed.
	mPos.x = mPos.x + vVector.x * cameraspeed;
	mPos.z = mPos.z + vVector.z * cameraspeed;
	mView.x = mView.x + vVector.x * cameraspeed;
	mView.z = mView.z + vVector.z * cameraspeed;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA ROTATE VIEW
/////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Rotate_View(float x, float y, float z)
{
	Vector3 vVector = mView - mPos;

	if (x)
	{
		mView.z = (float)(mPos.z + sin(x)*vVector.y + cos(x)*vVector.z);
		mView.y = (float)(mPos.y + cos(x)*vVector.y - sin(x)*vVector.z);
	}
	if (y)
	{
		mView.z = (float)(mPos.z + sin(y)*vVector.x + cos(y)*vVector.z);
		mView.x = (float)(mPos.x + cos(y)*vVector.x - sin(y)*vVector.z);
	}
	if (z)
	{
		mView.x = (float)(mPos.x + sin(z)*vVector.y + cos(z)*vVector.x);
		mView.y = (float)(mPos.y + cos(z)*vVector.y - sin(z)*vVector.x);
	}
}