#pragma once
#include <iostream>
#include <vector>

using namespace std;
enum Shape{
    wirebox,
    fullbox,
    fullcustom,
    wirecustom
};
struct Vector2{
    float X = 0;
    float Y = 0;
};
struct Vector3{
    float X = 0;
    float Y = 0;
    float Z = 0;
};
struct Color{
    float R = 1, G = 1, B = 1;
};
struct Vector4{
    float X = 0;
    float Y = 0;
    float Z = 0;
    float W = 0;
};
struct Transform{
    Vector3 position = {0.0f,0.0f,0.0f};
    Vector3 rotation = {0.0f,0.0f,0.0f};
    float scale = 1.0f;
    float rotationAngle = 0.0f; 
};
struct GameObject{
    Transform transform;
    Color color;
    Shape shape = Shape::wirebox;
    vector<Vector3> veticles;
};
struct ScriptData{
    Vector3 cameraPosition = {0.0f,0.0f,0.0f};
    Vector3 cameraTarget = {0.0f,0.0f,0.0f};
    Vector3 cameraUp = {0.0f,1.0f,0.0f};
    float FovY = 60.0f;
    vector<GameObject> gameobjects;
};