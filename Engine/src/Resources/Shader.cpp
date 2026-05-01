#include "Resources/Shader.h"
#include "Core/Debug/debug.h"
#include "Core/Debug/loader.h"

using namespace std;

REGISTER_MODULE();

Shader::Shader()
{
    shaderID = 0;
}

std::string Shader::FileToString(const std::string& path)
{
    std::string content;
    std::ifstream fileStream(path, std::ios::in);

    if (!fileStream.is_open()) {
        return "";
    }

    std::stringstream sstr;
    sstr << fileStream.rdbuf();
    content = sstr.str();
    fileStream.close();
    return content;
}

bool Shader::Load(const std::string& path)
{
    string vertexPath = path + signatureVertex;
    string fragmentPath = path + signatureFragment;

    string vertexString = FileToString(vertexPath);
    string fragmentString = FileToString(fragmentPath);

    if (vertexString.empty() || fragmentString.empty()) return false;

    shaderID = glCreateProgram();

    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexString);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentString);

    glAttachShader(shaderID, vs);
    glAttachShader(shaderID, fs);
    glLinkProgram(shaderID);

    int success;
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        Debug::g_Log.Print(infoLog);
        return false;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return true;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        Debug::g_Log.Print(infoLog);
    }

    return id;
}

void Shader::Matrix4D(const std::string& name, const ::Matrix4D& matrix)
{
    GLint location = glGetUniformLocation(shaderID, name.c_str());
    if (location != -1)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, matrix.m);
    }
}