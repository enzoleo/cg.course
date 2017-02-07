#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "bunny.h"

#define BUFSIZE 512

float fRotate = 156.5f;
// Whether to display in perspective mode
GLboolean bPersp = true;
// Whether to display animation
GLboolean bAnim = true;
// Whether to display in wire mode
GLboolean bWire = false;

// Eye position and the center of objects
float eye[] = { 0.0f, 0.9f, 3.0f };
float center[] = { 0.0f, 0.9f, -5.0f };

// Current width and height of window
GLint curWidth = 0, curHeight = 0;

GLint dl = 0;
int drawMode = 0;
GLfloat color[19][4];

/* Default color using namespace */
namespace Color
{
    // Basic color defined by RGBA value
    float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float pureGold[] = { 0.85f, 0.96f, 0.15f, 1.0f };
    float rostyBrown[] = { 0.75f, 0.56f, 0.56f, 1.0f };
    float darkGray[] = { 0.20f, 0.20f, 0.20f, 1.0f };
    float blueViolet[] = { 0.54f, 0.17f, 0.89f, 1.0f };
    float steelBlue[] = { 0.27f, 0.51f, 0.71f, 1.0f };
    float fireBrick[] = { 0.70f, 0.13f, 0.13f, 1.0f };
}

/* The position of bunnies */
GLfloat bunny_position[18][3] =
{
    { -1.0f, -1.0f, 5.5f }, {  0.0f, -1.0f, 5.5f }, {  1.0f, -1.0f, 5.5f },
    { -1.0f,  1.0f, 5.5f }, {  0.0f,  1.0f, 5.5f }, {  1.0f,  1.0f, 5.5f },
    { -1.0f,  0.0f, 5.5f }, {  0.0f,  0.0f, 5.5f }, {  1.0f,  0.0f, 5.5f },
    { -1.0f, -1.0f, 7.5f }, {  0.0f, -1.0f, 7.5f }, {  1.0f, -1.0f, 7.5f },
    { -1.0f,  1.0f, 7.5f }, {  0.0f,  1.0f, 7.5f }, {  1.0f,  1.0f, 7.5f },
    { -1.0f,  0.0f, 7.5f }, {  0.0f,  0.0f, 7.5f }, {  1.0f,  0.0f, 7.5f }
};

/* Initialize color array */
void initColor()
{
    glEnable(GL_DEPTH_TEST);
    for (int i = 0; i < 18; i++)
    {
        color[i][0] = 0.4;
        color[i][1] = 0.4;
        color[i][2] = 0.4;
        color[i][3] = 1.0;
    }
    for (int j = 0; j < 4; j++)
        color[18][j] = Color::darkGray[j];
}

void drawDL()
{
    glCallList(dl);
}

/* Function draws bunnies */
void drawBunny()
{
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(3.0f, 3.0f, 3.0f);
    if (drawMode == 0) drawNaive();
    else if (drawMode == 1) drawVA();
    else drawDL();
}

/* The function to draw a cuboid */
void drawCuboid(float* materialColor)
{
    glScalef(1.0f, 1.0f, 3.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialColor);
    glutSolidCube(1.0f);
}

/* Function draws a table */
void drawTable(GLenum mode)
{
    if (mode == GL_SELECT)  glLoadName(18);

    // Draw the desktop
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.5f);
    glScalef(5.0f, 4.0f, 1.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color[18]);
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw four legs of the table
    glPushMatrix();
    glTranslatef(1.5f, 1.0f, 1.5f);
    drawCuboid(color[18]);
    glPopMatrix(); glPushMatrix();
    glTranslatef(-1.5f, 1.0f, 1.5f);
    drawCuboid(color[18]);
    glPopMatrix(); glPushMatrix();
    glTranslatef(1.5f, -1.0f, 1.5f);
    drawCuboid(color[18]);
    glPopMatrix(); glPushMatrix();
    glTranslatef(-1.5f, -1.0f, 1.5f);
    drawCuboid(color[18]);
    glPopMatrix();
}

/* Function draws all bunnies */
void drawAllBunnies(GLenum mode)
{
    for (int i = 0; i < 18; i++)
    { // Draw 18 bunnies (just for FPS test)
        glPushMatrix();
        if (mode == GL_SELECT)  glLoadName(i);
        glTranslatef(bunny_position[i][0],
                     bunny_position[i][1],
                     bunny_position[i][2]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color[i]);
        drawBunny();
        glPopMatrix();
    }
    drawTable(mode);
}

