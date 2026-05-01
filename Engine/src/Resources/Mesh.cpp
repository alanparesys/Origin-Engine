#define _CRT_SECURE_NO_WARNINGS
#include "Resources/Mesh.h"

REGISTER_MODULE();

Mesh::Mesh()
{
    tex = nullptr;
    obj = new OBJLoader("Map");
    vao = 0;
    vbo = 0;
    res = false;
}

bool Mesh::Load(const std::string& path)
{
    if (vao != 0) glDeleteVertexArrays(1, &vao);
    if (vbo != 0) glDeleteBuffers(1, &vbo);

    if (!obj) obj = new OBJLoader("Map");

    res = obj->loader(path.c_str(), vertices, uvs, normals);

    if (!res) {
        return false;
    }

    if (!tex) {
        tex = new Texture();
        if (!tex->Load("./Assets/Textures/wooden_box.jpg")) {
            std::cout << "[Mesh Error] Failed to load default texture for mesh." << std::endl;
        }
    }

    std::vector<float> vertexData;
    vertexData.reserve(vertices.size() * 5);

    for (size_t i = 0; i < vertices.size(); i++) {
        vertexData.push_back(vertices[i].x);
        vertexData.push_back(vertices[i].y);
        vertexData.push_back(vertices[i].z);

        if (i < uvs.size()) {
            vertexData.push_back(uvs[i].x);
            vertexData.push_back(uvs[i].y);
        }
        else {
            vertexData.push_back(0.0f);
            vertexData.push_back(0.0f);
        }
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Mesh::update(Shader* shader)
{
    if (vao == 0 || shader == nullptr) return;

    shader->Use();

    if (tex && tex->textureID != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex->textureID);
    }

    model = Matrix4D::Identity();
    shader->Matrix4D("model", model);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    if (tex) delete tex;
    if (obj) delete obj;
    if (vao) glDeleteVertexArrays(1, &vao);
    if (vbo) glDeleteBuffers(1, &vbo);
}