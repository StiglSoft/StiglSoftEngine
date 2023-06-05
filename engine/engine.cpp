#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include "../stigengine.h"
#include "scripting.cpp"
ScriptData scriptData;
const int Width = 800;
const int Height = 600;
vector<void*> scripts;
void Update(){
    ExecuteUpdates(scripts);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(scriptData.cameraPosition.X,scriptData.cameraPosition.Y,scriptData.cameraPosition.Z,
    scriptData.cameraTarget.X,scriptData.cameraTarget.Y,scriptData.cameraTarget.Z,
    scriptData.cameraUp.X,scriptData.cameraUp.Y,scriptData.cameraUp.Z);
    for (GameObject go : scriptData.gameobjects) {
        glRotatef(0 ,go.transform.rotation.X, go.transform.rotation.Y, go.transform.rotation.Z);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(go.transform.position.X, go.transform.position.Y, go.transform.position.Z);
        glutWireCube(go.transform.scale);
    }
    glFlush(); 
    glutSwapBuffers();
    glutPostRedisplay();
}
void InitEngine(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("StiglEngine");
    glutDisplayFunc(Update);
    glutMainLoop();
}
int main(int argc, char **argv){
    scripts = loadScripts();
    ExecuteStartups(scripts,&scriptData);
    InitEngine(argc,argv);
}