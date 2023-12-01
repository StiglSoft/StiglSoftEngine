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
//Should be moved somewhere else
void vec3ToGL(Vector3 o, GLfloat d[]){
    d[0] = o.X;
    d[1] = o.Y;
    d[2] = o.Z;
}
Vector3 calculateLightIntensity(Vector3 lightPosition, float intensity, Vector3 target, Vector3 color){
    float distance = v3magnitude(vec3Sub(lightPosition,target));
    float divFactor = intensity / distance;
    return vec3Mul(color,divFactor);
}
void calculateLights(Vector3 pos){
    GLfloat buff[4];
    buff[3] = 1.0f;
    for(int i =0; i < scriptData.lightsUsed;i++){
        vec3ToGL(
            calculateLightIntensity(
                scriptData.lights[i].position,
                scriptData.lights[i].intensity,
                pos,scriptData.lights[i].color),buff);
        glLightfv(0x4000 + i, GL_DIFFUSE, buff);
    }
}
void Update(){
    //glutGet(GLUT_ELAPSED_TIME);

    //Calculates deltaTime
    t2 = std::chrono::high_resolution_clock::now().time_since_epoch();
    scriptData.deltaTimeUs = static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count());
    t1 = std::chrono::high_resolution_clock::now().time_since_epoch();
    ExecuteUpdates(scripts);
    //Drawing graphics
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(scriptData.FovY, (GLfloat)Width / (GLfloat)Height, 0.8f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for (GameObject go : scriptData.gameobjects) {
        calculateLights(go.transform.position);
        glPushMatrix();
        glLoadIdentity();
        gluLookAt(
            scriptData.cameraPosition.X,scriptData.cameraPosition.Y,scriptData.cameraPosition.Z,
            scriptData.cameraTarget.X,scriptData.cameraTarget.Y,scriptData.cameraTarget.Z,
            scriptData.cameraUp.X,scriptData.cameraUp.Y,scriptData.cameraUp.Z);
        glTranslatef(go.transform.position.X, go.transform.position.Y, go.transform.position.Z);
        glRotatef(go.transform.rotationAngle ,go.transform.rotation.X, go.transform.rotation.Y, go.transform.rotation.Z);
        glColor3f(go.color.R,go.color.G,go.color.B);
        if(go.shape == Shape::wirebox){
            glutWireCube(go.transform.scale);
        }else if(go.shape == Shape::fullbox){
            glutSolidCube(go.transform.scale);
        }else if(go.shape == Shape::wiresphere){
            glutWireSphere(go.transform.scale,10,10);
        }else if(go.shape == Shape::fullspere){
            glutSolidSphere(go.transform.scale,10,10);
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
int InitEngine(int argc, char **argv, const char* title){
    scriptData.keys = keys;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Width, Height);
    glutCreateWindow(title);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHTING);
    if(scriptData.lightsUsed > 7)
        return -1;
    GLfloat buff[4];
    buff[3] = 1.0f;
    for(int i =0; i < scriptData.lightsUsed;i++){
        glEnable(0x4000 + i);
        vec3ToGL(
            vec3Mul(scriptData.lights[i].color,
                    scriptData.lights[i].intensity
            ),buff);
        glLightfv(0x4000 + i, GL_DIFFUSE, buff);
        vec3ToGL(scriptData.lights[i].position,buff);
        glLightfv(0x4000 + i, GL_POSITION, buff);
    }
    glutDisplayFunc(Update);
    glutMouseFunc(MouseCallBack);
    glutPassiveMotionFunc(MouseCallBack2);
    glutKeyboardUpFunc(KeyboardUpCallBack);
    glutKeyboardFunc(KeyboardCallBack);
    glutMainLoop();
    return 0;
}
int main(int argc, char **argv){
    scripts = loadScripts();
    ExecuteStartups(scripts,&scriptData);
    return InitEngine(argc,argv,"Stiglsoft Engine");
}