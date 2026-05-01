#define _CRT_SECURE_NO_WARNINGS
#include "Core/Debug/debug.h"
#include "Core/Debug/loader.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <cstdio>
#include <iostream>
#include <string>
#include "Resources/resources_manager.h"
#include "Resources/texture.h"
#include "Resources/OBJLoader.h"
#include "Resources/Mesh.h"

REGISTER_MODULE();

void debugFilePath(const std::string& path);

int main()
{
    ResourceManager resourceManager;

    Debug::g_Log.OpenFile("log.txt");

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(Debug::glDebugOutput, nullptr);

    std::cout << "OpenGL loaded successfully" << std::endl;

    DEBUG_LOG("Engine started.");
    debugFilePath("./Assets/Models/sponza.obj");

    glEnable(GL_DEPTH_TEST);

    Shader* shader = resourceManager.Create<Shader>("./Assets/Shaders/default");
    Mesh* mesh = resourceManager.Create<Mesh>("./Assets/Models/sponza.obj");

    Matrix4D projection = Matrix4D::CreatePerspectiveProjectionMatrix(800.0f, 600.0f, 0.1f, 10000.0f, 60.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (mesh && shader)
        {
            shader->Use();

            shader->Matrix4D("projection", projection);

            Matrix4D view = Matrix4D::CreateTransformMatrix(
                Vector3D(0, 0, 0),
                Vector3D(0, -200, -1000),
                Vector3D(1, 1, 1)
            );
            shader->Matrix4D("view", view);

            mesh->update(shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void debugFilePath(const std::string& path)
{
    FILE* file = fopen(path.c_str(), "r");

    if (file) {
        std::string debug_message = "File FOUND: '" + path + "'\n";
        Debug::g_Log.Print(debug_message.c_str());

        char line[256];
        int vertexCount = 0;

        while (fgets(line, sizeof(line), file) && vertexCount < 3) {
            if (line[0] == 'v' && line[1] == ' ') {
                std::cout << "Vertex " << vertexCount + 1 << ": " << line;
                vertexCount++;
            }
        }

        if (vertexCount == 0) {
            std::cout << "Warning: No vertices ('v') found" << std::endl;
        }

        fclose(file);
    }
    else {
        std::cout << "File NOT FOUND: " << path << std::endl;
    }
}