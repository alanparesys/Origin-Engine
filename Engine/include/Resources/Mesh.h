#pragma once
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "Resources/resources_manager.h"
#include "Core/Maths/vector3D.h"
#include "Core/Maths/vector2D.h"
#include "Core/Maths/matrix4D.h"
#include "Resources/Shader.h"
#include "Resources/OBJLoader.h"
#include "Resources/texture.h"
#include "Core/Debug/loader.h"

using namespace std;

class Mesh : public IResource
{
public:
    Mesh();
    ~Mesh();

    bool Load(const std::string& path) override;

    void update(Shader* shader);

private:
    unsigned int vao, vbo;
    vector<Vector3D> vertices;
    vector<Vector2D> uvs;
    vector<Vector3D> normals;
    Texture* tex;
    OBJLoader* obj;
    bool res;
    Matrix4D model;
};