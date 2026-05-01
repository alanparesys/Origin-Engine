#pragma once
#include <iostream>
#include <map>

class IResource
{
public:
	virtual ~IResource() = default;
	virtual bool Load(const std::string& path) = 0;
};

class ResourceManager
{
public:
	ResourceManager();

	template <typename T>
	T* Create(std::string path);
	
	template <typename T>
	T* Get(std::string path);

	void Delete(std::string path);

	~ResourceManager();

	std::map <std::string,IResource*> dict_Resources;

};

template<typename T>
inline T* ResourceManager::Create(std::string path)
{
	T* resource = new T;

	if (resource->Load(path))
	{
		dict_Resources[path] = resource;
		return (T*)dict_Resources[path];
	}
	delete resource;
	return nullptr;
}

template<typename T>
inline T* ResourceManager::Get(std::string path)
{
	if (dict_Resources.contains(path))
		return (T*)dict_Resources[path];
	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const ResourceManager& r);