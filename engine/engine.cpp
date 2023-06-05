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
    
    for (GameObject go : scriptData.gameobjects) {
        glPushMatrix();
        glLoadIdentity();   
        gluLookAt(scriptData.cameraPosition.X,scriptData.cameraPosition.Y,scriptData.cameraPosition.Z,
            scriptData.cameraTarget.X,scriptData.cameraTarget.Y,scriptData.cameraTarget.Z,
            scriptData.cameraUp.X,scriptData.cameraUp.Y,scriptData.cameraUp.Z);
        glTranslatef(go.transform.position.X, go.transform.position.Y, go.transform.position.Z);
        glRotatef(0 ,go.transform.rotation.X, go.transform.rotation.Y, go.transform.rotation.Z);
        glColor3f(go.color.R,go.color.G,go.color.B);
        glutWireCube(go.transform.scale);
        glPopMatrix();
    }
    glFlush(); 
    glutSwapBuffers();
    glutPostRedisplay();
}
void KeyboardCallBack(unsigned char ch, int x, int y){
    ExecuteKeyboard(scripts,ch);
}
void InitEngine(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Stigl Soft Engine");
    glutDisplayFunc(Update);
    glutKeyboardFunc(KeyboardCallBack);
    glutMainLoop();
}
int main(int argc, char **argv){
    scripts = loadScripts();
    ExecuteStartups(scripts,&scriptData);
    InitEngine(argc,argv);
}