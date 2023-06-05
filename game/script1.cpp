#include <iostream>
#include <vector>
#include "../stigengine.h"
extern "C" {
    float z = 0, direction = 0;
    ScriptData* dataptr;
    void start(ScriptData* sd){
        dataptr = sd;
        Vector3 position = {0,0,0};
        Vector3 rotation = {0,0,0};
        float scale = 1.0f;
        Transform transform = {position,rotation,scale};
        Color clr = {1.0f,1.0f,1.0f};
        dataptr->gameobjects.push_back({transform,clr});
        dataptr->cameraPosition.Z = 5;
    }
    void update(){
        /*if(direction)z -= 0.1f;
        else z += 0.1f;
        if(z > 2)
            direction = 1;
        else if(z < -2)
            direction = 0;
        dataptr->gameobjects[0].transform.position.X= z;*/
    }
    void keyboard(char ch){
        if(ch == 'w'){
            dataptr->gameobjects[0].transform.position.Z+= 0.1f;
        }
    }
}
