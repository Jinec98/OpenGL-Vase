#include <stdlib.h>
#include <GL/glut.h>
#include "imageloader.h"
#include "buildvase.h"
#include <iostream>

using namespace std;

GLuint vaseTexture;

Vase* vase;
Image* image;

static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, vaseTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//缩放模型并调整模型位置
	glTranslatef(0, -3.0, -10);
	glScalef(0.02, 0.02, 0.02);

	glBegin(GL_QUADS);
	for (auto s : vase->vec_surface)
	{
		//纹理
		glTexCoord2d(vase->vec_vertex[s[0]].tx, vase->vec_vertex[s[0]].ty);
		glTexCoord2d(vase->vec_vertex[s[1]].tx, vase->vec_vertex[s[1]].ty);
		glTexCoord2d(vase->vec_vertex[s[2]].tx, vase->vec_vertex[s[2]].ty);
		glTexCoord2d(vase->vec_vertex[s[3]].tx, vase->vec_vertex[s[3]].ty);

		//顶点
		glVertex3d(vase->vec_vertex[s[0]].x, vase->vec_vertex[s[0]].y, vase->vec_vertex[s[0]].z);
		glVertex3d(vase->vec_vertex[s[1]].x, vase->vec_vertex[s[1]].y, vase->vec_vertex[s[1]].z);
		glVertex3d(vase->vec_vertex[s[2]].x, vase->vec_vertex[s[2]].y, vase->vec_vertex[s[2]].z);
		glVertex3d(vase->vec_vertex[s[3]].x, vase->vec_vertex[s[3]].y, vase->vec_vertex[s[3]].z);
	}
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

	vase = new Vase(200, 200);
	vase->bulidVase();
	vase->writeFile();

	image = loadBMP("texture.bmp");
	vaseTexture = loadTexture(image);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Textured Vase");
	glEnable(GL_DEPTH_TEST);

	glutReshapeFunc(resize);
	glutDisplayFunc(renderScene);
	Initialize();

	glutMainLoop();

	return 0;
}
