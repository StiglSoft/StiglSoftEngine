#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <GL/gl.h>
#include <GL/glut.h>
#include "../stigengine.hh"
#include "scripting.cpp"
ScriptData scriptData;
const int Width = 1280;
const int Height = 720;
vector<void*> scripts;

std::chrono::high_resolution_clock::duration t1, t2;
bool keys[256];
void Update(){
    //Calculates deltaTime
    t2 = std::chrono::high_resolution_clock::now().time_since_epoch();
    scriptData.deltaTimeUs = static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count());
    t1 = std::chrono::high_resolution_clock::now().time_since_epoch();
    ExecuteUpdates(scripts);
    //Drawing graphics
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(scriptData.FovY, (GLfloat)Width / (GLfloat)Height, 0.8f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for (GameObject go : scriptData.gameobjects) {
        glPushMatrix();
        glLoadIdentity();   
        gluLookAt(scriptData.cameraPosition.X,scriptData.cameraPosition.Y,scriptData.cameraPosition.Z,
            scriptData.cameraTarget.X,scriptData.cameraTarget.Y,scriptData.cameraTarget.Z,
            scriptData.cameraUp.X,scriptData.cameraUp.Y,scriptData.cameraUp.Z);
        glTranslatef(go.transform.position.X, go.transform.position.Y, go.transform.position.Z);
        glRotatef(go.transform.rotationAngle ,go.transform.rotation.X, go.transform.rotation.Y, go.transform.rotation.Z);
        glColor3f(go.color.R,go.color.G,go.color.B);
        if(go.shape == Shape::wirebox){
            glutWireCube(go.transform.scale);
        }else if(go.shape == Shape::fullbox){
            glutSolidCube(go.transform.scale);
        }else if(go.shape == Shape::wirecustom){
            glBegin(GL_LINES);
            for (Vector3 verticle : go.veticles) {
                glVertex3f(verticle.X, verticle.Y, verticle.Z);
            }
            glEnd();
        }else if(go.shape == Shape::fullcustom){
            glBegin(GL_TRIANGLES);
            for (Vector3 verticle : go.veticles) {
                glVertex3f(verticle.X, verticle.Y, verticle.Z);
            }
            glEnd();
        }
        glPopMatrix();
    }
    glFlush(); 
    glutSwapBuffers();
    glutPostRedisplay();
}//Keydown
void KeyboardCallBack(unsigned char ch, int x, int y){
    ExecuteKeyboard(scripts,ch);
    keys[ch] = 1;
}//KeyUp
void KeyboardUpCallBack(unsigned char ch, int x, int y){
    keys[ch] = 0;
}//Mouse click
void MouseCallBack(int button, int state, int x, int y){
    scriptData.mouseButton = button;
}//Mouse move
void MouseCallBack2(int x, int y){
    scriptData.mouseX = x;
    scriptData.mouseY = y;
}
void InitEngine(int argc, char **argv){
    scriptData.keys = keys;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Stigl Soft Engine");
    glutDisplayFunc(Update);
    glutMouseFunc(MouseCallBack);
    glutPassiveMotionFunc(MouseCallBack2);
    glutKeyboardUpFunc(KeyboardUpCallBack);
    glutKeyboardFunc(KeyboardCallBack);
    glutMainLoop();
}
int main(int argc, char **argv){
    scripts = loadScripts();
    ExecuteStartups(scripts,&scriptData);
    InitEngine(argc,argv);
}