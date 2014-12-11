#include "main.h"

Camera objCamera;
GLuint SkyboxTexture[6];
float angle = 0.0;

void Draw_Bezier(float width, float height)
{
	glColor3f(0, 0, 1);

	Bezier my = Bezier(width, height, angle);
	for (float t1 = -0.5; t1 < 0.49; t1 += 0.01)
	{
		for (float t2 = -0.5; t2 < 0.49; t2 += 0.01)
		{
			my.tessellate(t1, t2, .1);
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);

	Draw_Bezier(4.75,4.75);
	angle += .01;
	glColor3f(1, 1, 1);
	Draw_Skybox(0, 0, 0, 100, 100, 100);	// Draw the Skybox
	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	objCamera.mWindowWidth = w;
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	objCamera.mWindowWidth = w;
	objCamera.mWindowHeight = h;
}

void idle()
{
	display();
}

unsigned char* loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}

void loadTexture(const char* name, int id)
{
	//GLuint texture[1];     // storage for one texture
	int twidth, theight;   // texture width/height [pixels]
	unsigned char* tdata;  // texture pixel data

	// Load image file
	tdata = loadPPM(name, twidth, theight);
	if (tdata == NULL) return;

	// Create ID for texture
	glGenTextures(1, &SkyboxTexture[id]);

	// Set this texture to be the one we are working with
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[id]);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	// Set bi-linear filtering for both minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void initGL()
{
	glEnable(GL_TEXTURE_2D);   // enable texture mapping
	glShadeModel(GL_SMOOTH);   // enable smooth shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // black background
	glClearDepth(1.0f);        // depth buffer setup
	glEnable(GL_DEPTH_TEST);   // enables depth testing
	glDepthFunc(GL_LEQUAL);    // configure depth testing
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // really nice perspective calculations

	glEnable(GL_TEXTURE_2D);

	//objCamera.Position_Camera(0, 2.5f, 10, 0, 2.5f, 0, 0, 1, 0);
	objCamera.Position_Camera(0, 2.5, 0, 0, 0, 2.5, 0, 1, 0);

	// Load the Skybox textures
	loadTexture("PalldioPalace_extern_front.ppm", SKYFRONT);
	loadTexture("PalldioPalace_extern_back.ppm", SKYBACK);
	loadTexture("PalldioPalace_extern_left.ppm", SKYLEFT);
	loadTexture("PalldioPalace_extern_right.ppm", SKYRIGHT);
	loadTexture("PalldioPalace_extern_top.ppm", SKYUP);
}

void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYFRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYBACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYLEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYRIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYUP]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + height, z);
	glEnd();

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 114:
		objCamera.Rotate_View(0, -CAMERASPEED, 0);
		break;
	case 82:
		objCamera.Rotate_View(0, CAMERASPEED, 0);
		break;
	case 117:
		objCamera.Rotate_View(CAMERASPEED, 0, 0);
		break;
	case 85:
		objCamera.Rotate_View(-CAMERASPEED, 0, 0);
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);      // set initial window size
	glutCreateWindow("OpenGL Cube");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	initGL();

	glutMainLoop();
	return 0;
}