#include <GL/glut.h>

// The geometry pattern consists of some triangles
void draw_geometry()
{
	// Clear color buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// The red triangle
 	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
 	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.288675f, 0.5f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	// The red-yellow transition
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-0.288675f, 0.5f, 0.0f);

	// The yellow triangle
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-0.288675f, 0.5f, 0.0f);
	glVertex3f(-0.866025f, 0.5f, 0.0f);

	// The yellow-green transition
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-0.866025f, 0.5f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.577350f, 0.0f, 0.0f);

	// The green triangle
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.577350f, 0.0f, 0.0f);
	glVertex3f(-0.866025f, -0.5f, 0.0f);

	// The green-cyan transition
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.866025f, -0.5f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-0.288675f, -0.5f, 0.0f);

	// The cyan triangle
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-0.288675f, -0.5f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);

	// The cyan-blue transition
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.288675f, -0.5f, 0.0f);

	// The blue triangle
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.288675f, -0.5f, 0.0f);
	glVertex3f(0.866025f, -0.5f, 0.0f);

	// The blue-pink transition
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.866025f, -0.5f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.577350f, 0.0f, 0.0f);

	// The pink triangle
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.577350f, 0.0f, 0.0f);
	glVertex3f(0.866025f, 0.5f, 0.0f);

	// The pink-red transition
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.866025f, 0.5f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.288675f, 0.5f, 0.0f);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	// Initiate window parameters
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Compute the position of center window
	int screen_width = glutGet(GLUT_SCREEN_WIDTH);
	int screen_height = glutGet(GLUT_SCREEN_HEIGHT);
	int window_xpos = (screen_width - 500) / 2;
	int window_ypos = (screen_height - 500) / 2;

	// Create a window
	glutInitWindowPosition(window_xpos, window_ypos);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Experiment01");

	// Display the draw function
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glutDisplayFunc(draw_geometry);
	glutMainLoop();

	return 0;
}
