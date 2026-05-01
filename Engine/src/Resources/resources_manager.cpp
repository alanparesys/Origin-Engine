#include "Resources/resources_manager.h"
#include "Core/Debug/debug.h"
#include "Core/Debug/loader.h"
using namespace std;

REGISTER_MODULE();

ResourceManager::ResourceManager()
{

}

void ResourceManager::Delete(std::string path)
{
	delete dict_Resources[path];
	dict_Resources[path] = nullptr;
	dict_Resources.erase(path);
}

ResourceManager::~ResourceManager()
{
}

ostream& operator<<(ostream& os, const ResourceManager& r)
{
	string chain;
	
	//map <string, IResource*>::iterator itr;
	for (auto itr = r.dict_Resources.begin(); itr != r.dict_Resources.end(); ++itr)
		chain+= itr->first;

	return os << chain;
}