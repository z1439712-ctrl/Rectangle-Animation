#include <GL/glut.h>

float angle = 0.0;
float scale = 1.0;
float colorValue = 0.0;
bool increase = true;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // Move to center
    glTranslatef(0.0, 0.0, 0.0);

    // Rotate in XY direction
    glRotatef(angle, 0.0, 0.0, 1.0);

    // Magnify
    glScalef(scale, scale, 1.0);

    // Color changes gradually from red to white
    glColor3f(1.0, colorValue, colorValue);

    // Draw rectangle
    glBegin(GL_QUADS);
        glVertex2f(-0.3, -0.2);
        glVertex2f( 0.3, -0.2);
        glVertex2f( 0.3,  0.2);
        glVertex2f(-0.3,  0.2);
    glEnd();

    glutSwapBuffers();
}

void update(int value)
{
    // Rotation
    angle += 2.0;

    // Magnify animation
    if (increase)
    {
        scale += 0.01;
        if (scale >= 1.5)
            increase = false;
    }
    else
    {
        scale -= 0.01;
        if (scale <= 0.5)
            increase = true;
    }

    // Color animation (Red -> White)
    colorValue += 0.01;
    if (colorValue > 1.0)
        colorValue = 0.0;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Animated Rectangle");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}