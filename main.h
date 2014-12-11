#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "Camera.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Bezier.h"

#define SKYFRONT 0						// Give Front ID = 0
#define SKYBACK  1						// Give Back  ID = 1
#define SKYLEFT  2						// Give Left  ID = 2
#define SKYRIGHT 3						// Give Right ID = 3
#define SKYUP    4						// Give Up    ID = 4
#define SKYDOWN  5						// Give Down  ID = 5

#define CAMERASPEED 0.03f

//void Keyboard_Input();
//void Draw_Grid();
void Draw_Skybox(float x, float y, float z, float width, float height, float length);

#endif