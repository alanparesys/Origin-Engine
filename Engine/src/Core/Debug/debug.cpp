#include "Core/Debug/debug.h"
#include "Core/Debug/loader.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <chrono>   
#include <iomanip>  
#include <ctime>

REGISTER_MODULE();

namespace Debug
{
    Log g_Log;

    void Log::OpenFile(std::filesystem::path const& filename)
    {
        if (m_file.is_open())
            m_file.close();

        m_file.open(filename, std::ios::out);

        if (!m_file.is_open())
            throw std::runtime_error("Failed to open log file");

        Print("[Log]\n");
    }

    void Log::Print(const char* format, ...)
    {
        // Get current time
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        struct tm local_tm;

#ifdef _WIN32
        localtime_s(&local_tm, &time_t_now);
#else
        local_tm = *localtime(&time_t_now);
#endif

        // Create timestamp [HH:MM:SS]
        char time_str[12];
        strftime(time_str, sizeof(time_str), "[%H:%M:%S] ", &local_tm);

        // Process format and arguments
        char buffer[1024];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        // Output to console
        std::cout << time_str << buffer;

        // Output to file
        if (m_file.is_open())
        {
            m_file << time_str << buffer;
            m_file.flush();
        }
    }

    // Debugging function template : https://learnopengl.com/In-Practice/Debugging
    void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
    {
        // ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        std::cout << "---------------" << std::endl;
        std::cout << "Debug message (" << id << "): " << message << std::endl;

        switch (source)
        {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
        } std::cout << std::endl;

        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
        } std::cout << std::endl;

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
        } std::cout << std::endl;
        std::cout << std::endl;
    }
}