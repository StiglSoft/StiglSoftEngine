#include <GL/glut.h>
#include <cmath>

GLfloat light_position[] = {0.0f, 5.0f, 5.0f, 1.0f};
GLfloat light_direction = 1.0f;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Stationary cube
    glutSolidCube(2.0);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    // Move the light forward and backward
    //light_position[2] += 2;
    light_position[0] += 0.01;
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Moving Light in GLUT");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    init();

    glutMainLoop();
    return 0;
}
/*
int index = 0;
    if(scriptData.lights.size() < 8)
    for(Light light : scriptData.lights){
        GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
        GLfloat light_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
        GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

        GLfloat position[4], direction[4];
        position[0] = light.position.X;
        position[1] = light.position.Y;
        position[2] = light.position.Z;
        position[3] = 1.0f;
        
        direction[0] = light.rotation.X;
        direction[1] = light.rotation.Y;
        direction[2] = light.rotation.Z;
        direction[3] = 0.0f;
        /*cout << "Index:" << index << " Position: " 
        << position[0] << ", "
        << position[1] << ", "
        << position[2] << ", "
        << position[3] << ", "
        << " Direction: "
        << direction[0] << ", "
        << direction[1] << ", "
        << direction[2] << ", "
        << direction[3] << "\n";
        glEnable(GL_LIGHT0 + index);
        glLightfv(GL_LIGHT0 + index,GL_POSITION,position);
        glLightfv(GL_LIGHT0 + index,GL_SPOT_DIRECTION,direction);
        glLightf(GL_LIGHT0 + index, GL_SPOT_EXPONENT, 2.0f);
        glLightf(GL_LIGHT0 + index, GL_CONSTANT_ATTENUATION, 5.0f);

        glLightfv(GL_LIGHT0 + index,GL_AMBIENT,light_ambient);
        glLightfv(GL_LIGHT0 + index,GL_DIFFUSE,light_diffuse);
        glLightfv(GL_LIGHT0 + index,GL_SPECULAR,light_specular);
        index++;
    }
    */
