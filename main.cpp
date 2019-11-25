#include <GL/glut.h>
#include <math.h>

typedef float point3[3];

static GLfloat viewer[] = {3.0, 3.0, 10.0};

float up = 0.0;
float side = 0.0;
float r = 10.0;

static GLfloat theta = 0.0; // kąt obrotu obiektu
static GLfloat alfa = 0.0;  // kąt obrotu obiektu
static GLfloat pix2angle;   // przelicznik pikseli na stopnie

static GLint status = 0; // stan klawiszy myszy
                         // 0 - nie naciśnięto żadnego klawisza
                         // 1 - naciśnięty zostać lewy klawisz

static int x_pos_old = 0; // poprzednia pozycja kursora myszy
static int y_pos_old = 0;

static int delta_x = 0; // różnica pomiędzy pozycją bieżącą
                        // i poprzednią kursora myszy

static int delta_y = 0;

void Mouse(int btn, int state, int x, int y)
{

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x_pos_old = x; // przypisanie aktualnie odczytanej pozycji kursora
                       // jako pozycji poprzedniej
        y_pos_old = y;
        status = 1; // wcięnięty został lewy klawisz myszy
    }
    else

        status = 0; // nie został wcięnięty żaden klawisz
}

void Motion(GLsizei x, GLsizei y)
{

    delta_x = x - x_pos_old; // obliczenie różnicy położenia kursora myszy
    delta_y = y - y_pos_old;

    x_pos_old = x; // podstawienie bieżącego położenia jako poprzednie
    y_pos_old = y;
    glutPostRedisplay(); // przerysowanie obrazu sceny
}

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

    // Narysowanie osi przy pomocy funkcji zdefiniowanej powyżej
    Axes();

    if (status == 1) // jeśli lewy klawisz myszy wcięnięty
    {
        theta += delta_x * pix2angle; // modyfikacja kąta obrotu o kat proporcjonalny
        alfa += delta_y * pix2angle;
    }
    
    gluLookAt(r * cos(2 * M_PI * side)*cos(2*M_PI*up), r*sin(2*M_PI*up), r*sin(2*M_PI*side)*cos(2*M_PI*up), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // glRotatef(theta, 0.0, 1.0, 0.0); //obrót obiektu o nowy kąt
    // glRotatef(alfa, 1.0, 0.0, 0.0);
    // glScalef(1.0 + status, 1.0, 1.0);
    glColor3f(1.0f, 1.0f, 1.0f);

    glutWireTeapot(3.0);
    glFlush();
    glutSwapBuffers();
}

void keys(unsigned char key, int x, int y)
{
    if(key == 'z') up += 0.1;
    if(key == 'x') side += 0.1;
    if(key == 'c') r++;
   
    RenderScene(); // przerysowanie obrazu sceny
}


void MyInit(void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
    pix2angle = 360.0 / (float)horizontal; // przeliczenie pikseli na stopnie
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
    glutKeyboardFunc(keys);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(Mouse);
    // Ustala funkcję zwrotną odpowiedzialną za badanie stanu myszy

    glutMotionFunc(Motion);
    // Ustala funkcję zwrotną odpowiedzialną za badanie ruchu myszy
    MyInit();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}