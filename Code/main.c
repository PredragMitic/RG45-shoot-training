#include <stdlib.h>
#include <GL/glut.h>

#define INF 2000000

static int veiw_point_x;

static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);
static void on_reshape(int width, int height);
static void init(void);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(1600, 900);
    glutInitWindowPosition(64, 32);
    glutCreateWindow(argv[0]);

    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);

    init();
    glutMainLoop();
    return 0;
}

static void init(void)
{
    glClearColor(0.529, 0.808, 0.922, 0);
    glEnable(GL_DEPTH_TEST);
  
    // Postavljanje pocetne kordinate pogleda po x
    veiw_point_x = 10;

    glPointSize(5);
    glLineWidth(4);
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        // Izlazak iz programa
        exit(0);
        break;
    case 'l':
        // Kretanje pogleda levo po x
        veiw_point_x++;
        glutPostRedisplay();
        break;
    case 'r':
        // Kretanje pogleda desno po x
        veiw_point_x--;
        glutPostRedisplay();
        break;
    }
}

static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 150000);
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Kameru postaviti na 10,2,-4
    gluLookAt(10, 2, -4, veiw_point_x, 0.5, 2, 0, 1, 0);

    // Kordinatni sistem radi lakse orijetacije
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(INF,0,0);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,INF,0);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,INF);
    glEnd();

    // Pomocna linija 
    glBegin(GL_LINES);
        glColor3f(0.5,0.5,1);
        glVertex3f(20,0,0);
        glVertex3f(20,0,INF);
    glEnd();

    // Teren na kome ce biti streliste
    glColor3f(0.3, 0.60, 0.1);
    glBegin(GL_POLYGON);
        glVertex3f(30,0,-10);
        glVertex3f(-10,0,-10);
        glVertex3f(-100,0,300);
        glVertex3f(120,0,300);
    glEnd();

    glutSwapBuffers();
}
