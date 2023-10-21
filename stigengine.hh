#pragma once
#include <iostream>
#include <vector>

using namespace std;
enum Shape{
    wirebox,
    fullbox,
    wiresphere,
    fullspere,
    fullcustom,
    wirecustom
};
enum TextureScheme{
    solidcolor,
    texture
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
    bool *keys;
    int mouseX, mouseY, 
        mouseButton,
        deltaTimeUs;
};
Vector3 vec3Add(Vector3 v1, Vector3 v2){return {v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z};}
Vector3 vec3Sub(Vector3 v1, Vector3 v2){return {v1.X - v2.X, v1.Y - v2.Y, v1.Z - v2.Z};}
Vector3 vec3Mul(Vector3 v1, Vector3 v2){return {v1.X * v2.X, v1.Y * v2.Y, v1.Z * v2.Z};}
Vector3 vec3Div(Vector3 v1, Vector3 v2){return {v1.X / v2.X, v1.Y / v2.Y, v1.Z / v2.Z};}

Vector3 vec2Add(Vector2 v1, Vector2 v2){return {v1.X + v2.X, v1.Y + v2.Y};}
Vector3 vec2Sub(Vector2 v1, Vector2 v2){return {v1.X - v2.X, v1.Y - v2.Y};}
Vector3 vec2Mul(Vector2 v1, Vector2 v2){return {v1.X * v2.X, v1.Y * v2.Y};}
Vector3 vec2Div(Vector2 v1, Vector2 v2){return {v1.X / v2.X, v1.Y / v2.Y};}

Vector3 vec3Zero(){return {0,0,0};}
Vector3 vec3One(){return {1,1,1};}
Vector3 vec3UnitX(){return {1,0,0};}
Vector3 vec3UnitY(){return {0,1,0};}
Vector3 vec3UnitZ(){return {0,0,1};}