/* The function to update view */
void updateView(int width, int height)
{
    // Reset the current viewport
    glViewport(0.0f, 0.0f, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Perspective setting
    // If bPersp = false, then construct orthogonal projection
    if (bPersp) gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    else glOrtho(-3.0f, 3.0f, -3.0f, 3.0f, -100.0f, 100.0f);

    // Select The Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
}

/* Reshape function */
void reshape(int width, int height)
{
    // Height is not allowed to be zero
    if (height == 0) height = 1;

    curHeight = height;
    curWidth = width;

    updateView(curWidth, curHeight);
}

void idle()
{
    glutPostRedisplay();
}

/* Keyboard function */
void key(unsigned char k, int x, int y)
{
    switch (k)
    {
    case 27:
    case 'x': exit(0);
    case 'z': bPersp = !bPersp; break;
    case ' ': bAnim = !bAnim; break; 
    case 'c': bWire = !bWire; break; 
    case 'a': eye[0] -= 0.01f; center[0] -= 0.01f; break;
    case 'd': eye[0] += 0.01f; center[0] += 0.01f; break;
    case 'w': eye[1] -= 0.01f; center[1] -= 0.01f; break;
    case 's': eye[1] += 0.01f; center[1] += 0.01f; break;
    case 'q': eye[2] -= 0.01f; center[2] -= 0.01f; break;
    case 'e': eye[2] += 0.01f; center[2] += 0.01f; break;
    case 'r': drawMode++; drawMode %= 3; break; 
    }
}

/* Function computes FPS (Frame Per Second) */
void computeFramePerSecond()
{
    static int frame = 0, curTime, timeBase = 0;
    static char buffer[256];
    
    char mode[64];
    if (drawMode == 0) strcpy(mode, "naive");
    else if (drawMode == 1) strcpy(mode, "vertex array");
    else strcpy(mode, "display list");

    frame++;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    if (curTime - timeBase > 1000)
    {
        sprintf(buffer,"FPS:%4.2f %s", frame * 1000.0f / (curTime - timeBase), mode);
        timeBase = curTime;
        frame = 0;
    }

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, 480.0f, 0.0f, 480.0f, -1.0f, 1.0f);

    // Select the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(10, 10);

    // -----------------------------------------------------------------
    // Show the character buffer.
    // The fontface of FPS string shown on the bottomleft of the window
    // is HELVETICA (GLUT official).
    // The fontsize of FPS string is 18.
    // -----------------------------------------------------------------
    for (char* c = buffer; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    // Pop the projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

/* Redraw function */
void redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Look at objects - settings
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              0.0f, 1.0f, 0.0f);

    // WIRE mode or SOLID mode
    if (bWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat lightPosition[] = { 1.0f, 0.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, Color::white);
    glEnable(GL_LIGHT0);

    // Rotation - animation
    glRotatef(fRotate, 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.2f, 0.2f, 0.2f);
    drawAllBunnies(GL_RENDER);
    if (bAnim) fRotate += 0.5f;

    // Compute frame per second
    computeFramePerSecond();
    glutSwapBuffers();
}

/* Mouse hits process */
void processHits(GLint hits, GLuint buffer[])
{
    GLuint chosen_idx = 0;
    // The number of names
    GLuint names;
    // The buffer pointer
    GLuint *ptr = (GLuint*)buffer;
    // The minimum z-value among all vertices cross the view-frustum
    GLuint min_val_z = buffer[1];
    
    // -----------------------------------------------------------------------------
    // Traversal for each mouse hit
    // A mouse hit record consist of four items:
    // 1. The number of names in name stack when a hit occurs.
    // 2. The minimum and maximum z-value among all vertices cross the view-frustum
    //    after the last hit record.
    // 3. The content of name stack when a hit occurs.
    // 4. Get the number of names from the bottom element, hangle the content of
    //    name stack, get index of the block chosen and change its color.
    // -----------------------------------------------------------------------------
    for (GLuint idx = 0; idx < hits; idx++)
    {
        names = *ptr;
        ptr++;
        if (*ptr < min_val_z)
        { // Find nearest object for each candidate chosen object
            chosen_idx = idx;
            min_val_z = *ptr;
        }
        ptr += names + 2;
    }

    if (hits > 0)
    { // If mouse hits exist, change the color of objects chosen
        for (int j = 0; j < 2; j++)
        {
            color[buffer[3 + 4 * chosen_idx]][j] += 0.5f;
            if (color[buffer[3 + 4 * chosen_idx]][j] > 1.0f)
                color[buffer[3 + 4 * chosen_idx]][j] -= 1.0f;
        }
    }
}

/* Mouse pick function */
void pick(int button, int state, int x, int y)
{
    // The select buffer (saves information chosen)
    GLuint selectbuffer[BUFSIZE];
    
    // The information of objects chosen
    // Save the view matrix before SELECT mode
    GLint hits, viewport[4];

    // Detect the movement and click of mouse
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Create new viewport and set select-buffer (to save hit record)
        glGetIntegerv(GL_VIEWPORT, viewport);
        glSelectBuffer(BUFSIZE, selectbuffer);
        glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(0);
        
        // Save the projection matrix
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 5.0f, 5.0f, viewport);

        // Perspective setting
        // If bPersp = false, then construct orthogonal projection
        if (bPersp) gluPerspective(45.0f, (float)curWidth / (float)curHeight, 0.1f, 100.0f);
        else glOrtho(-3.0f, 3.0f, -3.0f, 3.0f, -100.0f, 100.0f);

        // Reload model view matrix
        // Render table and bunnies under SELECT mode
        glMatrixMode(GL_MODELVIEW);
        drawAllBunnies(GL_SELECT);
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glFlush();

        // Handle the chosen result
        hits = glRenderMode(GL_RENDER);
        processHits(hits, selectbuffer);
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480, 480);
    glutCreateWindow("gl_pick");
    
    initColor();
    glutMouseFunc(pick);
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    dl = Gen3DObjectList();

    glutMainLoop();
    return 0;
}
