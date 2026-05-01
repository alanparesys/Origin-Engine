#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

#include <glad/gl.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdarg>

namespace Debug
{
#ifdef _DEBUG
#define Assert(condition) if (!(condition)) { __debugbreak(); }
#else
#define Assert(condition) if (!(condition)) { *(int*)0 = 0; }
#endif

    class Log
    {
    public:
        void OpenFile(std::filesystem::path const& filename);
        void Print(const char* format, ...);

    private:
        std::ofstream m_file;
    };

    extern Log g_Log;

#define DEBUG_LOG(format, ...) Debug::g_Log.Print("%s(%d): " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

    void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id,
        GLenum severity, GLsizei length,
        const char* message, const void* userParam);
}