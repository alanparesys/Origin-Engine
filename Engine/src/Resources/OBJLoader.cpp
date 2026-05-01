#define _CRT_SECURE_NO_WARNINGS
#include "Resources/OBJLoader.h"
#include "Core/Debug/loader.h"

REGISTER_MODULE();

OBJLoader::OBJLoader(std::string name)
{
    this->name = name;
}

bool OBJLoader::loader(const char* path, std::vector<Vector3D>& out_v, std::vector <Vector2D>& out_uv, std::vector<Vector3D>& out_n)
{
    std::vector<unsigned int> vi, uvi, ni;
    std::vector<Vector3D> temp_v;
    std::vector <Vector2D> temp_uv;
    std::vector<Vector3D> temp_n;

    FILE* file = fopen(path, "r");
    if (file == 0)
    {
        std::cout << "error: no file!" << std::endl;
        return false;
    }
    while (1)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);

        if (res == EOF) break;
        if (strcmp(lineHeader, "v") == 0)
        {
            Vector3D vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_v.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0)
        {
            Vector2D uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uv.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            Vector3D normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_n.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            std::string v1, v2, v3;
            unsigned int vx[3], uvx[3], nx[3];
            int matches = fscanf(file,
                "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                &vx[0], &uvx[0], &nx[0],
                &vx[1], &uvx[1], &nx[1],
                &vx[2], &uvx[2], &nx[2]);
            if (matches != 9)
            {
                std::cout << "error: you file cant be read" << std::endl;
                return false;
            }
            vi.push_back(vx[0]);
            vi.push_back(vx[1]);
            vi.push_back(vx[2]);
            uvi.push_back(uvx[0]);
            uvi.push_back(uvx[1]);
            uvi.push_back(uvx[2]);
            ni.push_back(nx[0]);
            ni.push_back(nx[1]);
            ni.push_back(nx[2]);
        }
    }
    for (unsigned int i = 0; i < vi.size(); i++)
    {
        unsigned int vx = vi[i];
        unsigned int uvx = uvi[i];
        unsigned int nx = ni[i];
        Vector3D vertex = temp_v[vx - 1];
        Vector2D texCoord = temp_uv[uvx - 1];
        Vector3D normal = temp_n[nx - 1];
        out_v.push_back(vertex);
        out_uv.push_back(texCoord);
        out_n.push_back(normal);
    }
    fclose(file);
    return true;
}

OBJLoader::~OBJLoader()
{
    std::cout << "deleting " << name << std::endl;
}