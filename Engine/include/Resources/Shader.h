#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <glad/gl.h>
#include "Resources/resources_manager.h"
#include "Core/Maths/matrix4D.h"

class Shader : public IResource
{
public:
    Shader();
    unsigned int shaderID;

    bool Load(const std::string& path) override;

    void Use() { glUseProgram(shaderID); }

    void Matrix4D(const std::string& name, const ::Matrix4D& matrix);

private:
    std::string signatureVertex = "Vertex.glsl";
    std::string signatureFragment = "Fragment.glsl";

    unsigned int CompileShader(unsigned int type, const std::string& source);
    std::string FileToString(const std::string& path);
};