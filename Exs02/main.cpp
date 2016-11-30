#include <GL/glut.h>

static float fTranslate;
static float fRotate;
static float fScale = 1.0f;

/// /////////////////////////////////////////////////////////
/// DRAW FUNCTION:
/// This function draws sample graphics
///
/// Attention:
/// Here we draw a table with given specific shape.
/// This table consists of 5 cuboids:
/// 	CUBOIDS 1:	 length = 5, width = 4, height = 1	
/// 	CUBOIDS 2-5: length = 1, width = 1, height = 3
/// /////////////////////////////////////////////////////////

void Draw()
{
	glPushMatrix();
	glScalef(5.0f, 4.0f, 1.0f);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -2.0f);

	glPushMatrix();
	glTranslatef(1.5f, 1.0f, 0.0f);
	glScalef(1.0f, 1.0f, 3.0f);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5f, -1.0f, 0.0f);
	glScalef(1.0f, 1.0f, 3.0f);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -1.0f, 0.0f);
	glScalef(1.0f, 1.0f, 3.0f);
	glutWireCube(1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.5f, 1.0f, 0.0f);
	glScalef(1.0f, 1.0f, 3.0f);
	glutWireCube(1);
	glPopMatrix();

	glPopMatrix();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{

#if 0 // Set 0 to 1 if you want to display in wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-8.0f, 0.0f, -18.0f);
	glTranslatef(0.0f, fTranslate, 0.0f);
	Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -18.0f);
	glRotatef(fRotate, 0, 1.0f, 0);
	Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 0.0f, -18.0f);
	glScalef(fScale, fScale, fScale);
	Draw();
	glPopMatrix();

	fTranslate += 0.005f;
	fRotate += 0.5f;
	fScale -= 0.005f;

	if(fTranslate > 0.5f) fTranslate = 0.0f;
	if(fScale < 0.5f) fScale = 1.0f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(400, 240);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}

