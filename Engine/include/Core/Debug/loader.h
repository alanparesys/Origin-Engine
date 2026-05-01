#pragma once
#include <iostream>
#include <filesystem>

namespace Debug
{
    class FileLoader
    {
    public:
        FileLoader(const char* filepath)
        {
            std::filesystem::path p(filepath);
            std::cout << "[Engine] Loaded Module: " << p.filename().string() << std::endl;
        }
    };
}

#define REGISTER_MODULE() static Debug::FileLoader fileLoader(__FILE__)