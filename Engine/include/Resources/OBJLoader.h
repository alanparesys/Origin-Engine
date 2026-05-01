#pragma once 
#include <vector>
#include <string>
#include <cstring>
#include <iostream>

#include "Core/Maths/vector3D.h"
#include "Core/Maths/vector2D.h"

using namespace std;
class OBJLoader
{
public:
    OBJLoader(string name);
    bool loader(const char* path, vector<Vector3D>& out_v, vector<Vector2D>& out_uv, vector<Vector3D>& out_n);
    ~OBJLoader();
private:
    string name;
};