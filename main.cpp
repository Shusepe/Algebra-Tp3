#include <GL/glut.h>
#include <iostream>
#include "sphere.h"
#include "camera.h"
#include "frustum.h"

const int MAX_SPHERES = 10;

//Tamaño de ventana
int width = 600;
int height = 600;
int lastFrameTime;
int currentFrameTime;
int visibleSpheres = 0;
double deltaTime;
double rx = 0;
double ry = 0;
double rz = 0;
double px = 0;
double py = 0;
double pz = 0;
float aspect = 1.0f;
float fov = 1.0f;
float zFar = 500.0f;

Sphere spheres[MAX_SPHERES];

Camera mainCamera;
Frustum camFrustum;

void initSpheres();
void drawSpheres();
void calculateTime();

void update(int width, int height) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)height / (GLfloat)width, 1, 300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init() 
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	mainCamera = Camera(px, py, pz, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	initSpheres();
}

void display()
{
	visibleSpheres = 0;
	camFrustum = getFrustumFromCamera(mainCamera, aspect, fov, 0.5f, zFar);
	calculateTime();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	mainCamera.LookAt();
	glPushMatrix();

	// for (float i = -100; i < 100; i += 1.1)
	// {
	// 	glColor3f(1.0f, 1.0f, 1.0f);
	// 	glBegin(GL_LINE_STRIP);
	// 	glVertex3f(i, 0, -100);
	// 	glVertex3f(i, 0, 100);
	// 	glEnd();
	// }
	
	// for (float i = -100; i < 100; i += 1.1)
	// {
	// 	glColor3f(1.0f, 1.0f, 1.0f);
	// 	glBegin(GL_LINE_STRIP);
	// 	glVertex3f(-100, 0, i);
	// 	glVertex3f(100, 0, i);
	// 	glEnd();
	// }

	//Ejes

	// Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	glEnd();

	// X
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();
	
	// Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);
	glEnd();

	drawSpheres();

	std::cout << "Total spheres: " << MAX_SPHERES << std::endl;
	std::cout << "Visible spheres: " << visibleSpheres << std::endl;
	glPopMatrix();
	glutSwapBuffers();
}

void control(unsigned char key, int x, int y) 
{
	switch (key)
	{

	// Eje X
	case 'd': 
		rx = rx + 0.2;
		break;
	
	case 'a':
		rx = rx - 0.2;
		break;

	case 'l': 
		px = px + 0.8;
		break;
	
	case 'j': 
		px = px - 0.2;
		break;
		
	// Eje Y
	case 'q': 
		ry = ry + 0.2;
		break;
	
	case 'e':
		ry = ry - 0.2;
		break;

	case 'u': 
		py = py + 0.2;
		break;
	
	case 'o': 
		py = py - 0.2;
		break;

	case 49: // 1
		ry = ry + 0.2;
		py = py + 0.2;
		break;

	case 50: // 2
		ry = ry - 0.2;
		py = py - 0.2;
		break;
	
	case 'w': 
		rz = rz + 0.2;
		break;

	case 's': 
		rz = rz - 0.2;
		break;

	case 'i': 
		pz = pz + 0.8;
		break;

	case 'k': 
		pz = pz - 0.8;
		break;
	}

	glutPostRedisplay();
}

void arrows(int key, int x, int y) 
{
	std::cout << "time: " << deltaTime << std::endl;
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		mainCamera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
		break;
	
	case GLUT_KEY_LEFT:
		mainCamera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
		break;
	
	case GLUT_KEY_UP:
		mainCamera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
		break;

	case GLUT_KEY_DOWN:
		mainCamera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		break;
	}

	glutPostRedisplay();
}

void calculateTime()
{
	lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
	std::cout << "lastFrameTime: " << lastFrameTime << std::endl;

    currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
	std::cout << "currentFrameTime: " << currentFrameTime << std::endl;

    deltaTime = (currentFrameTime - lastFrameTime) / 0.5f;
    lastFrameTime = currentFrameTime;
}

void initSpheres()
{
	for (int i = 0; i < MAX_SPHERES; i++)
	{
		float xAxis = 7.0f;
		float zero = 0.0f;

		glm::vec3 position = { xAxis, zero + 1.0f * i, zero};

		spheres[i] = Sphere{position, 1.0f};
	}
}

void drawSpheres()
{
	for (int i = 0; i < MAX_SPHERES; i++)
	{
		if(spheres[i].isOnFrustum(camFrustum)){
			visibleSpheres++;
			spheres[i].draw();
		}
	}
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(width, height);
	glutCreateWindow("Algebra Tp 3");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(control);
	glutSpecialFunc(arrows);
	glutReshapeFunc(update);
	glutMainLoop();
}