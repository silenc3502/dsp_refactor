#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>

#define SLICE	360

void draw_y_x2(void);
void draw_big_rect(void);
void draw_small_rect(void);

float common_angles[5] = {15.0, 30.0, 45.0, 60.0, 75.0};
float freq_table[5] = {1000.0, 2400.0, 5000.0, 24000.0, 77000.0};

float theta = 0.0;

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1, 0, 0);

	glBegin(GL_LINE_LOOP);
	glVertex3f(100.0, 0.0, 0.0);
        glVertex3f(-100.0, 0.0, 0.0);
        glEnd();

        glColor3f(0.0, 1.0, 0.0);

        glBegin(GL_LINE_LOOP);
        glVertex3f(0.0, 100.0, 0.0);
        glVertex3f(0.0, -100.0, 0.0);
    glEnd();

	glLineWidth(3);
	draw_y_x2();
	glLineWidth(1);
	glColor3f(0, 0, 1);
	draw_small_rect();
	glColor3f(0, 1, 0);
	draw_big_rect();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
    GLfloat n_range = 100.0f;

    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w <= h)
        glOrtho(-n_range, n_range, -n_range * h / w, n_range * h / w, -n_range, n_range);
    else
        glOrtho(-n_range * w / h, n_range * w / h, -n_range, n_range, -n_range, n_range);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw_y_x2(void)
{
	float t = 0.0, step = 0.001;
	float x = 0, x2 = 0, y2, cx, cy;
	float tmp;
	int cache = 0;

	if(t > 100)
		t = 0.0;

	glBegin(GL_LINES);
	for(; ; t += step)
	{
		if(t > 100)
			break;

		y2 = t * t;

		if(cache)
		{
			glVertex2f(cx * 10, cy);
			glVertex2f(t * 10, y2);
		}

		cache = 1;
		cx = t;
		cy = y2;
	}
	glEnd();
}

void draw_big_rect(void)
{
	float t = 0.0, step = 0.5;
	float x2 = 0, y2, cx, cy;
	int cache = 0;

	if(t > 100)
		t = 0.0;

	for(; ; t += step)
	{
		if(t > 100)
			break;

		y2 = t * t;

		if(cache)
		{

			glBegin(GL_LINES);
				glVertex2f(cx * 10, 0);
				glVertex2f(t * 10, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex2f(cx * 10, 0);
				glVertex2f(cx * 10, y2);
			glEnd();

			glBegin(GL_LINES);
				glVertex2f(cx * 10, y2);
				glVertex2f(t * 10, y2);
			glEnd();

			glBegin(GL_LINES);
				glVertex2f(t * 10, y2);
				glVertex2f(t * 10, y2);
			glEnd();
		}

		cache = 1;
		cx = t;
		cy = y2;
	}
}

void draw_small_rect(void)
{
	float t = 0.0, step = 0.0001;
	float x2 = 0, y2, cx, cy;
	int cache = 0;

	if(t > 100)
		t = 0.0;

	for(; ; t += step)
	{
		if(t > 100)
			break;

		y2 = t * t;

		if(cache)
		{

			glBegin(GL_LINES);
				glVertex2f(cx * 10, 0);
				glVertex2f(t * 10, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex2f(cx * 10, 0);
				glVertex2f(cx * 10, y2);
			glEnd();

			glBegin(GL_LINES);
				glVertex2f(cx * 10, y2);
				glVertex2f(t * 10, y2);
			glEnd();

			glBegin(GL_LINES);
				glVertex2f(t * 10, y2);
				glVertex2f(t * 10, y2);
			glEnd();
		}

		cache = 1;
		cx = t;
		cy = y2;
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Digital Signal Processing");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
