#include <GL/glut.h>

typedef float point3[3];

static GLfloat viewer[] = {0.0, 0.0, 10.0};

void Axes(void)
{

    point3 x_min = {-5.0, 0.0, 0.0};
    point3 x_max = {5.0, 0.0, 0.0};

    point3 y_min = {0.0, -5.0, 0.0};
    point3 y_max = {0.0, 5.0, 0.0};

    point3 z_min = {0.0, 0.0, -5.0};
    point3 z_max = {0.0, 0.0, 5.0};
    glColor3f(1.0f, 0.0f, 0.0f); // kolor rysowania osi - czerwony
    glBegin(GL_LINES);           // rysowanie osi x
    glVertex3fv(x_min);
    glVertex3fv(x_max);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // kolor rysowania - zielony
    glBegin(GL_LINES);           // rysowanie osi y

    glVertex3fv(y_min);
    glVertex3fv(y_max);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // kolor rysowania - niebieski
    glBegin(GL_LINES);           // rysowanie osi z

    glVertex3fv(z_min);
    glVertex3fv(z_max);
    glEnd();
}

// Funkcja określająca co ma być rysowane (zawsze wywoływana, gdy trzeba przerysować scenę)
void RenderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Zdefiniowanie położenia obserwatora
    gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // Narysowanie osi przy pomocy funkcji zdefiniowanej powyżej
    Axes();

    // Ustawienie koloru rysowania na biały
    glColor3f(1.0f, 1.0f, 1.0f);

    glutWireTeapot(3.0);
    glFlush();
    glutSwapBuffers();
}

void MyInit(void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Ustawienie parametrów dla rzutu perspektywicznego
    gluPerspective(70, 1.0, 1.0, 30.0);

    if (horizontal <= vertical)
        glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

    else
        glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(300, 300);
    glutInit(&argc, argv);
    glutCreateWindow("Rzutowanie perspektywiczne");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    MyInit();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}